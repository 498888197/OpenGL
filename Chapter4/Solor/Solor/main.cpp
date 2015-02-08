//
//  main.cpp
//  Solor
//
//  Created by 关峰 on 15/1/31.
//
//
#include <OpenGL/gl.h>
#include <Glut/glut.h>
#include <math.h>

GLfloat whiteLight[] = {0.2, 0.2, 0.2, 1};
GLfloat sourceLight[] = {0.8, 0.8, 0.8, 1};
GLfloat lightPos[] = {0, 0, 0, 1};

void RenderScene(void)
{
    static float fMoonRot = 0;
    static float fEarthRot = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    glTranslatef(0, 0, -300);
    
    glDisable(GL_LIGHTING);
    glColor3ub(255, 255, 0);
    glutSolidSphere(15, 30, 17);
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    glRotatef(fEarthRot, 0, 1, 0);
    
    glColor3ub(0, 0, 255);
    glTranslatef(105, 0, 0);
    glutSolidSphere(15, 30, 17);
    
    glColor3ub(200, 200, 200);
    glRotatef(fMoonRot, 0, 1, 0);
    glTranslatef(30, 0, 0);

    
    glutSolidSphere(6, 30, 17);
    
    glPopMatrix();
    
    fMoonRot += 15;
    if (fMoonRot > 360) {
        fMoonRot = 0;
    }
    
    fEarthRot += 5;
    if (fEarthRot > 360) {
        fEarthRot = 0;
    }
    glutSwapBuffers();
}

void SetupRC()
{
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);
    
    glEnable(GL_COLOR_MATERIAL);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0, 0, 0, 1);
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat fAspect;
    if (h == 0) {
        h = 1;
    }
    glViewport(0, 0, w, h);
    fAspect = (GLfloat) w / (GLfloat)h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45, fAspect, 1, 425);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RED | GLUT_DEPTH);
    
    glutInitWindowSize(800, 600);
    glutCreateWindow("Solar");
    
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    
    glutTimerFunc(250, TimerFunc, 1);
    SetupRC();
    glutMainLoop();

    return 0;
}















