#include <stdio.h>

#define x_count 51
#define y_count 51
#define dx 0.002 //dx=dy for square mesh
#define dy 0.002 //dx=dy for square mesh
#define conv 100 //convectional coeff.
#define infit 20 //ambient temperature
#define roott 80 //root temperature
#define initt 50 //initial temperature
#define cond 300.0 //conductivity
#define iter 1000 //iteration #


void main()
{
	double temp[x_count][y_count]; //node[i][j]
	int i, j, l=0; //l = iteration parameter
	char filename[]="test.txt";
	FILE *fp;
	fp=fopen(filename, "w");

	for(i=0; i<x_count; i++)
	{
		for(j=0; j<y_count; j++)
		{
			temp[i][j]=initt;
		}
	}
	//initial condition
	
	while(l<iter)
	{
		for(j=0; j<y_count; j++)
		{
			temp[0][j]=roott;
		}
		//base temperature
		
		for(i=1; i<x_count-1; i++)
		{
			for(j=1; j<y_count-1; j++)
			{
				temp[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1])/4;
			}
		}
		//interior

		for(i=1; i<x_count-1; i++)
		{
			temp[i][0]=((temp[i-1][0]+temp[i+1][0]+2*temp[i][1]+(2*conv*dx*infit/cond))/(4+(2*conv*dx/cond)));
		}
		//upper edge

		for(i=1; i<x_count-1; i++)
		{
			temp[i][y_count-1]=((temp[i-1][y_count-1]+temp[i+1][y_count-1]+2*temp[i][y_count-2]+(2*conv*dx*infit/cond))/(4+(2*conv*dx/cond)));
		}
		//lower edge

		for(j=1; j<y_count-1; j++)
		{
			temp[x_count-1][j]=((temp[x_count-1][j-1]+temp[x_count-1][j+1]+2*temp[x_count-2][j]+(2*conv*dy*infit/cond))/(4+(2*conv*dy/cond)));
		}
		//tip

		temp[x_count-1][0]=((temp[x_count-2][0]+temp[x_count-1][1]+(2*conv*dx*infit/cond))/(2+(2*conv*dy/cond)));
		//upper corner node

		temp[x_count-1][y_count-1]=((temp[x_count-2][y_count-1]+temp[x_count-1][y_count-2]+(2*conv*dx*infit/cond))/(2+(2*conv*dy/cond)));
		//lower corner node
		
		l++;
	}
	//while

	
	
	for(i=0; i<x_count; i++)
	{
		for(j=0; j<y_count; j++)
		{
			fprintf(fp, "%f\t",temp[i][j]);
		}
		fprintf(fp, "\n");
	}
}
