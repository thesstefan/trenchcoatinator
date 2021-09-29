#pragma once

#include <string>
#include <concepts>
#include <functional>
#include <vector>

#include "repository.h"

template <typename T>
concept LessEqualComparable = std::equality_comparable<T> && std::strict_weak_order<std::less<T>, T, T>;

template <typename Entity> requires LessEqualComparable<Entity>
class MemoryRepository : public Repository<Entity> {
    protected:
        typedef typename std::vector<Entity>::iterator          iterator;
        typedef typename std::vector<Entity>::const_iterator    const_iterator;

        std::vector<Entity> data;

        iterator _find(const Entity& entity);

    public:
        MemoryRepository();
        MemoryRepository(const MemoryRepository& repository);
        MemoryRepository(MemoryRepository&& repository);

        std::size_t size() const;
        std::vector<Entity> getAll() const;

        virtual std::string getOpenCommand() const;

        virtual bool add(const Entity& entity);
        virtual bool remove(const Entity& entity);
        virtual bool update(const Entity& old_entity, const Entity& updated_entity);

        bool find(const Entity& entity) const;

        virtual ~MemoryRepository();
};

template <typename Entity> requires LessEqualComparable<Entity>
MemoryRepository<Entity>::MemoryRepository() {}

template <typename Entity> requires LessEqualComparable<Entity>
MemoryRepository<Entity>::MemoryRepository(const MemoryRepository& other) : data(other.data) {}

template <typename Entity> requires LessEqualComparable<Entity>
MemoryRepository<Entity>::MemoryRepository(MemoryRepository&& other) : data(std::move(other.data)) {}

template <typename Entity> requires LessEqualComparable<Entity>
std::string MemoryRepository<Entity>::getOpenCommand() const {
    return std::string("");
}

template <typename Entity> requires LessEqualComparable<Entity>
std::size_t MemoryRepository<Entity>::size() const {
    return this->data.size();
}

template <typename Entity> requires LessEqualComparable<Entity>
std::vector<Entity> MemoryRepository<Entity>::getAll() const {
    return this->data;
}

template <typename Entity> requires LessEqualComparable<Entity>
typename MemoryRepository<Entity>::iterator MemoryRepository<Entity>::_find(const Entity& entity) {
    return std::lower_bound(this->data.begin(), this->data.end(), entity, std::less());
}

template <typename Entity> requires LessEqualComparable<Entity>
bool MemoryRepository<Entity>::find(const Entity& entity) const {
    auto it = std::lower_bound(this->data.cbegin(), this->data.cend(), entity, std::less());

    return it != this->data.cend() && *it == entity;
}

template <typename Entity> requires LessEqualComparable<Entity>
bool MemoryRepository<Entity>::add(const Entity& entity) {
    auto it = this->_find(entity);

    if (it == this->data.end() || *it != entity) {
        this->data.insert(it, entity);

        return true;
    }

    return false;
}

template <typename Entity> requires LessEqualComparable<Entity>
bool MemoryRepository<Entity>::remove(const Entity& entity) {
    auto it = this->_find(entity);

    if (*it != entity) 
        return false;

    this->data.erase(it);

    return true;
}

template <typename Entity> requires LessEqualComparable<Entity>
bool MemoryRepository<Entity>::update(const Entity& old_entity, const Entity& updated_entity) {
    auto it = this->_find(old_entity);

    if (it == this->data.end() || *it != old_entity)
        return false;

    auto updated_it = this->_find(updated_entity);

    if (updated_it != this->data.end() && *updated_it == updated_entity && updated_entity != old_entity)
        return false;

    this->data.erase(it);
    
    if (updated_it <= it)
        this->data.insert(updated_it, updated_entity);
    else
        this->data.insert(updated_it - 1, updated_entity);

    return true;
}

template <typename Entity> requires LessEqualComparable<Entity>
MemoryRepository<Entity>::~MemoryRepository() {}

