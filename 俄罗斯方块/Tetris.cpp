#include "Tetris.h"
#include "Block.h"
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
								
#define MAX_LEVEL 5
const int SPEED_NORMAL[MAX_LEVEL] = { 500, 300, 150, 100, 80 };
const int SPEED_QUICK = 30;

Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
	this->rows = rows;
	this->cols = cols;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blockSize;

	for (int i = 0; i < rows; i++) {
		vector<int> row;
		for (int j = 0; j < cols; j++) {
			row.push_back(0);
		}
		map.push_back(row);
	}
}

void Tetris::init()
{
	delay = SPEED_NORMAL[0];

	//随机种子配置
	srand(time(NULL));

	//创建游戏窗口
	initgraph(938, 896);

	//加载背景图片
	loadimage(&imgBg, "res/bg2.png");

	//初始化游戏区中的数据
	char data[20][10] = {};
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[i][j] = 0;
		}
	}
	score = 0;
	level = 0;
	lineCount = 0;
}

void Tetris::play()
{
	init();

	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	int timer = 0;
	while (1) {
		//接受输入
		keyEvent();

		timer += getDelay();
		if (timer > delay) {
			timer = 0;
			drop();
			//渲染
			update = true;
		}

		if (update) {
			update = false;
			//渲染画面
			updateWindow();

			//更新游戏数据
			clearLine();
		}
	}
}

void Tetris::keyEvent()
{
	unsigned char ch; // 0...255
	bool rotateFlag = false;
	int dx = 0;

	while (_kbhit()) {
		ch = _getch();

		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72://up
				rotateFlag = true;
				break;
			case 80://down
				delay = SPEED_QUICK;
				break;
			case 75://left
				dx = -1;
				break;
			case 77://right
				dx = 1;
				break;
			default:
				break;
			}
		}
	}
	if (rotateFlag) {
		rotate();
		update = true;
	}

	if (dx != 0) {
		moveLeftRight(dx);
		update = true;
	}
}

void Tetris::updateWindow()
{
	putimage(0, 0, &imgBg);

	/*Block block;
	block.draw(163, 133);*/
	IMAGE** imgs = Block::getImages();

	BeginBatchDraw();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0)
				continue;
			int x = j * blockSize + leftMargin;
			int y = i * blockSize + topMargin;
			putimage(x, y, imgs[map[i][j] - 1]);
		}
	}

	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(689, 150);

	drawScore();



	EndBatchDraw();
}

int Tetris::getDelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();

	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}

	return 0;
}

void Tetris::drop()
{
	bakBlock = *curBlock;
	curBlock->drop();

	if (!curBlock->blockInMap(map)) {
		//固化方块
		bakBlock.slolidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}

	delay = SPEED_NORMAL[level - 1] ;
}

void Tetris::clearLine()
{
	int lines = 0;
	int slowIndex = rows - 1;
	for (int fastIndex = rows - 1; fastIndex >= 0; fastIndex--) {
		int count = 0;
		for (int i = 0; i < cols; i++) {
			if (map[fastIndex][i])
				count++;
			map[slowIndex][i] = map[fastIndex][i];
		}
		if (count < cols)
			slowIndex--;
		else
			lines++;
	}
	if (lines > 0) {
		int addScore[4] = { 10, 30, 60, 80 };
		score += addScore[lines - 1];

		mciSendString("play res/xiaochu1.mp3", 0, 0, 0);
		update = true;

		level = (score + 99) / 100;
	}
	lineCount += lines;
}

void Tetris::moveLeftRight(int offest)
{
	bakBlock = *curBlock;
	curBlock->moveLeftRight(offest);

	if (!curBlock->blockInMap(map)) {
		*curBlock = bakBlock;
	}
}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7)
		return;

	bakBlock = *curBlock;
	curBlock->rotate();

	if (!curBlock->blockInMap(map)) {
		*curBlock = bakBlock;
	}
}

void Tetris::drawScore()
{
	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);

	setcolor(RGB(180, 180, 180));

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 60;
	f.lfWeight = 30;
	f.lfQuality = ANTIALIASED_QUALITY;
	//使字体抗锯齿

	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));
	settextstyle(&f);

	setbkmode(TRANSPARENT);

	outtextxy(670, 727, scoreText);

	//消了多少行
	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);
	gettextstyle(&f);
	int xPox = 224 - f.lfWidth * strlen(scoreText);
	outtextxy(xPox, 817, scoreText);

	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(224 - 30, 727, scoreText);
}
