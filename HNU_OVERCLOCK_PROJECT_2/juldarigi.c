#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

int px[PLAYER_MAX], py[PLAYER_MAX];

void juldarigi_init(void);

void juldarigi_init(void) {
	map_init_sharp(3, 29);
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
		do {
			x = N_ROW - 2;
			do {
				y = randint(1, N_COL - 2);
			} while (N_COL - 20 <= y && y <= N_COL - 8);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}

	tick = 0;
}

void juldarigi(void) {
	juldarigi_init();
	display();
	dialog(" -준비- ");
}

/*
void sample_init(void);
void smove_manual(key_t key);
void smove_random(int i, int dir);
void smove_tail(int i, int nx, int ny);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기

void sample_init(void) {
	map_init(15, 40);
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
		do {
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}

	tick = 0;
}

void smove_manual(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
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
	if (!placable(nx, ny)) {
		return;
	}

	smove_tail(0, nx, ny);
}

// 0 <= dir < 4가 아니면 랜덤
void smove_random(int player, int dir) {
	int p = player;  // 이름이 길어서...
	int nx, ny;  // 움직여서 다음에 놓일 자리
	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	
	do {
		nx = px[p] + randint(-1, 1);
		ny = py[p] + randint(-1, 1);
	} while (!placable(nx, ny));

	smove_tail(p, nx, ny);
}

// back_buf[][]에 기록
void smove_tail(int player, int nx, int ny) {
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

void sample(void) {
	sample_init();
	system("cls");
	display();
	while (1) {
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			smove_manual(key);
		}
		// player 1 부터는 랜덤으로 움직임(8방향)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				smove_random(i, -1);
			}
		}
		display();
		Sleep(10);
		tick += 10;
	}
}
*/