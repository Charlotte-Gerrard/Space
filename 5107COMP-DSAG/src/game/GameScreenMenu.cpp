#include <GameScreenMenu.h>

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::LJMUGameScreenMenu::LJMUGameScreenMenu()
{
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::LJMUGameScreenMenu::~LJMUGameScreenMenu()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//Load the Content of the Level
//And assign two player controls. 
/////////////////////////////////////////
void LJMU::LJMUGameScreenMenu::loadContent()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	//this->_game_world.GameWorldBounds.height / 2.0f

	this->_back.loadFromFile("Assets/Statics/opening.png");
	this->_backg.setTexture(this->_back);
	this->_backg.setScale(1.0f, 1.0f);
	this->_pos_root = sf::Vector2f(0, 0);
	this->_text_root.setPosition(this->_pos_root);


	this->_img_root.loadFromFile("Assets/Statics/logo.png");
	this->_logo.setTexture(this->_img_root);
	this->_logo.setScale(0.5f, 0.5f);
	sf::Vector2f pos(((this->getLJMUSFMLManager().lock()->getWindow().getSize().x / 2) - (_logo.getGlobalBounds().width /2)), (this->getLJMUSFMLManager().lock()->getWindow().getSize().y / 2 - (_logo.getGlobalBounds().height / 2)-100));
	this->_pos_root = pos;
	this->_logo.setPosition(this->_pos_root);

	this->_img_root_title.loadFromFile("Assets/Statics/title.png");
	this->_text_root.setTexture(this->_img_root_title);
	this->_text_root.setScale(1.25f, 1.25f);
	sf::Vector2f pos2(600-(_logo.getGlobalBounds().width / 2),600);
	this->_pos_root = pos2;
	this->_text_root.setPosition(this->_pos_root);

}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenu::handleEvent(const sf::Event& pevent)
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
void LJMU::LJMUGameScreenMenu::bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered)
{
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenu::update(sf::Time& ptpf, sf::Time& ptotal)
{
	//-------GET THE UPDATE TIMES------------------------------------
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();
	static float tstarttime = ttotal;

	if (ttotal - tstarttime > 5.0f)
	{
		this->getLJMUSFMLManager().lock()->addScreen(std::shared_ptr<ILJMUScreenBase>(new GameScreenOptions()), 2);
	}
}

//////////////////////////////////////////
//  Holds the rendering logic to draw 
//  the screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenu::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	//------RENDER THE GAMEPLAY LAYERS---------------------------------
	twndw.draw(this->_backg);
	twndw.draw(this->_text_root);
	twndw.draw(this->_logo);
	
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::LJMUGameScreenMenu::cleanup()
{
	//Clean up our Data Structures
}

//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

void LJMU::LJMUGameScreenMenu::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	int index = 0;
	//Get Access to the Window via the Weak Pointer. 
	auto ttotal = this->getLJMUSFMLManager().lock()->getTotalElapsedTime();
}