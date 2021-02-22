#ifndef __GAME_SCREEN_MAIN_H_
#define __GAME_SCREEN_MAIN_H_

//Include our Framework Library
#include <LJMUPCH.h>

//Include our Game Application Classes
#include <GameAssets.h>
#include <GameEnums.h>
#include <GameControls.h>
#include <GameBullet.h>
#include <GamePlayer.h>
#include <GameEnemy.h>
#include <GameManager.h>
#include <GameGrenade.h>
#include <GamePickup.h>

namespace LJMU
{
	///////////////////////////////
	// Implementation of the main
	// gameplay screen using our
	// Screen Interface Class. 
	//
	// AUTHOR:  DR CHRIS CARTER
	///////////////////////////////
	class LJMUGameScreenMain : public sf::ILJMUScreenBase
	{
		//---------CONSTANTS-------------------------------------------------------
		static const unsigned int   HUD_SCALE = 48;   //Constant to hold the scale of the HUD

		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		LJMUGameScreenMain();	//Default Constructor
		LJMUGameScreenMain(int diff);	//Default Constructor
		~LJMUGameScreenMain();	//Default Destructor

	public:
		//-----------FUNCTION OVERRIDES/INTERFACE IMPLEMENTATION-------------
		virtual void    loadContent() override;
		virtual void	handleEvent(const sf::Event& pevent) override;
		virtual void    bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered = false) override;
		virtual void	update(sf::Time& ptpf, sf::Time& ptotal) override;
		virtual void	render() override;
		virtual void    cleanup() override;

	public:
		//-----------PUBLIC FUNCTIONS----------------------------------------

		//-----------PROTECTED FUNCTIONS-------------------------------------
	protected:
		void handleInput(sf::Keyboard::Key pkey, bool ppressed); //Handle Keyboard Events
		void fireBullet(int pindex, sf::Vector2f pdir,BulletColour col, BulletMotion mo = BulletMotion::LINEAR);			 //Fire Player Bullets
		void fireGrenade(int pindex, sf::Vector2f pdir);
		void setupPlayer();										 //Setup the Player
		void setupAliens();										 //Setup the Aliens
		void setupPickup();
		void fire(int pindex);
		
	public:

		//-----------GETTERS/SETTERS-----------------------------------------
		int coolDown;
		int waveCoolDown;
		int immune;
		int weapon;
		
	protected:
		//-----------PROTECTED DATA------------------------------------------
		std::shared_ptr<LJMUPlayer>  _player;				    //Player Sprite
		//std::vector< std::shared_ptr<LJMUPlayer>> _list_player;
		std::vector<LJMUEnemy>		_list_alien;			    //List of Animated Alien Sprites
		std::vector<LJMUPickup> _list_pickup;

		std::vector<LJMUBullet>	   _list_bullets;			//List of Bullets
		std::vector<LJMUGrenade>	_list_grenades;
		LJMUGameManager			   _game_world;				//Our Game World
		sf::Time				   _time_npcf;				//Time of Last NPC Fire

		int diffuclty;
		int gameMode;
		int waveTime;
		
		//float alienGap;

	};
}
#endif