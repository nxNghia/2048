#include <iostream>
#include <math.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define PI 3.1415
#define FPS 100

using namespace std;

char character = 'q'; 
unsigned char title_1[10] = "Score", title_2[12] = "High Score";
int a[5][5], b[5][5], score, high_score;
float x = 0.0, y = 1.0;
bool Continue = true;

void Generate();
void Hor_reverse();
void Ver_reverse();
void Hor(int n);
void Ver(int n);
void timer_callback(int);
void init();
void draw_graphic();
void Generate();
void display();
void keyboard_callback(int key, int, int);
void Cpy(unsigned char* source,unsigned char* des);
void draw_rect(float x, float y, float width, float height, float radius);
bool GoodToPlay();
bool OkToGenerate();
unsigned char* Convert(int n);
int Length(unsigned char*);

int main (int argc, char **argv)
{
	//Doc highscore tu file .txt co san
	fstream fp;
	fp.open("HighScore.txt");
	fp >> high_score;
	fp.close();

	srand(time(NULL));
	Generate();
	
	glutInit (&argc, argv);							//5 cau lenh de bat dau thao tac voi openGL
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutCreateWindow ("Game(demo)");

	glutDisplayFunc (display);
	glutTimerFunc(0, timer_callback, 0);		//Loop
	glutSpecialFunc(keyboard_callback);		//Ham dung de nhan biet phim da nhan tu keyboard
	init();			//Khoi tao
	glutMainLoop();
	
	return 0;
}

void display()		
{
	//drawVietnamFlag();
	draw_graphic();
	glFlush();
	glutSwapBuffers();
}

void timer_callback(int)		//Ham set thoi gian lap
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer_callback, 0);
}

void keyboard_callback(int key, int, int)		//Ham xu li khi nhan duoc gia tri cua phim da nhan tu keyboard
{
	switch(key)
	{
		case GLUT_KEY_UP:		//Neu nhan mui ten len thi xu li theo chieu doc
			Ver(0);
			break;

		case GLUT_KEY_DOWN:		//Neu nhan mui ten xuong thi xu li theo chieu doc
			Ver(1);
			break;

		case GLUT_KEY_RIGHT:	//Neu nhan mui ten phai thi xu li theo chieu ngang
			Hor(1);
			break;

		case GLUT_KEY_LEFT:		//Neu nhan mui ten trai thi xu li theo chieu ngang
			Hor(0);
			break;
	}

	if(score > high_score)
		high_score = score;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			b[i][j] = a[i][j];
}

