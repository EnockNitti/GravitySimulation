#pragma once
#include <iostream>

struct Vector
{
	double x;
	double y;

	Vector();
	Vector(double x, double y);

	Vector& Add(const Vector& vec);
	Vector& Substract(const Vector& vec);
	Vector& Multiply(const Vector& vec);
	Vector& Divide(const Vector& vec);
	Vector& Rotate(const double& Alpha);
	Vector& Extend(const double& dlen);

	friend Vector operator+(const Vector& vec1, const Vector& vec2);
	friend Vector operator-(const Vector& vec1, const Vector& vec2);
	friend Vector operator*(const Vector& vec1, const Vector& vec2);
	friend Vector operator/(const Vector& vec1, const Vector& vec2);

	Vector& operator+=(const Vector vec);
	Vector& operator-=(const Vector vec);
	Vector& operator*=(const Vector vec);
	Vector& operator/=(const Vector vec);

	Vector operator*(const double& i);
	Vector operator/(const double& i);
	Vector& Zero();

	double Lenght();

	friend std::ostream& operator<<(std::ostream& stream, const Vector vec);
};