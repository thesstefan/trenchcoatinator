#include "console_ui.h"
#include "exceptions.h"

#include <iostream>
#include <tuple>

void ConsoleUI::displayError(const std::string& errorMessage) const {
    std::cerr << errorMessage << std::endl;
}

void ConsoleUI::displayMessage(const std::string& message) const {
    std::cout << message << std::endl;
}

std::string ConsoleUI::getString(const std::string& requestMessage) const {
    std::cout << requestMessage;

    std::string input;
    std::getline(std::cin, input);

    return input;
}

TrenchcoatData ConsoleUI::getCoatData(const std::string& requestMessage) const {
    bool first = true;

    while (true) {
        if (first == true)
            this->displayMessage(requestMessage);
        else 
            this->displayError("Invalid trenchcoat data. Try again.\n");

        first = false;

        auto quantity_str = this->getString("Quantity: ");
        auto price_str = this->getString("Price: ");
        auto size = this->getString("Size: ");
        auto color = this->getString("Color: ");
        auto photoLink = this->getString("Photo: ");

        try { 
            TrenchcoatData data = std::make_tuple(std::stoul(quantity_str), std::stod(price_str),
                                                  size, color, photoLink);
            Validator<Trenchcoat>::validData(data);

            return data;
        } catch (const std::invalid_argument& exception) {
            continue;
        } catch (const InvalidTrenchcoat& exception) {
            continue;
        }
    }
}

unsigned int ConsoleUI::getPositiveInteger(const std::string& requestMessage,
                                           unsigned int upper_bound,
                                           unsigned int lower_bound) const {
    long index = -1;
    bool first = true;

    while (index < (long long) lower_bound || index > (long long) upper_bound) {
        if (!first)
            this->displayError("This is not a positive integer in [" 
                                + std::to_string(lower_bound) + ", " 
                                + std::to_string(upper_bound) + "]. Try again.\n");

        std::cout << requestMessage;
        first = false;

        std::string input_str;
        std::getline(std::cin, input_str);

        try {
            index = std::stol(input_str);
        } catch (const std::exception& exception) {
            continue;
        }
    }

    return (unsigned int) index;
}
