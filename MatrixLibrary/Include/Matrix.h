#pragma once
#ifndef MATRIX_H
#define MATRIX_H
//#pragma once

#include<iostream>
#include<vector>
#include<assert.h>
#include<sstream>

#include "ExceptionHandling.h"

/*
namespace mat {

	class Matrix
	{
	private:
		int x;

	public:
		void setX(int x);
		int getX();
		void PrintMessage();
	};
}
*/

namespace linalg {

	template<typename T> class Matrix;

	template <typename T> Matrix<T> operator+ (const Matrix<T>& mat1, const Matrix<T>& mat2);
	template <typename T> Matrix<T> operator- (const Matrix<T>& mat1, const Matrix<T>& mat2);
	template <typename T> Matrix<T> operator* (const Matrix<T>& mat1, const Matrix<T>& mat2);

	template <typename T> std::ostream& operator<< (std::ostream& os, Matrix<T>& matOut);

	template <typename T>
	class Matrix
	{
	private:
		std::vector< std::vector<T> > mat;
		int rows;
		int cols;

	public:
		Matrix<T>();	// null constructor
		Matrix<T>(int rows, int cols, const T& initial);	//create matrix with initial value
		Matrix<T>(int rows, int cols);	// create matrix with zero values
		Matrix<T>(std::vector<std::vector<T> > const& mat); // copy constructor
		virtual ~Matrix<T>();	// destructor

		int getRow();	// return matrix row size
		int getCol();	// return matrix column size


		// Operator overload: assignment
		Matrix<T>& operator=(const Matrix<T>& rhs);

		// Operator Overload: A matrix with another matrix mathematical operation
		friend Matrix<T> operator+ <> (const Matrix<T>& mat1, const Matrix<T>& mat2);
		Matrix<T>& operator+= (const Matrix<T>& rhs);
		friend Matrix<T> operator- <> (const Matrix<T>& mat1, const Matrix<T>& mat2);
		Matrix<T>& operator-= (const Matrix<T>& rhs);
		friend Matrix<T> operator* <> (const Matrix<T>& mat1, const Matrix<T>& mat2);
		Matrix<T>& operator*= (const Matrix<T>& rhs);

		// Operator Overload: A matrix with a scalar mathematical operation
		Matrix<T> operator+ (const T& rhs);
		Matrix<T>& operator+= (const T& rhs);
		Matrix<T> operator- (const T& rhs);
		Matrix<T>& operator-= (const T& rhs);
		Matrix<T> operator* (const T& rhs);
		Matrix<T>& operator*= (const T& rhs);
		Matrix<T> operator/ (const T& rhs);
		Matrix<T>& operator/= (const T& rhs);

		// Access individual element
		T& operator()(const int row, const int col); // return a particular element

		// Return Matrix
		Matrix<T> elementWiseMultiply(const Matrix<T>& rhs) const;	// return element-wise matrix multiplication
		Matrix<T> transpose() const;	// return matrix transpose
		Matrix<T> applyFun(T(*function)(T)) const;
		Matrix<T> subMatrix(int startR, int startC, int r, int c) const;

		// logical operator overloading for matrix
		bool operator==(const Matrix<T>& rhs);
		bool operator!=(const Matrix<T>& rhs);

		friend std::ostream& operator<< <> (std::ostream& os, Matrix<T>& matOut);
	};

} // end namespace "linalg"

#endif 

namespace linalg {
	// null constructor
	template <typename T>
	Matrix<T>::Matrix() : Matrix(1, 1) {}

	// constructor with initial value
	template <typename T>
	Matrix<T>::Matrix(int rows, int cols, const T& initial)
	{
		this->mat.resize(rows);
		for (int i = 0; i < this->mat.size(); i++)
		{
			this->mat[i].resize(cols, initial);
		}
		this->rows = rows;
		this->cols = cols;
	}

	// constructor with no initial value
	template <typename T>
	Matrix<T>::Matrix(int rows, int cols)
	{
		this->mat.resize(rows);
		for (int i = 0; i < this->mat.size(); i++)
		{
			this->mat[i].resize(cols, 0);
		}
		this->rows = rows;
		this->cols = cols;
	}

	// Copy constructor
	template <typename T>
	Matrix<T>::Matrix(std::vector<std::vector<T> > const& rhs)
	{
		assert(rhs.size() != 0);
		this->rows = rhs.size();
		this->cols = rhs[0].size();
		this->mat = rhs;
	}

	// virtual destructor
	template <typename T>
	Matrix<T>::~Matrix()
	{

	}


	// get the number of rows in this matrix
	template <typename T>
	int Matrix<T>::getRow() { return this->rows; }

	// get the number of columns in this matrix
	template <typename T>
	int Matrix<T>::getCol() { return this->cols; }


	// assignment operator overloading
	template <typename T>
	Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
	{
		if (&rhs == this)
			return *this;

		for (int i = 0; i < rhs.rows; i++)
		{
			for (int j = 0; j < rhs.cols; j++)
			{
				this->mat[i][j] = rhs.mat[i][j];
			}
		}

		this->rows = rhs.rows;
		this->cols = rhs.cols;

		return *this;
	}

