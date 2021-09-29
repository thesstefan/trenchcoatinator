#include "cart_widget.h"
#include "cart_model.h"
#include "image_delegate.h"

#include <QStringList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QDialogButtonBox>
#include <QLabel>

CartWidget::CartWidget(const std::vector<Trenchcoat>& coats, double price, QWidget *parent) 
    : QDialog(parent), coats(coats) {
        QVBoxLayout *layout = new QVBoxLayout();

        auto tableView = new QTableView(this);
        auto model = new CartModel();
        model->setCoats(QVector<Trenchcoat>(coats.begin(), coats.end()));

        tableView->setModel(model);
        tableView->setItemDelegate(new ImageDelegate(this));

        tableView->resizeColumnsToContents();
        tableView->resizeRowsToContents();

        resize(QSize(1000, 700));

        QLabel *label = new QLabel("The cost of the shopping cart is: " + QString::number(price));

        QDialogButtonBox *buttonBox = 
            new QDialogButtonBox(QDialogButtonBox::Ok);

        QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &CartWidget::accept);

        layout->addWidget(tableView);
        layout->addWidget(label);
        layout->addWidget(buttonBox);

        setLayout(layout);
}
