#ifndef __GAME_SCREEN_OPTIONS_H_
#define __GAME_SCREEN_OPTIONS_H_


//Include our Framework Library
#include <LJMUPCH.h>
#include "GameObjectBasic.h"
#include "GameHUDElemBasic.h"
#include "GameAssets.h"
#include "GameEnums.h"
//Include our Game Application Classes
//#include <GamePCH.h>

namespace LJMU
{

	///////////////////////////////
	// Implementation of a Main Menu Screen.
	//
	// AUTHOR:  DR CHRIS CARTER
	///////////////////////////////
	class GameScreenOptions : public sf::ILJMUScreenBase
	{
		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		GameScreenOptions();	//Default Constructor
		~GameScreenOptions();	//Default Destructor

	public:
		//-----------FUNCTION OVERRIDES/INTERFACE IMPLEMENTATION-------------
		virtual void    loadContent() override;
		virtual void	handleEvent(const sf::Event& pevent) override;
		virtual void    bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered = false) override;
		virtual void	update(sf::Time& ptpf, sf::Time& ptotal) override;
		virtual void	render() override;
		virtual void    cleanup() override;

		//-----------PROTECTED FUNCTIONS-------------------------------------
	protected:
		void handleInput(sf::Keyboard::Key pkey, bool ppressed); //Handle Keyboard Events

		//Sub-Routines
		void loadResources();
		void setupMenuBG();
		void setupMenuElements();

		//Event Handling
		void onMoveUp();
		void onMoveDown();
		void onIncrement();
		void onDecrement();
		void onSelect();
		void onCancel();

	protected:
		//-----------CLASS MEMBERS-------------------------------------------
	sf::LJMUResourceHelper<sf::Texture,std::string>   _res_level;		//Resource Manager for Level BG
		sf::LJMUResourceHelper<sf::Texture,std::string>   _res_static;	    //Resource Manager for Static Sprites
		sf::LJMUResourceHelper<sf::Font, LJMU::Fonts>	  _res_font;        //Resource Manager for Fonts

		//Gameplay Elements
		std::vector<LJMU::GameObjectBasic>		_bg_layers;			//Level Collection
		std::vector<LJMU::GameObjectBasic>      _menu_sprites;		//Menu Sprites
		std::vector<LJMU::GameHUDElemBasic>		_menu_elems;		//Menu Collection

		

 
		std::vector<std::string>                _option_difficulty;  
		int										_selected_index;
		int										_selected_option;
		int										_selected_difficulty;
		sf::Color								_clr_curr;
		sf::Color								_clr_other;
	};
}
#endif
