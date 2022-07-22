#ifndef TEST1_ENTITY_H
#define TEST1_ENTITY_H
#include "levl.h"
using namespace std;

class Entity {
private:
public:

    vector<Object>obj;
    float dx, dy, frame, speed, x, y, speed_animation, move_timer, timer_attack = 0;
    int  width, width_attack, height, height_attack, health, height_simple, damage = 0,width_simple;
    bool dir, flag, is_attack = false, is_damage = false, is_ground = true, life = true, is_agr = false;;

    String name;
    Sprite sprite;

    Entity(float X, float Y, int W,int H, String Name, Texture &texture){
        width = W;
        height = H;
        x = X;
        y = Y;
        name = Name;
        sprite.setTexture(texture);

    }
    FloatRect getRect(bool is_attack, int razn){
       if  (is_attack) { return FloatRect(x-razn, y, width_attack, height); }
       else            { return FloatRect(x, y, width_simple, height); }
    }



    virtual void update(float time) = 0;


};


#endif //TEST1_ENTITY_H
