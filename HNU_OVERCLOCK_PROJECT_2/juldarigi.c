#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define	DATA_FILE	"jjuggumi.dat"

#define DIR_S_UP	0
#define DIR_S_DOWN	1
#define L_SKILL	2
#define R_SKILL	3

int px[PLAYER_MAX], py[PLAYER_MAX];
int lx[3], ly[3];
double str, str1 = 0, str2 = 0;

void juldarigi_init(void);
void print_str(void);
void juldarigi_key_manual(void);
void juldarigi_right(void);
void juldarigi_left(void);
void juldarigi_line(void);
void juldarigi_move_tail(int i, int nx, int ny);

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
		lx[i] = x;
		ly[i] = y;
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
	tick = 0;
}

void print_str(void) {
	for (int i = 0; i < n_player; i++) {
		if (i % 2 == 0) {
			str1 += player[i].str;
		}
		if (i % 2 == 1) {
			str2 += player[i].str;
		}
	}
	str = str1 - str2;
	printf("\n\n\n\nstr:%5.1f\n\n", str);
}
void juldarigi_key_manual(void) {
	
}

void juldarigi_right(void) {
	for (int i = 8; i >= 0; i -= 2) {
		int nx, ny;
		nx = px[i] + 0;
		ny = py[i] + 1;
		if (!placable(nx, ny)) {
			return;
		}
		juldarigi_move_tail(i, nx, ny);
	}
	for (int i = 9; i >= 1; i -= 2) {
		int nx, ny;
		nx = px[i] + 0;
		ny = py[i] - 1;
		if (!placable(nx, ny)) {
			return;
		}
		juldarigi_move_tail(i, nx, ny);
	}
	for (int i = 9; i >= 1; i -= 2) {
		int nx, ny;
		nx = px[i] + 0;
		ny = py[i] - 1;
		if (!placable(nx, ny)) {
			return;
		}
		juldarigi_move_tail(i, nx, ny);
	}
	tick += 10;
}

void juldarigi_left(void) {
	for (int i = 9; i >= 1; i -= 2) {
		int nx, ny;
		nx = px[i] + 0;
		ny = py[i] - 1;
		if (!placable(nx, ny)) {
			return;
		}
		juldarigi_move_tail(i, nx, ny);
	}
	tick += 10;
}

void juldarigi_line(void) {

}

void juldarigi_move_tail(int player, int nx, int ny) {
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

void juldarigi(void) {
	juldarigi_init();
	//dialog(" -준비- ");
	print_str();
	display();
	while (1) {
		print_str();
		if (tick % 3000 == 0) {
			if (str > 0) {
				juldarigi_right();
			}
			else if (str < 0) {
				juldarigi_left();
			}
		}
		tick += 10;
		display();
		str = 0;
	}
}