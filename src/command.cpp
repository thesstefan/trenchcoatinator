#include "command.h"

bool AddCommand::exec() {
    return target->add(std::get<Trenchcoat>(param));
}

std::shared_ptr<AdminCommand> AddCommand::getUndo() const {
    return std::shared_ptr<AdminCommand>(new RemoveCommand(target, param));
}

bool RemoveCommand::exec() {
    return target->remove(std::get<Trenchcoat>(param));
}

std::shared_ptr<AdminCommand> RemoveCommand::getUndo() const {
    return std::shared_ptr<AdminCommand>(new AddCommand(target, param));
}

bool UpdateCommand::exec() {
    auto pair = std::get<std::pair<Trenchcoat, Trenchcoat>>(param);

    return target->update(pair.first, pair.second);
}


std::shared_ptr<AdminCommand> UpdateCommand::getUndo() const {
    auto pair = std::get<std::pair<Trenchcoat, Trenchcoat>>(param);

    return std::shared_ptr<AdminCommand>
        (new UpdateCommand(target, std::make_pair(pair.second, pair.first)));
}
