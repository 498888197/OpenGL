//
//  main.cpp
//  TriangleCulling
//
//  Created by 关峰 on 15/1/18.
//
//
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include <math.h>

#define GL_PI 3.14

static GLfloat xRot = 0;
static GLfloat yRot = 0;

int iCull = 0;
int iOutline = 0;
int iDepth = 0;

void ProcessMenu(int value)
{
    switch (value) {
        case 1:
            iDepth = !iDepth;
            break;
        case 2:
            iCull = !iCull;
            break;
        case 3:
            iOutline = !iOutline;
        default:
            break;
    }
    glutPostRedisplay();
}

void makeTriangleFan(GLint xTop, GLint yTop, GLint zTop)
{
    GLfloat x, y, angle;
    int iPivot = 1;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(xTop, yTop, zTop);
    for (angle = 0; angle < (2 * GL_PI); angle += (GL_PI / 8)) {
        x = 50 * sin(angle);
        y = 50 * cos(angle);
        
        if (iPivot % 2 == 0) {
            glColor3f(0, 1, 0);
        } else {
            glColor3f(1, 0, 0);
        }
        iPivot++;
        glVertex2f(x, y);
    }
    glEnd();
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (iCull) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
    
    if (!iDepth) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    
    if (!iOutline) {
        glPolygonMode(GL_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_BACK, GL_FILL);
    }
    glPushMatrix();
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    
    makeTriangleFan(0, 0, 75);
    makeTriangleFan(0, 0, 0);
    
    glPopMatrix();
    glutSwapBuffers();
}

void SetupRc()
{
    glClearColor(0, 0, 1, 1);
    glColor3f(0, 1, 0);
    glShadeModel(GL_FLAT);
    glFrontFace(GL_CW);
}

void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        xRot -= 5;
    if (key == GLUT_KEY_DOWN)
        xRot += 5;
    if (key == GLUT_KEY_LEFT)
        yRot -= 5;
    if (key == GLUT_KEY_RIGHT)
        yRot += 5;
    
    if (key > 365)
        xRot = 0;
    if (key < -1)
        xRot = 355;
    if (key > 355)
        yRot = 0;
    if (key < -1)
        yRot = 355;
    
    glutPostRedisplay();
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
    
    if (w <= h)
        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else
        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Triangle Culling");
    
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Toggle depth test", 1);
    glutAddMenuEntry("Toggle cull backface", 2);
    glutAddMenuEntry("Toggle outline back", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    
    SetupRc();
    glutMainLoop();
    
    return 0;
}

















