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
double str = 0, str_r = 0, str_l = 0, tmp_str;
bool stop_or_go; //더 땡길지 말지 정하는 신호
int r_skill = 1, l_skill = 1;

void juldarigi_init(void); //줄다리기 인트로
void print_str(void); //str 출력
void juldarigi_move_tail(int i, int nx, int ny); //줄다리기용 move_tail
void move_tail_for_line(int line, int nx, int ny); //줄다리기 '-' 전용 move_tail
void juldarigi_right(void); //오른쪽으로 당기는 함수
void juldarigi_left(void); //왼쪽으로 당기는 함수
void left_skill(void);
void right_skill(void);

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
	stop_or_go = true;
	tick = 0;
}

void print_str(void) {
	str = 0;
	str_r = 0;
	str_l = 0;
	for (int i = 0; i < n_player; i++) {
		if (i % 2 == 0) {
			str_r += player[i].str;
		}
		if (i % 2 == 1) {
			str_l += player[i].str;
		}
	}
	str = (-str_r) + str_l;
	gotoxy(N_ROW + 1, 0);
	printf("str:%5.1f", tmp_str);
}

bool juldarigi_placable(int y) {
	if (y == 6 || y == 22) {
		return false;
	}
	else {
		return true;
	}
}

void juldarigi_move_tail(int player, int nx, int ny) {
	int p = player;
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

void move_tail_for_line(int line, int nx, int ny) {
	int l = line;
	back_buf[nx][ny] = back_buf[lx[l]][ly[l]];
	back_buf[lx[l]][ly[l]] = ' ';
	lx[l] = nx;
	ly[l] = ny;
}

void juldarigi_right(void) {
	int nx, ny;
	if (stop_or_go == true) {
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
			move_tail_for_line(i, nx, ny);
		}
	}
	for (int i = 0; i <= n_player - 2; i += 2) {
		nx = px[i] + 0;
		ny = py[i] + 1;
		if (ny == 14) {
			stop_or_go = false;
			gotoxy(N_ROW + 1, 0);
			continue;
		}
		juldarigi_move_tail(i, nx, ny);
	}
}

void juldarigi_left(void) {
	int nx, ny;
	if (stop_or_go == true) {
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
	}
	for (int i = 1; i <= n_player-1; i += 2) {
		nx = px[i] + 0;
		ny = py[i] - 1;
		if (ny == 14) {
			stop_or_go = false;
			gotoxy(N_ROW + 1, 0);
			continue;
		}
		juldarigi_move_tail(i, nx, ny);
	}
}

void left_skill(void) {
	for (int i = 0; i <= n_player - 2; i += 2) {
		player[i].str *= 2;
		gotoxy(N_ROW, 0);
		printf("짝수팀 눕기 사용!");
	}
}

void right_skill(void) {
	for (int i = 1; i <= n_player - 1; i += 2) {
		player[i].str *= 2;
		gotoxy(N_ROW, 0);
		printf("홀수팀 눕기 사용!");
	}
}

void juldarigi(void) {
	juldarigi_init();
	print_str();
	tmp_str = str;
	display();
	dialog(" -준비- ");
	while (1) {
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key == K_STR_DOWN) {
			tmp_str -= 1;
		}
		else if (key == K_STR_UP) {
			tmp_str += 1;
		}
		else if (key == K_L_SKILL) {
			left_skill();
			l_skill = 2;
		}
		else if (key == K_R_SKILL) {
			right_skill();
			r_skill = 2;
		}
		print_str();
		if (tick % 3000 == 0) {
			if (tmp_str > 0) {
				if (r_skill == 2) {
					juldarigi_right();
					juldarigi_right();
					r_skill = 1;
					for (int i = 1; i <= n_player - 1; i += 2) {
						player[i].str /= 2;
					}
				}
				else {
					juldarigi_right();
				}
				tick = 0;
			}
			else if (tmp_str < 0) {
				if (l_skill == 2) {
					juldarigi_left();
					juldarigi_left();
					l_skill = 1;
					for (int i = 0; i <= n_player - 2; i += 2) {
						player[i].str /= 2;
					}
				}
				else {
					juldarigi_left();
				}
				tick = 0;
			}
		}
		Sleep(10);
		tick += 10;
		display();
	}
}