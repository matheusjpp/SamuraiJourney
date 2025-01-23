#pragma once
#include <iostream>
#include "stdlib.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <list>
#include <stack>
#include <sstream>

using namespace std;

namespace Math {
	template <typename TL>
	class Coord {
	public:
		TL x;
		TL y;
	public:
		Coord(TL x = 0, TL y = 0);
		~Coord() {}
		void operator=(Coord<TL> other);
		void operator+=(Coord<TL> other);
		void operator-=(Coord<TL> other);
		void operator*=(float scalar);
		void operator/=(float scalar);

		Coord<TL> operator+(Coord<TL> other);
		Coord<TL> operator-(Coord<TL> other);
		Coord<TL> operator*(Coord<TL> other);
		Coord<TL> operator*(float scalar);
		Coord<TL> operator/(Coord<TL> other);
		Coord<TL> operator/(float scalar);

	};

	typedef Coord<int> CoordI;
	typedef Coord<float> CoordF;
	typedef Coord<double> CoordD;
	typedef Coord<unsigned int> CoordUI;

	template <typename TL>
	Coord<TL>::Coord(TL x, TL y) {
		this->x = x;
		this->y = y;
	}

	// Operadores
	template <typename TL>
	void Coord<TL>::operator=(Coord<TL> other) {
		x = other.x;
		y = other.y;
	}

	template <typename TL>
	void Coord<TL>::operator+=(Coord<TL> other) {
		x += other.x;
		y += other.y;
	}

	template <typename TL>
	void Coord<TL>::operator-=(Coord<TL> other) {
		x -= other.x;
		y -= other.y;
	}

	template <typename TL>
	void Coord<TL>::operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
	}

	template <typename TL>
	void Coord<TL>::operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
	}

	template <typename TL>
	Coord<TL> Coord<TL>::operator+(Coord<TL> other) {
		Coord<TL> t;
		t.x = x + other.x;
		t.y = y + other.y;

		return t;
	}

	template <typename TL>
	Coord<TL> Coord<TL>::operator-(Coord<TL> other) {
		Coord<TL> t;
		t.x = x - other.x;
		t.y = y - other.y;

		return t;
	}

	template <typename TL>
	Coord<TL> Coord<TL>::operator*(Coord<TL> other) {
		Coord<TL> t;
		t.x = x * other.x;
		t.y = y * other.y;

		return t;
	}

	template <typename TL>
	Coord<TL> Coord<TL>::operator*(float other) {
		Coord<TL> t;
		t.x = x * other;
		t.y = y * other;

		return t;
	}

	template <typename TL>
	Coord<TL> Coord<TL>::operator/(Coord<TL> other) {
		Coord<TL> t;
		t.x = x / other.x;
		t.y = y / other.y;

		return t;
	}

	template <typename TL>
	Coord<TL> Coord<TL>::operator/(float other) {
		Coord<TL> t;
		t.x = x / other;
		t.y = y / other;

		return t;
	}
};