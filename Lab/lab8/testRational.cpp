/*
	rec08.cpp
	CS2124
	Implement the class Rational, so that the following program works.
 */

#include <iostream>


using namespace std;

class Rational{
    friend ostream& operator<<(ostream& os, const Rational& rhs);
    friend istream& operator>>(istream& is, Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);

public:
    Rational() : numerator(0), denominator(1) { }
    Rational(int numerator, int denominator) : numerator(numerator), denominator(denominator){
        if (denominator < 0){
            denominator *= -1;
            numerator *= -1;
        }
        int gcd = greatestCommonDivisor(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }
    Rational(int numerator) : numerator(numerator), denominator(1) { }
    
    int greatestCommonDivisor(int x, int y);
    void simplify(); 

    Rational& operator+=(const Rational& rhs); 
    Rational& operator++();
    Rational operator++(int dummy); 

    explicit operator bool() const; 

private:
    int numerator; 
    int denominator;
};

int Rational::greatestCommonDivisor(int x, int y){
    while (y != 0){
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

void Rational::simplify(){
    int top = numerator;
    int bottom = denominator;
    while (bottom != 0){
        int temp = top % bottom;
        top = bottom;
        bottom = temp;
    } 
    // top is how the gcd
    numerator /= top; 
    denominator /= top; 
}

ostream& operator<<(ostream& os, const Rational& rhs){
    os << rhs.numerator << "/" << rhs.denominator; 
    return os;
}

istream& operator>>(istream& is, Rational& rhs){
    char slash; 
    is >> rhs.numerator >> slash >> rhs.denominator;
    if (rhs.denominator < 0){
        rhs.denominator *= -1;
        rhs.numerator *= -1;
    }
    rhs.simplify();
    return is;
}


Rational& Rational::operator+=(const Rational& rhs){
        int initialDenom = denominator; 
        numerator *= rhs.denominator;
        denominator *= rhs.denominator; 
        numerator += (rhs.numerator * initialDenom);
        simplify(); 
        return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational result; 
    result += rhs; 
    result += lhs; 
    return result;
}

bool operator==(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator);
}

bool operator!=(const Rational& lhs, const Rational rhs){
    return !(lhs==rhs);
}

Rational& Rational::operator++(){
    numerator += denominator; 
    simplify(); 
    return *this;
}

Rational Rational::operator++(int dummy){
    numerator += denominator;
    simplify();
    return *this;
}

Rational& operator--(Rational& rhs){
    rhs += -1;
    return rhs; 
}

Rational& operator--(Rational& rhs, int dummy){
    rhs += -1;
    return rhs; 
}

Rational::operator bool() const{
    return numerator !=0;
}


bool operator<(const Rational& lhs, const Rational& rhs){
    return (((lhs.numerator / lhs.denominator) < (rhs.numerator / rhs.denominator)) && (lhs!=rhs));
}

bool operator<=(const Rational& lhs, const Rational& rhs){
    return ((lhs < rhs) || (rhs == lhs));
}

bool operator>(const Rational& lhs, const Rational& rhs){
    return (!(lhs < rhs) && (lhs != rhs));
}

bool operator>=(const Rational& lhs, const Rational& rhs){
    return ((lhs > rhs) || (lhs == rhs));
}

int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}
