#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

#define dimension 300

using namespace std;

unsigned char prevKey;

class GrilaCarteziana{
public:
    GrilaCarteziana(int cols,int rows){
        this->rows = rows;
        this->cols = cols;

    }
    GrilaCarteziana(){
        this->cols = 10;
        this->rows = 10;
    }
    void draw(int width,int height){
        for(int i=0;i < this->rows ;++i){
            vector<int> row;
            for(int j=0;j < this->cols;++j){
                row.push_back(0);
            }
            pixels.push_back(row);
        }
        double widthDistance,heightDistance;
        widthDistance = (double)(width)/(double)(this->cols);
        heightDistance = (double)(height)/double(this->rows);

        widthDistance = widthDistance < heightDistance ? widthDistance : heightDistance;
        heightDistance = heightDistance < widthDistance ? heightDistance : widthDistance ;

        double widthScale = -1 + (2/(widthDistance*this->cols))*(widthDistance);
        double heightScale = -1 + (2/(heightDistance*this->rows))*(heightDistance);

        cout<<widthScale<<" "<<heightScale<<endl;

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
    vector<vector<int>> pixels;
};

GrilaCarteziana gc;


void Init(void) {
   glClearColor(1.0,1.0,1.0,1.0);
   glLineWidth(3);
   glPointSize(4);
   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   gc.draw(dimension,dimension);
   glFlush();
}

void Reshape(int w, int h) {
   printf("Call Reshape : latime = %d, inaltime = %d\n", w, h);
   gc.draw(w,h);
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

   gc.setCols(9);
   gc.setRows(9);

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
