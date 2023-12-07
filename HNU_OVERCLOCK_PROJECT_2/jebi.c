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
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
		px[i] = 2;
		py[i] = 2 + i;
		//@가 제비를 선택한 표시인데 표시를 움직여야하니 @를 첫번째에 생성함.
		if (i == 0) {
			back_buf[px[i]][py[i]] = '@';
		}
		else {
			back_buf[px[i]][py[i]] = '?';
		}
	}
	tick = 0;
	draw();
}

void jebi_move_manual(key_t key) {
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

void jebi_move_tail(int player , int nx, int ny) {
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

 //제비를 프린트문으로 만드는게 맞는 걸까 라는 생각이 듦.
//내가 생각한 알고리즘은 제비하나 하나의 좌표(x,y)를 인식해서 @로 바꾸는걸 생각했었음.
void jebi_note(void) { //?출력 코드
	gotoxy(2, 2);
	/*for (int i = 0; i < n_alive; i++) { //플레이어 수 만큼 쪽지 생성해야함)
		printf("?");
	}*/
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
	int jebi_chance_randint = randint(1, n_player); //살아 있는 사람 수 중에 하나를 제비 당첨으로 뽑기 위한 코드
	jebi_init();
	jebi_display();
	//jebi_dialog("-준비-"); //dialog는 디버그 테스트 중에 거슬려서 주석처리 해놓았음.
	//밑에 jebi_dialog는 나중에 if문으로 거르기
	//jebi_dialog("player 0 fail!");
	//jebi_dialog("player 0 pass!");
	jebi_display();
	//jebi_note();
	while (1) {
		//draw();
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key == K_SPACE) {
			//(제비 성공 or실패 if문 쓰기
			jebi_dialog("player 0 fail!");
		}
		else if (key != K_UNDEFINED) {
			jebi_move_manual(key);
			draw();
		}
		tick += 10;
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