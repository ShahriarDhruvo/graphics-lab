#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<OpenGL/gl.h>
#include<GLUT/glut.h>
#include<OpenGl/glu.h>

float xStart, xEnd, yStart, yEnd, S_WIDTH = 1920, S_HEIGHT = 1080;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(0.0, S_WIDTH, 0.0, S_HEIGHT);

    // making sure that xEnd & yEnd will always be greater than xStart & yStart
    if (xEnd < xStart) {
        float tmp = xStart;
        
        xStart = xEnd;
        xEnd = tmp;
    }
    if (yEnd < yStart) {
        float tmp = yStart;
        
        yStart = yEnd;
        yEnd = tmp;
    }
}

void plotPoint(float x, float y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void display() {
    float x = xStart, y = yStart;
    float dy = yEnd - yStart, dx = xEnd - xStart, m = dy/dx, p = 2*dy - dx;

    while (x < xEnd) {
        x += 1;

        if (m < 1) {
            if (p < 0) {
                p += 2 * dy;
            }
            else {
                y += 1;
                p += 2*dy - 2*dx;
            }
        }
        else {
            y += 1;

            if (p < 0) {
                p += 2 * dx;
            }
            else {
                p += 2*dx - dy;
            }
        }

        plotPoint(x, y);
    }

    plotPoint(xEnd, yEnd);
    glFlush();
}

int main(int argc, char** argv) {
    printf("xStart, yStart, xEnd, yEnd\n");
    scanf("%f %f %f %f", &xStart, &yStart, &xEnd, &yEnd);

    glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(S_WIDTH, S_HEIGHT);
	glutCreateWindow("DDA Line Algorithm");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    init();
    glutDisplayFunc(display);
	glutMainLoop();
}