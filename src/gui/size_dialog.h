#pragma once

#include <QDialog>
#include <QComboBox>

#include <string>

class SizeDialog : public QDialog {
    Q_OBJECT

    private:
        QComboBox *sizeBox;

    public:
        SizeDialog(QWidget *parent = nullptr);

        std::string getSize() const;
};
