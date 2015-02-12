//
//  main.cpp
//  spot
//
//  Created by 关峰 on 15/2/12.
//  Copyright (c) 2015年 关峰. All rights reserved.
//

#include <glut/glut.h>
#include <OpenGL/gl.h>

static GLfloat xRot = 0;
static GLfloat yRot = 0;

GLfloat	 lightPos[] = { 0.0f, 0.0f, 75.0f, 1.0f };
GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f};
GLfloat  spotDir[] = { 0.0f, 0.0f, -1.0f };

#define MODE_FLAT 1
#define MODE_SMOOTH  2
#define MODE_VERYLOW 3
#define MODE_MEDIUM  4
#define MODE_VERYHIGH 5

int iShade = MODE_FLAT;
int iTess = MODE_VERYLOW;

void ProcessMenu(int value)
{
    switch(value)
    {
        case 1:
            iShade = MODE_FLAT;
            break;
            
        case 2:
            iShade = MODE_SMOOTH;
            break;
            
        case 3:
            iTess = MODE_VERYLOW;
            break;
            
        case 4:
            iTess = MODE_MEDIUM;
            break;
            
        case 5:
        default:
            iTess = MODE_VERYHIGH;
            break;
    }
    
    glutPostRedisplay();
}

void RenderScene(void)
{
    if (iShade == MODE_FLAT) {
        glShadeModel(GL_FLAT);
    } else {
        glShadeModel(GL_SMOOTH);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    
    glRotatef(yRot, 0, 1, 0);
    glRotatef(xRot, 1, 0, 0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    glColor3ub(255, 0, 0);
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    glutSolidCone(4, 6, 15, 15);
    glPushAttrib(GL_LIGHTING_BIT);
    
    glDisable(GL_LIGHTING);
    glColor3ub(255, 255, 0);
    glutSolidSphere(3, 15, 15);
    
    glPopAttrib();
    
    glPopMatrix();
    glColor3ub(0, 0, 255);
    
    if (iTess == MODE_VERYLOW) {
        glutSolidSphere(30, 7, 7);
    } else {
        if(iTess == MODE_MEDIUM)
            glutSolidSphere(30.0f, 15, 15);
        else //  iTess = MODE_MEDIUM;
            glutSolidSphere(30.0f, 50, 50);
    }
    glutSwapBuffers();
}

void SetupRC()
{
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    
    glEnable(GL_LIGHTING);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50);
    
    glEnable(GL_LIGHT0);
    
    glEnable(GL_COLOR_MATERIAL);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    
    glClearColor(0, 0, 0, 1);
}


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


void ChangeSize(int w, int h)
{
    GLfloat fAspect;
    
    // Prevent a divide by zero
    if(h == 0)
        h = 1;
    
    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);
    
    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Establish viewing volume
    fAspect = (GLfloat) w / (GLfloat) h;
    gluPerspective(35.0f, fAspect, 1.0f, 500.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -250.0f);
}

int main(int argc, char* argv[])
{
    int nMenu;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Spot Light");
    
    // Create the Menu
    nMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Flat Shading",1);
    glutAddMenuEntry("Smooth Shading",2);
    glutAddMenuEntry("VL Tess",3);
    glutAddMenuEntry("MD Tess",4);
    glutAddMenuEntry("VH Tess",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    
    return 0;
}