void init (void)
{
	glClearColor (0.17, 0.17, 0.17, 1.0);		//Set mau nen
	glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void draw_graphic()
{
	GLfloat quarter = PI / 2;
	int radius = 5;
	int triangleamout = 10;
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0.98, 0.98, 0.82);
	draw_rect(6.0, 6.0, 211.0, 585.0, 5.0);
	glColor3f(0.85 * x + 0.98 * y, 0.8 * x + 0.98 * y, 0.4 * x + 0.82 * y);
	draw_rect(220.0, 6.0, 574.0, 585.0, 5.0);

	//Tao hinh vuong to bao tron 16 hinh vuong nho
	glColor3f(0.65 * y + 0.85 * x, 0.65 * y + 0.8 * x, 0.65 * y + 0.4 * x);	//Set mau cua hinh vuong to
	draw_rect(283.0, 98.0, 440.0, 440.0, 5.0);

	Ver_reverse();		//Dao mang tran theo chieu doc
	for (float i = 291.0; i < 685.0; i += 108.0)
	{
		for (float j = 106.0; j < 500.0; j += 108.0)
		{
			//Danh sach mau cua o dua theo gia tri ma o do bieu dien
			switch(a[(int)(j - 102.0) / 103][(int)(i - 287.0) / 103])
			{
				case 0:	//Neu o do bang 0 thi no co mau giong vs mau nen
					glColor3f(0.85 * x + 0.65 * y, 0.8 * x + 0.65 * y, 0.4 * x + 0.65 * y);
					break;

				case 2:
					glColor3f(0.85 * x + 0.95 * y, 0.8 * x + 0.95 * y, 0.4 * x + 0.95 * y);
					break;

				case 4:
					glColor3f(0.85 * x + 1.0 + y, 0.8 * x + 0.87 * y, 0.4 * x + 0.67 * y);
					break;

				case 8:
					glColor3f(0.85 * x + 1.0 * y, 0.8 * x + 0.7 * y, 0.4 * x + 0.5 * y);
					break;

				case 16:
					glColor3f(0.85 * x + 0.99 * y, 0.8 * x + 0.79 * y, 0.4 * x + 0.67 * y);
					break;

				case 32:
					glColor3f(0.85 * x + 1.0 * y, 0.8 * x + 0.4 * y, 0.4 * x + 0.3 * y);
					break;

				case 64:
					glColor3f(0.85 * x + 1.0 * y, 0.8 * x + 0.38 * y, 0.4 * x + 0.17 * y);
					break;

				case 128:
					glColor3f(0.85 * x + 0.4 * y, 0.8 * x + 0.54 * y, 0.4 * x + 0.54 * y);
					break;

				case 256:
					glColor3f(0.85 * x + 0.8 * y, 0.8 * x + 0.74 * y, 0.4 * x + 0.43 * y);
					break;

				case 512:
					glColor3f(0.85 * x + 0.74 * y, 0.8 * x + 0.6 * y, 0.4 * x + 0.38 * y);
					break;

				case 1024:
					glColor3f(0.85 * x + 1.0 * y, 0.8 * x + 0.5 * y, 0.4 * x + 0.27 * y);
					break;

				case 2048:
					glColor3f(0.85 * x + 0.8 * y, 0.8 * x + 0.66 * y, 0.4 * x + 0.49 * y);
					break;

				case 4096:
					glColor3f(0.85 * x + 1.0 * y, 0.8 * x + 0.38 * y, 0.4 * x + 0.27 * y);
					break;
			}

			//Ve lan luot 16 o
			draw_rect(i, j, 100.0, 100.0, 5.0);
		}
	}

	//Khai bao bien buffer duoi dang char de co the hien thi len man hinh
	unsigned char* buffer = (unsigned char*)malloc(10*sizeof(unsigned char));
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			//Cai dat mau cua mot vai gia tri dac biet
			if(a[i][j] != 2 && a[i][j] != 4 && a[i][j] != 16)
				glColor3f(0.85 * x + 1.0 * y, 0.8 * x + 1.0 * y, 0.4 * x + 1.0 * y);
			else
				glColor3f(0.85 * x, 0.8 * x, 0.4 * x);

			buffer = Convert(a[i][j]);	//Ham convert() chuyen bien int thanh dang char sau do tra ve dia chi cua char do

			glPushMatrix();
			glLineWidth(3.0);
			//Ham set vi tri hien thi gia tri cua o do
			glTranslatef(206.0 + 108.0 * j + 135.0 - (float)Length(buffer) * 11.5, 106.0 + 108.0 * i + 37.5, 0.0);
			glScalef(0.3, 0.3, 0.3);
			//Hien thi xau bieu dien gia tri cua o do
			if(a[i][j] != 0)
				for (int i = 0; i < Length(buffer); ++i)
					glutStrokeCharacter(GLUT_STROKE_ROMAN, *(buffer + i));
			glPopMatrix();
		}
	}
	Ver_reverse();

	//Tao o de hien thi so diem hien tai
	glLineWidth(1.0);
	glColor3f(0.65, 0.65, 0.65);		//Set mau cua o
	draw_rect(36.5, 263.0, 135.0, 125.0, 5.0);
	glColor3f(1.0, 1.0, 1.0);	//Set mau chu
	glRasterPos2f(60.0, 350.0);		//Set vi tri viet diem trong o do

	glutBitmapString(GLUT_BITMAP_HELVETICA_18, title_1);

	buffer = Convert(score);
	/*glRasterPos2f(105.0 - (float)((Length(buffer) - 1.0) / 2) * 10.0, 460.0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);*/

	glPushMatrix();
	glTranslatef(105.0 - (float)Length(buffer) * 9.25, 302.0, 0.0);
	glScalef(0.25, 0.25, 0.25);
	for (int i = 0; i < Length(buffer); ++i)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *(buffer + i));
	glPopMatrix();

	//Tao o de hien thi highscore
	glColor3f(0.65, 0.65, 0.65);	//Set mau o
	draw_rect(36.5, 98.0, 135.0, 125.0, 5.0);

	glColor3f(1.0, 1.0, 1.0);	//Set color
	glRasterPos2f(60.0, 185.0);		//Set vi tri de viet
	buffer = Convert(high_score);	//Convert highscore tu dang int sang dang char
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, title_2);

	glPushMatrix();
	glTranslatef(105.0 - (float)Length(buffer) * 9.25, 137.0, 0.0);
	glScalef(0.25, 0.25, 0.25);

	for (int i = 0; i < Length(buffer); ++i)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *(buffer + i));
	glPopMatrix();

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

	free(buffer);

	if(Continue)
	{
		if(!GoodToPlay())
		{
			if(score > high_score)
			{
				ofstream fp;
				fp.open("HighScore.txt");
				fp << score;
				fp.close();
			}
			Continue = false;
			x = 0.75;
			y = 0.25;
		}
	}else{
		unsigned char end[20] = "GAME OVER";
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(WIDTH / 2 - 50.0, HEIGHT / 2, 0.0);
		glScalef(0.4, 0.4, 0.4);

		for (int i = 0; i < Length(end); ++i)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, end[i]);

		glPopMatrix();
	}
}

