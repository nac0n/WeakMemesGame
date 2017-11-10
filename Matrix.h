#pragma once
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
	Matrix(const int x, const int y) : a(new int[x*y]), width(x), height(y) {};
	Matrix() : a(new int[0]), width(0), height(0) {};
	Matrix(const Matrix& other);
	Matrix(Matrix&& other) noexcept;
	~Matrix() noexcept;
	Matrix& operator=(const Matrix &);
	Matrix& operator=(Matrix&&) noexcept;
	void fillWith(const int);
	int& at(int, int);
	int sizeX() const;
	int sizeY() const;
	void set(int x, int y, int num) { a[x + width*y] = num; }
	Matrix getArea(int, int, int, int) noexcept;
	void transpose();
private:
	int* a{ nullptr };
	int width{ 0 };
	int height{ 0 };
};

#endif