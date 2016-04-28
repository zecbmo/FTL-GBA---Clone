//FTL a Slimline gba port
//Ported by Gary McCartan (Zecbmo)
//First Year CGAD
//1402860@abertay.ac.uk
//Enjoy!!

//c:\gba700\RunMake "$(CURRENT_DIRECTORY)" run

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

///////////////////////////////////////////////Main Function///////////////////////////////////////////////////////

int main()
{
	clearScreenBlock30();
	/////////////////////////////////////variables////////////////////
	int starSpeed = 1;
	int shipX = 0;
	int shipY= 6;
	int enemyShipX = 14;
	int enemyShipY = 6;
	int plasmaBarY = 128;
	int missleBarY = 128;
	int shipsDestroyed = 0;
	
	missleBullet.x = 60;
	plasmaBullet.x = 60;
	
	enemyMissleBullet.x = 150;
	enemyPlasmaBullet.x = 150;
	
	bool enemyDead = false;

	currentDifficulty difficulty = veryEasy;
	
	uint16_t prevKeys = 0;
	
	//////////////////////////initial game set up//////////////////////////////
	initialSetUp();
	
	showIntro();
	playerStartingStats();

	while(true) //////////////////////////////////////Main Game loop
	{		
		if(shipsDestroyed == 20)
		{
			showYouWin();
			
		}
		setUpEncounter(
						shipsDestroyed, difficulty,
						shipX, shipY, 
						enemyShipX, enemyShipY,
						missleBarY, plasmaBarY,
						enemyDead);
			
		while(!enemyDead)////////////////////Encounter with enemy... Playable part of the game
		{
			uint16_t currentKeys = REG_KEYINPUT;			
			roomHealthSafetyCheck();			
			setWepStats(guy, guy.WepRoom.health);
			setWepStats(enemy, enemy.WepRoom.health);						
			moveStars(starSpeed);			
						
			getEnemyTarget();
			getEnemyCaptainTarget();
			movementControls(currentKeys, prevKeys);
			shootingControls(currentKeys, plasmaBarY, missleBarY);			
			setEvadeChance(guy, guy.NavRoom.health, guy.EngRoom.health);
			setEvadeChance(enemy, enemy.NavRoom.health, enemy.EngRoom.health);						
			updateWeapons(missleBarY, plasmaBarY);
			
			repairRoom(guy.captain, guy);
			repairRoom(enemy.captain, enemy);
			checkForEnemyMovement(enemy.captain);
			
			oxygenCheck(guy);
			oxygenCheck(enemy);
			healingRoom(guy.captain, guy);
			healingRoom(enemy.captain, enemy);	
			
			drawObjs();
			WaitVSync();
			UpdateObjects();			
			updateCounters();			
			levelStatusCheck(enemyDead, shipX, shipY, shipsDestroyed, difficulty);			
			prevKeys = currentKeys;
					
		}
	


	}

}







	
	