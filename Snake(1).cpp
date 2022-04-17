//debugged by dzq at 13:11,10/02/2020
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>       //������õ�API
#include <time.h>          //ʳ����� 
#include <conio.h>         //�������
////////////////////////////////////////////////////
//             �����궨��
#define MAPHEIGHT 26       //���ڵ�����
#define MAPWIDTH  60
#define SNAKESIZE 1000       //�ߵ�������



//�������
////////////////////////////////////////////////////
//             ʳ��Ľṹ��
struct
{
	//���ȥ��λ������
	int x;
	int y;

}food;
////////////////////////////////////////////////////
//             �ߵĽṹ��
struct
{
	int x[SNAKESIZE];
	int y[SNAKESIZE];
	int len;        //�ߵĳ���
	int speed;      //�ߵ��ƶ��ٶ�
}snake;

////////////////////////////////////////////////////
//             ȫ�ֱ���
int key = 'w';      //��ʼ���ƶ�����
int changeFlag = 0; //�ߵı仯���
int points = 0;//�÷� 
int speed=100;//�ߵ��ٶȣ�ÿ�����ٺ����ƶ�һ�� 
int len=3;//��ʼ���� 
////////////////////////////////////////////////////
//1.����ͼ
void drawMap();
//2.ʳ��Ĳ���
void createFood();
//3.��������
void keyDown();
//4.�ߵ�״̬���ж��Ƿ������Ϸ
int snakeStatus();
//5.��������������ƶ�
void gotoxy(int x, int y);           //TC ���еģ������Ѿ���̭�ˣ�Ҫ�Լ�ʵ��

int main()
{
	l2:
	char c=0;//�ж��Ƿ����¿�ʼ�ı��� 
	changeFlag = 0;key='w';points = 0;//���ò��� 
	gotoxy(73, 8);
	printf("Press W��A��S��D to control yourself"); 
	gotoxy(68, 10);
	printf("Press P to pause,then press any key to continue"); 
	gotoxy(67, 12);
	printf("Keep your keyboard in English or in Capital Lock");
	gotoxy(86, 14);
	printf("Good Luck!");
	gotoxy(100,20);
	printf("����Loong");
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
	gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 - 3);
	printf("Game  Over");
	gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 - 1);
	printf("Your points : %d",points);
	gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 + 1);
	printf("Do you want to start this game again?");
	gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 + 3);
	printf("Press Y for Yes,others for No");
	gotoxy(MAPWIDTH / 2 - 4, MAPHEIGHT / 2 + 5);
	scanf("%c",&c);
	fflush(stdin);
	if(c=='y'||c=='Y'){
		system("cls");
		goto l2;
	}
	return 0;
}

