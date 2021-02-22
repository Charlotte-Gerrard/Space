#include "GameManager.h"

using sf::LJMUSettings;

//--------------------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------------

/////////////////////////////////////////////
// Constructor for our Game State Class.
/////////////////////////////////////////////
LJMU::LJMUGameManager::LJMUGameManager(): 
GameWorldWindow(),
CameraGame(),
CameraHUD(),
CameraControl(),
ResourceSprites(),
ResourceFonts(),
GameWorldSize(),
GameWorldBounds(),
WorldLevel(),
WorldHUD(),
GamePlayTime(),
GameLives(),
GameScore(),
GameWave(),
GameMode()
{
	immune = false;
}

/////////////////////////////////////////////
// Destructor for our Game State class. 
/////////////////////////////////////////////
LJMU::LJMUGameManager::~LJMUGameManager()
{
	this->destroy();
}

//---------------------PUBLIC METHODS---------------------------------------------------------------

/////////////////////////////////////////////
// Create the Game State
/////////////////////////////////////////////
void LJMU::LJMUGameManager::create(sf::Vector2f pwndsize)
{
	//----------SETUP THE INITIAL GAME DATA---------------------------------------------------------
	this->GameScore = 0;
	this->GameWave = 1;
	this->GamePlayTime = 0.0f;
	this->GameStartTime = 3.0f;
	this->GameEndTimeStart = 0.0f;
	this->GameEndTimeDelay = 3.0f;
	this->GameLives = -1;
	this->GameWorldWindow = pwndsize;
	this->GameWorldSize = this->GameWorldWindow;
	this->GameWorldBounds = sf::fromdimf(this->GameWorldSize);
	this->GameMode = LJMUGamePlayMode::GAME_START;
	
	//----------SETUP UP THE GAME ASSETS----------------------------------------------------
	//Load the Default Font
	this->ResourceFonts.load(LJMUSIFont::SANSATION, LJMUSettings::DIR_FONTS + "Sansation.ttf");
	this->ResourceFonts.load(LJMUSIFont::RETRO, LJMUSettings::DIR_FONTS + "retrofont.ttf");

	//Load the Sprite Textures which are used in the game
	this->ResourceSprites.load(LJMUSIAssets::PLAYER_ANIM, LJMUSettings::DIR_ANIM + "player_anim.png");
	this->ResourceSprites.load(LJMUSIAssets::ALIEN_ONE_A, LJMUSettings::DIR_ANIM + "alien.png");
	this->ResourceSprites.load(LJMUSIAssets::ALIEN_TWO, LJMUSettings::DIR_ANIM + "alien_2.png");
	this->ResourceSprites.load(LJMUSIAssets::ALIEN_THREE, LJMUSettings::DIR_ANIM + "alien_3.png");
	this->ResourceSprites.load(LJMUSIAssets::BG_ONE, LJMUSettings::DIR_BG + "bg_3.png");
	this->ResourceSprites.load(LJMUSIAssets::BG_TWO, LJMUSettings::DIR_BG + "bg_4.png");
	this->ResourceSprites.load(LJMUSIAssets::BULLET, LJMUSettings::DIR_STATICS + "bullet.png");
	this->ResourceSprites.load(LJMUSIAssets::GRENADE, LJMUSettings::DIR_STATICS + "grenade.png");
	this->ResourceSprites.load(LJMUSIAssets::HEALTH, LJMUSettings::DIR_ANIM + "health.png");
	this->ResourceSprites.load(LJMUSIAssets::SHIELD, LJMUSettings::DIR_ANIM + "shield.png");
	//
	//this->ResourceColours.load(Colours::RED,sf::Color(255, 0, 0) )
	//this->ResourceColours[Colours::RED] = sf::Color(255, 0, 0);
	//this->ResourceColours[Colours::GREEN] = sf::Color(0, 255, 0);
	//this->ResourceColours[Colours::BLUE] = sf::Color(0, 0, 255);

	//this->MapEnemyColours[0] = Colours::RED;

	//----------CREATE THE GAME LEVEL---------------------------------------------------------

	//Populate our Level Background
	this->WorldLevel.push_back(sf::Sprite(this->ResourceSprites.get(LJMUSIAssets::BG_ONE)));
	this->WorldLevel.push_back(sf::Sprite(this->ResourceSprites.get(LJMUSIAssets::BG_TWO)));

	//Scale each Background to become Full Screen
	for (auto& tbg : this->WorldLevel)
	{
		sf::makeFullScreen(tbg, this->GameWorldSize);
	}
	
	//----------CREATE THE HUD----------------------------------------------------------------

	float txgap = (this->GameWorldBounds.width / 6.0f);
	float tsx = -40;
	float tty = 20;
	const int HUD_SCALE = 40;

	this->WorldHUD[LJMUSIHUD::LIVES] = sf::Text("", this->ResourceFonts.get(LJMUSIFont::RETRO), HUD_SCALE);
	this->WorldHUD[LJMUSIHUD::LIVES].setString("Lives : ");
	this->WorldHUD[LJMUSIHUD::LIVES].setPosition(tsx + txgap, tty);
	this->WorldHUD[LJMUSIHUD::LIVES].setFillColor(sf::Color::Green);

	this->WorldHUD[LJMUSIHUD::SCORE] = sf::Text("", this->ResourceFonts.get(LJMUSIFont::RETRO), HUD_SCALE);
	this->WorldHUD[LJMUSIHUD::SCORE].setString("Score : ");
	this->WorldHUD[LJMUSIHUD::SCORE].setPosition(tsx + txgap * 2, tty);
	this->WorldHUD[LJMUSIHUD::SCORE].setFillColor(sf::Color::Blue);

	this->WorldHUD[LJMUSIHUD::TIME] = sf::Text("", this->ResourceFonts.get(LJMUSIFont::RETRO), HUD_SCALE);
	this->WorldHUD[LJMUSIHUD::TIME].setString("Time : ");
	this->WorldHUD[LJMUSIHUD::TIME].setPosition(tsx + txgap * 3, tty);
	this->WorldHUD[LJMUSIHUD::TIME].setFillColor(sf::Color::Red);

	this->WorldHUD[LJMUSIHUD::WAVE] = sf::Text("", this->ResourceFonts.get(LJMUSIFont::RETRO), HUD_SCALE);
	this->WorldHUD[LJMUSIHUD::WAVE].setString("Wave : ");
	this->WorldHUD[LJMUSIHUD::WAVE].setPosition(tsx + txgap * 4, tty);
	this->WorldHUD[LJMUSIHUD::WAVE].setFillColor(sf::Color::Magenta);

	this->WorldHUD[LJMUSIHUD::IMMUNE] = sf::Text("", this->ResourceFonts.get(LJMUSIFont::RETRO), HUD_SCALE);
	this->WorldHUD[LJMUSIHUD::IMMUNE].setString("SHIELD");
	this->WorldHUD[LJMUSIHUD::IMMUNE].setPosition(tsx + txgap * 5, tty);
	this->WorldHUD[LJMUSIHUD::IMMUNE].setFillColor(sf::Color::Transparent);

	//-----------SETUP OUR GAME CAMERA--------------------------------------------------------
	//Setup our Game Camera
	sf::Vector2f tcamcentre = this->GameWorldSize * 0.5f;
	this->CameraGame.reset(this->GameWorldBounds);
	this->CameraGame.setCenter(tcamcentre);

	//Setup our HUD Camera
	this->CameraHUD.reset(this->GameWorldBounds);
	this->CameraHUD.setCenter(tcamcentre);
}

