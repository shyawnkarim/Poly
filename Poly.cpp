// --------------------- Poly.cpp -----------------------------------------
//
// Shyawn Karim, CSS 343
// Created:         October 6, 2015
// Last Modified:   October 10, 2015
// --------------------------------------------------------------
// Purpose:
// --------------------------------------------------------------
// Notes:
// --------------------------------------------------------------

#include "Poly.h"

using namespace std;


//// --------------------- operator>> -----------------------------------------
////
//// --------------------------------------------------------------
istream &operator>>(istream &inStream, Poly &poly)
{
    int coeff;
    int power;

    while (true)
    {
        inStream >> coeff >> power;

        if ((coeff == -1) && (power == -1))
        {
            break;
        }

        poly.setCoeff(coeff, power);
    }

    return inStream;
}

// --------------------- operator<< -----------------------------------------
//
// --------------------------------------------------------------
ostream &operator<<(ostream &outStream, const Poly &poly)
{
    bool allZeroes = true;

        for (int i = poly.size - 1; i >= 0; i--)
        {
            if (poly.coeffPtr[i] != 0)
            {
                allZeroes = false;

                outStream << " ";

                if (poly.coeffPtr[i] > 0)
                {
                    outStream << "+";
                }

                outStream << poly.coeffPtr[i];

                if (i != 0 && i != 1)
                {
                    outStream << "x^" << i;
                }

                if (i == 1)
                {
                    outStream << "x";
                }
            }
        }

    if (allZeroes == false)
    {
        return outStream;
    }
    else
    {
        return outStream << "0";
    }
}

// --------------------- Default Constructor -----------------------------------------
// Takes no parameters, creates Poly object with size 1 and value set to 0
// --------------------------------------------------------------
Poly::Poly()
{
    size = 1;
    coeffPtr = new int[size];
    coeffPtr[0] = 0;
}

// --------------------- Constructor int -----------------------------------------
// Overloaded constructor takes one parameter. Creates a Poly object with
// array size 1 and sets that value to the coefficent parameter
// --------------------------------------------------------------
Poly::Poly(int c)
{
    size = 1;
    coeffPtr = new int[size];
    coeffPtr[0] = c;
}

// --------------------- Constructor int int -----------------------------------------
// Overloaded constructor takes two parameters. Creates a Poly object with
// array size set to power + 1 and the coefficient value in the last index
// --------------------------------------------------------------
Poly::Poly(int c, int p)
{
    size = p + 1;
    coeffPtr = new int[size];

    for (int i = 0; i < size ; i++)
    {
        coeffPtr[i] = 0;
    }

    coeffPtr[p] = c;
}

// --------------------- Copy Constructor -----------------------------------------
// Creates a deep copy of the source Poly object passed in
// --------------------------------------------------------------
Poly::Poly(const Poly &source)
{
    size = source.size;
    coeffPtr = new int[size];

    for (int i = 0; i < size; i++)
    {
        coeffPtr[i] = source.coeffPtr[i];
    }
}

// --------------------- Destructor -----------------------------------------
// Deletes coeffPtr and sets it NULL
// --------------------------------------------------------------
Poly::~Poly()
{
    delete[] coeffPtr;
    coeffPtr = NULL;
}

// --------------------- getCoeff -----------------------------------------
// Returns the coefficient at chosen index (power)
// Returns 0 if index is out of range
// --------------------------------------------------------------
int Poly::getCoeff(int p) const
{
    if ((p >= 0) && (p < size))
    {
        return coeffPtr[p];
    }
    else
    {
        return 0;
    }
}

// --------------------- setCoeff -----------------------------------------
// Adds an additional coefficient to an already established poly array
// If new coefficient has a power greater than largest array index a new
// array is dynamically allocated and all coefficients are transferred
// to the new array
// --------------------------------------------------------------
void Poly::setCoeff(int c, int p)
{
    if (p >= 0)
    {
        if (p < size)
        {
            coeffPtr[p] = c;
        }
        else
        {
            int *tempArr = new int[p + 1];

            for (int i = 0; i < size; i++)
            {
                tempArr[i] = coeffPtr[i];
            }

            for (int j = size; j < p + 1; j++)
            {
                tempArr[j] = 0;
            }

            tempArr[p] = c;

            delete[] coeffPtr;
            coeffPtr = NULL;
            coeffPtr = tempArr;
            tempArr = NULL;
            size = p + 1;
        }
    }
}

// --------------------- operator+ -----------------------------------------
// DONE
// --------------------------------------------------------------
Poly Poly::operator+(const Poly &rhs) const
{
    if (this->size > rhs.size)
    {
        Poly polyDif(0, this->size);

        for (int i = 0; i < this->size; i++)
        {
            polyDif.coeffPtr[i] = this->coeffPtr[i];
        }

        for (int i = 0; i < rhs.size; i++)
        {
            polyDif.coeffPtr[i] += rhs.coeffPtr[i];
        }

        return polyDif;
    }
    else
    {
        Poly polyDif(0, rhs.size);

        for (int i = 0; i < rhs.size; i++)
        {
            polyDif.coeffPtr[i] = rhs.coeffPtr[i];
        }

        for (int i = 0; i < this->size; i++)
        {
            polyDif.coeffPtr[i] += this->coeffPtr[i];
        }

        return polyDif;
    }
}

