#include<gl/glut.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

#define MAX_FOOT_ANGLE 30
#define MIN_FOOT_ANGLE -30

#define MAX_HEAD_ANGLE 20
#define MIN_HEAD_ANGLE -20

#define MAX_TAIL_ANGLE 45
#define MIN_TAIL_ANGLE -45

#define MAX_WING_ANGLE 45
#define MIN_WING_ANGLE -15

float frame = 500;

float xt = 0.0f, yt = 0.0f, zt = 0.0f, xr = 0.0f, yr = 0.0f, zr = 0.0f, xrm = 0.0f, yrm = 0.0f, zrm = 0.0f, xAngle = 0.0f, yAngle = 0.0f, zAngle = 0.0f;
float tailAngle = 0.0f, footAngle = 0.0, earAngle = 0.0, headAngle = 0.0f, wingAngle = 0.0f;

float footRate = (MAX_FOOT_ANGLE - MIN_FOOT_ANGLE) / frame,
headRate = (MAX_HEAD_ANGLE - MIN_HEAD_ANGLE) / (frame * 2),
tailRate = (MAX_TAIL_ANGLE - MIN_TAIL_ANGLE) / (frame * 8),
wingRate = (MAX_WING_ANGLE - MIN_WING_ANGLE) / (frame);


bool reverseFoot = false;

void
Box(float width, float height, float depth, char solid)
{
	char i, j = 0;
	float x = width / 2.0, y = height / 2.0, z = depth / 2.0;

	for (i = 0; i < 4; i++) {
		glRotatef(90.0, 0.0, 0.0, 1.0);
		if (j) {
			if (!solid)
				glBegin(GL_LINE_LOOP);
			else
				glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-x, y, z);
			glVertex3f(-x, -y, z);
			glVertex3f(-x, -y, -z);
			glVertex3f(-x, y, -z);
			glEnd();
			if (solid) {
				glBegin(GL_TRIANGLES);
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(0.0, 0.0, z);
				glVertex3f(-x, y, z);
				glVertex3f(-x, -y, z);
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(0.0, 0.0, -z);
				glVertex3f(-x, -y, -z);
				glVertex3f(-x, y, -z);
				glEnd();
			}
			j = 0;
		}
		else {
			if (!solid)
				glBegin(GL_LINE_LOOP);
			else
				glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-y, x, z);
			glVertex3f(-y, -x, z);
			glVertex3f(-y, -x, -z);
			glVertex3f(-y, x, -z);
			glEnd();
			if (solid) {
				glBegin(GL_TRIANGLES);
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(0.0, 0.0, z);
				glVertex3f(-y, x, z);
				glVertex3f(-y, -x, z);
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(0.0, 0.0, -z);
				glVertex3f(-y, -x, -z);
				glVertex3f(-y, x, -z);
				glEnd();
			}
			j = 1;
		}
	}
}

void
disable(void)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_NORMALIZE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void
lighting(void)
{

	GLfloat position[] =
	{ 5.0, 5.0, 5.0, 0.7 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT, GL_FILL);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0);

	glTranslatef(5.0, 5.0, 5.0);
	glDisable(GL_LIGHTING);
	Box(0.1, 0.1, 0.1, 0);
	glEnable(GL_LIGHTING);
}

void drawFoot(char solid)
{
	float zTrans = -0.3, xTrans = -0.7, zScaleRot = -1;
	for (char i = 0; i < 4; i++)
	{
		zTrans = -zTrans;
		zScaleRot = -zScaleRot;
		if (i % 2 == 0)
		{
			xTrans = -xTrans;
		}
		glPushMatrix();
		glTranslatef(xTrans, -0.4, zTrans);
		glRotatef(footAngle, 0, 0, zScaleRot);
		glTranslatef(0.0, -0.3, 0.0);
		Box(0.3, 0.5, 0.25, solid);
		glPopMatrix();
	}
}

void drawWing(char solid)
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.4, 0.3, 0.35);
	glRotatef(wingAngle, -1, 0, 0);
	glTranslatef(0.0, 0.0, 0.35);
	Box(0.3, 0.3, 0.8, solid);
	glTranslatef(-0.3, 0, -0.05);
	Box(0.3, 0.3, 0.7, solid);
	glTranslatef(-0.3, 0, -0.1);
	Box(0.3, 0.3, 0.5, solid);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.4, 0.3, -0.35);
	glRotatef(wingAngle, 1, 0, 0);
	glTranslatef(0.0, 0.0, -0.35);
	Box(0.3, 0.3, 0.8, solid);
	glTranslatef(-0.3, 0, 0.05);
	Box(0.3, 0.3, 0.7, solid);
	glTranslatef(-0.3, 0, 0.1);
	Box(0.3, 0.3, 0.5, solid);
	glPopMatrix();
}

