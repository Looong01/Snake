//debugged by dzq at 13:11,10/02/2020
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>       //光标设置的API
#include <time.h>          //食物随机 
#include <conio.h>         //按键监控
////////////////////////////////////////////////////
//             辅助宏定义
#define MAPHEIGHT 26       //窗口的属性
#define MAPWIDTH  60
#define SNAKESIZE 1000       //蛇的最大节数


//数据设计
////////////////////////////////////////////////////
//             食物的结构体
struct
{
	//如何去定位：坐标
	int x;
	int y;

}food;
////////////////////////////////////////////////////
//             蛇的结构体
struct
{
	int x[SNAKESIZE];
	int y[SNAKESIZE];
	int len;        //蛇的长度
	int speed;      //蛇的移动速度
}snake;

////////////////////////////////////////////////////
//             全局变量
int key = 'w';      //初始化移动方向
int key2 = 0;
int key4 = 0;
int changeFlag = 0; //蛇的变化标记
int points = 0;     //得分 
int speed = 100;      //蛇的速度（每隔多少毫秒移动一格） 
int len = 3;          //初始长度 
////////////////////////////////////////////////////
//1.画地图
void drawMap();
//2.食物的产生
void createFood();
//3.按键操作
void keyDown();
//4.蛇的状态：判断是否结束游戏
int snakeStatus();
//5.辅助函数：光标移动
void gotoxy(int x, int y);           //TC 是有的，现在已经淘汰了，要自己实现

int main()
{
	system("mode con cols=120 lines=30");
r:
	char c = 0;//判断是否重新开始的变量 
	changeFlag = 0; key = 'w'; points = 0;//重置参数 
	gotoxy(63, 5);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 6);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 7);
	printf("\033[47;31;5m         Press W、A、S、D to control yourself         \033[0m");
	gotoxy(63, 8);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 9);
	printf("\033[47;31;5m         Press SPACE to pause and to continue         \033[0m");
	gotoxy(63, 10);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 11);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 12);
	printf("\033[47;31;5m   Keep your keyboard in English or in Capital Lock   \033[0m");
	gotoxy(63, 13);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 14);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 15); 
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 16);
	printf("\033[47;31;5m                       Good Luck!                     \033[0m");
	gotoxy(63, 17);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 18);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(100, 22);
	printf("——Loong");
	drawMap();
	while (1)
	{
		createFood();
		Sleep(snake.speed);
		keyDown();
		if (!snakeStatus())
		{
			break;
		}
	}
	system("cls");

	gotoxy(47, 10);
	printf("\033[47;31;5m                        \033[0m");
	gotoxy(47, 11);
	printf("\033[47;31;5m       Game  Over       \033[0m");
	gotoxy(47, 12);
	printf("\033[47;31;5m                        \033[0m");
	gotoxy(47, 13);
	printf("\033[47;31;5m            &           \033[0m");
	gotoxy(47, 14);
	printf("\033[47;31;5m                        \033[0m");

	gotoxy(47, 15);
	printf("\033[47;31;5m     Your points: \033[0m");
	printf("\033[47;31;5m%-6d\033[0m", points);
	gotoxy(47, 16);
	printf("\033[47;31;5m                        \033[0m");
	gotoxy(46, 24);
	printf("【Press SPACE to continue】");
	gotoxy(1, 1);

    j:
	key4 = _getch();
	fflush(stdin);

	if (key4 == ' ')
	{
		system("cls");
	}
	else goto j;

	a:
	gotoxy(34, 9);
	printf("\033[47;31;5m                                                     \033[0m");
	gotoxy(34, 10);
	printf("\033[47;31;5m                                                     \033[0m");
	gotoxy(34, 11);
	printf("\033[47;31;5m        Do you want to start this game again?        \033[0m");
	gotoxy(34, 12);
	printf("\033[47;31;5m                                                     \033[0m");
	gotoxy(34, 13);
	printf("\033[47;31;5m                                                     \033[0m");
	gotoxy(34, 14);
	printf("\033[47;31;5m                                                     \033[0m");
	gotoxy(34, 15);
	printf("\033[47;31;5m                                                     \033[0m");
	gotoxy(34, 16);
	printf("\033[47;31;5m                【Press SPACE for Yes】              \033[0m");
	gotoxy(34, 17);
	printf("\033[47;31;5m                                                     \033[0m");
	gotoxy(34, 18);
	printf("\033[47;31;5m                                                     \033[0m");
	gotoxy(1, 1);
    
    h:
	key2 = _getch();
	fflush(stdin);
	
	if (key2 == ' ') 
	{
		system("cls");
		goto r;
	}
	else goto h;
	return 0;
}

