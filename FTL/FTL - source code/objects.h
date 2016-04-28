//set up all the objects
#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>
#include <vector>
#include "playerShipData.h"


///////////////////////////////////////////////////////////////////////////////////obj number defines

#define CURSOR 0//46
#define WEP_CURSOR_1 1//47/////////////////////////////////////////////10 from hull 10 from power 41................... this will work
#define WEP_CURSOR_2 2//48

#define THE_GUY 3
#define THE_ENEMY 4
#define NAV_ROOM 5
#define WEP_ROOM 6
#define OXY_ROOM 7
#define MED_ROOM 8
#define SHE_ROOM 9
#define ENG_ROOM 10
#define ENEMY_NAV_ROOM 11
#define ENEMY_WEP_ROOM 12
#define ENEMY_OXY_ROOM 13
#define ENEMY_MED_ROOM 14
#define ENEMY_SHE_ROOM 15
#define ENEMY_ENG_ROOM 16

#define MIS_EXPL 17 //43    //add in more explosions please michael bay
#define PLAS_EXPL 18
#define ENEMY_MIS_EXPL 19 //43    //add in more explosions please michael bay
#define ENEMY_PLAS_EXPL 20

#define PLAYERSHIP 21  //due to a bug when I sandwich backgorunds between Objs the emulator does not display the BG properly
#define PLAYERSHIP2 22 //so I have the ships ordered at higher obj numbers .... to be drawn last
#define ENEMYSHIP 23
#define ENEMYSHIP2 24

#define SCRAP_BOX 25
#define SCRAP_BOX_2 26

#define MISSLE_READY 27 //due to a drawing order glitch... this obj would draw half below the SB and half above... work arround(added a white bar to the obj sprite to blend in with the SB)
#define PLASMA_READY 28

#define PLASMA_BAR 29
#define MISSLE_BAR 30
#define WEP_GREEN 31


#define MISS_MISSLE 32
#define MISS_PLASMA 33
#define MISS_SHIELD 34

//bullets
#define MISSLE 35
#define PLASMA 36
#define ENEMY_MISSLE 37
#define ENEMY_PLASMA 38

#define ENEMY_MISS_MISSLE 39
#define	ENEMY_MISS_PLASMA 40
#define ENEMY_MISS_SHIELD 41

#define HULL_BAR 42
#define ENEMY_HULL_BAR 57

#define NAV_BAR 72 //46
#define WEP_BAR 76 //50
#define OXY_BAR 82 //56
#define MED_BAR 86  //60
#define SHE_BAR  90 //64
#define ENG_BAR  98 //72

#define PLAYER_ORB 104 //78
#define ENEMY_ORB  108 //82











///////////////////////////////////////////////////////////////////////////////////////////////////screen block defines
#define HEL_BG 1
#define TAR_BG 16
#define EVD_BG 33
#define HUL_BG 227
#define HUL_2_BG 243
#define SHE_BG 151
#define SHE_2_BG 167
#define COIN_BG 144
#define COIN_2_BG 160
#define UPG_BG 176
#define UPG_2_BG 192
#define JUMP_BG 208
#define JUMP_2_BG 224



////////////////////////////////////////////////////////////////////////max room power/sheild power defines

#define MAX_HULL 15

#define MAX_NAV 4
#define MAX_WEP 6
#define MAX_OXY 4
#define MAX_MEDBAY 4
#define MAX_SHEILD 8
#define MAX_ENG 6

#define maxOrbs 4

///////////////////////////////////////////////////////////////reference to the starting index on the spirte sheet of the numbers 0-9

#define NUM_INDEX 182


/////////////////////////////////////////////////////////////////////////////////////////////////prototypes//////

void setUpObjects();
void setUI();
void setOnSB(int x, int y, int whatToPlace, int howBig);
void setWepUIonSB();
void makeObjVis(int obj);
void makeObjInvis(int obj);
void setScrapBox(int x, int y);