// --------------------- operator- ----------------------------------------
// DONE
// --------------------------------------------------------------
Poly Poly::operator-(const Poly &rhs) const
{
    if (this->size > rhs.size)
    {
        Poly polyDif(0, this->size);

        for (int i = 0; i < this->size; i++)
        {
            polyDif.coeffPtr[i] = this->coeffPtr[i];
        }

        for (int i = 0; i < rhs.size; i++)
        {
            polyDif.coeffPtr[i] -= rhs.coeffPtr[i];
        }

        return polyDif;
    }
    else
    {
        Poly polyDif(0, rhs.size);

        for (int i = 0; i < this->size; i++)
        {
            polyDif.coeffPtr[i] = this->coeffPtr[i];
        }

        for (int i = 0; i < rhs.size; i++)
        {
            polyDif.coeffPtr[i] -= rhs.coeffPtr[i];
        }

        return polyDif;
    }
}

// --------------------- operator* -----------------------------------------
// WORKING
// --------------------------------------------------------------
Poly Poly::operator*(const Poly &rhs) const
{
    int tempSize;
    tempSize = (this->size + rhs.size - 2);

    Poly tempArr(0, tempSize);

        for (int i = 0; i < this->size; i++)
        {
            if (this->coeffPtr[i] != 0)
            {
                for (int j = 0; j < rhs.size; j++)
                {
                    tempArr.coeffPtr[i + j] += (this->coeffPtr[i] * rhs.coeffPtr[j]);
                }
            }
        }

    return tempArr;
}

// --------------------- operator+= -----------------------------------------
//
// --------------------------------------------------------------
Poly& Poly::operator+=(const Poly &rhs)
{
    *this = *this + rhs;
    return *this;
}

// --------------------- operator-= -----------------------------------------
//
// --------------------------------------------------------------
Poly& Poly::operator-=(const Poly &rhs)
{
    *this = *this - rhs;
    return *this;
}

// --------------------- operator*= -----------------------------------------
//
// --------------------------------------------------------------
Poly& Poly::operator*=(const Poly &rhs)
{
    *this = *this * rhs;
    return *this;
}

// --------------------- operator== -----------------------------------------
//
// --------------------------------------------------------------
bool Poly::operator==(const Poly &rhs) const
{
    if (size == rhs.size)
    {
        for (int i = 0; i < size; i++)
        {
            if (coeffPtr[i] != rhs.coeffPtr[i])
            {
                return false;
            }
        }

        return true;
    }
    else
    {
        int bigArr;
        int smallArr;

        if (size < rhs.size)
        {
            smallArr = size;
            bigArr = rhs.size;

            for (int i = 0; i < smallArr; i++)
            {
                if (coeffPtr[i] != rhs.coeffPtr[i])
                {
                    return false;
                }
            }

            for (int j = smallArr; j < bigArr; j++)
            {
                if (rhs.coeffPtr != 0)
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            bigArr = size;
            smallArr = rhs.size;

            for (int i = 0; i < smallArr; i++)
            {
                if (coeffPtr[i] != rhs.coeffPtr[i])
                {
                    return false;
                }
            }

            for (int j = smallArr; j < bigArr; j++)
            {
                if (coeffPtr != 0)
                {
                    return false;
                }
            }

            return true;
        }
    }
}

// --------------------- operator!= -----------------------------------------
//
// --------------------------------------------------------------
bool Poly::operator!=(const Poly &rhs) const
{
    return !(*this == rhs);
}

// --------------------- operator= -----------------------------------------
// assigns rhs to lhs
// --------------------------------------------------------------
Poly& Poly::operator=(const Poly &rhs)
{
    if (this->coeffPtr == rhs.coeffPtr)
    {
        return *this;
    }

    if (this->size < rhs.size)
    {
        delete[] this->coeffPtr;
        coeffPtr = NULL;
        this->size = rhs.size;
        this->coeffPtr = new int[this->size];

        for (int i = 0; i < this->size; i++)
        {
            this->coeffPtr[i] = rhs.coeffPtr[i];
        }
    }

    if (this->size > rhs.size)
    {
        for (int i = 0; i < this->size; i++)
        {
            this->coeffPtr[i] = 0;
        }

        for (int j = 0; j < rhs.size; j++)
        {
            this->coeffPtr[j] = rhs.coeffPtr[j];
        }
    }

    if (this->size == rhs.size)
    {
        for (int k = 0; k < this->size; k++)
        {
            this->coeffPtr[k] = rhs.coeffPtr[k];
        }
    }

    return *this;
}