//1.画地图
void drawMap()
{   //⊙:食物   █:墙    ■；蛇身
	srand((unsigned int)time(NULL));              //随机函数种子
	//1.圈地
		//1.1 左右边框
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		gotoxy(0, i);
		printf("█");
		gotoxy(MAPWIDTH - 2, i);
		printf("█");
	}
	//1.2 上下边框
	for (int i = 0; i < MAPWIDTH; i += 2)          //因为█占两个字符
	{
		gotoxy(i, 0);
		printf("█");
		gotoxy(i, MAPHEIGHT - 1);
		printf("█");
	}
	//2.画蛇
		//2.1 确定蛇的属性
	snake.len = len;
	snake.speed = speed;
	//2.2 画蛇
	snake.x[0] = MAPWIDTH / 2;
	snake.y[0] = MAPHEIGHT - 6;                //开始蛇头在屏幕中央
	gotoxy(snake.x[0], snake.y[0]);
	printf("■");                              //一节 是x=2
	//画剩下身体
	for (int k = 1; k < snake.len; k++)
	{
		snake.x[k] = snake.x[k - 1] + 2;
		snake.y[k] = snake.y[k - 1];
		gotoxy(snake.x[k], snake.y[k]);
		printf("■");
	}
	//3.画食物
		//3.1确定坐标
	while (1)
	{
		food.x = rand() % (MAPWIDTH - 4) + 2;
		food.y = rand() % (MAPHEIGHT - 2) + 1;
		if (food.x % 2 == 0)
		{
			break;
		}
	}
	//3.2画出来就可以
	gotoxy(food.x, food.y);
	printf("⊙");
}

void drawMap1()
{
	gotoxy(63, 5);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 6);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 7);
	printf("\033[47;31;5m         Press W、A、S、D to control yourself         \033[0m");
	gotoxy(63, 8);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 9);
	printf("\033[47;31;5m         Press SPACE to pause and to continue         \033[0m");
	gotoxy(63, 10);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 11);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 12);
	printf("\033[47;31;5m   Keep your keyboard in English or in Capital Lock   \033[0m");
	gotoxy(63, 13);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 14);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 15);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 16);
	printf("\033[47;31;5m                       Good Luck!                     \033[0m");
	gotoxy(63, 17);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(63, 18);
	printf("\033[47;31;5m                                                      \033[0m");
	gotoxy(100, 22);
	printf("——Loong");

	//1.圈地
		//1.1 左右边框
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		gotoxy(0, i);
		printf("█");
		gotoxy(MAPWIDTH - 2, i);
		printf("█");
	}
	//1.2 上下边框
	for (int i = 0; i < MAPWIDTH; i += 2)          //因为█占两个字符
	{
		gotoxy(i, 0);
		printf("█");
		gotoxy(i, MAPHEIGHT - 1);
		printf("█");
	}
	//2.画蛇
	//2.2 画蛇
	gotoxy(snake.x[0], snake.y[0]);
	printf("■");                              //一节 是x=2
	//画剩下身体
	for (int k = 1; k < snake.len; k++)
	{
		gotoxy(snake.x[k], snake.y[k]);
		printf("■");
	}
	//3.画食物
	//3.2画出来就可以
	gotoxy(food.x, food.y);
	printf("⊙");
}

