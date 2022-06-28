#include "Literal.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

template<class>
inline constexpr bool always_false_v = false;

std::ostream& operator<<(std::ostream& output, const Literal& literal)
{
    std::visit([&output](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>)
            output << std::to_string(arg);
        else if constexpr (std::is_same_v<T, double>)
            output << std::to_string(arg);
        else if constexpr (std::is_same_v<T, std::string>)
            output << arg;
        else
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
    },
               literal.value);

    return output;
}
