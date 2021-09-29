#pragma once

#include "command.h"

#include "repository.h"
#include "trenchcoat.h"

#include <variant>

class ServiceCommand : public Command<Repository<Trenchcoat>, bool, 
                                    std::variant<Trenchcoat, std::pair<Trenchcoat, Trenchcoat>>> {
    public:
        using Command<Repository<Trenchcoat>, bool, 
                      std::variant<Trenchcoat, std::pair<Trenchcoat, Trenchcoat>>>::Command;

        virtual bool exec() = 0;
        virtual std::shared_ptr<ServiceCommand> getUndo() const = 0;
};

class AddCommand : public ServiceCommand {
    public:
        using ServiceCommand::ServiceCommand;

        bool exec();
        std::shared_ptr<ServiceCommand> getUndo() const;
};

class RemoveCommand : public ServiceCommand {
    public:
        using ServiceCommand::ServiceCommand;

        bool exec();
        std::shared_ptr<ServiceCommand> getUndo() const;
};

class UpdateCommand : public ServiceCommand {
    public:
        using ServiceCommand::ServiceCommand;

        bool exec();
        std::shared_ptr<ServiceCommand> getUndo() const;
};

bool ping_pong_stacks(std::stack<std::shared_ptr<ServiceCommand>>& pingStack,
                      std::stack<std::shared_ptr<ServiceCommand>>& pongStack,
                      unsigned int times = 1);
