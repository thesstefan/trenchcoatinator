#pragma once

#include "repository.h"
#include "trenchcoat.h"
#include "service_command.h"

#include <memory>
#include <variant>
#include <stack>

class AdminService {
    private:
        std::shared_ptr<Repository<Trenchcoat>> coatRepo;

        std::stack<std::shared_ptr<ServiceCommand>> undoStack;
        std::stack<std::shared_ptr<ServiceCommand>> redoStack;

    public:
        AdminService(std::shared_ptr<Repository<Trenchcoat>>& repo);

        bool addCoat(const TrenchcoatData& trenchcoatData);
        bool removeCoat(std::size_t index);
        bool updateCoat(std::size_t index,
                        const TrenchcoatData& trenchcoatData);
        
        std::vector<Trenchcoat> getAllCoats() const;

        bool undo();
        bool redo();
};
