#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include "gba.h"
#include "font.h"
#include "sprites.h"
#include "gridClasses.h"
#include "playerShipData.h"
#include "objects.h"
#include "spritesheetBG.h"
#include "functions.h"
#include "roomClasses.h"
#include "weaponClasses.h"
#include "shipClasses.h"

#define STAR_TILES_LENGHT 16

enum currentDifficulty {veryEasy, easy, average, hard, veryHard};


////////////////////////////////////////////////prototypes /////////////////////////////////////////////////////////////


//setup
void setBG();
void setPalette();	
void clearScreenBlock30();	
void drawStarsHor(int screenBlock, int xOffset, int yValue);
void drawStarBlock(int yValue, int size, int screenBlock);
void drawStarField();

/////////////

void moveStars(float velocity);
void drawHullHealth(int x, int y , int obj, int hullHealth);
void drawPowerBars(int x, int y, int obj, int currentMaxPower, int powerLevel);
void loadFont();
void drawText(int x, int y, const char string[]);
void setUpCrosshairs(int shipX, int shipY, int enemyShipX, int enemyShipY);
void drawShip(int obj, int x, int y);
void initialSetUp();
void showIntro();
void setUpEnemyRooms(int enemyShipX, int enemyShipY);
void drawEnemyRoomHealth();
void getTarget(tileMap &cursor, player &whichPlayer, target &whatIsAiming);
void damageThisRoom(weapon &gun, player &whichPlayer);

void doesWeaponHit(weapon &gun, player &whichPlayer, room &shieldRoom);
void setUpPlayerRooms(int shipX, int shipY);
void drawPlayerRoomHealth();
void setAllRoomCoords();
void playerStartingStats();
void setEnemyStats(currentDifficulty difficulty);
void setEnemyRoomHealth(int low, int high);
void drawSheildOrbs(int x, int y, int obj, int currentMaxSheild, int sheildLevel);

void setWepStats(player &whichPlayer, int powerLevel);

void setEvadeChance(player &whichPlayer, int navLevel, int engineLevel);
void bulletFired(bullet &Bullet, weapon &gun, int obj);
void enemyBulletFired( bullet &Bullet, weapon &gun, int obj);

void movementControls(uint16_t currentKeys, uint16_t prevKeys);
void shootingControls(uint16_t currentKeys, int &plasmaBarY, int &missleBarY);

void updateWeapons(int &missleBarY, int &plasmaBarY);

void drawObjs();
void updateCounters();

void getEnemyTarget();

void roomHealthSafetyCheck();

void repairRoom(character  &whichChar, player &whichPlayer);
void healThisRoom(character  &whichChar, player &whichPlayer);

void levelStatusCheck(bool &enemyDead, int x, int y, int &shipsDestroyed, currentDifficulty dif);
void gameOver();
void nextLevel(int x, int y, int &shipsDestroyed, currentDifficulty dif);
void drawNumber(int x, int y, int number);
void resetEncounter();
void getDifficulty(int shipsDestroyed, currentDifficulty &dif);
void getEnemyCaptainTarget();
void basicEnemyRepairCheck(character &whichChar, room &whichRoom);
void furtherEnemyRepairCheck(character &whichChar, room &whichRoom);
void checkForEnemyMovement(character &whichChar);
void oxygenCheck(player &whichPlayer);
void healingRoom(character &whichChar, player &whichPlayer);
void upgrades();
void highlightRoom(room &whichRoom, int cost, uint16_t &currentKeys, uint16_t &prevKeys, int MAX);
int getRandomScrap(int low, int high);
int getWinningScrap(currentDifficulty dif);
void showYouWin();
/////////////////////////////////////////globals/////////////////////////////////////////////////////////////////
tileMap playerShip;
tileMap enemyShip; 
tileMap crosshair;
tileMap missleCrosshair;
tileMap plasmaCrosshair;


player guy;
player enemy;



float speedS, speedM, speedF; //speed of the paralax stars .//REmOvE THIS

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setBG()
{
	REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ  |  DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3;
	REG_BG3CNT = BG_CBB(0) | BG_SBB(27) | BG_8BPP | BG_REG_32x32  | BG_PRIO(3) ;
	REG_BG2CNT = BG_CBB(0) | BG_SBB(28) | BG_8BPP | BG_REG_32x32 | BG_PRIO(3) ;
	REG_BG1CNT = BG_CBB(0) | BG_SBB(29) | BG_8BPP | BG_REG_32x32 | BG_PRIO(3) ;
	REG_BG0CNT = BG_CBB(1) | BG_SBB(30) | BG_8BPP | BG_REG_32x32 | BG_PRIO(2) ;
	
	
	LoadPaletteBGData(0, spritesheetBGPal, sizeof spritesheetBGPal);
	LoadTileData(1, 0, spritesheetBGTiles, sizeof spritesheetBGTiles);
	
	LoadPaletteObjData(0, playerShipDataPal, sizeof playerShipDataPal);	//take this out and put it before the enemy encounter .... hopefully to add more ships
	LoadTileData(4, 0, playerShipDataTiles, sizeof playerShipDataTiles);
	
	LoadTile8(1, 6, floorTileMiddle); //these tilles where made before the spritesheetBG so I have slotted
	LoadTile8(1, 7, floorTileTop);      //them in to the blank spaces
	LoadTile8(1, 8, floorTileBottom);
	LoadTile8(1, 9, floorTileLeft);
	LoadTile8(1, 10, floorTileRight);
	LoadTile8(1, 11, floorTileTopLeft);
	LoadTile8(1, 12, floorTileTopRight);
	LoadTile8(1, 13, floorTileBottomLeft);
	LoadTile8(1, 14, floorTileBottomRight);
	LoadTile8(1, 15, floorTileFarTop);
	LoadTile8(1, 21, floorTileFarBottom);
	LoadTile8(1, 22, floorTileFarLeft);
	LoadTile8(1, 23, floorTileFarRight);
	LoadTile8(1, 24, floorTileTopBottom);
	LoadTile8(1, 25, floorTileRightLeft);
	
	
}
void setPalette() //call after loading the spritesheet
{
// Set up the palette.
	SetPaletteBG(0, RGB(0, 0, 0)); // black                  toncs sprite thing may overwrite this
	SetPaletteBG(1, RGB(31, 31, 31)); // white 	
	SetPaletteBG(2, RGB(15, 15, 15)); // white
	SetPaletteBG(3, RGB(25, 25, 25)); // grey (cloud)
	SetPaletteBG(4, RGB(20, 10, 0)); // brown (brick)
	SetPaletteBG(5, RGB(25, 25, 25));
	SetPaletteBG(12, RGB(31, 31, 31));
}

void clearScreenBlock30()
{
	for (int y = 0; y < 32; ++y)
		{
			for (int x = 0; x < 32; ++x)
			{
				SetTile(30, x, y, 0);
			}
		}
}