//2.食物的产生
void createFood()
{
	//蛇把食物吃了
	if (snake.x[0] == food.x && snake.y[0] == food.y)
	{
		srand((unsigned int)time(NULL));
		//产生的食物不能在蛇身上，并且坐标要是偶数
		while (1)
		{
			int flag = 1;
			food.x = rand() % (MAPWIDTH - 4) + 2;
			food.y = rand() % (MAPHEIGHT - 2) + 1;
			//产生的食物不能在蛇身上
			for (int k = 0; k < snake.len; k++)
			{
				if (snake.x[k] == food.x && snake.y[k] == food.y)
				{
					flag = 0;                            //食物不合适的标志
					break;
				}
			}
			if (flag && food.x % 2 == 0)
			{
				break;
			}
		}
		gotoxy(food.x, food.y);
		printf("⊙");
		snake.len++;
		changeFlag = 1;
		points++;
	}
}

//3.按键操作
void keyDown()
{
	int key1 = key;                                        //标记上一次的移动 
	int key3 = 0;
	//无按键处理
	if (_kbhit())
	{    //有按键接受
		key = _getch();
	}
	//擦除最后位置
	if (!changeFlag)
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		printf("  ");
	}
	//后面的蛇身
	for (int i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	if (key == ' ')
	{
		gotoxy(MAPWIDTH / 2 - 8, MAPHEIGHT / 2-1);
		printf("\033[47;31;5m                 \033[0m");
		gotoxy(MAPWIDTH / 2 - 8, MAPHEIGHT / 2);
		printf("\033[47;31;5m   Pausing....   \033[0m");
		gotoxy(MAPWIDTH / 2 - 8, MAPHEIGHT / 2+1);
		printf("\033[47;31;5m                 \033[0m");
		gotoxy(119, 1);
		
		// system("pause>nul");//暂停
		// system("cls"); 
		// drawMap1();

		b:
		key3 = _getch();
		fflush(stdin);

		if (key3 == ' ')
		{
			system("cls"); 
			drawMap1();
		}
		else goto b;
	}
	   	  
	if ((key1 == 's' || key1 == 'S') && (key == 'w' || key == 'W')) key = 's';//蛇不能向反方向移动 
	if ((key1 == 'w' || key1 == 'W') && (key == 's' || key == 'S')) key = 'w';
	if ((key1 == 'a' || key1 == 'A') && (key == 'd' || key == 'D')) key = 'a';
	if ((key1 == 'd' || key1 == 'D') && (key == 'a' || key == 'A')) key = 'd';

	//移动方向处理
s:
	switch (key)
	{
	case'w':
	case'W':
		snake.y[0]--;
		break;
	case's':
	case'S':
		snake.y[0]++;
		break;
	case'a':
	case'A':
		snake.x[0] -= 2;                             //一个符号占用两个字符
		break;
	case'd':
	case'D':
		snake.x[0] += 2;
		break;
	default:key = key1;
		goto s;
	}
	gotoxy(snake.x[0], snake.y[0]);
	printf("■");
	changeFlag = 0;
	gotoxy(MAPHEIGHT + 2, 0);                        //移动不能一直看着光标
}

//4.蛇的状态：判断是否结束游戏
int snakeStatus()
{
	if (snake.y[0] == 0 || snake.y[0] == MAPHEIGHT - 2 || snake.x[0] == 0 || snake.x[0] == MAPWIDTH - 2)
		return 0;
	//蛇头不能撞自己
	for (int k = 1; k < snake.len; k++)
	{
		if (snake.x[0] == snake.x[k] && snake.y[k] == snake.y[0])
			return 0;
	}
	return 1;
}

//5.辅助函数：光标移动
void gotoxy(int x, int y)            //TC 是有的，现在已经淘汰了，要自己实现
{
	//调用win32 API 去设置控制台的光标位置
	//1.找到控制台的窗口
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//2.设置坐标
	COORD coord;
	//3.设置坐标
	coord.X = x;
	coord.Y = y;
	//4.同步到控制台SetConsoleCursorPosition
	SetConsoleCursorPosition(handle, coord);
}