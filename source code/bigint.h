/*
 * bigInt.h
 *
 *  Created on: 2015Äê10ÔÂ19ÈÕ
 *      Author: ThinkPad
 */

#ifndef BIGINT_H_
#define BIGINT_H_
#include <vector>
#include <string>
using namespace std;
class BigInt {
public:
	BigInt();
	BigInt(const char *str);
	BigInt(int i);
	BigInt(const BigInt &bi);
	~BigInt();

	bool from_string(const char* str);
	void to_string(char *str);

	BigInt operator+(const BigInt&) const;
	BigInt operator+(const int&) const;
	friend BigInt operator+(const int&, const BigInt&);
	BigInt operator-(const BigInt&) const;
	BigInt operator-(const int&) const;
	friend BigInt operator-(const int&, const BigInt&);
	BigInt operator*(const BigInt&) const;
	BigInt operator*(const int&) const;
	friend BigInt operator*(const int&, const BigInt&);
	BigInt operator/(const BigInt&) const;
	BigInt operator/(const int&) const;
	friend BigInt operator/(const int&, const BigInt&);
	BigInt operator%(const BigInt&) const;
	BigInt operator%(const int&) const;
	friend BigInt operator%(const int&, const BigInt&);
	BigInt &operator=(const BigInt&);
	BigInt &operator=(const int&);
	BigInt &operator++();
	BigInt operator++(int);
	BigInt &operator--();
	BigInt operator--(int);
	bool operator==(const BigInt&) const;
	bool operator==(const int&) const;
	friend bool operator==(const int&, const BigInt&);
	bool operator>(const BigInt&) const;
	bool operator>(const int&) const;
	friend bool operator>(const int&, const BigInt&);
	bool operator>=(const BigInt&) const;
	bool operator>=(const int&) const;
	friend bool operator>=(const int&, const BigInt&);
	bool operator<(const BigInt&) const;
	bool operator<(const int&) const;
	friend bool operator<(const int&, const BigInt&);
	bool operator<=(const BigInt&) const;
	bool operator<=(const int&) const;
	friend bool operator<=(const int&, const BigInt&);
	bool operator!=(const BigInt&) const;
	bool operator!=(const int&) const;
	friend bool operator!=(const int&, const BigInt&);
	BigInt operator<<(const BigInt&);
	BigInt operator>>(const BigInt&);
	friend istream& operator>>(istream&, BigInt&);
	friend ostream& operator<<(ostream&, const BigInt&);
private:
	vector<unsigned short> abs_value;
	char sign;
	friend BigInt multiply(BigInt &, BigInt &);	// a supplementary function for operator*
	friend string print(const BigInt&);	//convert BigInt into string
	friend void simplify(BigInt&);//delete the invalid 0s at the beginning of the vector
};

#endif /* BIGINT_H_ */
