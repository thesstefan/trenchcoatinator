#include <QFormLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QMessageBox>

#include "../exceptions.h"
#include "trenchcoat_dialog.h"

static constexpr long MAX_TRENCHCOAT_INPUT_QUANTITY = 500000;
static constexpr long MAX_TRENCHCOAT_INPUT_PRICE = 500000;

TrenchcoatDialog::TrenchcoatDialog(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("Trenchcoat Dialog");

    this->quantitySpinBox = new QSpinBox(this);
    this->quantitySpinBox->setRange(1, MAX_TRENCHCOAT_INPUT_QUANTITY);

    this->priceSpinBox= new QDoubleSpinBox(this);
    this->priceSpinBox->setRange(1, MAX_TRENCHCOAT_INPUT_PRICE);

    colorComboBox = new QComboBox(this);
    for (const auto& color : TRENCHCOAT_COLORS)
        colorComboBox->addItem(QString::fromStdString(color));

    sizeComboBox = new QComboBox(this);
    for (const auto& size : TRENCHCOAT_SIZES)
        sizeComboBox->addItem(QString::fromStdString(size));

    this->linkLineEdit = new QLineEdit(this);
    this->linkLineEdit->setMaxLength(32);

    QFormLayout *formLayout = new QFormLayout();

    formLayout->addRow(tr("&Quantity: "), quantitySpinBox);
    formLayout->addRow(tr("&Price: "), priceSpinBox);
    formLayout->addRow(tr("&Size: "), sizeComboBox);
    formLayout->addRow(tr("&Color: "), colorComboBox);
    formLayout->addRow(tr("&Link: "), linkLineEdit);

    QDialogButtonBox *buttonBox = 
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::rejected, this, &TrenchcoatDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &TrenchcoatDialog::validate);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    this->setLayout(mainLayout);
}

TrenchcoatDialog::TrenchcoatDialog(QWidget *parent, 
        unsigned int quantity, double price, const std::string& size,
        const std::string& color, const std::string& photoLink) : QDialog(parent) {
    this->setWindowTitle("Trenchcoat Dialog");

    this->quantitySpinBox = new QSpinBox(this);
    this->quantitySpinBox->setRange(1, MAX_TRENCHCOAT_INPUT_QUANTITY);
    quantitySpinBox->setValue(quantity);

    this->priceSpinBox= new QDoubleSpinBox(this);
    this->priceSpinBox->setRange(1, MAX_TRENCHCOAT_INPUT_PRICE);
    priceSpinBox->setValue(price);

    colorComboBox = new QComboBox(this);
    for (const auto& color : TRENCHCOAT_COLORS)
        colorComboBox->addItem(QString::fromStdString(color));
    colorComboBox->setCurrentText(QString::fromStdString(color));

    sizeComboBox = new QComboBox(this);
    for (const auto& size : TRENCHCOAT_SIZES)
        sizeComboBox->addItem(QString::fromStdString(size));
    sizeComboBox->setCurrentText(QString::fromStdString(size));

    this->linkLineEdit = new QLineEdit(this);
    this->linkLineEdit->setMaxLength(32);
    linkLineEdit->setText(QString::fromStdString(photoLink));

    QFormLayout *formLayout = new QFormLayout();

    formLayout->addRow(tr("&Quantity: "), quantitySpinBox);
    formLayout->addRow(tr("&Price: "), priceSpinBox);
    formLayout->addRow(tr("&Size: "), sizeComboBox);
    formLayout->addRow(tr("&Color: "), colorComboBox);
    formLayout->addRow(tr("&Link: "), linkLineEdit);

    QDialogButtonBox *buttonBox = 
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::rejected, this, &TrenchcoatDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &TrenchcoatDialog::validate);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    this->setLayout(mainLayout);
}

void TrenchcoatDialog::validate() {
    auto coatData = getTrenchcoat();

    try {
        Validator<Trenchcoat>::valid(std::make_from_tuple<Trenchcoat>(coatData));
    } catch (const InvalidTrenchcoat& exception) {
        int ret = QMessageBox::warning(this, tr("Invalid Trenchcoat"),
                               tr("The trenchcoat data is invalid. Try again"),
                               QMessageBox::Ok);

        return;
    }

    accept();
}

TrenchcoatData TrenchcoatDialog::getTrenchcoat() const {
    return TrenchcoatData(quantitySpinBox->value(), 
                          priceSpinBox->value(), 
                          sizeComboBox->currentText().toStdString(),
                          colorComboBox->currentText().toStdString(),
                          linkLineEdit->text().toStdString());
}
