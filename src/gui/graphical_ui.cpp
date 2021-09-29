#include "graphical_ui.h"
#include "setup_widget.h"

#include "admin_widget.h"
#include "user_widget.h"

#include "../init_factory.h"

#include <QScreen>
#include <QStyle>
#include <QDesktopWidget>

GraphicalUI::GraphicalUI(int argc, char **argv) : QObject() {
    app = new QApplication(argc, argv);

    main_window = new QMainWindow(nullptr);
    main_window->setWindowTitle(tr("Trenchcoatinator"));

    setup = new SetupWidget();
    main_window->setCentralWidget(setup);

    QObject::connect(setup, &SetupWidget::setupDone, this, &GraphicalUI::setupDone);
    QObject::connect(setup, &SetupWidget::rejected, main_window, &QMainWindow::deleteLater);
}


void GraphicalUI::run() {
    main_window->show();

    app->exec();
}

void GraphicalUI::setupDone() {
    auto service = InitFactory::getService(setup->getOptions());

    if (std::holds_alternative<std::shared_ptr<AdminService>>(service)) {
        AdminWidget *widget = new AdminWidget(std::get<std::shared_ptr<AdminService>>(service), nullptr);

        main_window->setCentralWidget(widget);
        main_window->adjustSize();

        return;
    } else if (std::holds_alternative<std::shared_ptr<UserService>>(service)) {
        UserWidget *widget = new UserWidget(std::get<std::shared_ptr<UserService>>(service), nullptr);

        main_window->setCentralWidget(widget);
        main_window->adjustSize();

        return;
    }
}
