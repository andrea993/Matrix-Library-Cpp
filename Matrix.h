/*
 * Matrix.h
 *
 *  Created on: 29 ago 2017
 *      Author: andrearch
 */
#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <istream>
#include <ostream>
#include <string>
#include <initializer_list>

using namespace std;

template <class T>
class Matrix
{
private:
	template <typename TE> friend Matrix<TE> operator*(const Matrix<TE>& a, const Matrix<TE>& b);
	template <typename TE> friend Matrix<TE> operator*(const TE& a, const Matrix<TE>& b);
	template <typename TE> friend Matrix<TE> operator*(const Matrix<TE>& a, const TE& b);
	template <typename TE> friend Matrix<TE> operator+(const Matrix<TE>& a, const Matrix<TE>& b);
	template <typename TE> friend Matrix<TE> operator-(const Matrix<TE>& a, const Matrix<TE>& b);
	template <typename TE> friend bool operator==(const Matrix<TE>& a, const Matrix<TE>& b);
	template <typename TE> friend ostream& operator<<(ostream &os, const Matrix<TE>& x);
	template <typename TE> friend istream& operator>>(istream &is, Matrix<TE>& x);


	vector<vector<T>> mat;
	unsigned N;
	unsigned M;


public:
	Matrix<T>(): N(0), M(0) {}

	Matrix<T>(unsigned N, unsigned M, T init=0)
	{
		this->N=N;
		this->M=M;

		mat.resize(N);
		for (unsigned i=0; i<N; i++)
		{
			mat[i].resize(M);
			fill(mat[i].begin(),mat[i].end(),init);
		}

	}

	Matrix<T>(const Matrix &m)
	{
		mat=m.mat;
		N=m.N;
		M=m.M;
	}

	Matrix<T>(const vector<vector<T>> &m)
	{
		unsigned c=0;
		if(m.size()>0)
		{
			c=m[0].size();
			for (unsigned i=1; i<m.size();i++)
				if(m[i].size()!=c)
					throw logic_error("Not a matrix");
		}
		mat=m;
		N=m.size();
		M=c;
	}

	Matrix<T>(initializer_list<initializer_list<T>> list)
	{
		 N=list.size();
		 mat.resize(N);

		 M=0;
		 if (N>0)
			 M=list.begin()->size();

		 unsigned i=0;
		 for (const auto& r : list)
		 {
			 mat[i].resize(M);
			 unsigned j=0;
			 for (const auto& val : r)
			 {
				 mat[i][j]=val;;
				 j++;
			 }
			 if (M!=j)
				 logic_error("Not a matrix");

			 i++;

		 }
	}

	Matrix<T>& operator=(const vector<vector<T>> &m);
	vector<T>& operator[](unsigned i) { return mat[i]; }
	vector<T> operator[](unsigned i) const { return mat[i]; }
	Matrix<T>& operator+=(const Matrix<T> &m);
	Matrix<T>& operator-=(const Matrix<T> &m);
	Matrix<T>& operator*=(const Matrix<T> &m);

	Matrix<T>& Fill(const T &val)
	{
		for (unsigned i=0; i<N; i++)
			fill(mat[i].begin(),mat[i].end(),val);

		return *this;
	}

	Matrix<T>& AppendRow(T init=0)
	{
		vector<T> r(M,init);
		mat.push_back(r);
		N++;
		return *this;
	}

	Matrix<T>& AppendCol(T init=0)
	{
		for (unsigned i=0;i<N;i++)
			mat[i].push_back(init);
		M++;
		return *this;
	}

	Matrix<T>& Clear()
	{
		mat.clear();
		N=M=0;
		return *this;
	}


	unsigned Rows() const { return N; }
	unsigned Cols() const { return M; }

	Matrix<T> Coff(unsigned i, unsigned j) const;
	T Det() const;
	Matrix<T> Inv() const;


	static T Det(const Matrix<T>& x);
	static Matrix<T> LinSolve(const Matrix &A, const Matrix &b) { return A.Inv()*b; }


};

#include "Matrix.tpp"

#endif /* MATRIX_H_ */
