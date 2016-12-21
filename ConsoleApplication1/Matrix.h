#pragma once
#include <iostream>
#include <string>

template <typename T = int>
class Matrix
{
	friend Matrix<T>;
private:
	int row = 0, column = 0;
	T** data = nullptr;
public:
	enum ErrorType { sizeError, nullptrException, wrongIndex };

	Matrix(const int row = 2, const int column = 2, const T value = 0)
	{
		this->assign(row, column, value);
	}
	Matrix(const Matrix& rhs) : Matrix(rhs.row, rhs.column)
	{
		*this = rhs;
	}
	~Matrix()
	{
		this->release();
	}

	Matrix& operator=(const Matrix& rhs)
	{
		if (rhs.nullCheck())
			throw nullptrException;
		this->release();
		this->assign(rhs.row, rhs.column);

		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				this->data[i][j] = rhs.data[i][j];
		return *this;
	}
	Matrix operator+(const Matrix& rhs) const
	{
		if (this->nullCheck() || rhs.nullCheck())
			throw nullptrException;
		if (this->row != rhs.row || this->column != rhs.column)
			throw sizeError;

		Matrix tmp(*this);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				tmp.data[i][j] += rhs.data[i][j];
		return tmp;
	}
	Matrix operator-(const Matrix& rhs) const
	{
		if (this->nullCheck() || rhs.nullCheck())
			throw nullptrException;
		if (this->row != rhs.row || this->column != rhs.column)
			throw sizeError;

		Matrix tmp(*this);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				tmp.data[i][j] -= rhs.data[i][j];
		return tmp;
	}
	Matrix operator*(const Matrix& rhs) const
	{
		if (this->nullCheck() || rhs.nullCheck())
			throw nullptrException;
		if (this->column != rhs.row)
			throw sizeError;

		Matrix tmp(this->row, rhs.column);
		for (int i = 0; i < tmp.row; i++)
			for (int j = 0; j < tmp.column; j++)
				for (int k = 0; k < rhs.row; k++)
					tmp.data[i][j] += this->data[i][k] * rhs.data[k][j];
		return tmp;
	}
	Matrix& operator+=(const Matrix& rhs)
	{
		return *this = *this + rhs;
	}
	Matrix& operator-=(const Matrix& rhs)
	{
		return *this = *this - rhs;
	}
	Matrix& operator*=(const Matrix& rhs)
	{
		return *this = *this * rhs;
	}
	bool operator==(const Matrix& rhs)
	{
		if (this->nullCheck() || rhs.nullCheck())
			throw nullptrException;

		if (this->row != rhs.row || this->column != rhs.column)
			return false;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				if (this->data[i][j] != rhs.data[i][j])
					return false;
		return true;
	}
	bool operator!=(const Matrix& rhs)
	{
		if (*this == rhs)
			return false;
		else return true;
	}

	Matrix& print()
	{
		if (this->nullCheck())
			throw nullptrException;

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
				std::cout << this->data[i][j] << ' ';
			std::cout << std::endl;
		}

		return *this;
	}
	bool nullCheck() const
	{
		if (this->data == nullptr && this->row == 0 && this->column == 0)
			return true;
		else return false;
	}
	Matrix& assign(const int row = 2, const int column = 2, const T value = 0)
	{
		if (row < 1 || column < 1)
			throw sizeError;

		release();

		this->row = row;
		this->column = column;

		data = new T*[row];
		for (int i = 0; i < row; i++)
			data[i] = new T[column];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				data[i][j] = value;

		return *this;
	}
	Matrix& release()
	{
		if (this->nullCheck())
			return *this;

		for (int i = 0; i < row; i++)
			delete[] this->data[i];
		delete[] this->data;
		this->data = nullptr;
		row = column = 0;

		return *this;
	}
	const int getRow() const
	{
		return this->row;
	}
	const int getColumn() const
	{
		return this->column;
	}
	T& at(int row, int column)
	{
		if (this->nullCheck())
			throw nullptrException;
		if (row < 0 || column < 0 || row >= this->row || column >= this->column)
			throw wrongIndex;

		return this->data[row][column];
	}
};