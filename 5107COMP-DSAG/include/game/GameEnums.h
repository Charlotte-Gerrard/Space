#ifndef __GAME_ENUMS_H_
#define __GAME_ENUMS_H_

///////////////////////////////
// Set of C++ 11 Scoped Enum 
// Classes for various purposes. 
//
// AUTHOR:  DR CHRIS CARTER
///////////////////////////////

namespace LJMU
{
	//----------------C++ 11 ENUMERATION DEFINITIONS--------------------------------------

	////////////////////////////////
	// Enumeration to represent the 
	// Types of HUD Display our Game
	// Has.
	////////////////////////////////
	enum class LJMUSIHUD
	{
		SCORE,
		LIVES,
		TIME,
		WAVE,
		IMMUNE
	};

	///////////////////////////////////
	// Enumeration of all the different
	// motion paths we could create. 
	///////////////////////////////////
	enum class LJMUEnemyMotion
	{
		CIRCULAR,
		SINUSOIDAL,
		LINEAR,
		WAVE,
		QUADRATIC
	};
	enum class BulletColour
	{
		WHITE,
		GREEN,
		RED
	};
	enum class BulletMotion
	{
		LINEAR,
		SINUSOIDAL
	};
	enum class Fonts
	{
		HUD,
		INFO
	};
	///////////////////////////////////
	// Enumeration to represent the 
	// states of the Gameplay.  
	///////////////////////////////////
	enum class LJMUGamePlayMode
	{
		GAME_START,
		GAME_PLAYING,
		GAME_WON,
		GAME_LOST,
		GAME_END
	};
	enum class LJMUPickupType
	{
		HEALTH,
		SHIELD
	};

}
#endif