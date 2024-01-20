#include<GL/freeglut.h>

struct screen_point_struct {
    GLint x , y ;
    };

class Point_on_screen {
private:
     GLint x , y ;

public:
    Point_on_screen() {
     x = 0 ;
     y = 0 ;
    }
    void setcord (GLint x_val , GLint y_val ){
        x =  x_val ;
        y =  y_val ;

    }
    GLint getx() const {
         return x;
      }
    GLint gety() const {
         return y;
      }
    void incx() {
         ++x;
      }
    void incy() {
         --y;
      }

};
// set a point in quaractor one
void setpixel(GLint x ,GLint y  ){

glBegin(GL_POINTS);
glVertex2i(x, y ) ;
glEnd();
}


// set a point in quaractor one
void plotfourpoint(screen_point_struct center,Point_on_screen p){
setpixel(center.x + p.getx() , center.y + p.gety() );
setpixel(center.x - p.getx() , center.y + p.gety() );
setpixel(center.x + p.getx() , center.y - p.gety() );
setpixel(center.x - p.getx() , center.y - p.gety() );
}

void midpointal(screen_point_struct center , GLint rx , GLint ry ){

   Point_on_screen curent_point;
   curent_point.setcord(0 , ry );
   GLint p1 = ry*ry - rx*rx*ry + 0.25*rx*rx ;
   GLint dx = 2 * ry * ry * curent_point.getx();
   GLint dy = 2 * rx *rx * curent_point.gety();

   while( dx < dy ){
    plotfourpoint(center , curent_point);
    curent_point.incx();

    if(p1 < 0 ){
        dx = 2 * ry * ry * curent_point.getx();
        p1 = p1 + dx +  ry*ry  ;
    }
    else {
            curent_point.incy();
            dx = 2 * ry * ry * curent_point.getx();
            dy = 2 * rx *rx * curent_point.gety();
             p1 = p1 + dx +  ry*ry  - dy ;

    }
   }

   GLint p2 =
   ry * ry * (curent_point.getx() + 0.5 )*(curent_point.getx() + 0.5)
   + rx * rx * (curent_point.gety() - 1) *(curent_point.gety() - 1) - rx*rx*ry*ry ;

    while( curent_point.gety() >= 0  ){
    plotfourpoint(center , curent_point);
    curent_point.incy();

    if(p2 > 0 ){
         dy = 2 * rx *rx * curent_point.gety();
        p2 = p2 - dy +  rx*rx  ;
    }
    else {
            curent_point.incx();
            dx = 2 * ry * ry * curent_point.getx();
            dy = 2 * rx *rx * curent_point.gety();
             p2 = p2 + dx +  rx*rx  - dy ;

    }
   }


};




 void init(){
 glClearColor(1.0 , 1.0 ,1.0 , 1.0 );
 glMatrixMode(GL_PROJECTION) ;
 gluOrtho2D(0,600, 0,600);

 };

void display() {
glClear(GL_COLOR_BUFFER_BIT) ;
glPointSize(5);
screen_point_struct center ;
center.x = 300 ;
center.y = 300 ;
glColor3f(0.0 , 0.0 , 1.0);

//
midpointal(center , 200 ,100 );
glFlush();


    }






int main(int argc , char **argv ){
    glutInit(&argc , argv );
     glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutCreateWindow("eillipes");
   init();
  glutDisplayFunc(display);
   glutMainLoop();
   return 0;

}