void Ver_reverse()		//Ham dao ma tran theo chieu doc
{
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 2; ++i)
		{
			int temp = a[i][j];
			a[i][j] = a[3 - i][j];
			a[3 - i][j] = temp;
		}
	}
}

void Hor_reverse()		//Ham dao ma tran theo chieu ngang
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			int temp = a[i][j];
			a[i][j] = a[i][3 - j];
			a[i][3 - j] = temp;
		}
	}
}

bool OkToGenerate()		//Ham kiem tra xem co the sinh so ngau nhien duoc hay khong
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if(b[i][j] != a[i][j])
				return true;

	return false;
}

void Hor(int n)
{
	if(n == 1)		//Neu n = 1 tuc xu li theo chieu ngang nhung la sang phai => reverse ma tran roi xu li nhu sang trai
		Hor_reverse();

	for (int i = 0; i < 4; ++i)
	{
		int t = 0;
		for (int j = 0; j < 4; ++j)
		{
			if(a[i][j] != 0)
			{
				int temp = a[i][j];
				a[i][j] = 0;
				if(a[i][t] == 0)
				{
					a[i][t] = temp;
				}else{
					if(a[i][t] == temp)
					{
						a[i][t++] += temp;
						score += 2 * temp;
					}else{
						a[i][++t] = temp;
					}
				}
			}
		}
	}

	if(n == 1)
		Hor_reverse();		//Neu don so cuong duoi thi sau khi xu li thi reverse lai ma tran

	if(OkToGenerate())		//Check xem co the sinh so ngau nhien nua hay khong
		Generate();
}

void Ver(int n)
{
	if(n == 1)	//Neu n = 1 tuc xu li theo chieu doc nhung la di xuong => reverse ma tran roi xu li nhu di len
		Ver_reverse();

	for (int j = 0; j < 4; ++j)
	{
		int t = 0;
		for (int i = 0; i < 4; ++i)
		{
			if(a[i][j] != 0)
			{
				int temp = a[i][j];
				a[i][j] = 0;
				if(a[t][j] == 0)
				{
					a[t][j] = temp;
				}else{
					if(a[t][j] == temp)
					{
						a[t++][j] += temp;
						score += 2 * temp;
					}else{
						a[++t][j] = temp;
					}
				}
			}
		}
	}

	if(n == 1)
		Ver_reverse();		//Neu don so cuong duoi thi sau khi xu li thi reverse lai ma tran

	if(OkToGenerate())		//Check xem co the sinh so ngau nhien nua hay khong
		Generate();
}

unsigned char* Convert(int n)	//Chuyen int thanh char
{
	unsigned char* str = (unsigned char*)malloc(10*sizeof(unsigned char));
	int k = 0;

	if(n == 0)
	{
		*str = '0';
		*(str + 1) = '\0';
		return str;
	}

	while(n >= 1)
	{
		*(str + k) = n % 10 + '0';
		++k;
		n /= 10;
	}

	*(str + k) = '\0';

	for (int i = 0; i < k / 2; ++i)
	{
		char temp = *(str + i);
		*(str + i) = *(str + k - 1 - i);
		*(str + k - 1 - i) = temp;
	}

	return str;
}

bool GoodToPlay()	//Ham xac dinh xem game co the choi tiep hay khong
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if(a[i][j] == 0 || a[i][j] == a[i-1][j] || a[i][j] == a[i + 1][j] || a[i][j] == a[i][j - 1] || a[i][j] == a[i][j + 1])
				return true;

	return false;
}

