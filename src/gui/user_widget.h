#pragma once

#include <QWidget>
#include <QTableWidget>

#include "../user_service.h"

class UserWidget : public QWidget {
    Q_OBJECT

    private:
        std::shared_ptr<UserService> service;

        void updateTable();

    public:
        UserWidget(std::shared_ptr<UserService> service, QWidget *parent);

    public slots:
        void openFile();
        void seeCart();
        void buyCoats();
};
