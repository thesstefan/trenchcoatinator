#include "size_dialog.h"

#include "../trenchcoat.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>

SizeDialog::SizeDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Size Dialog");

    sizeBox = new QComboBox(this);
    sizeBox->addItem("All");
    for (const auto& size : TRENCHCOAT_SIZES)
        sizeBox->addItem(QString::fromStdString(size));

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("&Size: "), sizeBox);

    QDialogButtonBox *buttonBox = 
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::rejected, this, &SizeDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SizeDialog::accept);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

std::string SizeDialog::getSize() const {
    return sizeBox->currentText().toStdString();
}
