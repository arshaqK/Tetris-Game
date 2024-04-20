/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */
 
 // Syed Arshaq Hussain Kirmani		22i-0834 	Final Project

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colorNum){
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        if (!anamoly()){
	       	for (int i=0;i<4;i++)
           		gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
           		colorNum = 1 + rand()%7;
           		
           	int n=rand()%7;
           	
                for (int i=0;i<4;i++){
            		point_1[i][0] = BLOCKS[n][i] % 2;  	//x-axis
                	point_1[i][1] = BLOCKS[n][i] / 2;  	//y-axis
               }
     		
        }
        timer=0;
    }
}


/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

void movingPiece(int& delta_x){
	for (int i=0;i<4;i++){
		point_1[i][0] += delta_x;			//Increments one on x-axis in every iteration, takes delta_x value by reference
	}
	
}

void lineCompleted(){
	int x = M-1;	
	int lineCount=0, score=0;					
	for(int p=M-1; p>0; p--){
		int counter=0;
		for(int q=0;q<N;q++){
			if (gameGrid[p][q])
				counter++;
			
			gameGrid[x][q] = gameGrid[p][q];
		}
		if(counter<N)
			x--;
			
		lineCount++;				//counts the number of lines that are filled completely
		switch(lineCount){			//calculates the scores according to the number of lines criteria
			case '1':
				score += 10;
			case '2': 
				score += 30;
			case '3': 
				score += 60;
		}
		
		if(lineCount>=4)
			score += 100;
	}
}  









///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
