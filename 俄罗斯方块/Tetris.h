#pragma once
#include "Block.h"
#include <vector>
#include <graphics.h>
using namespace std;
class Tetris
{
public:
	//���캯��
	Tetris(int rows, int cols, int left, int top, int blockSize);
	void init();
	void play();

private:
	void keyEvent();
	void updateWindow();

	//���ؾ��ϴε��õ�ʱ����
	//��һ�ε���ʱ�䣬����0
	int getDelay();
	void drop();
	void clearLine();
	void moveLeftRight(int offest);
	void rotate();
	void drawScore();

private:
	int delay = 30;
	bool update = false;//�Ƿ����

	vector<vector<int>> map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;

	////Ԥ�淽��
	Block *curBlock;
	Block* nextBlock;
	Block bakBlock;
	//����

	int score;
	int level;
	int lineCount;// �����˼���
};

