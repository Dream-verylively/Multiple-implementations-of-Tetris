/*
	1.������Ŀ
	2.�����ز�
	3.c++����
	4.�����Ŀģ�飨�ࣩ
		Block Tetris 
	5.���ģ����Ҫ�ӿ�
	6.��ʼ��Ϸ
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