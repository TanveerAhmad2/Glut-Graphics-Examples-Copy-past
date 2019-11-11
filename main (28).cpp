#include<windows.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
#define pi acos(-1)
using namespace std;

int xdeg=0;
int ydeg=0;
int zdeg=0;

double sx=.3;
double sy=.3;
double sz=.3;

double e_x=0;
double e_y=0;
double e_z=0;

vector< pair < double , double > > roll,pitch,yaw;

int flag=0;
double zoom=1;

double r=10;
int  R=1,P=90,Y=1;

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}



void cube()
{
    glBegin(GL_QUADS);

    glVertex3f(-2,2,2);
    glVertex3f(-2,-2,2);
    glVertex3f(2,-2,2);
    glVertex3f(2,2,2);

    //glColor3d(1,0,1);
    glVertex3f(-2,2,-2);
    glVertex3f(-2,-2,-2);
    glVertex3f(-2,-2,2);
    glVertex3f(-2,2,2);

    //glColor3d(1,0,0);
    glVertex3f(-2,-2,-2);
    glVertex3f(-2,2,-2);
    glVertex3f(2,2,-2);
    glVertex3f(2,-2,-2);

    //glColor3d(0,1,1);
    glVertex3f(2,2,2);
    glVertex3f(2,-2,2);
    glVertex3f(2,-2,-2);
    glVertex3f(2,2,-2);

    //glColor3d(0,0,0);
    glVertex3f(-2,2,2);
    glVertex3f(2,2,2);
    glVertex3f(2,2,-2);
    glVertex3f(-2,2,-2);

    //glColor3d(1,1,0);
    glVertex3f(-2,-2,2);
    glVertex3f(-2,-2,-2);
    glVertex3f(2,-2,-2);
    glVertex3f(2,-2,2);

    glEnd();
}

void cylinder(double r1=3,double r2=3,int flag=1){
    vector< pair < double,double > >point,point2;
    double r=r1;
    for(int i=0;i<360;i++){
        double x = r * cos( i * pi / 180 );
        double y = r * sin( i * pi / 180 );

        point.push_back(make_pair(x,y));
        x = r2 * cos( i * pi / 180 );
        y = r2 * sin( i * pi / 180 );
        point2.push_back(make_pair(x,y));
    }
    glBegin(GL_POLYGON);
            int sz=point.size()-1;
            for(int i=0;i<=sz;i++){
                glVertex3f(point[i].first,point[i].second,5);
            }
    glEnd();
    glBegin(GL_POLYGON);
            sz=point.size()-1;
            for(int i=sz;i>=0;i--){
                glVertex3f(point2[i].first,point2[i].second,-5);
            }
    glEnd();
    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<point.size();i++){
            if(!flag){
                int k=i%20;
                if(k>=0 and k<=10 ){
                    glColor3d(0,0,1);
                }
                else glColor3d(1,0,0);
            }
            glVertex3f(point[i].first,point[i].second,5);
            glVertex3f(point2[i].first,point2[i].second,-5);
        }
        glVertex3f(point[0].first,point[0].second,5);
        glVertex3f(point2[0].first,point2[0].second,-5);
    glEnd();
}

void boltu(double z){
    glColor3d(0,0,1);
    glPushMatrix();
        glTranslated(0,0,z);
        glScalef(.5,.5,.5);
        cube();
    glPopMatrix();
}

void wheel(double deg){
    glPushMatrix();
        glPushMatrix();
            glTranslated(-4,-2.5,4);
            glColor3d(1,0,0);
            glScalef(.75,.75,.1);
            glRotatef(deg,0,0,1);
            cylinder(3,3,0);
        glPopMatrix();

        glPushMatrix();
            glTranslated(-4,-2.5,-4);
            glColor3d(1,0,0);
            glScalef(.75,.75,.1);
            glRotatef(deg,0,0,1);
            cylinder(3,3,0);
        glPopMatrix();

        glPushMatrix();
            glTranslated(4,-2.5,4);
            glColor3d(1,0,0);
            glScalef(.75,.75,.1);
            glRotatef(deg,0,0,1);
            cylinder(3,3,0);
        glPopMatrix();

        glPushMatrix();
            glTranslated(4,-2.5,-4);
            glColor3d(1,0,0);
            glScalef(.75,.75,.1);
            glRotatef(deg,0,0,1);
            cylinder(3,3,0);
        glPopMatrix();
    glPopMatrix();
}

void glass(){
    glPushMatrix();
            glColor3d(0,0,1);
            glTranslatef(-1,4,3);
            glScalef(1.1,.5,.2);
            cube();
    glPopMatrix();
}

