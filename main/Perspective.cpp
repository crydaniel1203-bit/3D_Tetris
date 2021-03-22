#include <stdio.h>
#define I 4
#define J 4
#define K 10
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
};
void Tetris :: Set_Real_Coordinare()
{
	
	
	int centerX = 0, centerY =0, centerZ = 200; //長方形的中心
	//建立在空間中實際的點座標 
	for(int i=0; i<I+1; i++)
		for(int j=0; j<J+1; j++)
			for(int k=0; k<K+1; k++){
				data[i][j][k].x = centerX + (i-2)*(vec_matrix[0][0]) + (j-2)*(vec_matrix[0][2]) + (k-5)*(vec_matrix[0][1]);
				data[i][j][k].y = centerY + (i-2)*(vec_matrix[1][0]) + (j-2)*(vec_matrix[1][2]) + (k-5)*(vec_matrix[1][1]);
				data[i][j][k].z = centerZ + (i-2)*(vec_matrix[2][0]) + (j-2)*(vec_matrix[2][2]) + (k-5)*(vec_matrix[2][1]);
			}			
			
}
void Tetris :: Set_Perspective_Vector()
{
	//視點在原點，投影面為螢幕設為 z = 30
	double near = 30; //投影面 
	//先將點投影至 z =30 
	 for(int i=0; i<I+1; i++)
		for(int j=0; j<J+1; j++)
			for(int k=0; k<K+1; k++){
				data[i][j][k].x = data[i][j][k].x * near / data[i][j][k].z;
				data[i][j][k].y = data[i][j][k].y * near / data[i][j][k].z;
				data[i][j][k].z = near;
			}
	double v1_len, v2_len, v3_len, t1, t2, t3;
	
	v1_len = sqrt(vec_matrix[0][0]*vec_matrix[0][0] + vec_matrix[1][0]*vec_matrix[1][0] + vec_matrix[2][0]*vec_matrix[2][0]);
	v3_len = sqrt(vec_matrix[0][2]*vec_matrix[0][2] + vec_matrix[1][2]*vec_matrix[1][2] + vec_matrix[2][2]*vec_matrix[2][2]);
	v2_len = sqrt(vec_matrix[0][1]*vec_matrix[0][1] + vec_matrix[1][1]*vec_matrix[1][1] + vec_matrix[2][1]*vec_matrix[2][1]);
	//每個點都有自己對應的 v1' v2' v3'，　求出其縮放比例 
	for(int i=0; i<I; i++)
		for(int j=0; j<J; j++)
			for(int k=0; k<K; k++){
				// for v1 
				//先求出其在投影面上的長度 
				t1 = sqrt((data[i][j][k].x-data[i+1][j][k].x)*(data[i][j][k].x-data[i+1][j][k].x) + (data[i][j][k].y-data[i+1][j][k].y)*(data[i][j][k].y-data[i+1][j][k]).y);
				p_vector[i][j][k].v1.x = int(vec_matrix[0][0]/v1_len*t1); 
				p_vector[i][j][k].v1.y = int(vec_matrix[0][1]/v1_len*t1); 				
				//p_vector[i][j][k].v1.z = vec_matrix[0][2]/v1_len*t1;
				
				// for v2 
				//先求出其在投影面上的長度 
				t2 = sqrt((data[i][j][k].x-data[i][j+1][k].x)*(data[i][j][k].x-data[i][j+1][k].x) + (data[i][j][k].y-data[i][j+1][k].y)*(data[i][j][k].y-data[i][j+1][k]).y);
				p_vector[i][j][k].v2.x = int(vec_matrix[2][0]/v2_len*t2); 
				p_vector[i][j][k].v2.y = int(vec_matrix[2][1]/v2_len*t2);	
				
				//先求出其在投影面上的長度 
				t3 = sqrt((data[i][j][k].x-data[i][j][k+1].x)*(data[i][j][k].x-data[i][j][k+1].x) + (data[i][j][k].y-data[i][j][k+1].y)*(data[i][j][k].y-data[i][j][k+1]).y);
				p_vector[i][j][k].v3.x = int(vec_matrix[1][0]/v3_len*t3); 
				p_vector[i][j][k].v3.y = int(vec_matrix[1][1]/v3_len*t3);		 
			}		
} 
void Tetrix :: Set_XY(int *a, int *b, int px, int, py, int pz)
{
	int x = center.x, y = center.y, dx = px-2, dy = py-2, dz = pz-5;
	//先沿著v1 
	for(int i=1; i<=abs(dx); i++){
		x = x + (dx/abs(dx)) * p_vector[2+(dx/abs(dx))*i][2][5].v1.x;
		y = y + (dx/abs(dx)) * p_vector[2+(dx/abs(dx))*i][2][5].v1.y;
	}	
	//再沿著v2
	for(int i=1; i<=abs(dy); i++){
		x = x + (dy/abs(dy)) * p_vector[2][2+(dy/abs(dy))*i][5].v2.x;
		y = y + (dy/abs(dy)) * p_vector[2][2+(dy/abs(dy))*i][5].v2.y;
	}	 
	//最後沿著v3
	for(int i=1; i<=abs(dz); i++){
		x = x + (dz/abs(dz)) * p_vector[2][2][5+(dz/abs(dz))*i].v3.x;
		y = y + (dz/abs(dz)) * p_vector[2][2][5+(dz/abs(dz))*i].v3.y;
	}	
	(*a) = x;
	(*b) = y;
}  
void Tetris :: ShowParallelogram3D(int px, int py, int pz) const
{
	int x, y
	Set_XY(&x, &y, px, py, pz); 
	v1 = p_vector[px][py][pz].v1;
	v2 = p_vector[px][py][pz].v2;
	v3 = p_vector[px][py][pz].v3;
	
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
 
