#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_S_UP	0
#define DIR_S_DOWN	1
#define L_SKILL	2
#define R_SKILL	3

int px[PLAYER_MAX], py[PLAYER_MAX];
int str = 1;

void juldarigi_init(void);
void juldarigi_move_manual(key_t key);
void juldarigi_move_random(int i, int dir);
void juldarigi_move_tail(int i, int nx, int ny);

void juldarigi_move_manual(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key) {
	case K_STR_UP: dir = DIR_S_UP; break;
	case K_STR_DOWN: dir = DIR_S_DOWN; break;
	case K_L_SKILL: dir = L_SKILL; break;
	case K_R_SKILL: dir = R_SKILL; break;
	default: return;
	}

	// 움직여서 놓일 자리
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}

	juldarigi_move_tail(0, nx, ny);
	for (int i = 1; i < n_player; i++) {
		juldarigi_move_random(i, -1);
	}
}

void juldarigi_move_random(int player, int dir) {
	int p = player;  // 이름이 길어서...
	int nx = 0, ny = 0;  // 움직여서 다음에 놓일 자리
	int random_xy = 0;
	int percent = 0;
	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)
	do {
		
		switch (random_xy) {
		case 1: nx = px[p] + 0, ny = py[p] + +1; break; //뒤로
		case 2: nx = px[p] + 0, ny = py[p] + -1; break; //앞으로
		}
	} while (!placable(nx, ny));

	juldarigi_move_tail(p, nx, ny);
}

void juldarigi_move_tail(int player, int nx, int ny) {
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

void juldarigi_init(void) {
	map_init_sharp(3, 29);
	int x, y, t1 = 17, t2 = 13;

	for (int i = 0; i < 3; i++) {
		x = 0 + i;
		y = 14;
		px[i] = x;
		py[i] = y;
		back_buf[px[i]][py[i]] = ' ';
	}

	for (int i = 0; i < 3; i++) {
		x = 1;
		y = 13+i;
		px[i] = x;
		py[i] = y;
		back_buf[px[i]][py[i]] = '-';
	}

	for (int i = 0; i < n_player; i++) {
		x = N_ROW - 2;
		if (i % 2 == 0) {
			y = N_COL - t1;
			t1++;
		}
		else {
			y = N_COL - t2;
			t2--;
		}
		px[i] = x;
		py[i] = y;

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
	printf("\n\n\n\nstr:%5d\n\n", str);
	tick = 0;
}

void juldarigi(void) {
	juldarigi_init();
	display();
	dialog(" -준비- ");
	while (1) {
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			juldarigi_move_manual(key);
		}
	}
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