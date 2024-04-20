/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
 
// Syed Arshaq Hussain Kirmani		22i-0834 	Final Project

 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"


using namespace sf;



int main(){
    srand(time(0));
    RenderWindow window(VideoMode(480, 480), title);
    Texture obj1, obj2, obj3, obj4, obj5;
     
    
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/gameOver");				//Adding a new image "GAME OVER"
    obj5.loadFromFile("img/blackBG.jpg");			//Adding black background image for game over screen
    
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    Sprite sprite(obj1), background(obj2), frame(obj3), nextSprite(obj1), gameover(obj4), blackBG(obj5); 	//Three additional sprites created (Score, Game Over & Next block)
    
    Font scoreFont;	 
    scoreFont.loadFromFile("fonts/game_over.ttf"); 		//Loading new font for Score sprite			
      
    
  
    int delta_x=0, colorNum=3;
    float timer=0, delay=0.6;
    bool rotate=0;
    
    Clock clock;
    
    while (window.isOpen()){
 	delay = 0.6, delta_x=0;
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    	//Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                	//If cross/close is clicked/pressed
                window.close();                         	//Opened window disposes
            if (e.type == Event::KeyPressed) {          	//If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up){        	//Check if the other key pressed is UP key
                    rotate = true;   				//Rotation gets on
                    int rPoint[7][4];				//2D Array to store point of rotation co-ordinates for each shape
                    int n=4;
                    
                    rPoint[n][0] = point_1[1][0];		//x co-ordinate of point of rotation 
                    rPoint[n][1] = point_1[1][1];		//y co-ordinate of point of rotation
                    
                    for(int i=0; i<4; i++){
                    
                   	int a;
                   	int b;
                    
                    	a = point_1[i][1] - rPoint[n][1];	
                    	b = point_1[i][0] - rPoint[n][0]; 
               
                    	point_1[i][0] = rPoint[n][0] - a;	//New x-coordinate after rotation
                    	point_1[i][1] = rPoint[n][1] + b;	//New y-coordinate after rotation
                                 
                    }       
                }
                                           			
                else if (e.key.code == Keyboard::Left)   	//Check if the other key pressed is LEFT key
                    delta_x = -1;                        	//Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)  	//Check if the other key pressed is RIGHT key
                    delta_x = 1; 
                else if	(e.key.code == Keyboard::Space){         //Change in X-Axis - Positive
            		
            	}
            }
        
        
        if (Keyboard::isKeyPressed(Keyboard::Down))   		//Just another way to detect key presses without event listener
            delay=0.05;                                    	//If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
	                          
        }  

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
     
       	
        fallingPiece(timer, delay, colorNum);               	//Example: fallingPiece() function is called here
        
        if (e.key.code == Keyboard::Right)			//If right key is pressed, movingPiece function increments 1 in the x-coordinate
		movingPiece(delta_x);        			
              	
      	if (e.key.code == Keyboard::Left)			//If left key is pressed, movingPiece function decrements 1 in the x-coordinate
		movingPiece(delta_x);        			
       
	lineCompleted(); 
        	
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////


        window.clear(Color::Black);
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));	
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
                
            }
        }
        
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
              
        				
	for (int i=0; i<4; i++){						//Displays the next block on right side of the screen
            nextSprite.setTextureRect(IntRect(colorNum*18,0,18,18));	
            nextSprite.setPosition(20*18,3*18);
            nextSprite.move(28,31);
            window.draw(nextSprite);
        }
        
        Text score;								//Displays score on right side of the screen
        score.setFont(scoreFont);
        score.setCharacterSize(45);
        score.setString("SCORE:");
        score.setPosition(370,150);
      	window.draw(score);
          
          
        Text Level;								//Displays level on right side of the screen
        score.setFont(scoreFont);
        score.setCharacterSize(45);
        score.setString("LEVEL:");
        score.setPosition(370,220);
      	window.draw(score);
      	
      	Text Lines;								//Displays lines on right side of the screen
        score.setFont(scoreFont);
        score.setCharacterSize(45);
        score.setString("LINES:");
        score.setPosition(370,290);
      	window.draw(score);
          
       
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        
        if (gameGrid[0][20]){							//if blocks exceeds 20(vertical size of game area), game stops
            window.draw(blackBG);
            gameover.setPosition(110,165);
            //gameover.move(150,150);
            window.draw(gameover);    
      	}  
  
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
        
      
      
    }
  
    return 0;
}


