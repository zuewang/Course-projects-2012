/*
 * main.cpp
 * This is only a demo of BigInt test program. The one which grades your homework will be more complete and more strict.
 */

#include "bigint.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;
char str[1024];
bool test_addition() {
	// 2000+3000
	BigInt bi1("2000");
	BigInt bi2("3000");
	BigInt result = bi1 + bi2;
	result.to_string(str);
	cout << str[0] << endl;
	return strcmp(str, "5000") == 0;
}

bool test_subtraction() {
	// 2000-3000
	BigInt bi1("2000");
	BigInt bi2("3000");
	BigInt result = bi1 - bi2;
	result.to_string(str);
	return strcmp(str, "-1000") == 0;
}

bool test_multiplication() {
	// 500*600
	BigInt bi1("500");
	BigInt bi2("600");
	BigInt result = bi1 * bi2;
	result.to_string(str);
	return strcmp(str, "300000") == 0;
}

bool test_division() {
	// 1200/60
	BigInt bi1("1200");
	BigInt bi2("60");
	BigInt result = bi1 / bi2;
	result.to_string(str);
	cout << str[0] << " " << str[1] << " " << str[2] << endl;
	cout << print(result) << endl;
	return strcmp(str, "20") == 0;
}

bool test_mod() {
	// 1200/45
	BigInt bi1("1200");
	BigInt bi2("45");
	BigInt result = bi1 % bi2;
	result.to_string(str);
	cout << print(result) << endl;
	return strcmp(str, "30") == 0;
}

bool test_assignment() {
	// bi2=-12345
	BigInt bi1("-12345");
	BigInt bi2;
	bi2 = bi1;
	bi2.to_string(str);
	return strcmp(str, "-12345") == 0;
}

bool test_incdec() {
	// bi++
	BigInt bi("12345");
	bi++;
	bi.to_string(str);
	cout << str[0] << str[1] << str[2] << str[3] << str[4] << endl;
	return strcmp(str, "12346") == 0;
}

bool test_comparison() {
	// 12345<54321
	BigInt bi1("12345");
	BigInt bi2("54321");
	return bi1 < bi2;
}

bool test_shift() {
	// 1000<<2
	BigInt bi("1000");
	BigInt result = bi << 2;
	result.to_string(str);
	return strcmp(str, "4000") == 0;
}

bool test_iostream() {
	// output
	stringstream ss;
	BigInt bi("1000");
	ss << bi;
	return strcmp(ss.str().c_str(), "1000") == 0;
}

int main() {
	cout << "addition: " << test_addition() << endl;
	cout << "subtraction: " << test_subtraction() << endl;
	cout << "multiplication: " << test_multiplication() << endl;
	cout << "division: " << test_division() << endl;
	cout << "mod: " << test_mod() << endl;
	cout << "assigment: " << test_assignment() << endl;
	cout << "incdec: " << test_incdec() << endl;
	cout << "comparison: " << test_comparison() << endl;
	cout << "iostream: " << test_iostream() << endl;
	cout << "shift: " << test_shift() << endl;

	srand(time(0));
/*
	for (int i = -1001; i < 1001; i++) {
		for (int j = -11; j < 11; j++) {
			BigInt a1(i), a2(j);
			cout << "a1 = " << a1 << " a2= " << a2 << endl;
			cout << (a1 + a2) << " ";
			cout << (a1 - a2) << " ";
			cout << (a1 * a2) << " ";
			//cout << (a1 / a2) << " ";
			//cout << (a1 % a2) << " ";
			cout << a1 << " ";
			cout << (a1 << a2) << " ";
			cout << a2 << " ";
			cout << (a2 >> a2) << endl;
		}
	}
*/
	BigInt a(67), b(67);
	//int b;
	//b = pow(2,9) + pow(2,8) + pow(2,7) + pow(2,5) + pow(2,4)+pow(2,3)+pow(2,1) + pow(2,0);
	//cout<<pow(2,9)<<endl;
	//cout<<b<<endl;
	for (int i=0; i<71; i++){
		a = a * b;
		a = a % 73;
	}
	cout<<a<<endl;
	/*
	int a=2;
	cout<<(a1>>a2)<<endl;
	BigInt b1("-3128902;00000321000"), b2("-00021");
	cout << (b1 + b2) << endl;
	cout << (b1 - b2) << endl;
	cout << (b1 * b2) << endl;
	cout << (b1 / b2) << endl;
	cout << (b1 % b2) << endl;
	cout << b1 << " " << b2 << endl;
	cout<<(b1>>b2)<<endl;
	cout<<(b1<<b2)<<endl;
	a1 = a2++;
	cout<<a1<<" ";cout<<a2;
	a1 = ++++a2;
	cout<<a1<<" "<<a2<<endl;
	cout << "input a number: ";
	cin >> b1;
	cout << endl << b1 << endl;
	*/
	return 0;

}
