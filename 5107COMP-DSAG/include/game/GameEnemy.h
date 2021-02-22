#ifndef __GAME_ENEMY_H_
#define __GAME_ENEMY_H_

//Include Framework
#include <LJMUPCH.h>

//Include SFML Framework
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Clock.hpp>

//Include Game Classes
#include <GameEnums.h>
#include <GameInterfaces.h>
#include "LJMUAnimSprite.h"

namespace LJMU
{
	///////////////////////////////
	// Implementation of the Enemy
	// Class. 
	//
	// AUTHOR:  DR CHRIS CARTER
	///////////////////////////////
	class LJMUEnemy : public sf::ILJMUUpdatable, public ILJMUObjectState
	{
	public:
		//--------------------CONSTRUCTORS/DESTRUCTORS------------------------
		LJMUEnemy(sf::LJMUAnimSprite psprite, sf::Vector2f pspawnpos, sf::Time pspawntime);
		LJMUEnemy() {};
		~LJMUEnemy();
	public:
		//--------------------PUBLIC METHODS-----------------------------------
		virtual void update(sf::Time& ptpf, sf::Time& ptotal) override;

	public:
		//--------------------ACCESSORS/MUTATORS-------------------------------
	public:
		//--------------------CLASS MEMBERS------------------------------------
		sf::Vector2f		 SpawnPos;
		sf::LJMUAnimSprite   Enemy;
		sf::Time             SpawnTime;
		float				 LifeTime;
		int					 score;

		//Four Parameters to Assist our Parametric Equations
		float				 Parameter1;
		float				 Parameter2;
		float				 Parameter3;
		float				 Parameter4;
		LJMUEnemyMotion      MotionType;
		int timer;
		int multiplier;
		bool zigUp;
		bool spin;
	};
}
#endif