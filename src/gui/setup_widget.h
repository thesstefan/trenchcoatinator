#pragma once

#include <QComboBox>
#include <QStringList>
#include <QDialog>

#include <string>
#include <vector>

class SetupWidget : public QDialog {
    Q_OBJECT

    private:
        QComboBox *coatsCombo;
        QComboBox *cartCombo;
        QComboBox *modeCombo;

    public:
        SetupWidget(QWidget *parent = nullptr);

        std::vector<std::string> getOptions() const;

    public slots:
        void donePressed();

    signals:
        void setupDone();
};
