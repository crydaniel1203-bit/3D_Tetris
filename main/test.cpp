#include <stdio.h>
int main(void)
{
	/*for(int i=0; i<1; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<10; k++){
				//	printf("\n%d %d %d\n",i,j,k);
					for(int l = i*40 + j*10 + k + 1; l<160; l++){
						printf("%d %d %d %d\n",i,j,k,l);										
					}
					printf("\n");
				}*/
	for(int i=0; i<8; i++)
		printf("%d %d %d\n", 3*(i%2),3*(i%4)/2, 3*i/4);
		//if(priority[3*(i%2)][3*(i%4)/2][3*i/4] < priority[3*one_priority%2][3*(one_priority%4)/2][3*one_priority/4])			
	return 0;
} 
