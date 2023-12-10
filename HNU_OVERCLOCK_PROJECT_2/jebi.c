#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_LEFT   2
#define DIR_RIGHT   3

void jebi_init(void);
void jebi_move_manual(key_t key);
void jebi_move_tail(int i, int nx, int ny);
void jebi(void);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];
int nb = 2;

int randjebi;
int jebi_result[PLAYER_MAX];
int jebi_move_stack = 1;

void jebi_init(void) {
    map_init(5, 18);
    int x, y;
    for (int i = 0; i < n_player; i++) {
        // ���� �ڸ��� ������ �ٽ� ����
        px[i] = 2;
        py[i] = 2 + i;
        //@�� ���� ������ ǥ���ε� ǥ�ø� ���������ϴ� @�� ù��°�� ������
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

int jebi_flag = 1;
int jebi_flag_temp = 1;
//���� ����Ʈ������ ����°� �´� �ɱ� ��� ������ ��.
//���� ������ �˰����� �����ϳ� �ϳ��� ��ǥ(x,y)�� �ν��ؼ� @�� �ٲٴ°� �����߾���.
void jebi_move_manual(key_t key) {
    // �� �������� ������ �� x, y�� delta
    static int dx[4] = { -1, 1, 0, 0 };
    static int dy[4] = { 0, 0, -1, 1 };

    int dir;  // ������ ����(0~3);
    switch (key) {
    case K_LEFT: dir = DIR_LEFT; jebi_move_stack -= 1; jebi_flag_temp = 0; break; //0�� ����
    case K_RIGHT: dir = DIR_RIGHT; jebi_move_stack += 1; jebi_flag_temp = 1; break; //1�� ������
    default: return;
    }
    // �������� ���� �ڸ�
    int nx, ny;
    nx = px[0] + dx[dir];
    ny = py[0] + dy[dir];
    if (placable(nx, ny)) {
        if (dir == DIR_LEFT) {
            jebi_move_stack += 1;
        }else if(dir == DIR_RIGHT) {
            jebi_move_stack -= 1;
        }
        return;
    }
    //������� �ڵ� : �� ���� �Է��� ���� ���� �Է°��� �ٸ��� �ݴ�������� 2ĭ�� �Űܾ��ϴ� �ڵ�
    smove_tail(0, nx, ny);
    if (jebi_flag_temp != jebi_flag) {
        if (jebi_flag_temp == 0) {
            jebi_move_stack += 2;
        }
        else if (jebi_flag_temp == 1) {
            jebi_move_stack -= 2;
        }
        jebi_flag = jebi_flag_temp;
    }
    else {
        jebi_flag_temp = jebi_flag;
    }
    back_buf[2][jebi_move_stack] = '?';
}

void jebi_move_tail(int player, int nx, int ny) {
    int p = player;  // �̸��� ��...
    back_buf[nx][ny] = back_buf[px[p]][py[p]];
    back_buf[px[p]][py[p]] = ' ';
    px[p] = nx;
    py[p] = ny;
}

int jebi_pass_player = 0;
int jebi_round = 0;
void jebi(void) {
    int jebi_chance_randint = randint(1, n_alive); //��� �ִ� ��� �� �߿� �ϳ��� ���� ��÷���� �̱� ���� �ڵ�
    jebi_init();
    jebi_display(jebi_round, jebi_pass_player);
    //jebi_dialog("-�غ�-"); //dialog�� ����� �׽�Ʈ �߿� �Ž����� �ּ�ó�� �س�����.
    while (1) {
        key_t key = get_key(); //get_key ���� space�� �ν� ����
        if (key == K_QUIT) {
            break;
        }
        else if (key == K_SPACE) {
            //(���� ���� or���� if�� ����
            if (jebi_move_stack == jebi_chance_randint) {
                jebi_dialog("player pass!");
                jebi_pass_player += 1;
                jebi_round += 1;
                jebi_mia();
                jebi_display(jebi_round, jebi_pass_player);
            }
            else {
                jebi_dialog("player fail!");
                jebi_round += 1;
                jebi_mia();
                jebi_display(jebi_round, jebi_pass_player);
            }
        }
        else if (key != K_UNDEFINED) {
            jebi_move_manual(key);
            draw();
        }
        tick += 10;
    }
}