void drawStarsHor(int screenBlock, int xOffset, int yValue) 
{
	int starTileNo = 0;
	int p = 0; //p works technically as the star tile position.... if p = 0 it will the tile will be blank .... if not it will be a random star tile
	int finalOffset; //offsets the drawing position of the tiles so they are stagered, not in a column
	
	for(int i = 0; i < 32-xOffset; i++) // I -the offset as not to go over 32 and outside the screenblock boundaries
	{
		
		if(i%3 == 0)
		{
			p = starTileNo;
	
		}
		else
		{
			p = 0;
		}
		
		if(i <1) //this draws a random star at the first position (too many blank tiles because of the offset)
		{
			finalOffset = i;
			p = (yValue%STAR_TILES_LENGHT)+1; //using the yValue to seed a random tile
		}
		else
		{
			finalOffset = i + xOffset;
		}
						
		SetTile(screenBlock,finalOffset,yValue,p); 
		
		
		starTileNo++;
		if(starTileNo == STAR_TILES_LENGHT) //keeps k within the star tiles range
		{
			starTileNo=0;
		}
		
	}
}
void drawStarBlock(int yValue, int size, int screenBlock) //insert the Y value of where to start and how big vertically it should be
{
		
		int xOffset = 0;
		for (int i = yValue; i < (yValue+size); i++)
		{
			drawStarsHor(screenBlock,xOffset*xOffset,i);
			if(xOffset>3)
			{
				xOffset = 0;
			}
			xOffset++;
		}
}
void drawStarField() 
{		
		drawStarBlock(0,4,28); //these values make up the entire screen worth of stars.... spreading them out evenly
		drawStarBlock(4,3,29);
		drawStarBlock(7,6,27);
		drawStarBlock(13,3,29);
		drawStarBlock(16,4,28);
		
	
}
void moveStars(float velocity)
{
	REG_BG3HOFS = speedS; 
	REG_BG1HOFS = speedM;
	REG_BG2HOFS = speedF;
	
	speedS += velocity*0.3;  //Allows me to insert a velocity for the fastest background and the others will match it
	speedM += velocity*0.5;
	speedF += velocity;
}
void drawHullHealth(int x, int y , int obj, int hullHealth)
{
	

	for(int i = 0; i < MAX_HULL; i++) //clears everything up to the full health
	{
		makeObjInvis(obj+i);
	
	}
	
	for(int i = 0; i < hullHealth; i++) //draws only the health you have
	{
		makeObjVis(obj+i);
		SetObjectX(obj+i, (i*3)+x);
		SetObjectY(obj+i, y);
	
	}

}
void drawPowerBars(int x, int y, int obj, int currentMaxPower, int powerLevel)
{
	
	



	for(int i = 0; i < currentMaxPower; i++) 
	{
		makeObjVis(obj+i); //no need to hide the OBJ here as the current max power will not be able to decrease
		
		if( i >= powerLevel)
		{
			SetObjectID(obj+i, 386);
		}
		else 
		{
			SetObjectID(obj+i, 385);
		}
		
		SetObjectX(obj+i, x);
		SetObjectY(obj+i, y-(i*3));
	}


}
void loadFont()
{
	for (int i = 0; i < 26; i++)
		{
				LoadTile8(1, i+65, font_medium[i+65]); //loads it into the blank space of my sprite sheet
				
		}
	
}
void drawText(int x, int y, const char string[])
{
	int lenght = strlen(string);
	for(int i = 0; i < lenght; i++)
	{
		SetTile(30,x+i,y, string[i]);
	}
}
void setUpCrosshairs(int shipX, int shipY, int enemyShipX, int enemyShipY)
{
	int xOffset = 6;
	int yOffset = 1;

	for(int i = 0; i < 3; i++)
	{
		makeObjVis(CURSOR+i);
	}


	crosshair.cursorObjNumber = CURSOR; //must be callsed before drawing the crosshair //values need to be the same as when placing the player ship on the grid
	missleCrosshair.cursorObjNumber = WEP_CURSOR_1;
	plasmaCrosshair.cursorObjNumber = WEP_CURSOR_2;
	
	crosshair.clearGrid();
	crosshair.cursorPosX = 7; //CHANGE THIS
	crosshair.cursorPosY = 7;
	crosshair.placeOnGrid(shipX,shipY,shipLayout);

	missleCrosshair.clearGrid();
	missleCrosshair.placeOnGrid(enemyShipX+xOffset,enemyShipY+yOffset ,enemyShip.randomLayout);	
	missleCrosshair.cursorPosX = enemyShip.smallRoomX[0]+enemyShipX+xOffset;
	missleCrosshair.cursorPosY = enemyShip.smallRoomY[0]+enemyShipY+yOffset;
		
	plasmaCrosshair.clearGrid();
	plasmaCrosshair.placeOnGrid(enemyShipX+xOffset,enemyShipY+yOffset ,enemyShip.randomLayout);	
	plasmaCrosshair.cursorPosX = enemyShip.smallRoomX[1]+enemyShipX+xOffset;
	plasmaCrosshair.cursorPosY = enemyShip.smallRoomY[1]+enemyShipY+yOffset ;
	
}
void drawShip(int obj, int x, int y)
{
	makeObjVis(obj);
	makeObjVis(obj+1);
	
	SetObjectX(obj, x*8);
	SetObjectY(obj, y*8);
	
	SetObjectX(obj+1, (x*8)+64);
	SetObjectY(obj+1, y*8);

}
void initialSetUp()
{
	setBG();
	setPalette();
	makeSomeStarTiles();
	drawStarField();
	loadFont();
	setUpObjects();



}
void showIntro()
{
	int seed = 0;
	int blinker =0;
	uint16_t prevKeys = 0;
	while(true)
	{
		uint16_t currentKeys = REG_KEYINPUT;
	
		 clearScreenBlock30();
		
		moveStars(1);
		drawText(1, 3, "FTL....");
		drawText(6, 5, "FASTER THAN LIGHT");
		drawShip(PLAYERSHIP, 7,8);
		
		if(blinker > 40)
		{
			drawText(6, 18, "...PRESS START...");
			
			if(blinker > 80)
			{
				blinker = 0;
			}
		}
		
		if (((currentKeys & KEY_START) == 0))
		{
				srand(seed);
				break;
		}
		
		WaitVSync();
		UpdateObjects();
		seed++;
		blinker++;
		
	}
	setUpObjects(); //HIDES ALL OF THE OBJECTS
	
	while(true)
	{
		clearScreenBlock30();
		uint16_t currentKeys = REG_KEYINPUT;
		
		moveStars(1);
		drawText(1, 1, "COMMANDER....");
		drawText(1, 4, "WE RECIEVED AN URGENT ");
		drawText(1, 5, "TRANSMISSION FROM FARPOINT");
		drawText(1, 6, "ALPHA NINE. THE DAWN OF");
		drawText(1, 7, "RIECHTFALL HAS ARRIVED.");
		drawText(1, 8, "PREPARE FOR WAR.");
		drawText(1, 9, "OUR FLEET IS ENGAGED AT");
		drawText(1, 10, "FARPOINT. COMMANDER. YOU");
		drawText(1, 11, "ARE THE LAST SHIP BETWEEN");
		drawText(1, 12, "HERE AND EARTH...");
		
		drawText(1, 13, "SENSORS SHOW TWENTY ENEMY ");
		drawText(1, 14, "WARSHIPS ON A DIRECT COURSE.");
		
		drawText(1, 15, "DEFEND OUR EARTH COMMANDER.");
		drawText(1, 16, "DEFEAT THEM AT ALL COSTS...");
		drawText(15, 18, "...PRESS START");
		WaitVSync();
		UpdateObjects();
		if (((currentKeys & KEY_START) == 0)&& (prevKeys & KEY_START )!= 0)
		{
			break;
		}
		prevKeys = currentKeys;
		
	}
	prevKeys = 0;
	while(true)
	{
		clearScreenBlock30();
		uint16_t currentKeys = REG_KEYINPUT;
		
		moveStars(1);
		drawText(1, 1, "...CONTROLS...");
		drawText(1, 3, "D.PAD TO MOVE CURSOR.");
		drawText(1, 4, "A TO MOVE PLAYER.");
		drawText(1, 6, "HOLD L TO CONTROL MISSLE.");
		drawText(1, 7, "HOLD R TO CONTROL PLASMA.");
		
		drawText(1, 9, "WITH L OR R HELD:");
		drawText(4, 10, "D.PAD MOVES");
		drawText(4, 11, "WEAPON CURSOR.");
		drawText(4, 12, "A FIRES WEPON.");
		
		drawText(1,14, "WHEN UPGRADING");
		drawText(4,15, "A TO SELECT UPGRADE");
		drawText(4,16, "START TO CONTINUE");
	
		
		
		drawText(15, 18, "...PRESS START");
		WaitVSync();
		UpdateObjects();
		if (((currentKeys & KEY_START) == 0)&& (prevKeys & KEY_START )!= 0)
		{
			break;
		}
		prevKeys = currentKeys;
		
	}

}
void setUpEnemyRooms(int enemyShipX, int enemyShipY)
{
	int xOffset = 6;
	int yOffset = 1;
	
	
	enemy.NavRoom.initalize(
		enemyShip.smallRoomX[0]+enemyShipX+xOffset,
		enemyShip.smallRoomY[0]+enemyShipY+yOffset,
		ENEMY_NAV_ROOM, 265, navRoom);
	
	enemy.EngRoom.initalize(
		enemyShip.smallRoomX[1]+enemyShipX+xOffset,
		enemyShip.smallRoomY[1]+enemyShipY+yOffset,
		ENEMY_ENG_ROOM, 326, engRoom);

	enemy.WepRoom.initalize(
		enemyShip.smallRoomX[2]+enemyShipX+xOffset,
		enemyShip.smallRoomY[2]+enemyShipY+yOffset,
		ENEMY_WEP_ROOM, 281, wepRoom);
	
	enemy.OxyRoom.initalize(
		enemyShip.bigRoomX[0]+enemyShipX+xOffset,
		enemyShip.bigRoomY[0]+enemyShipY+yOffset,
		ENEMY_OXY_ROOM, 288, oxyRoom);
	
	enemy.MedRoom.initalize(
		enemyShip.bigRoomX[1]+enemyShipX+xOffset,
		enemyShip.bigRoomY[1]+enemyShipY+yOffset,
		ENEMY_MED_ROOM, 294, medRoom);
	
	enemy.SheRoom.initalize(
		enemyShip.bigRoomX[2]+enemyShipX+xOffset,
		enemyShip.bigRoomY[2]+enemyShipY+yOffset,
		ENEMY_SHE_ROOM,  320, sheRoom);
		
	enemy.captain.setPlayerPos(enemy.WepRoom.getX(), enemy.WepRoom.getY());
	enemy.captain.setObj(THE_ENEMY);
		
}

