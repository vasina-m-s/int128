#ifndef INT128_H
#define INT128_H

#include <string>
#include <string_view>
#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <limits>

class Int128 {
public:
	
	// Конструкторы
	Int128();
	explicit Int128(int64_t value);
	explicit Int128(std::string_view str);

	// преобразования
	explicit operator int64_t() const;
	explicit operator double() const;
	std::string str() const;

	// операторы
	Int128 operator+(const Int128& other) const;
	Int128& operator+=(const Int128& other);

	Int128 operator-(const Int128& other) const;
	Int128& operator-=(const Int128& other);

	Int128& operator*=(const Int128& other);
	Int128 operator*(const Int128& other) const;

	Int128& operator/=(const Int128& other);
	Int128 operator/(const Int128& other) const;

	Int128 operator-() const; // унарный минус

	// Сравнение
	bool operator==(const Int128& other) const;
	bool operator!=(const Int128& other) const;


private:
	__int128 value_;

	static __int128 parseString(std::string_view str);
};

std::ostream& operator<<(std::ostream& os, const Int128& num);

#endif // INT128_H