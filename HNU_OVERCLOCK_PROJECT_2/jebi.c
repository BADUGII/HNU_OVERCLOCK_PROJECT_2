#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_LEFT	2
#define DIR_RIGHT	3

void jebi_init(void);
void jebi_move_manual(key_t key);
void jebi_move_tail(int i, int nx, int ny);


int px[PLAYER_MAX], py[PLAYER_MAX];
int nb = 2;

int randjebi;
int jebi_result[PLAYER_MAX];

void jebi_init(void) {
	if (n_player == 10) {
		map_init(5, 32);
	}
	else if (n_player == 9) {
		map_init(5, 29);
	}
	else if (n_player == 8) {
		map_init(5, 26);
	}
	else if (n_player == 7) {
		map_init(5, 23);
	}
	else if (n_player == 6) {
		map_init(5, 20);
	}
	else if (n_player == 5) {
		map_init(5, 17);
	}
	else if (n_player == 4) {
		map_init(5, 14);
	}
	else if (n_player == 3) {
		map_init(5, 11);
	}
	else if (n_player == 2) {
		map_init(5, 8);
	}
	else if (n_player == 1) {
		printf("error");
	}
	else if (n_player == 0) {
		printf("error");
	}

	int x, y;
	x = 2;
	y = 2;
	px[0] = x;
	py[0] = y;
	back_buf[px[0]][py[0]] = '0';
	draw();
}
void jebi_move_manual(key_t key) {
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key) {
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// 움직여서 놓일 자리
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	

	jebi_move_tail(0, nx, ny);
}

void jebi_move_tail(int player , int nx, int ny) {
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
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
	while (1) {
		jebi_init();
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			jebi_move_manual(key);
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