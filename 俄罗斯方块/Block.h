#pragma once
#include <graphics.h>
#include <vector>
using namespace std;

struct Point {
	int row;
	int col;
};

class Block
{
public:
	Block();
	void drop();
	void moveLeftRight(int offest);
	void rotate();
	void draw(int leftMargin, int topMargin);
	static IMAGE** getImages();
	Block& operator = (const Block& other);

	bool blockInMap(const vector<vector<int>>& map);
	void slolidify(vector<vector<int>>& map);
	int getBlockType();

private:
	//∑ΩøÈ¿‡–Õ
	int blockType;
	Point smallBlocks[4];
	IMAGE *img;

	static IMAGE* imgs[7];
	static int size;
};

