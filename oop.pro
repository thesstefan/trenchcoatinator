QT += sql widgets core network charts
CONFIG += c++2a force_debug_info
DEFINES += DEBUG

SOURCES +=  src/main.cpp \
            src/exceptions.cpp \
            src/trenchcoat.cpp \
            src/csv_repository.cpp \
            src/html_repository.cpp \
            src/sql_repository.cpp \
            src/user_service.cpp \
            src/admin_service.cpp \
            src/console_ui.cpp \
            src/admin_console_ui.cpp \
            src/user_console_ui.cpp \
            src/gui/trenchcoat_dialog.cpp \
            src/gui/admin_widget.cpp \
            src/gui/user_widget.cpp \
            src/gui/setup_widget.cpp \
            src/gui/graphical_ui.cpp \
            src/gui/cart_widget.cpp \
            src/gui/buy_widget.cpp \
            src/gui/size_dialog.cpp \
            src/gui/stats_widget.cpp \
            src/init_factory.cpp \
            src/service_command.cpp \
            src/gui/cart_model.cpp \
            src/gui/image_delegate.cpp \

HEADERS +=  src/exceptions.h \
            src/trenchcoat.h \
            src/validator.h \
            src/console_ui.h \ 
            src/repository.h \
            src/memory_repository.h \
            src/file_repository.h \
            src/csv_repository.h \
            src/html_repository.h \
            src/sql_repository.h \
            src/admin_service.h \
            src/user_service.h \
            src/console_ui.h \
            src/admin_console_ui.h \
            src/user_console_ui.h \
            src/gui/trenchcoat_dialog.h \
            src/gui/admin_widget.h \
            src/gui/user_widget.h \
            src/gui/setup_widget.h \
            src/gui/graphical_ui.h \
            src/gui/cart_widget.h \
            src/gui/buy_widget.h \
            src/gui/size_dialog.h \
            src/gui/stats_widget.h \
            src/init_factory.h \
            src/command.h \
            src/service_command.h \
            src/gui/cart_model.h \
            src/gui/image_delegate.h \

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = data

TARGET = oop
