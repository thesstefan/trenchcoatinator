#pragma once 

#include <fstream>

#include "validator.h"
#include "memory_repository.h"
#include "exceptions.h"

template <typename Entity> requires LessEqualComparable<Entity>
class FileRepository : public MemoryRepository<Entity> {
    protected:
        static const std::string HEADER_CONTENT;
        static const std::string FOOTER_CONTENT;

        const std::string fileName;

        void loadAll();
        void storeAll();

        virtual void readHeader(std::istream& in);
        virtual void writeHeader(std::ostream& out);

        virtual void readFooter(std::istream& in) {};
        virtual void writeFooter(std::ostream& out) {};

        virtual void readEntity(std::istream& in, Entity& entity);
        virtual void writeEntity(std::ostream& out, const Entity& entity);

    public:
        FileRepository(const std::string& fileName, bool writeOnly = false);

        virtual std::string getOpenCommand() const;

        bool remove(const Entity& entity);
        bool update(const Entity& old_entity, const Entity& updated_entity);
        bool add(const Entity& entity);

        virtual ~FileRepository();
};

template <typename Entity> requires LessEqualComparable<Entity>
const std::string FileRepository<Entity>::HEADER_CONTENT("--- FILE REPOSITORY ---");

template <typename Entity> requires LessEqualComparable<Entity>
void FileRepository<Entity>::readHeader(std::istream& in) {
    std::string line;
    std::getline(in, line);

    if (line != FileRepository<Entity>::HEADER_CONTENT)
        throw RepoReadFail("Failed to read plain text repo header");
}

template <typename Entity> requires LessEqualComparable<Entity>
void FileRepository<Entity>::writeHeader(std::ostream& out) {
    out << FileRepository<Entity>::HEADER_CONTENT << std::endl;
}

template <typename Entity> requires LessEqualComparable<Entity>
void FileRepository<Entity>::readEntity(std::istream& in, Entity& entity) {
    in >> entity;
}

template <typename Entity> requires LessEqualComparable<Entity>
void FileRepository<Entity>::writeEntity(std::ostream& out, const Entity& entity) {
    out << entity;
}

template <typename Entity> requires LessEqualComparable<Entity>
void FileRepository<Entity>::loadAll() {
    std::ifstream in(this->fileName);

    readHeader(in);

    bool done = false;
    while (in.good() && !done) {
        Entity entity;

        try {
            readEntity(in, entity);
        } catch (...) {
            if (in.eof())
                done = true;
            else
                throw RepoReadFail("Can't read repo");
        }

        if (done)
            continue;

        Validator<Entity>::valid(entity);
        MemoryRepository<Entity>::add(entity);
    }

    readFooter(in);

    in.close();
}

template <typename Entity> requires LessEqualComparable<Entity>
void FileRepository<Entity>::storeAll() {
    std::ofstream out(this->fileName);

    writeHeader(out);

    for (const Entity& entity : this->getAll())
        writeEntity(out, entity);

    writeFooter(out);

    out.close();
}

template <typename Entity> requires LessEqualComparable<Entity>
FileRepository<Entity>::FileRepository(const std::string& fileName, bool writeOnly) 
    : MemoryRepository<Entity>(), fileName(fileName) {
        if (writeOnly) {
            std::ofstream temp(fileName);
            temp.close();

            return;
        }

        loadAll();
}

template <typename Entity> requires LessEqualComparable<Entity>
bool FileRepository<Entity>::add(const Entity& entity) {
    bool status = MemoryRepository<Entity>::add(entity);

    storeAll();

    return status;
}

template <typename Entity> requires LessEqualComparable<Entity>
bool FileRepository<Entity>::remove(const Entity& entity) {
    bool status = MemoryRepository<Entity>::remove(entity);

    storeAll();

    return status;
}

template <typename Entity> requires LessEqualComparable<Entity>
bool FileRepository<Entity>::update(const Entity& oldEntity, const Entity& updatedEntity) {
    bool status = MemoryRepository<Entity>::update(oldEntity, updatedEntity);

    storeAll();

    return status;
}

template <typename Entity> requires LessEqualComparable<Entity>
FileRepository<Entity>::~FileRepository() {}

template <typename Entity> requires LessEqualComparable<Entity>
std::string FileRepository<Entity>::getOpenCommand() const {
    return std::string("mousepad " + this->fileName);
}
