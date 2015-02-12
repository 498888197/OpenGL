//
//  main.cpp
//  CCUBE
//
//  Created by 关峰 on 15/2/10.
//  Copyright (c) 2015年 关峰. All rights reserved.
//
#include <glut/glut.h>
#include <opengl/gl.h>

static GLfloat xRot = 0;
static GLfloat yRot = 0;

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    
    // Draw six quads
    glBegin(GL_QUADS);
    // Front Face
    // White
    glColor3ub((GLubyte) 255, (GLubyte)255, (GLubyte)255);
    glVertex3f(50.0f,50.0f,50.0f);
    
    // Yellow
    glColor3ub((GLubyte) 255, (GLubyte)255, (GLubyte)0);
    glVertex3f(50.0f,-50.0f,50.0f);
    
    // Red
    glColor3ub((GLubyte) 255, (GLubyte)0, (GLubyte)0);
    glVertex3f(-50.0f,-50.0f,50.0f);
    
    // Magenta
    glColor3ub((GLubyte) 255, (GLubyte)0, (GLubyte)255);
    glVertex3f(-50.0f,50.0f,50.0f);
    
    
    // Back Face
    // Cyan
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(50.0f,50.0f,-50.0f);
    
    // Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(50.0f,-50.0f,-50.0f);
    
    // Black
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-50.0f,-50.0f,-50.0f);
    
    // Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-50.0f,50.0f,-50.0f);
    
    // Top Face
    // Cyan
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(50.0f,50.0f,-50.0f);
    
    // White
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(50.0f,50.0f,50.0f);
    
    // Magenta
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-50.0f,50.0f,50.0f);
    
    // Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-50.0f,50.0f,-50.0f);
    
    // Bottom Face
    // Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(50.0f,-50.0f,-50.0f);
    
    // Yellow
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(50.0f,-50.0f,50.0f);
    
    // Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-50.0f,-50.0f,50.0f);
    
    // Black
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-50.0f,-50.0f,-50.0f);
    
    // Left face
    // White
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(50.0f,50.0f,50.0f);
    
    // Cyan
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(50.0f,50.0f,-50.0f);
    
    // Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(50.0f,-50.0f,-50.0f);
    
    // Yellow
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(50.0f,-50.0f,50.0f);
    
    // Right face
    // Magenta
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-50.0f,50.0f,50.0f);
    
    // Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-50.0f,50.0f,-50.0f);
    
    // Black
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-50.0f,-50.0f,-50.0f);
    
    // Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-50.0f,-50.0f,50.0f);
    glEnd();
    
    glPopMatrix();
    
    glutSwapBuffers();
}

void SetupRC() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DITHER);
    glShadeModel(GL_SMOOTH);
}

// Get Arrow Keys
void SpecialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
        xRot-= 5.0f;
    
    if(key == GLUT_KEY_DOWN)
        xRot += 5.0f;
    
    if(key == GLUT_KEY_LEFT)
        yRot -= 5.0f;
    
    if(key == GLUT_KEY_RIGHT)
        yRot += 5.0f;
    
    if(key > 356.0f)
        xRot = 0.0f;
    
    if(key < -1.0f)
        xRot = 355.0f;
    
    if(key > 356.0f)
        yRot = 0.0f;
    
    if(key < -1.0f)
        yRot = 355.0f;
    
    // Refresh the Window
    glutPostRedisplay();
}

void CHangeSize(int w, int h) {
    GLfloat fAspect;
    if (h == 0) {
        h = 1;
    }
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    fAspect = (GLfloat)w / (GLfloat)h;
    gluPerspective(35, fAspect, 1, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -400);
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("cube");
    glutReshapeFunc(CHangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    
    SetupRC();
    glutMainLoop();
    
    return 0;
}






