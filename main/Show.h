#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <synchapi.h>
#include <stdlib.h>
//#include "Class.h"
void Tetris :: Circle()
{
	c_matrix[0][2] = -sin(alpha * M_PI / 180);
	c_matrix[2][0] = -c_matrix[0][2];
	c_matrix[0][0] = c_matrix[2][2] = cos(alpha * M_PI / 180);
	c_matrix[0][1] = c_matrix[1][0] = c_matrix[1][2] = c_matrix[2][1] = 0;
	c_matrix[1][1] = 1;
}
void Tetris :: Dump()
{
	d_matrix[0][0] = 1;
	d_matrix[0][1] = d_matrix[0][2]	= d_matrix[1][0] = d_matrix[2][0] = 0;
	d_matrix[1][1] = d_matrix[2][2] = cos(beta * M_PI / 180);
	d_matrix[1][2] = -sin(beta * M_PI / 180);
	d_matrix[2][1] = -d_matrix[1][2];
}
void Tetris :: Project()
{
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			p_matrix[i][j] = 0;
						
	p_matrix[0][0] = p_matrix[1][1] = 1;	
}
void Tetris :: Mul_matrix(double bemul[3][3], double mul[3][3])
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
void Tetris :: SetAngle(double a1, double a2)
{
	alpha  = a1;
	beta = a2;
}
void Tetris :: Reset_vec_matrix()
{
	int len = 70;  //here can change cube's length 
	for(int i=0; i<3; i++)
		for(int j=0 ;j<3; j++)
			vec_matrix[i][j] = 0;
	vec_matrix[0][0] = len;
		vec_matrix[1][1] = vec_matrix[2][2] = -len; 
}
void Tetris :: SetVector()
{
	Circle();
	Dump();
	Project();
	Mul_matrix(vec_matrix, c_matrix); //step.1 circle	
//	Show(vec_matrix);
	Mul_matrix(vec_matrix, d_matrix); //step.2 dump
//	Show(vec_matrix);
	Mul_matrix(vec_matrix, p_matrix); //step.3 project
//	Show(vec_matrix);
	v1.x = (int)vec_matrix[0][0];
	v1.y = (int)vec_matrix[1][0];
	
	v2.x = (int)vec_matrix[0][2];
	v2.y = (int)vec_matrix[1][2];
	
	v3.x = (int)vec_matrix[0][1];
	v3.y = (int)vec_matrix[1][1];
	Reset_vec_matrix();	
}
void Tetris :: ShowTetris()   
{
	setvisualpage(cur_page);    
    cur_page = -cur_page + 1;    
    setactivepage(cur_page);
    cleardevice();
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++)  //*v3.y
				if(place[i][j][k])
					ShowLine(i,j,k);
	 			
}
void Tetris :: ShowLine(int px, int py, int pz) const 
{
	int x = center.x + (px-2)*(v1.x) + (py-2)*(v2.x) + (pz-5)*(v3.x);
	int y = center.y + (px-2)*(v1.y) + (py-2)*(v2.y) + (pz-5)*(v3.y);
//	printf("%d %d\n",x,y);
	line(x, y, x+v1.x, y+v1.y);
	line(x, y, x+v2.x, y+v2.y);
	line(x+v1.x, y+v1.y, x+v1.x+v2.x, y+v1.y+v2.y);
	line(x+v2.x, y+v2.y, x+v1.x+v2.x, y+v1.y+v2.y);
	
	line(x, y, x+v3.x, y+v3.y);
	line(x+v1.x, y+v1.y, x+v1.x+v3.x, y+v1.y+v3.y); 
	line(x+v2.x, y+v2.y, x+v2.x+v3.x, y+v2.y+v3.y); 
	line(x+v1.x+v2.x, y+v1.y+v2.y, x+v1.x+v2.x+v3.x, y+v1.y+v2.y+v3.y);
	
	line(x+v3.x, y+v3.y, x+v1.x+v3.x, y+v1.y+v3.y);
	line(x+v3.x, y+v3.y, x+v2.x+v3.x, y+v2.y+v3.y);
	line(x+v1.x+v3.x, y+v1.y+v3.y, x+v1.x+v2.x+v3.x, y+v1.y+v2.y+v3.y);
	line(x+v2.x+v3.x, y+v2.y+v3.y, x+v1.x+v2.x+v3.x, y+v1.y+v2.y+v3.y);
}
void Tetris :: SetPlace(int x, int y, int z, int color){
	place[x][y][z] = color;
} 
