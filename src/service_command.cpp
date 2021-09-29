#include "service_command.h"

#include <variant>

bool AddCommand::exec() {
    return target->add(std::get<Trenchcoat>(param));
}

std::shared_ptr<ServiceCommand> AddCommand::getUndo() const {
    return std::shared_ptr<ServiceCommand>(new RemoveCommand(target, param));
}

bool RemoveCommand::exec() {
    return target->remove(std::get<Trenchcoat>(param));
}

std::shared_ptr<ServiceCommand> RemoveCommand::getUndo() const {
    return std::shared_ptr<ServiceCommand>(new AddCommand(target, param));
}

bool UpdateCommand::exec() {
    auto pair = std::get<std::pair<Trenchcoat, Trenchcoat>>(param);

    return target->update(pair.first, pair.second);
}

std::shared_ptr<ServiceCommand> UpdateCommand::getUndo() const {
    auto pair = std::get<std::pair<Trenchcoat, Trenchcoat>>(param);

    return std::shared_ptr<ServiceCommand>
        (new UpdateCommand(target, std::make_pair(pair.second, pair.first)));
}

bool ping_pong_stacks(std::stack<std::shared_ptr<ServiceCommand>>& pingStack,
                      std::stack<std::shared_ptr<ServiceCommand>>& pongStack,
                      unsigned int times) {

    if (pingStack.empty() || pingStack.size() % times != 0)
        return false;

    for (unsigned int i = 0; i < times; i++) {
        auto command = pingStack.top();
        pingStack.pop();
        pongStack.push(command->getUndo());

        command->exec();
    }

    return true;
}
