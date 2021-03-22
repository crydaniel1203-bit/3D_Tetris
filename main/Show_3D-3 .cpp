#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <synchapi.h>
#include <stdlib.h>
//#include "Perspective.h"
#define W_KEY 0x57
#define A_KEY 0x41
#define S_KEY 0x53
#define D_KEY 0x44
#define I 4
#define J 4
#define K 10
struct Pixel
{
	int x;
	int y;
};
struct Direction
{
	int x;
	int y;  
	int z;
};
struct N_Direction
{
	double x;
	double y;  
	double z;
};
struct data_for_Priority{
	int i;
	int j;
	int k;
	double value;
};
struct Real_Coordinate
{
	double x;
	double y;
	double z;

};
struct P_Vecter
{
	Direction v1;
	Direction v2;
	Direction v3;
	Direction v4;
	Direction v5;
	Direction v6;			
	Direction v7;
}; 
class Tetris
{
	int  place[4][4][10];  // if Tetris have cube
	int priority[4][4][10], one_priority; //*
	int cur_page;
	double c_matrix[3][3]; //circle
	double d_matrix[3][3]; //dump
	double p_matrix[3][3]; //project
	double vec_matrix[3][3];  // vector for v1,v2,v3
	double n_matrix[3][3]; //*
	double alpha, beta; //alpha for circle , beta for dump  (angle!!
	Pixel center; //點 
	Direction v1; 
	Direction v2;
	Direction v3;  //v1,v2,v3 basic vector  for xy plane <-3D  (there z dirction always be 0)
	Direction v4; 
	Direction v5;
	Direction v6;
	Direction v7;
	
	N_Direction n;  //*
	P_Vecter p_vector[I][J][K];
	Real_Coordinate data[I+1][J+1][K+1];
	
		
  public:
 	 Tetris();
 	 
	 void Set_Real_Coordinare();
	 void Set_Perspective_Vector();
	 void Set_XY(int *a, int *b, int px, int py, int pz);
	 void ShowParallelogram3D(int px, int py, int pz);
	 void ShowLine3D(int px, int py, int pz);
	 
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
	 /*void Show(const double data[3][3])
		{
			for(int i=0; i<3; i++){
				for(int j=0; j<3; j++)
					printf("%7.2lf ",data[i][j]);
				printf("\n");	
			}
			printf("\n");
		}  */
	 void Set_N_Vector();	
	 void SetPriority();                                   //*
	 void ShowParallelogram(int px, int py, int pz) const; //*	
};
Tetris :: Tetris()
{	
	int count = 1;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++){
				place[i][j][k] = 8;
				priority[i][j][k] = count;
				count++;
			}
				
				
	center.x = 500;
	center.y = 400;
	
	for(int i=0; i<3; i++)
		for(int j=0 ;j<3; j++)
			vec_matrix[i][j] = 0;
	vec_matrix[0][0] = 5;
	vec_matrix[1][1] = vec_matrix[2][2] = -5;
	
	
	//for 法向量的矩陣 ,3*3是為了配合function Mul_matrix 
	for(int i=0; i<3; i++)
		for(int j=0 ;j<3; j++)
			n_matrix[i][j] = 0;
	n_matrix[2][0] = -1;
	
	alpha = 45;
	beta = 25;
	cur_page = 0;
	one_priority = 0;   //* 
	
