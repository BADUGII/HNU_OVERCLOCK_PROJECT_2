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
	// �ɷ�ġ: ����, ��, ���¹̳�
	int intel, str, stamina;
	// ���� ����
	bool is_alive; // Ż�������� false
	bool hasitem; // �������� ������ true
	bool pass;
	ITEM item; // ������ 1�� ���� ����
} PLAYER;

PLAYER player[PLAYER_MAX]; // �⺻�� true, Ż���ϸ� false => player[i].is_alive

//bool player[PLAYER_MAX];
int n_player, n_alive, n_alive_arr[PLAYER_MAX], winner_player;
int n_item;
int tick;  // �ð�
int skill_tick;
int stop_tick;
bool yh_stop;

// �̴ϰ���
void sample(void);
void mugunghwa(void);
//void nightgame(void);
void juldarigi(void);
void jebi(void);

int randint(int low, int high);

#endif