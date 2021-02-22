#include <GameScreenOptions.h>
#include <GameScreenMenuPause.h>
#include <LJMUSettings.h>
#include <LJMUTrigonometry.h>
#include <GameScreenMain.h>
#include <GameScreenTest.h>

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::GameScreenOptions::GameScreenOptions()
	:_selected_index(0),
	_selected_option(0),
	_selected_difficulty(0)
{
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::GameScreenOptions::~GameScreenOptions()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//  Setup the Initial Content of the 
//  Level.
/////////////////////////////////////////
void LJMU::GameScreenOptions::loadContent()
{
	//Call our Sub-Routines - Some Order is Important
	this->loadResources();

	//Call our Setup Routines to Initialise the Menu
	this->setupMenuBG();
	this->setupMenuElements();

	//Setup our Cameras 
}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::GameScreenOptions::handleEvent(const sf::Event& pevent)
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
void LJMU::GameScreenOptions::bgUpdate(sf::Time & ptpf, sf::Time & ptotal, bool pcovered)
{
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::GameScreenOptions::update(sf::Time & ptpf, sf::Time & ptotal)
{
	//-------GET THE UPDATE TIMES----------------------------------------------------
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();

	//--------MENU TRANSFORMATION LOGIC--------------------------------------------


	std::string tchoice2 = this->_option_difficulty[this->_selected_difficulty];
	this->_menu_elems[1].getText().setString("Difficulty: " + tchoice2);
	std::string tcurr2 = " ";
	//tcurr += _option_choices[this->_selected_option];
	//this->_menu_elems[1].getText().setString(this->_menu_elems[1].getString() + tcurr);

	//--------MENU GRAPHICAL UPDATE------------------------------------------------
	int i = 0;
	for (auto& telem : this->_menu_elems)
	{
		bool tselected = i == this->_selected_index;
		sf::Color& tclr = tselected ? this->_clr_curr : this->_clr_other;
		telem.getText().setFillColor(tclr);
		if (tselected)
		{
			float tscale = 1.5f + (sf::LJMUTrig<float>::sin(ttotal*180.0f) * 0.5f);
			telem.getText().setScale(tscale, tscale);
		}
		else
		{
			float tscale = 1.0f;
			telem.getText().setScale(tscale, tscale);
		}
		i++;
	}

}

//////////////////////////////////////////
//  Holds the rendering logic to draw 
//  the screen.
//////////////////////////////////////////
void LJMU::GameScreenOptions::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();


	//------RENDER THE GAMEPLAY LAYERS---------------------------------

	//Draw the Background to Screen
	for (auto& tbg : this->_bg_layers) { tbg.render(twndw); }
	//Draw the Level Elements
	for (auto& tms : this->_menu_sprites) { tms.render(twndw); }
	//Draw the Composite Elements
	for (auto& tmt : this->_menu_elems) { tmt.render(twndw); }
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::GameScreenOptions::cleanup()
{

}

//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

///////////////////////////////////////
// Helper function for easy keyboard 
// control.
///////////////////////////////////////
void LJMU::GameScreenOptions::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	//Get Access to the Window via the Weak Pointer. 
	auto ttotal = this->getLJMUSFMLManager().lock()->getTotalElapsedTime();

	using kb = sf::Keyboard;
	using keys = sf::Keyboard::Key;
	if (!ppressed && pkey == keys::Up)
		this->onMoveUp();
	else if (!ppressed && pkey == keys::Down)
		this->onMoveDown();
	else if (!ppressed && pkey == keys::Right)
		this->onIncrement();
	else if (!ppressed && pkey == keys::Left)
		this->onDecrement();
	else if (!ppressed && pkey == keys::Enter)
		this->onSelect();
	else if (!ppressed && pkey == keys::Escape)
		this->onCancel();
}
//-------------LOGICAL SUB-ROUTINES---------------------------------------

///////////////////////////////////////////
// Load our External DCC Resources
///////////////////////////////////////////
void LJMU::GameScreenOptions::loadResources()
{
	//Load the Default Font
	std::string ts_dir = sf::LJMUSettings::DIR_STATICS;
	std::string tbg_dir = sf::LJMUSettings::DIR_BG;
	std::string tf_dir = sf::LJMUSettings::DIR_FONTS;

	using namespace LJMU;

	//Load the Fonts

	this->_res_font.load(Fonts::INFO, tf_dir + "Sansation.ttf");
	this->_res_font.load(Fonts::HUD, tf_dir + "ca.ttf");

	//Load the backgrounds
	this->_res_level.load("menu_bg", tbg_dir + "Background.png");

}

///////////////////////////////////////////
// Load our Level Resources
///////////////////////////////////////////
void LJMU::GameScreenOptions::setupMenuBG()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const sf::Vector2f tscrdim = sf::tof(twndw.getSize());

	//Setup our Background Layer
	LJMU::GameObjectBasic tbg;
	tbg.getSprite().setTexture(this->_res_level.get("menu_bg"));
	sf::makeFullScreen(tbg.getSprite(), tscrdim);
	this->_bg_layers.push_back(tbg);
}

