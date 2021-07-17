#ifndef _GAME_
#define _GAME_

#include <string>
#include <array>

#define PI 3.14
#define FPS 100
#define WIDTH 800
#define HEIGHT 600
#define POS_X 200
#define POS_Y 200

extern std::array<std::array<int, 5>, 5> a;	//save the following state
extern std::array<std::array<int, 5>, 5> b;	//save the previous state
extern int score;	//current score
extern bool end;
extern unsigned char title1[10];
extern unsigned char title2[10];
extern unsigned char title3[10];
extern const char* GAME_TITLE;

void InitWindow(int argc, char** argv);

void LeftHandler();
void RightHandler();
void UpHandler();
void DownHandler();

void AddNewValue();
void Keyboard_recognize(int key, int, int);

bool GameOver();

#endif