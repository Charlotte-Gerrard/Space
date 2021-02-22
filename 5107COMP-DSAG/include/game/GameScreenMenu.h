#ifndef __GAME_SCREEN_MENU_H_
#define __GAME_SCREEN_MENU_H_

//Include our Framework Library
#include <LJMUPCH.h>
#include <GameAssets.h>
#include <GameControls.h>
#include "GameScreenMenuSub.h"
#include "GameScreenOptions.h"

namespace LJMU
{
	///////////////////////////////
	// Implementation of the main
	// gameplay screen using our
	// Screen Interface Class. 
	//
	// AUTHOR:  DR CHRIS CARTER
	///////////////////////////////
	class LJMUGameScreenMenu : public sf::ILJMUScreenBase
	{
		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		LJMUGameScreenMenu();	//Default Constructor
		~LJMUGameScreenMenu();	//Default Destructor

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

	protected:
		//-----------PROTECTED DATA------------------------------------------
		sf::Texture _img_root;
		sf::Texture _img_root_title;
		sf::Texture _back;
		sf::Sprite _text_root;
		sf::Sprite _logo;
		sf::Sprite _backg;
		sf::Vector2f _pos_root;
		sf::Vector2f _pos_title;
	};
}
#endif