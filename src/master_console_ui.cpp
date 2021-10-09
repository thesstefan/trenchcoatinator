#include "master_console_ui.h"

#include "init_factory.h"
#include "gui/graphical_ui.h"

#include "user_console_ui.h"
#include "admin_console_ui.h"

std::string MasterConsoleUI::getCoatRepoType() const {
    std::string input;

    do {
        std::cout << "Use SQL Trenchcoat Database? (Y=SQL/N=FILE): ";
        std::getline(std::cin, input);
    } while (input != "Y" && input != "N");

    return input == "Y" ? "SQL" : "FILE";
}

std::string MasterConsoleUI::getShoppingCartRepoType() const {
    std::string input;

    do {
        std::cout << "Use HTML Shopping Cart Output? (Y=HTML/N=CSV): ";
        std::getline(std::cin, input);
    } while (input != "Y" && input != "N");

    return input == "Y" ? "HTML" : "CSV";
}

std::unique_ptr<UI> MasterConsoleUI::getConsoleUI() const {
    std::string input; 

    do {
        std::cout << "Admin (A) or User (U)? ";
        std::getline(std::cin, input);
    } while (input != "A" && input != "U");

    auto coatRepo = InitFactory::getCoatRepo(this->getCoatRepoType());
    auto shoppingRepo = InitFactory::getShoppingRepo(this->getShoppingCartRepoType());

    if (input == "A")
        return std::unique_ptr<UI>(new AdminConsoleUI(coatRepo));

    return std::unique_ptr<UI>(new UserConsoleUI(coatRepo, shoppingRepo));
}

void MasterConsoleUI::run(int argc, char **argv) {
    std::string input;

    do {
        std::cout << "Use GUI? (Y/N): ";
        std::getline(std::cin, input);
    } while (input != "Y" && input != "N");

    auto gui = GraphicalUI(argc, argv);

    input == "Y" ? gui.run() : this->getConsoleUI()->run();
}
