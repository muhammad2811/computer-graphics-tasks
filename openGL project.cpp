#include<stdio.h>
#include<cmath>
#include<GL/glut.h>
float angle = 0;
float xScale = 1, yScale = 1, zangle = 0;
float doorAngle = 0.0; 
float windowAngle = 0.0; 
float bikePositionX = 0.0;  
float bikeSpeed = 0.1;      
float bikeAngle = 0.0;


void rotateFunc(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_RIGHT:
        angle += 1;
        if (angle > 360) angle = 0.0;
        break;
    case GLUT_KEY_LEFT:
        angle -= 1;
        if (angle > 360) angle = 0.0;
        break;
    case GLUT_KEY_DOWN:
        if (xScale > 0.7)
        {
            xScale -= 0.01;
            yScale -= 0.01;
        }
        break;
    case GLUT_KEY_UP:
        if (xScale < 1.5) {
            xScale += 0.01;
            yScale += 0.01;
        }
        break;

    case GLUT_KEY_PAGE_UP:
        zangle = 1;
        break;
    case GLUT_KEY_PAGE_DOWN:
        zangle = 0;
        break;


    }
    glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y) {
    if (key == 'o') {
        doorAngle += 10; 
        if (doorAngle > 90) doorAngle = 90; 
    }
    else if (key == 'c') {
        doorAngle -= 10; 
        if (doorAngle < 0) doorAngle = 0;
    }
    else if (key == 'w') {
        windowAngle += 10; 
        if (windowAngle > 90) windowAngle = 90;
    }
    else if (key == 'x') {
        windowAngle -= 10; 
        if (windowAngle < 0) windowAngle = 0; 
    }
    else if (key == 'g') {
        bikePositionX += bikeSpeed;  
    }
    else if (key == 'b') {
        bikePositionX -= bikeSpeed;  
    }
    else if (key == 'r') {
        bikeAngle += 2.5;
    }
    else if (key == 'l') {
        bikeAngle -= 2.5;
    }
    glutPostRedisplay();
}

