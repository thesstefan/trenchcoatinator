#pragma once

#include "../console_ui.h"

#include <QApplication>
#include <QObject>
#include <QMainWindow>

#include "setup_widget.h"

class GraphicalUI : public QObject, public UI {
    Q_OBJECT

    public:
        void run();

        GraphicalUI(int argc, char **argv);

    private:
        QApplication *app;
        QMainWindow *main_window;

        SetupWidget *setup;

    public slots:
        void setupDone();
};
