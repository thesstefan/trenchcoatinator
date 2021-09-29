#pragma once

#include <QTableWidget>
#include <QDialog>

#include "../trenchcoat.h"

class CartWidget : public QDialog {
    Q_OBJECT

    private:
        const std::vector<Trenchcoat>& coats;
        QTableWidget *table;

        void updateTable();

    public:
        CartWidget(const std::vector<Trenchcoat>& coats, 
                   double price,
                   QWidget *parent = nullptr);
};
