#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;

double Txval=0,Tyval=0,Tzval=0;
double eyeX=0.0, eyeY=30.0, eyeZ=50.0, refX = 0,refY=30,refZ=0,f=0,f1=0;
double windowHeight=900, windowWidth=900;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false,s1 = true,s2 = true,s3 = true;
bool flag=false,a0=true,d0=true,s0=true;

GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

static GLfloat cube[8][4] =
{
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},

    {0.0, 1.0, 0.0},
    {1.0, 1.0, 0.0},
    {1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0},

};

static GLubyte p_Indices[6][4] =
{
    {0, 1, 2, 3},
    {7, 6, 5, 4},
    {4, 0, 3, 7},
    {6, 2, 1, 5},
    {5, 1, 0, 4},
    {3, 2, 6, 7},


};

/*static GLubyte quadIndices[1][4] =
{
    {0, 3, 2, 1}
};
*/
static GLfloat colors[13][3] =
{
    {0.0f, 0.0f, 1.0f},//blue
    {0.1f, 0.0f, 0.0f},//Brown
    {0.0f, 0.5f, 1.0f},//baby Blue
    {0.0f, 0.5f, 0.5f},//Blue-Green
    {0.1f, 0.1f, 0.1f},//Dark grey
    {0.784, 0.898, 0.866},
    {0.870, 0.803, 0.917},
    {0.588, 0.611, 0.596},
    {0.956, 0.925, 0.882},
    {0.094, 0.054, 0.007},
    {0.321, 0.098, 0.160},
    {0.325, 0.113, 0.325},
    {0.270, 0.031, 0.145}



};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


void drawcube(double x,double y,double z )
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5*x, 0.5*y, 0.5*z, 1.0 };
    GLfloat mat_diffuse[] = { x, y, z, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};
    GLfloat mat_emission[] = {0.3*x, 0.2*y, 0.2*z, 1.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    //glColor3f(x,y,z);

    //glColor3f(1,0,0);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <8; i++)
    {
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(cube[p_Indices[i][0]][0], cube[p_Indices[i][0]][1], cube[p_Indices[i][0]][2],
                    cube[p_Indices[i][1]][0], cube[p_Indices[i][1]][1], cube[p_Indices[i][1]][2],
                    cube[p_Indices[i][2]][0], cube[p_Indices[i][2]][1], cube[p_Indices[i][2]][2]);

        for (GLint j = 0; j <8; j++)
        {
            glVertex3fv(&cube[p_Indices[i][j]][0]);

        }
    }
    glEnd();

}


void light()//tubelight
{

    GLfloat light_position[] = {37,42,-15,1 };
    glEnable( GL_LIGHT0);

    if( s1&&a0)
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    else
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);

    if( s1&&d0)
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    else
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
    if(s1&& s0)
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    else
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_FRONT, GL_EMISSION, mat_emission);

}

void light1()//window
{
    GLfloat light_position[] = {-25,50,0,1 };

    glEnable( GL_LIGHT1);
    if( s2&&a0)
        glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    else
        glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);

    if( s2&&d0)
        glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    else
        glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
    if(s2&& s0)
        glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    else
        glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);


    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_FRONT, GL_EMISSION, mat_emission);

    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 35.0);
}

void light2()//tubelight
{
    GLfloat light_position[] = {0,45,-47.5,1 };

    glEnable( GL_LIGHT2);
    if( s3&&a0)
        glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    else
        glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);

    if( s3&&d0)
        glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    else
        glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
    if(s3&& s0)
        glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    else
        glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);


    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    glLightfv(GL_FRONT, GL_EMISSION, mat_emission);



}