//1.����ͼ
void drawMap()
{   //��:ʳ��   ��:ǽ    �d����ͷ     ��������
	srand((unsigned int)time(NULL));              //�����������
	//1.Ȧ��
		//1.1 ���ұ߿�
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		gotoxy(0, i);
		printf("��");
		gotoxy(MAPWIDTH - 2, i);
		printf("��");
	}
	//1.2 ���±߿�
	for (int i = 0; i < MAPWIDTH; i += 2)          //��Ϊ��ռ�����ַ�
	{
		gotoxy(i, 0);
		printf("��");
		gotoxy(i, MAPHEIGHT - 1);
		printf("��");
	}
	//2.����
		//2.1 ȷ���ߵ�����
	snake.len = len;
	snake.speed = speed;
	//2.2 ����
	snake.x[0] = MAPWIDTH / 2;
	snake.y[0] = MAPHEIGHT - 6;                //��ʼ��ͷ����Ļ����
	gotoxy(snake.x[0], snake.y[0]);
	printf("��");                              //һ�� ��x=2
	//��ʣ������
	for (int k = 1; k < snake.len; k++)
	{
		snake.x[k] = snake.x[k - 1] + 2;
		snake.y[k] = snake.y[k - 1];
		gotoxy(snake.x[k], snake.y[k]);
		printf("��");
	}
	//3.��ʳ��
		//3.1ȷ������
	while (1)
	{
		food.x = rand() % (MAPWIDTH - 4)+2;
		food.y = rand() % (MAPHEIGHT - 2)+1;
		if (food.x % 2 == 0)
		{
			break;
		}
	}
	//3.2�������Ϳ���
	gotoxy(food.x, food.y);
	printf("��");
}
void drawMap1()
{   gotoxy(73, 8);
	printf("Press W��A��S��D to control yourself"); 
	gotoxy(68, 10);
	printf("Press P to pause,then press any key to continue"); 
	gotoxy(67, 12);
	printf("Keep your keyboard in English or in Capital Lock");
	gotoxy(86, 14);
	printf("Good Luck!");
	gotoxy(100,20);
	printf("����Loong");
	//1.Ȧ��
		//1.1 ���ұ߿�
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		gotoxy(0, i);
		printf("��");
		gotoxy(MAPWIDTH - 2, i);
		printf("��");
	}
	//1.2 ���±߿�
	for (int i = 0; i < MAPWIDTH; i += 2)          //��Ϊ��ռ�����ַ�
	{
		gotoxy(i, 0);
		printf("��");
		gotoxy(i, MAPHEIGHT - 1);
		printf("��");
	}
	//2.����
	//2.2 ����
	gotoxy(snake.x[0], snake.y[0]);
	printf("��");                              //һ�� ��x=2
	//��ʣ������
	for (int k = 1; k < snake.len; k++)
	{
		gotoxy(snake.x[k], snake.y[k]);
		printf("��");
	}
	//3.��ʳ��
	//3.2�������Ϳ���
	gotoxy(food.x, food.y);
	printf("��");
}
//2.ʳ��Ĳ���
void createFood()
{
	//�߰�ʳ�����
	if (snake.x[0] == food.x && snake.y[0] == food.y)
	{
		srand((unsigned int)time(NULL));
		//������ʳ�ﲻ���������ϣ���������Ҫ��ż��
		while (1)
		{
			int flag = 1;
			food.x = rand() % (MAPWIDTH - 4) + 2;
			food.y = rand() % (MAPHEIGHT - 2) + 1;
			//������ʳ�ﲻ����������
			for (int k = 0; k < snake.len; k++)
			{
				if (snake.x[k] == food.x && snake.y[k] == food.y)
				{
					flag = 0;                            //ʳ�ﲻ���ʵı�־
					break;
				}
			}
			if (flag && food.x % 2 == 0)
			{
				break;
			}
		}
		gotoxy(food.x, food.y);
		printf("��");
		snake.len++;
		changeFlag = 1;
		points++;
	}
}
//3.��������
void keyDown()
{
	int key1=key;//�����һ�ε��ƶ� 
	//�ް�������
	if (_kbhit())
	{    //�а�������
		key = _getch();
	}
	//�������λ��
	if (!changeFlag)
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		printf("  ");
	}
	//���������
	for (int i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	if(key=='p'){
	system("pause");//��ͣ 
	system("cls");//���� 
	drawMap1();//���°ѵ�ͼ�ȶ��������������������¶������꣬����������һ������ 
	}
	if ((key1=='s'||key1=='S')&&(key=='w'||key=='W')) key='s';//�߲����򷴷����ƶ� 
	if ((key1=='w'||key1=='W')&&(key=='s'||key=='S')) key='w';
	if ((key1=='a'||key1=='A')&&(key=='d'||key=='D')) key='a';	
	if ((key1=='d'||key1=='D')&&(key=='a'||key=='A')) key='d';
	//�ƶ�������
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
		snake.x[0] -= 2;                             //һ������ռ�������ַ�
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
	printf("��");
	changeFlag = 0;
	gotoxy(MAPHEIGHT + 2, 0);                        //�ƶ�����һֱ���Ź��
}
//4.�ߵ�״̬���ж��Ƿ������Ϸ
int snakeStatus()
{
	if (snake.y[0] == 0 || snake.y[0] == MAPHEIGHT -2 || snake.x[0] == 0 || snake.x[0] == MAPWIDTH - 2)
		return 0;
	//��ͷ����ײ�Լ�
	for (int k = 1; k < snake.len; k++)
	{
		if (snake.x[0] == snake.x[k] && snake.y[k] == snake.y[0])
			return 0;
	}
	return 1;
}
//5.��������������ƶ�
void gotoxy(int x, int y)            //TC ���еģ������Ѿ���̭�ˣ�Ҫ�Լ�ʵ��
{
	//����win32 API ȥ���ÿ���̨�Ĺ��λ��
	//1.�ҵ�����̨�Ĵ���
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//2.��������
	COORD coord;
	//3.��������
	coord.X = x;
	coord.Y = y;
	//4.ͬ��������̨SetConsoleCursorPosition
	SetConsoleCursorPosition(handle, coord);
}
