// ConsoleApplication3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include<GL/glut.h>
//#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

#define GL_BGR eaf5be
#define pi (3.14)

#define CUBE (0)
#define ELIPSE (1)
#define	BOTH (2)

#define X (0)
#define Y (1)

float size_cube = 0.5;
float size_elipse = 0.5;
float color_cube[3];
float color_elipse[3];
float pos_cube[3];
float pos_elipse[3];
int angle_cube[2];
int angle_elipse[2];
int timer = 0;
int state = CUBE;
int rotating_state = 0;

int xpos, ypos;

void init(void)
{
	pos_cube[0] = 1.0;
	pos_cube[1] = 0.0;
	pos_cube[2] = 1.0;
	pos_elipse[0] = -1.0;
	pos_elipse[1] = 0.0;
	pos_elipse[2] = 0.0;

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 20.2, 20.0, 30.0, 0.0 };
	glClearColor(0.72, 0.73, 0.85, 0.3); //screen's color
	glShadeModel(GL_FLAT);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void mouse(int x, int y)
{
	xpos = x;
	ypos = y;

	glutPostRedisplay();
}

void timer_func(int a)
{
	if (timer < 350) {
		timer++;
	}

	glutPostRedisplay();
	glutTimerFunc(25, timer_func, a);
}

void drawAxes()
{
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glPopMatrix();

	glBegin(GL_LINES);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	glVertex3f(0.0f, -10.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
}

void drawParalelepiped(float size)
{
	glTranslatef(pos_cube[0], pos_cube[1], pos_cube[2]);
	glColor3f(color_cube[0], color_cube[1], color_cube[2]);
	glPushMatrix();
	glPopMatrix();

	glRotatef(angle_cube[0], 1.0, 0.0, 0.0);
	glRotatef(angle_cube[1], 0.0, 1.0, 0.0);
	int a = -1, b = -2;
	double c = 0.5;
	glBegin(GL_QUADS);
	//front
	glNormal3f(0.0f, 0.0f, size);
	glVertex3f(a*size, b*size, c*size);
	glVertex3f(c*size, b*size, c*size);
	glVertex3f(c*size, c*size, c*size);
	glVertex3f(a*size, c*size, c*size);
	//back
	glNormal3f(0.0f, 0.0f, -1.0*size);
	glVertex3f(a*size, b*size, -c*size);
	glVertex3f(a*size, c*size, -c*size);
	glVertex3f(c*size, c*size, -c*size);
	glVertex3f(c*size, b*size, -c*size);
	//top
	glNormal3f(0.0f, 1.0*size, 0.0f);
	glVertex3f(a*size, c*size, -c*size);
	glVertex3f(a*size, c*size, c*size);
	glVertex3f(c*size, c*size, c*size);
	glVertex3f(c*size, c*size, -c*size);
	//bottom
	glNormal3f(0.0f, -1.0*size, 0.0f);
	glVertex3f(a*size, b*size, -c*size);
	glVertex3f(c*size, b*size, -c*size);
	glVertex3f(c*size, b*size, c*size);
	glVertex3f(a*size, b*size, c*size);
	//right
	glNormal3f(1.0*size, 0.0f, 0.0f);
	glVertex3f(c*size, b*size, -c*size);
	glVertex3f(c*size, c*size, -c*size);
	glVertex3f(c*size, c*size, c*size);
	glVertex3f(c*size, b*size, c*size);
	//left
	glNormal3f(-1.0*size, 0.0f, 0.0f);
	glVertex3f(a*size, b*size, -c*size);
	glVertex3f(a*size, b*size, c*size);
	glVertex3f(a*size, c*size, c*size);
	glVertex3f(a*size, c*size, -c*size);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawEllipsoid(float size) {
	glTranslatef(pos_elipse[0], pos_elipse[1], pos_elipse[2]);
	glRotatef(angle_elipse[0], 1.0, 0.0, 0.0); //view from 30 degree
	glRotatef(angle_elipse[1], 0.0, 1.0, 0.0);
	glColor3f(color_elipse[0], color_elipse[1], color_elipse[2]);
	glPushMatrix();
	glPopMatrix();
	glBegin(GL_LINE_STRIP);
	float x, y, z;
	for (float i = 0; i < 360; i = i + 0.1)
	{
		x = size * 2 * sin(i);
		y = size * cos(i);
		z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glBegin(GL_TRIANGLE_STRIP);
	float x1, y1, z1;
	for (float i = -pi / 2; i < pi / 2; i = i + 0.1)
	{
		for (float j = -pi; j < pi; j = j + 0.1)
		{
			x = size * 2 * cos(j)*cos(i);
			y = size*sin(j)*cos(i);
			z = size *sin(i);
			glVertex3f(x, y, z);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 4.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	glScalef(1.0, 1.0, 1.0);

	drawAxes();

	//DRAWING CUBE
	glPushMatrix();
	//rotate to get the right perspective
	glRotatef(1.0, 5.0, 0.0, 0.0);
	drawParalelepiped(size_cube);
	glPopMatrix();

	//DRAWING Elipse
	glPushMatrix();
	//rotate to get the right perspective
	glRotatef(1.0, 3.0, 0.0, 0.0);
	drawEllipsoid(size_elipse);
	glPopMatrix();
	glFlush();
}

void rotate_cube_global_axes(int axis, int direction)
{
	float angle_x, angle_y, radius;
	if (axis == Y)
	{
		radius = sqrt(pos_cube[0] * pos_cube[0] + pos_cube[2] * pos_cube[2]);
		if (radius == 0)
		{
			angle_cube[1] += direction;
			return;
		}
		angle_x = acos(pos_cube[0] / radius);
		angle_x += direction*pi / 180;
		pos_cube[0] = radius*cos(angle_x);
		pos_cube[2] = radius*sin(angle_x);
		std::cout << pos_cube[2] << std::endl;
	}
	else
	{
		radius = sqrt(pos_cube[1] * pos_cube[1] + pos_cube[2] * pos_cube[2]);
		if (radius == 0)
		{
			angle_cube[0] += direction;
			return;
		}
		angle_y = acos(pos_cube[1] / radius);
		angle_y += direction*pi / 180;
		pos_cube[1] = radius*cos(angle_y);
		pos_cube[2] = radius*sin(angle_y);
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);

}
void rotate_elipse_global_axes(int axis, int direction)
{
	float angle_x, angle_y, radius;
	if (axis == Y)
	{
		radius = sqrt(pos_elipse[0] * pos_elipse[0] + pos_elipse[2] * pos_elipse[2]);
		if (radius == 0)
		{
			angle_elipse[1] += direction;
			return;
		}
		angle_x = acos(pos_elipse[0] / radius);
		angle_x += direction*pi / 180;
		pos_elipse[0] = radius*cos(angle_x);
		pos_elipse[2] = radius*sin(angle_x);
		std::cout << pos_elipse[2] << std::endl;
	}
	else
	{
		radius = sqrt(pos_elipse[1] * pos_elipse[1] + pos_elipse[2] * pos_elipse[2]);
		if (radius == 0)
		{
			angle_elipse[0] += direction;
			return;
		}
		angle_y = acos(pos_elipse[1] / radius);
		angle_y += direction*pi / 180;
		pos_elipse[1] = radius*cos(angle_y);
		pos_elipse[2] = radius*sin(angle_y);
	}
}

void keyboard(unsigned char key, int x, int y)
{

switch (key)
{
case 'c': state = CUBE; break;
case 'e': state = ELIPSE; break;
case 'b': state = BOTH; break;
case 'r':
	if (rotating_state == 0) rotating_state = 1;
	else rotating_state = 0;
	break;
case '+':
	switch (state)
	{
	case CUBE:
		if (size_cube <= 1)
			size_cube += 0.1;
		break;
	case ELIPSE:
		if (size_elipse <= 1)
			size_elipse += 0.1;
		break;
	case BOTH:
		if (size_cube <= 1)
			size_cube += 0.1;
		if (size_elipse <= 1)
			size_elipse += 0.1;
		break;
	}
	break;
case '-':
	switch (state)
	{
	case CUBE:
		if (size_cube >= 0.2)
			size_cube -= 0.1;
		break;
	case ELIPSE:
		if (size_elipse >= 0.2)
			size_elipse -= 0.1;
		break;
	case BOTH:
		if (size_cube >= 0.2)
			size_cube -= 0.1;
		if (size_elipse >= 0.2)
			size_elipse -= 0.1;
		break;
	}
	break;
case 'w':
	if (rotating_state == 0)
	{
		switch (state)
		{
		case CUBE: angle_cube[0]++; break;
		case ELIPSE: angle_elipse[0]++; break;
		case BOTH: angle_cube[0]++; angle_elipse[0]++; break;
		}
	}
	else
	{
		switch (state)
		{
		case CUBE: rotate_cube_global_axes(X, 1); break;
		case ELIPSE: rotate_elipse_global_axes(X, 1); break;
		case BOTH: rotate_cube_global_axes(X, 1); rotate_elipse_global_axes(X, 1); break;
		}
	}
	break;
case 's':
	if (rotating_state == 0)
	{
		switch (state)
		{
		case CUBE: angle_cube[0]--; break;
		case ELIPSE: angle_elipse[0]--; break;
		case BOTH: angle_cube[0]--; angle_elipse[0]--; break;
		}
	}
	else
	{
		switch (state)
		{
		case CUBE: rotate_cube_global_axes(X, -1); break;
		case ELIPSE: rotate_elipse_global_axes(X, -1); break;
		case BOTH: rotate_cube_global_axes(X, -1); rotate_elipse_global_axes(X, -1); break;
		}
	}
	break;
case 'd':
	if (rotating_state == 0)
	{
		switch (state)
		{
		case CUBE: angle_cube[1]++; break;
		case ELIPSE: angle_elipse[1]++; break;
		case BOTH: angle_cube[1]++; angle_elipse[1]++; break;
		}
	}
	else
	{
		switch (state)
		{
		case CUBE: rotate_cube_global_axes(Y, 1); break;
		case ELIPSE: rotate_elipse_global_axes(Y, 1); break;
		case BOTH: rotate_cube_global_axes(Y, 1); rotate_elipse_global_axes(Y, 1); break;
		}
	}
	break;
case 'a':
	if (rotating_state == 0)
	{
		switch (state)
		{
		case CUBE: angle_cube[1]--; break;
		case ELIPSE: angle_elipse[1]--; break;
		case BOTH: angle_cube[1]--; angle_elipse[1]--; break;
		}
	}
	else
	{
		switch (state)
		{
		case CUBE: rotate_cube_global_axes(Y, -1); break;
		case ELIPSE: rotate_elipse_global_axes(Y, -1); break;
		case BOTH: rotate_cube_global_axes(Y, -1); rotate_elipse_global_axes(Y, -1); break;
		}
	}
	break;
}
}

void skeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		switch (state)
		{
		case CUBE: pos_cube[1] -= 0.1; break;
		case ELIPSE: pos_elipse[1] -= 0.1; break;
		case BOTH: pos_cube[1] -= 0.1; pos_elipse[1] -= 0.1; break;
		}
		break;
	case GLUT_KEY_UP:
		switch (state)
		{
		case CUBE: pos_cube[1] += 0.1; break;
		case ELIPSE: pos_elipse[1] += 0.1; break;
		case BOTH: pos_cube[1] += 0.1; pos_elipse[1] += 0.1; break;
		}
		break;
	case GLUT_KEY_LEFT:
		switch (state)
		{
		case CUBE: pos_cube[0] -= 0.1; break;
		case ELIPSE: pos_elipse[0] -= 0.1; break;
		case BOTH: pos_cube[0] -= 0.1; pos_elipse[0] -= 0.1; break;
		}
		break;
	case GLUT_KEY_RIGHT:
		switch (state)
		{
		case CUBE: pos_cube[0] += 0.1; break;
		case ELIPSE: pos_elipse[0] += 0.1; break;
		case BOTH: pos_cube[0] += 0.1; pos_elipse[0] += 0.1; break;
		}
		break;
	}

}


void set_color()
{

		color_cube[0] = 0.5; color_cube[1] = 0.2; color_cube[2] = 0.8;
		color_elipse[0] = 0.8; color_elipse[1] = 0.1; color_elipse[2] = 0.2;
	
}

int main(int argc, char** argv)
{
	set_color();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(skeyboard);
	glutReshapeFunc(reshape);

	glutTimerFunc(25, timer_func, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	return 0;
}
