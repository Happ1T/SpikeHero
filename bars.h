//
// Created by Honor MagicBook Pro on 17.05.2022.
//

#ifndef TEST1_BARS_H
#define TEST1_BARS_H
#include "consts.h"
#include "view.h"
#include "entity.h"
#include "levl.h"
#include <SFML/Graphics.hpp>


class Bars {
public:
    Texture health_t;
    Sprite health_s;
    int max,Hp;
    RectangleShape health;

    Bars(){

        health_t.loadFromFile("game/texture/player/hpBar_adventurer.png");
        health_s.setTexture(health_t);
        health.setFillColor(Color(0,0,0));
        max=100;
    }
    void update(int hp)
    {
        if(hp>=0 && hp<max){
            health.setSize(Vector2f(1.5*(max-hp),14));
            Hp=hp*1.5;}
    }
    void draw(RenderWindow &window)
    {
        Vector2f center=window.getView().getCenter();
        Vector2f size=window.getView().getSize();
        health_s.setPosition(center.x - size.x/2 , center.y - size.y / 2+5);
        health.setPosition(center.x - size.x/2 +Hp, center.y - size.y / 2 +5);
        health_s.setTextureRect(IntRect(0,16,150,15));
        window.draw(health_s);
        window.draw(health);
        health_s.setTextureRect(IntRect(0,0,150,15));
        window.draw(health_s);
    }
};


#endif //TEST1_BARS_H
