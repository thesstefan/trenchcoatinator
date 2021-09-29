#pragma once

#include "validator.h"

#include <string>
#include <array>

class Trenchcoat {
    private:
        unsigned int _quantity;
        double _price;

        std::string _size;
        std::string _color;
        std::string _photoLink;

    public:
        Trenchcoat();
        Trenchcoat(unsigned int quantity, double price,
                   const std::string& size, const std::string& color, const std::string& photoLink);

        Trenchcoat(const Trenchcoat& coat);
        Trenchcoat(Trenchcoat&& coat);

        Trenchcoat& operator=(const Trenchcoat& coat);
        Trenchcoat& operator=(Trenchcoat&& coat);

        bool operator==(const Trenchcoat& other) const;
        bool operator<(const Trenchcoat& other) const;

        const std::string& size() const;
        void size(const std::string& size);

        const std::string& color() const;
        void color(const std::string& size);

        const std::string& photoLink() const;
        void photoLink(const std::string& photoLink);

        unsigned int quantity() const;
        void quantity(unsigned int quantity);

        double price() const;
        void price(double price);

        std::string string() const;
};

std::istream& operator>>(std::istream& in, Trenchcoat& coat);
std::ostream& operator<<(std::ostream& out, const Trenchcoat& coat);

typedef std::tuple<unsigned int, double, std::string, std::string, std::string> TrenchcoatData;

template <>
struct Validator<Trenchcoat> {
    static void validSize(const std::string& size);
    static void validColor(const std::string& color);
    static void validPrice(double price);
    static void validQuantity(unsigned int quantity);
    static void validPhotoLink(const std::string& photoLink);

    static void validData(const TrenchcoatData &data);
    static void valid(const Trenchcoat &coat);
};

constexpr unsigned int TRENCHCOAT_COLOR_COUNT = 7;

const std::array<std::string, TRENCHCOAT_COLOR_COUNT> TRENCHCOAT_COLORS {
    "RED", "BLUE", "GREEN", "ORANGE", "YELLOW", "PURPLE", "BLACK" 
};

const std::array<std::string, 5> TRENCHCOAT_SIZES {
    "S", "M", "L", "XL", "XXL"
};
