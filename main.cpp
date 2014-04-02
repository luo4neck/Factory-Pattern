// gsl_mini.h contains the factory of minization algorithms..

#include<fstream>
#include<iostream>
#include<gsl/gsl_multimin.h>
#include<stdlib.h>
#include"gsl_mini.h"
#include"function.h"

using namespace std;

int main()
{
char *FileName = (char *)malloc(sizeof(char));
cout<<"Please input a file FileName:"<<endl;
cin>>FileName;

FILE *fp;//check if the file could be read.. 
if(( fp = fopen(FileName, "r")) == NULL)
    {
    cout<<"Cannot open :"<<FileName<<"!"<<endl;
    free(FileName);
    fclose(fp);
    exit(0);
    }
free(FileName);

int max=0;//read data from the given file..
fscanf(fp, "%d", &max);
cout<<"Number of points in the file: "<<max<<endl;
if(max < 1) 
{
    cout<<"Data in the file is not enough!"<<endl;  
    exit(0);
}

short Nform;// select a functional form at runtime..
cout<<"Please enter a number to select a form:"<<endl;
cout<<"1) Linear: f(x, A, B)=A + Bx"<<endl;
cout<<"2) Exponetial: f(x, A, B)=A*exp(-B*x)"<<endl;
cout<<"3) Gaussian: f(x, A, B)=A*exp((mu-x)/2/B/B)"<<endl;
cin>>Nform;

if(Nform!=1 && Nform!=2 && Nform!=3)// exit if the input number is not 1 or 2 or 3 
{
    cout<<"Please select from form 1 or 2 or 3"<<endl;
    exit(0);
}
cout<<"In form "<<Nform<<":"<<endl;

Factory fact;// make a new object of factory..
Mini* MN = fact(Nform, max); // pointer to the object..

for(int i=0; i<max; ++i)
{
    fscanf(fp, "%lf%lf%lf", &MN->X[i], &MN->Y[i], &MN->err[i]);
}
fclose(fp);

double test = MN->Xsqr(MN->A, MN->B); // just have a test if the pointer works..

/* =============== Minization by gnuplot start from here ============== */

ofstream mini("minidata.dat");// read the sub-range for minization..
for(int i=MN->i1; i<MN->i2; ++i)
{
    mini<<MN->X[i]<<" "<<MN->Y[i]<<" "<<MN->err[i]<<endl;
}
mini.close();

fp = popen("gnuplot -persist", "w");
if(fp == NULL)
{
    cout<<"Cannot plot the data!"<<endl;
    exit(0);
}
if(Nform == 1)
{
    fprintf(fp, "f1(x)=a*x+b\n");
    fprintf(fp, "a=%f;b=%f\n", MN->A, MN->B);
}
else if(Nform == 2)
{
    fprintf(fp, "f1(x)=a*exp(-1*x*b)\n");
    fprintf(fp, "a=%f;b=%f\n", MN->A, MN->B);
}
else
{
    fprintf(fp, "f1(x)=a*exp((mu-x)/2/b/b)\n");
    fprintf(fp, "a=%f;b=%f;mu=%f\n", MN->A, MN->B, MN->mu);
}
fprintf(fp, "unset key\n");
fprintf(fp, "fit f1(x) 'minidata.dat' u 1:2:3 via a,b\n");
fprintf(fp, "plot 'minidata.dat' u 1:2 , f1(x) lw 1 lc rgb 'orange'\n");
fprintf(fp, "pause -1\n");
fclose(fp); 

/* =============== Minization by gnuplot start from here ============== */

cout<<"Please enter a number to select a minimization algorithm:"<<endl;
cout<<"1) gsl_multimin_fminimizer_nmsimplex:"<<endl;
cout<<"2) gsl_multimin_fminimizer_nmsimplex2:"<<endl;
cout<<"3) gsl_multimin_fminimizer_nmsimplex2rand:"<<endl;
cin>>Nform;

if(Nform!=1 && Nform!=2 && Nform!=3) // exit if the input number is not 1 or 2 or 3 
{
    cout<<"Please select from 1, 2 or 3"<<endl;
    exit(0);
}
cout<<"In form "<<Nform<<":"<<endl;

MiniFactory mnfct;
Sim* fct = mnfct(Nform);

return 0;
}
