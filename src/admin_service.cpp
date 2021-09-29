#include <variant>

#include "admin_service.h"
#include "service_command.h"

AdminService::AdminService(std::shared_ptr<Repository<Trenchcoat>>& repo) : coatRepo(repo) {}

bool AdminService::addCoat(const TrenchcoatData& trenchcoatData) {
    auto addCommand = std::make_shared<AddCommand>
        (coatRepo, std::make_from_tuple<Trenchcoat>(trenchcoatData));

    undoStack.push(addCommand->getUndo());

    while (!redoStack.empty()) 
        redoStack.pop();

    return addCommand->exec();
}

bool AdminService::removeCoat(std::size_t index) {
    auto removeCommand = std::make_shared<RemoveCommand>(coatRepo, coatRepo->getAll()[index]);

    undoStack.push(removeCommand->getUndo());

    while (!redoStack.empty()) 
        redoStack.pop();

    return removeCommand->exec();
}

bool AdminService::updateCoat(std::size_t index, const TrenchcoatData& trenchcoatData) {
    auto updateCommand = std::make_shared<UpdateCommand>(coatRepo, 
            std::make_pair(coatRepo->getAll()[index], std::make_from_tuple<Trenchcoat>(trenchcoatData)));

    undoStack.push(updateCommand->getUndo());

    while (!redoStack.empty()) 
        redoStack.pop();

    return updateCommand->exec();
}

std::vector<Trenchcoat> AdminService::getAllCoats() const {
    return this->coatRepo->getAll();
}

bool AdminService::undo() {
    return ping_pong_stacks(undoStack, redoStack);
}

bool AdminService::redo() {
    return ping_pong_stacks(redoStack, undoStack);
}
