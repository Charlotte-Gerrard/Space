#ifndef __GAME_ASSETS_H_
#define __GAME_ASSETS_H_

//---------ENUMERATIONS AND ENUMERATED LISTS------------------------------

namespace LJMU
{
	//////////////////////////////////
	// Enumeration to represent the 
	// Different Font Assets available.
	// AUTHOR:  DR CHRIS CARTER
	//////////////////////////////////
	enum class LJMUSIFont
	{
		SANSATION = 0,
		RETRO
	};

	//////////////////////////////////
	// Enumeration to represent the 
	// Different Sprite Assets available.
	// AUTHOR:  DR CHRIS CARTER
	//////////////////////////////////
	enum class LJMUSIAssets
	{
		BG_ONE,
		BG_TWO,
		ALIEN_ONE_A,
		ALIEN_TWO,
		ALIEN_THREE,
		PLAYER_ANIM,
		BULLET,
		GRENADE,
		HEALTH,
		SHIELD
	};

	enum class Colours
	{
		RED,
		GREEN,
		BLUE
	};
}
#endif