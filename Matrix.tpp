#ifndef MATRIX_TPP_
#define MATRIX_TPP_

#include "Matrix.h"

// FRIENDS
template <typename TE>
Matrix<TE> operator*(const Matrix<TE>& a, const Matrix<TE>& b)
{
	if(a.M != b.N)
		throw std::logic_error("columns(A)!=rows(B)");
	
	if(a.N<1)
		throw std::logic_error("Empty matrices");

	Matrix<TE> y(a.N,b.M);

	for(unsigned i=0;i<y.N; i++)
	{
		for(unsigned j=0; j<y.M; j++)
		{
			TE sum=0;
			for(unsigned k=0; k<b.N; k++)
				sum+=a.mat[i][k]*b.mat[k][j];

			y.mat[i][j]=sum;

		}
	}

	return y;
}

template <typename TE>
Matrix<TE> operator*(const TE& a, const Matrix<TE>& b)
{
	Matrix<TE> y(b.N,b.M);
	for (unsigned i=0; i< b.N; i++)
		for (unsigned j=0; j<b.M; j++)
			y[i][j]=a*b[i][j];
	
	return y;
}

template <typename TE>
Matrix<TE> operator+(const Matrix<TE>& a, const Matrix<TE>& b)
{
	if (a.N != b.N || a.M!= b.M)
		throw std::logic_error("Operator+ requires two matrices of same size");
	
	Matrix<TE> y(a.N,a.M);
	for (unsigned i=0; i<a.N; i++)
		for (unsigned j=0; j<a.M; j++)
			y.mat[i][j]=a.mat[i][j]+b.mat[i][j];
	
	return y;
}


template <typename TE>
Matrix<TE> operator-(const Matrix<TE>& a, const Matrix<TE>& b)
{
	if (a.N != b.N || a.M!= b.M)
		throw std::logic_error("Operator- requires two matrices of same size");
	
	Matrix<TE> y(a.N,a.M);
	for (unsigned i=0; i<a.N; i++)
		for (unsigned j=0; j<a.M; j++)
			y.mat[i][j]=a.mat[i][j]-b.mat[i][j];
	
	return y;
}


template <typename TE>
Matrix<TE> operator*(const Matrix<TE>& a, const TE& b)
{
	return b*a;
}

template <typename TE>
bool operator==(const Matrix<TE>& a, const Matrix<TE>& b)
{
	if (a.N != b.N || a.M |= b.M)
		return false;

	for (unsigned i=0; i<a.N; i++)
		if(a[i]!=b[i])
			return false;

	return true;
}

template <typename TE> 
std::ostream& operator<<(std::ostream &os, const Matrix<TE>& x)
{
	os << '[' << std::endl;
	for (unsigned i=0; i<x.N-1; i++)
	{	
		for (unsigned j=0; j<x.M-1; j++)
			os << x.mat[i][j] << ",\t";

		os << x.mat[i][x.M-1] << " ;" << std::endl;	
	}

	if(x.N>0)
	{
		for (unsigned j=0; j<x.M-1; j++)
				os << x.mat[x.N-1][j] << ",\t";

		os << x.mat[x.N-1][x.M-1] << std::endl;
	}

	os << "]" <<std::endl;
	
	return os;
}

template <typename TE> 
std::istream& operator>>(std::istream &is, Matrix<TE>& x)
{
	unsigned m;
	x.Clear();
	char c;
	TE v;
	
	is>>c;
	c=is.peek();
	
	if (c!=']')
	{
		do
		{
			x.AppendRow();
			m=0;
			c=0;
			while (c != ';' && c != ']')
			{
				is>>v>>c;
				m++;
				if(m>x.M && x.N>1)
					throw std::logic_error("Input is not a mtrix");

				if(m>x.M)
					x.AppendCol();

				x.mat[x.N-1][m-1]=v;

			}
		} while(c != ']');
		
		if(m != x.M)
			throw std::logic_error("Input is not a matrix");
	}
	
	return is;
	
}


// CLASS METHODS
template <class T>
Matrix<T>& Matrix<T>::operator=(const std::vector<std::vector<T>> &m)
{
	unsigned c=0;
	if(m.size()>0)
	{
		c=m[0].size();
		for (unsigned i=1; i<m.size();i++)
			if(m[i].size()!=c)
				throw std::logic_error("Not a matrix");
	}
	mat=m.mat;
	N=m.size();
	M=c;

	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T> &m)
{
	if (N != m.N || M!= m.M)
		throw std::logic_error("Operator+= requires two matrices of same size");
	
	for (unsigned i=0; i<N; i++)
		for (unsigned j=0; j<M; j++)
			mat[i][j]+=m.mat[i][j];
	
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T> &m)
{
	if (N != m.N || M != m.M)
		throw std::logic_error("Operator= requires two matrices of same size");
	
	for (unsigned i=0; i<N; i++)
		for (unsigned j=0; j<M; j++)
			mat[i][j]-=m.mat[i][j];
	
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T> &m)
{
	*this=*this*m;
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::Coff(unsigned i, unsigned j) const
{
	if (N==0)
		throw std::logic_error("Coff: the matrix is empty");

	Matrix<T> y(N-1,M-1);
	
	unsigned k_c=0;
	for (unsigned k_x=0; k_x<N;k_x++)
	{
		if (k_x==i)
			continue;
		
		unsigned j_c=0;
		for (unsigned j_x=0 ; j_x<N; j_x++)
		{
			if (j_x==j)
				continue;
				
			y.mat[k_c][j_c]=mat[k_x][j_x];
			j_c++;
		}

		k_c++;
	}
	
	return y;	
	
}

template <class T>
T Matrix<T>::Det(const Matrix<T>& x)
{
	if(x.N != x.M)
		throw std::logic_error("Can't compute the determinant of a non square matrix");
	
	if (x.N == 0)
		throw std::logic_error("Empty matrix");
	
	if (x.N==1)
		return x.mat[0][0];
	
	T y=0;
	signed char d=1;
	
	for (unsigned i=0; i<x.N; i++)
	{
		y+=d*x.mat[i][0]*Det(x.Coff(i,0));
		d=-d;
	}

	return y;
}

template <class T>
T Matrix<T>::Det() const
{
	return Det(*this);
}

template <class T>
Matrix<T> Matrix<T>::Inv() const
{
	double det_x=Det();
	if(abs(det_x)<std::numeric_limits<double>::epsilon())
		throw std::logic_error("Can't invert matrix  (determinant=0)");
	
	Matrix<T> y(N,M);
	
	signed int d=1;

	for (unsigned i=0; i<N; i++)
		for (unsigned j=0; j<N; j++)
		{
			y.mat[j][i]=d*Det(Coff(i,j))/det_x;
			d=-d;
		}

	return y;
	
}


#endif
