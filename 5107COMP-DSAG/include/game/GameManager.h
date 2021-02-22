#ifndef __GAME_MANAGER_H_
#define __GAME_MANAGER_H_

#include <LJMUPCH.h>
#include <SFML/Graphics.hpp>
#include "GameControls.h"
#include "GameAssets.h"
#include "GameEnums.h"

namespace LJMU
{

	///////////////////////////////////////
	// Class to represent the Global State
	// of the Game. 
	//
	// AUTHOR: CHRIS CARTER
	///////////////////////////////////////
	class LJMUGameManager : sf::ILJMUUpdatable
	{
		//--------------------CONSTRUCTORS/DESTRUCTORS------------------------
	public:
		LJMUGameManager();
		~LJMUGameManager();
	public:
		//--------------------PUBLIC METHODS-----------------------------------
		void create(sf::Vector2f pwndsize);
		virtual void update(sf::Time& ptpf, sf::Time& ptotal) override;
		void destroy();
		void reduceLives();
		void increaseLives();
		void increaseScore(int val);
		int returnLives();
		void setImmune();
		void nextWave();
	public:
		bool bigScore();
	public:
		//--------------------CLASS MEMBERS------------------------------------
		//		MapEnemyColour;
		
		sf::View											CameraGame;
		sf::View											CameraHUD;
		LJMUCamControls										CameraControl;
		sf::LJMUResourceHelper<sf::Texture, LJMUSIAssets>   ResourceSprites;
		sf::LJMUResourceHelper<sf::Font, LJMUSIFont>   	    ResourceFonts;
		sf::LJMUResourceHelper<sf::Color,Colours>   ResourceColours;
		sf::Vector2f										MapEnemyColours;


		Colours tcolour;

		unsigned int										GameLives;
		unsigned int										GameScore;
		unsigned int										GameWave;
		sf::Vector2f										GameWorldSize;
		sf::Vector2f										GameWorldWindow;
		sf::FloatRect										GameWorldBounds;
		LJMUGamePlayMode									GameMode;
		float                                               GamePlayTime;
		float												GameStartTime; 
		float												GameEndTimeStart;
		float												GameEndTimeDelay;

		std::vector<sf::Sprite>								WorldLevel;
		std::map<LJMUSIHUD, sf::Text>						WorldHUD;
		bool												immune;
		int tdisptime;


	};
}
#endif