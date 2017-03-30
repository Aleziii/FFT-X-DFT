#include <iostream>
#include <math.h>
#include <iomanip>
#include <limits>
#include <fstream>
#include <time.h>
#define N 2097152 //4611686018427387903
using namespace std;

double Magnitude(double x, double y);
double Phase(double x, double y);

main(){
	double xn, ts = 1.0/8000, fs = 1.0/ts, real, img;

	ofstream file("xn.txt");
	real = 0; img = 0;
	for (int n = 0; n < N; n++)
	{	
		xn = sin(2*M_PI*1000*n*ts) + 0.5*sin(2*M_PI*2000*n*ts + M_PI*3/4); 	
		file<<xn<<"\n";	
	} 
}

double Magnitude(double x, double y){
	double mag;
	mag = sqrt((pow(x,2))+(pow(y,2)));

	return mag;
}

double Phase(double x, double y){
	double phase;
	phase = atan(y/x);
	phase = (phase*180)/M_PI;

	return isnan(phase) ? 0.0 : phase;
}
