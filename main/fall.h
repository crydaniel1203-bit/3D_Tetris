#define W_KEY 0x57
#define A_KEY 0x41
#define S_KEY 0x53
#define D_KEY 0x44
using namespace std;

void Tetris::RunGame()
{
	double a1 = 25, a2 = 45;
	int time=0;
	while(1)
	{
	//	data1.SetPlace(x,y,z,color);
		if(kbhit()){
			if(GetAsyncKeyState(W_KEY)!=0) a2+=10;
			if(GetAsyncKeyState(S_KEY)!=0) a2-=10;
			if(GetAsyncKeyState(A_KEY)!=0) a1-=10;
			if(GetAsyncKeyState(D_KEY)!=0) a1+=10;
		}
		if(a1>=90 || a1<=-90)
			a1= a1/fabs(a1)*90;
		if(a2>=90 || a2<= -90)
			a2= a2/fabs(a2)*90;
		SetAngle(a1,a2);
		SetVector();
		Set_N_Vector();
		SetPriority();
		ShowTetris();
		
	//	data1.ShowTetris();
		if(!(time%6)){  
		
			if(rand()&1)
				GenBrick(1,1); 
			else
				GenBrick(0,1);
		} 
		Fall();
		//ezfall();
		ShowTetris();
		time++;
		Sleep(600);
		scanf("%lf",&a1);
	}
}
void Tetris::ezfall()
{
	//easy fall
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<4;j++)
		{
			for(int k=0;k<4;k++)
			{
				if(place[k][j][i]&&i==0);
				else
				{
					place[k][j][i]=place[k][j][i+1];
				}
			}
		}
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			place[i][j][9]=0;
		}
	}

//test code
/*		for(int i=9;i>=0;i--)
		{
			for(int j=0;j<4;j++)
			{
				for(int k=0;k<4;k++)
				{
					cout<<place[k][j][i];
				}
			}
			cout<<endl;
		}
		cout<<endl;
*/
		//getch();
}
void Tetris::Fall()
{
	int t;
	for(int i=0;i<br.size();i++)
	{
		if(br[i].org.z==0||place[br[i].org.x][br[i].org.y][br[i].org.z-1])
		{
			br[i].fall=false;
		}
		if(br[i].fall)
		{
			for(int j=0;j<br[i].n;j++)
			{
				t=*(br[i].p[j]);
				*(br[i].p[j])=0;
			}
			(br[i].org.z)--;
			for(int j=0;j<br[i].n;j++)
			{
				br[i].p[j]=&(place[br[i].org.x+br[i].vx[j]][br[i].org.y+br[i].vy[j]][br[i].org.z+br[i].vz[j]]);
				*(br[i].p[j])=t;
			}
		}
	}
}
void Tetris::GenBrick(int type,int color)
{
	int pos=br.size();
	br.push_back(brtype[type]);
	br[pos].fall=true;
	br[pos].org.x=rand()%2;
	br[pos].org.y=rand()%2;
	br[pos].org.z=5;
	for(int i=0;i<br[pos].n;i++)
	{
		br[pos].p[i]=&(place[br[pos].org.x+br[pos].vx[i]][br[pos].org.y+br[pos].vy[i]][br[pos].org.z+br[pos].vz[i]]);
		*(br[pos].p[i])=color;
	}
}
