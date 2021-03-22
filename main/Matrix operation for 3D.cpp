#include <stdio.h>
#include <math.h>
void Circle(double alpha, double c_matrix[3][3])
{
	c_matrix[0][2] = -sin(alpha * M_PI / 180);
	c_matrix[2][0] = -c_matrix[0][2];
	c_matrix[0][0] = c_matrix[2][2] = cos(alpha * M_PI / 180);
	c_matrix[0][1] = c_matrix[1][0] = c_matrix[1][2] = c_matrix[2][1] = 0;
	c_matrix[1][1] = 1;
}
void Dump(double beta, double d_matrix[3][3])
{
	d_matrix[0][0] = 1;
	d_matrix[0][1] = d_matrix[0][2]	= d_matrix[1][0] = d_matrix[2][0] = 0;
	d_matrix[1][1] = d_matrix[2][2] = cos(beta * M_PI / 180);
	d_matrix[1][2] = -sin(beta * M_PI / 180);
	d_matrix[2][1] = -d_matrix[1][2];
}
void Project(double p_matrix[3][3])
{
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			p_matrix[i][j] = 0;
						
	p_matrix[0][0] = p_matrix[1][1] = 1;	
}
void Mul_matrix(double bemul[3][3], double mul[3][3])
{
	double temp[3][3] = {0};
	
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			for(int k=0; k<3; k++)
				temp[i][j] += mul[i][k] * bemul[k][j]; 
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			bemul[i][j] = temp[i][j];
}
void Show(const double data[3][3])
{
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++)
			printf("%7.2lf ",data[i][j]);
		printf("\n");	
	}
	printf("\n");
}
int main()
{
	int len;
	double alpha, beta;
	double c_matrix[3][3], d_matrix[3][3], p_matrix[3][3], ori[3][3] = {0};
	while(scanf("%d %lf %lf", &len, &alpha, &beta)){
		Circle(alpha, c_matrix);
		Show(c_matrix);
		Dump(beta, d_matrix);
		Project(p_matrix);
		ori[0][0] = len;
		ori[1][1] = ori[2][2] = -len;
		Show(ori);	
		Mul_matrix(ori, c_matrix);
		Show(ori);	
		Mul_matrix(ori, d_matrix);
		Show(ori);	
		Mul_matrix(ori, p_matrix);
		Show(ori);	
		
	}
	return 0;
}
