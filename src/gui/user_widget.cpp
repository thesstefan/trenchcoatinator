#include "user_widget.h"
#include "cart_widget.h"
#include "buy_widget.h"

#include <QVBoxLayout>
#include <QPushButton>

UserWidget::UserWidget(std::shared_ptr<UserService> service, QWidget *parent)
    : QWidget(parent), service(service) {
        QVBoxLayout *buttonLayout = new QVBoxLayout();

        QPushButton *buyButton = new QPushButton("Buy Coats");
        QPushButton *seeCartButton = new QPushButton("See Cart");
        QPushButton *fileButton = new QPushButton("See Cart File");

        QObject::connect(buyButton, &QPushButton::clicked, this, &UserWidget::buyCoats);
        QObject::connect(seeCartButton, &QPushButton::clicked, this, &UserWidget::seeCart);
        QObject::connect(fileButton, &QPushButton::clicked, this, &UserWidget::openFile);

        buttonLayout->addWidget(buyButton);
        buttonLayout->addWidget(seeCartButton);
        buttonLayout->addWidget(fileButton);

        setLayout(buttonLayout);
}

void UserWidget::openFile() {
    system(service->getDisplayFileCommand().c_str());
}

void UserWidget::seeCart() {
    CartWidget *dialog = new CartWidget(service->getShoppingCart(), 
                                        service->getShoppingCartPrice(),
                                        this);

    dialog->show();
}

void UserWidget::buyCoats() {
    BuyWidget *widget = new BuyWidget(service, this);

    widget->show();
}
