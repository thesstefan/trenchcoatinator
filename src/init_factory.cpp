#include "init_factory.h"

const std::string InitFactory::SQL_PATH("data/coats.db");
const std::string InitFactory::FILE_PATH("data/coats.txt");

const std::string InitFactory::HTML_PATH("data/cart.html");
const std::string InitFactory::CSV_PATH("data/cart.csv");

std::shared_ptr<Repository<Trenchcoat>> InitFactory::getCoatRepo(const std::string& type) {
    return std::shared_ptr<Repository<Trenchcoat>>(
        type == "SQL" ?
                static_cast<Repository<Trenchcoat>*>(new SQL_Repository<Trenchcoat>(SQL_PATH)) :
                static_cast<Repository<Trenchcoat>*>(new FileRepository<Trenchcoat>(FILE_PATH)));
}

std::shared_ptr<Repository<Trenchcoat>> InitFactory::getShoppingRepo(const std::string& type) {
    return std::shared_ptr<Repository<Trenchcoat>>(
        type == "HTML" ? 
                static_cast<Repository<Trenchcoat>*>(new HTMLRepository<Trenchcoat>(HTML_PATH)) :
                static_cast<Repository<Trenchcoat>*>(new CSVRepository<Trenchcoat>(CSV_PATH)));
}

std::variant<std::shared_ptr<UserService>, std::shared_ptr<AdminService>>
    InitFactory::getService(const std::vector<std::string>& settings) {
        auto coatRepo = getCoatRepo(settings[0]);
        auto cartRepo = getShoppingRepo(settings[1]);

        std::variant<std::shared_ptr<UserService>, std::shared_ptr<AdminService>> service;

        if (settings[2] == "Admin")
            service = std::make_shared<AdminService>(coatRepo);
        else 
            service = std::make_shared<UserService>(coatRepo, cartRepo);

        return service;
}
