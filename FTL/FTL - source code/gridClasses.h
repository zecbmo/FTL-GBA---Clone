#ifndef CLASSES_H
#define CLASSES_H

#include <stdint.h>
#include <vector>


enum position {top, middle, bottom, left, right, topLeft, topRight, bottomLeft, bottomRight, farTop, farLeft, farBottom, farRight, rightLeft, topBottom, alone, empty}; 
																														//rightLeft and topBottom will be a connecting piece with walls to the left and right or top and bottom
																														
enum size {small, medium};


//This class represents a 30*20 grid in a 2d Array ... this grid in turn covers the entire screen in the GBA ... elements in this grid may have a value of either 1 or 0.. All elements set to 0 on creation
//It is used for control of cursors and drawing the ship layouts.
//for example here is a 2d vector containing the layout of a ship

//    { 0, 0, 0, 0, 0, 0, 0}, 
//    { 0, 1, 1, 1, 1, 1, 0},
//    { 0, 1, 1, 0, 0, 1, 1},
//    { 0, 1, 1, 0, 0, 1, 1},
//    { 0, 0, 1, 1, 1, 1, 1},
//    { 0, 0, 0, 0, 0, 0, 0},

//I can use a fuction within this class to paste it on to the 30*20 grid.
//Calling the drawTiles function will look through the grid and where there a 1 is in the grid, it will draw the approprate floor tile
//Using this same ship vector I can say where a cursor can and cannot move. EG... it can move between 1 values but not onto any 0 values (and then draw the cursor)

//Having the a grid set up in this manner allows me to create random ship layouts... A function creates a vector of 1's and 0's and pastes it on to the main grid.
//The creation of random layouts is similar to a dungeon map generator.
//I have 2 room sizes Small and Big and each random ship vector has 3 of each room.

//{1,1}, big room               {1,1}    small room
//{1,1}

//the rooms then connect to each other creating the vector of 1s and 0s
//Again I can from here, I paste the random Vector on to the main grid, then draw the floor tiles, then control cursors within this shipLayout


class tileMap //this will help create ship layouts. Used to control where the cursor and rooms will be.
{
	public:
			
			 
			 
			int gridLayout[20][30]; // a blank grid to paste ship layouts on
			// drawTilesBool[20][30];	//use this to say if the tile will be drawn at that position			
			int obj; //what object will be drawn
			int layer; //what layer to draw it on			
			position floorPos;
			size shipSize; // used when ranomly generating the rooms#
			std::vector< std::vector< int > > randomLayout;			 
			int smallRoomX[3];
			int smallRoomY[3];			
			int bigRoomX[3]; //six rooms max and will contain the x and y locations 
			int bigRoomY[3];			
			////////////////////////////////////
		
			int cursorPosX ; 
			int cursorPosY ;						
			int cursorObjNumber;
								
			/////////////////////////////////////////////////////////
			
			//member functions
			tileMap()
			{				
				for(int j = 0; j < 20; j++)  // set the crosshair dimensions for the grid
				{
					for(int i = 0; i < 30; i++)
					{
						floorPos = empty;
						 gridLayout[j][i] = 0;							
					}
				} 
			}
			
			void placeOnGrid(const int x, const int y, const std::vector< std::vector < int > > &whatToPlace); //&after int			
			void placeOnRandom(const int xGrid, const int yGrid, const std::vector< std::vector < int > > &whatToPlace);				
			void drawPaths(int roomSizeNum);
			void setBoolsBetweenTwoPos(int x1, int y1, int x2, int y2);			
			void randomShipSize(int chance);			
			void getRooms();
			void placeRoom(int iterations, std::vector< std::vector< int > > room, std::vector< std::vector< int > > bigRoom);			
			void placeRandomLayout(int enemyX, int enemyY);			
			void drawTiles(); //need to place the bool layout on the grid before calling: drawTiles sets the object and scales it up from 20*30 to 160*240 // this is where you were getting confused.... please dont in future
			void drawSpecificFloor(int x, int y);			
			
			////////////////////////INHERIT THIS STUFF??			
			void drawOneTile(); //specific for the cursor class
			void cursorControl(uint16_t currentKeys, uint16_t prevKeys);			
			////////////////////////////////
			void clearGrid();
};



void tileMap:: placeOnGrid(const int xGrid, const int yGrid, const std::vector< std::vector < int > > &whatToPlace) //insert the 2d vector on to the main grid
{
    for (int j = 0; j < whatToPlace.size(); j++)
    {
        for (int i = 0; i < whatToPlace[0].size(); i++)
        {
            gridLayout[yGrid + j][xGrid + i] = whatToPlace[j][i];
        }
    }
}

