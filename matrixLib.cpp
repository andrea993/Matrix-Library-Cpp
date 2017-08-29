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

	Matrix<double> a= {{
	{ 17,    24,    1},
	{ 23,    5,     7 },
	{  4,     6,    13 }

}};


	Matrix<double> b {{
		 {17.0000,   23.0000,    4.0000,    0.2785,    0.5469},
		 {24.0000,    5.0000 ,   6.0000,    0.9575,    0.9649},
		 {1.0000,    7.0000,   13.0000,   0.1576 ,   0.9706}

	}};

	cout<<a<<endl;


	cout<<"det: "<<a.Det()<<endl;

	Matrix<double> y=a.Inv();
	cout<<"Inv:\n"<<y<<endl;


	Matrix<double> y2=a*b;
	cout<<"Mul:\n"<<setprecision(3)<<y2<<endl;

	Matrix<int> mi;
	cout<<"Write a matrix:"<<endl;
	cin>>mi;

	cout<<"Your matrix is:"<<endl<<mi<<endl;

	return 0;

}
