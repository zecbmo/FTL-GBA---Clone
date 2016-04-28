#ifndef SHIP_CLASSES_H
#define SHIP_CLASSES_H

#define JUMP_TRIGGER 1000

#include "functions.h"

//enum charName {guyName, enemyName};

class weapon
{
	public:
		int damage;
		int fireRate;
		int fireCounter;
		int chargeCounter;
		
		bool penetrate;		
		bool miss;
		bool shieldHit;
		bool hit;
		
		int missCounter;
		int shieldCounter;
		float explosionCounter;
		
		target targeting;
				
		void upgrade(int newDamage, int newFireRate);
		void showWeaponMiss(int obj, int &counter, bool &hitOrMiss);
		//void showExplosion(int obj, float &counter, bool &wepHit);
};

struct bullet
{
	int x, y;
	bool fired;
	
	void missle()
	{
		fired = false;
		
	}

};
bullet missleBullet;
bullet plasmaBullet;
bullet enemyMissleBullet;
bullet enemyPlasmaBullet;

class character
{
	public:
		int repairCounter;
		int repairTime;		
		int obj;		
		int x;
		int y;
		int health;
		
		character()
		{
			repairTime = 8*60;
			health = 100;
		}
		
		target tempTarget;
		target playerTarget;
		void setPlayerPos(int newX, int newY);
		void setObj(int obj1);
		void drawPlayer();
		void setRepairCounter(int newTime);
		int getHealth();

};



class player
{

public:		
		
		int hullHealth;		
	
		int health;		
		int jumpLevel;
		int evade; 
		int coins;
		int ammo;		
		int oxyCounter;
		int healingCounter;
		
		weapon missle;
		weapon plasma;		
 		room NavRoom;
		room EngRoom;
		room WepRoom;
		room OxyRoom;
		room MedRoom;
		room SheRoom; 
		
		character captain;
		character commander;
		

		void setRandomHullHealth(int low, int high);

}; 

void weapon::upgrade(int newDamage, int newFireRate)
{
			damage = newDamage;
			fireRate = newFireRate*60; // converts it to seconds
			
		
} 
void weapon::showWeaponMiss(int obj, int &counter, bool &hitOrMiss)
{
	if(hitOrMiss)
	{
		makeObjVis(obj);
	
		counter++;
		
		if(counter > 2*60)
		{
			makeObjInvis(obj);
			hitOrMiss = false;
			counter = 0;
		
		}
	
	}

}
/* void weapon::showExplosion(int obj, float &counter, bool &wepHit)
{

	
	
	if(wepHit)
	{
		makeObjVis(obj);
	
		
		
		if(counter >= 0.5*60)
		{
			SetObjectID(obj,343);
		}
		if(counter >= 1*60)
		{
			SetObjectID(obj,344);
		}
		if(counter >= 1.5*60)
		{
			SetObjectID(obj,345);
		}
		
		
		if(counter > 2*60)
		{
			makeObjInvis(obj);
			wepHit = false;
			counter = 0;
			SetObjectID(obj, 342);
		}
		
		counter+=0.5;
	
	}

} */


void player::setRandomHullHealth(int low, int high)
{
	hullHealth = rand()%(high-low)+low;
}
void character::setPlayerPos(int newX, int newY)
{
	x = newX;
	y = newY;

}
void character::setObj(int obj1)
{
	obj = obj1;
}
void character::drawPlayer()
{
	makeObjVis(obj);
	SetObjectX(obj, x*8);
	SetObjectY(obj, y*8);

}
void character::setRepairCounter(int newTime)
{
	repairCounter = newTime;
}

#endif