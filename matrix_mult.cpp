//Serial and Parallel Matrix Multiplication
#include<iostream>
#include<cstdlib>
#include<omp.h>
#include<time.h>
#define max 1000
using namespace std;

int A[max][max];
int B[max][max];
int C[max][max];

void serial_m(int A[max][max],int B[max][max],int C[max][max])			//Serial matrix multiplication
{
	int i,j,k;
	for(i=0;i<max;i++)
	{
		for(j=0;j<max;j++)
		{
			for(k=0;k<max;k++)
			{
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
}

void parallel_m(int A[max][max],int B[max][max],int C[max][max])		//Parallel Matrix Multiplication
{
	int i,j,k;
   #pragma omp for private(i,j,k) shared(A,B,C)					//pragma directives
	for(i=0;i<max;i++)
	{
		for(j=0;j<max;j++)
		{
			for(k=0;k<max;k++)
			{
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
}

int main()
{
	int n,i,j;
	double e1,s1,r1=0,e2,s2,r2=0;
	for(i=0;i<max;i++)
	{
		for(j=0;j<max;j++)
		{
			A[i][j]=2;
			B[i][j]=3;
		}
	}
	s1=omp_get_wtime();							//serial time (start)
	serial_m(A,B,C);
	e1=omp_get_wtime();							//serial time (end)
	r1=e1-s1;								//Ts = T(end) - T(start) 
	s2=omp_get_wtime();							//parallel time(start)
	parallel_m(A,B,C);
	e2=omp_get_wtime();							//parallel time(end)
	r2=e2-s2;								//Tp = T(end) - T(start)
	cout<<"\nTs: "<<r1;
	cout<<"\nTp: "<<r2;	
	return 0;
}
