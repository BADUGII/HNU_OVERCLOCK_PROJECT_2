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
        // 같은 자리가 나오면 다시 생성
        px[i] = 2;
        py[i] = 2 + i;
        //@가 제비를 선택한 표시인데 표시를 움직여야하니 @를 첫번째에 생성함
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
//제비를 프린트문으로 만드는게 맞는 걸까 라는 생각이 듦.
//내가 생각한 알고리즘은 제비하나 하나의 좌표(x,y)를 인식해서 @로 바꾸는걸 생각했었음.
void jebi_move_manual(key_t key) {
    // 각 방향으로 움직일 때 x, y값 delta
    static int dx[4] = { -1, 1, 0, 0 };
    static int dy[4] = { 0, 0, -1, 1 };

    int dir;  // 움직일 방향(0~3);
    switch (key) {
    case K_LEFT: dir = DIR_LEFT; jebi_move_stack -= 1; jebi_flag_temp = 0; break; //0이 왼쪽
    case K_RIGHT: dir = DIR_RIGHT; jebi_move_stack += 1; jebi_flag_temp = 1; break; //1이 오른쪽
    default: return;
    }
    // 움직여서 놓일 자리
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
    //만들려는 코드 : 이 전에 입력한 값과 현재 입력값이 다르면 반대반향으로 2칸씩 옮겨야하는 코드
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
    int p = player;  // 이름이 길어서...
    back_buf[nx][ny] = back_buf[px[p]][py[p]];
    back_buf[px[p]][py[p]] = ' ';
    px[p] = nx;
    py[p] = ny;
}

int jebi_pass_player = 0;
int jebi_round = 0;
int jebi_player_stack = 0;
void jebi(void) {
    int jebi_chance_randint = randint(1, n_alive); //살아 있는 사람 수 중에 하나를 제비 당첨으로 뽑기 위한 코드
    jebi_init();
    jebi_display(jebi_round, jebi_player_stack);
    //jebi_dialog("-준비-"); //dialog는 디버그 테스트 중에 거슬려서 주석처리 해놓았음.
    while (1) {
        key_t key = get_key(); //get_key 에서 space를 인식 못함
        if (key == K_QUIT) {
            break;
        }
        else if (key == K_SPACE) {
            //(제비 성공 or실패 if문 쓰기
            if (jebi_move_stack != jebi_chance_randint) {
                jebi_dialog("player pass!");//
                jebi_mia();
                while (1) {
                    jebi_player_stack += 1;
                    if (jebi_player_stack == 10) {
                        jebi_player_stack = 0;
                        break;
                    }
                    if (player[jebi_player_stack].is_alive == true) {
                        break;
                    }
                }

                jebi_display(jebi_round, jebi_player_stack);
            }
            else {
                jebi_dialog("player fail!"); //실패할때 마다 n_alive하나씩 없어짐.
                player[jebi_player_stack].is_alive = false;
                n_alive -= 1;
                jebi_round += 1;
                jebi_chance_randint = randint(1, n_alive);
                jebi_mia();
                while (1) {
                    jebi_player_stack += 1;
                    if (jebi_player_stack == n_alive) {
                        jebi_player_stack = 0;
                        break;
                    }
                    if (player[jebi_player_stack].is_alive == true) {
                        break;
                    }
                }
                jebi_display(jebi_round, jebi_player_stack);
                if (n_alive == 1) {
                    jebi_dialog("Game End!");
                    break;
                }
            }
        }
        else if (key != K_UNDEFINED) {
            jebi_move_manual(key);
            draw();
        }
        tick += 10;
    }
}