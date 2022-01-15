#include <stdio.h>

#define x_count 51
#define y_count 51
#define t_count 2400 //seconds
#define dx 0.002 //dx=dy for square mesh
#define dy 0.002 //dx=dy for square mesh
#define conv 100 //convectional coeff.
#define infit 20 //ambient temperature
#define roott 80 //root temperature
#define initt 20 //initial temperature
#define cond 300.0 //conductivity
#define alpha 0.001 //thermal diffusivity
#define dt 0.002 //dt = dx^2/2*alpha
#define tau 0.5 //tau = (alpha*dt)/(dx^2)


void main()
{
	double temp[x_count][t_count]; //node[i][j]
	int i, j = 0;
	int l = 1;
	char filename[]="test.txt";
	FILE *fp;
	fp=fopen(filename, "w");

	for(j=0; j<t_count; j++)
	{
		temp[0][j]=roott;

		for(i=1; i<x_count; i++)
		{
			temp[i][j]=initt;
		}
	}
	//initial condition
	
	while(l<t_count)
	{
			temp[0][l]=roott;
		//base temperature
		
			for(i=1; i<x_count-1; i++)
			{
				temp[i][l]=(temp[i-1][l-1]+temp[i+1][l-1])/2;
			}
		//interior


			temp[x_count-1][l]=(((-conv*dx/cond)*temp[x_count-1][l-1])+(tau*(2*(temp[x_count-2][l-1])+2*(conv*dx*infit/cond))));
		//tip

		l++;
	}
	//while

	
	
	for(j=0; j<t_count; j++)
	{
		for(i=0; i<x_count; i++)
		{
			fprintf(fp, "%f\t",temp[i][j]);
		}
		fprintf(fp, "\n");
	}
}
