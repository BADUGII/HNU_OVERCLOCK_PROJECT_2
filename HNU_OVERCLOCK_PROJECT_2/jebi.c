#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_LEFT	2
#define DIR_RIGHT	3

void jebi_init(void);
void jebi_move_manual(key_t key);
void jebi_move_tail(int i, int nx, int ny);
void jebi(void);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];
int nb = 2;

int randjebi;
int jebi_result[PLAYER_MAX];

void jebi_init(void) {
	map_init(5, 18);
	tick = 0;
}

void jebi_move_manual(key_t key) {
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // ������ ����(0~3)
	switch (key) {
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// �������� ���� �ڸ�
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	jebi_move_tail(0, nx, ny);
}

void jebi_move_tail(int player , int nx, int ny) {
	int p = player;  // �̸��� ��...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

 //���� ����Ʈ������ ����°� �´� �ɱ� ��� ������ ��.
//���� ������ �˰����� �����ϳ� �ϳ��� ��ǥ(x,y)�� �ν��ؼ� @�� �ٲٴ°� �����߾���.
void jebi_note(void) { //?��� �ڵ�
	gotoxy(2, 2);
	int n = 8;
	for (int i = 0; i < n; i++) { //i < n n�Լ��� ���� �÷��̾� �� ���� ��(player alive) �÷��̾� �� ��ŭ ���� �����ؾ���)
		printf("?");
		printf(" ");
	}
}

void jebi(void) {
	/*
	for (int i = 0; i < n_player; i++) {
		x = 2;
		y = i+nb;
		px[i] = x;
		py[i] = y;
		back_buf[px[i]][py[i]] = '?';
		nb += 2;
	}
	*/
	jebi_init();
	jebi_display();
	//jebi_dialog("-�غ�-"); //dialog�� ����� �׽�Ʈ �߿� �Ž����� �ּ�ó�� �س�����.
	//�ؿ� jebi_dialog�� ���߿� if������ �Ÿ���
	//jebi_dialog("player 0 fail!");
	//jebi_dialog("player 0 pass!");
	jebi_display();
	jebi_note();
	while (1) {
		jebi_init();
		//draw();
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key == K_SPACE) {
			//(���� ���� or���� if�� ����
			jebi_dialog("player 0 fail!");
		}
		else if (key != K_UNDEFINED) {
			jebi_move_manual(key);
			draw();
		}
	}

	/*
	randjebi = randint(0, n_player - 1);
	for (int i = 0; i < n_player; i++) {
		if (randjebi == i) {
			jebi_result[i] = 1;
		}
		else {
			jebi_result[i] == 0;
		}
	}
	for (int i = 0; i < n_player; i++) {
		printf("%d ", jebi_result[i]);
	}
	*/
}