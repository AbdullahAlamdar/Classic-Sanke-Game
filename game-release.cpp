//Name   :   M.Abdullah
//Roll Number : 23i-2597
// Section DS-C
//1st semester project 2023
#define TETRIS_CPP_
#include "util.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath> 
#include <string>     

using namespace std;




const int column=65;
const int rows=65;
const int cell_size=10;



 // Variable for saving the player's score
 
int score=0;  

//variables and arrays for snake

const int max_segments=5225;      // Maximum segments the snake can have
int snake_x[max_segments];       //Arrays to store x and y coordinates of each segment
int snake_y[max_segments];      //Arrays to store x and y coordinates of each segment
int num_segments=3;            // Initial number of segments
int direction=1;              // Initial direction (1: right, 2: left, 3: up, 4: down)

//variables and arrays for food

const int maximum_food=5;
int food_x[maximum_food];
int food_y[maximum_food];
time_t food_creation_time[maximum_food];
int num_of_food=0;

// arrays and variables for power food

const int max_power_food = 1; // Change the number of power food if needed
int power_food_x[max_power_food];
int power_food_y[max_power_food];
bool power_food_active[max_power_food];
time_t power_food_creation_time[max_power_food];
int num_of_power_food = 0;


//different functions for food generation

bool isfoodpositionvalid(int x, int y, int snake_x[], int snake_y[], int num_segments);
void generatefood(int snake_x[] , int snake_y[] , int num_segments);
void displayfood();
void removalofexpiredfood();
void displayPowerFood();






void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);           // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}



double startx=320,starty=400;

void Display(){

       

  
    

    glClearColor(0.0, 0.0 , 0.0, 1.0);
// 0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    
    
   

 



DrawRoundRect(0.0, 680.0, 650.0, 180.0, 0,0.3f);
DrawLine(10,10,640,10,50,colors[5]);
DrawLine(10,10,10,640,50,colors[5]);
DrawLine(10,640,640,640,50,colors[5]);
DrawLine(640,640,640,10,50,colors[5]);
DrawLine(0,0,650,0,50,colors[DARK_BLUE]);
DrawLine(0,0,0,650,50,colors[DARK_BLUE]);
DrawLine(0,650,650,650,50,colors[DARK_BLUE]);
DrawLine(650,650,650,0,50,colors[DARK_BLUE]);
DrawString(20, 830, "Score: " + to_string(score), colors[DARK_BLUE]);
for(int i=0;i<num_segments;i++)
              {
                 DrawSquare(snake_x[i],snake_y[i],10,colors[GREEN]);
              }
displayfood();
displayPowerFood();


 



          
  
     
										
																		
   
    
 
  
     
   glutSwapBuffers();   // do not modify this line..
}


void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT && direction !=1           /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
    direction=2;
											// what to do when left key is pressed...
      
      
    } else if (key == GLUT_KEY_RIGHT && direction !=2   /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
   direction=1;
		
    } else if (key == GLUT_KEY_UP && direction !=4)    /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
        direction=3;
        
    }
    else if (key == GLUT_KEY_DOWN && direction !=3)    /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
direction=4;
    
    
		
    }
    


     glutPostRedisplay();

}


void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    
    else if (int(key) == 13)
    {  
	}
    
    glutPostRedisplay();
}



