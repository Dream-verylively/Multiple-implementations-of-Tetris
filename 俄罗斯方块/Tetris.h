#pragma once
#include "Block.h"
#include <vector>
#include <graphics.h>
using namespace std;
class Tetris
{
public:
	//构造函数
	Tetris(int rows, int cols, int left, int top, int blockSize);
	void init();
	void play();

private:
	void keyEvent();
	void updateWindow();

	//返回距上次调用的时间间隔
	//第一次调用时间，返回0
	int getDelay();
	void drop();
	void clearLine();
	void moveLeftRight(int offest);
	void rotate();
	void drawScore();

private:
	int delay = 30;
	bool update = false;//是否更新

	vector<vector<int>> map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;

	////预告方块
	Block *curBlock;
	Block* nextBlock;
	Block bakBlock;
	//备份

	int score;
	int level;
	int lineCount;// 消除了几行
};

