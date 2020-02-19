//Serial and Parallel bubblesort
#include<iostream>
#include<bits/stdc++.h>
#include<omp.h>
#include<time.h>
#include<cstdlib>
#define MAX 1000000
using namespace std;

void fillarr(int a[],int b[],int n)				//populating the array with random values				
{
	int i;
	for(i=0;i<n;i++)
	{
		a[i]=rand()%1000 + 1;
		b[i]=a[i];	
	}
}

void disp(int a[],int n)
{
	int i;
	cout<<endl;
	for(i=0;i<n;i++)
		cout<<" "<<a[i];
}

void serial_b(int a[],int n)					//serial bubblesort
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				swap(a[j],a[j+1]);
			}
		}
	}
}

void parallel_b(int a[],int n)					//parallel bubblesort
{
	int i;
	for(i=0;i<(n+1)/2;i++)
	{
		int j;
		#pragma omp parallel for private(j)		//pragma directives
		for(j=0;j<n-1;j=j+2)
		{
			if(a[j]>a[j+1])
			{
				swap(a[j],a[j+1]);
			}
		}
		int k;
		#pragma omp parallel for private(k)
		for(k=1;k<n-1;k=k+2)
		{
			if(a[j]>a[j+1])
			{
				swap(a[j],a[j+1]);
			}
		}
	}
}


int main()
{
	int i,j;
	int a[MAX],b[MAX],n;
	double s1,s2,e1,e2,r1,r2;
	cout<<"Enter no. of elements: ";
	cin>>n;
	fillarr(a,b,n);
	disp(a,n);

	s1=omp_get_wtime();				// serial time
	cout<<endl<<endl<<s1;
	serial_b(a,n);
	disp(a,n);
	e1=omp_get_wtime();
	cout<<endl<<endl<<e1;
	r1=e1-s1;					//Ts = T(end) - T(start)

	disp(b,n);

	s2=omp_get_wtime();				// parallel time
	parallel_b(b,n);
	disp(b,n);
	e2=omp_get_wtime();
	r2=e2-s2;					//Tp = T(end) - T(start)

	cout<<"\nTs: "<<r1;
	cout<<"\nTp: "<<r2;
	return 0;
}	
	
	