void l1()
{
    glPushMatrix();//base
    // glTranslatef(5,0,0);
    glScalef(5,0.5,0.25);
    //glColor3f(0.913, 0.898, 0.886);
    drawcube(0.913, 0.898, 0.886);
    glPopMatrix();

    glPushMatrix();//light
    glTranslatef(0.25,0.125,0.25);
    glScalef(4.5,0.25,0.25);
    //glColor3f(1,1,1);
    drawcube(1,1,1);
    glPopMatrix();
}
void window()
{
    glPushMatrix();//back
    glTranslatef(0,0,0.25);
    glScalef(5,3,0.00005);
    drawcube(0.811, 0.905, 0.905);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//upper side
    glTranslatef(-0.25,3,0);
    glScalef(5.5,0.5,0.5);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//rod 1
    glTranslatef(0.25,1,0.5);
    glScalef(4.75,0.05,0.05);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//rod 2
    glTranslatef(0.25,2,0.5);
    glScalef(4.75,0.05,0.05);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();


    glPushMatrix();//lower side
    glTranslatef(-0.25,0,0);
    glScalef(5.5,0.5,0.5);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left side
    glTranslatef(-0.25,0,0);
    glScalef(0.5,3.5,0.5);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//rod 4
    glTranslatef(1,0.5,0.5);
    glScalef(0.05,2.5,0.05);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//rod 5
    glTranslatef(2,0.5,0.5);
    glScalef(0.05,2.5,0.05);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//rod 6
    glTranslatef(3,0.5,0.5);
    glScalef(0.05,2.5,0.05);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//rod 7
    glTranslatef(4,0.5,0.5);
    glScalef(0.05,2.5,0.05);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//right side
    glTranslatef(5,0,0);
    glScalef(0.5,3.5,0.5);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();
}
void texture()
{
    for (int i=0; i<4; i+=2)
    {
        glPushMatrix();

        glTranslatef(i,0,0);
        glScalef(1,0.25,1);
        drawcube(1,1,1);
        // drawcube();
        glPopMatrix();
    }
    for (int i=-1; i<4; i+=2)
    {
        glPushMatrix();

        glTranslatef(i,0,0);
        glScalef(1,0.25,1);
        drawcube(colors[9][0],colors[9][1],colors[9][2]);
        // drawcube();
        glPopMatrix();
    }

}
void texture1()
{
    for (int i=0; i<4; i+=2)
    {
        glPushMatrix();

        glTranslatef(i,0,0);
        glScalef(1,0.25,1);
        drawcube(colors[9][0],colors[9][1],colors[9][2]);
        //drawcube();
        glPopMatrix();
    }
    for (int i=-1; i<4; i+=2)
    {
        glPushMatrix();

        glTranslatef(i,0,0);
        glScalef(1,0.25,1);
        drawcube(1,1,1);
        //drawcube();
        glPopMatrix();
    }

}

