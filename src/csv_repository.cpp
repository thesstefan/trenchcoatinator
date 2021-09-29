#include "csv_repository.h"
#include "trenchcoat.h"

#include <sstream>

template <>
void CSVRepository<Trenchcoat>::writeEntity(std::ostream& out, const Trenchcoat& coat) {
    out << coat.quantity() << "," << coat.price() << "," << coat.size() << ","
        << coat.color() << "," << coat.photoLink() << std::endl;
}
