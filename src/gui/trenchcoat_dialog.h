#pragma once

#include <QDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>

#include "../trenchcoat.h"

class TrenchcoatDialog: public QDialog {
    Q_OBJECT

    public:
        TrenchcoatDialog(QWidget *parent = nullptr);
        TrenchcoatDialog(QWidget *parent, 
                unsigned int quantity, double price,
                const std::string& size,
                const std::string& color,
                const std::string& link);

        TrenchcoatData getTrenchcoat() const;

    private:
        QSpinBox *quantitySpinBox;
        QDoubleSpinBox *priceSpinBox;

        QComboBox *colorComboBox;
        QComboBox *sizeComboBox;

        QLineEdit *linkLineEdit;
        QLabel *resultLabel;

    signals:
        void trenchcoatReady(const TrenchcoatData& data);

    public slots:
        void validate();
};