/*	v1.x = 80;  //100
	v1.y = 0;
	
	v2.x = 0;  //50
	v2.y = 0;	//75
	
	v3.x = 0;
	v3.y = -80; //100
	
	angle = 0;	 */
}
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
	int len = 180*3*2;  //here can change cube's length  
	for(int i=0; i<3; i++)
		for(int j=0 ;j<3; j++)
			vec_matrix[i][j] = 0;
	vec_matrix[0][0] = len;
	vec_matrix[1][1] = vec_matrix[2][2] = -len; 
}
void Tetris :: Reset_n_matrix()
{
	
	for(int i=0; i<3; i++)
		for(int j=0 ;j<3; j++)
			n_matrix[i][j] = 0;
	n_matrix[2][0] = -1;
	
}
void Tetris :: Set_N_Vector(){
	alpha = -alpha;  //考量了其相對關西 
	beta = -beta;
	Circle();
	Dump();
	Mul_matrix(n_matrix, c_matrix);
	Mul_matrix(n_matrix, d_matrix);
	
	
	n.x = n_matrix[0][0];
	n.y = n_matrix[1][0];
	n.z = n_matrix[2][0];
	printf("Alpha = %3lf, Beta = %3lf ",alpha, beta);   //  -90 <= alpha,beta <= 90   
	printf("n.x = %lf\n",n.x);
	printf("n.y = %lf\n",n.y);
	printf("n.z = %lf\n",n.z);
	Reset_n_matrix();
	alpha = -alpha;
	beta = -beta;
}	
void Tetris :: SetVector()
{
	Circle();
	Dump();
	Project();
	Mul_matrix(vec_matrix, c_matrix); //step.1 circle	
	Mul_matrix(vec_matrix, d_matrix); //step.2 dump
//	Mul_matrix(vec_matrix, p_matrix); //step.3 project	

	v1.x = vec_matrix[0][0];
	v1.y = vec_matrix[1][0];
	
	v2.x = vec_matrix[0][2];
	v2.y = vec_matrix[1][2];
	
	v3.x = vec_matrix[0][1];
	v3.y = vec_matrix[1][1];
	
	Set_Real_Coordinare();
	Set_Perspective_Vector();

/*	n.x =  vec_matrix[0][2]/70;
	n.y =  vec_matrix[1][2]/70;
	n.z = -vec_matrix[2][2]/70;
	printf("nx = %lf, ny= %lf, nz = %lf\n", n.x, n.y, n.z);
	printf("v1_x = %lf, v1_ y = %lf, v1_z =%lf\n", vec_matrix[0][0]/70, vec_matrix[1][0]/70, vec_matrix[2][0]/70);
	printf("v2_x = %lf, v2_ y = %lf, v2_z =%lf\n", vec_matrix[0][2]/70, vec_matrix[1][2]/70, vec_matrix[2][2]/70);
	printf("v3_x = %lf, v3_ y = %lf, v3_z =%lf\n", vec_matrix[0][1]/70, vec_matrix[1][1]/70, vec_matrix[2][1]/70);
	printf("%lf %lf\n",alpha,beta);*/ 
	
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
	/*for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++)  //*v3.y
				if(place[i][j][k])
					ShowLine(i,j,k);*/
	for(int order=1; order<=160; order++)  // 1<= order <=160	
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				for(int k=0; k<10; k++)  //*v3.y
					if(place[i][j][k] && (priority[i][j][k]==order)){
					//	ShowLine3D(i,j,k);
						ShowParallelogram3D(i,j,k);
					//	ShowParallelogram(i,j,k);
					}
						 
						 
/*	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++)  //*v3.y
					ShowLine(i,j,k);  	*/			 
	 			
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
void Tetris :: ShowParallelogram(int px, int py, int pz) const
{
	int x = center.x + (px-2)*(v1.x) + (py-2)*(v2.x) + (pz-5)*(v3.x);
	int y = center.y + (px-2)*(v1.y) + (py-2)*(v2.y) + (pz-5)*(v3.y);
	int parallelogram1[10] = {x+v3.x, y+v3.y, x+v2.x+v3.x, y+v2.y+v3.y, x+v1.x+v2.x+v3.x, y+v1.y+v2.y+v3.y, x+v1.x+v3.x, y+v1.y+v3.y, x+v3.x, y+v3.y};
	int parallelogram2[10] = {x+v2.x, y+v2.y, x+v2.x+v3.x, y+v2.y+v3.y, x+v1.x+v2.x+v3.x, y+v1.y+v2.y+v3.y, x+v1.x+v2.x, y+v1.y+v2.y, x+v2.x, y+v2.y};
	int parallelogram3[10] = {x+v1.x, y+v1.y, x+v1.x+v3.x, y+v1.y+v3.y, x+v1.x+v2.x+v3.x, y+v1.y+v2.y+v3.y, x+v1.x+v2.x, y+v1.y+v2.y, x+v1.x, y+v1.y};
	int parallelogram4[10] = {x, y, x+v3.x, y+v3.y, x+v2.x+v3.x, y+v2.y+v3.y, x+v2.x, y+v2.y, x, y};
	int parallelogram5[10] = {x, y, x+v1.x, y+v1.y, x+v1.x+v3.x, y+v1.y+v3.y, x+v3.x, y+v3.y, x, y};
	int parallelogram6[10] = {x, y, x+v1.x, y+v1.y, x+v1.x+v2.x, y+v1.y+v2.y, x+v2.x, y+v2.y, x, y};	
	setfillstyle(INTERLEAVE_FILL, place[px][py][pz]);
	//printf("%d\n",one_priority);
	switch(one_priority){ // 0 1 4 5 2 3 6 7
		case 0:
			fillpoly(5, parallelogram1);  //前一個參數放5 ,因為為四邊形且需要繞一圈 所以為五個點 
			fillpoly(5, parallelogram2);
			fillpoly(5, parallelogram3);
			break;
		case 1:
			fillpoly(5, parallelogram1);
			fillpoly(5, parallelogram2);
			fillpoly(5, parallelogram4);
			break;	
		case 2:
			fillpoly(5, parallelogram1);
			fillpoly(5, parallelogram3);
			fillpoly(5, parallelogram5);
			break;	
		case 3:
			fillpoly(5, parallelogram1);
			fillpoly(5, parallelogram4);
			fillpoly(5, parallelogram5);
			break;	
		case 4:
			fillpoly(5, parallelogram2);
			fillpoly(5, parallelogram3);
			fillpoly(5, parallelogram6);
			break;	
		case 5:
			fillpoly(5, parallelogram2);
			fillpoly(5, parallelogram4);
			fillpoly(5, parallelogram6);
			break;
		case 6:
			fillpoly(5, parallelogram3);
			fillpoly(5, parallelogram5);
			fillpoly(5, parallelogram6);
			break;
		case 7:
			fillpoly(5, parallelogram4);
			fillpoly(5, parallelogram5);
			fillpoly(5, parallelogram6);
			break;		
	}
	
   /*fillpoly(5, parallelogram1);
	fillpoly(5, parallelogram2);
	fillpoly(5, parallelogram3);*/ 
}
void Tetris :: SetPlace(int x, int y, int z, int color){
	place[x][y][z] = color;
} 
void Tetris :: SetPriority() 	//處理所有的優先顯示問題  //* 
{  
	double t;
	data_for_Priority data[4][4][10], temp;
	// Assign initial value 
	t = fabs(sqrt((200*200)/( (n.x*n.x)+(n.y*n.y)+(n.z*n.z) )));
	
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++){
				data[i][j][k].i = i;
				data[i][j][k].j = j;
				data[i][j][k].k = k;
				data[i][j][k].value = fabs((n.x)*(i-1.5) + (n.y)*(-k+5)+ (n.z)*(-j+1.5) - (200*200/t)); 
				  
				//空間中點到平面的距離公式 
				//+10是為了校正在空間中的位置,以確保後面的運算 
				//	printf("[%d][%d][%d] = %lf\n", i,j,k, data[i][j][k].value);
			}

	//selection sort 完後 最大的 value -> 優先顯示 	且位於 [0][0][0]		
				
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++){
				//	printf("\n%d %d %d\n",i,j,k);
					for(int l = i*40 + j*10 + k + 1; l<160; l++){
					//	printf("%d %d %d\n",l/40,(l%40)/10,l%10);						
						if(data[i][j][k].value < data[l/40][(l%40)/10][l%10].value){
							temp = data[i][j][k];
							data[i][j][k] = data[l/40][(l%40)/10][l%10];
							data[l/40][(l%40)/10][l%10] = temp;
						}					
					}
				}

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++)
				priority[data[i][j][k].i][data[i][j][k].j][data[i][j][k].k] = i*40 + j*10 + k + 1; //1~160
				
	for(int i=0; i<8; i++)
		printf("priority %d %d %d %d\n",i%2, (i%4)/2, i/4, priority[i%2][(i%4)/2][i/4]);	
	//一 個正方體 該由何處開始顯示
	for(int i=0; i<8; i++)
		if(priority[(i%2)][(i%4)/2][i/4] < priority[one_priority%2][(one_priority%4)/2][one_priority/4])
			one_priority = i;	
	//最先被show的 
	printf("%d\n",one_priority);												
}

