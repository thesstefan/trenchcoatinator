#include "setup_widget.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QComboBox>

#include <string>
#include <vector>

SetupWidget::SetupWidget(QWidget *parent) : QDialog(parent) {
    coatsCombo = new QComboBox(this);
    cartCombo = new QComboBox(this);
    modeCombo = new QComboBox(this);

    coatsCombo->addItem("Text");
    coatsCombo->addItem("SQL");

    cartCombo->addItem("HTML");
    cartCombo->addItem("CSV");

    modeCombo->addItem("Admin");
    modeCombo->addItem("User");

    QFormLayout *formLayout = new QFormLayout();

    formLayout->addRow(tr("&Coat File: "), coatsCombo);
    formLayout->addRow(tr("&Shopping Output File: "), cartCombo);
    formLayout->addRow(tr("&Mode: "), modeCombo);

    QDialogButtonBox *buttonBox = 
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &SetupWidget::donePressed);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &SetupWidget::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

std::vector<std::string> SetupWidget::getOptions() const {
    return { 
        coatsCombo->currentText().toStdString(), 
        cartCombo->currentText().toStdString(), 
        modeCombo->currentText().toStdString()
    };
}

void SetupWidget::donePressed() {
    emit setupDone();
}
