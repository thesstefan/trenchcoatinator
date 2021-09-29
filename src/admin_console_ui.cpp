#include "admin_console_ui.h"

AdminConsoleUI::AdminConsoleUI(std::shared_ptr<Repository<Trenchcoat>> repo) : service(repo) {}

void AdminConsoleUI::addCoat() {
    auto data = this->getCoatData("The data of the trenchcoat to be added: ");
            
    if (!this->service.addCoat(data))
        this->displayError("Trenchcoat already exists.\n");
}

void AdminConsoleUI::removeCoat() {
    if (this->service.getAllCoats().size() == 0) {
        this->displayError("Can't remove. Empty trenchcoat database");

        return;
    }

    this->displayEntityVector<Trenchcoat>(this->service.getAllCoats());

    std::size_t index = this->getPositiveInteger("The index of the trenchcoat to be removed: ",
                                                     this->service.getAllCoats().size(),
                                                     1) - 1;

    if (!this->service.removeCoat(index))
        this->displayError("The trenchcoat does not exist.\n");
}

void AdminConsoleUI::updateCoat() {
    if (this->service.getAllCoats().size() == 0) {
        this->displayError("Can't update. Empty trenchcoat database");

        return;
    }

    this->displayEntityVector<Trenchcoat>(this->service.getAllCoats());

    std::size_t index = this->getPositiveInteger("The index of the trenchcoat to be updated: ",
                                                     this->service.getAllCoats().size(),
                                                     1) - 1;
    auto data = this->getCoatData("The data of the updated trenchcoat: ");

    if (!this->service.updateCoat(index, data)) 
        this->displayError("The updated coat already exists.");
}

void AdminConsoleUI::displayCoats() {
    this->displayEntityVector<Trenchcoat>(this->service.getAllCoats());
}

void AdminConsoleUI::exit() {
    this->displayMessage("Exitting...");
}

void AdminConsoleUI::displayMenu() {
    this->displayMessage(
        "============= ADMIN MODE =============\n" +
        std::string(1, ADD_KEY) + ". Add a coat.\n" +
        std::string(1, REMOVE_KEY) + ". Remove a coat.\n" +
        std::string(1, UPDATE_KEY) + ". Update a coat.\n" +
        std::string(1, LIST_KEY) + ". Display coats.\n" +
        std::string(1, EXIT_KEY) + ". Exit.\n"); 
}

void AdminConsoleUI::run() {
    for (;;) {
        this->displayMenu();

        auto choice = this->getString("Your choice: ");
        if (choice.size() != 1) {
            this->displayError("Invalid choice. Try again.\n");

            continue;
        }
        switch (choice[0]) {
            case ADD_KEY:
                this->addCoat();
                break;

            case REMOVE_KEY:
                this->removeCoat();
                break;

            case UPDATE_KEY:
                this->updateCoat();
                break;

            case LIST_KEY:
                this->displayCoats();
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
