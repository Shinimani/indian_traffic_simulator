#include "common.hpp"
#include "vehicle.hpp"
#include "road.hpp"
#include "Parser.hpp"
#include <ctime>
#include <GL/glut.h>
#include <math.h>

Road r;
int mat_len, mat_wid;
vector<Vehicle> list_vehicle, Signals;
int k = 0;


void common(string s,string initType);


//List of OpenGL functions 
void myinit();
void mydisplay();
void display();
void idle();

void disp();
void vehicles(Vehicle);

//list of the different vehicles that can be drawn
void car(vector<tuple<int, int> > corners, vector<float> acolour);
void bus(vector<tuple<int, int> > corners, vector<float> acolour);
void truck(vector<tuple<int, int> > corners, vector<float> acolour);
void rikshaw(vector<tuple<int, int> > corners, vector<float> acolour);
void bike(vector<tuple<int, int> > corners, vector<float> acolour);

//list of basic figures  that can be drawn
void drawCircle(float cx, float cy, float r, int num_segments, vector<float> acolour);
void rectangle(float x1, float y1, float x2, float y2, vector<float> acolour);
void triangle (float x1, float y1, float x2, float y2, float x3, float y3, vector<float> acolour);

//Function to print vehicles
void vehicle(Vehicle);

//Function to print road
void Roadp();

int GLowerBound(vector<int> temp, float value);
void dispSignal(int column, vector<int> list);

vector<float> getRGBValue(string s);


int main(int argc, char **argv){
    srand(time(0));
    int c = stoi(argv[1]);
    string a = argv[3];
    string initType = argv[2];
    if(c == 1){
        common(a,initType);
    // cout <<typeid(mat_len).name()<<" "<<mat_len<<" "<<mat_len+(mat_len/10)<<" "<<typeid(mat_len+(mat_len/10)).name();

        r.Simulation(mat_len,mat_wid);

    }else{
            //opengl code
         common(a,initType);

         glutInit(&argc, argv);

         glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
         glutInitWindowSize(1600, 400);
         glutInitWindowPosition(0,0);
         glutCreateWindow("Traffic signal");

         //call back functions
        
         
         myinit();

         glutIdleFunc(display);
         glutDisplayFunc(display);


         glutMainLoop();
    }

        
return 0;

}


void common(string s,string initType){

    vector<vector<string> > temp = Parser(s);
    vector<Vehicle> vh1 = InitVehicles(temp);

    mat_len = RoadLen(temp);
    mat_wid = RoadWid(temp);
    
    //10% road hidden for collision handling

    r.Init_road(mat_wid, mat_len);

    vector<Vehicle> list_vehicle1 = GetVehicle(temp, vh1);

    Signals = GetSignals(list_vehicle1);
    for(int i=0; i<Signals.size(); i++){
        for (int j =0; j< Signals[i].Get_free_area().size(); j++){
            cout<<Signals[i].Get_free_area()[j]<<" ";
        }
        cout<<endl;
        r.Set_signal(Signals[i].Get_lenth(), Signals[i].Get_free_area());
    }

    list_vehicle = GetVehicles(list_vehicle1);

    vector<int> signaltime = GetSignalPosition(temp);
    
     r.Add_vehicles(list_vehicle);
     if (initType == "normal"){
         r.New_initializer(mat_len,mat_wid);
     }else{
        r.Vehicle_intializer(mat_len,mat_wid);
     }
     r.getAllVehSize();
     r.setAllVehSize();
}

void display(){
    while(r.Sim_fin()){
        r.LoopSimulation(mat_len,mat_wid);
        mydisplay();
    }

}

void disp(){
    glClearColor(0.0, 1.0, 0.0, 0.0); 
    
    vector<Vehicle> list = r.Get_vehicles();
    

    for(int i=0; i<list.size(); i++){
            if(r.time == 1000){
                vector<tuple<int, int> > corners = {make_tuple(1,2), make_tuple(3,2), make_tuple(3,0), make_tuple(1,0)};
                car(corners,getRGBValue(list[0].GetColour()) );
                
            }
            r.time += 1;
    }
    glFlush();
    glutSwapBuffers(); 

}

void vehicles(Vehicle a ){

    car(a.getCorners(), getRGBValue(a.GetColour()));

}

void mydisplay(){
    
    Roadp();

    vector<Vehicle> list = r.Get_vehicles();

    for(int i=0; i<list.size(); i++){
        if(list[i].Get_start_time()<r.time){
            vehicle(list[i]);
        }
        
    }   
    
    glFlush();
    glutSwapBuffers();  
}

//Function for printing Road
void Roadp(){

    glBegin(GL_QUADS);

    //setting the dark grey colour for the road
    glColor3f(0.411, 0.411, 0.411);

    //defigning the length and width of the road
    //cout<<mat_len*50<<" "<<mat_wid*20<<endl;
    glVertex2i(0,0);
    glVertex2i(mat_len*50,0);
    glVertex2i(mat_len*50 ,mat_wid*50);
    glVertex2i(0,mat_wid*50);

    glEnd();

}

