#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

int px[PLAYER_MAX], py[PLAYER_MAX];
int x, y;
int nb = 2;

void jebi(void) {
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
	for (int i = 0; i < n_player; i++) {
		x = 2;
		y = i+nb;
		px[i] = x;
		py[i] = y;
		back_buf[px[i]][py[i]] = '?';
		nb += 2;
	}
	draw();
}