//
//  main.cpp
//  SIMPLE
//
//  Created by 关峰 on 15/1/16.
//
//

#include <glut/glut.h>
#include <OpenGL/gl.h>

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void SetRC()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Simple");
    glutDisplayFunc(RenderScene);
    
    SetRC();
    
    glutMainLoop();
    return 0;
}
