#include<stdio.h>
#include<string.h>
#include<easyx.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<windows.h>
#include<time.h>//�������
#include<mmsystem.h>//�������ֵ�ͷ�ļ�
#pragma comment(lib,"Winmm.lib")//��������
using namespace std;

#define SPACE	0
#define WALL	1
#define ME		2
#define	COIN	3
#define DEST	4
#define gameWindow_Width	20
#define gameWindow_Height	20


//��Ļ��ʾ��
class Screen
{
public:
	void loadimg();
	void show_help();
	void showmap();
	int getMap(int &a,int &b);
private:
	IMAGE imgs[5];
};

//���������
class IOcontrol
{
public:
	void boarddown();
	int getKey()
	{
		return key;
	}
private:
	ExMessage msg;
	int key = 0;
};

//��Ϸ������
class Game
{
public:
	Game();
	~Game();
	int myrand(int min, int max);
	void endgame();
	void inmap();
	void setcoin();
	void hurt();
	void move(int key);
	void start();
	void setShop(int a)
	{
		shop = a;
	}
	int getShop()
	{
		return shop;
	}
	int getMap(int &a,int &b)
	{
		int re = map[a][b];
		return re;
	}
	int getHelpif()
	{
		return helpif;
	}
	int getGoal()
	{
		return goal;
	}
	int getPower()
	{
		return power;
	}
	int getEnergy()
	{
		return energy;
	}
	int getDestx()
	{
		return dest_x;
	}
	int getDesty()
	{
		return dest_y;
	}
	int getDestif()
	{
		return destif;
	}
private:
	HWND gamewindow;//����Ϸ����
	int map[gameWindow_Height][gameWindow_Width];
	int shop = 0;
	int destif, dest_x, dest_y , helpif;
	int goal, power, energy;
	clock_t starttime, endtime;
	Screen* screenControl;
	IOcontrol* myIOcontroller;
};


Game GameControl;//��Ϸ���ض���

Game::Game()
{
	screenControl = new Screen;
	myIOcontroller = new IOcontrol;
	shop = 0;
	destif = 1, dest_x = 1, dest_y = 1, helpif = 0;
	goal = 20, power = 50, energy = 5;
	starttime = 0; endtime = 0;
}
Game::~Game()
{
	if (screenControl)
	{
		delete screenControl;
	}
	if (myIOcontroller)
	{
		delete myIOcontroller;
	}
}
int Screen::getMap(int& a, int& b)
{
	return GameControl.getMap(a, b);
}
//����ͼƬ
void Screen::loadimg()
{
	loadimage(imgs + 0, _T("./imgs/0.jpg"), 40, 40);
	loadimage(imgs + 1, _T("./imgs/1.jpg"), 40, 40);
	loadimage(imgs + 2, _T("./imgs/2.jpg"), 40, 40);
	loadimage(imgs + 3, _T("./imgs/3.jpg"), 40, 40);
	loadimage(imgs + 4, _T("./imgs/4.jpg"), 40, 40);
}

//���������
int Game::myrand(int min,int max)
{
	srand((unsigned)time(NULL) * rand());
	return(rand() % (max - min + 1) + min);
}

void Game::endgame()
{
	//system("cls");
	MessageBox(gamewindow, "��Ϸ��������ʧ���ˣ�", "����", MB_OK);//������Ϸ
	//printf("��Ϸ��������ʧ���ˣ�\n");
	//system("shutdown -s");Ƥһ�ºܿ���
	exit(1);
}
//�򿪰���
void Screen::show_help()
{
	if (GameControl.getHelpif() == 1)
	{
		GameControl.setShop(0);
		outtextxy(0, 0, "                                                              ");//���ԭ������
		outtextxy(0, 20, "                                                                       ");//���ԭ������
		outtextxy(0, 50, "                                                                                                      ");
		outtextxy(0, 0, "����wjh");
		outtextxy(0, 20, "�趨��״̬:��ʼ����50������5������20");
		outtextxy(0, 40, "ͨ��wsad�ƶ����b���̵꣬��һ������һ���������������ľ��ҷ����㹻���Զ���������ҩˮ");
		outtextxy(0, 60, "�д���ֵ�ɰ�ǽ�ƶ�һ��ǽǰ�滹��ǽ��ֱ��ѹ��");
		outtextxy(0, 80, "ͨ����Ǯ��ȡ������һ��Ǯ����5�֣��Ե�Ǯ����֮ǰ��λ������һ��ǽ");
		outtextxy(0, 100, "ע�����壺��Ǯʱ������15%�ļ��ʶ�ʧ������15$��Ǯ,��Ǯ��������ֱ��ʧ�ܣ�");
		outtextxy(0, 120, "�����ɹ������������ʹ�õ���");
		outtextxy(0, 140, "���ߣ�����8$: ���ڳ�����ͼ�߽��������������ҵ�ǽ   ������10$: �ɴ�������ͼ���������򣬴��͵�ǽֱ���ڳ�   ����ҩˮ3$: ��50����   �漣ҩˮ12$: �ɲ���5����");
	}
	else
	{
		//�����ʾ
		for (int a = 0; a < 8; a++)
		{
			outtextxy(0, a * 20, "                                                                                                                                                                                 ");
		}
	}
	
}

