//
//  main.cpp
//  SPHEREWORLD
//
//  Created by 关峰 on 15/1/28.
//  Copyright (c) 2015年 关峰. All rights reserved.
//

#include "gltools.h"
#include "glFrame.h"
#include <math.h>

#define NUM_SPHERES 50
GLFrame spheres[NUM_SPHERES];
GLFrame frameCamera;

void SetupRC()
{
    int iSphere;
    glClearColor(0, 0, 0.5, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    for (iSphere = 0; iSphere < NUM_SPHERES; iSphere++) {
        float x = ((float)((rand() % 400) - 200) * 0.1f);
        float z = (float)((rand() % 400) - 200) * 0.1f;
        spheres[iSphere].SetOrigin(x, 0.0f, z);
    }
}

void DrawGround(void)
{
    GLfloat fExtent = 20;
    GLfloat fStep = 1;
    GLfloat y = -0.4;
    GLint iLine;
    
    glBegin(GL_LINES);
    for(iLine = -fExtent; iLine <= fExtent; iLine += fStep)
    {
        glVertex3f(iLine, y, fExtent);    // Draw Z lines
        glVertex3f(iLine, y, -fExtent);
        
        glVertex3f(fExtent, y, iLine);
        glVertex3f(-fExtent, y, iLine);
    }
    glEnd();
}


void RenderScene(void)
{
    static GLfloat yRot = 0;
    yRot += 0.5;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    //方向怎么不对
//        frameCamera.ApplyActorTransform();
        DrawGround();
        for (int i = 0; NUM_SPHERES > i; i++) {
            glPushMatrix();
            spheres[i].ApplyActorTransform();
            glutSolidSphere(0.1, 13, 26);
            glPopMatrix();
        }
        glPushMatrix();
            glTranslatef(0, 0, -2.5);
    
            glPushMatrix();
                glRotatef(-yRot * 2, 0, 1, 0);
                glTranslatef(1, 0, 0);
                glutSolidSphere(0.1, 13, 26);
            glPopMatrix();
        
            glRotatef(yRot, 0, 1, 0);
            gltDrawTorus(0.35, 0.15, 40, 20);
        glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP) {
        frameCamera.MoveForward(0.1);
    } else if (key == GLUT_KEY_DOWN) {
        frameCamera.MoveForward(-0.1);
    } else if (key == GLUT_KEY_LEFT) {
        frameCamera.RotateLocalY(0.1);
    } else if (key == GLUT_KEY_RIGHT) {
        frameCamera.RotateLocalY(-0.1);
    }
    
    glutPostRedisplay();
}

void TimerFunction(int value)
{
    glutPostRedisplay();
    glutTimerFunc(3, TimerFunction, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat fAspect;
    if (h == 1) {
        h = 1;
    }
    glViewport(0, 0, w, h);
    
    fAspect = (GLfloat)w / (GLfloat)h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(35, fAspect, 1, 50);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("OpenGL SphereWorld Demo");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
    
    SetupRC();
    glutTimerFunc(33, TimerFunction, 1);
    glutMainLoop();
    
    return 0;
}
