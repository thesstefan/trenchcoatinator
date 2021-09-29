#include "user_service.h"

#include "html_repository.h"
#include "csv_repository.h"

#include "service_command.h"

#include <functional>
#include <algorithm>
#include <numeric>

UserService::UserService(std::shared_ptr<Repository<Trenchcoat>>& repo,
                         std::shared_ptr<Repository<Trenchcoat>>& cartRepo) 
    : coatRepo(repo), shoppingCart(cartRepo) {}

void UserService::buyCoat(const Trenchcoat& coat) {
    auto newCoat(coat);
    newCoat.quantity(coat.quantity() - 1);

    std::shared_ptr<ServiceCommand> command(nullptr);

    if (newCoat.quantity() == 0)
        command.reset(new RemoveCommand(coatRepo, coat));
    else
        command.reset(new UpdateCommand(coatRepo, std::make_pair(coat, newCoat)));

    command->exec();
    undoStack.push(command->getUndo());

    while (!redoStack.empty()) 
        redoStack.pop();

    auto cart = shoppingCart->getAll();
    auto shopCartIt = std::find(cart.begin(), cart.end(), coat);

    if (shopCartIt != cart.end()) {
        newCoat.quantity(shopCartIt->quantity() + 1);

        auto oldCoat(coat);
        oldCoat.quantity(newCoat.quantity() - 1);

        command.reset(new UpdateCommand(shoppingCart, std::make_pair(oldCoat, newCoat)));
        command->exec();

        undoStack.push(command->getUndo());

        return;
    }

    newCoat.quantity(1);
    
    command.reset(new AddCommand(shoppingCart, newCoat));
    command->exec();

    undoStack.push(command->getUndo());
}

double UserService::getShoppingCartPrice() const {
    std::vector<double> prices(shoppingCart->size());
    const auto cart = shoppingCart->getAll();

    std::for_each(cart.begin(), cart.end(),
                  [&prices](const auto &coat) 
                    { prices.push_back(coat.price() * coat.quantity()); });

    return std::accumulate(prices.begin(), prices.end(), 0.0);
}

std::vector<Trenchcoat> UserService::getCoats(const std::string& size) const {
    std::vector<Trenchcoat> coats(this->coatRepo->getAll());

    if (!size.empty())
        coats.erase(std::remove_if(coats.begin(), coats.end(),
                       [&size](const Trenchcoat& coat) 
                            { return coat.size() != size; }),
                    coats.end());

    return coats;
}

std::vector<Trenchcoat> UserService::getShoppingCart() const {
    return this->shoppingCart->getAll();
}

std::string UserService::getDisplayFileCommand() const {
    return this->shoppingCart->getOpenCommand();
}

bool UserService::undo() {
    return ping_pong_stacks(undoStack, redoStack, 2);
}

bool UserService::redo() {
    return ping_pong_stacks(redoStack, undoStack, 2);
}