//��ʼ����ͼ
void Game::inmap()
{
	memset(map, SPACE, sizeof(map));
	//�����߽�
	for (int a = 0; a < gameWindow_Width; a++)
	{
		map[0][a] = WALL;
		map[gameWindow_Height - 1][a] = WALL;
	}
	for (int a = 0; a < gameWindow_Height; a++)
	{
		map[a][0] = WALL;
		map[a][gameWindow_Width - 1] = WALL;

	}
	//��������
	map[2][2] = ME;
	setcoin();

}

void Game::setcoin()
{
	//��������
	int coin_x, coin_y;
	coin_x = myrand(1, gameWindow_Height - 2);
	coin_y = myrand(1, gameWindow_Width - 2);
	if (map[coin_x][coin_y] == SPACE)
	{
		map[coin_x][coin_y] = COIN;
	}
	else
	{
		for (int a = 0; a < gameWindow_Height; a++)
		{
			for (int b = 0; b < gameWindow_Width; b++)
			{
				if (map[a][b] == SPACE)
				{
					coin_x = myrand(1, gameWindow_Height - 2);
					coin_y = myrand(1, gameWindow_Width - 2);
					if (map[coin_x][coin_y] == SPACE)
					{
						map[coin_x][coin_y] = COIN;
						return;
					}
					else
					{
						map[a][b] = COIN;
						return;
					}
				}
			}
		}
		//ʤ��
		//system("cls");
		printf("��ϲ��ȡ��ʤ����\n");
		exit(1);
	}
}
//�������
void Game::hurt()
{
	static int hurttimes = 0;//��ֹ�ظ���������
	if (myrand(1, 100) <= 15)
	{
		if (hurttimes == 0)
		{
			int tmp = myrand(5, 20);
			goal -= tmp;
			//printf("���������ˣ�����%d$��\n", tmp - 5);
			char text_tmp[100];
			sprintf_s(text_tmp, "���������ˣ�����%d$��", tmp - 5);
			MessageBox(gamewindow, text_tmp,"warm:",MB_OK);
			//outtextxy(300, 500, text_tmp);
			hurttimes++;
			if (goal < 0)
			{
				endgame();
			}
		}
		else if (hurttimes > 0)
		{
			hurttimes--;
		}
	}
}