	// + operator overloading with another matix
	template <typename T>
	Matrix<T> operator+ (const Matrix<T>& mat1, const Matrix<T>& mat2)
	{
		if (mat1.rows == mat2.rows && mat2.cols == mat2.cols)
		{
			Matrix<T> result(mat1.rows, mat1.cols, 0);
			for (int i = 0; i < mat1.rows; i++)
			{
				for (int j = 0; j < mat1.cols; j++)
				{
					result.mat[i][j] = mat1.mat[i][j] + mat2.mat[i][j];
				}
			}
			return result;
		}
		else
		{
			std::stringstream ss;
			ss << "Matrix addition failed: check dimension of both the matrices";
			throw MatrixException(ss.str());
		}
	}

	// += opertor overloading with another matix
	template <typename T>
	Matrix<T>& Matrix<T>::operator+= (const Matrix<T>& rhs)
	{
		if (this->rows == rhs.rows && this->cols == rhs.cols)
		{
			for (int i = 0; i < rhs.rows; i++)
			{
				for (int j = 0; j < rhs.cols; j++)
				{
					this->mat[i][j] += rhs.mat[i][j];
				}
			}
			return *this;
		}
		else
		{
			std::stringstream ss;
			ss << "Matrix addition failed: check dimension of both the matrices";
			throw MatrixException(ss.str());
		}
	}

	// - operator overloading
	template <typename T>
	Matrix<T> operator- (const Matrix<T>& mat1, const Matrix<T>& mat2)
	{
		if (mat1.rows == mat2.rows && mat2.cols == mat2.cols)
		{
			Matrix<T> result(mat1.rows, mat1.cols, 0);
			for (int i = 0; i < mat1.rows; i++)
			{
				for (int j = 0; j < mat1.cols; j++)
				{
					result.mat[i][j] = mat1.mat[i][j] - mat2.mat[i][j];
				}
			}
			return result;
		}
		else
		{
			std::stringstream ss;
			ss << "Matrix subtraction failed: check dimension of both the matrices";
			throw MatrixException(ss.str());
		}
	}

	// -= operator overloading
	template <typename T>
	Matrix<T>& Matrix<T>::operator-= (const Matrix<T>& rhs)
	{
		if (this->rows == rhs.rows && this->cols == rhs.cols)
		{
			for (int i = 0; i < rhs.rows; i++)
			{
				for (int j = 0; j < rhs.cols; j++)
				{
					this->mat[i][j] -= rhs.mat[i][j];
				}
			}
			return *this;
		}
		else
		{
			std::stringstream ss;
			ss << "Matrix subtraction failed: check dimension of both the matrices";
			throw MatrixException(ss.str());
		}
	}

	// * operator overloading
	template <typename T>
	Matrix<T> operator* (const Matrix<T>& mat1, const Matrix<T>& mat2)
	{
		if (mat1.cols == mat2.rows)
		{
			Matrix<T> result(mat1.rows, mat2.cols, 0);
			for (int i = 0; i < mat1.rows; i++)
			{
				for (int j = 0; j < mat2.cols; j++)
				{
					for (int k = 0; k < mat1.rows; k++)
					{
						result.mat[i][j] += mat1.mat[i][k] * mat2.mat[k][j];
					}
				}
			}
			return result;
		}
		else
		{
			std::stringstream ss;
			ss << "Matrix multiplication failed: column of first matrix should be equal to row of second matrix";
			throw MatrixException(ss.str());
		}
	}

	// *= operator overloading
	template <typename T>
	Matrix<T>& Matrix<T>::operator*= (const Matrix<T>& rhs)
	{
		if (this->cols == rhs.rows)
		{
			Matrix<T> result = (*this) * rhs;
			(*this) = result;

			return *this;
		}
		else
		{
			std::stringstream ss;
			ss << "Matrix multiplication failed: column of first matrix should be equal to row of second matrix";
			throw MatrixException(ss.str());
		}
	}

