//
//  main.cpp
//  TransformGL
//
//  Created by 关峰 on 15/1/31.
//
//
#include "gltools.h"
#include "math3d.h"
#include <math.h>

void RenderScene(void)
{
    M3DMatrix44f rotationMatrix, translationMatrix,transformtionMatrix;
    static GLfloat yRot = 0;
    yRot += 0.5;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m3dRotationMatrix44(transformtionMatrix, m3dDegToRad(yRot), 0, 1, 0);
    transformtionMatrix[12] = 0;
    transformtionMatrix[13] = 0;
    transformtionMatrix[14] = -2.5;
    
    glLoadMatrixf(transformtionMatrix);
    
    gltDrawTorus(0.35, 0.15, 40, 20);
    
    glutSwapBuffers();
}

void SetupRC()
{
    glClearColor(0, 0, 50, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TimerFunction(int value)
{
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat fAspect;
    if (h == 0 ) {
        h = 1;
    }
    glViewport(0, 0, w, h);
    
    fAspect = (GLfloat)w / (GLfloat)h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35, fAspect, 1, 80);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGl Transformation Demo");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    
    SetupRC();
    glutTimerFunc(33, TimerFunction, 1);
    
    glutMainLoop();

    return 0;
}