void fourglass(){
        glass();
        glPushMatrix();
            glTranslatef(0,0,-1.1);
            glScalef(.8,1,1);
            glRotatef(90,0,1,0);
            glass();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2,0,0);
            glRotatef(180,0,1,0);
            glass();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2,0,1.1);
            glScalef(.8,1,1);
            glRotatef(-90,0,1,0);
            glass();
        glPopMatrix();
}



void init(){
    R += 360;
    R %= 360;
    P += 360;
    P %= 360;
    Y += 360;
    Y %= 360;
}




void headlight(){
        glPushMatrix();
            glColor3d(1,0,0);
            glTranslatef(7,1.5,2);
            glRotated(-90,0,1,0);
            glScalef(.6,.6,.07);

            cylinder(2,1);
        glPopMatrix();

        glPushMatrix();
            glColor3d(1,0,0);
            glTranslatef(7,1.5,-2);
            glRotated(-90,0,1,0);
            glScalef(.6,.6,.07);

            cylinder(2,1);
        glPopMatrix();
}


static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    init();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(e_x,e_y,e_z,0,0,-10,0,1,0);

    glColor3d(0,1,0);
    glPushMatrix();
        glTranslated(0,0,-10);
        glScalef(sx*zoom,sy*zoom,sz*zoom);
        glRotated(xdeg,1,0,0);
        glRotated(ydeg,0,1,0);
        glRotated(zdeg,0,0,1);

        glPushMatrix(); ///body
            glColor3d(0,1,0);
            glScalef(3.5,1.5,2);
            cube();
        glPopMatrix();

        wheel(-a);

        glColor3d(1,0,0);
        glPushMatrix();   ///head
            glTranslatef(-1,3,0);
            glScalef(1.5,1.5,1.5);
            cube();
        glPopMatrix();
        fourglass();
        headlight();

        glColor3d(0,0,0);
        glPushMatrix(); /// shamner bar
            glTranslatef(7,-1.8,0);
            glScalef(.2,.3,1.8);
            cube();
        glPopMatrix();
        glColor3d(0,0,1);
        glPushMatrix(); ///picher bar
            glTranslatef(-7,-1.8,0);
            glScalef(.2,.3,1.8);
            cube();
        glPopMatrix();

        glColor3d(1,0,0);
        glPushMatrix(); /// lal bar
            glTranslatef(-7,1,0);
            glScalef(.2,.3,1.8);
            cube();
        glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'x':
            if(flag==4)e_x++;
            else xdeg+=3;
            break;
        case 'y':
            if(flag==4)e_y++;
            else ydeg+=3;
            break;
        case 'z':
            if(flag==4)e_z++;
            else zdeg+=3;
            break;
       case 'X':
            if(flag==4)e_x--;
            else xdeg-=3;
            break;
        case 'Y':
            if(flag==4)e_y--;
            else ydeg-=3;
            break;
        case 'Z':
            if(flag==4)e_z--;
            else zdeg-=3;
            break;


        case 'a':
            sx+=.2;
            break;
        case 'b':
            sy+=.2;
            break;
        case 'c':
            sz+=.2;
            break;
        case 'A':
            sx-=.2;
            break;
        case 'B':
            sy-=.2;
            break;
        case 'C':
            sz-=.2;
            break;

        case 'r':
            cout<<"Roll mode on"<<endl;
            flag=1;
            break;
        case 'p':
            cout<<"Pitch mode on"<<endl;
            flag=2;
            break;
        case 'i':
            cout<<"Yaw mode on"<<endl;
            flag=3;
            break;
        case 'n':
            flag=0;
            cout<<"Normal Mode on"<<endl;
            break;

        case 'l':
            cout<<"LookAt mode on"<<endl;
            flag=4;
            break;

        case '+':
            if(flag==0)zoom+=.2;
            else if(flag==1){
                e_x = r * cos( R * pi / 180 );
                e_y = r * sin( R * pi / 180 );
                R++;

            }
            else if(flag==2){
                e_y = r * cos( P * pi / 180 );
                e_z = r * sin( P * pi / 180 )-10;
                P++;
            }
            else if(flag==3){
                e_x = r * cos( Y * pi / 180 );
                e_z = r * sin( Y * pi / 180 )-10;
                Y++;
            }
            break;
        case '-':
            if(flag==0)zoom-=.2;
            else if(flag==1){
                e_x = r * cos( R * pi / 180 );
                e_y = r * sin( R * pi / 180 );
                R--;
            }
            else if(flag==2){
                e_y = r * cos( P * pi / 180 );
                e_z = r * sin( P * pi / 180 )-10;
                P--;
            }
            else if(flag==3){
                e_x = r * cos( Y * pi / 180 );
                e_z = r * sin( Y * pi / 180 )-10;
                Y--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Car");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutMainLoop();

    return EXIT_SUCCESS;
}