void Timer(int m) {
   
       // detection logic between snake and the walls 
 if( snake_x[0]<15 || snake_x[0]>63*cell_size || snake_y[0]<15 || snake_y[0]>63*cell_size ){
string scoreStr = to_string(score);//converting intger score to string 
    
    //  command to display the message box with the score
    string command = "zenity --info --text='Snake hit the wall! Game Over. Score: " + scoreStr + "'";
    
    // Called Zenity to display the message box
    system(command.c_str());
 exit(1);
 }

if(direction==1){ // 1 for right
 for (int i = num_segments - 1; i > 0; --i) {
                snake_x[i] = snake_x[i - 1];
                snake_y[i] = snake_y[i - 1];}
                 snake_x[0] += cell_size;
                 }

if(direction==2){ // 2 for left
for (int i = num_segments - 1; i > 0; --i) {
                snake_x[i] = snake_x[i - 1];
                snake_y[i] = snake_y[i - 1];
            }
            snake_x[0] -= cell_size;
            }

if(direction==3){ // 3 for up
for (int i = num_segments - 1; i > 0; --i) {
                snake_x[i] = snake_x[i - 1];
                snake_y[i] = snake_y[i - 1];
            }
            snake_y[0] += cell_size;
            }
if(direction==4){ // 4 for down
for (int i = num_segments - 1; i > 0; --i) {
                snake_x[i] = snake_x[i - 1];
                snake_y[i] = snake_y[i - 1];
            }
            snake_y[0] -= cell_size;
            }
           

generatefood( snake_x, snake_y, num_segments);
removalofexpiredfood();

// logic to detect collision with the snakes own segments


  for(int i=1; i<=num_segments;i++)
                    {
                        if((snake_x[0]==snake_x[i]) && (snake_y[0]==snake_y[i]))
                                   {
                                      string scoreStr = to_string(score);//converting intger score to string 
    
    //  command to display the message box with the score
    string command = "zenity --info --text='Snake bit itself ! Game Over. Score: " + scoreStr + "'";
    
    // Called Zenity to display the message box
    system(command.c_str());
 exit(1);
                                    }
                    }
                    
                    


//snake eating food logic and increase in its length


for(int i=0;i<num_of_food;++i)
        {  
           

  int food_on_left = food_x[i]  - 5;  // Adjust the size of the bounding box as needed
    int food_on_right = food_x[i] + 5;
    int food_on_top = food_y[i]   + 5;
    int food_on_bottom=  food_y[i]- 5;

    if ((snake_x[0] >= food_on_left && snake_x[0] <= food_on_right && snake_y[0] >= food_on_bottom && snake_y[0] <= food_on_top)) {
        
        score+=5;
       

  

                 
                    
                    // remove the eaten food 
                    
                    for(int j=0;j<num_of_food - 1; ++j){
                                       
                    food_x[j] = food_x[j + 1];
            food_y[j] = food_y[j + 1];
            food_creation_time[j] = food_creation_time[j + 1];
        
        num_of_food--;}
       
            
                   // increasing the snake length
                    snake_x[num_segments]=snake_x[num_segments-1];
                    snake_y[num_segments]=snake_y[num_segments-1];
                    num_segments++;
                   
            
                 }
         }
         
         
          time_t currentTime = time(nullptr);
    for (int i = 0; i < num_of_power_food; i++) {
        if (power_food_active[i] && (currentTime - power_food_creation_time[i] >= 15)) {
            power_food_active[i] = false; // Deactivate expired power food
        }
    }

  // snake eating power food
    
    for (int i = 0; i < num_of_power_food; ++i) {
    if (power_food_active[i] && (snake_x[0] == power_food_x[i] && snake_y[0] == power_food_y[i])) {
        score += 20; // Increase score if snake eats power food

        // Deactivate power food after being eaten by the snake
        power_food_active[i] = false;
    }
}


         
         
 
                    




	glutPostRedisplay();

    glutTimerFunc(1000.0 / FPS, Timer, 0);
}


