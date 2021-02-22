#include <GameScreenMenuPause.h>

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::LJMUGameScreenMenuPause::LJMUGameScreenMenuPause()
{
	this->_popup = true;
	this->_trans_on_time = sf::seconds(1.0f);
	this->_trans_off_time = sf::seconds(1.0f);
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::LJMUGameScreenMenuPause::~LJMUGameScreenMenuPause()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//Load the Content of the Level
//And assign two player controls. 
/////////////////////////////////////////
void LJMU::LJMUGameScreenMenuPause::loadContent()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	this->_img_pause.loadFromFile("Assets/Backgrounds/pause.png");
	this->_menu_pause.setTexture(this->_img_pause);
}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenuPause::handleEvent(const sf::Event& pevent)
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

//////////////////////////////////////////
//  Secondary update function. 
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenuPause::bgUpdate(sf::Time & ptpf, sf::Time & ptotal, bool pcovered)
{
	sf::Color tcolour = this->_menu_pause.getColor();
	tcolour.a = static_cast<sf::Uint8>(this->getTransAlpha() * 255.0f);
	this->_menu_pause.setColor(tcolour); 
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenuPause::update(sf::Time & ptpf, sf::Time & ptotal)
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
void LJMU::LJMUGameScreenMenuPause::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	//------RENDER THE GAMEPLAY LAYERS---------------------------------
	twndw.draw(this->_menu_pause);
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenuPause::cleanup()
{

}

void LJMU::LJMUGameScreenMenuPause::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	//Get Access to the Window via the Weak Pointer. 
	auto ttotal = this->getLJMUSFMLManager().lock()->getTotalElapsedTime();

	if (pkey == sf::Keyboard::Key::Return && !ppressed)
	{
		this->exitScreen();
		//this->getLJMUSFMLManager().lock()->addScreen(std::shared_ptr<ILJMUScreenBase>(new LJMUGameScreenMain()), 5);
	}
	if (pkey == sf::Keyboard::Key::Escape && !ppressed)
	{
		this->exitScreen();

	}
}