void f_texture()
{
    for (int i=0; i<10; i+=2)
    {
        glPushMatrix();
        glTranslatef(0,0,i);
        glScalef(1,0.25,1);
        texture();
        glPopMatrix();
    }
    for (int i=-1; i<10; i+=2)
    {
        glPushMatrix();
        glTranslatef(0,0,i);
        glScalef(1,0.25,1);
        texture1();
        glPopMatrix();
    }

}
void parda()
{
    glPushMatrix();//top side
    // glTranslatef(5,0,0);
    glScalef(6,0.25,0.5);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//right side
    glTranslatef(-0.25,0,-0.5);
    glScalef(0.25,0.25,1);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left side
    glTranslatef(6,0,-0.5);
    glScalef(0.25,0.25,1);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//porda1
    glTranslatef(0.25,-4.75,-0.25);
    glScalef(0.05,5,1);
    drawcube(0.098, 0.498, 0.639);
    // drawcube();
    glPopMatrix();

    glPushMatrix();//porda2
    glTranslatef(0.75,-4.75,-0.25);
    glScalef(0.05,5,1);
    drawcube(0.098, 0.498, 0.639);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//porda3
    glTranslatef(1.25,-4.75,-0.25);
    glScalef(0.05,5,1);
    drawcube(0.098, 0.498, 0.639);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//porda4
    glTranslatef(4.75,-4.75,-0.25);
    glScalef(0.05,5,1);
    drawcube(0.098, 0.498, 0.639);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//porda5
    glTranslatef(5.25,-4.75,-0.25);
    glScalef(0.05,5,1);
    drawcube(0.098, 0.498, 0.639);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//porda6
    glTranslatef(5.75,-4.75,-0.25);
    glScalef(0.05,5,1);
    drawcube(0.098, 0.498, 0.639);
    //drawcube();
    glPopMatrix();




}
void door()
{
    glPushMatrix();//door

    glTranslatef(4.75,0.25,-0.25);//glRotatef(270,0,1,0);
    glScalef(0.2,4.75,2.5);
    drawcube(0.086, 0.117, 0.254);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//lock
    glTranslatef(4.5,3,0.25);
    //glRotatef(90,0,1,0);
    glScalef(0.25,0.5,0.25);
    drawcube(0.019, 0.058, 0.219);
    // drawcube();
    glPopMatrix();

    glPushMatrix();//top
    glTranslatef(4.75,5,-0.25);
    glScalef(0.25,0.25,2.5);
    // glColor3f(1,0,0);
    drawcube(0.019, 0.058, 0.219);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left
    glTranslatef(4.75,0.25,-0.5);
    glScalef(0.25,5,0.25);
    drawcube(0.019, 0.058, 0.219);
    // drawcube();
    glPopMatrix();

    glPushMatrix();//right
    glTranslatef(4.75,0.25,2.25);
    glScalef(0.25,5,0.25);
    drawcube(0.019, 0.058, 0.219);
    //drawcube();
    glPopMatrix();
}
void wall()
{
    glPushMatrix();//left1
    glTranslatef(0,0.25,0);
    glScalef(0.25,4.75,3);
    drawcube(colors[6][0],colors[6][1],colors[6][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//right1
    glTranslatef(4.75,0.25,0);
    glScalef(0.25,4.75,2);
    drawcube(colors[6][0],colors[6][1],colors[6][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//uper right
    glTranslatef(4.75,4,2);
    glScalef(0.25,1,1.5);
    drawcube(colors[6][0],colors[6][1],colors[6][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//light
    glTranslatef(4.75,4.25,3.5);
    glScalef(0.25,0.5,0.5);
    glRotatef(-90,0,1,0);

    //glColor3f(colors[6][0],colors[6][1],colors[6][2]);
    l1();
    glPopMatrix();

    glPushMatrix();//door
    glTranslatef(2.5,0,2.25);
    glScalef(0.5,0.76,0.5);
    door();
    glPopMatrix();

    glPushMatrix();//window
    glTranslatef(0,1,5.75);
    glScalef(0.25,1,0.5);
    //glColor3f(colors[6][0],colors[6][1],colors[6][2]);
    glRotatef(90,0,1,0);
    window();
    glPopMatrix();

    glPushMatrix();//parda
    glTranslatef(0.5,4.5,5.75);
    glScalef(0.25,0.75,0.5);
    //glColor3f(colors[6][0],colors[6][1],colors[6][2]);
    glRotatef(90,0,1,0);
    parda();
    glPopMatrix();

    glPushMatrix();//left lower
    glTranslatef(0,0.25,3);
    glScalef(0.25,0.75,2.85);
    drawcube(colors[6][0],colors[6][1],colors[6][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left upper
    glTranslatef(0,4.5,3);
    glScalef(0.25,0.5,2.85);
    drawcube(colors[6][0],colors[6][1],colors[6][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left2
    glTranslatef(0,0.25,5.8);
    glScalef(0.25,4.75,4);
    drawcube(colors[6][0],colors[6][1],colors[6][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//right2
    glTranslatef(4.75,0.25,3.5);
    glScalef(0.25,4.75,6.5);
    drawcube(colors[6][0],colors[6][1],colors[6][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//top
    glTranslatef(0,5,0);
    glScalef(5.0,0.25,10.0);
    drawcube(colors[8][0],colors[8][1],colors[8][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//bottom
    glTranslatef(1,0.125,0.9);
    glScalef(1,1.5,0.9);
    //glColor3f(colors[7][0],colors[7][1],colors[7][2]);
    f_texture();
    glPopMatrix();

    glPushMatrix();//back
    glTranslatef(0,0,0);
    glScalef(5,5,0.25);
    drawcube(colors[5][0],colors[5][1],colors[5][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//front
    glTranslatef(0,0,9.75);
    glScalef(5,5,0.25);
    drawcube(colors[5][0],colors[5][1],colors[5][2]);
    //drawcube();
    glPopMatrix();
}
void desk()
{
    glPushMatrix();//right
    glScalef(0.05,6,3);
    drawcube(colors[4][0],colors[4][1],colors[4][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left
    glTranslatef(5,0,0);
    glScalef(0.05,6,3);
    //drawcube();
    drawcube(colors[4][0],colors[4][1],colors[4][2]);
    glPopMatrix();

    glPushMatrix();//top
    glTranslatef(0,5,0);
    glScalef(5.0,0.05,3.0);
    drawcube(colors[12][0],colors[12][1],colors[12][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//middle
    glTranslatef(2.5,0,0);
    glScalef(0.05,5.0,3.0);
    //drawcube();
    drawcube(colors[4][0],colors[4][1],colors[4][2]);
    glPopMatrix();

    glPushMatrix();//left lower1
    glTranslatef(0,4,0);
    glScalef(2.5,0.05,3.0);
    drawcube(colors[12][0],colors[12][1],colors[12][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//right lower2
    glTranslatef(2.5,3,0);
    glScalef(2.5,0.05,3.0);
    //drawcube();
    drawcube(colors[12][0],colors[12][1],colors[12][2]);
    glPopMatrix();

    glPushMatrix();//right lower3
    glTranslatef(2.5,1,0);
    glScalef(2.5,0.05,3.0);
    drawcube(colors[12][0],colors[12][1],colors[12][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//back
    glScalef(5,6,1);
    drawcube(colors[10][0],colors[10][1],colors[10][2]);
    //drawcube();
    glPopMatrix();

}
void fan(void)
{
    glPushMatrix();//middle base
    glScalef(1,0.5,1);
    drawcube(colors[4][0],colors[4][1],colors[4][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//base 1
    glTranslatef(0.4,0.25,1);
    glScalef(0.25,0.05,2);
    drawcube(colors[0][0],colors[0][1],colors[0][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//arm 1
    glTranslatef(0,0.25,2);
    glScalef(1,0.05,5);
    drawcube(colors[0][0],colors[0][1],colors[0][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//base 2
    glTranslatef(1,0.25,0.4);
    glScalef(2,0.05,0.25);
    drawcube(colors[0][0],colors[0][1],colors[0][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//arm 2
    glTranslatef(3,0.25,0);
    glScalef(5,0.05,1);
    drawcube(colors[0][0],colors[0][1],colors[0][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//base 3
    glTranslatef(-2,0.25,0.4);
    glScalef(2,0.05,0.25);
    drawcube(colors[0][0],colors[0][1],colors[0][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//arm 3
    glTranslatef(-7,0.25,0);
    glScalef(5,0.05,1);
    drawcube(colors[0][0],colors[0][1],colors[0][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//base 4
    glTranslatef(0.4,0.25,-2);
    glScalef(0.25,0.05,2);
    drawcube(colors[0][0],colors[0][1],colors[0][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//arm 4
    glTranslatef(0,0.25,-7);
    glScalef(1,0.05,5);
    drawcube(colors[0][0],colors[0][1],colors[0][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//top base
    glScalef(0.25,1.5,0.25);
    glTranslatef(1.5,0,1.5);
    drawcube(colors[3][0],colors[3][1],colors[3][2]);
    //drawcube();
    glPopMatrix();
}
void riser_floor()
{
    glPushMatrix();
    glScalef(6,2,3);
    drawcube(0.349, 0.309, 0.345);
    //drawcube();
    glPopMatrix();
}
void table1()
{
    glPushMatrix();//right
    glScalef(0.05,5,3);
    drawcube(0.607, 0.549, 0.031);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left
    glTranslatef(5,0,0);
    glScalef(0.05,5,3);
    drawcube(0.607, 0.549, 0.031);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//top
    glTranslatef(0,5,0);
    glScalef(5.0,0.05,3.0);
    drawcube(0.584, 0.141, 0.054);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//middle
    glTranslatef(2.5,0,0);
    glScalef(0.05,5.0,3.0);
    drawcube(0.607, 0.549, 0.031);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left lower1
    glTranslatef(0,4,0);
    glScalef(2.5,0.05,3.0);
    drawcube(0.584, 0.141, 0.054);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//right lower2
    glTranslatef(2.5,3,0);
    glScalef(2.5,0.05,3.0);
    drawcube(0.584, 0.141, 0.054);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//right lower3
    glTranslatef(2.5,1,0);
    glScalef(2.5,0.05,3.0);
    drawcube(0.584, 0.141, 0.054);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//back
    glTranslatef(0,3.5,0);
    glScalef(2.5,1,1);
    drawcube(0.607, 0.549, 0.031);
    //drawcube();
    glPopMatrix();
}
void almirah()
{
    glPushMatrix();//right
    glScalef(0.05,5,3);
    drawcube(colors[11][0],colors[11][1],colors[11][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left
    glTranslatef(5,0,0);
    glScalef(0.05,5,3);
    drawcube(colors[11][0],colors[11][1],colors[11][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//top
    glTranslatef(0,4.75,0);
    glScalef(5.0,0.05,3.0);
    drawcube(colors[11][0],colors[11][1],colors[11][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//bottom
    glTranslatef(0,0.25,0);
    glScalef(5.0,0.05,3.0);
    drawcube(colors[11][0],colors[11][1],colors[11][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//back
    glTranslatef(0,0,0);
    glScalef(5,5,0.05);
    drawcube(colors[11][0],colors[11][1],colors[11][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//middle
    glTranslatef(2.25,0,0);//glRotatef(180,1,0,0);
    glScalef(0.5,5.0,3.25);
    drawcube(colors[12][0],colors[12][1],colors[12][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//front left door
    glTranslatef(0,0,3);
    glScalef(2.25,5,0.05);
    drawcube(colors[11][0],colors[11][1],colors[11][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//front right door
    glTranslatef(2.75,0,3);
    glScalef(2.25,5,0.05);
    drawcube(colors[11][0],colors[11][1],colors[11][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//lock
    glTranslatef(3.25,2.25,3);
    glScalef(0.5,0.5,0.5);
    drawcube(colors[12][0],colors[12][1],colors[12][2]);
    //drawcube();
    glPopMatrix();
}

void board()
{
    glPushMatrix();//back
    glTranslatef(0,0,0);
    glScalef(5,3,0.05);
    drawcube(colors[9][0],colors[9][1],colors[9][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//upper side
    glTranslatef(-0.25,3,0);
    glScalef(5.5,0.5,0.5);
    drawcube(colors[10][0],colors[10][1],colors[10][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//lower side
    glTranslatef(-0.25,0,0);
    glScalef(5.5,0.5,0.5);
    drawcube(colors[10][0],colors[10][1],colors[10][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left side
    glTranslatef(-0.25,0,0);
    glScalef(0.5,3.5,0.5);
    drawcube(colors[10][0],colors[10][1],colors[10][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//right side
    glTranslatef(5,0,0);
    glScalef(0.5,3.5,0.5);
    drawcube(colors[10][0],colors[10][1],colors[10][2]);
    //drawcube();
    glPopMatrix();
}

void chair()
{
    glPushMatrix();//sit part
    glScalef(5.25,0.25,4);
    glTranslatef(0,15,0);
    drawcube(0.52, 0.37, 0.26);
    //drawcube();
    glPopMatrix();

    glPushMatrix();// right leg1
    glScalef(0.25,8,0.25);
    drawcube(colors[10][0],colors[10][1],colors[10][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//left leg1
    glScalef(0.25,8,0.25);
    glTranslatef(20,0,0);
    drawcube(colors[10][0],colors[10][1],colors[10][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//uppper vertex line 1
    glScalef(5,0.25,0.25);
    glTranslatef(0,26,0);
    drawcube(0.478, 0.168, 0.043);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//uppper vertex line 2
    glScalef(5,0.25,0.25);
    glTranslatef(0,24,0);
    drawcube(0.478, 0.168, 0.043);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//uppper vertex line 3
    glScalef(5,0.25,0.25);
    glTranslatef(0,22,0);
    drawcube(0.478, 0.168, 0.043);
    //drawcube();
    glPopMatrix();

    glPushMatrix();// lower right leg
    glScalef(0.25,4,0.25);
    glTranslatef(0,0,15);
    drawcube(colors[10][0],colors[10][1],colors[10][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//lower left leg
    glScalef(0.25,4,0.25);
    glTranslatef(20,0,15);
    drawcube(colors[10][0],colors[10][1],colors[10][2]);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//lower vertex line 1
    glScalef(0.25,0.25,4);
    glTranslatef(0,1,0);
    drawcube(0.478, 0.168, 0.043);
    //drawcube();
    glPopMatrix();

    glPushMatrix();//lower vertex line 2
    glScalef(0.25,0.25,4);
    glTranslatef(20,1,0);
    drawcube(0.478, 0.168, 0.043);
    //drawcube();
    glPopMatrix();
}

void chair_table()
{
    glPushMatrix();
    glTranslatef(0,0,Tzval);
    glScalef(0.25,0.3,0.25);
    // glTranslatef(0,16,20);
    // glRotatef( theta, axis_x, axis_y, 0.0 );
    //glColor3f(0.65 , 0.50 , 0.39);
    table1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,Tzval);
    glScalef(0.2,0.2,0.25);
    glTranslatef(6.25,0,10);
    // glRotatef( theta, axis_x, axis_y, 0.0 );
    glRotatef(180,0,1,0);
    chair();
    glPopMatrix();
}
void dis()
{
    glPushMatrix();
    //glTranslatef(3,0,5);
    //glRotatef( alpha,axis_x, axis_y, 0.0 );
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    wall();
    glPopMatrix();

    glPushMatrix();
    // glTranslatef(0,0,Tzval);
    glScalef(0.5,0.25,0.25);
    glTranslatef(2.4,12,2);
    board();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0,0,Tzval);
    glScalef(0.5,0.25,0.25);
    glTranslatef(3.25,0.75,2);
    riser_floor();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0,0,Tzval);
    glScalef(0.25,0.4,0.25);
    glTranslatef(18.75,0.5,18.5);
    glRotatef(-90,0,1,0);
    almirah();
    glPopMatrix();

    glPushMatrix();
    //  glTranslatef(0,0,Tzval);
    glScalef(0.25,0.25,0.25);
    glTranslatef(6.25,0.75,5);
    //glColor3f(colors[5][0],colors[5][1],colors[5][2]);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    glRotatef(180,0,1,0);
    desk();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0,0,Tzval);
    glScalef(0.25,0.25,0.25);
    glTranslatef(10,19,20);

    glRotatef( theta, axis_x, axis_y, 0.0 );
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0.25,2);
    chair_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,0.25,2);
    chair_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0.25,5);
    chair_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,0.25,5);
    chair_table();
    glPopMatrix();
}

void show()
{
    glPushMatrix();

    if(f==0)
    {
        dis();
    }
    else
    {

        //int c=0;
        if(eyeZ>=25)
        {
            eyeZ-=0.2;
            dis();

        }
        else if(refX>=-18.75&&flag==false)
        {

            refX-=0.2;
            //eyeX-=0.2;
            // cout<<flag<<" "<<refX<<" ";
            if(refX<=-18.75) flag=true;
            dis();

            //   cout<<"eyeX :"<<eyeX<<"eyeY :"<<eyeY<<"eyeZ :"<<eyeZ<<"refx :"<<refX<<"refy :"<<refY<<"refz :"<<refZ<<endl;

        }
        else if(refZ<=25)
        {

            refZ+=0.2;
            eyeZ-=0.2;
            //cout<<refZ<<" ";
            dis();

        }
        else if(eyeZ>=-25)
        {

            eyeZ-=0.2;
            // eyeX-=0.2;
            //refX+=0.2;
            //cout<<eyeZ<<" ";

            dis();

        }

        else if(eyeX>=-18.75)
        {

            eyeX-=0.2;
            //eyeX-=0.2;
            //cout<<c<<" "<<eyeX<<endl;
            dis();

        }
        else if(refX<=4&&flag==true)
        {

            refX+=0.2;
            //cout<<flag<<" "<<refX<<endl;
            dis();
        }

        else
        {

            //  cout<<flag<<"eyeX :"<<eyeX<<"eyeY :"<<eyeY<<"eyeZ :"<<eyeZ<<"refx :"<<refX<<"refy :"<<refY<<"refz :"<<refZ<<endl;
            f=0;
            flag=false;

            //break;
        }

    }


    glPopMatrix();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor (0,0,0,0); //Color de fondo R G B
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-3,3,-3,3, 3, 150);
    // gluPerspective(90,0.95,5,100);
    //glOrtho(-5,5,-5,5, 4, 50);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  0,1,0);
    //gluLookAt(p,q,r, p1,q1,r1, 0,1,0);
    glViewport(0, 0, windowHeight, windowWidth);
    //glEnable(GL_COLOR_MATERIAL);

    glPushMatrix();
    glTranslatef(-37.5,0,-50);
    glScalef(15,10,10);
    show();
    glPopMatrix();

    glPushMatrix();
    light();
    light1();
    glRotatef(180,0,0,1);
    light2();
    glPopMatrix();


    /*glPushMatrix();
    glTranslatef(-37.5,0,-47.5);
    glScalef(75,50,2.5);
    drawcube(0,0.5,1);
    glPopMatrix();*/

    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 's':
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'Y': // move eye point upwards along Y axis
        eyeY+=0.2;
        break;
    case 'y': // move eye point downwards along Y axis
        eyeY-=0.2;
        break;
    case 'x': // move eye point left along X axis
        eyeX-=0.2;
        //cout<<"eyeX :"<<eyeX<<endl;
        break;
    case 'X': // move eye point right along X axis
        eyeX+=0.2;
        // cout<<"eyeX :"<<eyeX<<endl;
        break;
    case '+':  //zoom out
        // eyeX=0;
        eyeZ+=0.2;
        //cout<<"eyez :"<<eyeZ<<endl;
        // refZ++;
        break;
    case '-': //zoom in
        eyeZ-=0.2;
        //cout<<"eyez :"<<eyeZ<<endl;
        break;
    case 'q': //back to default eye point and ref point
        eyeX=0.0;
        eyeY=30.0;
        eyeZ=50.0;
        refX = 0 ;
        refY=30;
        refZ=0;
        f=0;
        break;
    case 'B': // move ref point upwards along Y axis
        refY+=0.2;
        break;
    case 'b': // move ref point downwards along Y axis
        refY-=0.2;
        break;
    case 'a': // move ref point left along X axis
        refX-=0.2;
        // cout<<"refx :"<<refX<<endl;
        // eyeZ-=0.2;
        break;
    case 'A': // move ref point right along X axis
        refX+=0.2;
        //cout<<"refx :"<<refX<<endl;
        //  eyeZ+=0.2;
        break;
    case 'Z':  //move ref point away from screen/ along z axis
        refZ+=0.2;
        //cout<<"refz :"<<refZ<<endl;
        break;
    case 'z': //move ref point towards screen/ along z axis
        refZ-=0.2;
        //cout<<"refz :"<<refZ<<endl;
        break;
    case 'm':
        f=1;
        break;
    /* case 'n':
         f=2;
         break;*/
    case '1': //to turn on and off light one
        if(s1 == false)
        {
            a0=true;
            d0=true;
            s0=true;
            s1 = true;
            glEnable( GL_LIGHT0);
            break;
        }
        else if(s1 == true)
        {
            a0=true;
            d0=true;
            s0=true;
            s1 = false;
            glDisable( GL_LIGHT0);
            break;
        }

    case '2': //to turn on and off light 2
        if(s2 == false)
        {
            a0=true;
            d0=true;
            s0=true;
            s2 = true;
            glEnable( GL_LIGHT1);
            break;
        }
        else if(s2 == true)
        {
            a0=true;
            d0=true;
            s0=true;
            s2 = false;
            glDisable( GL_LIGHT1);
            break;
        }
    case '3': //to turn on and off light 3
        if(s3 == false)
        {
            a0=true;
            d0=true;
            s0=true;
            s3 = true;
            glEnable( GL_LIGHT2);
            break;
        }
        else if(s3 == true)
        {
            a0=true;
            d0=true;
            s0=true;
            s3 = false;
            glDisable( GL_LIGHT2);
            break;
        }
    case '4'://ambient
        a0=true;
        d0=false;
        s0=false;
        break;
    case '5'://diffuse
        a0=false;
        d0=true;
        s0=false;
        break;
    case '6'://specular
        a0=false;
        d0=false;
        s0=true;
        break;
    case 27:    // Escape key
        exit(1);

    }

    glutPostRedisplay();
}

void animate()
{
    if (bRotate == true)
    {
        theta += 0.5;
        if(theta > 360.0)
            //theta -= 360.0*floor(theta/360.0);
            theta=0.0;
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    //glutFullScreen ();
    glutCreateWindow("classroom-Demo");

    printf("\t********** Activities **********\n");
    printf( "\tFOR RIGHT Direction(lookat), PRESS A \n");
    printf(" \tFOR LEFT Direction(lookat), PRESS a\n ");
    printf( "\tmove eye point right along X axis, PRESS X \n");
    printf(" \tmove eye point left along X axis, PRESS x\n ");
    printf( "\tmove ref point upwards along Y axis, PRESS B \n");
    printf(" \tmove ref point downwards along Y axis, PRESS b\n ");
    printf( "\tmove ref point away from screen/ along z axis, PRESS Z \n");
    printf(" \tmove ref point towards screen/ along z axis, PRESS z\n ");
    printf("\tFOR UP DIRECTION, PRESS y \n");
    printf("\tFOR DOWN DIRECTION, PRESS Y \n");
    printf("\tFOR ZOOM IN, PRESS - \n");
    printf("\tFOR ZOOM OUT, PRESS + \n");
    printf("\tFOR FAN ON OFF, PRESS s \n");
    printf("\tTo turn on and off light 1 ,press 1 \n");
    printf("\tTo turn on and off light 2 (spot light) ,press 2\n");
    printf("\tTo turn on and off light 3 ,press 3\n");
    printf("\tTo turn on and off ambient property ,press 4\n");
    printf("\tTo turn on and off diffuse property ,press 5\n");
    printf("\tTo turn on and off specular property ,press 6\n");

    printf("\tTO DEFAULT, PRESS q \n");
    printf("\tTO Movement through lookat changed, PRESS m \n");
    //printf("\tTO Movement through eyeposition changed, PRESS n \n");



    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    light();
    light1();
    glRotatef(180,0,0,1);
    light2();


    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}

