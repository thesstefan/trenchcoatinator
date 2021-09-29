#include "buy_widget.h"
#include "size_dialog.h"

#include <QPixmap>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QUrl>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QShortcut>

const unsigned int BuyWidget::IMAGE_WIDTH = 480;
const unsigned int BuyWidget::IMAGE_HEIGHT = 640;

BuyWidget::BuyWidget(std::shared_ptr<UserService> service, QWidget *parent) :
    QDialog(parent), service(service), currentIndex(-1) {
        SizeDialog *dialog = new SizeDialog(this);

        if (dialog->exec() == QDialog::Accepted)
            filterSize = dialog->getSize();

        imageLabel = new QLabel(this);
        imageLabel->setFixedSize(IMAGE_WIDTH, IMAGE_HEIGHT);
        imageLabel->setAlignment(Qt::AlignCenter);

        QVBoxLayout *mainLayout = new QVBoxLayout();

        QPushButton *buyButton = new QPushButton("Buy");
        QPushButton *skipButton = new QPushButton("Skip");

        QObject::connect(buyButton, &QPushButton::clicked, this, &BuyWidget::buy);
        QObject::connect(skipButton, &QPushButton::clicked, this, &BuyWidget::skip);

        QHBoxLayout *buttonLayout = new QHBoxLayout();

        coatLabel = new QLabel(this);
        coatLabel->setAlignment(Qt::AlignCenter);

        costLabel = new QLabel(this);
        costLabel->setAlignment(Qt::AlignCenter);

        buttonLayout->addWidget(buyButton);
        buttonLayout->addWidget(skipButton);

        QHBoxLayout *undoRedoLayout = new QHBoxLayout();

        QShortcut *undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
        QObject::connect(undoShortcut, &QShortcut::activated, this, &BuyWidget::undo); 

        QShortcut *redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
        QObject::connect(redoShortcut, &QShortcut::activated, this, &BuyWidget::redo); 

        QPushButton *undoButton = new QPushButton("Undo");
        QPushButton *redoButton = new QPushButton("Redo");

        QObject::connect(undoButton, &QPushButton::clicked, this, &BuyWidget::undo); 
        QObject::connect(redoButton, &QPushButton::clicked, this, &BuyWidget::redo); 

        undoRedoLayout->addWidget(undoButton);
        undoRedoLayout->addWidget(redoButton);

        mainLayout->addWidget(imageLabel);
        mainLayout->addWidget(coatLabel);
        mainLayout->addLayout(buttonLayout);
        mainLayout->addLayout(undoRedoLayout);
        mainLayout->addWidget(costLabel);

        setLayout(mainLayout);
        nextCoat();
}

static QString getPath(const std::string& link) {
    return "data/" + QString::fromStdString(link).remove(QChar('/'));
}

void BuyWidget::getImage(const std::string& link) {
    auto path = getPath(link);

    if (QFile::exists(path)) {
        QPixmap pix(path);
        pix = pix.scaled(IMAGE_WIDTH, IMAGE_HEIGHT, Qt::KeepAspectRatio);

        imageLabel->setPixmap(pix);

        return;
    }

    QUrl url = QUrl::fromUserInput(QString::fromStdString(link));
    QFile* destinationFile = new QFile(path);

    Q_ASSUME(destinationFile->open(QFile::WriteOnly));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::readyRead, destinationFile,
            [path, destinationFile, reply, this]() { 

            destinationFile->write(reply->readAll()); 
            QPixmap pix(path);
            pix = pix.scaled(IMAGE_WIDTH, IMAGE_HEIGHT, Qt::KeepAspectRatio);

            imageLabel->setPixmap(pix);
    });

    connect(reply, &QNetworkReply::finished, destinationFile, &QFile::deleteLater);
    connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);
}

void BuyWidget::buy() {
    service->buyCoat(service->getCoats(filterSize)[currentIndex]);

    nextCoat();
}

void BuyWidget::skip() {
    nextCoat();
}

void BuyWidget::nextCoat() {
    if (filterSize == "All")
        filterSize = "";
    auto filteredCoats = service->getCoats(filterSize);

    if (filteredCoats.empty()) {
        QMessageBox::warning(this, tr("Empty"),
                             tr("No trenchcoats in this size."),
                             QMessageBox::Ok);

        return;
    }

    bool first = false;
    if (currentIndex == -1)
        first = true;

    currentIndex = (currentIndex + 1) % filteredCoats.size();

    if (currentIndex == 0 && !first)
        QMessageBox::warning(this, tr("Warning"),
                             tr("Reached end of shop. We'll start from the beginning."),
                             QMessageBox::Ok);


    auto coat = filteredCoats[currentIndex];
    costLabel->setText("The cost of the shopping cart is: " + QString::number(
                service->getShoppingCartPrice()));

    coatLabel->setText(QString::fromStdString(coat.string()));

    getImage(coat.photoLink());
}

void BuyWidget::undo() {
    bool done = service->undo();

    if (!done)
        QMessageBox::warning(this, tr("Error"), tr("Nothing to undo!"),
                             QMessageBox::Ok);

    currentIndex--;
    nextCoat();
}

void BuyWidget::redo() {
    bool done = service->redo();

    if (!done)
        QMessageBox::warning(this, tr("Error"), tr("Nothing to redo!"),
                             QMessageBox::Ok);

    currentIndex--;
    nextCoat();
}
