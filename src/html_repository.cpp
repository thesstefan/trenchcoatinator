#include "html_repository.h"
#include "trenchcoat.h"

#include <sstream>

template <>
void HTMLRepository<Trenchcoat>::writeEntity(std::ostream& out, const Trenchcoat& coat) {
    out << "    <tr>" << std::endl;

    out << "            <td>" << coat.quantity() << "</td>" << std::endl;
    out << "            <td>" << coat.price() << "</td>" << std::endl;
    out << "            <td>" << coat.size() << "</td>" << std::endl;
    out << "            <td>" << coat.color() << "</td>" << std::endl;
    out << "            <td><a href=" << coat.photoLink() << ">Link</a></td>" << std::endl;

    out << "    </tr>" << std::endl;
}
