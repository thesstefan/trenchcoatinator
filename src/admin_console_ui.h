#include "console_ui.h"
#include "admin_service.h"

#include <memory>

struct AdminConsoleUI : public ConsoleUI {
    AdminConsoleUI(std::shared_ptr<Repository<Trenchcoat>> repo);

    void run() override;

    private:
        AdminService service;

        enum KEYS {
            ADD_KEY = '1',
            REMOVE_KEY = '2',
            UPDATE_KEY = '3',
            LIST_KEY = '4',
            EXIT_KEY = '5'
        };

        void addCoat();
        void removeCoat();
        void updateCoat();
        void displayCoats();

        void displayMenu();
        void exit();
};
