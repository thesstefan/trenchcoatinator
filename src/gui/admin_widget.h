#pragma once

#include <QWidget>
#include <QTableWidget>

#include "trenchcoat_dialog.h"
#include "../admin_service.h"

class AdminWidget : public QWidget {
    Q_OBJECT

    private:
        std::shared_ptr<AdminService> service;

        QTableWidget *table;

        void updateTable();

    public:
        AdminWidget(std::shared_ptr<AdminService> service, QWidget *parent);

    public slots:
        void remove();
        void add();
        void update();
        void stats();

        void undo();
        void redo();
};