void drawEnemyRoomHealth()
{
	enemy.NavRoom.getState();
	enemy.NavRoom.drawState();
	
	enemy.EngRoom.getState();
	enemy.EngRoom.drawState();
	
	enemy.WepRoom.getState();
	enemy.WepRoom.drawState();
	
	enemy.OxyRoom.getState();
	enemy.OxyRoom.drawState();
	
	enemy.MedRoom.getState();
	enemy.MedRoom.drawState();
	
	enemy.SheRoom.getState();
	enemy.SheRoom.drawState();

}

void getTarget(tileMap &cursor, player &whichPlayer,target &whatIsAiming)
{

	if(((cursor.cursorPosX == whichPlayer.OxyRoom.coordX[0]) && (cursor.cursorPosY == whichPlayer.OxyRoom.coordY[0])) || ((cursor.cursorPosX == whichPlayer.OxyRoom.coordX[1]) && (cursor.cursorPosY == whichPlayer.OxyRoom.coordY[1]))  ||  ((cursor.cursorPosX == whichPlayer.OxyRoom.coordX[2]) && (cursor.cursorPosY == whichPlayer.OxyRoom.coordY[2])) ||  ((cursor.cursorPosX == whichPlayer.OxyRoom.coordX[3]) && (cursor.cursorPosY == whichPlayer.OxyRoom.coordY[3])) )
	{
		whatIsAiming = whichPlayer.OxyRoom.roomName;
		//makeObjVis(THE_GUY);	//used for testing... guy object showed when over a room
	}
	else if(((cursor.cursorPosX == whichPlayer.MedRoom.coordX[0]) && (cursor.cursorPosY == whichPlayer.MedRoom.coordY[0])) || ((cursor.cursorPosX == whichPlayer.MedRoom.coordX[1]) && (cursor.cursorPosY == whichPlayer.MedRoom.coordY[1]))  ||  ((cursor.cursorPosX == whichPlayer.MedRoom.coordX[2]) && (cursor.cursorPosY == whichPlayer.MedRoom.coordY[2])) ||  ((cursor.cursorPosX == whichPlayer.MedRoom.coordX[3]) && (cursor.cursorPosY == whichPlayer.MedRoom.coordY[3])) )
	{
		whatIsAiming = whichPlayer.MedRoom.roomName;
		//makeObjVis(THE_GUY);	
	}
	else if(((cursor.cursorPosX == whichPlayer.SheRoom.coordX[0]) && (cursor.cursorPosY == whichPlayer.SheRoom.coordY[0])) || ((cursor.cursorPosX == whichPlayer.SheRoom.coordX[1]) && (cursor.cursorPosY == whichPlayer.SheRoom.coordY[1]))  ||  ((cursor.cursorPosX == whichPlayer.SheRoom.coordX[2]) && (cursor.cursorPosY == whichPlayer.SheRoom.coordY[2])) ||  ((cursor.cursorPosX == whichPlayer.SheRoom.coordX[3]) && (cursor.cursorPosY == whichPlayer.SheRoom.coordY[3])) )
	{
		whatIsAiming = whichPlayer.SheRoom.roomName;
		//makeObjVis(THE_GUY);	
	}
	else if(((cursor.cursorPosX == whichPlayer.NavRoom.coordX[0]) && (cursor.cursorPosY == whichPlayer.NavRoom.coordY[0])) || ((cursor.cursorPosX == whichPlayer.NavRoom.coordX[1]) && (cursor.cursorPosY == whichPlayer.NavRoom.coordY[1]))  )
	{
		whatIsAiming = whichPlayer.NavRoom.roomName;
		//makeObjVis(THE_GUY);	
	}
	else if(((cursor.cursorPosX == whichPlayer.EngRoom.coordX[0]) && (cursor.cursorPosY == whichPlayer.EngRoom.coordY[0])) || ((cursor.cursorPosX == whichPlayer.EngRoom.coordX[1]) && (cursor.cursorPosY == whichPlayer.EngRoom.coordY[1]))  )
	{
		whatIsAiming = whichPlayer.EngRoom.roomName;
		//makeObjVis(THE_GUY);	
	}
	else if(((cursor.cursorPosX == whichPlayer.WepRoom.coordX[0]) && (cursor.cursorPosY == whichPlayer.WepRoom.coordY[0])) || ((cursor.cursorPosX == whichPlayer.WepRoom.coordX[1]) && (cursor.cursorPosY == whichPlayer.WepRoom.coordY[1]))  )
	{
		whatIsAiming = whichPlayer.WepRoom.roomName;
		//makeObjVis(THE_GUY);	
	}
	else
	{
			
		whatIsAiming = noRoom;
	}
}
void damageThisRoom(weapon &gun, player &whichPlayer)
{
	switch(gun.targeting)
	{
		case navRoom:	whichPlayer.NavRoom.health -= gun.damage;
								break;
								
		case engRoom: 	whichPlayer.EngRoom.health -= gun.damage;
								break;
								
		case wepRoom: 	whichPlayer.WepRoom.health -= gun.damage;
								break;
								
		case sheRoom: 	whichPlayer.SheRoom.health -= gun.damage;
								break;
								
		case medRoom:	whichPlayer.MedRoom.health -= gun.damage;
								break;
		
		case oxyRoom: 	whichPlayer.OxyRoom.health -= gun.damage;
								break;
								
		case noRoom: 	//nothing
								break;
				
	}
	
	whichPlayer.hullHealth -= gun.damage;

}

