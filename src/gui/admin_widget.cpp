#include "admin_widget.h"
#include "stats_widget.h"

#include <QStringList>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QShortcut>

static constexpr unsigned int TABLE_COLUMN_COUNT = 5;
static constexpr unsigned int TABLE_WIDGET_HEIGHT = 330;
static constexpr unsigned int TABLE_WIDGET_MAX_COLUMN_WIDTH = 300;

AdminWidget::AdminWidget(std::shared_ptr<AdminService> service, QWidget *parent) 
    : QWidget(parent), service(service) {
        table = new QTableWidget();

        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);

        table->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table->setColumnCount(TABLE_COLUMN_COUNT);

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(table);

        QHBoxLayout *buttonLayout = new QHBoxLayout();

        QPushButton *addButton = new QPushButton("Add Coat");
        QPushButton *removeButton = new QPushButton("Remove Coat");
        QPushButton *updateButton = new QPushButton("Update Coat");

        QObject::connect(addButton, &QPushButton::clicked, this, &AdminWidget::add);
        QObject::connect(removeButton, &QPushButton::clicked, this, &AdminWidget::remove);
        QObject::connect(updateButton, &QPushButton::clicked, this, &AdminWidget::update);

        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(updateButton);
        buttonLayout->addWidget(removeButton);

        QHBoxLayout *undoRedoLayout = new QHBoxLayout();

        QShortcut *undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
        QObject::connect(undoShortcut, &QShortcut::activated, this, &AdminWidget::undo); 

        QShortcut *redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
        QObject::connect(redoShortcut, &QShortcut::activated, this, &AdminWidget::redo); 

        QPushButton *undoButton = new QPushButton("Undo");
        QPushButton *redoButton = new QPushButton("Redo");

        QObject::connect(undoButton, &QPushButton::clicked, this, &AdminWidget::undo); 
        QObject::connect(redoButton, &QPushButton::clicked, this, &AdminWidget::redo); 

        undoRedoLayout->addWidget(undoButton);
        undoRedoLayout->addWidget(redoButton);

        QPushButton *statsButton = new QPushButton("See Statistics");

        QObject::connect(statsButton, &QPushButton::clicked, this, &AdminWidget::stats);

        layout->addLayout(buttonLayout);
        layout->addLayout(undoRedoLayout);
        layout->addWidget(statsButton);

        setLayout(layout);

        updateTable();
}

void AdminWidget::updateTable() {
    auto coats = service->getAllCoats();

    table->setRowCount(coats.size());

    QStringList headerLabels = { "Price", "Size", "Color", "Quantity", "Link" };
    table->setHorizontalHeaderLabels(headerLabels);

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setMaximumSectionSize(TABLE_WIDGET_MAX_COLUMN_WIDTH);

    for (std::size_t index = 0; index < coats.size(); index++) {
        table->setItem(index, 0, new QTableWidgetItem(QString::number(coats[index].price())));
        table->setItem(index, 1, new QTableWidgetItem(QString::fromStdString(coats[index].size())));
        table->setItem(index, 2, new QTableWidgetItem(QString::fromStdString(coats[index].color())));
        table->setItem(index, 3, new QTableWidgetItem(QString::number(coats[index].quantity())));
        table->setItem(index, 4, new QTableWidgetItem(QString::fromStdString(coats[index].photoLink())));
    }

    table->setFixedSize(table->columnWidth(0) + table->columnWidth(1) + table->columnWidth(2) +
                        table->columnWidth(3) + table->columnWidth(4), TABLE_WIDGET_HEIGHT);
}

void AdminWidget::remove() {
    QModelIndexList indexList = table->selectionModel()->selectedIndexes();

    if (indexList.empty())
        return;

    service->removeCoat(indexList.begin()->row());

    updateTable();
}

void AdminWidget::add() {
    TrenchcoatDialog *dialog = new TrenchcoatDialog(this);

    if (dialog->exec() == QDialog::Accepted) {
        bool status = service->addCoat(dialog->getTrenchcoat());

        if (!status)
            QMessageBox::warning(this, tr("Warning"),
                                 tr("Trenchcoat already exists. Nothing happens."),
                                 QMessageBox::Ok);
    }

    dialog->deleteLater();

    updateTable();
}

void AdminWidget::update() {
    QModelIndexList indexList = table->selectionModel()->selectedIndexes();

    if (indexList.empty())
        return;

    Trenchcoat coat = service->getAllCoats()[indexList.begin()->row()];

    TrenchcoatDialog *dialog = new TrenchcoatDialog(this, 
        coat.quantity(), coat.price(), coat.size(), coat.color(), coat.photoLink());

    if (dialog->exec() == QDialog::Accepted) {
        bool status = service->updateCoat(indexList.begin()->row(), dialog->getTrenchcoat());

        if (!status)
            QMessageBox::warning(this, tr("Warning"),
                                 tr("Trenchcoat already exists. Nothing happens."),
                                 QMessageBox::Ok);
    }

    dialog->deleteLater();

    updateTable();
}

void AdminWidget::stats() {
    StatsWidget *widget = new StatsWidget(service->getAllCoats(), this);

    widget->open();
}

void AdminWidget::undo() {
    bool done = service->undo();

    if (!done)
        QMessageBox::warning(this, tr("Error"), tr("Nothing to undo!"),
                             QMessageBox::Ok);

    updateTable();
}

void AdminWidget::redo() {
    bool done = service->redo();

    if (!done)
        QMessageBox::warning(this, tr("Error"), tr("Nothing to redo!"),
                             QMessageBox::Ok);

    updateTable();
}
