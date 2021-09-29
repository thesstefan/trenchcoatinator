#include <QVariant>

#include "sql_repository.h"
#include "trenchcoat.h"

template <>
const QString SQL_Repository<Trenchcoat>::DRIVER("QSQLITE");

template <> 
const QString SQL_Repository<Trenchcoat>::TABLE_NAME("trenchcoats");

template <> 
const QString SQL_Repository<Trenchcoat>::ENTITY_QUERY(
    "SELECT * FROM " + SQL_Repository<Trenchcoat>::TABLE_NAME
);

template <>
const QString SQL_Repository<Trenchcoat>::CREATE_QUERY(
    QString(
    "CREATE TABLE IF NOT EXISTS %1 (\n"
    "quantity INT NOT NULL, \n"
    "price REAL, \n"
    "size TEXT NOT NULL, \n"
    "color TEXT NOT NULL, \n"
    "photoLink TEXT NOT NULL \n);")
        .arg(SQL_Repository<Trenchcoat>::TABLE_NAME));

template <>
void SQL_Repository<Trenchcoat>::readEntity(QSqlQuery& query) {
    const unsigned int quantity = query.value("quantity").toUInt();
    const double price = query.value("price").toDouble();

    const std::string size = query.value("size").toString().toStdString();
    const std::string color = query.value("color").toString().toStdString();
    const std::string link = query.value("photoLink").toString().toStdString();

    Trenchcoat coat(quantity, price, size, color, link);

    Validator<Trenchcoat>::valid(coat);
    MemoryRepository<Trenchcoat>::add(coat);
}

template <>
void SQL_Repository<Trenchcoat>::SQL_add(const Trenchcoat& coat) {
    QSqlQuery query;

    query.prepare(QString("INSERT INTO %1 (quantity, price, size, color, photoLink) "
                          "VALUES (%2, %3, \"%4\", \"%5\", \"%6\");")
                        .arg(
                            SQL_Repository<Trenchcoat>::TABLE_NAME,
                            QString::number(coat.quantity()),
                            QString::number(coat.price()),
                            QString::fromStdString(coat.size()),
                            QString::fromStdString(coat.color()), 
                            QString::fromStdString(coat.photoLink())));

    if (!query.exec())
        throw SQLQueryFail(query.lastError().text().toStdString());
}

template <>
void SQL_Repository<Trenchcoat>::SQL_remove(const Trenchcoat& coat) {
    QSqlQuery query;

    query.prepare(QString("DELETE FROM %1 WHERE "
                          "price = %2 AND color = \"%3\" AND size = \"%4\" AND photoLink = \"%5\";")
                        .arg(
                            SQL_Repository<Trenchcoat>::TABLE_NAME,
                            QString::number(coat.price()),
                            QString::fromStdString(coat.color()), 
                            QString::fromStdString(coat.size()), 
                            QString::fromStdString(coat.photoLink())));

    if (!query.exec())
        throw SQLQueryFail(query.lastError().text().toStdString());
}