void tileMap:: placeOnRandom(const int xGrid, const int yGrid, const std::vector< std::vector < int > > &whatToPlace) //used to place rooms on to a grid vector ti create a random room layout
{
    for (int j = 0; j < whatToPlace.size(); j++)
    {
        for (int i = 0; i < whatToPlace[0].size(); i++)
        {
            randomLayout[yGrid + j][xGrid + i] = whatToPlace[j][i];
        }
    }
}

 void tileMap:: drawTiles() //a switch which checks the position of each tile determining it's position and what tile to draw. (allows me to draw walls)
{
	for(int j = 0; j < 20; j++)
	{
		for(int i = 0; i < 30; i++)
		{
			if(gridLayout[j][i] && gridLayout[j][i+1] && gridLayout[j][i-1] && gridLayout[j+1][i] && gridLayout[j-1][i])
			{
				floorPos = middle;  // try to represent this as an offset 0,0
			}
			if(gridLayout[j][i] && !gridLayout[j][i+1] && gridLayout[j][i-1] && gridLayout[j+1][i] && gridLayout[j-1][i])
			{
				floorPos = right; //0,1
			}
			if(gridLayout[j][i] && gridLayout[j][i+1] && !gridLayout[j][i-1] && gridLayout[j+1][i] && gridLayout[j-1][i])
			{
				floorPos = left;
			}
			if(gridLayout[j][i] && gridLayout[j][i+1] && gridLayout[j][i-1] && !gridLayout[j+1][i] && gridLayout[j-1][i])
			{
				floorPos = bottom;
			}
			if(gridLayout[j][i] && gridLayout[j][i+1] && gridLayout[j][i-1] && gridLayout[j+1][i] && !gridLayout[j-1][i])
			{
				floorPos = top;
			}
			if(gridLayout[j][i] && !gridLayout[j][i+1] && gridLayout[j][i-1] && !gridLayout[j+1][i] && gridLayout[j-1][i])
			{
				floorPos = bottomRight;
			}
			if(gridLayout[j][i] && gridLayout[j][i+1] && !gridLayout[j][i-1] && !gridLayout[j+1][i] && gridLayout[j-1][i])
			{
				floorPos = bottomLeft;
			}
			if(gridLayout[j][i] && !gridLayout[j][i+1] && gridLayout[j][i-1] && gridLayout[j+1][i] && !gridLayout[j-1][i])
			{
				floorPos = topRight;
			}
			if(gridLayout[j][i] && gridLayout[j][i+1] && !gridLayout[j][i-1] && gridLayout[j+1][i] && !gridLayout[j-1][i])
			{
				floorPos =  topLeft;
			}
			if(gridLayout[j][i] && !gridLayout[j][i+1] && !gridLayout[j][i-1] && !gridLayout[j+1][i] && !gridLayout[j-1][i])
			{
				floorPos = alone;
			}
			if(gridLayout[j][i] && !gridLayout[j][i+1] && !gridLayout[j][i-1] && gridLayout[j+1][i] && gridLayout[j-1][i])
			{
				floorPos = rightLeft;
				
			}
			if(gridLayout[j][i] && gridLayout[j][i+1] && gridLayout[j][i-1] && !gridLayout[j+1][i] && !gridLayout[j-1][i])
			{
				floorPos = topBottom;
			}
			if(gridLayout[j][i] && gridLayout[j][i+1] && !gridLayout[j][i-1] && !gridLayout[j+1][i] && !gridLayout[j-1][i])
			{
				floorPos = farLeft;
				
			}
			if(gridLayout[j][i] && !gridLayout[j][i+1] && gridLayout[j][i-1] && !gridLayout[j+1][i] && !gridLayout[j-1][i])
			{
				floorPos = farRight;
				
			}
			if(gridLayout[j][i] && !gridLayout[j][i+1] && !gridLayout[j][i-1] && gridLayout[j+1][i] && !gridLayout[j-1][i])
			{
				floorPos = farTop;
				
			}
			if(gridLayout[j][i] && !gridLayout[j][i+1] && !gridLayout[j][i-1] && !gridLayout[j+1][i] && gridLayout[j-1][i])
			{
				floorPos = farBottom;
				
			}
			if((!gridLayout[j][i] && !gridLayout[j][i+1] && !gridLayout[j][i-1] && !gridLayout[j+1][i] && !gridLayout[j-1][i]) || !gridLayout[j][i])
			{
				floorPos = empty;
				
			}			
			
			drawSpecificFloor(i,j);
					
		}
	}

} 

