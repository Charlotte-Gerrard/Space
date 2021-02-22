#ifndef __GAME_SCREEN_MENUBG_H_
#define __GAME_SCREEN_MENUBG_H_

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
	class LJMUGameScreenMenuBG : public sf::ILJMUScreenBase
	{
		//---------CONSTANTS-------------------------------------------------------
		static const unsigned int   HUD_SCALE = 48;   //Constant to hold the scale of the HUD

		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		LJMUGameScreenMenuBG();	//Default Constructor
		~LJMUGameScreenMenuBG();	//Default Destructor

	public:
		//-----------FUNCTION OVERRIDES/INTERFACE IMPLEMENTATION-------------
		virtual void    loadContent() override;
		virtual void	handleEvent(const sf::Event& pevent) override;
		virtual void    masterUpdate(sf::Time& ptpf, sf::Time& ptotal, bool potherfocused, bool poverlaid);
		virtual void    bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered = false) override;
		virtual void	update(sf::Time& ptpf, sf::Time& ptotal) override;
		virtual void	render() override;
		virtual void    cleanup() override;

	public:
		//-----------PUBLIC FUNCTIONS----------------------------------------

		//-----------PROTECTED FUNCTIONS-------------------------------------
	protected:
		void handleInput(sf::Keyboard::Key pkey, bool ppressed); //Handle Keyboard Events


	public:

		//-----------GETTERS/SETTERS-----------------------------------------

	protected:
		//-----------CLASS MEMBERS-------------------------------------------
		sf::Texture _img_bg;
		sf::Sprite _menu_bg;
	};
}
#endif