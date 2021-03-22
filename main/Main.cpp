#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <synchapi.h>
#include <stdlib.h>
#include <time.h>
#include "Class.h"
#include "Show.h"
#include "fall.h"
using namespace std;
int main()
{
	Tetris data1;
	initwindow(1200,800);
	srand(time(NULL));
	data1.RunGame();
	return 0;
}
