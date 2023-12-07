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
        // 旭精 切軒亜 蟹神檎 陥獣 持失
        px[i] = 2;
        py[i] = 2 + i;
        //@亜 薦搾研 識澱廃 妊獣昔汽 妊獣研 崇送食醤馬艦 @研 湛腰属拭 持失敗
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
    // 唖 号狽生稽 崇送析 凶 x, y葵 delta
    static int dx[4] = { -1, 1, 0, 0 };
    static int dy[4] = { 0, 0, -1, 1 };

    int jebi_switch_temp_1;
    int jebi_switch_temp_2 = NULL;
    int dir;  // 崇送析 号狽(0~3);
    switch (key) {
    case K_LEFT: dir = DIR_LEFT; jebi_move_stack -= 1; jebi_switch_temp_1 = 0; break;
    case K_RIGHT: dir = DIR_RIGHT; jebi_move_stack += 1; jebi_switch_temp_1 = 1; break;
    default: return;
    }
    // 崇送食辞 兜析 切軒
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
    } //松びびびびびびびびびびびびびびびびびびびびびびび降!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //袴軒亜 褐焼鎧形嬢嬢嬢嬢っ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //幻級形澗 坪球 : 戚 穿拭 脊径廃 葵引 薄仙 脊径葵戚 陥牽檎 鋼企鋼狽生稽 2牒梢 薪移醤馬澗 坪球
    smove_tail(0, nx, ny);
    if (jebi_switch_temp_1 != jebi_switch_temp_2) {
        jebi_switch_temp_1 = jebi_switch_temp_2;
    }
    else {
        jebi_move_stack += 2;
        jebi_switch_temp_1 = jebi_switch_temp_2;
    }
    back_buf[2][jebi_move_stack] = '?';
}

void jebi_move_tail(int player, int nx, int ny) {
    int p = player;  // 戚硯戚 掩嬢辞...
    back_buf[nx][ny] = back_buf[px[p]][py[p]];
    back_buf[px[p]][py[p]] = ' ';
    px[p] = nx;
    py[p] = ny;
}

//薦搾研 覗鍵闘庚生稽 幻球澗惟 限澗 杏猿 虞澗 持唖戚 糾.
//鎧亜 持唖廃 硝壱軒葬精 薦搾馬蟹 馬蟹税 疎妊(x,y)研 昔縦背辞 @稽 郊荷澗杏 持唖梅醸製.
void jebi_note(void) { //?窒径 坪球
    gotoxy(2, 2);
    /*for (int i = 0; i < n_alive; i++) { //巴傾戚嬢 呪 幻鏑 楕走 持失背醤敗)
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
    int jebi_chance_randint = randint(1, n_player); //詞焼 赤澗 紫寓 呪 掻拭 馬蟹研 薦搾 雁歎生稽 嗣奄 是廃 坪球
    jebi_init();
    jebi_display();
    //jebi_dialog("-層搾-"); //dialog澗 巨獄益 砺什闘 掻拭 暗十形辞 爽汐坦軒 背兜紹製.
    //購拭 jebi_dialog澗 蟹掻拭 if庚生稽 暗牽奄
    //jebi_dialog("player 0 fail!");
    //jebi_dialog("player 0 pass!");
    jebi_display();
    //jebi_note();
    while (1) {
        key_t key = get_key();
        if (key == K_QUIT) {
            break;
        }
        else if (key == K_SPACE) {
            //(薦搾 失因 or叔鳶 if庚 床奄
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