int main(int argc, char*argv[]) {
 


 
 //snake's initial position hard coded
snake_x[0]=rows/2;
snake_y[0]=column/2;
snake_x[1]=(rows/2)-10;
snake_y[1]=column/2;
snake_x[2]=(rows/2)-20;
snake_y[2]=column/2;
          
 
    
    
    


    int width = 650, height =850; 
    InitRandomizer(); 
    glutInit(&argc, argv); 
    
    

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowPosition(50, 50); 
    glutInitWindowSize(width, height);
    glutCreateWindow("PF's Snake Game"); 
    SetCanvasSize(width, height);
  


    glutDisplayFunc(Display); 
    glutSpecialFunc(NonPrintableKeys); 
    glutKeyboardFunc(PrintableKeys); 

    glutTimerFunc(5.0 / FPS, Timer, 0);


    glutMainLoop();
    return 1;
}
bool isfoodpositionvalid(int x, int y, int snake_x[], int snake_y[], int num_segments)
   {
        
    for(int i=0;i<num_of_food;i++)       // to check if food item is in the same column (same x-coordinate)
    
                       { 
                          if(x==food_x[i])
                          return false;
                       }
                  
    for(int i=0;i<num_of_food;i++)      // to check if the food item is in the same row( same y-coordinate)
                       {
                          if(y==food_y[i])
                          return false;
                       }
    for(int i=0;i<num_of_food;i++)
                       {
                          if(x - food_x[i] == y - food_y[i] || x - food_x[i] == food_y[i] - y)  // to check if the food is in the same diagonal
                          return false;
                       }
                       
                       for (int i = 0; i < num_segments; i++) 
                       {
        if (x == snake_x[i] && y == snake_y[i]) 
                       {
            return false; // Check if the food overlaps with the snake's segments
                       }
                       }
    for(int i=0;i<num_of_food;i++)      // to check if the food collides with lower and upper horizantal walls of the maze
                       {
                           if(((food_y[i]<=20)&&(food_x[i]<=20)) || ((food_y[i]>=630)&&(food_x[i]>=630)))
                           return false;
                       } 
 
      return true;
   }
   
   
void generatefood(int snake_x[] , int snake_y[] , int num_segments)
    {
        while(num_of_food<maximum_food)
                  {
                     int new_food_x=rand()%610+30;   // within the range of the grid
                     new_food_x = (new_food_x/10) * 10;
                     int new_food_y=rand()%610+30;
                     new_food_y = (new_food_y/10) * 10;
                     if(isfoodpositionvalid(new_food_x , new_food_y , snake_x , snake_y , num_segments))
                                     {
                                       food_x[num_of_food]=new_food_x;     // will assign new random numbers to food-x ,food-y arrays  
                                       food_y[num_of_food]=new_food_y;
                                       food_creation_time[num_of_food]=time((nullptr));  // will record the time of created food 
                                       num_of_food++;     // increment in number of foods
                                     }
                   }
                      
                      while (num_of_power_food < max_power_food) 
                      {
        int new_power_food_x = rand() % 610 + 30; // Within the range of the grid
        new_power_food_x = (new_power_food_x / 10) * 10;
        int new_power_food_y = rand() % 610 + 30;
        new_power_food_y = (new_power_food_y / 10) * 10;

        if (isfoodpositionvalid(new_power_food_x, new_power_food_y, snake_x, snake_y, num_segments)) 
         {
            power_food_x[num_of_power_food] = new_power_food_x;
            power_food_y[num_of_power_food] = new_power_food_y;
            power_food_active[num_of_power_food] = true;
            power_food_creation_time[num_of_power_food] = time(nullptr);
            num_of_power_food++;
         }
                       }
                      
     }                                 
               
void displayfood()
                   {
                      for(int i=0;i<num_of_food;i++)
                                      {
                                         DrawCircle(food_x[i] + 5 , food_y[i] + 5 , 5 , colors[MEDIUM_TURQUOISE]);
                                      }
                   }
                   
                   
void displayPowerFood() {
    for (int i = 0; i < num_of_power_food; i++) {
        if (power_food_active[i]) 
        {
            DrawCircle(power_food_x[i]+5,power_food_y[i]+5,10,colors[MEDIUM_TURQUOISE]);
        }
    }
}
                   
void removalofexpiredfood() 
{
    time_t currentTime = time(nullptr);
    for (int i = 0; i < num_of_food; ++i) {
        if (currentTime - food_creation_time[i] >= 15) {
            food_x[i] = food_x[num_of_food - 1];
            food_y[i] = food_y[num_of_food - 1];
            food_creation_time[i] = food_creation_time[num_of_food - 1];
            num_of_food--;
            i--;
        }
    }
}


              

                                                                                 
                  
          
             
//#endif /* Snake Game */

