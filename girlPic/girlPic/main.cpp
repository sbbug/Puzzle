#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<time.h>
using namespace std;
/*
  ƴ������Ϸ
  ������:���ΰ
  ʱ��:2017/2/7
  4*3����ƴͼ
  */
//���崰�ڴ�С
#define WIN_WIDTH 480
#define WIN_HEIGHT 360
//����ͼƬ��������
#define row 3
#define col 4
//ͼƬ��С
#define PIC_SIZE 120 
//����ͼƬ���͵ı���
IMAGE img; 
//������ͼƬ������
IMAGE images[3*4]; 
//��ά����
int map[row][col] = { //���һ�ų�Ϊ��ɫ��
	{0,1,2,3},
    {4,5,6,7},
    {8,9,10,11}};

void GameInit();
void DrawMap();
void RandMap();
void PlayGame();
//�Զ�ά��������������

void main(int argc, char*argv[]) {

	//��ʼ������
	initgraph(WIN_WIDTH,WIN_HEIGHT);

	srand((unsigned int )time(NULL));

	//����ͼƬ
	loadimage(&img, __T("../public/girl.jpg"), WIN_WIDTH, WIN_HEIGHT);
	
	RandMap();
	GameInit();
	while (1) {
		DrawMap();
		PlayGame();
	}
	

	_getch();
	closegraph();
	system("pause");
}

void GameInit() {
	//���û�ͼ����
	SetWorkingImage(&img);
	int n = 0;

	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			getimage(&images[n], j * 120, i * 120, PIC_SIZE, PIC_SIZE);
			n++;
		}
	}
	cout << "n===" << n << endl;
	SetWorkingImage(NULL);
	loadimage(&images[11],L"../public/blank.bmp",PIC_SIZE,PIC_SIZE);
	
}

//���ƽ���
void DrawMap() {
	//�Ѷ�ά����Ԫ����ͼƬ��
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			putimage(j*PIC_SIZE, i*PIC_SIZE, &images[map[i][j]]);
		}
	}
	//putimage(360, 240, &images[11]);
}

//���Ҷ�ά����
//���ֵĴ��ң����о�
void RandMap() {

	//����һ����ʱ���飬
	int temp[row*col];
	for (int i = 0;i < row*col;i++) {
		temp[i] = i;
		cout << i << '\t';
	}
	//����map�����������
	int num = 0;
	//��ȡtemp�����Ԫ�ش�С
	int maxSize = row*col;
	for (int a = 0;a < row;a++) {
		for (int b = 0;b < col;b++) {

			num = rand()%maxSize; //����0~maxSize-1�������
			map[a][b] = temp[num];//ע������ĸ���
			//���Ѿ��������Ԫ��ɾ����
			for (int n = num;n < maxSize-1;n++) {
				temp[n] = temp[n + 1];
			}
			maxSize--;
		}
	}
	cout << endl;
	for (int a1 = 0;a1 < row;a1++) {
		for (int b1 = 0;b1 < col;b1++) {
			cout << map[a1][b1]<<'\t';
		}
	}
}

void PlayGame() {
	//1.����Ϸʱ��ȷ��������ȥ��������ͼƬ
	//2.���ͼƬ�󣬻�Ҫȷ��ͼƬ��հ�ͼƬ�Ƿ�����
	//3.������������ά�������Ϣ
	int r=0, c=0;//�����Ԫ�ض�Ӧ������Ԫ��
	int blankR=0, blankC=0;//�հ�Ԫ�ض�Ӧ�±�
	MOUSEMSG msg = { 0 };

	//��ʼȷ���հ�ͼƬ�±�
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (map[i][j] == 11) {
				blankR = i;
				blankC = j;
			}
		}
	}
	//ȷ���������ͼƬ���±�
	msg = GetMouseMsg();
	switch (msg.uMsg) {
		case WM_LBUTTONDOWN:
			r = msg.y/PIC_SIZE;
			c = msg.x/PIC_SIZE;
			//�����ֿ�������ж�
			if ((r == blankR && c == blankC - 1) || (r == blankR && c == blankC + 1) || (c == blankC && r == blankR + 1) || c == blankC && r == blankR - 1) {
				map[blankR][blankC] = map[r][c];
				map[r][c] = 11;
			}
			
			break;
		default:
			break;
	}
}