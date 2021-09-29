#pragma once

template <typename Entity>
struct Validator {
    static void valid(const Entity& entity);
};