void tileMap:: drawSpecificFloor(int i, int j)//Should be x and y but i copied code into the switch statement without realising the SetTile function already had i and j
{
	switch(floorPos)
	{
	case top:			SetTile(30, i, j, 7); //from above.... will set the speific floor tile determined by the position and its surrounding tiles
							break;
							
	case middle: 		SetTile(30, i, j, 6);
							break;
							
	case bottom:		SetTile(30, i, j, 8);
							break;
							
	case left:			SetTile(30, i, j, 9);
							break;
							
	case right:			SetTile(30, i, j, 10);
							break;
							
	case topLeft:		SetTile(30, i, j, 11);
							break;
							
	case topRight:	SetTile(30, i, j, 12);
							break;
							
	case bottomLeft:SetTile(30, i, j, 13);
							break;
							
	case bottomRight:SetTile(30, i, j, 14);
							break;
							
	case farTop:		SetTile(30, i, j, 15);
							break;
							
	case farLeft:		SetTile(30, i, j, 22);
							break;
							
	case farBottom:	SetTile(30, i, j, 21);
							break;
							
	case farRight:	SetTile(30, i, j, 23);
							break;
							
	case rightLeft:	SetTile(30, i, j, 25);
							break;
							
	case topBottom:SetTile(30, i, j, 24);
							break;
	
	case alone:		SetTile(30, i, j, 6);
							break;
							
	case empty:		//nothing but resets the state :)
							break;
	
	
		
	}

}
 
void tileMap:: drawOneTile() //draw the cursor   //////////////CHANGE THIS NAME
{
	for(int j = 0; j < 20; j++)
	{
		for(int i = 0; i < 30; i++)
		{
		
			if(gridLayout[j][i])
			{
				SetObjectX(cursorObjNumber, cursorPosX*8); //*8 to convert the 30*20 grid to the 240*160 resoloution of the GBA screen
				SetObjectY(cursorObjNumber, cursorPosY*8); 
			}
		}
	}
}
void tileMap:: cursorControl(uint16_t currentKeys, uint16_t prevKeys) //checks the bool grid and lets me move on to tiles that have a true bool
{
	
			if (((currentKeys & KEY_RIGHT) == 0) && (prevKeys & KEY_RIGHT )!= 0)
			{
				if(gridLayout[cursorPosY][cursorPosX+1] == true)
				{
					cursorPosX++;
				}
			}
			if (((currentKeys & KEY_LEFT) == 0) && (prevKeys & KEY_LEFT )!= 0)
			{
				if(gridLayout[cursorPosY][cursorPosX-1] == true)
				{
					cursorPosX--;
				}
			}
			if (((currentKeys & KEY_UP) == 0) && (prevKeys & KEY_UP )!= 0)
			{
				if(gridLayout[cursorPosY-1][cursorPosX] == true)
				{
					cursorPosY--;
					
				}
			}
			if (((currentKeys & KEY_DOWN) == 0) && (prevKeys & KEY_DOWN )!= 0)
			{
				if(gridLayout[cursorPosY+1][cursorPosX] == true)
				{
					cursorPosY++;
					
				}
			}
		
	
}
void tileMap:: randomShipSize(int chance) //used only to get the size of the ship. 
{
	if(rand()%chance == 0)
	{
		shipSize = small;
	}
	else 
	{
		shipSize = medium;
	}
}


void tileMap:: getRooms() //builds the rooms Small and mediums
{
	 std::vector< std::vector< int > > smallRoom =
	{
		{ 1, 1} // a grid of the ship i want to place
	};
	std::vector< std::vector< int > > bigRoom =
	{
		{ 1, 1},
		{ 1, 1},
	};
	
	switch(shipSize)
	{
		case small: 		placeRoom(3, smallRoom, bigRoom); //goes through the number of iterations and places rooms on the random vector
								break;
		
		case medium: 	placeRoom(3, smallRoom, bigRoom);
								break;		
	}
	
}

