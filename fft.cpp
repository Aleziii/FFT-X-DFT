#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>
#define N  131072 //33554432

void FFT(float *real, float *imag, int NPuntos)
{
  int Fases, Grupos;
  int fase, grupo, NumDatosGrupo, dual;
  int i, j, grupoini, pos, pos_dual,aux;
  float real_i, imag_i, real_dual, imag_dual;
  float coseno, seno,PI=3.141592654;
  Fases = log(NPuntos)/log(2.0F)+1;
  Grupos = 1;
  for(fase=0; fase< Fases; fase++)
  {
    NumDatosGrupo = NPuntos/Grupos ;
    dual = NumDatosGrupo/2;
    grupoini = 0;
    for(grupo = 0; grupo < Grupos; grupo++)
    {
      for(i=0; i< dual; i++)
      {
	pos = i + grupoini;
	pos_dual = pos + dual;
	real_i = real[pos] + real[pos_dual];
	imag_i = imag[pos] + imag[pos_dual];
	real_dual = real[pos] - real[pos_dual];
	imag_dual = imag[pos] - imag[pos_dual];
	coseno = cos(2*PI*i/NumDatosGrupo);
	seno = sin(2*PI*i/NumDatosGrupo);
	real[pos_dual] = real_dual*coseno + imag_dual*seno;
	imag[pos_dual] = imag_dual*coseno - real_dual*seno ;
	real[pos] = real_i;
	imag[pos] = imag_i;
      }
      grupoini += NumDatosGrupo;
    }
    Grupos *= 2;
  }

// Bit reversal
  pos = 0;
  for(i=0; i < NPuntos; i++)
  {
    pos = i;
    dual = 0;
    aux = NPuntos/2;
    for(j=0 ; j <= Fases ; j++)
    {
      dual = dual + (pos %2) * aux;
      pos = pos/2;
      aux = aux/2;
    }
    if(dual > i)
    {
      real_i = real[i];
      imag_i = imag[i];
      real[i] = real[dual];
      imag[i] = imag[dual];
      real[dual] = real_i;
      imag[dual] = imag_i;
    }
  }
}

int main()
{
   //Valores lidos do arquivo
  std::ifstream infile;
  infile.open("xn.txt");
  float* real = new float[N];
  float* imag = new float[N];  
  for(int i=0; i < N; i++){
  	infile >> real[i];
  	imag[i] = 0;
  }
  //std::cout<<"lidos\n\n";
  
  
  //Valores usados no exemplo do livro texto
  //float real[8] = {0.3535,0.3535,0.6464,1.0607,0.3535,-1.0607,-1.3535,-0.3535};
  //float imag[8] = {0,0,0,0,0,0,0,0};
  int i,a = N;
  float c;
  //clrscr();
  FFT(real,imag,a);
  
  
  //Este laco eh para nao imprimir numeros muito pequenos
  /*for(i=0; i<a; i++)
  {
     c = real[i]; if (c<0) c = c * -1;
     if (c < 0.001) real[i] = 0;
     c = imag[i]; if (c<0) c = c * -1;
     if (c < 0.0001) imag[i] = 0;
  }
  for(i=0; i<a; i++)
  {
    std::cout <<"\n X["<<i<<"]= ("<< real[i]<<") + j("<<imag[i]<<")";
  }
  std::cout<<"\n\n" ;
  */
  
  return 0;
}
