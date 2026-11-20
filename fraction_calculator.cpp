#include <iostream>
using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;
    static int objectCount;

    static int gcd(int a, int b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b != 0) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

public:
    Fraction() {
        numerator = 0;
        denominator = 1;
        objectCount++;
    }

    Fraction(int n, int d) {
        numerator = n;
        denominator = d;
        if (denominator == 0) {
            cout << "Denominator cannot be zero. Using 1.\n";
            denominator = 1;
        }
        simplify();
        objectCount++;
    }

    void simplify() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        if (numerator == 0) {
            denominator = 1;
            return;
        }
        int g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
    }

    static int getObjectCount() {
        return objectCount;
    }

    Fraction operator+(const Fraction &f) const {
        return Fraction(numerator * f.denominator + f.numerator * denominator, denominator * f.denominator);
    }

    Fraction operator-(const Fraction &f) const {
        return Fraction(numerator * f.denominator - f.numerator * denominator, denominator * f.denominator);
    }

    Fraction operator*(const Fraction &f) const {
        return Fraction(numerator * f.numerator, denominator * f.denominator);
    }

    Fraction operator/(const Fraction &f) const {
        if (f.numerator == 0) {
            cout << "Cannot divide by zero.\n";
            return Fraction(0, 1);
        }
        return Fraction(numerator * f.denominator, denominator * f.numerator);
    }

    bool operator==(const Fraction &f) const {
        return numerator == f.numerator && denominator == f.denominator;
    }

    bool operator<(const Fraction &f) const {
        return numerator * f.denominator < f.numerator * denominator;
    }

    Fraction operator-() const {
        return Fraction(-numerator, denominator);
    }

    Fraction &operator++() {
        numerator += denominator;
        return *this;
    }

    Fraction operator++(int) {
        Fraction temp = *this;
        numerator += denominator;
        return temp;
    }

    friend ostream &operator<<(ostream &out, const Fraction &f) {
        out << f.numerator << "/" << f.denominator;
        return out;
    }

    friend istream &operator>>(istream &in, Fraction &f) {
        int n, d;
        in >> n >> d;
        while (d == 0) {
            cout << "Denominator cannot be zero. Re-enter numerator and denominator: ";
            in >> n >> d;
        }
        f.numerator = n;
        f.denominator = d;
        f.simplify();
        return in;
    }
};

int Fraction::objectCount = 0;

int main() {
    int n;
    cout << "How many fractions? ";
    cin >> n;
    while (n < 1) {
        cout << "Enter at least 1: ";
        cin >> n;
    }

    Fraction *fractions = new Fraction[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter numerator and denominator of fraction " << i + 1 << ": ";
        cin >> fractions[i];
    }

    cout << "\nFractions in simplified form:\n";
    for (int i = 0; i < n; i++) {
        cout << fractions[i] << "\n";
    }

    Fraction sum(0, 1);
    Fraction product(1, 1);
    for (int i = 0; i < n; i++) {
        sum = sum + fractions[i];
        product = product * fractions[i];
    }
    cout << "\nSum     : " << sum << "\n";
    cout << "Product : " << product << "\n";

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (fractions[j + 1] < fractions[j]) {
                Fraction temp = fractions[j];
                fractions[j] = fractions[j + 1];
                fractions[j + 1] = temp;
            }
        }
    }

    cout << "\nSorted in ascending order:\n";
    for (int i = 0; i < n; i++) {
        cout << fractions[i] << "\n";
    }

    cout << "\nSmallest : " << fractions[0] << "\n";
    cout << "Largest  : " << fractions[n - 1] << "\n";

    cout << "\nTotal Fraction objects created: " << Fraction::getObjectCount() << "\n";

    delete[] fractions;
    return 0;
}
