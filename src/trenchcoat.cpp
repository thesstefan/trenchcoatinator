#include "trenchcoat.h"
#include "exceptions.h"

#include <tuple>
#include <algorithm>
#include <iostream>
#include <sstream>

static std::string stringGetUpper(const std::string& string) {
    auto copy(string);

    std::transform(copy.begin(), copy.end(), copy.begin(), ::toupper);

    return copy;
}

Trenchcoat::Trenchcoat() :
    _quantity(0), _price(0), _size(""), _color(""), _photoLink("") {}

Trenchcoat::Trenchcoat(unsigned int quantity, double price,
                       const std::string& size, const std::string& color, const std::string& photoLink) :
    _quantity(quantity), _price(price), _size(stringGetUpper(size)), _color(stringGetUpper(color)), _photoLink(photoLink) {}

Trenchcoat::Trenchcoat(const Trenchcoat& coat) :
    _quantity(coat._quantity), _price(coat._price), _size(coat._size), _color(coat._color), _photoLink(coat._photoLink) {}

Trenchcoat::Trenchcoat(Trenchcoat&& coat) :
    _quantity(std::move(coat._quantity)), _price(std::move(coat._price)), _size(std::move(coat._size)), _color(std::move(coat._color)), _photoLink(std::move(coat._photoLink)) {}

Trenchcoat& Trenchcoat::operator=(const Trenchcoat& other) {
    _quantity = other._quantity;
    _price = other._price;
    _size = other._size;
    _color = other._color;
    _photoLink = other._photoLink;

    return *this;
}

Trenchcoat& Trenchcoat::operator=(Trenchcoat&& other) {
    _quantity = std::move(other._quantity);
    _price = std::move(other._price);
    _size = std::move(other._size);
    _color = std::move(other._color);
    _photoLink = std::move(other._photoLink);

    return *this;
}

bool Trenchcoat::operator==(const Trenchcoat& other) const {
    return 
           this->_price == other._price &&
           this->_size == other._size &&
           this->_color == other._color &&
           this->_photoLink == other._photoLink;
}

bool Trenchcoat::operator<(const Trenchcoat& other) const {
    return std::tie(this->_price, this->_size, this->_color, this->_photoLink) <
           std::tie(other._price, other._size, other._color, other._photoLink);
}

const std::string& Trenchcoat::size() const { return this->_size; }

void Trenchcoat::size(const std::string& size) { this->_size = size; }

const std::string& Trenchcoat::color() const { return this->_color; }
void Trenchcoat::color(const std::string& color) { this->_color = color; }

const std::string& Trenchcoat::photoLink() const { return this->_photoLink; }
void Trenchcoat::photoLink(const std::string& photoLink) { this->_photoLink = photoLink; }

unsigned int Trenchcoat::quantity() const { return this->_quantity; }
void Trenchcoat::quantity(unsigned int quantity) { this->_quantity = quantity; } 

double Trenchcoat::price() const { return this->_price; }
void Trenchcoat::price(double price) { this->_price = price; }

void Validator<Trenchcoat>::validQuantity(unsigned int quantity) {
    if (quantity == 0)
        throw InvalidTrenchcoatQuantity("Invalid trenchcoat quantity: " + std::to_string(quantity));
}

void Validator<Trenchcoat>::validPrice(double price) {
    if (price < 0)
        throw InvalidTrenchcoatPrice("Invalid trenchcoat price: " + std::to_string(price));
}

void Validator<Trenchcoat>::validSize(const std::string& size) {
    if (std::find(TRENCHCOAT_SIZES.begin(), TRENCHCOAT_SIZES.end(), stringGetUpper(size))
            == TRENCHCOAT_SIZES.end())
        throw InvalidTrenchcoatSize("Trenchcoat invalid size: " + size);
}

void Validator<Trenchcoat>::validColor(const std::string& color) {
    if (std::find(TRENCHCOAT_COLORS.begin(), TRENCHCOAT_COLORS.end(), stringGetUpper(color)) 
            == TRENCHCOAT_COLORS.end())
        throw InvalidTrenchcoatColor("Trenchcoat invalid color: " + color);
}

void Validator<Trenchcoat>::validPhotoLink(const std::string& photoLink) {
    if (photoLink.empty())
        throw InvalidTrenchcoatLink("Invalid trenchcoat link: " + photoLink);
}

void Validator<Trenchcoat>::validData(const TrenchcoatData& data) {
    const auto [quantity, price, size, color, photoLink] = data;

    Validator<Trenchcoat>::validQuantity(quantity);
    Validator<Trenchcoat>::validPrice(price);
    Validator<Trenchcoat>::validSize(size);
    Validator<Trenchcoat>::validColor(color);
    Validator<Trenchcoat>::validPhotoLink(photoLink);
}

void Validator<Trenchcoat>::valid(const Trenchcoat& coat) {
    Validator<Trenchcoat>::validQuantity(coat.quantity());
    Validator<Trenchcoat>::validPrice(coat.price());
    Validator<Trenchcoat>::validSize(coat.size());
    Validator<Trenchcoat>::validColor(coat.color());
    Validator<Trenchcoat>::validPhotoLink(coat.photoLink());
}

std::istream& operator>>(std::istream& in, Trenchcoat &trenchcoat) {
    std::string line, field;
    std::getline(in, line);
    std::stringstream stream(line);

    std::getline(stream, field, ' ');
    unsigned int quantity = std::stoul(field);

    std::getline(stream, field, ' ');
    double price = std::stod(field);

    std::getline(stream, field, ' ');
    std::string size(field);

    std::getline(stream, field, ' ');
    std::string color(field);

    std::getline(stream, field, ' ');
    std::string link(field);

    trenchcoat = Trenchcoat(quantity, price, size, color, link);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Trenchcoat &trenchcoat) {
    out << trenchcoat.quantity() << " " 
        << trenchcoat.price() << " "
        << trenchcoat.size() << " "
        << trenchcoat.color() << " "
        << trenchcoat.photoLink() << std::endl;

    return out;
}

std::string Trenchcoat::string() const {
    std::stringstream ss;

    ss << "Quantity: " << quantity()
       << ", Price: " << price() 
       << ", Size: " << size() 
       << ", Color: " << color();

    return ss.str();
}