/////////////////////////////////////////////
// Update the Game State.
/////////////////////////////////////////////
void LJMU::LJMUGameManager::update(sf::Time& ptpf, sf::Time& ptotal)
{
	this->GamePlayTime += ptpf.asSeconds();
	float ttpf = ptpf.asSeconds();

	if (this->GameMode == LJMUGamePlayMode::GAME_START)
	{
		this->WorldHUD[LJMUSIHUD::SCORE].setString("");
		this->WorldHUD[LJMUSIHUD::LIVES].setString("GAME START");
		this->WorldHUD[LJMUSIHUD::TIME].setString("");
		this->WorldHUD[LJMUSIHUD::WAVE].setString("");

		if (this->GamePlayTime >= this->GameStartTime)
		{
			this->GameMode = LJMUGamePlayMode::GAME_PLAYING;
		}
	}
	else if (this->GameMode == LJMUGamePlayMode::GAME_PLAYING)
	{
		float tzoomfactor = 1;
		if (this->CameraControl.isActive(LJMUCameraActions::MOVE_CAM_LEFT))
			this->CameraGame.move(sf::Vector2f(-200.0f* ttpf, 0));
		if (this->CameraControl.isActive(LJMUCameraActions::MOVE_CAM_RIGHT))
			this->CameraGame.move(sf::Vector2f(200.0f* ttpf, 0));
		if (this->CameraControl.isActive(LJMUCameraActions::MOVE_CAM_UP))
			this->CameraGame.move(sf::Vector2f(0, -200.0f* ttpf));
		if (this->CameraControl.isActive(LJMUCameraActions::MOVE_CAM_DOWN))
			this->CameraGame.move(sf::Vector2f(0, 200.0f* ttpf));
		if (this->CameraControl.isActive(LJMUCameraActions::ROT_CAM_CCW))
			this->CameraGame.rotate(180.0f * ttpf);
		if (this->CameraControl.isActive(LJMUCameraActions::ROT_CAM_CW))
			this->CameraGame.rotate(-180.0f * ttpf);
		if (this->CameraControl.isActive(LJMUCameraActions::ZOOM_CAM_OUT))
			tzoomfactor -= 1.0f * ttpf;
		if (this->CameraControl.isActive(LJMUCameraActions::ZOOM_CAM_IN))
			tzoomfactor += 1.0f * ttpf;
		this->CameraGame.zoom(tzoomfactor);

		tdisptime = static_cast<int>(std::floor(this->GamePlayTime));
		this->WorldHUD[LJMUSIHUD::SCORE].setString("Score : " + std::to_string(this->GameScore));
		this->WorldHUD[LJMUSIHUD::LIVES].setString("Lives : " + std::to_string(this->GameLives));
		this->WorldHUD[LJMUSIHUD::TIME].setString("Time:  " + std::to_string(tdisptime));
		this->WorldHUD[LJMUSIHUD::WAVE].setString("Wave:  " + std::to_string(this->GameWave));
		//this->WorldHUD[LJMUSIHUD::WAVE].setString("SHIELD:  " + std::to_string(this->GameWave));
		if (this->GameLives == 1)
		{
			if (tdisptime % 2 == 0)
			{
				this->WorldHUD[LJMUSIHUD::LIVES].setFillColor(sf::Color::Yellow);
			}
			else
			{
				this->WorldHUD[LJMUSIHUD::LIVES].setFillColor(sf::Color::Red);
			}
		}
		if (this->bigScore() ==true)
		{
			if (tdisptime % 2 == 0)
			{
				this->WorldHUD[LJMUSIHUD::SCORE].setFillColor(sf::Color::White);
			}
			else
			{
				this->WorldHUD[LJMUSIHUD::SCORE].setFillColor(sf::Color::Green);
			}
		}
		else 
		{
			this->WorldHUD[LJMUSIHUD::SCORE].setFillColor(sf::Color::Blue);
		}

		if (this->immune == true)
		{
			if (tdisptime % 2 == 0)
			{
				this->WorldHUD[LJMUSIHUD::IMMUNE].setFillColor(sf::Color::White);
			}
			else
			{
				this->WorldHUD[LJMUSIHUD::IMMUNE].setFillColor(sf::Color::Yellow);
			}
		}
		else if (this->immune == false)
		{
			this->WorldHUD[LJMUSIHUD::IMMUNE].setFillColor(sf::Color::Transparent);
		}
	}
	//All statements below Should be done with the screen manager instead - creating a new screen.
	else if (this->GameMode == LJMUGamePlayMode::GAME_WON)
	{
		if (this->GamePlayTime > this->GameEndTimeStart + this->GameEndTimeDelay)
		{
			this->GameMode = LJMUGamePlayMode::GAME_END;
		}
	}

}
void LJMU::LJMUGameManager::reduceLives()
{
	this->GameLives = this->GameLives - 1;
}
void LJMU::LJMUGameManager::increaseLives()
{
	this->GameLives = this->GameLives + 1;
}
void LJMU::LJMUGameManager::increaseScore(int val)
{
	this->GameScore += val;
}
int LJMU::LJMUGameManager::returnLives()
{
	return this->GameLives;
}
/////////////////////////////////////////////
// Destroy the Game State.
/////////////////////////////////////////////
void LJMU::LJMUGameManager::destroy()
{
	//Cleanup our STL Containers
	this->WorldHUD.clear();
	this->WorldLevel.clear();
	this->ResourceFonts.clear();
	this->ResourceSprites.clear();
}
bool LJMU::LJMUGameManager::bigScore()
{
	if ((this->GameScore >= 500 && this->GameScore < 600) || (this->GameScore >= 1000 && this->GameScore < 1100) || (this->GameScore >= 2000 && this->GameScore < 2100))
		return true;

	else
		return false;
}

void LJMU::LJMUGameManager::setImmune()
{
	this->immune = !this->immune;
}
void LJMU::LJMUGameManager::nextWave()
{
	this->GameWave++;
}