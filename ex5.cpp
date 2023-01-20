#include <glut.h>
#include <stdio.h>

int ww = 600, wh = 400;
int xi, yi, xf, yf;

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2)
{
	glPointSize(2.0);
	int temp,temp1;
	int dx,dy;
	
	if(x1>x2 || y1>y2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;

		temp1 = y1;
		y1 = y2;
		y2 = temp1;
	}

	dx=x2-x1;
	dy=y2-y1;

	glBegin(GL_POINTS);

	glVertex2i(x1, y1);	//plotting the first point

	GLint x,y;
	
	float m = (y2 - y1) / (float)(x2 - x1);
	float c = y1 - x1 * m;
	printf("m = %f   ,    c = %f \n", m, c);

	if(dx>dy)
	{
	for (GLint x = x1 + 1; x <= x2; x++) {
		y = m * x + c;
		glVertex2i(x, y);	//plotting points
	}
	}
	else
	{
		for (GLint y = y1 + 1; y <= y2; y++) {
		x = (y-c)/m;
		glVertex2i(x, y);	//plotting points
	}
	}


	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glLineWidth(2.0f);
	glBegin(GL_LINES);        
		glVertex2f(xi, yi);        
		glVertex2f(xf, yf);  
	glEnd();
	glFlush();
}

void display2()
{
	drawLine(xi,yi,xf,yf);
	glFlush();
}
void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
		{
			xi = x;
			yi = (wh - y);
		}
		else if (state == GLUT_UP) {
			xf = x;
			yf = (wh - y);
			glutPostRedisplay();
		}
	if (btn == GLUT_RIGHT_BUTTON) {
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}

void myinit()
{
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0, 0.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("Lines");

	glutDisplayFunc(display);
	glutDisplayFunc(display2);
	glutMouseFunc(mouse);
	myinit();
	glutMainLoop();

	return 0;
}