void Scene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //sky
    glPushMatrix();
    glTranslatef(0, 0, -10);
    glColor3f(0, .6, .9);
    glBegin(GL_QUADS);
    glVertex3f(-10, 10, 0);
    glVertex3f(10, 10, 0);
    glVertex3f(10, -10, 0);
    glVertex3f(-10, -10, 0);
    glEnd();
    glPopMatrix();

    //grass
    glPushMatrix();
    glTranslatef(0, 0, -6);
    glColor3f(0, 1, .1);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);
    glVertex3f(-30, -1.5, 100);
    glVertex3f(-30, -1.5, -100);
    glVertex3f(30, -1.5, -100);
    glVertex3f(30, -1.5, 100);
    glEnd();
    glPopMatrix();

    //front wall up
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);  
    glVertex3f(-2,0 , 1);
    glVertex3f(2, 0, 1);
    glVertex3f(2,-.5 , 1);
    glVertex3f(-2,-.5 , 1);
    glEnd();
    glPopMatrix();
    //front wall left door
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); 
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);
    glVertex3f(-2,-1 , 1);
    glVertex3f(.5,-1 , 1);
    glVertex3f(.5,-1.5 , 1);
    glVertex3f(-2,-1.5 , 1);
    glEnd();
    glPopMatrix();
    //front wall right door
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); 
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);
    glVertex3f(1,-1 , 1);
    glVertex3f(2,-1 , 1);
    glVertex3f(2,-1.5 , 1);
    glVertex3f(1,-1.5 , 1);
    glEnd();
    glPopMatrix();
    //front wall center 1
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);
    glVertex3f(-2,-.5 , 1);
    glVertex3f(-1.5,-.5 , 1);
    glVertex3f(-1.5,-1 , 1);
    glVertex3f(-2,-1 , 1);
    glEnd();
    glPopMatrix();
    //front wall center 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); 
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);
    glVertex3f(-.8,-.5 , 1);
    glVertex3f(-.5,-.5 , 1);
    glVertex3f(-.5,-1 , 1);
    glVertex3f(-.8, -1, 1);
    glEnd();
    glPopMatrix();
    //front wall center 3
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); 
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);
    glVertex3f(.2,-.5 , 1);
    glVertex3f(.5,-.5 , 1);
    glVertex3f(.5,-1 , 1);
    glVertex3f(.2, -1, 1);
    glEnd();
    glPopMatrix();
    //front wall center 4
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);
    glVertex3f(1,-.5 , 1);
    glVertex3f(1.2,-.5 , 1);
    glVertex3f(1.2,-1 , 1);
    glVertex3f(1, -1, 1);
    glEnd();
    glPopMatrix();
    //front wall center 5
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); 
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);
    glVertex3f(1.9,-.5 , 1);
    glVertex3f(2,-.5 , 1);
    glVertex3f(2, -1, 1);
    glVertex3f(1.9,-1 , 1);
    glEnd();
    glPopMatrix();

    //back wall
    glPushMatrix();
    glColor3f(.8, .8, 0.0); 
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);  
    glVertex3f(-2, 0, -1);
    glVertex3f(2, 0, -1);
    glVertex3f(2, -1.5, -1);
    glVertex3f(-2, -1.5, -1);
    glEnd();
    glPopMatrix();

    //right wall
    glPushMatrix();
    glColor3f(.9, .9, 0.0);
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);  
    glVertex3f(2, 0, -1);
    glVertex3f(2, 0, 1);
    glVertex3f(2, -1.5, 1);
    glVertex3f(2, -1.5, -1);
    glEnd();
    glPopMatrix();
    //wall upper right
    glPushMatrix();
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_TRIANGLES);
    glColor3f(.9, .9, 0.0);
    glVertex3f(2, 0, 1.1);
    glVertex3f(1.9, .8, 0);
    glVertex3f(2, 0, -1.1);
    glEnd();
    glPopMatrix();

    //left wall
    glPushMatrix();
    glColor3f(.9, .9, 0.0); 
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);  
    glVertex3f(-2, 0, -1);
    glVertex3f(-2, 0, 1);
    glVertex3f(-2, -1.5, 1);
    glVertex3f(-2, -1.5, -1);
    glEnd();
    glPopMatrix();
    //wall upper left
    glPushMatrix();
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_TRIANGLES);
    glColor3f(.9, .9, 0.0);
    glVertex3f(-2, 0, 1.1);
    glVertex3f(-1.9, .8, 0);
    glVertex3f(-2, 0, -1.1);
    glEnd();
    glPopMatrix();


    //front roof
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0); 
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);  
    glColor3f(1.0, 0.5, 0.0); 
    glVertex3f(-2.1, 0, 1.1);
    glVertex3f(2.1, 0, 1.1);
    glVertex3f(2, .8, 0);
    glVertex3f(-2, .8, 0);
    glEnd();
    glPopMatrix();
    //back roof
    glPushMatrix();
    glColor3f(.9, 0.4, 0.0); 
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glBegin(GL_QUADS);
    glVertex3f(-2.1, 0, -1.1);
    glVertex3f(2.1, 0, -1.1);
    glVertex3f(2, .8, 0);
    glVertex3f(-2, .8, 0);
    glEnd();
    glPopMatrix();

    //door draw
    glPushMatrix();
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glTranslatef(0.5, -1.0, 1.0005); 
    glRotatef(doorAngle, 0, 1, 0); 
    glTranslatef(-0.5, 1.0, -1.0005);
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.1f, 0.0f);
    glVertex3f(0.5, -0.5, 1.0005);
    glVertex3f(1, -0.5, 1.0005);
    glVertex3f(1, -1.49, 1.0005);
    glVertex3f(0.5, -1.49, 1.0005);
    glEnd();
    glPopMatrix();

    //windo 1 draw
    glPushMatrix();
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glTranslatef(-1.5, .8, 1.01); 
    glRotatef(windowAngle, 0, 1, 0); 
    glTranslatef(1.5, -.8, -1.01); 
    glBegin(GL_QUADS);
    glColor3f(0, .7, .6);
    glVertex3f(-1.5, -0.5, 1.01);
    glVertex3f(-0.8, -0.5, 1.01);
    glVertex3f(-0.8, -1, 1.01);
    glVertex3f(-1.5, -1, 1.01);
    glEnd();
    glPopMatrix();
    //window 2 draw
    glPushMatrix();
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glTranslatef(-.5, -.2, 1.01); 
    glRotatef(windowAngle, 0, 1, 0); 
    glTranslatef(.5, .2, -1.01); 
    glBegin(GL_QUADS);
    glColor3f(0, .7, .6);
    glVertex3f(-.5, -.5, 1.01);
    glVertex3f(.2, -.5, 1.01);
    glVertex3f(.2, -1, 1.01);
    glVertex3f(-.5, -1, 1.01);
    glEnd();
    glPopMatrix();
    //window 3 draw
    glPushMatrix();
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    glTranslatef(1.2, -1.9, 1.01); 
    glRotatef(windowAngle, 0, 1, 0); 
    glTranslatef(-1.2, 1.9, -1.01); 
    glBegin(GL_QUADS);
    glColor3f(0, .7, .6);
    glVertex3f(1.2, -.5, 1.01);
    glVertex3f(1.9, -.5, 1.01);
    glVertex3f(1.9, -1, 1.01);
    glVertex3f(1.2, -1, 1.01);
    glEnd();
    glPopMatrix();

    // bicycle 
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1, zangle);
    glScalef(xScale, yScale, 1);
    // Draw front wheels
    glPushMatrix();
    glTranslatef(bikePositionX, -.8, 1);
    glRotatef(bikeAngle, 0, 1, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 50; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(50);
        float x = 0.2f * cosf(theta);
        float y = 0.2f * sinf(theta);
        glVertex3f(x + 0.5f, y + -0.5f, 1);
    }
    glEnd();
    glPopMatrix();
    // Draw back wheels
    glPushMatrix();
    glTranslatef(bikePositionX, -.8, 1);
    glRotatef(bikeAngle, 0, 1, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 50; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(50);
        float x = 0.2f * cosf(theta);
        float y = 0.2f * sinf(theta);
        glVertex3f(x + -0.5f, y + -0.5f, 1);
    }
    glEnd();
    glPopMatrix();
    //draw frame
    glTranslatef(bikePositionX, -.8, 1);
    glRotatef(bikeAngle, 0, 1, 0);
    // Draw body
    glBegin(GL_LINES);
    glVertex3f(-0.5f, -0.5f, 1);
    glVertex3f(0.5f, -0.5f, 1);
    glVertex3f(-0.5f, -0.5f, 1);
    glVertex3f(-0.2f, 0.1f, 1);
    glVertex3f(-0.2f, 0.1f, 1);
    glVertex3f(0.2f, 0.1f, 1);
    glVertex3f(0.2f, 0.1f, 1);
    glVertex3f(0.5f, -0.5f, 1);
    glVertex3f(0.2f, 0.1f, 1);
    glVertex3f(0.3f, 0.3f, 1);
    glVertex3f(-0.5f, -0.5f, 1);
    glVertex3f(-0.3f, -0.5f, 1);
    glVertex3f(-0.3f, -0.5f, 1);
    glVertex3f(0.5f, -0.5f, 1);
    glVertex3f(-0.2f, 0.1f, 1);
    glVertex3f(-0.3f, -0.5f, 1);
    glVertex3f(-0.2f, 0.1f, 1);
    glVertex3f(0.2f, 0.1f, 1);
    glEnd();
    // Draw handlebars
    glBegin(GL_LINES);
    glVertex3f(0.3f, 0.3f, 1);
    glVertex3f(0.3f, 0.4f, 1);
    glVertex3f(0.3f, 0.4f, 1);
    glVertex3f(0.3f, 0.4f, 1.15);
    glVertex3f(0.3f, 0.4f, 1);
    glVertex3f(0.3f, 0.4f, .85);
    glEnd();
    // Draw seat
    glBegin(GL_LINES);
    glVertex3f(-0.2f, 0.1f, 1);
    glVertex3f(-0.15f, 0.2f, 1);
    glVertex3f(-0.15f, 0.2f, 1);
    glVertex3f(-0.25f, 0.2f, 1);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();

}

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(2000, 1300);
    glutCreateWindow("openGL_project");
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(resize);
    glutDisplayFunc(Scene);
    glutSpecialFunc(rotateFunc);
    glutKeyboardFunc(keyboardFunc); 

    Initialize();
    glutMainLoop();
    return 0;
}