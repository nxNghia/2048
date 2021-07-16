#include <Game.h>
#include <time.h>
#include <stdlib.h>
#include <Graphic.h>
#include <GL/freeglut.h>
#include <iostream>

int a[5][5];
int b[5][5];
int score = 0;
bool end = false;
unsigned char title3[10] = "GAME OVER";
unsigned char title1[10] = "SCORE";
const char* GAME_TITLE = "2048";

void display();
void timer(int);
void init();

void InitWindow(int argc, char** argv)
{
	AddNewValue();

	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(POS_X, POS_Y);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow(GAME_TITLE);

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutSpecialFunc(Keyboard_recognize);
	init();
	glutMainLoop();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//draw 16 squares//
	fillRects();
	//-----------------------------------------------------//

	//write score//
	glLineWidth(1.0);
	glColor3f(0.65, 0.65, 0.65);
	fillRect(36.5, 263.0, 135.0, 125.0, score, 0.3);

	glRasterPos2f(60.0, 350.0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, title1);
	//-----------------------------------------------------//

	//write 2048//
	glLineWidth(5.0);
	glPushMatrix();
	glTranslatef(15.0, 450.0, 0.0);
	glScalef(0.6, 0.6, 0.6);
	glColor3f(1.0, 0.0, 0.0);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, '2');
	glColor3f(0.85, 0.85, 0.0);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
	glColor3f(0.0, 1.0, 0.0);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, '4');
	glColor3f(0.0, 0.0, 1.0);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, '8');
	glPopMatrix();
	//-----------------------------------------------------//

	if(!end)
	{
		end = GameOver();
	}else{
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(350.0, 300);
		glScalef(2.0, 2.0, 2.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, title3);
	}
	glFlush();
	glutSwapBuffers();
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

void init(void)
{
	glClearColor (0.17, 0.17, 0.17, 1.0);
	glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

//handle left event//
void LeftHandler()
{
	int t = 0;
	for (int i = 0; i < 4; ++i)
	{
		t = 0;
		for (int j = 0; j < 4; ++j)
		{
			if (a[i][j] != 0)
			{
				int tmp = a[i][j];
				a[i][j] = 0;
				if(a[i][t] == 0)
				{
					a[i][t] = tmp;
				}else{
					if(a[i][t] == tmp)
					{
						a[i][t++] += tmp;
						score += tmp * 2;
					}else{
						a[i][++t] = tmp;
					}
				}
			}
		}
	}
}

//handle right event
void RightHandler()
{
	int t = 3;
	for (int i = 3; i >= 0; --i)
	{
		t = 3;
		for (int j = 3; j >= 0; --j)
		{
			if (a[i][j] != 0)
			{
				int tmp = a[i][j];
				a[i][j] = 0;
				if(a[i][t] == 0)
				{
					a[i][t] = tmp;
				}else{
					if(a[i][t] == tmp)
					{
						a[i][t--] += tmp;
						score += tmp * 2;
					}else{
						a[i][--t] = tmp;
					}
				}
			}
		}
	}
}

//handle up event
void UpHandler()
{
	int t = 0;
	for (int j = 3; j >= 0; --j)
	{
		t = 3;
		for (int i = 3; i >= 0; --i)
		{
			if (a[i][j] != 0)
			{
				int tmp = a[i][j];
				a[i][j] = 0;
				if(a[t][j] == 0)
				{
					a[t][j] = tmp;
				}else{
					if(a[t][j] == tmp)
					{
						a[t--][j] += tmp;
						score += tmp * 2;
					}else{
						a[--t][j] = tmp;
					}
				}
			}
		}
	}
}

//handle down event
void DownHandler()
{
	int t = 3;
	for (int j = 0; j < 4; ++j)
	{
		t = 0;
		for (int i = 0; i < 4; ++i)
		{
			if(a[i][j] != 0)
			{
				int tmp = a[i][j];
				a[i][j] = 0;
				if(a[t][j] == 0)
				{
					a[t][j] = tmp;
				}else{
					if(a[t][j] == tmp)
					{
						a[t++][j] += tmp;
						score += 2 * tmp;
					}else{
						a[++t][j] = tmp;
					}
				}
			}
		}
	}
}

//check if there is any avalable position for new value
//by compare two state a and b, determined if there is any change in posion of values
//if not => not add new value
bool AvalableForNewValue()
{
	bool begin = true;	//check if player pressed the button for the first time or not
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			if (a[i][j] != b[i][j])
				return true;

			if(a[i][j] != 0)
				begin = false;
		}

	//if begin = true, user hasn't played the game so return true for adding the first value into the game
	return begin || false;
}

//add new value in avalable position
void AddNewValue()
{
	if(!AvalableForNewValue())
	{
		return;
	}

	int x;
	int y;

	//get coordinates continuously until we get an avalable position 

	do
	{
		x = rand() % 4;
		y = rand() % 4;
	}while(a[x][y] != 0);

	//if found, then assign its value to 2 or 4 (need improve)
	a[x][y] = (rand() % 2 + 1) * 2;
}


void Keyboard_recognize(int key, int, int)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			UpHandler();
			AddNewValue();
			break;

		case GLUT_KEY_DOWN:
			DownHandler();
			AddNewValue();
			break;

		case GLUT_KEY_RIGHT:
			RightHandler();
			AddNewValue();
			break;

		case GLUT_KEY_LEFT:
			LeftHandler();
			AddNewValue();
			break;
	}

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			b[i][j] = a[i][j];
}

//game over if there isn't any pair of the same value squares by horizontal or vertical
bool GameOver()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if(a[i][j] == 0 || a[i][j] == a[i-1][j] || a[i][j] == a[i+1][j] || a[i][j] == a[i][j+1] || a[i][j] == a[i][j-1])
				return false;

	return true;
}