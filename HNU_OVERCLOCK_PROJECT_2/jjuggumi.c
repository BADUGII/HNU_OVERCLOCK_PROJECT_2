// 2023-2 ������α׷��� ����: �޲ٹ� ����
// 2023 �޲ٹ� 2.0 ��ŸƮ 2023
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"

#define	DATA_FILE	"jjuggumi.dat"

int old_jjuggumi_init(void);
//int jjuggumi_init(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

n_player_trigger = 0;

int old_jjuggumi_init(void) {
	system("cls");
	srand((unsigned int)time(NULL));
	printf("�޲ٹ� ���� �ִ� �÷��̾� : %d\n", PLAYER_MAX);
	printf("�÷��̾� �� : ");
	scanf_s("%d", &n_player);
	if (n_player <= PLAYER_MAX) { //PLAYER_MAX �� = 10
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
		return -1; // -1 �����ϸ� �����Լ����� ó���ϰ� ����
	}
	// �÷��̾� ������ load
	fscanf_s(fp, "%d", &n_player);
	for (int i = 0; i < n_player; i++) {
		// ���� �� ��� ����(����ü ������, ��������������)
		PLAYER* p = &player[i];
		// ���Ͽ��� �� ���� �ִ� �б�
		fscanf_s(fp, "%s%d%d",
			p->name, (unsigned int)sizeof(p->name),
			&(p->intel), &(p->str));
		p->stamina = 100; // 100%
		// ���� ����
		p->is_alive = true;
		p->hasitem = false;
	}
	// ������ ������ load
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
