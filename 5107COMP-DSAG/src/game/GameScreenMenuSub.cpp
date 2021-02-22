#include <corecrt_math.h>
#include <GameScreenMenuSub.h>
#include <GameScreenMain.h>
#include <GameScreenTest.h>

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::GameScreenMenuSub::GameScreenMenuSub()
{
	this->_trans_on_time = sf::seconds(2.0f);
	this->_trans_off_time = sf::seconds(2.0f);
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::GameScreenMenuSub::~GameScreenMenuSub()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//Load the Content of the Level
//And assign two player controls. 
/////////////////////////////////////////
void LJMU::GameScreenMenuSub::loadContent()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	this->_img_start.loadFromFile("Assets/Statics/mi_start.png");
	this->_text_start.setTexture(this->_img_start);
	this->_pos_start = sf::Vector2f(600, 600);
	this->_text_start.setPosition(this->_pos_start);
	this->_text_start.setScale(1.25f, 1.25f);


}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::GameScreenMenuSub::handleEvent(const sf::Event& pevent)
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
void LJMU::GameScreenMenuSub::bgUpdate(sf::Time & ptpf, sf::Time & ptotal, bool pcovered)
{
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();

	sf::Color tcolour = this->_text_start.getColor();
	tcolour.a = static_cast<sf::Uint8>(this->getTransAlpha() * 255.0f);
	this->_text_start.setColor(tcolour);

	float tpow = powf(this->_trans_pos, 2);
	int   trate = this->_trans_mode == sf::TransMode::TransOn ? -128 : 256;
	float tx = trate * tpow;
	sf::Vector2f tnewpos = this->_pos_start + sf::Vector2f(tx, 0);
	this->_text_start.setPosition(tnewpos);
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::GameScreenMenuSub::update(sf::Time & ptpf, sf::Time & ptotal)
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
void LJMU::GameScreenMenuSub::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	//------RENDER THE GAMEPLAY LAYERS---------------------------------
	twndw.draw(this->_text_start);		
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::GameScreenMenuSub::cleanup()
{

}

//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

///////////////////////////////////////
// Helper function for easy keyboard 
// control.
///////////////////////////////////////
void LJMU::GameScreenMenuSub::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	//Get Access to the Window via the Weak Pointer. 
	auto ttotal = this->getLJMUSFMLManager().lock()->getTotalElapsedTime();
	if (pkey == sf::Keyboard::Key::Return && !ppressed)
	{
		this->getLJMUSFMLManager().lock()->addScreen(std::shared_ptr<ILJMUScreenBase>(new LJMUGameScreenMain()), 5);
	}
	else if (pkey == sf::Keyboard::Key::Escape && !ppressed)
	{
		this->exitScreen();
	}

}