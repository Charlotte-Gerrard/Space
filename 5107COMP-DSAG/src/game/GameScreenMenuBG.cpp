#include <GameScreenMenuBG.h>

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::LJMUGameScreenMenuBG::LJMUGameScreenMenuBG()
{
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::LJMUGameScreenMenuBG::~LJMUGameScreenMenuBG()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//Load the Content of the Level
//And assign two player controls. 
/////////////////////////////////////////
void LJMU::LJMUGameScreenMenuBG::loadContent()
{
	this->_popup = true;
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	this->_img_bg.loadFromFile("Assets/Backgrounds/menu_bg.png");
	this->_menu_bg.setTexture(this->_img_bg);

}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenuBG::handleEvent(const sf::Event& pevent)
{
	//Cache the passed event locally
	sf::Event tevent = pevent;
	
	//Switch Statement to decide between the different Event Types
	switch (tevent.type)
	{
		case sf::Event::KeyPressed:
		{
			this->handleInput(tevent.key.code, true);
			break;
		}
		case sf::Event::KeyReleased:
		{
			this->handleInput(tevent.key.code, false);
			break;
		}
	}
}

void LJMU::LJMUGameScreenMenuBG::masterUpdate(sf::Time & ptpf, sf::Time & ptotal, bool potherfocused, bool poverlaid)
{
	ILJMUScreenBase::masterUpdate(ptpf, ptotal, potherfocused, false);
}

//////////////////////////////////////////
//  Secondary update function. 
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenuBG::bgUpdate(sf::Time & ptpf, sf::Time & ptotal, bool pcovered)
{
	
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenuBG::update(sf::Time & ptpf, sf::Time & ptotal)
{
	//-------GET THE UPDATE TIMES------------------------------------
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();

	
	
	//--------DEBUG OUTPUT-----------------------------------------------------------
#ifdef _DEBUG
	//Monitor the lists by outputting the size to the console
	sf::err() << "Debug Information: " << std::endl;
#endif
}

//////////////////////////////////////////
//  Holds the rendering logic to draw 
//  the screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenuBG::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	//------RENDER THE GAMEPLAY LAYERS---------------------------------
	twndw.draw(this->_menu_bg);
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenuBG::cleanup()
{

}

//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

///////////////////////////////////////
// Helper function for easy keyboard 
// control.
///////////////////////////////////////
void LJMU::LJMUGameScreenMenuBG::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	//Get Access to the Window via the Weak Pointer. 
	auto ttotal = this->getLJMUSFMLManager().lock()->getTotalElapsedTime();
}