void doesWeaponHit(weapon &gun, player &whichPlayer, room &shieldRoom)
{
	//random chance to hit dertemind by enemies evade skill and player wepon skill
	int hit = rand()%100;
	
	
	
	if(hit > whichPlayer.evade)
	{
	//if hit create a bullet a what ever x and y
		
	// when that bulllet reaches the enemy ship
		//if hit
			//show HIT
			if(gun.penetrate == false && shieldRoom.health > 0)
			{
				shieldRoom.health -= gun.damage;
				gun.shieldHit = true;
			}
			else
			{
				damageThisRoom(gun, whichPlayer);
				
			}
			
			if(whichPlayer.captain.playerTarget == gun.targeting)
			{
				whichPlayer.captain.health -=10;
			}
			gun.hit = true;
	}
	else 
	{
		gun.miss = true;
	}
	
	
	
}
void setUpPlayerRooms(int shipX, int shipY)
{
	guy.NavRoom.initalize(shipX+7, shipY+1, NAV_ROOM, 265, navRoom);
	guy.EngRoom.initalize(shipX+9, shipY+2, ENG_ROOM, 326, engRoom);	
	guy.WepRoom.initalize(shipX+7, shipY+6, WEP_ROOM, 281, wepRoom);	
	guy.OxyRoom.initalize(shipX+2, shipY+3, OXY_ROOM, 288, oxyRoom);	
	guy.MedRoom.initalize(shipX+5, shipY+3, MED_ROOM, 294, medRoom); 
	guy.SheRoom.initalize(shipX+11, shipY+3, SHE_ROOM, 320, sheRoom);
	
	guy.captain.setPlayerPos(guy.WepRoom.getX(), guy.WepRoom.getY());
	guy.captain.setObj(THE_GUY);
	
	
	guy.captain.playerTarget = noRoom;

	
	guy.missle.penetrate = true;
}
void drawPlayerRoomHealth()
{
	guy.NavRoom.getState();
	guy.NavRoom.drawState();
	
	guy.EngRoom.getState();
	guy.EngRoom.drawState();
	
	guy.WepRoom.getState();
	guy.WepRoom.drawState();
	
	guy.OxyRoom.getState();
	guy.OxyRoom.drawState();
	
	guy.MedRoom.getState();
	guy.MedRoom.drawState();
	
	guy.SheRoom.getState();
	guy.SheRoom.drawState();

}
void setAllRoomCoords()
{
	guy.SheRoom.setTargetCoords();
	guy.MedRoom.setTargetCoords();
	guy.OxyRoom.setTargetCoords();
	guy.EngRoom.setTargetCoords();
	guy.WepRoom.setTargetCoords();
	guy.NavRoom.setTargetCoords();
	
	enemy.SheRoom.setTargetCoords();
	enemy.MedRoom.setTargetCoords();
	enemy.OxyRoom.setTargetCoords();
	enemy.WepRoom.setTargetCoords();
	enemy.EngRoom.setTargetCoords();
	enemy.NavRoom.setTargetCoords();
}

void playerStartingStats()
{
	guy.NavRoom.maxHealth = 1;
	guy.EngRoom.maxHealth = 1;
	guy.WepRoom.maxHealth = 2;
	guy.OxyRoom.maxHealth = 1;
	guy.MedRoom.maxHealth = 1;
	guy.SheRoom.maxHealth = 2;



	guy.NavRoom.health = guy.NavRoom.maxHealth;
	guy.EngRoom.health = guy.EngRoom.maxHealth;
	guy.WepRoom.health = guy.WepRoom.maxHealth;
	guy.OxyRoom.health = guy.OxyRoom.maxHealth;
	guy.MedRoom.health = guy.MedRoom.maxHealth;
	guy.SheRoom.health = guy.SheRoom.maxHealth;

	guy.hullHealth = MAX_HULL;


}
void setEnemyStats(currentDifficulty difficulty)
{
	for(int i = 0; i < 6; i++) //I have 6 room objs to cycle through
	{
		makeObjVis(NAV_ROOM+i);
	}
	
	enemy.SheRoom.doesRoomExist(true);
	enemy.NavRoom.doesRoomExist(true);
	enemy.WepRoom.doesRoomExist(true);
	enemy.EngRoom.doesRoomExist(true);
	enemy.MedRoom.doesRoomExist(true);
	enemy.OxyRoom.doesRoomExist(true);
	
	switch(difficulty)
	{
		case veryEasy:	setEnemyRoomHealth(0,3);
								enemy.setRandomHullHealth(3,5);
								break;
		
		case easy:			setEnemyRoomHealth(1,3);
								enemy.setRandomHullHealth(5,6);
								break;
							
		case average:	setEnemyRoomHealth(1,5);
								enemy.setRandomHullHealth(5,8);
								break;
		
		case hard:			setEnemyRoomHealth(2,7);
								enemy.setRandomHullHealth(7,11);
								break;
								
		case veryHard:	setEnemyRoomHealth(3,9);
								enemy.setRandomHullHealth(10,11);
								enemy.SheRoom.maxHealth = MAX_SHEILD; // sheilds will be max for the hardest enemies
								enemy.SheRoom.health = MAX_SHEILD; 
								break;
	
	}
	
	
	if(enemy.NavRoom.maxHealth == 0)
	{
		makeObjInvis(ENEMY_NAV_ROOM);
		enemy.NavRoom.doesRoomExist(false);
		//make it not exisit to enemy AI
	}
	if(enemy.EngRoom.maxHealth == 0)
	{
		makeObjInvis(ENEMY_ENG_ROOM);
		enemy.EngRoom.doesRoomExist(false);
	}
	if(enemy.MedRoom.maxHealth == 0)
	{
		makeObjInvis(ENEMY_MED_ROOM);
		enemy.MedRoom.doesRoomExist(false);
	}
	if(enemy.SheRoom.maxHealth == 0)
	{
		makeObjInvis(ENEMY_SHE_ROOM);
		enemy.SheRoom.doesRoomExist(false);
	}
	
	enemy.missle.penetrate = true;
	
}
void setEnemyRoomHealth(int low, int high)
{
	enemy.NavRoom.setRandomHealth(low, high, MAX_NAV);
	enemy.EngRoom.setRandomHealth(low, high, MAX_ENG);
	enemy.WepRoom.setRandomHealth(low, high,MAX_WEP);
	enemy.OxyRoom.setRandomHealth(low, high, MAX_OXY);
	enemy.MedRoom.setRandomHealth(low, high, MAX_MEDBAY);
	enemy.SheRoom.setRandomHealth(low, high, MAX_SHEILD);
	
	if(enemy.SheRoom.maxHealth == 1) // meaning if the enemies shields are working
	{												//it will always have at least one shield orb
		enemy.SheRoom.maxHealth = 2;
		enemy.SheRoom.health = 2;
	
	}
	
	if(enemy.OxyRoom.maxHealth == 0)
	{
		enemy.OxyRoom.maxHealth = 1; //proctection so the enemy always has oxy and weapons
		enemy.OxyRoom.health = 1; 
	}
	
	if(enemy.WepRoom.maxHealth == 0)
	{
		enemy.WepRoom.maxHealth = 1;	
		enemy.WepRoom.health = 1;
	}
	
}


