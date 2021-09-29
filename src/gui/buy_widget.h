#pragma once

#include <QDialog>
#include <QLabel>
#include <QStringLiteral>

#include "../user_service.h"

class BuyWidget : public QDialog {
    Q_OBJECT

    private:
        std::shared_ptr<UserService> service;
        static const QString IMAGE_PATH;

        static const unsigned int IMAGE_WIDTH;
        static const unsigned int IMAGE_HEIGHT;

        QLabel *imageLabel;
        QLabel *costLabel;
        QLabel *coatLabel;
        std::string filterSize;

        void getImage(const std::string& link);
        void nextCoat();

        int currentIndex;

    public:
        BuyWidget(std::shared_ptr<UserService> service, QWidget *parent = nullptr);

    public slots:
        void buy();
        void skip();

        void undo();
        void redo();
};
