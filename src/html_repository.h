#pragma once

#include "file_repository.h"
#include "trenchcoat.h"

template <typename Entity> requires LessEqualComparable<Entity>
class HTMLRepository : public FileRepository<Entity> {
    protected:
        static const std::string HEADER_CONTENT;
        static const std::string FOOTER_CONTENT;

        void writeHeader(std::ostream& out);
        void writeFooter(std::ostream& out);

        void writeEntity(std::ostream& out, const Entity& entity);

    public:
        HTMLRepository(const std::string& fileName);

        std::string getOpenCommand() const;
};

template <typename Entity> requires LessEqualComparable<Entity>
const std::string HTMLRepository<Entity>::HEADER_CONTENT {
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "   <title>Trenchcoats</title>\n"
    "</head>\n"
    "<body>\n"
    "<table border=\"1\">\n"
    "   <tr>"
    "           <th>Quantity</th>"
    "           <th>Price ($)</th>"
    "           <th>Size</th>"
    "           <th>Color</th>"
    "           <th>Link</th>"
    "   <tr>"
};

template <typename Entity> requires LessEqualComparable<Entity>
const std::string HTMLRepository<Entity>::FOOTER_CONTENT {
    "</table>\n"
    "</body>\n"
    "</html>"
};

template <typename Entity>
requires LessEqualComparable<Entity>
HTMLRepository<Entity>::HTMLRepository(const std::string& fileName) 
    : FileRepository<Entity>(fileName, true) {}

template <typename Entity>
requires LessEqualComparable<Entity>
void HTMLRepository<Entity>::writeHeader(std::ostream& out) {
    out << HEADER_CONTENT;
}

template <typename Entity>
requires LessEqualComparable<Entity>
void HTMLRepository<Entity>::writeFooter(std::ostream& out) {
    out << FOOTER_CONTENT;
}

template <typename Entity> requires LessEqualComparable<Entity>
std::string HTMLRepository<Entity>::getOpenCommand() const {
    return std::string("firefox --new-window " + this->fileName);
}