///////////////////////////////////////////
// Setup our Level Elements
///////////////////////////////////////////
void LJMU::GameScreenOptions::setupMenuElements()
{
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const sf::Vector2f tscrdim = sf::tof(twndw.getSize());

	//Construct Menu Data
	this->_option_difficulty = { "Easy", "Medium", "Hard" };
	this->_clr_curr = sf::Color::Yellow;
	this->_clr_other = sf::Color::White;
	this->_selected_index = 0;
	this->_selected_option = 0;
	this->_selected_difficulty = 0;

	//Setup the Menu Items
	this->_menu_elems.resize(3);
	sf::Vector2f tpos(200, 300.0f);

	//Set the Font and Initial Position
	for (auto& the : this->_menu_elems)
	{
		the.getText().setFont(this->_res_font.get(Fonts::INFO));
		the.getText().setCharacterSize(50);
		the.getText().setPosition(tpos);
		tpos.y += 100.0f;
	}
	this->_menu_elems[0].getText().setString("Start Game");
	this->_menu_elems[1].getText().setString("Difficulty: ");
	this->_menu_elems[2].getText().setString("Controls");
}

///////////////////////////////////////////
// Setup our Cameras
///////////////////////////////////////////

//-----------EVENT HANDLERS------------------------------------------

////////////////////////////////////////
// Handle Moving the Menu Item Down
////////////////////////////////////////
void LJMU::GameScreenOptions::onMoveUp()
{
	this->_selected_index = (--this->_selected_index + this->_menu_elems.size()) % this->_menu_elems.size();
}

////////////////////////////////////////
// Handle Moving the Menu Item Up
////////////////////////////////////////
void LJMU::GameScreenOptions::onMoveDown()
{
	this->_selected_index = (++this->_selected_index + this->_menu_elems.size()) % this->_menu_elems.size();
}

////////////////////////////////////////
// Handle Increment Events
////////////////////////////////////////
void LJMU::GameScreenOptions::onIncrement()
{
	switch (this->_selected_index)
	{
	case 0:
		
		break;
	case 1:
		//Work out the Array Index
		this->_selected_difficulty = ++this->_selected_difficulty  % this->_option_difficulty.size();
		break;
	default:
		break;
	}
}

////////////////////////////////////////
// Handle Decrement Events
////////////////////////////////////////
void LJMU::GameScreenOptions::onDecrement()
{
	switch (this->_selected_index)
	{
	case 0:
		
		break;
	case 1:
		//Work out the Array Index
		this->_selected_difficulty = --this->_selected_difficulty  % this->_option_difficulty.size();
		break;
	case 2:

		break;
	default:
		break;
	}
}

////////////////////////////////////////
// Handle Selection Events
////////////////////////////////////////
void LJMU::GameScreenOptions::onSelect()
{
	auto tmngr = this->getLJMUSFMLManager().lock();

	switch (this->_selected_index)
	{
	case 0:
	{
		std::shared_ptr<sf::ILJMUScreenBase> tscreen(new LJMU::LJMUGameScreenMain( _selected_difficulty));
		tmngr->addScreen(tscreen, 1);
	}
	break;
	case 1:
	{


	}
	case 2:
	{
		//void LJMU::GameScreenTest::setOptions(_selected_difficulty, _selected_option);
		//this->exitScreen();
		this->getLJMUSFMLManager().lock()->addScreen(std::shared_ptr<ILJMUScreenBase>(new GameScreenTest()), 6);
	}
	break;
	default:
		break;
	}
}

////////////////////////////////////////
//  Handle Back Events
////////////////////////////////////////
void LJMU::GameScreenOptions::onCancel()
{

}