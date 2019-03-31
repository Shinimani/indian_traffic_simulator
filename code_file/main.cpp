#include "common.hpp"
#include "vehicle.hpp"
#include "road.hpp"
#include "Parser.hpp"
#include <ctime>
#include <GL/glut.h>

Road r;
int mat_len, mat_wid;
vector<Vehicle> list_vehicle, Signals;

void common(string s);

void myinit();
void mydisplay();
void display();
void idle();
//Function to print vehicles
void vehicle(Vehicle);
//Function to print road
void Roadp();
vector<float> getRGBValue(string s);


// void simulation_wrapper(int mat_len, int mat_wid, string config_file){

// }

int main(int argc, char **argv){
    srand(time(0));
    int c = stoi(argv[1]);
    string a = argv[2];
    if(c == 1){
        common(a);
    // cout <<typeid(mat_len).name()<<" "<<mat_len<<" "<<mat_len+(mat_len/10)<<" "<<typeid(mat_len+(mat_len/10)).name();

        r.Simulation(mat_len,mat_wid);
    }else{
            //opengl code
         common(a);

         glutInit(&argc, argv);

         glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
         glutInitWindowSize(mat_len*50, mat_wid*20);
         glutInitWindowPosition(0,0);
         glutCreateWindow("Traffic signal");

         /*call back functions*/
         glutDisplayFunc(mydisplay);

         myinit();
         //glutIdleFunc(idle);
         glutDisplayFunc(display);
         //atexit(onexit);
         glutMainLoop();
    }

        
return 0;

}

// void onexit(){

// }

void common(string s){

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
     r.New_initializer(mat_len,mat_wid);
     r.getAllVehSize();
     r.setAllVehSize();
}

void display(){

    while(r.Sim_fin()){
        r.LoopSimulation(mat_len,mat_wid);
        mydisplay();
    }

}

void mydisplay(){
    Roadp();

    vector<Vehicle> list = r.Get_vehicles();
    for(int i=0; i<list.size(); i++){
        if(list[i].Get_start_time()<r.time){
            cout<<list[i].GetColour();
            vehicle(list[i]);
        }
        
    }

    glFlush();
    glutSwapBuffers(); 
    }

//Function for printing Road
void Roadp(){
    glBegin(GL_QUAD_STRIP);
    //setting the dark grey colour for the road
    glColor3f(0.411, 0.411, 0.411);   
    //defigning the length and width of the road
    glVertex2i(0,0);
    glVertex2i(mat_len,0);
    glVertex2i(mat_len ,mat_wid);
    glVertex2i(0,mat_wid);

    glEnd();

}

void vehicle(Vehicle temp){


        for(int i =0 ;i<Signals.size(); i++){

        string c = Signals[i].GetColour();
        vector<float> acolour =  getRGBValue(c);
        if(r.time >= Signals[i].Get_start_time()){
            glColor3f(0,1,0);
            glBegin(GL_QUADS);

        }else{
            glColor3f(1,0,0);
            glBegin(GL_QUADS);
        }
            glVertex2i(Signals[i].Get_lenth()*50,0);
            glVertex2i(Signals[i].Get_lenth()*50+10,0);
            glVertex2i(Signals[i].Get_lenth()*50+10,mat_wid*20);
            glVertex2i(Signals[i].Get_lenth()*50,mat_wid*20);

    }

    vector<tuple<int, int> > corners = temp.getCorners();

    //glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_QUAD_STRIP);
    string c = temp.GetColour();
    vector<float> acolour =  getRGBValue(c);

    glColor3f(acolour[0], acolour[1], acolour[2]);
    glVertex2i(get<0>(corners[0]),get<1>(corners[0]));
    glVertex2i(get<0>(corners[1]),get<1>(corners[1]));
    glVertex2i(get<0>(corners[2]),get<1>(corners[2]));
    glVertex2i(get<0>(corners[3]),get<1>(corners[3]));
    
    glEnd();
}


void myinit(){


    glPointSize(1.0); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 

    glClear(GL_COLOR_BUFFER_BIT);

    // Set window size in X- and Y- direction 
    gluOrtho2D(0.0, mat_len-10, 0.0, mat_wid); 

    // Reset background color with white (since all three argument is 1.0) 
    glClearColor(0.0, 1.0, 0.0, 0.0); 
  
}


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