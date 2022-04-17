//debugged by dzq at 13:11,10/02/2020
#include <iostream>
#include <cstdlib>
#include <windows.h>       //光标设置的API
#include <ctime>          //食物随机 
#include <conio.h>         //按键监控
using namespace std;
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
int changeFlag = 0; //蛇的变化标记
int points = 0;//得分 
int speed=100;//蛇的速度（每隔多少毫秒移动一格） 
int len=3;//初始长度 
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
	l2:
	char c=0;//判断是否重新开始的变量 
	changeFlag = 0;key='w';points = 0;//重置参数 
	gotoxy(73, 8);
	cout << "Press W、A、S、D to control yourself"; 
	gotoxy(68, 10);
	cout << "Press P to pause,then press any key to continue"; 
	gotoxy(67, 12);
	cout << "Keep your keyboard in English or in Capital Lock";
	gotoxy(86, 14);
	cout << "Good Luck!";
	gotoxy(100,20);
	cout << "——Loong";
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
	// 系统sleep函数，暂停一段时间
	Sleep(1000);
	system("cls");
	gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 - 3);
	cout << "Game  Over";
	gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 - 1);
	cout << "Your points : " << points;
	gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 + 1);
	cout << "Do you want to start this game again?";
	gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 + 3);
	cout << "Press Y for Yes,others for No";
	gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 + 5);
	cin >> c;
	fflush(stdin);
	if(c=='y'||c=='Y'){
		system("cls");
		goto l2;
	}
	return 0;
}

//1.画地图
void drawMap()
{   //⊙:食物   █:墙    卍；蛇头     ■；蛇身
	srand((unsigned int)time(NULL));              //随机函数种子
	//1.圈地
		//1.1 左右边框
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		gotoxy(0, i);
		cout << "█";
		gotoxy(MAPWIDTH - 2, i);
		cout << "█";
	}
	//1.2 上下边框
	for (int i = 0; i < MAPWIDTH; i += 2)          //因为█占两个字符
	{
		gotoxy(i, 0);
		cout << "█";
		gotoxy(i, MAPHEIGHT - 1);
		cout << "█";
	}
	//2.画蛇
		//2.1 确定蛇的属性
	snake.len = len;
	snake.speed = speed;
	//2.2 画蛇
	snake.x[0] = MAPWIDTH / 2;
	snake.y[0] = MAPHEIGHT - 6;                //开始蛇头在屏幕中央
	gotoxy(snake.x[0], snake.y[0]);
	cout << "■";                              //一节 是x=2
	//画剩下身体
	for (int k = 1; k < snake.len; k++)
	{
		snake.x[k] = snake.x[k - 1] + 2;
		snake.y[k] = snake.y[k - 1];
		gotoxy(snake.x[k], snake.y[k]);
		cout << "■";
	}
	//3.画食物
		//3.1确定坐标
	while (1)
	{
		food.x = rand() % (MAPWIDTH - 4)+2;
		food.y = rand() % (MAPHEIGHT - 2)+1;
		if (food.x % 2 == 0)
		{
			break;
		}
	}
	//3.2画出来就可以
	gotoxy(food.x, food.y);
	cout << "⊙";
}
void drawMap1()
{   gotoxy(73, 8);
	cout << "Press W、A、S、D to control yourself"; 
	gotoxy(68, 10);
	cout << "Press P to pause,then press any key to continue"; 
	gotoxy(67, 12);
	cout << "Keep your keyboard in English or in Capital Lock";
	gotoxy(86, 14);
	cout << "Good Luck!";
	gotoxy(100,20);
	cout << "——Loong";
	//1.圈地
		//1.1 左右边框
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		gotoxy(0, i);
		cout << "█";
		gotoxy(MAPWIDTH - 2, i);
		cout << "█";
	}
	//1.2 上下边框
	for (int i = 0; i < MAPWIDTH; i += 2)          //因为█占两个字符
	{
		gotoxy(i, 0);
		cout << "█";
		gotoxy(i, MAPHEIGHT - 1);
		cout << "█";
	}
	//2.画蛇
	//2.2 画蛇
	gotoxy(snake.x[0], snake.y[0]);
	cout << "■";                              //一节 是x=2
	//画剩下身体
	for (int k = 1; k < snake.len; k++)
	{
		gotoxy(snake.x[k], snake.y[k]);
		cout << "■";
	}
	//3.画食物
	//3.2画出来就可以
	gotoxy(food.x, food.y);
	cout << "⊙";
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
		cout << "⊙";
		snake.len++;
		changeFlag = 1;
		points++;
	}
}
//3.按键操作
void keyDown()
{
	int key1=key;//标记上一次的移动 
	//无按键处理
	if (_kbhit())
	{    //有按键接受
		key = _getch();
	}
	//擦除最后位置
	if (!changeFlag)
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		cout << "  ";
	}
	//后面的蛇身
	for (int i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	if(key=='p'){
	system("pause");//暂停 
	system("cls");//清屏 
	drawMap1();//重新把地图等东西画出来，但不用重新定义坐标，所以新设了一个函数 
	}
	if ((key1=='s'||key1=='S')&&(key=='w'||key=='W')) key='s';//蛇不能向反方向移动 
	if ((key1=='w'||key1=='W')&&(key=='s'||key=='S')) key='w';
	if ((key1=='a'||key1=='A')&&(key=='d'||key=='D')) key='a';	
	if ((key1=='d'||key1=='D')&&(key=='a'||key=='A')) key='d';
	//移动方向处理
	l:
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
	default: 
	key=key1;
	goto l;
	}
	gotoxy(snake.x[0], snake.y[0]);
	cout << "■";
	changeFlag = 0;
	gotoxy(MAPHEIGHT + 2, 0);                        //移动不能一直看着光标
}
//4.蛇的状态：判断是否结束游戏
int snakeStatus()
{
	if (snake.y[0] == 0 || snake.y[0] == MAPHEIGHT -2 || snake.x[0] == 0 || snake.x[0] == MAPWIDTH - 2)
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