void Generate()		//Ham sinh so ngau nhien tai vi tri trong ngau nhien
{
	int x, y;

	do
	{
		x = rand() % 4;
		y = rand() % 4;
	}while(a[x][y] != 0);

	a[x][y] = 2 * (rand() % 2 + 1);
}

int Length(unsigned char* str)
{
	int i = 0;
	while(*(str + i) != '\0')
		++i;

	return i;
}

void Cpy(unsigned char* source, unsigned char* des)
{
	int i = 0;
	do
	{
		*(des + i) = *(source + i);
		++i;
	}while(*(source + i) != '\0');
	*(des + i) = '\0';
}

//Ve hinh vuong voi goc tron
void draw_rect(float x, float y, float width, float height, float radius)
{
	int triangleamount = 20;
	float quarter = PI / 2;

	glBegin(GL_POLYGON);
		glVertex2f(x + radius, y + radius);
		glVertex2f(x + radius, y + height - radius);
		glVertex2f(x + width - radius, y + height - radius);
		glVertex2f(x + width - radius, y + radius);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x + width - radius, y + height - radius);
		for (int i = 0; i <= triangleamount; ++i)
			glVertex2f(x + width - radius + radius * cos(i * quarter / triangleamount), y + height - radius + radius * sin(i * quarter / triangleamount));
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x + radius, y + height - radius);
		for (int i = 0; i <= triangleamount; ++i)
			glVertex2f(x + radius + radius * cos(i * quarter / triangleamount + quarter), y + height - radius + radius * sin(i * quarter / triangleamount + quarter));
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x + radius, y + radius);
		for (int i = 0; i <= triangleamount; ++i)
			glVertex2f(x + radius + radius * cos(i * quarter / triangleamount + 2 * quarter), y + radius + radius * sin(i * quarter / triangleamount + 2 * quarter));
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x + width - radius, y + radius);
		for (int i = 0; i <= triangleamount; ++i)
			glVertex2f(x + width - radius + radius * cos(i * quarter / triangleamount + 3 * quarter), y + radius + radius * sin(i * quarter / triangleamount + 3 * quarter));
	glEnd();

	glLineWidth(radius);
	glBegin(GL_LINES);
		glVertex2f(x + radius / 2, y + radius);
		glVertex2f(x + radius / 2, y + height - radius);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(x + radius, y + height - radius / 2);
		glVertex2f(x + width - radius, y + height - radius / 2);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(x + width - radius / 2, y + height - radius);
		glVertex2f(x + width - radius / 2, y + radius);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(x + width - radius, y + radius / 2);
		glVertex2f(x + radius, y + radius / 2);
	glEnd();
}

/*g++ test.cpp -o test -lglut -lGLU -lGL
void drawVietnamFlag()
{
	int triangleAmount = 20;
	int radius1 = 60;
	double radius2 = radius1 * (cos(3 * PI / 10) * sin(2 * PI / 5) / cos(2 * PI / 5) + sin(3 * PI / 10));

	GLfloat twicePi = 2.0f * PI;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(WIDTH / 2, HEIGHT / 2);
		for (int i = 0; i <= triangleAmount; ++i)
			glVertex2f(WIDTH / 2 + (radius1 * cos(i * twicePi / triangleAmount + 3 * PI / 10)), HEIGHT / 2 + (radius1 * sin(i * twicePi / triangleAmount + 3 * PI / 10)));
	glEnd();

	/*for (int i = 0; i <= triangleAmount; ++i)
	{
		glBegin(GL_POLYGON);
			glVertex2f(WIDTH / 2 + radius2 * cos(i * twicePi / triangleAmount + PI / 2), HEIGHT / 2 + radius2 * sin(i * twicePi / triangleAmount + PI / 2));
			glVertex2f(WIDTH / 2 + radius1 * cos(i * twicePi / triangleAmount + 3 * PI / 10), HEIGHT / 2 + radius1 * sin(i * twicePi / triangleAmount + 3 * PI / 10));
			glVertex2f(WIDTH / 2 + radius1 * cos((i + 1) * twicePi / triangleAmount + 3 * PI / 10), HEIGHT / 2 + radius1 * sin((i + 1) * twicePi / triangleAmount + 3 * PI / 10));
		glEnd();
	}
}*/