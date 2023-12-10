#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#define PLAYER_MAX		10
#define ITEM_MAX        10

typedef struct {
	char name[100];
	int intel_buf, str_buf, stamina_buf;
} ITEM;
ITEM item[ITEM_MAX];

typedef struct {
	int id; //player[i].id
	char name[100];
	// 능력치: 지능, 힘, 스태미나
	int intel, str, stamina;
	// 현재 상태
	bool is_alive; // 탈락했으면 false
	bool hasitem; // 아이템이 있으면 true
	bool pass;
	ITEM item; // 아이템 1개 장착 가능
} PLAYER;

PLAYER player[PLAYER_MAX]; // 기본값 true, 탈락하면 false => player[i].is_alive

//bool player[PLAYER_MAX];
int n_player, n_alive, n_alive_arr[PLAYER_MAX], winner_player;
int n_item;
int tick;  // 시계
int skill_tick;
int stop_tick;
bool yh_stop;

// 미니게임
void sample(void);
void mugunghwa(void);
//void nightgame(void);
void juldarigi(void);
void jebi(void);

int randint(int low, int high);

#endif