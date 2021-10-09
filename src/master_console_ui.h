#pragma once

#include "console_ui.h"

#include <memory>

class MasterConsoleUI {
    private:
        std::string getCoatRepoType() const;
        std::string getShoppingCartRepoType() const;
        std::unique_ptr<UI> getConsoleUI() const;

    public:
        void run(int argc, char **argv);
};