void tileMap:: placeRoom(int iterations, std::vector< std::vector< int > > smallRoom, std::vector< std::vector< int > > bigRoom)
{
	bool moveNext = false; //this function looks for a valid space on the randomLayout grid and places rooms
	int randomX, randomY;
	
	
	for(int i = 0; i < iterations; i++)
	{
		while(!moveNext) //place the small room
		{
			randomX = rand()%(randomLayout[0].size()-1);
			randomY = rand()%(randomLayout.size());
			
			if(randomLayout[randomY][randomX] == 0 && randomLayout[randomY][randomX+1] ==0)
			{
				placeOnRandom(randomX, randomY, smallRoom);
				smallRoomX[i] = randomX; //20 the size of the placement value.... change this to add it somewhere else
				smallRoomY[i] = randomY;
				moveNext = true;
			}
		}
		moveNext = false;
		
	while(!moveNext)
		{
			randomX = rand()%(randomLayout[0].size()-1);
			randomY = rand()%(randomLayout.size()-1);
			
			if(randomLayout[randomY][randomX] == 0 && randomLayout[randomY][randomX+1] ==0 && randomLayout[randomY+1][randomX] ==0 && randomLayout[randomY+1][randomX+1] ==0)
			{
				placeOnRandom(randomX, randomY, bigRoom);
				bigRoomX[i] = randomX; //20 the size of the placement value.... change this to add it somewhere else
				bigRoomY[i] = randomY;
				moveNext = true;
			}
		}
		moveNext = false; 
	}
}

void tileMap:: drawPaths(int roomSizeNum)
{
	for(int i = 0; i < roomSizeNum; i++)
	{
		setBoolsBetweenTwoPos(smallRoomX[0], smallRoomY[0], smallRoomX[i], smallRoomY[i]);
		setBoolsBetweenTwoPos(smallRoomX[0], smallRoomY[0], bigRoomX[i], bigRoomY[i]);
		
	
	}

}
void tileMap:: setBoolsBetweenTwoPos(int x1, int y1, int x2, int y2)
{
	int newX;
	
	if(rand()%2 == 0) 
	{
		newX =x2;
		
	}
	else
	{
		newX = x2+1;
	}
	

	int i;
	int j;

	if(x1 <= x2 && y1 <= y2)
	{
		for(i = x1; i <= x2; i++)
		{
			randomLayout[y1][i] = 1;
		}
		for(j = y1; j <= y2; j++)
		{
			randomLayout[j][newX] = 1;
		}
	}
	else if(x1 >= x2 && y1 <= y2)
	{
		for(i = x2; i <= x1; i++)
		{
			randomLayout[y1][i] = 1;
		}
		for(j = y1; j <= y2; j++)
		{
			randomLayout[j][newX] = 1;
		}
	}
		
	else if(x1 <= x2 && y1 >= y2)
	{
		for(i = x1; i <= x2; i++)
		{
			randomLayout[y1][i] = 1;
		}
		for(j = y2; j <= y1; j++)
		{
			randomLayout[j][newX] = 1;
		}
	}
	else if(x1 >= x2 && y1 >= y2)
	{
		for(i = x2; i <= x1; i++)
		{
			randomLayout[y1][i] = 1;
		}
		for(j = y2; j <= y1; j++)
		{
			randomLayout[j][newX] = 1;
		}
	}	

	 
}

void tileMap:: placeRandomLayout(int enemyX, int enemyY) //puts everything together for random rooms
{
	 randomShipSize(2); 
	//clear the previous ship
	//8**grid....
	int x, y, roomSizeNum;
		
	for(int j = 0; j< randomLayout.size(); j++) //reset the random vector
	{
		for(int i = 0; i< randomLayout[0].size(); i++)
		{
			randomLayout[j][i] = 0;
		}
	}
	clearGrid();
	
	for (int i = 0; i < 4; i++)
	{
		smallRoomX[i] = 0;
		smallRoomY[i] = 0;
		bigRoomX[i] = 0;
		bigRoomY[i] = 0;
	}
	switch(shipSize)
	{
		
	
		case small:	randomLayout.resize(6, std::vector<int>(9)); //must be called first
							x = enemyX+6; //4 and 1 are the offset of the ship layout compared to the actual ship sprite
							y = enemyY+1;
							roomSizeNum = 3;
							break;
		
		case medium:	randomLayout.resize(6, std::vector<int>(9));
							x = enemyX+6;
							y = enemyY+1;
							roomSizeNum = 3;
							break;
		
	}


	getRooms();
	drawPaths(roomSizeNum);
	placeOnGrid(x,y, randomLayout);
	
	
	
	//Must have the cursors space filled
	//?draw 4 rooms first .... Pathfinding
	//? then connect these
	//Profit????
	


}
void tileMap:: clearGrid()
{
	for(int j = 0; j < 20; j++) // reset the grid
	{
		for(int i = 0; i < 30; i++)
		{
		
			gridLayout[j][i] = 0;
			
		}
	}

}




























#endif