#pragma once

struct Literal {
    using var_t = std::variant<std::string, double>;
    var_t value;
};

std::ostream& operator<<(std::ostream& output, const Literal& literal);
