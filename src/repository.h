#pragma once

#include <string>
#include <concepts>
#include <functional>
#include <vector>

template <typename Entity>
class Repository {
    public:
        virtual std::size_t size() const = 0;
        virtual std::vector<Entity> getAll() const = 0;

        virtual std::string getOpenCommand() const = 0;

        virtual bool add(const Entity& entity) = 0;
        virtual bool remove(const Entity& entity) = 0;
        virtual bool update(const Entity& old_entity, const Entity& updated_entity) = 0;
        virtual bool find(const Entity& entity) const = 0;

        virtual ~Repository() {};
};