void drawSheildOrbs(int x, int y, int obj, int currentMaxSheild, int sheildLevel)
{
	int tempMax = currentMaxSheild * 0.5;
	
	int tempLevel = sheildLevel* 0.5;
	
			for(int i = 0; i < MAX_SHEILD; i++) //clears everything up to the full health
	{
		makeObjInvis(obj+i);
	
	}
	
	
	for(int i = 0; i < tempMax; i++) 
	{
		makeObjVis(obj+i);
		
		if( i >= tempLevel)
		{
			SetObjectID(obj+i, 362);
		}
		else 
		{
			SetObjectID(obj+i, 361);
		}
		
		SetObjectX(obj+i, x+(i*8));
		SetObjectY(obj+i, y);
	}
		
}
void setWepStats(player &whichPlayer, int powerLevel)
{
	switch(powerLevel)
	{
		case 0: 	whichPlayer.missle.upgrade(1,50);
					whichPlayer.plasma.upgrade(1,15);
					break;
		
		case 1:	whichPlayer.missle.upgrade(1, 15);
					whichPlayer.plasma.upgrade(1, 10);
					break;
					
		case 2:	whichPlayer.missle.upgrade(2 , 14);
					whichPlayer.plasma.upgrade(1, 9);
					break;
		
		case 3:	whichPlayer.missle.upgrade(2 , 12);
					whichPlayer.plasma.upgrade(2, 9);
					break;
		
		case 4:	whichPlayer.missle.upgrade(2 , 12);
					whichPlayer.plasma.upgrade(2, 8);
					break;
					
		case 5:	whichPlayer.missle.upgrade(2 , 11);
					whichPlayer.plasma.upgrade(2, 7);
					break;
		
		case 6:	whichPlayer.missle.upgrade(2 , 11);
					whichPlayer.plasma.upgrade(2, 6);
					break;
	}


} 

