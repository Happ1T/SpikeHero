#ifndef TEST1_CONST_H
#define TEST1_CONST_H
#include <iostream>
#include <math.h>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

// dir
const int left_dir= 1;
const int right_dir= 0;
const int up_dir = 2;

//ADVENTURE
const int WIDTH_OF_PLAYER = 26;
const int HEIGHT_OF_PLAYER = 30; // make always +7
const int WIDTH_ATTACK_ADVENTURE=38;
const int HEIGTH_ATTACK_ADVENTURE=30;
const float ATTACK_ANIMATION=0.01;
const float SPEED_ANIMATION = 0.01;
const float SPEED_ADVENTURER = 0.15;

float DAMAGE = 25;
//SKELETON
const int HEIGHT_OF_SKELETON = 32;
const int WIDTH_OF_SKELETON = 24;
const float SPEED_SKELETON_ANIMATION=0.01;
const float SPEED_SKELETON = 0.02;
const int HEIGHT_OF_SKELETON_ATTACK = 37;
const int WIDTH_OF_SKELETON_ATTACK = 40;

//map
const int HEIGHT_MAP = 34;
const int WIDTH_MAP = 80;
const int CENTER = 400;

//size block
const int SIZE_OF_BLOCK = 16;

//size hp
const int WIDTH_HP=89;
const int HEIDTH_HP=17;
float ZOOM=1;
//screen
float WIDTH_SCREEN = 640;
float HEIGHT_SCREEN = 360;
float WIDTH_CAMERA= WIDTH_SCREEN/4;
float HEIGHT_CAMERA=HEIGHT_SCREEN/4 ;
float three_four=(WIDTH_CAMERA/(SIZE_OF_BLOCK*4));
float LEFT_LINE  = (SIZE_OF_BLOCK)*((WIDTH_CAMERA/(2*SIZE_OF_BLOCK)-three_four+1));
float RIGHT_LINE =(WIDTH_MAP-((WIDTH_CAMERA/(2*SIZE_OF_BLOCK)+three_four+1)))*SIZE_OF_BLOCK;
const int GROUND = HEIGHT_MAP*SIZE_OF_BLOCK;
const float DEFAULT_WIDTH_SCREEN=1920;
const float DEFAULT_HEIGHT_SCREEN=1080;

//razr
const int r1920x1080 = 1;
const int r1600x900 = 2;
const int r1440x900 = 3;
const int r1280x720 = 4;
const int r640x360 = 5;

//speed

const float JUMP_RANGE = -0.2;


//animation


const float TIME_ATTACK = 800;

unsigned short PORT1 = 6948; // 6 = P , 9 = I, 4 = D, 8 = R.            (PIDR mod(10))

//port


#endif//TEST1_CONST_H
