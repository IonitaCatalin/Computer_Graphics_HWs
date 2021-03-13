#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// dimensiunea ferestrei in pixeli

#define dim 300

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
   double xmax, ymax, xmin, ymin;
   double a = 1, b = 2;
   double pi = 4 * atan(1);
   double ratia = 0.05;

   // calculul valorilor maxime/minime ptr. x si y
   // aceste valori vor fi folosite ulterior la scalare
   xmax = a - b - 1;
   xmin = a + b + 1;
   ymax = ymin = 0;
   for (double t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = a + b * cos(t);
      xmax = (xmax < x1) ? x1 : xmax;
      xmin = (xmin > x1) ? x1 : xmin;

      x2 = a - b * cos(t);
      xmax = (xmax < x2) ? x2 : xmax;
      xmin = (xmin > x2) ? x2 : xmin;

      y1 = a * tan(t) + b * sin(t);
      ymax = (ymax < y1) ? y1 : ymax;
      ymin = (ymin > y1) ? y1 : ymin;

      y2 = a * tan(t) - b * sin(t);
      ymax = (ymax < y2) ? y2 : ymax;
      ymin = (ymin > y2) ? y2 : ymin;
   }

   xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
   ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP);
   for (double t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();

   glBegin(GL_LINE_STRIP);
   for (double t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x2,y2);
   }
   glEnd();
}

// graficul functiei
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$,
void Display2() {
   double pi = 4 * atan(1);
   double xmax = 8 * pi;
   double ymax = exp(1.1);
   double ratia = 0.05;

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP);
   for (double x = 0; x < xmax; x += ratia) {
      double x1, y1;
      x1 = x / xmax;
      y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();
}

void Display3() {

   //functia distanta

   double ratia = 0.01;
   double xmax = 100;

   glColor3f(1,0.1,0.1); // rosu

   glBegin(GL_LINE_STRIP);
   for (double x = 0; x <= xmax; x += ratia) {
        double x1, y1;
        if (x == 0){
           y1 = 1;
        }
        else{
            if(ceil(x) - x < x - floor(x)){
                y1 = (ceil(x) - x)/x;
            }else{
                y1 = (x - floor(x))/x;
            }
        }

      x1 = x/xmax;
      glVertex2f(x1,y1);
   }
   glEnd();
}


void Display4() {
    //melcul lui Pascal

   double ratia = 0.01;
   double pi = 4 * atan(1);
   double a = 0.3;
   double b = 0.2;
   double tmax = pi;

   glColor3f(1,0.1,0.1); // rosu

   glBegin(GL_LINE_STRIP);
   for (double t = -pi + ratia; t < tmax; t += ratia) {

      double x = 2 * (a * cos(t) + b) * cos(t);
      double y = 2 * (a * cos(t) + b) * sin(t);

      glVertex2f(x - 0.1, y);
   }
   glEnd();
}

void Display5() {
    //trisectoarea lui Longchamps

   double ratia = 0.005;
   double pi = 4 * atan(1);
   double a = 0.2;

   //cadran

    double tmax = -0.58;

    //primul punct y
    double y1 = (a*tan(-pi/2 + 14*ratia))/(4*pow(cos(-pi/2 + 14*ratia), 2) - 3);
    //ultimul punct x
    double x2;

   glColor3f(0.1,0.1,1); // albastru
   glBegin(GL_LINE_LOOP);
   for (double t = -pi/2 + 14*ratia; t < tmax; t += ratia) {
        double x = a/(4*pow(cos(t), 2) - 3);
        double y = (a*tan(t))/(4*pow(cos(t), 2) - 3) ;
        glVertex2f(x, y);
        x2 = x;
   }
   glVertex2d(x2, y1);
   glEnd();

   //desenam primul set de triunghiuri t in (-pi/2 + 0.005 * 14, -1.3)
   tmax = -1.3;
   glColor3f(1,0.1,0.1);
   glBegin(GL_TRIANGLES);
   int step = 0;
   for (double t = -pi/2 + 14*ratia; t < tmax; t += ratia) {
        double x = a/(4*pow(cos(t), 2) - 3);
        double y = (a*tan(t))/(4*pow(cos(t), 2) - 3);

        if (step % 3 != 0){
            glVertex2d(x, y);
        }else{
            glVertex2d(x2, y1);
        }

        step++;
   }
   glEnd();


   //desenam al doilea set de triunghiuri t in (-0.75, -0.58)
   tmax = -0.58;
   glColor3f(1,0.1,0.1);
   glBegin(GL_TRIANGLES);
   step = 0;
   for (double t = -0.75; t < tmax; t += ratia) {
        double x = a/(4*pow(cos(t), 2) - 3);
        double y = (a*tan(t))/(4*pow(cos(t), 2) - 3);

        if (step % 3 != 0){
            glVertex2d(x, y);
        }else{
            glVertex2d(x2, y1);
        }

        step++;
   }
   glEnd();
}

