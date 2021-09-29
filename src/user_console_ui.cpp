#include "user_console_ui.h"
#include "exceptions.h"

static const char OPEN_LINK[] = "/usr/bin/firefox --new-window "; 
static const char CLOSE_LINK[] = "wmctrl -ic \"$(wmctrl -l | grep 'Mozilla Firefox' | tail -1 | awk '{ print $1 }')\""; 

UserConsoleUI::UserConsoleUI(std::shared_ptr<Repository<Trenchcoat>> repo,
                             std::shared_ptr<Repository<Trenchcoat>> cartRepo) 
    : service(repo, cartRepo) {}

void UserConsoleUI::seeCoats() {
    std::string size("FIRST");

    for (;;) {
        if (size != "FIRST")
            this->displayError("Invalid size. Try again.\n");

        size = this->getString("Size: ");

        bool stop = true;
        try {
            Validator<Trenchcoat>::validSize(size);
        } catch (const InvalidTrenchcoatSize&) {
            stop = false;
        }

        if (!stop && !size.empty())
            continue;

        break;
    }

    std::size_t index = 0;
    bool validInput = true;
    for (;;) {
        auto filteredCoats = this->service.getCoats(size);
        Trenchcoat coat = filteredCoats[index];

        if (filteredCoats.empty()) {
            this->displayError("No coats in this size. Sorry.");

            return;
        }

        if (validInput)
            index = (index + 1) % filteredCoats.size();

        validInput = true;

        system((std::string(OPEN_LINK) + " " + coat.photoLink()).c_str());

        this->displayEntity<Trenchcoat>(coat);
        auto choice = this->getString(
            "Buy (" + std::string(1, BUY_KEY) + 
                "), Skip (" + std::string(1, SKIP_KEY) + 
                ") or Menu (" + std::string(1, MENU_KEY) + 
                "): "
        );

        system(CLOSE_LINK);

        if (choice.size() > 1)
            choice[0] = '\0';

        switch (choice[0]) {
            case BUY_KEY:
                this->service.buyCoat(coat);
                this->displayMessage("Current cost: $" + 
                        std::to_string(this->service.getShoppingCartPrice()));
                break;

            case SKIP_KEY:
                break;

            case MENU_KEY:
                return;
            
            default:
                this->displayError("Invalid choice. Try again.\n");
                validInput = false;
        };

        this->displayMessage("");
    }
}

void UserConsoleUI::showCart() {
    this->displayEntityVector<Trenchcoat>(
        this->service.getShoppingCart()
    );

    this->displayMessage("Cart cost: $" + 
        std::to_string(this->service.getShoppingCartPrice()));
}

void UserConsoleUI::seeCoatsFile() {
    system(service.getDisplayFileCommand().c_str());
}

void UserConsoleUI::exit() {
    this->displayMessage("Exitting...");
}

void UserConsoleUI::displayMenu() {
    this->displayMessage(
        "\n+++++++++++++ USER MODE +++++++++++++\n" +
        std::string(1, LIST_KEY) + ". Show coats.\n" + 
        std::string(1, BASKET_KEY) + ". Show shopping cart.\n" + 
        std::string(1, FILE_LIST_KEY) + ". Show coats (file format)\n" +
        std::string(1, EXIT_KEY) + ". Exit.\n"); 
}

void UserConsoleUI::run() {
    for (;;) {
        this->displayMenu();
        auto choice = this->getString("Your choice: ");

        if (choice.size() > 1)
            choice[0] = '\0';

        switch (choice[0]) {
            case LIST_KEY:
                this->seeCoats();
                break;

            case BASKET_KEY:
                this->showCart();
                break;

            case FILE_LIST_KEY:
                this->seeCoatsFile();
                break;

            case EXIT_KEY:
                this->exit();
                return;
            
            default:
                this->displayError("Invalid choice. Try again.\n");
                break;
        };
    }
}
