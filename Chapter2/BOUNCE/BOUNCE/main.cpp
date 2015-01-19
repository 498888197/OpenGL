//
//  main.cpp
//  BOUNCE
//
//  Created by 关峰 on 15/1/18.
//
//

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

GLfloat x1 = 0.0;
GLfloat y1 = 0.0;
GLfloat rsize = 25;

GLfloat xstep = 1;
GLfloat ystep = 1;

GLfloat windowWidth;
GLfloat windowHeight;

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(x1, y1, x1 + rsize, y1 - rsize);
    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLfloat aspectRatio = 1.0f;
    if (h == 0) {
        h = 1;
    }
//    if (w == 0) {
//        w = 1;
//    }
    windowHeight = h / 2 ;
    windowWidth = w / 2;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h) {
        glOrtho(-100.0, 100.0, -100.0/aspectRatio, 100.0/aspectRatio, 1.0, -1.0);
    } else {
        glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TimerFunction(int value)
{
    //到达最右边或最左边
    if (x1 + rsize > windowWidth || x1 < -windowWidth) {
        xstep = -xstep;
    }
    //最下边或最上边
    if (y1 - rsize < -windowHeight || y1 > windowHeight) {
        ystep = -ystep;
    }
    x1 += xstep;
    y1 += ystep;
    
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

int main(int argc, char * argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(200, 200);
    glutCreateWindow("Bounce");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33, TimerFunction, 1);
    
    SetupRC();
    glutMainLoop();
    
    
    return 0;
}