int GLowerBound(vector<int> temp, float value){

    int count; 

    for(int i=0; i<temp.size(); i++){

        if(abs(temp[i]) < value){

        }else{
            cout<<" "<<temp[i-1]<<" "<<value<<endl;
            count = temp[i-1];
            if(temp[i-1]>=0){
                return 1;
            }else{
                return -1;
            }
        }
    }
    cout<<endl;
    
    if(temp[temp.size()-1]>= 0 ){
        return 1;
    }else{
        return -1;
    }
    

}

void vehicle(Vehicle temp){

        vector<tuple <int,vector<int> > > signal = r.Get_signals();

        for(int i=0; i<signal.size(); i++){

            dispSignal(get<0>(signal[i]), get<1>(signal[i]));

        }

                vector<tuple<int, int> > corners = temp.getCorners();
                string c = temp.GetColour();
                vector<float> acolour =  getRGBValue(c);
                car(corners, acolour);


}


void dispSignal(int column, vector<int> list){
        int check = GLowerBound(list, r.time);

        if(check <0){
            glColor3f(getRGBValue("RED")[0], getRGBValue("RED")[1], getRGBValue("RED")[2]);

        }else{

            glColor3f(getRGBValue("GREEN")[0], getRGBValue("GREEN")[1], getRGBValue("GREEN")[2]);

            }
                
        glBegin(GL_QUADS);

        glVertex2i(column*50,0);
        glVertex2i(column*50+10,0);
        glVertex2i(column*50+10,mat_wid*50);
        glVertex2i(column*50,mat_wid*50);
        
        glEnd();

}





void myinit(){

    glPointSize(1.0); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    // Set window size in X- and Y- direction 
    gluOrtho2D(0.0, mat_len*50-500, 0.0, mat_wid*50); 

    // Reset background color with white (since all three argument is 1.0) 
    glClearColor(0.0, 1.0, 0.0, 0.0); 
  
}

//function to get the colour in RGB value
vector<float> getRGBValue(string s){
    
    vector<float> color;
    if(s.compare("BLACK")== 0){
        color.push_back(0.0);
        color.push_back(0.0);
        color.push_back(0.0);

    }else{
        if(s.compare("RED")==0){
            color.push_back(1.0);
            color.push_back(0.0);
            color.push_back(0.0);
        }else{
            if(s.compare("GREEN")==0){
                color.push_back(0.0);
                color.push_back(1.0);
                color.push_back(0.0);
            }else{
                if(s.compare("BLUE")==0){
                    color.push_back(0.0);
                    color.push_back(0.0);
                    color.push_back(1.0);
                }else{
                    color.push_back(1.0);
                    color.push_back(1.0);
                    color.push_back(0.0);
                }
                
            }
        }
    }
    return color;
}

void car(vector<tuple<int, int> > corners, vector<float> acolour){
    int x1 = get<0>(corners[0])*50;
    int y1 = (get<1>(corners[0])*50) +10;

    int x2 = get<0>(corners[1])*50;
    int y2 = (get<1>(corners[1])*50)+10;

    int x3 = get<0>(corners[2])*50;
    int y3 = (get<1>(corners[2])*50);

    int x4 = get<0>(corners[3])*50;
    int y4 = (get<1>(corners[3])*50);

    float sq_x = (x1+x2)/2;
    float sq_y = (y4+3*y1)/4;

    float tr_x = (3*x2+x1)/4;
    float tr_y = (3*y4+y1)/4;

    // cout<<x1<<" "<<y1<<endl;
    // cout<<x2<<" "<<y2<<endl;
    // cout<<x3<<" "<<y3<<endl;
    // cout<<x4<<" "<<y4<<endl;
    // cout<<sq_x<<" "<<sq_y<<endl;
    // cout<<tr_x<<" "<<tr_y<<endl;

    // cout<<x1<<" "<<tr_y<<endl;
    // cout<<x1<<" "<<sq_y<<endl;
    // cout<<tr_x<<" "<<sq_y<<endl;
    // cout<<sq_x<<" "<<tr_y<<endl;

    rectangle(x1, tr_y, x3, y3, acolour);


    // trapezium part
    glBegin(GL_QUADS);
    glColor3f(acolour[0], acolour[1], acolour[2]);

    glVertex2i(x1, y1);
    glVertex2i(sq_x, y1);
    glVertex2i(tr_x, tr_y);
    glVertex2i(x1, tr_y);

    glEnd();

    //Headlight part
    x4 = (11*x3 + x4)/12;
    
    rectangle(x4, tr_y, x3, y3, getRGBValue("YELLOW"));

}

void truck(vector<tuple<int, int> > corners, vector<float> acolour){

}

void drawCircle(float cx, float cy, float r, int num_segments, vector<float> acolour){

    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}

void rectangle(float x1, float y1, float x2, float y2, vector<float> acolour){
        glBegin(GL_QUADS);
        glColor3f(acolour[0], acolour[1], acolour[2]);

            glVertex2i(x1, y1);
            glVertex2i(x1, y2);
            glVertex2i(x2, y2);
            glVertex2i(x2, y1);

        glEnd();

}

void triangle(float x1 , float y1, float x2, float y2, float x3, float y3, vector<float> acolour){
    glBegin(GL_TRIANGLES);
    glColor3f(acolour[0], acolour[1], acolour[2]);
        
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glVertex2i(x3, y3);

    glEnd();
    
}