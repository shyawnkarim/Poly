//
// Created by Shyawn Karim on 10/6/15.
//

#ifndef POLY_POLY_H
#define POLY_POLY_H


class Poly
{
    friend istream& operator>>(istream &inStream, Poly &);
    friend ostream& operator<<(ostream &outStream, const Poly &);

public:
    Poly();
    Poly(int coeff);
    Poly(int coeff, int power);
    Poly(const Poly &source);
    ~Poly();

    int getCoeff() const;
    void setCoeff(int coeff, int power) const;

    Poly operator+(const Poly &rhs) const;
    Poly operator-(const Poly &rhs) const;
    Poly operator*(const Poly &rhs) const;

    Poly operator+=(const Poly &rhs);
    Poly operator-=(const Poly &rhs);
    Poly operator*=(const Poly &rhs);

    bool operator==(const Poly &rhs) const;
    bool operator!=(const Poly &rhs) const;
    void operator=(const Poly &rhs);

private:
    int* coeffPtr;
};


#endif //POLY_POLY_H
