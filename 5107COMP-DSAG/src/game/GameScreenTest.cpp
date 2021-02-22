#include <GameScreenTest.h>
#include <GameScreenMenuPause.h>
#include <LJMUSettings.h>
#include <LJMUTrigonometry.h>
#include <GameScreenMain.h>
#include <GameScreenOptions.h>

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::GameScreenTest::GameScreenTest()
	:_selected_index(0),
	_selected_option(0)
{
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::GameScreenTest::~GameScreenTest()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//  Setup the Initial Content of the 
//  Level.
/////////////////////////////////////////
void LJMU::GameScreenTest::loadContent()
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
void LJMU::GameScreenTest::handleEvent(const sf::Event& pevent)
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
void LJMU::GameScreenTest::bgUpdate(sf::Time & ptpf, sf::Time & ptotal, bool pcovered)
{
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::GameScreenTest::update(sf::Time & ptpf, sf::Time & ptotal)
{
	//-------GET THE UPDATE TIMES----------------------------------------------------
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();

	//--------MENU TRANSFORMATION LOGIC--------------------------------------------

	std::string tchoice = this->_option_choices[this->_selected_option];
	this->_menu_elems[0].getText().setString("Weapon: " + tchoice);
	std::string tcurr = " ";

	//--------MENU GRAPHICAL UPDATE------------------------------------------------
	int i = 0;
	for (auto& telem : this->_menu_elems)
	{
		bool tselected = i == this->_selected_index;
		sf::Color& tclr = tselected ? this->_clr_curr : this->_clr_other;
		telem.getText().setFillColor(tclr);
		if (tselected)
		{
			float tscale = 1.25f + (sf::LJMUTrig<float>::sin(ttotal*180.0f) * 0.5f);
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
void LJMU::GameScreenTest::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();


	//------RENDER THE GAMEPLAY LAYERS---------------------------------

	//Draw the Background to Screen
	for (auto& tb : this->_bg_layers)
	{ tb.render(twndw); }
	//Draw the Level Elements
	for (auto& tms : this->_menu_sprites) { tms.render(twndw); }
	//Draw the Composite Elements
	for (auto& tmt : this->_menu_elems) { tmt.render(twndw); }

	//for (auto& twe : this->_weapon_sprites) { twe.render(twndw); }
	this->_weapon_sprites[this->_selected_option].render(twndw);
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::GameScreenTest::cleanup()
{

}

//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

///////////////////////////////////////
// Helper function for easy keyboard 
// control.
///////////////////////////////////////
void LJMU::GameScreenTest::handleInput(sf::Keyboard::Key pkey, bool ppressed)
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
void LJMU::GameScreenTest::loadResources()
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
	this->_res_level.load("background.png", tbg_dir + "background.png");
	this->_res_level.load("controls.png", tbg_dir + "controls.png");
	this->_res_level.load("single.png", tbg_dir + "single.png");
	this->_res_level.load("multi.png", tbg_dir + "multi.png");
	this->_res_level.load("grenade.png", tbg_dir + "grenade.png");
	this->_res_level.load("wave.png", tbg_dir + "wave.png");
}

///////////////////////////////////////////
// Load our Level Resources
///////////////////////////////////////////
void LJMU::GameScreenTest::setupMenuBG()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const sf::Vector2f tscrdim = sf::tof(twndw.getSize());

	//Setup our Background Layer
	LJMU::GameObjectBasic tbg;
	tbg.getSprite().setTexture(this->_res_level.get("background.png"));
	sf::makeFullScreen(tbg.getSprite(), tscrdim);
	this->_bg_layers.push_back(tbg);
	LJMU::GameObjectBasic tbg2;
	tbg2.getSprite().setTexture(this->_res_level.get("controls.png"));
	sf::makeFullScreen(tbg2.getSprite(), tscrdim);
	this->_bg_layers.push_back(tbg2);

	sf::Vector2f tpos(850, 300);
	LJMU::GameObjectBasic single;
	single.getSprite().setTexture(this->_res_level.get("single.png"));
	single.getSprite().setPosition(tpos);
	this->_weapon_sprites.push_back(single);

	LJMU::GameObjectBasic multi;
	multi.getSprite().setTexture(this->_res_level.get("multi.png"));
	multi.getSprite().setPosition(tpos);
	this->_weapon_sprites.push_back(multi);

	LJMU::GameObjectBasic grenade;
	grenade.getSprite().setTexture(this->_res_level.get("grenade.png"));
	grenade.getSprite().setPosition(tpos);
	this->_weapon_sprites.push_back(grenade);

	LJMU::GameObjectBasic wave;
	wave.getSprite().setTexture(this->_res_level.get("wave.png"));
	wave.getSprite().setPosition(tpos);
	this->_weapon_sprites.push_back(wave);

}

///////////////////////////////////////////
// Setup our Level Elements
///////////////////////////////////////////
void LJMU::GameScreenTest::setupMenuElements()
{
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	const sf::Vector2f tscrdim = sf::tof(twndw.getSize());

	//Construct Menu Data
	this->_option_choices = { "Single Bullet", "Triple Bullet", "Grenade", "Wave" };
	this->_clr_curr = sf::Color::Yellow;
	this->_clr_other = sf::Color::White;
	this->_selected_index = 0;
	this->_selected_option = 0;

	//Setup the Menu Items
	this->_menu_elems.resize(2);
	sf::Vector2f tpos(200, 100.0f);

	//Set the Font and Initial Position
	for (auto& the : this->_menu_elems)
	{
		the.getText().setFont(this->_res_font.get(Fonts::INFO));
		the.getText().setCharacterSize(40);
		the.getText().setPosition(tpos);
		tpos.y += 100.0f;
	}

	this->_menu_elems[0].getText().setString("Weapons");
	this->_menu_elems[1].getText().setString("Exit");
}

///////////////////////////////////////////
// Setup our Cameras
///////////////////////////////////////////

//-----------EVENT HANDLERS------------------------------------------

////////////////////////////////////////
// Handle Moving the Menu Item Down
////////////////////////////////////////
void LJMU::GameScreenTest::onMoveUp()
{
	this->_selected_index = (--this->_selected_index + this->_menu_elems.size()) % this->_menu_elems.size();
}

////////////////////////////////////////
// Handle Moving the Menu Item Up
////////////////////////////////////////
void LJMU::GameScreenTest::onMoveDown()
{
	this->_selected_index = (++this->_selected_index + this->_menu_elems.size()) % this->_menu_elems.size();
}

////////////////////////////////////////
// Handle Increment Events
////////////////////////////////////////
void LJMU::GameScreenTest::onIncrement()
{
	switch (this->_selected_index)
	{
	case 0:
		//Work out the Array Index
		this->_selected_option = ++this->_selected_option % this->_option_choices.size();
		break;
	default:
		break;
	}
}

////////////////////////////////////////
// Handle Decrement Events
////////////////////////////////////////
void LJMU::GameScreenTest::onDecrement()
{
	switch (this->_selected_index)
	{
	case 0:
		//Work out the Array Index
		this->_selected_option = --this->_selected_option % this->_option_choices.size();
		break;
	default:
		break;
	}
}

////////////////////////////////////////
// Handle Selection Events
////////////////////////////////////////
void LJMU::GameScreenTest::onSelect()
{
	auto tmngr = this->getLJMUSFMLManager().lock();

	switch (this->_selected_index)
	{
	case 0:
	{
		
	}
	break;
	case 1:
	{
		
		this->exitScreen();
	}
	break;
	default:
		break;
	}
}

////////////////////////////////////////
//  Handle Back Events
////////////////////////////////////////
void LJMU::GameScreenTest::onCancel()
{

}

