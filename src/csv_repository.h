#pragma once

#include "file_repository.h"
#include "trenchcoat.h"

template <typename Entity> requires LessEqualComparable<Entity>
class CSVRepository : public FileRepository<Entity> {
    protected:
        static const std::string HEADER_CONTENT;

        void writeHeader(std::ostream& out);
        void writeFooter(std::ostream& out);

        void writeEntity(std::ostream& out, const Entity& entity);

    public:
        CSVRepository(const std::string& fileName);

        std::string getOpenCommand() const;
};

template <typename Entity> requires LessEqualComparable<Entity>
const std::string CSVRepository<Entity>::HEADER_CONTENT {
    "Quantity,Price,Size,Color,Link"
};

template <typename Entity> requires LessEqualComparable<Entity>
CSVRepository<Entity>::CSVRepository(const std::string& fileName) 
    : FileRepository<Entity>(fileName, true) {}

template <typename Entity> requires LessEqualComparable<Entity>
void CSVRepository<Entity>::writeHeader(std::ostream& out) {
    out << HEADER_CONTENT << std::endl;
}

template <typename Entity> requires LessEqualComparable<Entity>
void CSVRepository<Entity>::writeFooter(std::ostream& out) {}

template <typename Entity> requires LessEqualComparable<Entity>
std::string CSVRepository<Entity>::getOpenCommand() const {
    return std::string("tad " + this->fileName + " >/dev/null 2>&1");
}
