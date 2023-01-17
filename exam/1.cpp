#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<OpenGL/gl.h>
#include<GLUT/glut.h>
#include<OpenGl/glu.h>

float offsetX = 0, offsetY = 0; 
float S_WIDTH = 1920, S_HEIGHT = 1080;
// float xStart, xEnd, yStart, yEnd, S_WIDTH = 1920, S_HEIGHT = 1080;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(-500 + offsetX, S_WIDTH, -500 + offsetY, S_HEIGHT);
}

void plotPoint(float x, float y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void drawCircle(float ox, float oy, float r) {
    float x = 0, y = r, p = 1-r;

    while (x < y) {
        float tx = x, ty = y;

        plotPoint(ox+tx, oy+ty);
        plotPoint(ox-tx, oy+ty);
        plotPoint(ox+tx, oy-ty);
        plotPoint(ox-tx, oy-ty);

        plotPoint(ox+ty, oy+tx);
        plotPoint(ox-ty, oy+tx);
        plotPoint(ox+ty, oy-tx);
        plotPoint(ox-ty, oy-tx);
        
        x += 1;

        if (p < 0) {
            p += 4 * x + 6;
        }
        else {
            y -= 1;
            p += 4 * (x - y) + 10;
        }
    }

    glFlush();
}

void drawLine(float xStart, float yStart, float xEnd, float yEnd) {
    // making sure that xEnd & yEnd will always be greater than xStart & yStart
    // if (xEnd < xStart) {
    //     float tmp = xStart;
        
    //     xStart = xEnd;
    //     xEnd = tmp;
    // }
    // if (yEnd < yStart) {
    //     float tmp = yStart;
        
    //     yStart = yEnd;
    //     yEnd = tmp;
    // }

    float x = xStart, y = yStart;
    float dy = yEnd - yStart, dx = xEnd - xStart, m = dy/dx;

    if (m <= 1) {
        while (x <= xEnd - 1) {
            x += 1;
            y += m;

            plotPoint(x, y);
        }
    } else {
        while (y <= yEnd - 1) {
            y += 1;
            x += 1/m;

            plotPoint(x, y);
        }
    }

    plotPoint(xEnd, yEnd);
    glFlush();
}

void drawDottedLine(float xStart, float yStart, float xEnd, float yEnd) {
    int gap = 10;
    float x = xStart, y = yStart;
    float dy = yEnd - yStart, dx = xEnd - xStart, m = dy/dx;

    if (m <= 1) {
        while (x <= xEnd - 1) {
            x += 1;
            y += m;

            if (int(x) % gap == 0 && int(y) % gap == 0) plotPoint(x, y);
        }
    } else {
        while (y <= yEnd - 1) {
            y += 1;
            x += 1/m;

            if (int(x) % gap == 0 && int(y) % gap == 0) plotPoint(x, y);
        }
    }

    plotPoint(xEnd, yEnd);
    glFlush();
}

void display() {
    // left pillar
    drawLine(100, 0, 100, 500);
    drawLine(200, 0, 200, 500);
    drawLine(100, 500, 200, 500);

    // mid pillar
    drawLine(400, 0, 400, 500);
    drawLine(500, 0, 500, 170);
    drawLine(500, 330, 500, 500);
    drawLine(600, 0, 600, 500);
    
    drawLine(400, 500, 450, 550);
    drawLine(450, 550, 550, 550);
    
    drawLine(500, 500, 550, 550);
    drawLine(550, 550, 650, 550);
    
    drawLine(600, 500, 650, 550);
    
    // right pillar
    drawLine(800, 0, 800, 500);
    drawLine(900, 0, 900, 500);
    drawLine(800, 500, 900, 500);

    drawLine(0, 0, 1000, 0);
    drawLine(100, -100, 900, -100);
    drawDottedLine(200, -200, 800, -200);
    
    drawLine(0, 0, 100, -100);
    drawLine(900, -100, 1000, 0);

    drawDottedLine(100, -100, 200, -200);
    drawDottedLine(800, -200, 900, -100);
    
    // mid circle
    drawCircle(500, 250, 80);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(S_WIDTH, S_HEIGHT);
	glutCreateWindow("1st Question's Answer");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    init();
    glutDisplayFunc(display);
	glutMainLoop();
}