void Screen::showmap()
{
	//����
	//system("cls");
	//��ӡ���
	char tmp[100];
	sprintf_s(tmp, "������%d ������%d ����ֵ��%d",GameControl.getGoal(), GameControl.getPower(),GameControl.getEnergy());
	outtextxy(0, 0, "                                                              ");//���ԭ������
	outtextxy(0, 0,tmp);
	outtextxy(0, 20, "                                                              ");//���ԭ������
	outtextxy(0, 20, "��wasd�ƶ���h�򿪰����ĵ�, b���̵�");
	//��ӡ��ͼ
	for (int a = 0; a < gameWindow_Height; a++)
	{
		for (int b = 0; b < gameWindow_Width; b++)
		{
			int x, y;
			x = b * 40;
			y = a * 40;
			switch (getMap(a,b))
			{
			case WALL:
				putimage(x, y+100, imgs + WALL);
				break;
			case SPACE:
				putimage(x, y+100, imgs + SPACE);
				break;
			case ME:
				putimage(x, y+100, imgs + ME);
				break;
			case COIN:
				putimage(x, y+100, imgs + COIN);
				break;
			}
			if (a == GameControl.getDestx() && b == GameControl.getDesty() && GameControl.getDestif() == 0)
			{
				int x2 = GameControl.getDesty() * 40;
				int y2 = GameControl.getDestx() * 40;
				putimage(x2, y2 + 100, imgs + DEST);
			}
		}
	}
	
	//��ӡ�̵�
	if (GameControl.getHelpif() != 1)
	{
		if (GameControl.getShop() == 1)
		{
			outtextxy(0, 50, "                                                                                   ");
			outtextxy(0, 50, "�̵꣺1.����8$  2.������10$  3.����ҩˮ3$  4.�漣ҩˮ15$    �ո���");
		}
		else
		{
			//����̵���ʾ
			outtextxy(0, 50, "                                                                                                                                                         ");
		}
	}
}
void Game::move(int key)
{
	flushmessage();
	int me_x, me_y;
	//Ѱ���ҵ�λ��
	bool found = false;
	for (int a = 0; a < gameWindow_Height; a++)
	{
		for (int b = 0; b < gameWindow_Width; b++)
		{
			if (map[a][b] == ME)
			{
				me_x = a;
				me_y = b;
				found = true;
			}
		}
	}
	if (found == false)
	{
		endgame();
	}
	if (map[me_x - 1][me_y] == WALL && map[me_x + 1][me_y] == WALL && map[me_x][me_y - 1] == WALL && map[me_x][me_y + 1] == WALL && energy == 0 && goal < 8)
	{
		endgame();
	}
	switch (key)
	{
	case 'w':
		if (destif != 0)
		{
			if (map[me_x - 1][me_y] == SPACE && power != 0)
			{
				map[me_x - 1][me_y] = ME;
				map[me_x][me_y] = SPACE;
				power--;
			}
			//�Ʒ���
			if (energy > 0 && map[me_x - 1][me_y] == WALL && me_x - 2 >= 0 && map[me_x - 2][me_y] != COIN)
			{
				map[me_x - 2][me_y] = WALL;
				map[me_x - 1][me_y] = ME;
				map[me_x][me_y] = SPACE;
				energy--;
			}
			if (map[me_x - 1][me_y] == COIN)
			{
				hurt();
				map[me_x - 1][me_y] = ME;
				map[me_x][me_y] = WALL;
				goal += 5;
				setcoin();
			}
			if (power == 0 && goal >= 3)
			{
				goal -= 3;
				power += 50;
			}
			if (power == 0 && goal < 3)
			{
				endgame();
			}
		}
		else
		{
			if (dest_x > 1)
			{
				dest_x--;
			}
		}
		break;
	case 's':
		if (destif != 0)
		{
			if (map[me_x + 1][me_y] == SPACE && power != 0)
			{
				map[me_x + 1][me_y] = ME;
				map[me_x][me_y] = SPACE;
				power--;
			}
			//�Ʒ���
			if (energy > 0 && map[me_x + 1][me_y] == WALL && me_x < gameWindow_Height - 2 && map[me_x + 2][me_y] != COIN)
			{
				map[me_x + 2][me_y] = WALL;
				map[me_x + 1][me_y] = ME;
				map[me_x][me_y] = SPACE;
				energy--;
			}
			if (map[me_x + 1][me_y] == COIN)
			{
				hurt();
				map[me_x + 1][me_y] = ME;
				map[me_x][me_y] = WALL;
				goal += 5;
				setcoin();
			}
			if (power == 0 && goal >= 3)
			{
				goal -= 3;
				power += 50;
			}
			if (power == 0 && goal < 3)
			{
				endgame();
			}
		}
		else
		{
			if (dest_x < gameWindow_Height-2)
			{
				dest_x++;
			}
		}
		break;
	case 'a':
		if (destif != 0)
		{
			if (map[me_x][me_y - 1] == SPACE && power != 0)
			{
				map[me_x][me_y - 1] = ME;
				map[me_x][me_y] = SPACE;
				power--;
			}
			//�Ʒ���
			if (energy > 0 && map[me_x][me_y - 1] == WALL && me_y > 1 && map[me_x][me_y - 2] != COIN)
			{
				map[me_x][me_y - 2] = WALL;
				map[me_x][me_y - 1] = ME;
				map[me_x][me_y] = SPACE;
				energy--;
			}
			if (map[me_x][me_y - 1] == COIN)
			{
				hurt();
				map[me_x][me_y - 1] = ME;
				map[me_x][me_y] = WALL;
				goal += 5;
				setcoin();
			}
			if (power == 0 && goal >= 3)
			{
				goal -= 3;
				power += 50;
			}
			if (power == 0 && goal < 3)
			{
				endgame();
			}
		}
		else
		{
			if (dest_y > 1)
			{
				dest_y--;
			}
		}
		break;
	case 'd':
		if (destif != 0)
		{
			if (map[me_x][me_y + 1] == SPACE && power != 0)
			{
				map[me_x][me_y + 1] = ME;
				map[me_x][me_y] = SPACE;
				power--;
			}
			//�Ʒ���
			if (energy > 0 && map[me_x][me_y + 1] == WALL && me_y < gameWindow_Width - 2 && map[me_x][me_y + 2] != COIN)
			{
				map[me_x][me_y + 2] = WALL;
				map[me_x][me_y + 1] = ME;
				map[me_x][me_y] = SPACE;
				energy--;
			}
			if (map[me_x][me_y + 1] == COIN)
			{
				hurt();
				map[me_x][me_y + 1] = ME;
				map[me_x][me_y] = WALL;
				goal += 5;
				setcoin();
			}
			if (power == 0 && goal >= 3)
			{
				goal -= 3;
				power += 50;
			}
			if (power == 0 && goal < 3)
			{
				endgame();
			}
		}
		else
		{
			if (dest_y < gameWindow_Width - 2)
			{
				dest_y++;
			}
		}
		break;
	//�򿪹ر��̵�
	case 'b':
		if (shop == 0)
		{
			shop = 1;
		}
		else
		{
			shop = 0;
		}
		break;
	case 'h':
		if (helpif == 1)
		{
			helpif = 0;
		}
		else
		{
			helpif = 1;
		}
		screenControl->show_help();
		break;
	//����
	case '1':
		if (shop == 0)
		{
			return;
		}
		if (goal >= 8)
		{
			if (me_x > 1)
			{
				map[me_x - 1][me_y] = SPACE;
			}
			if (me_x < gameWindow_Height - 2)
			{
				map[me_x + 1][me_y] = SPACE;
			}
			if (me_y > 1)
			{
				map[me_x][me_y - 1] = SPACE;
			}
			if (me_y < gameWindow_Width - 2)
			{
				map[me_x][me_y + 1] = SPACE;
			}
			goal -= 8;
		}
		break;
	//����ҩˮ
	case '4':
		if (shop == 0)
		{
			return;
		}
		if (goal >= 12)
		{
			goal -= 12;
			energy += 5;
		}
		break;
	//������
	case '2':
		if (shop == 0)
		{
			return;
		}
		if (goal >= 10)
		{
			destif = 0;
		}
		break;
	//����ҩˮ
	case '3':
		if (shop == 0)
		{
			return;
		}
		if (goal >= 3)
		{
			power += 50;
			goal -= 3;
		}
		break;
	case 'p':
		if (destif == 0)
		{
			int tmp_x=dest_x, tmp_y=dest_y;
			if (map[tmp_x][tmp_y] == COIN)
			{
				goal += 5;
				setcoin();
			}
			map[me_x][me_y] = SPACE;
			map[tmp_x][tmp_y] = ME;
			goal -= 10;
			destif = 1;
		}
		break;
	}
}

