#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <math.h>

#define dimension 300

using namespace std;

unsigned char prevKey;

class GrilaCarteziana{
public:
    GrilaCarteziana(int cols,int rows){
        this->rows = rows;
        this->cols = cols;
        this->c0 = -1.0;
        this->l0 = -1.0;

    }
    GrilaCarteziana(){
        this->cols = 10;
        this->rows = 10;
        this->c0 = -1.0;
        this->l0 = -1.0;

    }
    void writePixel(){

    }
    void drawCartGrid(){
        double c1 = this->c0 + (double)(this->cols) - 1.0;
        double l1 = this->l0 + (double)this->rows - 1.0;

        double dl = (double)((2.0-2.0*this->epsilon)/((double)(this->rows) - 1.0));
        double dc = (double)((2.0-2.0*this->epsilon)/((double)(this->cols) - 1.0));


        for(int i = 0;i < this->cols;i++){
            glColor3f(0.2,0.15,0.8);
            glBegin(GL_LINE_STRIP);
            glVertex2f(-1.0 + this->epsilon + i * dc,-1.0 + this->epsilon);
            glVertex2f(-1.0 + this->epsilon + i * dc,1.0 - this->epsilon);
            glEnd();
        }
        for(int i = 0;i < this->rows;i++){
            glColor3f(0.2,0.15,0.8);
            glBegin(GL_LINE_STRIP);
            glVertex2f(-1.0 + this->epsilon ,-1.0 + this->epsilon + i*dl);
            glVertex2f(1.0 - this->epsilon ,-1.0 + this->epsilon + i*dl);
            glEnd();
        }

    }
    void setCols(int cols){
        this->cols=cols;
    }

    void setRows(int rows){
        this->rows=rows;
    }

    ~GrilaCarteziana(){}
private:
    int cols;
    int rows;
    double c0;
    double l0;
    double epsilon = 0.03;
    vector<vector<int>> pixels;
};

GrilaCarteziana gc;


void Init(void) {
   glClearColor(1.0,1.0,1.0,1.0);
   glLineWidth(1);
   glPointSize(4);
   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   gc.drawCartGrid();
   glFlush();
}

void Reshape(int w, int h) {
   printf("Call Reshape : latime = %d, inaltime = %d\n", w, h);
   gc.drawCartGrid();
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}


void KeyboardFunc(unsigned char key, int x, int y) {
   prevKey = key;
   if (key == 27) // escape
      exit(0);
   glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
   printf("Call MouseFunc : ati %s butonul %s in pozitia %d %d\n",
      (state == GLUT_DOWN) ? "apasat" : "eliberat",
      (button == GLUT_LEFT_BUTTON) ?
      "stang" :
      ((button == GLUT_RIGHT_BUTTON) ? "drept": "mijlociu"),
      x, y);
}

int main(int argc, char** argv) {

   gc.setCols(12);
   gc.setRows(12);

   glutInit(&argc, argv);

   glutInitWindowSize(dimension, dimension);

   glutInitWindowPosition(100, 100);

   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   glutCreateWindow (argv[0]);

   Init();

   glutReshapeFunc(Reshape);

   glutKeyboardFunc(KeyboardFunc);

   glutMouseFunc(MouseFunc);

   glutDisplayFunc(Display);

   glutMainLoop();

   return 0;
}
