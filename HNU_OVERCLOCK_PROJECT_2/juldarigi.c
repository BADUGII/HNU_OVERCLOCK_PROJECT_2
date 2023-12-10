#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <stdbool.h>

#define	DATA_FILE	"jjuggumi.dat"

#define DIR_S_UP	0
#define DIR_S_DOWN	1
#define L_SKILL	2
#define R_SKILL	3

int px[PLAYER_MAX], py[PLAYER_MAX];
int lx[3], ly[3];
double str = 0, str_r = 0, str_l = 0;

void juldarigi_init(void);
void print_str(void);
void juldarigi_key_manual(void);
void juldarigi_right(void);
void juldarigi_left(void);
void juldarigi_line(void);
void juldarigi_move_tail(int i, int nx, int ny);
void move_tail_for_line(int line, int nx, int ny);

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
		back_buf[lx[i]][ly[i]] = '-';
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
			str_r += player[i].str;
		}
		if (i % 2 == 1) {
			str_l += player[i].str;
		}
	}
	str = str_r - str_l;
	printf("\n\n\n\nstr:%5.1f\n\n", str);
}

bool juldarigi_placable(int y) {
	if (y == 0 || y == 28) {
		return false;
	}
	else {
		return true;
	}
}

void move_tail_for_line(int line, int nx, int ny) {
	int l = line;
	back_buf[nx][ny] = back_buf[lx[l]][ly[l]];
	back_buf[lx[l]][ly[l]] = ' ';
	lx[l] = nx;
	ly[l] = ny;
}

void juldarigi_key_manual(void) {

}

void juldarigi_right(void) {
	int nx, ny;
	for (int i = n_player - 1; i > 0; i -= 2) {
		nx = px[i] + 0;
		ny = py[i] + 1;
		if (juldarigi_placable(ny) == false) {
			break;
		}
		juldarigi_move_tail(i, nx, ny);
	}
	for (int i = 2; i >= 0; i--) {
		nx = lx[i] + 0;
		ny = ly[i] + 1;
		if (!placable(nx, ny)) {
			break;
		}
		move_tail_for_line (i, nx, ny);
	}
	for (int i = 0; i <= n_player - 2; i += 2) {
		nx = px[i] + 0;
		ny = py[i] + 1;
		if (!placable(nx, ny)) {
			break;
		}
		juldarigi_move_tail(i, nx, ny);
	}
}

void juldarigi_left(void) {
	int nx, ny;
	for (int i = n_player - 2; i >= 0; i -= 2) {
		nx = px[i] + 0;
		ny = py[i] - 1;
		if (juldarigi_placable(ny) == false) {
			break;
		}
		juldarigi_move_tail(i, nx, ny);
	}
	for (int i = 0; i < 3; i++) {
		nx = lx[i] + 0;
		ny = ly[i] - 1;
		if (!placable(nx, ny)) {
			break;
		}
		move_tail_for_line(i, nx, ny);
	}
	for (int i = 1; i <= n_player - 1; i += 2) {
		nx = px[i] + 0;
		ny = py[i] - 1;
		if (!placable(nx, ny)) {
			break;
		}
		juldarigi_move_tail(i, nx, ny);
	}
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

		if (tick / 3000 == 1) {
			if (str > 0) {
				juldarigi_right();
				tick = 0;
			}
			else if (str < 0) {
				juldarigi_left();
				tick = 0;
			}
		}
		Sleep(10);
		tick += 10;
		display();
	}
}