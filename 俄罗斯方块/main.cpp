/*
	1.创建项目
	2.导入素材
	3.c++开发
	4.设计项目模块（类）
		Block Tetris 
	5.设计模块主要接口
	6.开始游戏
*/

#include "Tetris.h"
#include "Block.h"

int main(void) {
	Tetris game(20, 10, 263, 133, 36);
	game.play();

	/*game.init();
	Block block;
	block.draw(56, 58);
	system("pause");*/

	return 0;
}