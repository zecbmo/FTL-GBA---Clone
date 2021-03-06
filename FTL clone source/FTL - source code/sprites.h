#ifndef SPRITES_H
#define SPRITES_H

#include <stdint.h>


const uint8_t blankTile[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};
const uint8_t crosshairTile[64] = {
	12, 12, 12, 0, 0, 12, 12, 12,
	12, 0, 0, 0, 0, 0, 0, 12,
	12, 0, 0, 0, 0, 0, 0, 12,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	12, 0, 0, 0, 0, 0, 0, 12,
	12, 0, 0, 0, 0, 0, 0, 12,
	12, 12, 12, 0, 0, 12, 12, 12,
};


	  std::vector< std::vector< int > > shipLayout =  //16*8 to make it easier to lay over the imported sprites
{ 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 }, // a grid of the ship i want to place
    { 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};   
  std::vector< std::vector< int > > enemyLayout =
{
	
    { 0, 0, 0, 0, 0, 0, 0}, // a grid of the ship i want to place
    { 0, 1, 1, 1, 1, 1, 0},
    { 0, 1, 1, 0, 0, 1, 1},
    { 0, 1, 1, 0, 0, 1, 1},
    { 0, 0, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0},
	
};  

std::vector< std::vector< int > > upgradeLayout = 
{
	{1},
	{1},
	{1},
	{1},
	{1},
	{1},
	{1},
	{1},
	{1},
	{1},
	{1},
	{1},
};


void makeSomeStarTiles()
{
	
	
	for(int i = 1 ; i < 16; i++)
	{
		uint8_t k = 0, p = 0, f = 0, q = 0; //faux random star positions. set with the modulus operator

		if( i%2 == 0)
		{
			k = 1;
		}
		else if(i%2 ==1 && i !=9)
		{
			f = 1;
		}
		
		if(i%3 == 0)
		{
			p = 1;
		}
		if(i%5 ==0)
		{
			q = 1;
		}
			
		const uint8_t  new_tile[64] = 
			{
			0, 0, 0, 0, 0, 0, 0, 0,
			0, k, 0, 0, 0, q, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, p, 0, 0, 0,
			f, 0, 0, 0, 0, 0, 0, 0,
			0, 0, p, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, k, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			};
	
	
		
		LoadTile8(0, i, new_tile); //this may be affected by toncs thingymagig
		
	}
	

	
	
}

const uint8_t floorTileMiddle[64] = {
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
};


const uint8_t floorTileTop[64] = {
	5, 5, 5, 5, 5, 5, 5, 5,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
};
const uint8_t floorTileBottom[64] = {
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	5, 5, 5, 5, 5, 5, 5, 5,
};
const uint8_t floorTileLeft[64] = {
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
};
const uint8_t floorTileRight[64] = {
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
};
const uint8_t floorTileTopLeft[64] = {
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
};
const uint8_t floorTileTopRight[64] = {
	5, 5, 5, 5, 5, 5, 5, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
};
const uint8_t floorTileBottomLeft[64] = {
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 5, 5, 5, 5, 5, 5, 5,
}; 
const uint8_t floorTileBottomRight[64] = {
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
}; 
const uint8_t floorTileFarTop[64] = {
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
};  
const uint8_t floorTileFarBottom[64] = {
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
}; 
 const uint8_t floorTileFarLeft[64] = {
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 2, 2, 2, 2, 2, 2, 2,
	5, 5, 5, 5, 5, 5, 5, 5,
};  
 const uint8_t floorTileFarRight[64] = {
	5, 5, 5, 5, 5, 5, 5, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	2, 2, 2, 2, 2, 2, 2, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
};  
 const uint8_t floorTileTopBottom[64] = {
	5, 5, 5, 5, 5, 5, 5, 5,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	5, 5, 5, 5, 5, 5, 5, 5,
};
const uint8_t floorTileRightLeft[64] = {
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
	5, 2, 2, 2, 2, 2, 2, 5,
}; 
 // rightLeft,
 // topBottom,
 // alone



#endif
