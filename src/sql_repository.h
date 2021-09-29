#pragma once

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QString>

#include "exceptions.h"
#include "memory_repository.h"

template <typename Entity> requires LessEqualComparable<Entity>
class SQL_Repository : public MemoryRepository<Entity> {
    protected:
        const static QString DRIVER;
        const static QString TABLE_NAME;
        const static QString ENTITY_QUERY;
        const static QString CREATE_QUERY;

        QString db_filename;
        QSqlQuery query;
        QSqlDatabase db;

        void readEntity(QSqlQuery& query);
        void SQL_add(const Entity& entity);
        void SQL_remove(const Entity& entity);

        void loadAll();

    public:
        bool add(const Entity& entity);
        bool remove(const Entity& entity);
        bool update(const Entity& old_entity, const Entity& new_entity);

        std::string getOpenCommand() const;

        SQL_Repository(const std::string& db_filename);
};

template <typename Entity> requires LessEqualComparable<Entity>
SQL_Repository<Entity>::SQL_Repository(const std::string& db_filename) 
    : db_filename(QString::fromStdString(db_filename)) {

    if (QSqlDatabase::isDriverAvailable(SQL_Repository<Entity>::DRIVER) == false)
        throw RepoReadFail("Not available SQL driver: " + SQL_Repository<Entity>::DRIVER.toStdString());

    this->db = QSqlDatabase::addDatabase(SQL_Repository<Entity>::DRIVER);
    this->db.setDatabaseName(QString::fromStdString(db_filename));

    this->query = QSqlQuery(this->db);

    if (this->db.open() == false)
        throw RepoReadFail("SQL: " + db.lastError().text().toStdString());

    QSqlQuery query;
    query.prepare(SQL_Repository<Entity>::CREATE_QUERY);

    if (!query.exec())
        throw SQLQueryFail(query.lastError().text().toStdString());

    this->loadAll();
}

template <typename Entity> requires LessEqualComparable<Entity>
void SQL_Repository<Entity>::loadAll() {
    if (this->query.prepare(ENTITY_QUERY) == false)
        throw RepoReadFail("SQL: " + query.lastError().text().toStdString());

    if (!query.exec())
        throw RepoReadFail("SQL: " + query.lastError().text().toStdString());

    if (!query.first())
        return;

    while (query.isValid()) {
        readEntity(query);

        query.next();
    }
}

template <typename Entity> requires LessEqualComparable<Entity>
bool SQL_Repository<Entity>::add(const Entity& entity) {
    if (MemoryRepository<Entity>::add(entity) == false)
        return false;

    SQL_add(entity);
    return true;
}

template <typename Entity> requires LessEqualComparable<Entity>
bool SQL_Repository<Entity>::remove(const Entity& entity) {
    if (MemoryRepository<Entity>::remove(entity) == false)
        return false;

    SQL_remove(entity);
    return true;
}

template <typename Entity> requires LessEqualComparable<Entity>
bool SQL_Repository<Entity>::update(const Entity& old_entity, const Entity& new_entity) {
    if (MemoryRepository<Entity>::update(old_entity, new_entity) == false)
        return false;

    SQL_remove(old_entity);
    SQL_add(new_entity);

    return true;
}

template <typename Entity> requires LessEqualComparable<Entity>
std::string SQL_Repository<Entity>::getOpenCommand() const {
    return std::string("");
}
