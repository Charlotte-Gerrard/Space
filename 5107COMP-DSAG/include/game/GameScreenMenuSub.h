#ifndef __GAME_SCREEN_MENU_SUB_H_
#define __GAME_SCREEN_MENU_SUB_H_

//Include our Framework Library
#include <LJMUPCH.h>
//Include our Game Application Classes


namespace LJMU
{
	///////////////////////////////
	// Implementation of the main
	// gameplay screen using our
	// Screen Interface Class. 
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    01/06/2017
	///////////////////////////////
	struct MenuSystem
	{
		int activeindex;
		int itemcount;
		MenuSystem()
		{
			activeindex = 0;
			itemcount = 0;
		}
	};
	class GameScreenMenuSub : public sf::ILJMUScreenBase
	{
		//---------CONSTANTS-------------------------------------------------------
		static const unsigned int   HUD_SCALE = 48;   //Constant to hold the scale of the HUD

		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		GameScreenMenuSub();	//Default Constructor
		~GameScreenMenuSub();	//Default Destructor

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
		//

	public:

		//-----------GETTERS/SETTERS-----------------------------------------

	protected:
		//-----------CLASS MEMBERS-------------------------------------------
		sf::Texture _img_start;
		sf::Sprite _text_start;
		sf::Vector2f _pos_start;

	
	};
}
#endif