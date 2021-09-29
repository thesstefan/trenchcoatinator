#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "trenchcoat.h"

struct UI {
    virtual void run() = 0;
    virtual ~UI() {};

    protected:
    /*
        virtual void displayError(const std::string& errorMessage) const = 0;
        virtual void displayMessage(const std::string& message) const = 0;

        virtual std::string getString(const std::string& requestMessage) const = 0;
    */
};

struct ConsoleUI : public UI {
    protected:
        void displayError(const std::string& errorMessage) const;
        void displayMessage(const std::string& errorMessage) const;

        std::string getString(const std::string& requestMessage) const;

        TrenchcoatData getCoatData(const std::string& requestMessage) const;

        template <typename Entity>
        void displayEntity(const Entity& trenchcoat) const;

        template <typename Entity>
        void displayEntityVector(const std::vector<Entity>& vec) const;

        unsigned int getPositiveInteger(const std::string& requestMessage,
                                        unsigned int upper_bound,
                                        unsigned int lower_bound = 0) const;
};

template <typename Entity>
void ConsoleUI::displayEntityVector(const std::vector<Entity>& vec) const {
    if (vec.empty()) {
        std::cout << "Empty" << std::endl;

        return;
    }

    std::cout << std::endl;
    for (std::size_t index = 0; index < vec.size(); index++) {
        std::cout << "[" << index + 1 << "] ";

        this->displayEntity(vec.at(index));
    }
    std::cout << std::endl;
}

template <typename Entity>
void ConsoleUI::displayEntity(const Entity& entity) const {
    std::cout << entity;
}
