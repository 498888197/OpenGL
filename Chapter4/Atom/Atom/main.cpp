//
//  main.cpp
//  Atom
//
//  Created by 关峰 on 15/1/25.
//  Copyright (c) 2015年 关峰. All rights reserved.
//

#include <Opengl/gl.h>
#include <Glut/glut.h>

void SetupRC();
void RenderScene();

void RenderScene()
{
    static GLfloat fElect = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslated(0, 0, 0);
    
    glColor3ub(255, 0, 0);
    glutSolidSphere(10, 15, 15);
    
    glPushMatrix();
    glColor3ub(255, 255, 0);
    glRotatef(fElect, 0, 1, 0);
    glTranslatef(90, 0, 0);
    glutSolidSphere(6, 15, 15);
    glPopMatrix();
    
    glPushMatrix();
    glColor3ub(255, 255, 255);
    glRotatef(45, 0, 0, 1);
    glRotatef(fElect, 0, 1, 0);
    glTranslatef(-70, 0, 0);
    glutSolidSphere(6, 15, 15);
    glPopMatrix();
    
    glPushMatrix();
    glColor3ub(0, 255, 0);
    glRotatef(-45, 0, 0, 1);
    glRotatef(fElect, 0, 1, 0);
    glTranslatef(0, 0, 60);
    glutSolidSphere(6, 15, 15);
    glPopMatrix();
    
    fElect += 10;
    if (fElect > 360) {
        fElect = 0;
    }
    glutSwapBuffers();
}

void SetupRC()
{
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glClearColor(0, 0, 0, 1);
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 100;
    if (h == 0) {
        h = 1;
    }
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (w <= h) {
        glOrtho(-nRange, nRange, nRange * h / w, -nRange * h / w, -nRange * 2, nRange * 2);
    } else {
        glOrtho(-nRange * w / h, nRange * w / h, nRange, -nRange, -nRange * 2, nRange * 2);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Atom");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(500, TimerFunc, 1);
    SetupRC();
    
    glutMainLoop();
    
    return 0;
}












