#include <iostream>
#include <math.h>
#include <iomanip>
#include <limits>
#include <fstream>
#include <time.h>
#define N 131072 //4611686018427387903
using namespace std;

double Magnitude(double x, double y);
double Phase(double x, double y);

main(){
	double ts = 1.0/8000, fs = 1.0/ts, real, img;

	 //Valores lidos do arquivo
	std::ifstream infile;
	infile.open("xn.txt");
	float* xn = new float[N];
	for(int i=0; i < N; i++){
		infile >> xn[i];
	}
	for (int m = 0; m < N; m++)
	{
		real = 0; img = 0;
		for (int n = 0; n < N; n++)
		{		
			real += xn[n] * cos(2*M_PI*n*m/N);
			img += -1 * xn[n] * sin(2*M_PI*n*m/N);
		} 

		if (real > -0.0001 && real < 0.0001) real = 0.0;
		if (img > -0.0001 && img < 0.0001) img = 0.0;

		//cout << (m*fs)/N << " " << Magnitude(real, img) << " " << Phase(real, img) << endl;
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
