#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <synchapi.h>
#include <stdlib.h>
#include <vector> 
using namespace std;

struct Pixel
{
	int x;
	int y;
};
struct Direction
{
	int x;
	int y;  
};
struct Brick
{
	int n;
	bool fall;
	int vx[8];
	int vy[8];
	int vz[8];
	struct O
	{
		int x;
		int y;
		int z;
	} org;
	int *p[8];
};
Brick brtype[5];//各種形狀 

class Tetris
{
	int  place[4][4][10];  // if Tetris have cube
	int cur_page;
	double c_matrix[3][3]; //circle
	double d_matrix[3][3]; //dump
	double p_matrix[3][3]; //project
	double vec_matrix[3][3];  // vector for v1,v2,v3
	double alpha, beta; //alpha for circle , beta for dump  (angle!!
	Pixel center; //點 
	Direction v1; 
	Direction v2;
	Direction v3;  //v1,v2,v3 basic vector  for xy plane <-3D  (there z dirction always be 0)
		
  public:
 	 Tetris(); 
	 void ShowTetris();  
	 void ShowLine(int, int, int) const; 	
	 void SetPlace(int, int, int, int);
	 void SetVector();
	 void Circle();
	 void Dump();
	 void Project();
	 void Mul_matrix(double bemul[3][3], double mul[3][3]);
	 void Reset_vec_matrix();
	 void Reset_n_matrix();
	 void SetAngle(double, double); //之後由滑鼠拖曳更改
	 void Set_N_Vector();	 
	 void SetPriority();  
	 void ShowParallelogram(int px, int py, int pz) const;
	 void Show(const double data[3][3])
		{
			for(int i=0; i<3; i++){
				for(int j=0; j<3; j++)
					printf("%7.2lf ",data[i][j]);
				printf("\n");	
			}
			printf("\n");
		}  
	 vector<struct Brick> br;//掉落的方塊 
	 void RunGame();
	 void ezfall();
	 void GenBrick(int,int);
	 void Fall();
};
Tetris :: Tetris()
{	
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++)
				place[i][j][k] = 0;
				
	center.x = 500;
	center.y = 400;
	
	for(int i=0; i<3; i++)
		for(int j=0 ;j<3; j++)
			vec_matrix[i][j] = 0;
	vec_matrix[0][0] = 70;
		vec_matrix[1][1] = vec_matrix[2][2] = -70;
	
	alpha = 45;
	beta = 25;
	cur_page = 0;
/*	v1.x = 80;  //100
	v1.y = 0;
	
	v2.x = 0;  //50
	v2.y = 0;	//75
	
	v3.x = 0;
	v3.y = -80; //100
	
	angle = 0;	 */
	
	//brick 各種形狀的初值 
	brtype[0].n=4;
	int V1[4][3]={{0,0,0},{0,0,1},{0,0,2},{0,0,3}};
	for(int i=0;i<4;i++)
	{
		brtype[0].vx[i]=V1[i][0];
		brtype[0].vy[i]=V1[i][1];
		brtype[0].vz[i]=V1[i][2];
	}
	
	brtype[1].n=8;
	int V2[8][3]={{0,0,0},{1,0,0},{0,1,0},{1,1,0},{0,0,1},{1,0,1},{0,1,1},{1,1,1}};
	for(int i=0;i<8;i++)
	{
		brtype[1].vx[i]=V2[i][0];
		brtype[1].vy[i]=V2[i][1];
		brtype[1].vz[i]=V2[i][2];
	}
}