void setEvadeChance(player &whichPlayer, int navLevel, int engineLevel)
{
	switch(engineLevel)
	{
		case 0:	whichPlayer.evade = 0;
					break;
					
		case 1:	whichPlayer.evade = 10 + (navLevel*3);
					break;
					
		case 2:	whichPlayer.evade = 15 + (navLevel*3);;
					break;
					
		case 3:	whichPlayer.evade = 20 + (navLevel*3);
					break;
					
		case 4:	whichPlayer.evade = 25 + (navLevel*3);
					break;	
					
		case 5:	whichPlayer.evade = 30 + (navLevel*3);
					break;
		
		case 6:	whichPlayer.evade = 40 + (navLevel*3);
					break;
		
	}


}
void bulletFired( bullet &Bullet, weapon &gun, int obj)
{
	if(Bullet.fired)
	{
		Bullet.x++;
		
		if(Bullet.x >= 150)
		{
			doesWeaponHit(gun, enemy, enemy.SheRoom);
			makeObjInvis(obj);
			Bullet.fired = false;
			Bullet.x = 60;
		}
				
	}
}
void enemyBulletFired( bullet &Bullet, weapon &gun, int obj)
{
	if(Bullet.fired)
	{
		Bullet.x--;
		
		if(Bullet.x <= 60)
		{
			doesWeaponHit(gun, guy, guy.SheRoom);
			makeObjInvis(obj);
			Bullet.fired = false;
			Bullet.x = 150;
		}
				
	}
}
void movementControls(uint16_t currentKeys, uint16_t prevKeys)
{

		if (((currentKeys & KEY_L) == 0))
		{
					
			missleCrosshair.cursorControl(currentKeys, prevKeys);
					
			
		}
		else if (((currentKeys & KEY_R) == 0))
		{
			plasmaCrosshair.cursorControl(currentKeys, prevKeys);
		
		}
		else
		{
			crosshair.cursorControl(currentKeys, prevKeys);
		}
		
		if (((currentKeys & KEY_A) == 0) && ((currentKeys & KEY_L) != 0) && ((currentKeys & KEY_R) != 0))
		{
			guy.captain.setPlayerPos(crosshair.cursorPosX, crosshair.cursorPosY);
			getTarget(crosshair, guy, guy.captain.playerTarget);
			guy.captain.setRepairCounter(0);
		}
/* 		if (((currentKeys & KEY_B) == 0) && ((currentKeys & KEY_L) != 0) && ((currentKeys & KEY_R) != 0))
		{
			guy.commander.setPlayerPos(crosshair.cursorPosX, crosshair.cursorPosY);
			getTarget(crosshair, guy, guy.commander.playerTarget);
			guy.commander.setRepairCounter(0);
		} */
	
}
void shootingControls(uint16_t currentKeys, int &plasmaBarY, int &missleBarY)
{
			
		if(((currentKeys & KEY_L) == 0) &&((currentKeys & KEY_A) == 0) && guy.missle.fireCounter >= guy.missle.fireRate)
		{
			getTarget(missleCrosshair, enemy,  guy.missle.targeting);
			missleBullet.fired = true;
			makeObjVis(MISSLE);				
			missleBarY = 128; //origin				
			guy.missle.fireCounter = 0;
			guy.missle.chargeCounter = 0;
			makeObjInvis(MISSLE_READY);
			
		}
		
		
		if(((currentKeys & KEY_R) == 0) &&((currentKeys & KEY_A) == 0) && guy.plasma.fireCounter >= guy.plasma.fireRate)
		{
			getTarget(plasmaCrosshair, enemy, guy.plasma.targeting);
			plasmaBullet.fired = true;
			makeObjVis(PLASMA);				
			plasmaBarY = 128; //origin				
			guy.plasma.fireCounter = 0;
			guy.plasma.chargeCounter = 0;
			makeObjInvis(PLASMA_READY);				

		}
}
void updateWeapons(int &missleBarY, int &plasmaBarY)
{
	bulletFired(missleBullet, guy.missle, MISSLE);
	bulletFired(plasmaBullet, guy.plasma, PLASMA);
	enemyBulletFired(enemyPlasmaBullet, enemy.plasma, ENEMY_PLASMA);
	enemyBulletFired(enemyMissleBullet, enemy.missle, ENEMY_MISSLE);
	SetObjectX(MISSLE, missleBullet.x);
	SetObjectX(PLASMA, plasmaBullet.x);
	SetObjectX(ENEMY_MISSLE, enemyMissleBullet.x);
	SetObjectX(ENEMY_PLASMA, enemyPlasmaBullet.x);
			

	if(guy.plasma.fireCounter >= guy.plasma.fireRate)
	{
		makeObjVis(PLASMA_READY);
	
	}
		
	if(guy.missle.fireCounter >= guy.missle.fireRate)
	{
		makeObjVis(MISSLE_READY);
	
	}
	
	if(guy.plasma.chargeCounter >= guy.plasma.fireRate/6) //6 segments to move down
	{
		plasmaBarY++;
		guy.plasma.chargeCounter = 0;
	
	}
		
	if(guy.missle.chargeCounter >= guy.missle.fireRate/6)
	{
		missleBarY++;
		guy.missle.chargeCounter = 0;
	
	}
	
	if( enemy.missle.fireCounter >= enemy.missle.fireRate)
	{
		enemyMissleBullet.fired = true;
		makeObjVis(ENEMY_MISSLE);				
		
		enemy.missle.fireCounter = 0;				
	}
	if( enemy.plasma.fireCounter >= enemy.plasma.fireRate)
	{
		enemyPlasmaBullet.fired = true;
		makeObjVis(ENEMY_PLASMA);				
		
		enemy.plasma.fireCounter = 0;				
	}

	
	guy.plasma.showWeaponMiss(MISS_PLASMA, guy.plasma.missCounter, guy.plasma.miss);
	guy.missle.showWeaponMiss(MISS_MISSLE, guy.missle.missCounter, guy.missle.miss);
	guy.plasma.showWeaponMiss(MISS_SHIELD, guy.plasma.shieldCounter, guy.plasma.shieldHit);
	
	enemy.plasma.showWeaponMiss(ENEMY_MISS_PLASMA, enemy.plasma.missCounter, enemy.plasma.miss);
	enemy.missle.showWeaponMiss(ENEMY_MISS_MISSLE, enemy.missle.missCounter, enemy.missle.miss);
	enemy.plasma.showWeaponMiss(ENEMY_MISS_SHIELD, enemy.plasma.shieldCounter, enemy.plasma.shieldHit); 
	
	//guy.missle.showExplosion(MIS_EXPL, guy.missle.explosionCounter, guy.missle.hit);

	SetObjectY(MISSLE_BAR, missleBarY);
	SetObjectY(PLASMA_BAR, plasmaBarY);

}
void drawObjs()
{
	crosshair.drawOneTile();			
	missleCrosshair.drawOneTile();			
	plasmaCrosshair.drawOneTile();
	
	guy.captain.drawPlayer();
	enemy.captain.drawPlayer();
			
	drawEnemyRoomHealth();
	drawPlayerRoomHealth();
	
	drawNumber(5,5, guy.captain.health);
	drawNumber(12,5, guy.evade);
	drawNumber(14,1, guy.coins);

	drawHullHealth(8, 17 , HULL_BAR, guy.hullHealth);
	drawHullHealth(168, 137, ENEMY_HULL_BAR, enemy.hullHealth);
	
	drawPowerBars(17, 130, OXY_BAR, guy.OxyRoom.maxHealth, guy.OxyRoom.health);
	drawPowerBars(25, 130, NAV_BAR, guy.NavRoom.maxHealth, guy.NavRoom.health);
	drawPowerBars(33, 130, MED_BAR, guy.MedRoom.maxHealth, guy.MedRoom.health);
	drawPowerBars(41, 130, SHE_BAR, guy.SheRoom.maxHealth, guy.SheRoom.health);
	drawPowerBars(49, 130, ENG_BAR, guy.EngRoom.maxHealth, guy.EngRoom.health);
	drawPowerBars(57, 130, WEP_BAR, guy.WepRoom.maxHealth, guy.WepRoom.health);
	
	
	drawSheildOrbs(40,25, PLAYER_ORB, guy.SheRoom.maxHealth, guy.SheRoom.health);
	drawSheildOrbs(200,145, ENEMY_ORB, enemy.SheRoom.maxHealth, enemy.SheRoom.health);

}
void updateCounters()
{
	guy.missle.fireCounter++;
	guy.plasma.fireCounter++;
	guy.missle.chargeCounter++;
	guy.plasma.chargeCounter++;
	guy.captain.repairCounter++;
	guy.oxyCounter++;
	guy.healingCounter++;
	
	enemy.missle.fireCounter++;
	enemy.plasma.fireCounter++;
	enemy.captain.repairCounter++;
	enemy.oxyCounter++;
	enemy.healingCounter++;
	
}
void getEnemyTarget()
{
	int hitThis; 

	if(guy.EngRoom.health > 3)
	{
		enemy.missle.targeting = guy.EngRoom.roomName;
		enemy.plasma.targeting = guy.SheRoom.roomName;
	}
	else if(guy.SheRoom.health >= 2)
	{
		hitThis = rand()%2;
		
		if(hitThis == 0 && guy.WepRoom.health != 0)
		{
			enemy.missle.targeting = guy.WepRoom.roomName;
			
		}
		else
		{
			enemy.missle.targeting = guy.SheRoom.roomName;
		}
		enemy.plasma.targeting = guy.SheRoom.roomName;
	}
	else
	{	
		hitThis = rand()%6+1;
		
		if(hitThis == 1 && guy.NavRoom.health != 0)
		{
			enemy.missle.targeting = guy.NavRoom.roomName;
			enemy.plasma.targeting = guy.NavRoom.roomName;			
		}
		else if(hitThis == 2 && guy.WepRoom.health != 0)
		{
			enemy.missle.targeting = guy.WepRoom.roomName;		
			enemy.plasma.targeting = guy.WepRoom.roomName;
		}
		else if(hitThis == 3 && guy.EngRoom.health != 0)
		{
			enemy.missle.targeting = guy.EngRoom.roomName;
			enemy.plasma.targeting = guy.EngRoom.roomName;
		}
		else if(hitThis == 4 && guy.OxyRoom.health != 0)
		{
			enemy.missle.targeting = guy.OxyRoom.roomName;	
			enemy.plasma.targeting = guy.OxyRoom.roomName;
		}
		else if(hitThis == 5 && guy.MedRoom.health != 0)
		{
			enemy.missle.targeting = guy.MedRoom.roomName;	
			enemy.plasma.targeting = guy.MedRoom.roomName;
		}
		else if(hitThis == 6 && guy.NavRoom.health != 0)
		{
			enemy.missle.targeting = guy.SheRoom.roomName;
			enemy.plasma.targeting = guy.SheRoom.roomName;
		}
		else 
		{
			enemy.missle.targeting = guy.WepRoom.roomName;		
			enemy.plasma.targeting = guy.WepRoom.roomName;		
		}
		
	
	}
	
}
void roomHealthSafetyCheck()
{
enemy.NavRoom.fixHealth(); //try to stick these in classes
enemy.EngRoom.fixHealth();
enemy.WepRoom.fixHealth();
enemy.OxyRoom.fixHealth();
enemy.MedRoom.fixHealth();
enemy.SheRoom.fixHealth();

guy.NavRoom.fixHealth();
guy.EngRoom.fixHealth();
guy.WepRoom.fixHealth();
guy.OxyRoom.fixHealth();
guy.MedRoom.fixHealth();
guy.SheRoom.fixHealth();

}
void repairRoom(character &whichChar, player &whichPlayer)
{
	if(whichChar.repairCounter >= whichChar.repairTime)
	{
		healThisRoom(whichChar, whichPlayer);
	
	}

}
void healThisRoom(character &whichChar, player &whichPlayer)
{
	switch(whichChar.playerTarget) //if the capatin is "targeting" the room
	{
		case navRoom:	whichPlayer.NavRoom.repairAndCheck();
								break;
								
		case engRoom: 	whichPlayer.EngRoom.repairAndCheck();
								break;
								
		case wepRoom: 	whichPlayer.WepRoom.repairAndCheck();
								break;
								
		case sheRoom: 	whichPlayer.SheRoom.repairAndCheck();
								break;
								
		case medRoom:	whichPlayer.MedRoom.repairAndCheck();
								break;
		
		case oxyRoom: 	whichPlayer.OxyRoom.repairAndCheck();
								break;
								
		case noRoom: 	//nothing
								break;
				
	}
	
	whichChar.setRepairCounter(0);

}
void levelStatusCheck(bool &enemyDead, int x, int y, int &shipsDestroyed, currentDifficulty dif)
{
	if(guy.hullHealth <= 0 || guy.captain.health <= 0)
	{
		gameOver();
	}
	if(enemy.hullHealth <= 0)
	{
		shipsDestroyed++;
		nextLevel(x, y, shipsDestroyed, dif);
		enemyDead= true;
	}

}
void gameOver()
{
	while(true)
	{
		clearScreenBlock30();
		setUpObjects();
		moveStars(1);
		drawText(2,3, "GAME OVER");
		drawText(10,9, "YOU HAVE NO CHANCE");
		drawText(18,104, "TO SURVIVE");
		
		drawText(14,17, "MAKE YOUR TIME");
		
		WaitVSync();
		UpdateObjects();
	}
}
void nextLevel(int x, int y, int &shipsDestroyed, currentDifficulty dif)
{
	float warp = 0;
	
	int tempScrap = getWinningScrap(dif);	
	guy.coins += tempScrap;
	
	while(true)
	{
		uint16_t currentKeys = REG_KEYINPUT;
		
		setUpObjects();
		clearScreenBlock30();
		moveStars(1);
		drawShip(PLAYERSHIP, x, y);
		drawText(8,3, "ENEMY SHIP DESTROYED");
		drawText(6,5, "NO. OF SHIPS DESTROYED");
		
		drawText(16, 8, "SCRAP GAINED");
		drawNumber(25, 9, tempScrap);
		
		drawNumber(25, 6, shipsDestroyed);
		
		drawText(15, 15, "PRESS START");
		
		
		if (((currentKeys & KEY_START) == 0))
		{
				
				break;
		}
		
		WaitVSync();
		UpdateObjects();
		
	}
	while(true)
	{
		clearScreenBlock30();
		moveStars(warp);
		
		warp+= 0.2;
		if(warp >= 40)
		{
			break;
		}
				
		WaitVSync();
		UpdateObjects();
	}
	upgrades();

}
void drawNumber(int x, int y, int number)
{
	//take a number.
	//get the H...T...U
	int H, T, U, R;
	
	if(number >= 100)
	{
		H = number* 0.01;

		R = number%100;

		T = R*0.1;

		U = R%10;
	}
	else if(number >= 10)
	{
		H = 0;
	
		T = number*0.1;
		
		U = number%10;
		
	}
	else if( number < 10)
	{
		H = 0;
		T = 0;
		U  = number;	
	}
	

	
	//3 seperate objects H T U
	
	//SetTile(30, x, y, 0)
	
	SetTile(30, x, y, NUM_INDEX+H);
	SetTile(30, x+1, y, NUM_INDEX+T);
	SetTile(30, x +2, y, NUM_INDEX+U);

	

}
void resetEncounter(int &missleBarY, int &plasmaBarY )
{
	guy.missle.fireCounter = 0;
	guy.plasma.fireCounter= 0;
	guy.missle.chargeCounter = 0;
	guy.plasma.chargeCounter = 0;
	guy.captain.repairCounter = 0;
	enemy.missle.fireCounter = 0;
	enemy.plasma.fireCounter = 0;
	
	guy.NavRoom.health = guy.NavRoom.maxHealth;
	guy.EngRoom.health = guy.EngRoom.maxHealth;
	guy.WepRoom.health = guy.WepRoom.maxHealth;
	guy.OxyRoom.health = guy.OxyRoom.maxHealth;
	guy.MedRoom.health = guy.MedRoom.maxHealth;
	guy.SheRoom.health = guy.SheRoom.maxHealth;
	
	guy.captain.health = 100;
	enemy.captain.health =100;
	
	missleBarY = 128;
	plasmaBarY = 128;
	
	missleBullet.fired = false; // stops the bullet from moving at the start of the next encounter
	plasmaBullet.fired = false;
	enemyMissleBullet.fired = false;
	enemyPlasmaBullet.fired = false;
}
void getDifficulty(int shipsDestroyed, currentDifficulty &dif)
{
	if(shipsDestroyed <= 4)
	{
		dif = veryEasy;
	}
	if(shipsDestroyed >= 5 && shipsDestroyed <= 8)
	{
		dif = easy;
	}
	if(shipsDestroyed >= 9 && shipsDestroyed <= 13)
	{
		dif = average;
	}
	if(shipsDestroyed >= 14 && shipsDestroyed <= 17)
	{
		dif = hard;
	}
	if(shipsDestroyed >= 18)
	{
		dif = veryHard;
	}

}
void getEnemyCaptainTarget()
{
	if(enemy.captain.health < 100 && enemy.MedRoom.getExistance() )
	{
		enemy.captain.playerTarget = enemy.MedRoom.roomName;
		enemy.captain.setPlayerPos(enemy.MedRoom.getX(), enemy.MedRoom.getY());	
	}

	basicEnemyRepairCheck(enemy.captain, enemy.MedRoom); //simple if statements in order of room priority
	basicEnemyRepairCheck(enemy.captain, enemy.OxyRoom);
	basicEnemyRepairCheck(enemy.captain, enemy.NavRoom);
	basicEnemyRepairCheck(enemy.captain, enemy.SheRoom);
	basicEnemyRepairCheck(enemy.captain, enemy.EngRoom);
	basicEnemyRepairCheck(enemy.captain, enemy.WepRoom);

	
	//AI for some specific situations
	furtherEnemyRepairCheck(enemy.captain, enemy.SheRoom);
	furtherEnemyRepairCheck(enemy.captain, enemy.WepRoom);
	
	if(enemy.captain.health <= 25 && enemy.MedRoom.getExistance())
	{
		enemy.captain.playerTarget = enemy.MedRoom.roomName;
		enemy.captain.setPlayerPos(enemy.MedRoom.getX(), enemy.MedRoom.getY());
	}
	
	furtherEnemyRepairCheck(enemy.captain, enemy.OxyRoom);

	

}
void basicEnemyRepairCheck(character &whichChar, room &whichRoom)
{
	if(whichRoom.health < whichRoom.maxHealth && whichRoom.getExistance())
	{
		whichChar.playerTarget = whichRoom.roomName;
		whichChar.setPlayerPos(whichRoom.getX(), whichRoom.getY());
	}
}
void furtherEnemyRepairCheck(character &whichChar, room &whichRoom)
{
	if(whichRoom.health == 0 && whichRoom.getExistance())
	{
		whichChar.playerTarget = whichRoom.roomName;
		whichChar.setPlayerPos(whichRoom.getX(), whichRoom.getY());
	}
	

}
void checkForEnemyMovement(character &whichChar)
{
	//if the enemy moves rooms, reset his room counter
	
	//whichChar.tempTarget
	
	if(whichChar.tempTarget != whichChar.playerTarget)
	{
		whichChar.repairCounter = 0;
	}

	whichChar.tempTarget = whichChar.playerTarget;
	
}
void oxygenCheck(player &whichPlayer)
{
	int oxyDecrementer = 30;
	
	if(whichPlayer.OxyRoom.health == 0 && whichPlayer.oxyCounter >= oxyDecrementer)
	{
		whichPlayer.captain.health--;
		whichPlayer.oxyCounter = 0;
	
	}
	
}
void healingRoom(character &whichChar, player &whichPlayer)
{
	int healingIncrementor = 40/whichPlayer.MedRoom.health;

	if(whichChar.playerTarget == medRoom && whichPlayer.healingCounter >= healingIncrementor)
	{
		whichChar.health++;
		whichPlayer.healingCounter = 0;
	}

}
void enemyShipApproaching()
{
	setUpObjects();
	while(true)
	{
	
		clearScreenBlock30();
		uint16_t currentKeys = REG_KEYINPUT;
		
		moveStars(1);
		drawText(7, 2, "...WARNING...");
		drawText(16, 9, "ENEMY SHIP");
		drawText(19, 10, "INBOUND");
	
		
		
		drawText(15, 18, "...PRESS A");
		WaitVSync();
		UpdateObjects();
		if ((currentKeys & KEY_A) == 0)
		{
			break;
		}
		
		
	}
}
void upgrades()
{
	setUpObjects();
	
	clearScreenBlock30();
	
	int navCost = 10;
	int engCost = 15;
	int wepCost = 30;
	int sheCost = 20;
	int medCost = 15;
	int oxyCost = 15;
	int hullCost = 4;
	
	drawText(1, 1, "UPGRADES.");	
	drawText(1,3, "COST");
	drawText(8, 4, "NAVIGATION ROOM");
	drawText(8, 6, "ENGINE ROOM");
	drawText(8, 8, "WEAPON ROOM");
	drawText(8, 10, "SHIELD ROOM");
	drawText(8, 12, "MED BAY");
	drawText(8, 14, "LIFESUPPORT");
	
	drawText(17,1, "SCRAP");
	
	drawText(14, 16, "B TO RESTORE ");
	drawText(14,17, "HEALTH.COST");
	drawNumber(26, 17 , hullCost);
	drawText(18, 18, "OF");
	
	drawNumber(2,4, navCost);
	drawNumber(2,6, engCost);
	drawNumber(2,8, wepCost);
	drawNumber(2,10, sheCost);
	drawNumber(2,12, medCost);
	drawNumber(2,14, oxyCost);
	
	guy.NavRoom.initalize(25, 4, NAV_ROOM, 265, navRoom);
	guy.EngRoom.initalize(25, 6, ENG_ROOM, 326, engRoom);	
	guy.WepRoom.initalize(25, 8, WEP_ROOM, 281, wepRoom);	
	guy.SheRoom.initalize(25, 10, SHE_ROOM, 320, sheRoom);
	guy.MedRoom.initalize(25, 12, MED_ROOM, 294, medRoom); 
	guy.OxyRoom.initalize(25, 14, OXY_ROOM, 288, oxyRoom);	
	
	setAllRoomCoords();
	
	uint16_t prevKeys = 0;
	
	makeObjVis(CURSOR);
	crosshair.cursorObjNumber = CURSOR; 

	
	crosshair.clearGrid();
	crosshair.cursorPosX = 25; 
	crosshair.cursorPosY = 4;
	crosshair.placeOnGrid(25, 4,upgradeLayout);
	

	
	setWepUIonSB();
		
	while(true)
	{
		uint16_t currentKeys = REG_KEYINPUT;
	
		moveStars(1);
		drawNumber(23, 1, guy.coins);
		drawNumber(14, 18 , guy.hullHealth);
		drawNumber(21, 18 , MAX_HULL);
		
		
		crosshair.cursorControl(currentKeys, prevKeys);
		getTarget(crosshair, guy, guy.captain.playerTarget);
		
		highlightRoom(guy.OxyRoom, oxyCost, currentKeys, prevKeys, MAX_OXY);
		highlightRoom(guy.NavRoom, navCost,  currentKeys, prevKeys, MAX_NAV);
		highlightRoom(guy.EngRoom, engCost, currentKeys, prevKeys, MAX_ENG);
		highlightRoom(guy.WepRoom, wepCost, currentKeys, prevKeys, MAX_WEP);
		highlightRoom(guy.SheRoom, sheCost, currentKeys, prevKeys,MAX_SHEILD);
		highlightRoom(guy.MedRoom, medCost, currentKeys, prevKeys, MAX_MEDBAY);
		
		drawPowerBars(17, 130, OXY_BAR, guy.OxyRoom.maxHealth, guy.OxyRoom.health);
		drawPowerBars(25, 130, NAV_BAR, guy.NavRoom.maxHealth, guy.NavRoom.health);
		drawPowerBars(33, 130, MED_BAR, guy.MedRoom.maxHealth, guy.MedRoom.health);
		drawPowerBars(41, 130, SHE_BAR, guy.SheRoom.maxHealth, guy.SheRoom.health);
		drawPowerBars(49, 130, ENG_BAR, guy.EngRoom.maxHealth, guy.EngRoom.health);
		drawPowerBars(57, 130, WEP_BAR, guy.WepRoom.maxHealth, guy.WepRoom.health);
		
		if((currentKeys & KEY_START) == 0) 
		{
			break;
		}
		if(((currentKeys & KEY_B) == 0)&& ((prevKeys & KEY_B) != 0) && hullCost <= guy.coins && guy.hullHealth < MAX_HULL) 
		{
			guy.coins -= hullCost;
			guy.hullHealth++;
		}
		
		crosshair.drawOneTile();	
		WaitVSync();
		UpdateObjects();
		
		prevKeys = currentKeys;
	}
}
void highlightRoom(room &whichRoom, int cost, uint16_t &currentKeys, uint16_t &prevKeys,  int MAX)
{
	if(guy.captain.playerTarget == whichRoom.roomName)
	{
		SetObjectID(whichRoom.obj, whichRoom.objIndex+2);
		
		if(((currentKeys & KEY_A) == 0) && ((prevKeys & KEY_A) != 0) && cost <= guy.coins && whichRoom.maxHealth < MAX) 
		{
			guy.coins -= cost;
			whichRoom.maxHealth++;
		}
		
		
	}
	else
	{
		SetObjectID(whichRoom.obj, whichRoom.objIndex);
	}
	
	whichRoom.health = whichRoom.maxHealth;

}
int getWinningScrap(currentDifficulty dif)
{
	int scrap;
	switch(dif)
	{
		case veryEasy:	scrap = getRandomScrap(5,20);
								break;
		
		case easy:			scrap = getRandomScrap(10,20);
								break;
							
		case average:	scrap = getRandomScrap(10,30);
								break;
		
		case hard:			scrap = getRandomScrap(15,40);
								break;
								
		case veryHard:	scrap = getRandomScrap(20,50);
								break;	
	
	
	}

	return scrap;
}
int getRandomScrap(int low, int high)
{
	int scrap = rand()%(high-low)+low;
	return scrap;
}

