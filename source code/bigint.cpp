/*
 * bigInt.cpp
 *
 *  Created on: 2015Äê10ÔÂ19ÈÕ
 *      Author: ThinkPad
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "bigint.h"
using namespace std;
// to delete invalid 0s at the beginning
void simplify(BigInt&op) {
	while (op.abs_value[0] == 0 && op.abs_value.size() > 1) {
		op.abs_value.erase(op.abs_value.begin());
	}
	if (op.abs_value.size() == 1 && op.abs_value[0] == 0) {
		op.sign = '+';
	}
}
BigInt::BigInt() {
	abs_value.push_back(0);
	sign = '+';
}
BigInt::~BigInt() {
	abs_value.clear();
}
//push_back the bits from head(most significant bits) to tail(least significant bits)
BigInt::BigInt(const char *str) {
	BigInt temp;
	// the from_string function will store the string into the temp if
	// the string is valid
	if(temp.from_string(str)){
		abs_value = temp.abs_value;
		sign = temp.sign;
	}else{
		abs_value.push_back(0);
		sign = '+';
		cout<<"The string is not valid!"<<endl;
	}
}
BigInt::BigInt(int integer) {
	abs_value.erase(abs_value.begin(), abs_value.end());
	//sign
	if (integer < 0) {
		sign = '-';
		integer = -integer;
	} else {
		sign = '+';
	}
	if (integer == 0) {
		abs_value.push_back(0);
	}
	//abs_value
	while (integer / 100 != 0) {
		abs_value.insert(abs_value.begin(), integer % 100);
		integer /= 100;
	}
	if (integer) {
		abs_value.insert(abs_value.begin(), integer);
	}

}
BigInt::BigInt(const BigInt &bi) {
	abs_value = bi.abs_value;
	sign = bi.sign;
}
//convert the BigInt into string
string print(const BigInt&op) {
	string str;
	if (op.sign == '-') {
		str.push_back('-');
	}
	for (unsigned int i = 0; i < op.abs_value.size(); i++) {
		ostringstream stream;
		stream << op.abs_value.at(i);
		// 0 should be added if the one element in the vector < 10 and
		// is not the most significant digits (e.g. 1->01)
		if (i != 0 && op.abs_value.at(i) < 10) {
			str += "0";
		}
		//append the string
		str += stream.str();
	}
	return str;
}

bool BigInt::from_string(const char* str) {
	if (str[0] != '0' && str[0] != '1' && str[0] != '2' && str[0] != '3'
			&& str[0] != '4' && str[0] != '5' && str[0] != '6' && str[0] != '7'
			&& str[0] != '8' && str[0] != '9' && str[0] != '+'
			&& str[0] != '-') {
		return false;
	}
	//copy str into a string
	string temp(str);
	for (unsigned int i = 1; i < temp.length(); i++) {
		// if there is non-numeric after the first digit, return false
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3'
				&& str[i] != '4' && str[i] != '5' && str[i] != '6'
				&& str[i] != '7' && str[i] != '8' && str[i] != '9') {
			return false;
		}
	}
	//convert the string into BigInt object
	int j = 0, size = 0;
	//string str_int;
	abs_value.erase(abs_value.begin(), abs_value.end());
	//find the size of the str
	while (str[size] != '\0') {
		size++;
	}
	//sign
	if (str[0] == '+' || str[0] == '-') {
		sign = str[0];
		j++;
	} else {
		sign = '+';
	}
	//abs_value
	if (size == 0) {
		abs_value.push_back(0);
	}
	// from the least significant digits to the most ones
	for (int i = size - 1; i >= j; i--) {
		//convert the i-th and i-1th char into unsigned short
		unsigned short unit_digit = 0, tens_digit = 0;
		//check the i-th digit
		if (str[i] != '+' && str[i] != '-') {
			unit_digit = str[i] - '0';
		} else {
			break;
		}
		//check the (i-1)-th digit
		if (i > j) {
			i--;
			// stop at the sign
			if (str[i] != '+' && str[i] != '-') {
				tens_digit = str[i] - '0';
			} else {
				abs_value.insert(abs_value.begin(), unit_digit);
				break;
			}
		}
		abs_value.insert(abs_value.begin(), unit_digit + tens_digit * 10);
	}
	//delete the invalid 0 at the beginning of the vector
	simplify(*this);
	return true;
}

void BigInt::to_string(char *str) {
	// initialize str
	for (int i = 0; i < 1024; i++) {
		str[i] = 0;
	}
	string temp;
	if (sign == '-') {
		temp.push_back('-');
	}
	for (unsigned int i = 0; i < abs_value.size(); i++) {
		ostringstream stream;
		//copy the vector values into the stream
		stream << abs_value.at(i);
		// 0 should be added if the one element in the vector < 10 and
		// is not the most significant digits
		if (i != 0 && abs_value.at(i) < 10) {
			temp += "0";
		}
		temp += stream.str();
	}
	for (unsigned int i = 0; i < temp.length(); i++) {
		str[i] = temp[i];
	}
}
// operator+
BigInt BigInt::operator+(const BigInt &bi) const {
	//start from least significant bits
	//complement the positive+positive part
	if (sign == '+' && bi.sign == '+') {
		if (*this == 0 && bi == 0) {
			BigInt sum_bi(0);
			return sum_bi;
		}
		int i = abs_value.size() - 1, j = bi.abs_value.size() - 1;
		int sum = 0, carry = 0;
		BigInt sum_bi;
		sum_bi.abs_value.erase(sum_bi.abs_value.begin(),
				sum_bi.abs_value.end());
		sum_bi.sign = '+';
		// do addition and take carries to more significant elements to sum up
		while (i >= 0 && j >= 0) {
			sum = abs_value[i] + bi.abs_value[j] + carry;
			sum_bi.abs_value.insert(sum_bi.abs_value.begin(), sum % 100);
			carry = sum / 100;
			i--;
			j--;
		}
		while (i >= 0) {
			sum = abs_value[i] + carry;
			sum_bi.abs_value.insert(sum_bi.abs_value.begin(), sum % 100);
			carry = sum / 100;
			i--;
		}
		while (j >= 0) {
			sum = bi.abs_value[j] + carry;
			sum_bi.abs_value.insert(sum_bi.abs_value.begin(), sum % 100);
			carry = sum / 100;
			j--;
		}
		// continue until the carry is 0
		if (carry != 0) {
			sum_bi.abs_value.insert(sum_bi.abs_value.begin(), carry);
		}
		return sum_bi;
	}
	// for the following cases, do the transformation
	if (sign == '+' && bi.sign == '-') {
		BigInt temp(bi);
		temp.sign = '+';
		BigInt sum(*this - temp);
		return sum;
	}
	if (sign == '-' && bi.sign == '+') {
		BigInt temp(*this);
		temp.sign = '+';
		BigInt sum(bi - temp);
		return sum;
	}
	if (sign == '-' && bi.sign == '-') {
		BigInt temp1(*this), temp2(bi);
		temp1.sign = '+';
		temp2.sign = '+';
		BigInt sum(temp1 + temp2);
		sum.sign = '-';
		return sum;
	}
}
BigInt BigInt::operator+(const int& adden) const {
	BigInt temp(adden);
	return (*this + temp);
}
BigInt operator+(const int &adden, const BigInt&op) {
	BigInt temp(adden);
	return (temp + op);
}
// operator-
BigInt BigInt::operator-(const BigInt &bi) const {
	//complement the positive-positive part
	if (sign == '+' && bi.sign == '+') {
		//if the result > 0
		if (*this > bi) {
			int i = abs_value.size() - 1, j = bi.abs_value.size() - 1;
			int differ = 0, carry = 0;
			BigInt minus_bi;
			minus_bi.abs_value.erase(minus_bi.abs_value.begin(),
					minus_bi.abs_value.end());
			// do subtraction and borrow 'carry' from the more significant element
			while (i >= 0 && j >= 0) {
				differ = abs_value[i] - bi.abs_value[j] + carry;
				int k = 0;
				while (differ < 0) {
					k--;
					differ += 100;
				}
				minus_bi.abs_value.insert(minus_bi.abs_value.begin(), differ);
				carry = k;
				i--;
				j--;
			}
			while (i >= 0) {
				differ = abs_value[i] + carry;
				int k = 0;
				while (differ < 0) {
					k--;
					differ += 100;
				}
				minus_bi.abs_value.insert(minus_bi.abs_value.begin(), differ);
				carry = k;
				i--;
			}
			//delete the invalid 0s at the beginning of the vector
			simplify(minus_bi);
			return minus_bi;
		}
		// if the result == 0
		else if (*this == bi) {
			BigInt minus_bi(0);
			return minus_bi;
		}
		// if the result < 0
		else {
			BigInt minus(bi - *this);
			minus.sign = '-';
			return minus;
		}
	}
	if (sign == '+' && bi.sign == '-') {
		BigInt temp(bi);
		temp.sign = '+';
		BigInt minus(*this + temp);
		return minus;
	}
	if (sign == '-' && bi.sign == '+') {
		BigInt temp1(*this), temp2(bi);
		temp1.sign = '+';
		BigInt minus(temp1 + temp2);
		minus.sign = '-';
		return minus;
	}
	if (sign == '-' && bi.sign == '-') {
		BigInt temp1(*this), temp2(bi);
		temp1.sign = '+';
		temp2.sign = '+';
		BigInt minus(temp2 - temp1);
		return minus;
	}
}
BigInt BigInt::operator-(const int& subtra) const {
	BigInt temp(subtra);
	return (*this - temp);
}
BigInt operator-(const int &minuend, const BigInt&op) {
	BigInt temp(minuend);
	return (temp - op);
}
// operator*
//more details of this algorithm in README file
BigInt multiply(BigInt &a, BigInt &b) {
	unsigned int n = a.abs_value.size();
	if (n < b.abs_value.size()) {
		n = b.abs_value.size();
		int differ = n - a.abs_value.size();
		for (int i = 0; i < differ; i++) {
			a.abs_value.insert(a.abs_value.begin(), 0);
		}
	} else {
		int differ = n - b.abs_value.size();
		for (int i = 0; i < differ; i++) {
			b.abs_value.insert(b.abs_value.begin(), 0);
		}
	}
	if (n == 1) {
		BigInt mul_int(a.abs_value[0] * b.abs_value[0]);
		return mul_int;
	}
	int middle = n / 2;
	// the left halves and right halves of a and b
	BigInt left_a, left_b, right_a, right_b;
	left_a.abs_value.erase(left_a.abs_value.begin(), left_a.abs_value.end());
	left_b.abs_value.erase(left_b.abs_value.begin(), left_b.abs_value.end());
	right_a.abs_value.erase(right_a.abs_value.begin(), right_a.abs_value.end());
	right_b.abs_value.erase(right_b.abs_value.begin(), right_b.abs_value.end());
	for (unsigned int i = 0; i < n - middle; i++) {
		left_a.abs_value.push_back(a.abs_value[i]);
		left_b.abs_value.push_back(b.abs_value[i]);
	}
	if (left_a.abs_value.size() == 0) {
		left_a.abs_value.push_back(0);
	}
	if (left_b.abs_value.size() == 0) {
		left_b.abs_value.push_back(0);
	}
	for (unsigned int i = n - middle; i < n; i++) {
		right_a.abs_value.push_back(a.abs_value[i]);
		right_b.abs_value.push_back(b.abs_value[i]);
	}
	if (right_a.abs_value.size() == 0) {
		right_a.abs_value.push_back(0);
	}
	if (right_b.abs_value.size() == 0) {
		right_b.abs_value.push_back(0);
	}
	BigInt temp_1 = multiply(left_a, left_b);
	BigInt temp_2 = multiply(right_a, right_b);
	BigInt temp_a = right_a + left_a;
	BigInt temp_b = right_b + left_b;
	BigInt temp_3 = multiply(temp_a, temp_b);
	BigInt result = temp_2;
	for (int i = 0; i < middle; i++) {
		temp_1.abs_value.push_back(0);
		temp_2.abs_value.push_back(0);
		temp_3.abs_value.push_back(0);
	}
	simplify(temp_3);
	simplify(temp_1);
	simplify(temp_2);
	result = (result + temp_3 - temp_1 - temp_2);
	for (int i = 0; i < middle; i++) {
		temp_1.abs_value.push_back(0);
	}
	simplify(result);
	simplify(temp_1);
	result = result + temp_1;
	simplify(result);
	return result;
}

BigInt BigInt::operator*(const BigInt&op) const {
	BigInt temp1(*this), temp2(op);
	temp2.sign = '+';
	temp1.sign = '+';
	BigInt mul = multiply(temp1, temp2);
	// the result will be negative if it's not 0 and the signs are different
	if (sign != op.sign && mul != 0) {
		mul.sign = '-';
	}
	return mul;
}
BigInt BigInt::operator*(const int& k) const {
	BigInt temp(k);
	return (*this * temp);
}
BigInt operator*(const int&k, const BigInt&op) {
	BigInt temp(k);
	return (temp * op);
}
// operator/
BigInt BigInt::operator/(const BigInt&op) const {
	BigInt dividend(*this), divisor(op);
	dividend.sign = '+';
	divisor.sign = '+';
	BigInt quotient(0);
	if (divisor == 0) {
		cout << "Invalid division! The divisor is 0!" << endl;
		exit(0);
	}
	// shift the divisor as big as possible while smaller than the dividend
	// and then record the number of shifting(s)
	while (divisor <= dividend) {
		BigInt mul_divisor(divisor), shift(0);
		while (mul_divisor <= dividend) {
			shift++;
			mul_divisor << 1;
		}
		// do >> shifting because the mul_divisor is just right bigger than the dividend
		mul_divisor >> 1;
		shift--;
		// get the remainder
		dividend = dividend - mul_divisor;
		BigInt increment(1);
		BigInt temp(1);
		for (int i = 0; i < shift; i++) {
			temp = temp * 2;
		}
		// sum up the quotients
		quotient = quotient + temp;
	}
	// the quotient will be negative if it's not 0 and the signs are different
	if (sign != op.sign && quotient != 0) {
		quotient.sign = '-';
	}
	return quotient;
}
BigInt BigInt::operator/(const int& k) const {
	BigInt temp(k);
	return (*this / temp);
}
BigInt operator/(const int&k, const BigInt&op) {
	BigInt temp(k);
	return (temp / op);
}
// operator%
BigInt BigInt::operator%(const BigInt&op) const {
	return *this - op * (*this / op);
}
BigInt BigInt::operator%(const int& k) const {
	BigInt temp(k);
	return (*this % temp);
}
BigInt operator%(const int &k, const BigInt &op) {
	BigInt temp(k);
	return (temp % op);
}
// operator=
BigInt &BigInt::operator=(const BigInt &op) {
	sign = op.sign;
	abs_value = op.abs_value;
	return *this;
}
BigInt &BigInt::operator=(const int& assign) {
	BigInt temp(assign);
	sign = temp.sign;
	abs_value = temp.abs_value;
	return *this;
}
// operator++
//post-increment
BigInt BigInt::operator++(int) {
	BigInt increment(1), value(*this);
	*this = (*this + increment);
	return value;
}
//pre-increment
BigInt &BigInt::operator++() {
	BigInt increment(1);
	*this = (*this + increment);
	return *this;
}
// operator--
//post-decrement
BigInt BigInt::operator--(int) {
	BigInt increment(1), value(*this);
	*this = (*this - increment);
	return value;
}
//pre-decrement
BigInt &BigInt::operator--() {
	BigInt increment(1);
	*this = (*this - increment);
	return *this;
}
// operator>
bool BigInt::operator>(const BigInt &bi) const {
	BigInt temp1(*this), temp2(bi);
	simplify(temp1);
	simplify(temp2);
	// compare the signs
	if (temp1.sign == '+' && temp2.sign == '-') {
		return true;
	}	//+ > -
	if (temp1.sign == '+' && temp2.sign == '+') {
		// for same signs, compare the sizes
		if (temp1.abs_value.size() > temp2.abs_value.size()) {
			return true;
		}
		if (temp1.abs_value.size() == temp2.abs_value.size()) {
			// for same sizes, compare each element from most significant elements to least ones
			for (unsigned int i = 0; i < temp1.abs_value.size(); i++) {
				if (temp1.abs_value[i] > temp2.abs_value[i]) {
					return true;
				}
				if (temp1.abs_value[i] < temp2.abs_value[i]) {
					return false;
				}
			}
		}
	}
	if (temp1.sign == '-' && temp2.sign == '-') {
		if (temp1.abs_value.size() < temp2.abs_value.size()) {
			return true;
		}
		if (temp1.abs_value.size() == temp2.abs_value.size()) {
			for (unsigned int i = 0; i < temp1.abs_value.size(); i++) {
				if (temp1.abs_value[i] < temp2.abs_value[i]) {
					return true;
				}
				if (temp1.abs_value[i] > temp2.abs_value[i]) {
					return false;
				}
			}
		}
	}
	return false;
}
bool BigInt::operator>(const int&k) const {
	BigInt temp(k);
	return *this > temp;
}
bool operator>(const int&k, const BigInt&op) {
	BigInt temp(k);
	return temp > op;
}
bool BigInt::operator==(const BigInt &bi) const {
	BigInt temp1(*this), temp2(bi);
	simplify(temp1);
	simplify(temp2);
	// the signs, sizes and every corresponding elements should be the same
	if (temp1.sign == temp2.sign
			&& temp1.abs_value.size() == temp2.abs_value.size()) {
		for (unsigned int i = 0; i < temp1.abs_value.size(); i++) {
			if (temp1.abs_value[i] != temp2.abs_value[i]) {
				return false;
			}
		}
		return true;
	} else {
		return false;
	}
}
bool BigInt::operator==(const int &k) const {
	BigInt temp(k);
	return *this == temp;
}
bool operator==(const int&k, const BigInt&op) {
	BigInt temp(k);
	return temp == op;
}
// transform other comparison cases into a combination of > and ==
// operator<
bool BigInt::operator<(const BigInt &bi) const {
	if (!(*this == bi) && !(*this > bi)) {
		return true;
	} else {
		return false;
	}
}
bool BigInt::operator<(const int&k) const {
	BigInt temp(k);
	return *this < temp;
}
bool operator<(const int&k, const BigInt&op) {
	BigInt temp(k);
	return temp < op;
}
// operator>=
bool BigInt::operator>=(const BigInt &bi) const {
	if (*this == bi || *this > bi) {
		return true;
	} else {
		return false;
	}
}
bool BigInt::operator>=(const int&k) const {
	BigInt temp(k);
	return *this >= temp;
}
bool operator>=(const int&k, const BigInt&op) {
	BigInt temp(k);
	return temp >= op;
}
// operator<=
bool BigInt::operator<=(const BigInt &bi) const {
	if (*this == bi || *this < bi) {
		return true;
	} else {
		return false;
	}
}
bool BigInt::operator<=(const int&k) const {
	BigInt temp(k);
	return *this <= temp;
}
bool operator<=(const int&k, const BigInt&op) {
	BigInt temp(k);
	return temp <= op;
}
// operator!=
bool BigInt::operator!=(const BigInt &bi) const {
	if (*this == bi) {
		return false;
	} else {
		return true;
	}
}
bool BigInt::operator!=(const int&k) const {
	BigInt temp(k);
	return *this != temp;
}
bool operator!=(const int&k, const BigInt&op) {
	BigInt temp(k);
	return temp != op;
}

// operator<<shifting
BigInt BigInt::operator<<(const BigInt &op) {
	if (op >= 0) {
		// multiplied by 2 for op times
		for (int i = 0; i < op; i++) {
			// multiply each element by 2 from the least significant element to the most one
			// and add the carry to the upper element
			int carry = 0, mul = 0;
			for (int j = abs_value.size() - 1; j >= 0; j--) {
				mul = abs_value[j] * 2 + carry;
				abs_value[j] = mul % 100;
				carry = mul / 100;
			}
			while (carry) {
				mul = carry;
				abs_value.insert(abs_value.begin(), mul % 100);
				carry = mul / 100;
			}
			simplify(*this);
		}
		simplify(*this);
		return *this;
	} else {
		BigInt temp(op);
		temp.sign = '+';
		return (*this >> temp);
	}
}
// operator>>shifting
BigInt BigInt::operator>>(const BigInt &op) {
	// divided by 2 for op times
	if (op >= 0) {
		for (int i = 0; i < op; i++) {
			int remain = 0, dividend = 0;
			//divide each element by 2 from the most significant element to the least one
			// and add the remainder to the lower element
			for (unsigned int j = 0; j < abs_value.size(); j++) {
				dividend = abs_value[j] + remain * 100;
				remain = dividend % 2;
				abs_value[j] = dividend / 2;
			}
			simplify(*this);
		}
		simplify(*this);
		return *this;
	} else {
		BigInt temp(op);
		temp.sign = '+';
		return (*this << temp);
	}
}
// operator>>input
istream& operator>>(istream& is, BigInt&op) {
	// copy input into the string temp
	string temp;
	is >> temp;
	// copy the string temp into a char array str
	char *str = new char[temp.length() + 1];// one more space for '\0' at the back
	for (unsigned int i = 0; i <= temp.length(); i++) {
		str[i] = temp[i];
	}
	// assign str to the BigInt
	op = BigInt(str);
	return is;
}
// operator<<output
ostream& operator<<(ostream& os, const BigInt&op) {
	// convert the BigInt into a string and input to ostream
	os << print(op);
	return os;
}
