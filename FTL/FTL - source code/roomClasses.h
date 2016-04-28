#ifndef ROOM_CLASSES_H
#define ROOM_CLASSES_H



#include <stdint.h>

enum roomState{dead, broke, fixed};
enum target {navRoom, engRoom, wepRoom, oxyRoom, medRoom, sheRoom, noRoom};

class room
{
	public: /// make these private
		int health;
		int maxHealth;
		//int level;
		int x; //*8 to set the obj sprite position 
		int y; //will work on the 30* 20 grid so Y's maxium is 19		
		//for drawing the room i need to match the class's ID
		//with the OBJS ID... these need to be set before drawing
		int obj;
		int objIndex;		
		int coordX[4];
		int coordY[4];		
		bool exists;		
		target roomName;				
		roomState state;
		
		room()
		{
			exists = true;
		}
		
		void initalize(int x, int y, int obj, int objIndex, target roomName);
		
		void getState();
		void drawState();
		void setTargetCoords(); //will set x and y points to match with cursors for targeting
		void setRandomHealth(int low, int high, int max);
		void fixHealth();
		void repairAndCheck();
		bool doesRoomExist(bool doesIt);
		int getX();
		int getY();
		bool getExistance();
};
void room::initalize(int x1, int y1, int obj1, int objIndex1, target roomName1)
{
	x = x1;
	y = y1;
	obj = obj1;
    objIndex = objIndex1;
	roomName = roomName1;
	
	makeObjVis(obj);
	SetObjectX(obj, x*8);
	SetObjectY(obj, y*8);
	

	
	
}
void room:: getState()
{
	if(health == maxHealth)
	{
		state = fixed;	
	}
	if(health < maxHealth && health > 0)
	{
		state = broke;
	}
	if(health <= 0)
	{
		state = dead;
	}
	
}
void room:: drawState()
{
	switch(state)
	{
		case fixed: 	SetObjectID(obj, objIndex);
							break;
		case broke:	SetObjectID(obj, objIndex+2);
							break;
		case dead:		SetObjectID(obj, objIndex+4);
							break;
		
	
	}
}

void room:: setTargetCoords()
{
	for(int i = 0; i < 2; i ++)
	{
		coordX[i] =x+i;
		coordY[i] =y;
		
		coordX[i+2] =x+i;
		coordY[i+2] =y+1;
	}


}
void room:: setRandomHealth(int low, int high, int max) // called depending on difficulty
{
	
/* 	do  //will set a random enemy health level
	{
	
		maxHealth = rand()%high;
		
		
	}while (maxHealth < low || maxHealth > high); */
	
	maxHealth = rand()%(high-low)+low;
	
	if(maxHealth >= max) //if the random health level is greater than the rooms max then 
	{								//set if to the max health available
		maxHealth = max; 
	}
		
	health = maxHealth;
	
	//std: min and max
	
	///random between rand()(high - low )+low
}
void room::fixHealth()
{
	if (health < 0)
	{
		health = 0;
	}
	
}
int room::getX()
{
	return x;
}
int room::getY()
{
	return y;
}
void room::repairAndCheck()
{
	if(health < maxHealth)
	{
		health++;
	}
	
}
bool room::doesRoomExist(bool doesIt)
{
	exists = doesIt;
	return exists;
}
bool room::getExistance()
{
	return exists;

}
#endif