void setUpEncounter(
						int &shipsDestroyed, currentDifficulty &difficulty,
						int shipX, int shipY, 
						int enemyShipX, int enemyShipY,
						int &missleBarY, int &plasmaBarY,
						bool &enemyDead)
{
		if(shipsDestroyed >= 20)
		{
			showYouWin();
		}
		enemyShipApproaching();
		//////////////////////////////////Enemy encounter set up
		clearScreenBlock30();		
		setUI();		
		
		getDifficulty(shipsDestroyed, difficulty);
		//set up enemy based on level.... switch statement
		
		drawShip(PLAYERSHIP, shipX, shipY);		
		playerShip.placeOnGrid(shipX, shipY, shipLayout);
		playerShip.drawTiles();
		setUpPlayerRooms(shipX, shipY);	// set player pos as well		
		drawShip(ENEMYSHIP, enemyShipX, enemyShipY);		
		enemyShip.placeRandomLayout(enemyShipX,enemyShipY);
		enemyShip.drawTiles();			
		setUpEnemyRooms(enemyShipX, enemyShipY);	//set enemy pos as well			
		setUpCrosshairs(shipX, shipY, enemyShipX, enemyShipY); // call after placing the ships	
		resetEncounter(missleBarY, plasmaBarY);
		
		
		setAllRoomCoords();		
		setEnemyStats(difficulty);
					
		enemyDead = false;

}
void showYouWin()
{
	while(true)
	{
		clearScreenBlock30();
		setUpObjects();
		moveStars(1);
		drawText(2,3, "WELL DONE");
		drawText(7,9, "EARTH HAS BEEN SAVED");
		drawText(12,15, "WORST ENDING....");
		
		drawText(17,17, ".....EVER");
		
		WaitVSync();
		UpdateObjects();
	}
}


#endif