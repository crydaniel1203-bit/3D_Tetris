#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <synchapi.h>
#include <stdlib.h>
#define W_KEY 0x57
#define A_KEY 0x41
#define S_KEY 0x53
#define D_KEY 0x44
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
class Tetris
{
	int  place[4][4][10];  // if Tetris have cube
	int priority[4][4][10], one_priority; //*
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
	N_Direction n;  //*
		
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
	 void SetAngle(double, double); //之後由滑鼠拖曳更改
	 void Show(const double data[3][3])
		{
			for(int i=0; i<3; i++){
				for(int j=0; j<3; j++)
					printf("%7.2lf ",data[i][j]);
				printf("\n");	
			}
			printf("\n");
		}  
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
				place[i][j][k] = 0;
				priority[i][j][k] = count;
				count++;
			}
				
				
	center.x = 500;
	center.y = 400;
	
	for(int i=0; i<3; i++)
		for(int j=0 ;j<3; j++)
			vec_matrix[i][j] = 0;
	vec_matrix[0][0] = 50;
	vec_matrix[1][1] = vec_matrix[2][2] = -50;
	
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
	int len = 50;  //here can change cube's length 
	for(int i=0; i<3; i++)
		for(int j=0 ;j<3; j++)
			vec_matrix[i][j] = 0;
	vec_matrix[0][0] = len;
		vec_matrix[1][1] = vec_matrix[2][2] = -len; 
}
void Tetris :: Set_N_Vector(){
	double result[3];
	n.x =  0;
	n.y =  0;
	n.z =  1;
	
	//Circle
	result[0] = (n.x)*cos(-alpha * M_PI / 180) + (n.z) * -sin(-alpha * M_PI / 180);
	result[1] = (n.y)*1;
	result[2] = (n.x)*sin(-alpha * M_PI / 180) + (n.z) * cos(-alpha * M_PI / 180);
	n.x = result[0], n.y = result[1], n.z = result[2];
	
	//Dump	
	result[0] = (n.x)*1;
	result[1] = (n.y)*cos(-beta * M_PI / 180) + (n.z) * -sin(-beta * M_PI / 180);
	result[2] = (n.y)*sin(-beta * M_PI / 180) + (n.z) * cos(-beta * M_PI / 180);
	n.x = result[0], n.y = result[1], n.z = result[2];
	printf("x = %lf, y= %lf, z = %lf\n", n.x, n.y, n.z);
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
	n.x =  vec_matrix[0][2]/70;
	n.y =  vec_matrix[1][2]/70;
	n.z = -vec_matrix[2][2]/70;
	printf("nx = %lf, ny= %lf, nz = %lf\n", n.x, n.y, n.z);
	printf("v1_x = %lf, v1_ y = %lf, v1_z =%lf\n", vec_matrix[0][0]/70, vec_matrix[1][0]/70, vec_matrix[2][0]/70);
	printf("v2_x = %lf, v2_ y = %lf, v2_z =%lf\n", vec_matrix[0][2]/70, vec_matrix[1][2]/70, vec_matrix[2][2]/70);
	printf("v3_x = %lf, v3_ y = %lf, v3_z =%lf\n", vec_matrix[0][1]/70, vec_matrix[1][1]/70, vec_matrix[2][1]/70);
	printf("%lf %lf\n",alpha,beta);
	Mul_matrix(vec_matrix, p_matrix); //step.3 project
//	Show(vec_matrix);
	v1.x = (int)vec_matrix[0][0];
	v1.y = (int)vec_matrix[1][0];
	
	v2.x = (int)vec_matrix[0][2];
	v2.y = (int)vec_matrix[1][2];
	
	v3.x = (int)vec_matrix[0][1];
	v3.y = (int)vec_matrix[1][1];
//	Set_N_Vector();	
/*	n.x = - v2.x;
	n.y =   v2.y;
	n.z = -(int)vec_matrix[2][2];*/
	 
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
					if(place[i][j][k] && (priority[i][j][k]==order))
						 ShowParallelogram(i,j,k);
						 
/*	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++)  //*v3.y
					ShowLine(i,j,k);  */				 
	 			
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
	
	/*switch(one_priority){ // 0 1 4 5 2 3 6 7
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
		case 4:
			fillpoly(5, parallelogram1);
			fillpoly(5, parallelogram3);
			fillpoly(5, parallelogram5);
			break;	
		case 3:
			fillpoly(5, parallelogram1);
			fillpoly(5, parallelogram4);
			fillpoly(5, parallelogram5);
			break;	
		case 5:
			fillpoly(5, parallelogram2);
			fillpoly(5, parallelogram3);
			fillpoly(5, parallelogram6);
			break;	
		case 2:
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
	}*/ 
	
   fillpoly(5, parallelogram1);
	fillpoly(5, parallelogram2);
	fillpoly(5, parallelogram3);
}
void Tetris :: SetPlace(int x, int y, int z, int color){
	place[x][y][z] = color;
} 
void Tetris :: SetPriority() 	//處理所有的優先顯示問題  //* 
{  
	data_for_Priority data[4][4][10], temp;
	// Assign initial value 
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++){
				data[i][j][k].i = i;
				data[i][j][k].j = j;
				data[i][j][k].k = k;
				data[i][j][k].value = (n.x)*i + (n.y)*(-k)+ (n.z)*(-j); 
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
			for(int k=0; k<10; k++){
				priority[data[i][j][k].i][data[i][j][k].j][data[i][j][k].k] = i*40 + j*10 + k + 1; 
			}	
		
	//一 個正方體 該由何處開始顯示
	for(int i=0; i<8; i++)
		if(priority[3*i%2][3*(i%4)/2][3*i/4] < priority[3*one_priority%2][3*(one_priority%4)/2][3*one_priority/4])
			one_priority = i;	
	printf("%d\n",one_priority);												
}
int main(void){
	double a1, a2;
	int x, y, z, color = 1, mx, my;
	Tetris data1; 
	initwindow(1200,800);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	scanf("%lf %lf", &a1, &a2);
//	data1.SetAngle(25,45);
	data1.SetPlace(2,2,5,9);
//	data1.SetPlace(1,2,1,1);
//	data1.SetPlace(1,3,1,1);
/*	data1.SetPlace(0,0,0,1);
	data1.SetPlace(0,3,0,2);
	data1.SetPlace(0,0,9,3);
	data1.SetPlace(0,3,9,4);
	data1.SetPlace(3,0,0,5);
	data1.SetPlace(3,3,0,6);
	data1.SetPlace(3,0,9,7);
	data1.SetPlace(3,3,9,8);	*/						
	while(1){
		
	//	a2 += 5 ;
	//	a1 += 5 ;
	//	scanf("%d",&a2);
		if(a1>=360 || a1<=-360)
			a1=0;
		if(a2>=360 || a2<= -360)
			a2=0;
		if(kbhit()){
			if(GetAsyncKeyState(W_KEY)!=0) a2+=5;
			if(GetAsyncKeyState(S_KEY)!=0) a2-=5;
			if(GetAsyncKeyState(A_KEY)!=0) a1+=5;
			if(GetAsyncKeyState(D_KEY)!=0) a1-=5;
			
		}
	//	scanf("%d %d %d",&x,&y,&z);	 
	//	printf("a1 = %d\n",a1);
	//	data1.SetPlace(x,y,z,1);
		data1.SetAngle(a1,a2);
		data1.SetVector();
		data1.SetPriority();
		data1.ShowTetris();
	//	data1.SetPriority();
	//	scanf("%d ", &x);
		_sleep(50);

	}
		
	return 0;
}
