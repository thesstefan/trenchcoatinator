#pragma once

#include "trenchcoat.h"
#include "file_repository.h"
#include "service_command.h"

#include <memory>
#include <stack>

class UserService {
    private:
        std::shared_ptr<Repository<Trenchcoat>> coatRepo;
        std::shared_ptr<Repository<Trenchcoat>> shoppingCart;

        std::stack<std::shared_ptr<ServiceCommand>> undoStack;
        std::stack<std::shared_ptr<ServiceCommand>> redoStack;

    public:
        UserService(std::shared_ptr<Repository<Trenchcoat>>& repo, 
                    std::shared_ptr<Repository<Trenchcoat>>& cartRepo); 

        void buyCoat(const Trenchcoat& coat);
        std::vector<Trenchcoat> getCoats(const std::string& size) const;

        std::vector<Trenchcoat> getShoppingCart() const;
        double getShoppingCartPrice() const;

        std::string getDisplayFileCommand() const;

        bool undo();
        bool redo();
};