	// + operator overloading matrix with a scalar
	template <typename T>
	Matrix<T> Matrix<T>::operator+ (const T& rhs)
	{
		Matrix<T> result(this->rows, this->cols, 0);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				result.mat[i][j] = this->mat[i][j] + rhs;
			}
		}
		return result;
	}

	// += operator overloading matrix with a scalar
	template <typename T>
	Matrix<T>& Matrix<T>::operator+= (const T& rhs)
	{
		Matrix<T> result = (*this) + rhs;
		(*this) = result;

		return *this;
	}

	// - operator overloading matrix with a scalar
	template <typename T>
	Matrix<T> Matrix<T>::operator- (const T& rhs)
	{
		Matrix<T> result(this->rows, this->cols, 0);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				result.mat[i][j] = this->mat[i][j] - rhs;
			}
		}
		return result;
	}

	// -= operator overloading matrix with a scalar
	template <typename T>
	Matrix<T>& Matrix<T>::operator-= (const T& rhs)
	{
		Matrix<T> result = (*this) - rhs;
		(*this) = result;

		return *this;
	}

	// * operator overloading matrix with a scalar
	template <typename T>
	Matrix<T> Matrix<T>::operator* (const T& rhs)
	{
		Matrix<T> result(this->rows, this->cols, 0);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				result.mat[i][j] = this->mat[i][j] * rhs;
			}
		}
		return result;
	}

	// *= operator overloading matrix with a scalar
	template <typename T>
	Matrix<T>& Matrix<T>::operator*= (const T& rhs)
	{
		Matrix<T> result = (*this) * rhs;
		(*this) = result;

		return *this;
	}

	// / operator overloading matrix with a scalar
	template <typename T>
	Matrix<T> Matrix<T>::operator/ (const T& rhs)
	{
		if (rhs != 0)
		{
			Matrix<T> result(this->rows, this->cols, 0);
			for (int i = 0; i < this->rows; i++)
			{
				for (int j = 0; j < this->cols; j++)
				{
					result.mat[i][j] = this->mat[i][j] / rhs;
				}
			}
			return result;
		}
		else
		{
			std::stringstream ss;
			ss << "Matrix division by scalar failed: divied by zero";
			throw MatrixException(ss.str());
		}

	}

	// /= operator overloading matrix with a scalar
	template <typename T>
	Matrix<T>& Matrix<T>::operator/= (const T& rhs)
	{
		if (rhs != 0)
		{
			Matrix<T> result = (*this) / rhs;
			(*this) = result;

			return *this;
		}
		else
		{
			std::stringstream ss;
			ss << "Matrix division by scalar failed: divied by zero";
			throw MatrixException(ss.str());
		}

	}


	// return element-wise matrix multiplication
	template <typename T>
	Matrix<T> Matrix<T>::elementWiseMultiply(const Matrix<T>& rhs) const
	{
		if (this->rows == rhs.rows && this->cols == rhs.cols)
		{
			Matrix<T> result(rhs.rows, rhs.cols, 0);

			for (int i = 0; i < rhs.rows; i++)
			{
				for (int j = 0; j < rhs.cols; j++)
				{
					result.mat[i][j] = this->mat[i][j] * rhs.mat[i][j];
				}
			}
			return result;
		}
		else
		{
			std::stringstream ss;
			ss << "Matrix element-wise multiplication failed: check dimensions of both the matrices";
			throw MatrixException(ss.str());
		}

	}

	// return matrix transpose
	template <typename T>
	Matrix<T> Matrix<T>::transpose() const
	{
		Matrix<T> result(this->cols, this->rows, 0);
		for (int i = 0; i < this->cols; i++)
		{
			for (int j = 0; j < this->rows; j++)
			{
				result.mat[i][j] = this->mat[j][i];
			}
		}
		return result;
	}

	template <typename T>
	Matrix<T> Matrix<T>::applyFun(T(*function)(T)) const
	{
		Matrix<T> result(rows, cols);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result.mat[i][j] = (*function)(mat[i][j]);
			}
		}

		return result;
	}


	// () operator overloading to access each element
	template<typename T>
	T& Matrix<T>::operator()(const int row, const int col)
	{
		return this->mat[row][col];
	}

	// == operator over loading
	template <typename T>
	bool Matrix<T>::operator==(const Matrix<T>& rhs)
	{
		if (this->rows == rhs.rows && this->cols == rhs.cols)
		{
			for (int i = 0; i < this->rows; i++)
			{
				for (int j = 0; j < this->cols; j++)
				{
					if (this->mat[i][j] != rhs.mat[i][j])
					{
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}

	// != operator overloading
	template <typename T>
	bool Matrix<T>::operator!=(const Matrix<T>& rhs)
	{
		return !operator==(rhs);
	}

	// fetching sub-matrix
	template <typename T>
	Matrix<T> Matrix<T>::subMatrix(int startR, int startC, int r, int c) const
	{
		if (startR + r <= this->rows && startC + c <= this->cols)
		{
			Matrix<T> result(r, c, 0);
			for (int i = startR; i < startR + r; i++)
			{
				for (int j = startC; j < startC; j++)
				{
					result.mat[i - startR][j - startC] = this->mat[i][j];
				}
			}
			return result;
		}
		else
		{
			std::stringstream ss;
			ss << "Sub-matrix operation failed: check dimension";
			throw MatrixException(ss.str());
		}
	}


	// printing matrix
	template <typename T>
	std::ostream& operator<< (std::ostream& os, Matrix<T>& matOut)
	{
		for (int i = 0; i < matOut.rows; i++)
		{
			for (int j = 0; j < matOut.cols; j++)
			{
				std::cout << matOut.mat[i][j] << ", ";
			}
			std::cout << std::endl;
		}

		return os;
	}
} // end namespace "linalg"