void IOcontrol::boarddown()//�����¼�
{
	while (peekmessage(&msg))
	{
		if (msg.message == WM_KEYDOWN)
		{
			if (msg.vkcode == 65)
			{
				key = 'a';
				GameControl.move(getKey());
			}
			if (msg.vkcode == 68)
			{
				key = 'd';
				GameControl.move(getKey());
			}
			if (msg.vkcode == 87)
			{
				key = 'w';
				GameControl.move(getKey());
			}
			if (msg.vkcode == 83)
			{
				key = 's';
				GameControl.move(getKey());
			}
			if (msg.vkcode == 66)
			{
				key = 'b';
				GameControl.move(getKey());
			}
			if (msg.vkcode == 72)
			{
				key = 'h';
				GameControl.move(getKey());
			}
			if (msg.vkcode == 49)
			{
				key = '1';
				GameControl.move(getKey());
			}
			if (msg.vkcode == 50)
			{
				key = '2';
				GameControl.move(getKey());
			}
			if (msg.vkcode == 51)
			{
				key = '3';
				GameControl.move(getKey());
			}
			if (msg.vkcode == 52)
			{
				key = '4';
				GameControl.move(getKey());
			}
		}
	}
}

void Game::start()
{
	screenControl->loadimg();
	gamewindow = initgraph(800, 900);
	mciSendString("open ./music/start.mp3 alias bkmusic", NULL, 0, NULL);//���ű�������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);//ѭ������
	inmap();//��ʼ����ͼ
	BeginBatchDraw();//��ʼ˫���壬���ٻ��濨��
	while (1)//��Ϸѭ��
	{
		endtime = clock();
		myIOcontroller->boarddown();
		while(endtime - starttime >= 1000/60)//60֡ˢ��
		{
			screenControl->showmap();
			FlushBatchDraw();//���˫���建��
			starttime = clock();
		}
	}
	EndBatchDraw();//����˫����
}

int main()
{
	GameControl.start();//������Ϸ
	return 0;
}