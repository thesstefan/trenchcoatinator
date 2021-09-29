#pragma once

#include <exception>
#include <stdexcept>

struct InvalidTrenchcoat : public std::runtime_error {
    InvalidTrenchcoat(const std::string& msg = "");
};

struct InvalidTrenchcoatQuantity : public InvalidTrenchcoat {
    InvalidTrenchcoatQuantity(const std::string& msg = "");
};

struct InvalidTrenchcoatPrice: public InvalidTrenchcoat {
    InvalidTrenchcoatPrice(const std::string& msg = "");
};

struct InvalidTrenchcoatSize : public InvalidTrenchcoat {
    InvalidTrenchcoatSize(const std::string& msg = "");
};

struct InvalidTrenchcoatColor : public InvalidTrenchcoat {
    InvalidTrenchcoatColor(const std::string& msg = "");
};

struct InvalidTrenchcoatLink : public InvalidTrenchcoat {
    InvalidTrenchcoatLink(const std::string& msg = "");
};

struct RepoReadFail : public std::runtime_error {
    RepoReadFail(const std::string& msg = "");
};

struct SQLQueryFail: public RepoReadFail {
    SQLQueryFail(const std::string& msg = "");
};
