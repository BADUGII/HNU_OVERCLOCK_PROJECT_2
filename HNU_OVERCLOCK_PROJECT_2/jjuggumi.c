// 2023-2 고급프로그래밍 과제: 쭈꾸미 게임
// 2023 쭈꾸미 2.0 스타트 2023
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"

#define	DATA_FILE	"jjuggumi.dat"

int old_jjuggumi_init(void);
//int jjuggumi_init(void);

// low 이상 high 이하 난수를 발생시키는 함수
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

n_player_trigger = 0;

int old_jjuggumi_init(void) {
	system("cls");
	srand((unsigned int)time(NULL));
	printf("쭈꾸미 게임 최대 플레이어 : %d\n", PLAYER_MAX);
	printf("플레이어 수 : ");
	scanf_s("%d", &n_player);
	if (n_player <= PLAYER_MAX) { //PLAYER_MAX 값 = 10
		n_player_trigger = 0;
	}
	else {
		n_player_trigger =1;
	}
	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i].is_alive = true;
		n_alive_arr[i] = i;
	}
	system("cls");
	return 0;
}
/*
int jjuggumi_init() {
	srand((unsigned int)time(NULL));
	FILE* fp;
	fopen_s(&fp, DATA_FILE, "r");
	if (fp == NULL) {
		return -1; // -1 리턴하면 메인함수에서 처리하고 종료
	}
	// 플레이어 데이터 load
	fscanf_s(fp, "%d", &n_player);
	for (int i = 0; i < n_player; i++) {
		// 아직 안 배운 문법(구조체 포인터, 간접참조연산자)
		PLAYER* p = &player[i];
		// 파일에서 각 스탯 최댓값 읽기
		fscanf_s(fp, "%s%d%d",
			p->name, (unsigned int)sizeof(p->name),
			&(p->intel), &(p->str));
		p->stamina = 100; // 100%
		// 현재 상태
		p->is_alive = true;
		p->hasitem = false;
	}
	// 아이템 데이터 load
	fscanf_s(fp, "%d", &n_item);
	for (int i = 0; i < n_item; i++) {
		fscanf_s(fp, "%s%d%d%d",
			item[i].name, (unsigned int)sizeof(item[i].name),
			&(item[i].intel_buf),
			&(item[i].str_buf),
			&(item[i].stamina_buf));
	}
	fclose(fp);
	return 0;
}
*/

int main(void) {
	//intro();
	old_jjuggumi_init();
	if (n_player_trigger == 1) {
		outro_np();
		exit(0);
	}
	//sample();
	mugunghwa();
	//outro_p();	
	//nightgame();
	//juldarigi();
	//jebi();
	return 0;
}
