#pragma once

#include <variant>
#include <vector>
#include <memory>

#include "sql_repository.h"
#include "html_repository.h"
#include "csv_repository.h"

#include "user_service.h"
#include "admin_service.h"

class InitFactory {
    private:
        static const std::string SQL_PATH;
        static const std::string FILE_PATH;

        static const std::string HTML_PATH;
        static const std::string CSV_PATH;

    public:
        static std::shared_ptr<Repository<Trenchcoat>> getCoatRepo(const std::string& type);
        static std::shared_ptr<Repository<Trenchcoat>> getShoppingRepo(const std::string& type);

        static std::variant<std::shared_ptr<UserService>, std::shared_ptr<AdminService>>
            getService(const std::vector<std::string>& settings);
};