#define OBJ_NAME 0
#define OBJ_SHAPE 1
#define OBJ_Y 2
#define OBJ_SIZE 3
#define OBJ_X 4
#define OBJ_ID 5
#define OBJ_PRIO 6
#define OBJ_COUNT 39
int my_Object_Data[OBJ_COUNT][7] = 
{
	{PLAYERSHIP,0,0,3,0,0,3},  // name, shape, y_pos, size, x_pos, id, priority
	{PLAYERSHIP2,0,0,3,0,8,3},
	{ENEMYSHIP,0,0,3,0,128,3},
	{ENEMYSHIP2,0,0,3,0,136,3},
	{THE_GUY,0,0,0,0,256,0},
	{THE_ENEMY,0,0,0,0,272,0},
	{NAV_ROOM,1,0,0,0,265,2},
	{WEP_ROOM,1,0,0,0,281,2},
	{OXY_ROOM,0,0,1,0,288,2},
	{MED_ROOM,0,0,1,0,294,2},
	{SHE_ROOM,0,0,1,0,320,2},
	{ENG_ROOM,1,0,0,0,326,2},
	{MIS_EXPL,0,0,0,0,342,2},
	{CURSOR,0,0,0,0,380,0},
	{WEP_CURSOR_1,0,0,0,0,381,0},
	{WEP_CURSOR_2,0,0,0,0,382,0},
	{ENEMY_NAV_ROOM,1,0,0,0,265,2},
	{ENEMY_WEP_ROOM,1,0,0,0,281,2},
	{ENEMY_OXY_ROOM,0,0,1,0,288,2},
	{ENEMY_MED_ROOM,0,0,1,0,294,2},
	{ENEMY_SHE_ROOM,0,0,1,0,320,2},
	{ENEMY_ENG_ROOM,1,0,0,0,326,2},
	{MISSLE_READY,1,128,0,64,352,3},
	{PLASMA_READY,1,128,0,80,354,3},
	{MISSLE_BAR,0,128,0,64,373,3},
	{PLASMA_BAR,0,128,0,88,374,3},
	{WEP_GREEN,1,128,1,64,368,3},
	{MISS_MISSLE,1,50,0,120,394,3},
	{MISS_PLASMA,1,100,0,120,394,3},
	{MISS_SHIELD,1,100,1,120,356,3},
	{MISSLE,1,55,0,0,391,3},
	{PLASMA,0,95,0,0,393,3},
	{ENEMY_MISSLE,1,65,0,0,391,3},
	{ENEMY_PLASMA,0,85,0,0,393,3},
	{SCRAP_BOX,1,0,2,0,432,2},
	{SCRAP_BOX_2,1,0,2,32,436,2},
	{ENEMY_MISS_MISSLE,1,50,0,95,394,3},
	{ENEMY_MISS_PLASMA,1,100,0,95,394,3},
	{ENEMY_MISS_SHIELD,1,100,1,95,356,3}
	
};

									  
										  
/////////////////////////////////////////////////////////////////////////////////////////////////functions

void setUpObjects() //I have mapped every object and set them to hide. This will allow easy access to each object when it is needed(making them either visible or invisible)
{

	for (int i=0;i<OBJ_COUNT;i++)
	{
		SetObject(my_Object_Data[i][OBJ_NAME],
			  ATTR0_SHAPE(my_Object_Data[i][OBJ_SHAPE]) | ATTR0_8BPP |
			  ATTR0_HIDE | ATTR0_Y(my_Object_Data[i][OBJ_Y]), 
			  ATTR1_SIZE(my_Object_Data[i][OBJ_SIZE]) | ATTR1_X(my_Object_Data[i][OBJ_X]),
			  ATTR2_ID8(my_Object_Data[i][OBJ_ID])  | ATTR2_PRIO(my_Object_Data[i][OBJ_PRIO])); 
	}


		for(int i = 0; i < MAX_HULL; i++) //sets all hull health bars at once
		{
			SetObject(HULL_BAR+i,
			  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(0), 
			  ATTR1_SIZE(0) | ATTR1_X(0),
			  ATTR2_ID8(363)  | ATTR2_PRIO(2));

			SetObject(ENEMY_HULL_BAR+i,
			  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(0), 
			  ATTR1_SIZE(0) | ATTR1_X(0),
			  ATTR2_ID8(363)  | ATTR2_PRIO(2));
		
		}

		for(int i = 0; i < 34; i++) //I need to set an hull power bar obj for each rooms power level. Each room has a max value of power they can have
		{									//i have defined all the "names" of each power to corisponding rooms
			SetObject(NAV_BAR+i,							//this for loop adds all the max values (34) and sets all the objs at once
			  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(0), //I start the intial obj at The NAV_BAR define because it is the lowest and passes through all the other defines
			  ATTR1_SIZE(0) | ATTR1_X(0),
			  ATTR2_ID8(386)  | ATTR2_PRIO(0));			
		}


		for(int i = 0; i < 8; i++) // 8 number of player shiled orbs + enemy shield orbs
		{									
			SetObject(PLAYER_ORB+i,							
			  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(0),
			  ATTR1_SIZE(0) | ATTR1_X(0),
			  ATTR2_ID8(361)  | ATTR2_PRIO(0));			
		}
		
		ObjBuffer[ENEMY_MISSLE].attr1 |= ATTR1_HFLIP; //flips the Enemies missle after being created in the array so it faces the right way
		
}


