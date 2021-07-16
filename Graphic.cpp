#include <Graphic.h>
#include <Game.h>
#include <GL/freeglut.h>
#include <stack>
#include <math.h>

#define QUARTER PI / 2

std::stack<unsigned char> ConvertToStack(int value)
{
	std::stack<unsigned char> result;

	if(value == 0)
	{
		result.push('0');
	}else{
		while(value >= 1)
		{
			result.push(value % 10 + '0');
			value /= 10;
		}

	}
	return result;
}

//draw 16 rectangles
void fillRects()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//draw the left rectangle
	glColor3f(0.98, 0.98, 0.82);
	fillRect(6.0, 6.0, 211.0, 585.0, -1, 1.0);

	//draw the right rectangle
	glColor3f(0.98, 0.98, 0.82);
	fillRect(220.0, 6.0, 574.0, 585.0, -1, 1.0);

	//draw the smaller rectangle inside the right one
	glColor3f(0.65, 0.65, 0.65);
	fillRect(283.0, 98.0, 440.0, 440.0, -1, 1.0);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			switch(a[i][j])
			{
				case 0:
					glColor3f(0.65, 0.65, 0.65);
					break;

				case 2:
					glColor3f(0.95, 0.95, 0.95);
					break;

				case 4:
					glColor3f(1.0, 0.87, 0.67);
					break;

				case 8:
					glColor3f(1.0, 0.7, 0.5);
					break;

				case 16:
					glColor3f(0.99, 0.79, 0.67);
					break;

				case 32:
					glColor3f(1.0, 0.4, 0.3);
					break;

				case 64:
					glColor3f(1.0, 0.38, 0.17);
					break;

				case 128:
					glColor3f(0.4, 0.54, 0.54);
					break;

				case 256:
					glColor3f(0.8, 0.74, 0.43);
					break;

				case 512:
					glColor3f(0.74, 0.6, 0.38);
					break;

				case 1024:
					glColor3f(1.0, 0.5, 0.27);
					break;

				case 2048:
					glColor3f(0.8, 0.66, 0.49);
					break;

				case 4096:
					glColor3f(1.0, 0.38, 0.27);
					break;

				default:
					glColor3f(1.0, 1.0, 1.0);
					break;
			}

			fillRect(291.0 + j * 108.0, 106.0 + i * 108.0, 100.0, 100.0, a[i][j], 0.25);
		}
	}
}

//draw single rectangle
void fillRect(float x, float y, float width, float height, int value, float scale)
{
	//draw a little bit smaller rectangle
	glBegin(GL_POLYGON);
		glVertex2f(x + RADIUS, y);
		glVertex2f(x + RADIUS, y + height);
		glVertex2f(x + width - RADIUS, y + height);
		glVertex2f(x + width - RADIUS, y);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2f(x, y + RADIUS);
		glVertex2f(x, y + height - RADIUS);
		glVertex2f(x + width, y + height - RADIUS);
		glVertex2f(x + width, y + RADIUS);
	glEnd();
	//--------------------------------------------//

	//draw a quarter of round shape in 4 corners
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x + width - RADIUS, y + height - RADIUS);
		for (int i = 0; i <= TRIANGLE_NUMBER; ++i)
			glVertex2f(x + width - RADIUS + RADIUS * cos(i * QUARTER / TRIANGLE_NUMBER), y + height - RADIUS + RADIUS * sin(i * QUARTER / TRIANGLE_NUMBER));
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x + RADIUS, y + height - RADIUS);
		for (int i = 0; i <= TRIANGLE_NUMBER; ++i)
			glVertex2f(x + RADIUS + RADIUS * cos(i * QUARTER / TRIANGLE_NUMBER + QUARTER), y + height - RADIUS + RADIUS * sin(i * QUARTER / TRIANGLE_NUMBER + QUARTER));
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x + RADIUS, y + RADIUS);
		for (int i = 0; i <= TRIANGLE_NUMBER; ++i)
			glVertex2f(x + RADIUS + RADIUS * cos(i * QUARTER / TRIANGLE_NUMBER + 2 * QUARTER), y + RADIUS + RADIUS * sin(i * QUARTER / TRIANGLE_NUMBER + 2 * QUARTER));
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x + width - RADIUS, y + RADIUS);
		for (int i = 0; i <= TRIANGLE_NUMBER; ++i)
			glVertex2f(x + width - RADIUS + RADIUS * cos(i * QUARTER / TRIANGLE_NUMBER + 3 * QUARTER), y + RADIUS + RADIUS * sin(i * QUARTER / TRIANGLE_NUMBER + 3 * QUARTER));
	glEnd();

	//--------------------------------------------//

	//depend on its value, set the appopriate string color to match with background color
	if(value == 2 || value == 4 || value == 16)
		glColor3f(0.0, 0.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1.0);

	glLineWidth(3.0);

	if(value != 0)
		fillNumber(x + width / 2, y + height / 2, scale, value);
}

//split every digit of number then push into stack
void fillNumber(float x, float y, float scale, int number)
{
	std::stack<unsigned char> display_number = ConvertToStack(number);
	glPushMatrix();

	//translate the x_axis by the number of digits centerlize the number
	glTranslatef(x - 100.0 / 1.5 * scale * display_number.size() / 2, y - 50.0 * scale, 0.0);
	glScalef(scale, scale, scale);
	while(!display_number.empty())
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, display_number.top());
		display_number.pop();
	}
	glPopMatrix();
}