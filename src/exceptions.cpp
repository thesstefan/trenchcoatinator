#include "exceptions.h"

InvalidTrenchcoat::InvalidTrenchcoat
    (const std::string& msg) : std::runtime_error(msg) {}

InvalidTrenchcoatQuantity::InvalidTrenchcoatQuantity
    (const std::string& msg) : InvalidTrenchcoat(msg) {}

InvalidTrenchcoatPrice::InvalidTrenchcoatPrice
    (const std::string& msg) : InvalidTrenchcoat(msg) {}

InvalidTrenchcoatSize::InvalidTrenchcoatSize
    (const std::string& msg) : InvalidTrenchcoat(msg) {}

InvalidTrenchcoatColor::InvalidTrenchcoatColor
    (const std::string& msg) : InvalidTrenchcoat(msg) {}

InvalidTrenchcoatLink::InvalidTrenchcoatLink
    (const std::string& msg) : InvalidTrenchcoat(msg) {}

RepoReadFail::RepoReadFail
    (const std::string& msg) : std::runtime_error(msg) {}

SQLQueryFail::SQLQueryFail
    (const std::string& msg) : RepoReadFail(msg) {}
