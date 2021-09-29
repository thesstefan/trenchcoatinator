#pragma once

#include <memory>
#include <stack>

template <typename Target, typename Return_t, typename Param_t>
class Command {
    protected:
        std::shared_ptr<Target> target;
        const Param_t param;

    public:
        Command(std::shared_ptr<Target> target, const Param_t& param)
            : target(target), param(param) {}

        virtual Return_t exec() = 0;
};
