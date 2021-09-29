#include "user_service.h"
#include "console_ui.h"

struct UserConsoleUI : public ConsoleUI {
    UserConsoleUI(std::shared_ptr<Repository<Trenchcoat>> repo,
                  std::shared_ptr<Repository<Trenchcoat>> cartRepo);

    void run() override;

    private:
        UserService service;

        enum KEYS {
            LIST_KEY = '1',
            BASKET_KEY = '2',
            FILE_LIST_KEY = '3',
            EXIT_KEY = '4',

            BUY_KEY = 'B',
            SKIP_KEY = 'S',
            MENU_KEY = 'M'
        };

        void seeCoats();
        void seeCoatsFile();
        void showCart();


        void displayMenu();
        void exit();
};
