#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<OpenGL/gl.h>
#include<GLUT/glut.h>
#include<OpenGl/glu.h>

float ox, oy, r, S_WIDTH = 1920, S_HEIGHT = 1080;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(-S_WIDTH-ox, S_WIDTH, -S_HEIGHT-oy, S_HEIGHT);
}

void plotPoint(float x, float y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void display() {
    float x = 0, y = r, p = 1-r;

    while (x < y) {
        plotPoint(x, y);
        plotPoint(-x, y);
        plotPoint(x, -y);
        plotPoint(-x, -y);

        plotPoint(y, x);
        plotPoint(-y, x);
        plotPoint(y, -x);
        plotPoint(-y, -x);
        
        x += 1;

        if (p < 0) {
            p += 2*x + 1;
        }
        else {
            y -= 1;
            p += 2*x - 2*y + 1;
        }
    }

    glFlush();
}

int main(int argc, char** argv) {
    printf("OriginX, OriginY, Radius: ");
    scanf("%f %f %f", &ox, &oy, &r);

    glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(S_WIDTH, S_HEIGHT);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Midpoint Circle Algorithm");

    init();
    glutDisplayFunc(display);
	glutMainLoop();
}