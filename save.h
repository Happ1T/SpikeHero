//
// Created by Honor MagicBook Pro on 30.05.2022.
//

#ifndef TEST1_SAVE_H
#define TEST1_SAVE_H
#include <stdio.h>
#include "hero.h"
#include "consts.h"
#include "view.h"
#include "entity.h"
#include "enemy.h"
#include "levl.h"
#include "bars.h"
#include "menu.h"
#include "game.h"



FILE *stream_save, *stream_up;
bool save(float &x, float &y, int &hp, int player) {
    stream_save = fopen("game/save/save", "w+");
    if (!stream_save) return false;
    fprintf(stream_save, "%f %f %d", x, y, hp);
    fclose(stream_save);
    return true;


}
bool upload(float &x, float &y, int &hp, int player){
    stream_up = fopen("game/save/save", "r");
    if (!stream_up) return false;
    for (int i = 1; i <= player; i++) fscanf(stream_up, "%f %f %d", &x,&y,&hp);
    fclose(stream_up);
    return true;
}
#endif //TEST1_SAVE_H