void setUI()
{
	setOnSB(1,1,HUL_BG, 3);
	setOnSB(1,2,HUL_2_BG,3);
	setOnSB(1,3,SHE_BG,8);
	setOnSB(1,4,SHE_2_BG,8);
	setOnSB(1,5,HEL_BG, 4);
	setOnSB(8,5,EVD_BG, 4);
	//setOnSB(12,1,COIN_BG, 6);
	//setOnSB(12,2,COIN_2_BG,6);
	setOnSB(24,1,UPG_BG, 5); //upgrade box and jump, these no longer needed as i will not be implementing them but they make the screen look symetrical 
	setOnSB(24,2,UPG_2_BG,5);
	setOnSB(26,3,JUMP_BG,3);
	setOnSB(26,4,JUMP_2_BG,3);
	setOnSB(21,18,SHE_BG,8);
	setOnSB(21,19,SHE_2_BG,8);
	setOnSB(21,16,HUL_BG+3,4);
	setOnSB(21,17,HUL_2_BG,3);
	setOnSB(21, 15, TAR_BG,4);
	setWepUIonSB();
	setScrapBox(92,4);
	makeObjVis(PLASMA_BAR);
	makeObjVis(MISSLE_BAR);
	makeObjVis(WEP_GREEN);
	
}
void setOnSB(int x, int y, int whatToPlace, int howBig) //Set a tile from the BG spritesheet. Int what to places refers to the starting point of the BG object
{
	for(int i = 0; i < howBig; i++)
	{
		SetTile(30, x+i, y, whatToPlace+i);
	}
}
void setWepUIonSB() //This Code is unfortuantly untidy but very specific for drawing the weaponUI 
{
	SetTile(30, 1, 17, 128);
	for(int i = 0; i < 6; i++)
	{
		SetTile(30, 2+i, 17, 129);
	}
	for(int i = 0; i <2;i++)
	{
		SetTile(30,1,16+i,112);
	}
	SetTile(30,1,15,113);
	setOnSB(8,16, 115,4);
	setOnSB(8,17,131,5);
	setOnSB(2,18,JUMP_BG+3,6);
}
void makeObjVis(int obj)
{
		ObjBuffer[obj].attr0 &= ~ATTR0_HIDE;
		ObjBuffer[obj].attr0 |= ATTR0_REG;
			
}
void makeObjInvis(int obj)
{
		ObjBuffer[obj].attr0 &= ~ATTR0_REG;
		ObjBuffer[obj].attr0 |= ATTR0_HIDE;
			
}
void setScrapBox(int x, int y)
{
	makeObjVis(SCRAP_BOX);
	makeObjVis(SCRAP_BOX_2);
	
	SetObjectX(SCRAP_BOX, x);
	SetObjectY(SCRAP_BOX, y);
	
	SetObjectX(SCRAP_BOX_2, x+32);
	SetObjectY(SCRAP_BOX_2, y);

}



#endif