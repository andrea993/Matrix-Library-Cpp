//============================================================================
// Name        : matrixLib.cpp
// Author      : Andrea993
// Version     : 1.0
//============================================================================

#include <iomanip>
#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {

	/* In this main function I show you how to use this library,
	 * you have only to include the "Matrix.h" file in your project
	 * and start use it
	 *
	 * Note: you should build with -std=c++11*/


	/* MATRIX DECLARATION
	 * Matrix uses template, so you can make matrices of each type or class you want.
	 * There are several way to declare a Matrix (see constructors), for example you can set
	 * data manually
	 */

	Matrix<double> a={
		{ 17.2,    24.4,    1.5  },
		{ 23.8,     5.1,    7.4  },
		{  4.9,     6.4,    13.2 }
	};

	/*Alternatively you can make an empty Matrix and set the value of each cell*/

	Matrix <double> b(2,2,10); //2x2 matrix with each cell set to 10
	b[1][1]=5;
	b.AppendCol(100); //initialize each element of the new column with 100;
	b.AppendRow(20);

	/*It is possible to print matrices with ostrem */

	cout<<"matrix a:\n"<<a<<endl;
	cout<<"matrix b:\n"<<b<<endl;

	/*and read matrix with istream */
	cout<<"Write a matrix in format [ x11, x12,..., x1N ; x21, x22,..., x2N ; xM1, xM2,...,xMN]"<<endl
			<<"for example you can insert [1, 2, 3 ; 4, 5, 6 ; 7, 8, 9]"<<endl;

	Matrix<float> mi;
	cin>>mi;

	cout<<"You have inserted:\n"<<mi<<endl;

	/* There are also some linear algebra functions */
	cout<<"The determinant of a is: "<<a.Det()<<endl;
	cout<<"3*a=\n"<<3.0*a<<endl;
	cout<<"The inverse of a is:\n"<<a.Inv()<<endl;
	cout<<"a*b=:\n"<<a*b<<endl;

	/* You can also solve a linear equation system */
	Matrix<float> A1={
			{ 3,	1 },
			{ 7, 17 }
	};

	Matrix<float> b1={
			{1},
			{1}
	};

	Matrix<float> x=Matrix<float>::LinSolve(A1, b1);

	cout<<"The solution of the linear equation system is:\n"<<x<<endl;

	cout<<"End of tutorial, have fun ;)"<<endl;

	return 0;

}
