#pragma once

//Include the LJMU Framework
#include <LJMUPCH.h>

//Include the Transform and Time Classes of SFML
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Clock.hpp>

//Include the Player Control Scheme. 
#include "GameControls.h"
#include "GameInterfaces.h"
#include "GameManager.h"

namespace LJMU
{
	///////////////////////////////////////
	// Class to represent an individual
	// Player within our game.  
	//
	// AUTHOR:  DR CHRIS CARTER
	///////////////////////////////////////
	class LJMUPlayer : public sf::ILJMUUpdatable, public ILJMUObjectState
	{
	public:
		//--------------------CONSTANTS---------------------------------------
		const int DEF_SPEED = 200;
		const int DEF_LIVES = 5;

		//--------------------CONSTRUCTORS/DESTRUCTORS------------------------
		LJMUPlayer(sf::LJMUAnimSprite psprite, LJMUPlayerControls pcontrols, sf::Vector2f pspawnpos);
		~LJMUPlayer();
	public:
		//--------------------PUBLIC METHODS-----------------------------------
		virtual void update(sf::Time& ptpf, sf::Time& ptotal) override;

	


	public:
		//--------------------CLASS MEMBERS------------------------------------
		sf::LJMUAnimSprite	Player;
		LJMUPlayerControls	Controls;
		sf::Vector2f		Direction;
		sf::Vector2f		SpawnPos;
		float				Speed;
		int                 Lives;
		sf::Time            LastChange;
		int                 IdleFrame;

		LJMUGameManager _game_world;
	};
}