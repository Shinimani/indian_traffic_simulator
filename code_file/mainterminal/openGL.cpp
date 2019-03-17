#include "common.hpp"
#include "vehicle.hpp"
#include "road.hpp"
#include "Parser.hpp"
#include <ctime>
#include <GL/glut.h>

vector<Vehicle> InitVehicles(vector<vector<string> > prased);
vector<vector<string> > Parser(string name);
vector<Vehicle> GetSignals(vector<Vehicle> temp);
vector<Vehicle> GetVehicles(vector<Vehicle> temp);

void myinit();
void mydisplay();



//Function to print vehicles
void vehicle();

//Function to print road
void Roadp();

Road r;
int mat_len, mat_wid;

int main(int argc, char** argv)
{   

    glutInit(&argc, argv);
    vector<vector<string> > temp = Parser("Mayank.ini");

    mat_len = RoadLen(temp)*50;
    mat_wid = RoadWid(temp)*20;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(mat_len, mat_wid);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Traffic signal");

    //setScreensize();

    /*call back functions*/
    glutDisplayFunc(mydisplay);


    myinit();
    glutDisplayFunc(mydisplay);
    glutMainLoop();
    return 0;
}
void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);

    Roadp();


    glutSwapBuffers(); 
}

//Function for printing Road
void Roadp(){
    glBegin(GL_QUADS);
    //setting the dark grey colour for the road
    glColor3f(0.411, 0.411, 0.411);
    
    //defigning the length and width of the road
    glVertex2i(0,0);
    glVertex2i(mat_len,0);
    glVertex2i(mat_len,mat_wid);
    glVertex2i(0,mat_wid);

    glEnd();
}

void vehicle(){
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(0,0);
    glVertex2i(0,100);
    glVertex2i(600,100);
    glVertex2i(600,0);
    glEnd();
}


void myinit(){

    // Reset background color with white (since all three argument is 1.0) 
    glClearColor(1.0, 1.0, 1.0, 0.0); 
  
    // Set picture color to red (in RGB model) 
    // as only argument corresponding to R (Red) is 1.0 and rest are 0.0 
    glColor3f(1.0f, 0.0f, 0.0f); 
  
    // Set width of point to one unit 
    glPointSize(1.0); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
  
    // Set window size in X- and Y- direction 
    gluOrtho2D(0, mat_len, 0, mat_wid); 
}

