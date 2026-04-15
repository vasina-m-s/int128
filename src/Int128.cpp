#include "Int128.hpp"

#include <string>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <cctype>
#include <sstream>





// Конструктор
Int128::Int128() : value_(0) {}
Int128::Int128(int64_t value) : value_(value) {}
Int128::Int128(std::string_view str) { value_ = parseString(str); }

// Преобразование
Int128::operator int64_t() const { return static_cast<int64_t>(value_); }
Int128::operator double() const { return static_cast<double>(value_); }
std::string Int128::str() const { return std::to_string((int64_t)value_); }


// Внутренний парсинг строки
__int128 Int128::parseString(std::string_view str) {
    size_t start = 0;
    while (start < str.size() && isspace(str[start])) ++start;
    size_t end = str.size();
    while (end > start && isspace(str[end - 1])) --end;
    if (start >= end) {
        throw std::invalid_argument("Empty string");
    }
    std::string s(str.substr(start, end - start));
    bool negative = false;
    if (s[0] == '-') {
        negative = true;
        s.erase(0, 1);
    } else if (s[0] == '+') {
        s.erase(0, 1);
    }

    if (s.empty() || !all_of(s.begin(), s.end(), ::isdigit)) {
        throw std::invalid_argument("Invalid number format");
    }

    __int128 result = 0;
    for (char c : s) {
        result = result * 10 + (c - '0');
    }

    if (negative) result = -result;

    return result;
}



// Арифметические операции
Int128 Int128::operator+(const Int128& other) const {
	__int128 res = value_ + other.value_;
	return Int128(res);
}
Int128& Int128::operator+=(const Int128& other) {
	*this = *this + other;
	return *this;
}


Int128 Int128::operator-(const Int128& other) const {
	__int128 res = value_ - other.value_;
	return Int128(res);
}
Int128& Int128::operator-=(const Int128& other) {
	*this = *this - other;
	return *this;
}


Int128 Int128::operator*(const Int128& other) const {
	__int128 res = value_ * other.value_;
	return Int128(res);
}
Int128& Int128::operator*=(const Int128& other) {
	*this = *this * other;
	return *this;
}


Int128 Int128::operator/(const Int128& other) const {
	if (other.value_ == 0) {
		throw std::domain_error("Division by zero");
	}
	__int128 res = value_ / other.value_;
	return Int128(res);
}
Int128& Int128::operator/=(const Int128& other) {
	*this = *this / other;
	return *this;
}


Int128 Int128::operator-() const {
	return Int128(-value_);
}



// Сравнение
bool Int128::operator==(const Int128& other) const {
	return value_ == other.value_;
}
bool Int128::operator!=(const Int128& other) const {
	return value_ != other.value_;
}


// Вывод в поток
std::ostream& operator<<(std::ostream& os, const Int128& num) {
    os << num.str();
    return os;
}