void Tetris :: Set_Real_Coordinare()
{
	
	
	double centerX = 0, centerY =0, centerZ = 1500*3.2*2; //長方形的中心
	//建立在空間中實際的點座標 
	for(int i=0; i<I+1; i++)
		for(int j=0; j<J+1; j++)
			for(int k=0; k<K+1; k++){
				data[i][j][k].x = centerX + (i-2)*(vec_matrix[0][0]) + (j-2)*(vec_matrix[0][2]) + (k-5)*(vec_matrix[0][1]);
				data[i][j][k].y = centerY + (i-2)*(vec_matrix[1][0]) + (j-2)*(vec_matrix[1][2]) + (k-5)*(vec_matrix[1][1]);
				data[i][j][k].z = centerZ + (i-2)*(vec_matrix[2][0]) + (j-2)*(vec_matrix[2][2]) + (k-5)*(vec_matrix[2][1]);
				//printf("0");
			}			
	//printf("\n123\n");		
}
void Tetris :: Set_Perspective_Vector()
{
	//視點在原點，投影面為螢幕設為 z = 30
	double n; //投影面 
	//先將點投影至 z =30 
	n = 100*3*2;  // n =near
	 for(int i=0; i<I+1; i++)
		for(int j=0; j<J+1; j++)
			for(int k=0; k<K+1; k++){
				data[i][j][k].x = data[i][j][k].x * n / data[i][j][k].z;
				data[i][j][k].y = data[i][j][k].y * n / data[i][j][k].z;
				data[i][j][k].z = n;
				//printf("11\n");
			}
	double v1_len, v2_len, v3_len, v4_len, v5_len, v6_len, v7_len;
	double t1, t2, t3, t;
	
	for(int i=0; i<I; i++)
		for(int j=0; j<J; j++)
			for(int k=0; k<K; k++){
				// for v1 
				//先求出其在投影面上的長度, 再依此縮減其比例 
				
				t1 = fabs(sqrt((data[i][j][k].x - data[i+1][j][k].x)*(data[i][j][k].x - data[i+1][j][k].x) + (data[i][j][k].y - data[i+1][j][k].y)*(data[i][j][k].y-data[i+1][j][k].y)));
			//	printf("v1_len = %lf\n",v1_len);
			//	printf("t1 = %lf\n",t1);
				p_vector[i][j][k].v1.x = int(-data[i][j][k].x + data[i+1][j][k].x);
				p_vector[i][j][k].v1.y = int(-data[i][j][k].y + data[i+1][j][k].y);				
				//p_vector[i][j][k].v1.z = vec_matrix[0][2]/v1_len*t1;
				
				// for v2 
				//先求出其在投影面上的長度, 再依此縮減其比例 
				t2 = fabs(sqrt((data[i][j][k].x-data[i][j+1][k].x)*(data[i][j][k].x-data[i][j+1][k].x) + (data[i][j][k].y-data[i][j+1][k].y)*(data[i][j][k].y-data[i][j+1][k].y)));
				p_vector[i][j][k].v2.x = int(-data[i][j][k].x+data[i][j+1][k].x);
				p_vector[i][j][k].v2.y = int(-data[i][j][k].y+data[i][j+1][k].y);
			//	printf("v2_len = %lf\n",v2_len);
			//	printf("t2 = %lf\n",t2);
				//for v3
				//先求出其在投影面上的長度 , 再依此縮減其比例
				t3 = fabs(sqrt((data[i][j][k].x-data[i][j][k+1].x)*(data[i][j][k].x-data[i][j][k+1].x) + (data[i][j][k].y-data[i][j][k+1].y)*(data[i][j][k].y-data[i][j][k+1].y)));
				p_vector[i][j][k].v3.x = int(-data[i][j][k].x+data[i][j][k+1].x);
				p_vector[i][j][k].v3.y = int(-data[i][j][k].y+data[i][j][k+1].y);
			//	printf("v2_len = %lf\n",v2_len);
			//	printf("t2 = %lf\n",t2);

				//for v4 = v2 + v3
				//先求出其在投影面上的長度 , 再依此縮減其比例
				t = fabs(sqrt((data[i][j][k].x - data[i][j+1][k+1].x)*(data[i][j][k].x - data[i][j+1][k+1].x) + (data[i][j][k].y - data[i][j+1][k+1].y)*(data[i][j][k].y-data[i][j+1][k+1].y)));				
				p_vector[i][j][k].v4.x = int(-data[i][j][k].x + data[i][j+1][k+1].x);
				p_vector[i][j][k].v4.y = int(-data[i][j][k].y + data[i][j+1][k+1].y);	
				
				//for v5 = v3 +v1
				//先求出其在投影面上的長度 , 再依此縮減其比例
				t = fabs(sqrt((data[i][j][k].x - data[i+1][j][k+1].x)*(data[i][j][k].x - data[i+1][j][k+1].x) + (data[i][j][k].y - data[i+1][j][k+1].y)*(data[i][j][k].y-data[i+1][j][k+1].y)));				
				p_vector[i][j][k].v5.x = int(-data[i][j][k].x + data[i+1][j][k+1].x);
				p_vector[i][j][k].v5.y = int(-data[i][j][k].y + data[i+1][j][k+1].y);
				
				//for v6 = v2 + v1
				//先求出其在投影面上的長度 , 再依此縮減其比例
				t = fabs(sqrt((data[i][j][k].x - data[i+1][j+1][k].x)*(data[i][j][k].x - data[i+1][j+1][k].x) + (data[i][j][k].y - data[i+1][j+1][k].y)*(data[i][j][k].y-data[i+1][j+1][k].y)));				
				p_vector[i][j][k].v6.x = int(-data[i][j][k].x + data[i+1][j+1][k].x);
				p_vector[i][j][k].v6.y = int(-data[i][j][k].y + data[i+1][j+1][k].y);
				
				//for v7 = v3 + v2 + v1
				//先求出其在投影面上的長度 , 再依此縮減其比例
				t = fabs(sqrt((data[i][j][k].x - data[i+1][j+1][k+1].x)*(data[i][j][k].x - data[i+1][j+1][k+1].x) + (data[i][j][k].y - data[i+1][j+1][k+1].y)*(data[i][j][k].y-data[i+1][j+1][k+1].y)));				
				p_vector[i][j][k].v7.x = int(-data[i][j][k].x + data[i+1][j+1][k+1].x);
				p_vector[i][j][k].v7.y = int(-data[i][j][k].y + data[i+1][j+1][k+1].y);
			
			}
	
/*	v1_len = fabs(sqrt(vec_matrix[0][0]*vec_matrix[0][0] + vec_matrix[1][0]*vec_matrix[1][0] + vec_matrix[2][0]*vec_matrix[2][0]));
	v2_len = fabs(sqrt(vec_matrix[0][2]*vec_matrix[0][2] + vec_matrix[1][2]*vec_matrix[1][2] + vec_matrix[2][2]*vec_matrix[2][2]));
	v3_len = fabs(sqrt(vec_matrix[0][1]*vec_matrix[0][1] + vec_matrix[1][1]*vec_matrix[1][1] + vec_matrix[2][1]*vec_matrix[2][1]));
	v4_len = fabs(sqrt(v2_len*v2_len + v3_len*v3_len));
	v5_len = fabs(sqrt(v1_len*v1_len + v3_len*v3_len));
	v6_len = fabs(sqrt(v1_len*v1_len + v2_len*v2_len));
	v7_len = fabs(sqrt(v1_len*v1_len + v2_len*v2_len + v3_len*v3_len));
	//每個點都有自己對應的 v1' v2' v3'，　求出其縮放比例 
	for(int i=0; i<I; i++)
		for(int j=0; j<J; j++)
			for(int k=0; k<K; k++){
				// for v1 
				//先求出其在投影面上的長度, 再依此縮減其比例 
				
				t1 = fabs(sqrt((data[i][j][k].x - data[i+1][j][k].x)*(data[i][j][k].x - data[i+1][j][k].x) + (data[i][j][k].y - data[i+1][j][k].y)*(data[i][j][k].y-data[i+1][j][k].y)));
			//	printf("v1_len = %lf\n",v1_len);
			//	printf("t1 = %lf\n",t1);
				p_vector[i][j][k].v1.x = int(vec_matrix[0][0]/v1_len*t1); 
				p_vector[i][j][k].v1.y = int(vec_matrix[1][0]/v1_len*t1); 				
				//p_vector[i][j][k].v1.z = vec_matrix[0][2]/v1_len*t1;
				
				// for v2 
				//先求出其在投影面上的長度, 再依此縮減其比例 
				t2 = fabs(sqrt((data[i][j][k].x-data[i][j+1][k].x)*(data[i][j][k].x-data[i][j+1][k].x) + (data[i][j][k].y-data[i][j+1][k].y)*(data[i][j][k].y-data[i][j+1][k].y)));
				p_vector[i][j][k].v2.x = int(vec_matrix[0][2]/v2_len*t2); 
				p_vector[i][j][k].v2.y = int(vec_matrix[1][2]/v2_len*t2);	
			//	printf("v2_len = %lf\n",v2_len);
			//	printf("t2 = %lf\n",t2);
				//for v3
				//先求出其在投影面上的長度 , 再依此縮減其比例
				t3 = fabs(sqrt((data[i][j][k].x-data[i][j][k+1].x)*(data[i][j][k].x-data[i][j][k+1].x) + (data[i][j][k].y-data[i][j][k+1].y)*(data[i][j][k].y-data[i][j][k+1].y)));
				p_vector[i][j][k].v3.x = int(vec_matrix[0][3]/v3_len*t3); 
				p_vector[i][j][k].v3.y = int(vec_matrix[1][3]/v3_len*t3);
			//	printf("v2_len = %lf\n",v2_len);
			//	printf("t2 = %lf\n",t2);

				//for v4 = v2 + v3
				//先求出其在投影面上的長度 , 再依此縮減其比例
				t = fabs(sqrt((data[i][j][k].x - data[i][j+1][k+1].x)*(data[i][j][k].x - data[i][j+1][k+1].x) + (data[i][j][k].y - data[i][j+1][k+1].y)*(data[i][j][k].y-data[i][j+1][k+1].y)));				
				p_vector[i][j][k].v4.x = int((vec_matrix[0][1]+vec_matrix[0][2])/v4_len*t); 
				p_vector[i][j][k].v4.y = int((vec_matrix[1][1]+vec_matrix[1][2])/v4_len*t); 	
				
				//for v5 = v3 +v1
				//先求出其在投影面上的長度 , 再依此縮減其比例
				t = fabs(sqrt((data[i][j][k].x - data[i+1][j][k+1].x)*(data[i][j][k].x - data[i+1][j][k+1].x) + (data[i][j][k].y - data[i+1][j][k+1].y)*(data[i][j][k].y-data[i+1][j][k+1].y)));				
				p_vector[i][j][k].v5.x = int((vec_matrix[0][1]+vec_matrix[0][0])/v5_len*t); 
				p_vector[i][j][k].v5.y = int((vec_matrix[1][1]+vec_matrix[1][0])/v5_len*t); 
				
				//for v6 = v2 + v1
				//先求出其在投影面上的長度 , 再依此縮減其比例
				t = fabs(sqrt((data[i][j][k].x - data[i+1][j+1][k].x)*(data[i][j][k].x - data[i+1][j+1][k].x) + (data[i][j][k].y - data[i+1][j+1][k].y)*(data[i][j][k].y-data[i+1][j+1][k].y)));				
				p_vector[i][j][k].v6.x = int((vec_matrix[0][2]+vec_matrix[0][0])/v6_len*t); 
				p_vector[i][j][k].v6.y = int((vec_matrix[1][2]+vec_matrix[1][0])/v6_len*t); 
				
				//for v7 = v3 + v2 + v1
				//先求出其在投影面上的長度 , 再依此縮減其比例
				t = fabs(sqrt((data[i][j][k].x - data[i+1][j+1][k+1].x)*(data[i][j][k].x - data[i+1][j+1][k+1].x) + (data[i][j][k].y - data[i+1][j+1][k+1].y)*(data[i][j][k].y-data[i+1][j+1][k+1].y)));				
				p_vector[i][j][k].v7.x = int((vec_matrix[0][2]+vec_matrix[0][0]+vec_matrix[0][1])/v7_len*t); 
				p_vector[i][j][k].v7.y = int((vec_matrix[1][2]+vec_matrix[1][0]+vec_matrix[1][1])/v7_len*t); 
			
			}	*/
} 
void Tetris :: Set_XY(int *a, int *b, int px, int py, int pz)
{
	int x = center.x, y = center.y, dx = -2+px, dy = -2+py, dz = -5+pz, t1, t2, t3, i, j ,k;
	t1 = t2 = t3 =0;
	for( i=1; i<=2; i++){
			x = x -  p_vector[2-i][2-i][5-i].v7.x;
			y = y -  p_vector[2-i][2-i][5-i].v7.y;
			
		}
	for( i=1; i<=2; i++){
			x = x -  p_vector[0][0][3-i].v1.x;
			y = y -  p_vector[0][0][3-i].v1.y;
			
	}
	
	for( i=0; i<px; i++){
			x = x + p_vector[i][0][0].v1.x;
			y = y + p_vector[i][0][0].v1.y;			
			t1 = i;
		}	
	for( i=0; i<py; i++){
			x = x + p_vector[t1][i][0].v2.x;
			y = y + p_vector[t1][i][0].v2.y;			
			t2 = i;
		}	
	for( i=0; i<pz; i++){
			x = x + p_vector[t1][t2][0].v3.x;
			y = y + p_vector[t1][t2][0].v3.y;			
			t3 = i;
		}
		
/*	//先沿著v1 
	if(dx<0){
		
		for( i=1; i<=abs(dx); i++){
			x = x -  p_vector[2-i][2][5].v1.x;
			y = y -  p_vector[2-i][2][5].v1.y;
			t1 = -i;
		}
	}
	else
		for( i=0; i<abs(dx); i++){
			x = x + p_vector[2+i][2][5].v1.x;
			y = y + p_vector[2+i][2][5].v1.y;			
			t1 = i;
		}	
		
	//再沿著v2


	if(dy<0)
		for(j=1; j<=abs(dy); j++){
			x = x - p_vector[2+t1][2-j][5].v2.x;
			y = y - p_vector[2+t1][2-j][5].v2.y;		
			t2 = -j;
		}	 
	else
		for(j=0; j<abs(dy); j++){
			x = x + p_vector[2+t1][2+j][5].v2.x;
			y = y + p_vector[2+t1][2+j][5].v2.y;		
			t2 = j;	
		}	
		
	//最後沿著v3

	
	if(dz<0)
		for(k=1; k<=abs(dz); k++){
			x = x - p_vector[2+t1][2+t2][5-k].v3.x;
			y = y - p_vector[2+t1][2+t2][5-k].v3.y;
		\
		}
	else
		for(k=0; k<abs(dy); k++){
			x = x + p_vector[2+t1][2+t2][5+k].v3.x;
			y = y + p_vector[2+t1][2+t2][5+k].v3.y;			
		}	
	*/
	(*a) = x;
	(*b) = y;
} 
void Tetris :: ShowLine3D(int px, int py, int pz)
{
	int x, y;
	Set_XY(&x, &y, px, py, pz);
	v1 = p_vector[px][py][pz].v1;
	v2 = p_vector[px][py][pz].v2;
	v3 = p_vector[px][py][pz].v3;
	v4 = p_vector[px][py][pz].v4;
	v5 = p_vector[px][py][pz].v5;
	v6 = p_vector[px][py][pz].v6;
	v7 = p_vector[px][py][pz].v7; 
//	printf("%d %d\n",x,y);
	line(x, y, x+v1.x, y+v1.y);
	line(x, y, x+v2.x, y+v2.y);
	line(x+v1.x, y+v1.y, x+v6.x, y+v6.y);
	line(x+v2.x, y+v2.y, x+v6.x, y+v6.y);
	
	line(x, y, x+v1.x, y+v1.y);
	line(x, y, x+v3.x, y+v3.y);
	line(x+v1.x, y+v1.y, x+v5.x, y+v5.y);
	line(x+v3.x, y+v3.y, x+v5.x, y+v5.y);
	
	line(x, y, x+v2.x, y+v2.y);
	line(x, y, x+v3.x, y+v3.y);
	line(x+v2.x, y+v2.y, x+v4.x, y+v4.y);
	line(x+v3.x, y+v3.y, x+v4.x, y+v4.y);
	
	line(x+v3.x, y+v3.y, x+v5.x, y+v5.y);
	line(x+v3.x, y+v3.y, x+v4.x, y+v4.y);
	line(x+v7.x, y+v7.y, x+v4.x, y+v4.y);
	line(x+v7.x, y+v7.y, x+v5.x, y+v5.y);
	
	line(x+v7.x, y+v7.y, x+v4.x, y+v4.y);
	line(x+v7.x, y+v7.y, x+v6.x, y+v6.y);
	line(x+v2.x, y+v2.y, x+v4.x, y+v4.y);
	line(x+v2.x, y+v2.y, x+v6.x, y+v6.y);
	
	line(x+v7.x, y+v7.y, x+v5.x, y+v5.y);
	line(x+v7.x, y+v7.y, x+v6.x, y+v6.y);
	line(x+v1.x, y+v1.y, x+v5.x, y+v5.y);
	line(x+v1.x, y+v1.y, x+v6.x, y+v6.y);
} 
void Tetris :: ShowParallelogram3D(int px, int py, int pz) 
{
	int x, y;
	Set_XY(&x, &y, px, py, pz); 
	v1 = p_vector[px][py][pz].v1;
	v2 = p_vector[px][py][pz].v2;
	v3 = p_vector[px][py][pz].v3;
	v4 = p_vector[px][py][pz].v4;
	v5 = p_vector[px][py][pz].v5;
	v6 = p_vector[px][py][pz].v6;
	v7 = p_vector[px][py][pz].v7;
	
	int parallelogram1[10] = {x+v3.x, y+v3.y, x+v5.x, y+v5.y, x+v7.x, y+v7.y, x+v4.x, y+v4.y, x+v3.x, y+v3.y};
	int parallelogram2[10] = {x+v2.x, y+v2.y, x+v6.x, y+v6.y, x+v7.x, y+v7.y, x+v4.x, y+v4.y, x+v2.x, y+v2.y};
	int parallelogram3[10] = {x+v1.x, y+v1.y, x+v5.x, y+v5.y, x+v7.x, y+v7.y, x+v6.x, y+v6.y, x+v1.x, y+v1.y};
	int parallelogram4[10] = {x, y, x+v2.x, y+v2.y, x+v4.x, y+v4.y, x+v3.x, y+v3.y, x, y};
	int parallelogram5[10] = {x, y, x+v1.x, y+v1.y, x+v5.x, y+v5.y, x+v3.x, y+v3.y, x, y};
	int parallelogram6[10] = {x, y, x+v1.x, y+v1.y, x+v6.x, y+v6.y, x+v2.x, y+v2.y, x, y};	
	setfillstyle(INTERLEAVE_FILL, place[px][py][pz]);
	
	printf("v1.x = %d, v1.y = %d\n",v1.x, v1.y);
	printf("v2.x = %d, v2.y = %d\n",v2.x, v2.y);
	printf("v3.x = %d, v3.y = %d\n",v3.x, v3.y);
	printf("v4.x = %d, v4.y = %d\n",v4.x, v4.y);
	printf("v5.x = %d, v5.y = %d\n",v5.x, v5.y);
	printf("v6.x = %d, v6.y = %d\n",v6.x, v6.y);
	printf("v7.x = %d, v7.y = %d\n",v7.x, v7.y);
	switch(one_priority){ // 0 1 4 5 2 3 6 7
		case 0:
			fillpoly(5, parallelogram1);  //前一個參數放5 ,因為為四邊形且需要繞一圈 所以為五個點 
			fillpoly(5, parallelogram2);
			fillpoly(5, parallelogram3);
			break;
		case 1:
			fillpoly(5, parallelogram1);
			fillpoly(5, parallelogram2);
			fillpoly(5, parallelogram4);
			break;	
		case 2:
			fillpoly(5, parallelogram1);
			fillpoly(5, parallelogram3);
			fillpoly(5, parallelogram5);
			break;	
		case 3:
			fillpoly(5, parallelogram1);
			fillpoly(5, parallelogram4);
			fillpoly(5, parallelogram5);
			break;	
		case 4:
			fillpoly(5, parallelogram2);
			fillpoly(5, parallelogram3);
			fillpoly(5, parallelogram6);
			break;	
		case 5:
			fillpoly(5, parallelogram2);
			fillpoly(5, parallelogram4);
			fillpoly(5, parallelogram6);
			break;
		case 6:
			fillpoly(5, parallelogram3);
			fillpoly(5, parallelogram5);
			fillpoly(5, parallelogram6);
			break;
		case 7:
			fillpoly(5, parallelogram4);
			fillpoly(5, parallelogram5);
			fillpoly(5, parallelogram6);
			break;		
	}
	
 /* fillpoly(5, parallelogram1);
	fillpoly(5, parallelogram2);
	fillpoly(5, parallelogram3);
	fillpoly(5, parallelogram4);
	fillpoly(5, parallelogram5);
	fillpoly(5, parallelogram6);*/
}
int main(void){
	double a1, a2;
	int x, y, z, color = 1, mx, my, n=1;
	Tetris data1; 
	initwindow(1200,800);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	scanf("%lf %lf", &a1, &a2);
	data1.SetPlace(2,2,5,9);
/*	data1.SetPlace(0,0,0,1);
	data1.SetPlace(0,n,0,2);
	data1.SetPlace(0,0,3*n,3);
	data1.SetPlace(0,n,3*n,4);
	data1.SetPlace(n,0,0,5);
	data1.SetPlace(n,n,0,6);
	data1.SetPlace(n,0,n*3,7);
	data1.SetPlace(n,n,n*3,8);		*/					
	while(1){
		
	//	a2 += 5 ;
	//	a1 += 5 ;
	//	scanf("%d",&a2);
	/*	if(a1>=90 || a1<=-90)
			a1= a1/fabs(a1)*90;
		if(a2>=90 || a2<= -90)
			a2= a2/fabs(a2)*90;*/
		if(kbhit()){
			if(GetAsyncKeyState(W_KEY)!=0) a2+=5;
			if(GetAsyncKeyState(S_KEY)!=0) a2-=5;
			if(GetAsyncKeyState(A_KEY)!=0) a1+=5;
			if(GetAsyncKeyState(D_KEY)!=0) a1-=5;
			
		}
		if(a1>=90 || a1<=-90)
			a1= a1/fabs(a1)*90;
		if(a2>=90 || a2<= -90)
			a2= a2/fabs(a2)*90;
	//	scanf("%d %d %d",&x,&y,&z);	 
	//	printf("a1 = %d\n",a1);
	//	data1.SetPlace(x,y,z,1);
		data1.SetAngle(a1,a2);
		data1.SetVector();
		
		data1.Set_N_Vector();
		data1.SetPriority();
	//	data1.Set_Real_Coordinare();
	//	data1.Set_Perspective_Vector();
		data1.ShowTetris();
	//	data1.SetPriority();
	//	scanf("%d ", &x);
		_sleep(50);
	//	scanf("%lf %lf", &a1, &a2);
	}
		
	return 0;
}
