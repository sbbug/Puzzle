#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<time.h>
using namespace std;
/*
  拼你妹游戏
  制作者:孙宏伟
  时间:2017/2/7
  4*3方格拼图
  */
//定义窗口大小
#define WIN_WIDTH 480
#define WIN_HEIGHT 360
//定义图片横竖个数
#define row 3
#define col 4
//图片大小
#define PIC_SIZE 120 
//定义图片类型的变量
IMAGE img; 
//定义存放图片的数组
IMAGE images[3*4]; 
//二维数组
int map[row][col] = { //最后一张成为白色的
	{0,1,2,3},
    {4,5,6,7},
    {8,9,10,11}};

void GameInit();
void DrawMap();
void RandMap();
void PlayGame();
//对二维数组进行随机打乱

void main(int argc, char*argv[]) {

	//初始化窗口
	initgraph(WIN_WIDTH,WIN_HEIGHT);

	srand((unsigned int )time(NULL));

	//加载图片
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
	//设置绘图环境
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

//绘制界面
void DrawMap() {
	//把二维数组元素与图片绑定
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			putimage(j*PIC_SIZE, i*PIC_SIZE, &images[map[i][j]]);
		}
	}
	//putimage(360, 240, &images[11]);
}

//打乱二维数组
//数字的打乱，有研究
void RandMap() {

	//定义一个临时数组，
	int temp[row*col];
	for (int i = 0;i < row*col;i++) {
		temp[i] = i;
		cout << i << '\t';
	}
	//打乱map数组里的数据
	int num = 0;
	//获取temp数组的元素大小
	int maxSize = row*col;
	for (int a = 0;a < row;a++) {
		for (int b = 0;b < col;b++) {

			num = rand()%maxSize; //生成0~maxSize-1的随机数
			map[a][b] = temp[num];//注意这里的辅助
			//把已经随机到的元素删除掉
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
	//1.玩游戏时，确定鼠标点下去后，是哪张图片
	//2.点击图片后，还要确定图片与空白图片是否相邻
	//3.交换这两个二维数组的信息
	int r=0, c=0;//鼠标点击元素对应的数组元素
	int blankR=0, blankC=0;//空白元素对应下标
	MOUSEMSG msg = { 0 };

	//开始确定空白图片下标
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (map[i][j] == 11) {
				blankR = i;
				blankC = j;
			}
		}
	}
	//确定鼠标点击的图片的下标
	msg = GetMouseMsg();
	switch (msg.uMsg) {
		case WM_LBUTTONDOWN:
			r = msg.y/PIC_SIZE;
			c = msg.x/PIC_SIZE;
			//对四种可能情况判断
			if ((r == blankR && c == blankC - 1) || (r == blankR && c == blankC + 1) || (c == blankC && r == blankR + 1) || c == blankC && r == blankR - 1) {
				map[blankR][blankC] = map[r][c];
				map[r][c] = 11;
			}
			
			break;
		default:
			break;
	}
}