void Display6() {
    //cicloida

   double ratia = 0.01;
   double a = 0.1;
   double b = 0.2;


   double tmax = 9.4;


   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu

   glBegin(GL_LINE_STRIP);
   for (double t = -9.4; t < tmax; t += ratia) {

    double x = a * t - b * sin(t);
    double y = a - b * cos(t);

    glVertex2f(x, y);

   }
   glEnd();
}

void Display7() {
    //epicicloida

   double ratia = 0.01;
   double R = 0.1;
   double r = 0.3;

   double pi = 4 * atan(1);
   double tmax = pi*2;


   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu

   glBegin(GL_LINE_STRIP);
   for (double t = 0; t <= tmax; t += ratia) {

    double x = (R + r)*cos((r/R)*t) - r*cos(t + (r/R)*t);
    double y = (R + r)*sin((r/R)*t) - r*sin(t + (r/R)*t);

    glVertex2f(x, y);

   }
   glEnd();
}

void Display8() {
    //hipocicloida

   double ratia = 0.01;
   double R = 0.1;
   double r = 0.3;

   double pi = 4 * atan(1);
   double tmax = pi*2;


   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu

   glBegin(GL_LINE_STRIP);
   for (double t = 0; t <= tmax; t += ratia) {

    double x = (R - r)*cos((r/R)*t) - r*cos(t - (r/R)*t);
    double y = (R - r)*sin((r/R)*t) - r*sin(t - (r/R)*t);

    glVertex2f(x, y);

   }
   glEnd();
}

void Display9() {
    //lemniscata lui Bernoulli

   double ratia = 0.01;
   double a = 0.4;

   double pi = 4 * atan(1);
   double tmax = pi*2;

   glColor3f(1,0.1,0.1); // rosu

   glBegin(GL_LINE_STRIP);
   for (double t = -pi/4 + ratia; t < tmax; t += ratia) {
        double r = a * sqrt(2 * cos(2*t));
        double x = r * cos(t);
        double y = r * sin(t);
        glVertex2f(x, y);
   }
   glEnd();


   glBegin(GL_LINE_STRIP);

   double r = a * sqrt(2 * cos(2*(-pi/4 + ratia)));
   double x1 = r * cos(-pi/4 + ratia);
   double y1 = r * sin(-pi/4 + ratia);

   double x2 = -r * cos(-pi/4 + ratia);
   double y2 = -r * sin(-pi/4 + ratia);

   glVertex2f(x1, y1);
   glVertex2f(x2, y2);
   glEnd();

}

void Display10() {
    //spirala logaritmica

   double ratia = 0.01;
   double a = 0.02;

   double pi = 4 * atan(1);


   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu

   glBegin(GL_LINE_STRIP);
   for (double t = 0; t <= 100; t += ratia) {
    double r = a * exp(1+t);
    double x = r * cos(t);
    double y = r * sin(t);

    glVertex2f(x, y);
   }
   glEnd();
}

void Init(void) {

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

//   glPointSize(4);

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   switch(prevKey) {
   case '1':
      Display1();
      break;
   case '2':
      Display2();
      break;
   case '3':
      Display3();
      break;
   case '4':
      Display4();
      break;
   case '5':
      Display5();
      break;
   case '6':
      Display6();
      break;
   case '7':
      Display7();
      break;
   case '8':
      Display8();
      break;
   case '9':
      Display9();
      break;
   case '0':
      Display10();
      break;
   default:
      break;
   }

   glFlush();
}

void Reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
   prevKey = key;
   if (key == 27) // escape
      exit(0);
   glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

   glutInit(&argc, argv);

   glutInitWindowSize(dim, dim);

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