void
display(void)
{
	float solid = 1;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if (solid) {
		glPushMatrix();
		lighting();
		glPopMatrix();
	}
	else
		disable();

	glRotatef(yr, 0, 1, 0);
	yr = 0.0;
	glRotatef(xr, 1, 0, 0);
	xr = 0.0;
	glRotatef(zr, 0, 0, 1);
	zr = 0.0;


	glPushMatrix();

	glTranslatef(xt, yt, zt);

	//glShadeModel(GL_FLAT);

	// base body
	glColor3f(0.6, 0.6, 0.0);
	Box(2.0, 1.0, 1.0, solid);

	drawFoot(solid);

	// tail
	glPushMatrix();
	glTranslatef(-0.9, 0.4, 0.0);
	glRotatef(tailAngle, 0, 0, 1);
	glTranslatef(-0.3, 0.3, 0.0);
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	Box(1.0, 0.3, 0.25, solid);
	glPopMatrix();

	// head
	glPushMatrix();
	glTranslatef(1.4, 0.2, 0.0);
	glRotatef(headAngle, 1.0, 0.0, 0.0);
	Box(0.8, 1.2, 1.2, solid);

	// earR
	glPushMatrix();
	glTranslatef(0.0, 0.7, 0.3);
	glRotatef(earAngle, 1.0, 0.0, 0.0);
	Box(0.1, 0.3, 0.3, solid);
	glPopMatrix();

	// earL
	glPushMatrix();
	glTranslatef(0.0, 0.7, -0.3);
	glRotatef(earAngle, 1.0, 0.0, 0.0);
	Box(0.1, 0.3, 0.3, solid);
	glPopMatrix();

	glColor3f(0, 0, 0);

	//eye r
	glPushMatrix();
	glTranslatef(0.4, 0.2, 0.2);
	Box(0.1, 0.2, 0.2, solid);
	glPopMatrix();

	//eye l
	glPushMatrix();
	glTranslatef(0.4, 0.2, -0.2);
	Box(0.1, 0.2, 0.2, solid);
	glPopMatrix();

	// nose
	glPushMatrix();
	glTranslatef(0.4, 0.0, 0.0);
	Box(0.1, 0.1, 0.1, solid);
	glPopMatrix();

	glPopMatrix(); // end of head

	drawWing(solid);

	glPopMatrix(); // end of base(body)
	
	glFlush();
	glutSwapBuffers();
}

void
myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 1.2, -5.5);  /* viewing transform  */
}

void displayAtrib()
{
	cout << "xt = " << xt << " yt = " << yt << " zt = " << zt << "\nxAngle = " << xAngle << " yAngle = " << yAngle << " zAngle = " << zAngle << "\n";
}

void mySpecial(int key, int k, int l)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		yt += 0.1;
		break;
	case GLUT_KEY_RIGHT:
		xt += 0.1;
		break;
	case GLUT_KEY_DOWN:
		yt -= 0.1;
		break;
	case GLUT_KEY_LEFT:
		xt -= 0.1;
		break;
	}

	displayAtrib();
	glutPostRedisplay();
}

void myKey(unsigned char key, int w, int h)
{
	switch (key)
	{
	case 'z':
		zt -= 0.1;
		break;
	case 'x':
		zt += 0.1;
		break;
	case '6':
		yr = 1.0;
		break;
	case '4':
		yr = -1.0;
		break;
	case '8':
		xr = -1.0;
		break;
	case '2':
		xr = 1.0;
		break;
	case '1':
		zr = -1.0;
		break;
	case '3':
		zr = 1.0;
		break;
	case 'w':
		xrm += -1.0;
		xAngle--;
		break;
	case 's':
		xrm += 1.0;
		xAngle++;
		break;
	case 'a':
		yrm += -1.0;
		yAngle--;
		break;
	case 'd':
		yrm += 1.0;
		yAngle++;
		break;
	}

	displayAtrib();

	glutPostRedisplay();
}

void walkAnimation()
{
	if (!reverseFoot)
	{
		footAngle += footRate;
		headAngle += headRate;
		tailAngle -= tailRate;
		wingAngle -= wingRate;
	}
	else
	{
		footAngle -= footRate;
		headAngle -= headRate;
		tailAngle += tailRate;
		wingAngle += wingRate;
	}

	if (footAngle >= MAX_FOOT_ANGLE)
	{
		reverseFoot = true;
	}
	else if (footAngle <= MIN_FOOT_ANGLE)
	{
		reverseFoot = false;
	}

}

void animation()
{
	//yr = 0.025;
	walkAnimation();

	glutPostRedisplay();
}


int
main(int argc, char **argv)
{
	/* start of glut windowing and control functions */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("glutmech: Vulcan Gunner");
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutSpecialFunc(mySpecial);
	glutKeyboardFunc(myKey);
	glutIdleFunc(animation);

	glutMainLoop();
	return 0;

}