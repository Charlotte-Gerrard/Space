#include <GameScreenMain.h>
#include<GameScreenMenuPause.h>
#include <GameEnums.h>

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::LJMUGameScreenMain::LJMUGameScreenMain()
{
	//Nothing Dynamic to initialise
	coolDown = 0;
	weapon = 1;
}
LJMU::LJMUGameScreenMain::LJMUGameScreenMain(int diff)
{
	//Nothing Dynamic to initialise 

	diffuclty = diff;
	coolDown = 0;
	waveCoolDown = 0;
	weapon = 1;
	immune = 0;

	switch (this->diffuclty)
	{
	case 0:
		waveTime = 65;
		break;
	case 1:
		waveTime = 55;
		break;
	case 2:
		waveTime = 40;
		break;
	}
	//alienGap = 250 / diffuclty;
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::LJMUGameScreenMain::~LJMUGameScreenMain()
{
	//Nothing Dynamic to Destruct. 

}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//Load the Content of the Level
//And assign two player controls. 
/////////////////////////////////////////
void LJMU::LJMUGameScreenMain::loadContent()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	this->_game_world.create(sf::tof(twndw.getSize()));
	this->setupPlayer();
	this->setupAliens();
	this->setupPickup();
}

//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::handleEvent(const sf::Event& pevent)
{
	//Cache the passed event locally
	sf::Event tevent = pevent;

	//Switch Statement to decide between the different Event Types
	switch (tevent.type)
	{
	case sf::Event::KeyPressed:
	{
		if (this->_game_world.GameMode == LJMUGamePlayMode::GAME_PLAYING)
		{
			this->handleInput(tevent.key.code, true);
		}
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
void LJMU::LJMUGameScreenMain::bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered)
{
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::update(sf::Time& ptpf, sf::Time& ptotal)
{

	//-------GET THE UPDATE TIMES------------------------------------
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();

	//-------ONLY UPDATE THE FULL STATE IN A GAMEPLAY SITUATION------
	if (this->_game_world.GameMode > LJMUGamePlayMode::GAME_PLAYING)
	{
		//Call update on our Game World Object
		this->_game_world.update(ptpf, ptotal);
		return;
	}

	//-------UPDATE THE ALIENS---------------------------------------
	//Update the Enemies
	unsigned int tenemycount = 0;
	for (auto& te : this->_list_alien)
	{
		//If it is still updatable, it is still alive!
		if (te.Updatable)
		{
			te.update(ptpf, ptotal);
			tenemycount++;
		}
	}

	//-------UPDATE THE PLAYER---------------------------------------
		
		if (this->_player->Updatable)
			this->_player->update(ptpf, ptotal);

		if (static_cast<unsigned int>(this->_player->Lives) < this->_game_world.GameLives)
			this->_game_world.GameLives = static_cast<unsigned int>(this->_player->Lives); //this updates the HUD too.

		coolDown--;

	
	//-------UPDATE THE BULLETS--------------------------------------
	//Update the Player's Bullets
	for (auto& tpb : this->_list_bullets)
	{
		if (tpb.Updatable)
			tpb.update(ptpf, ptotal);
	}
	for (auto& tpb : this->_list_bullets)
	{
		if (tpb.Bullet.getPosition().x >= 1600 || tpb.Bullet.getPosition().y <= 0 || tpb.Bullet.getPosition().y >= 900)
		{
			tpb.Collidable = false;
			tpb.Visible = false;
			tpb.Updatable = false;
		}
	}
	///---------update GRENADES
	for (auto& tpG : this->_list_grenades)
	{
		if (tpG.Updatable)
		{
			tpG.update(ptpf, ptotal);

		}
	}
	//----- UPDATE PICKUPS
	for (auto& tpi : this->_list_pickup)
	{
		if (tpi.Updatable)
		{
			tpi.update(ptpf, ptotal);
		}
	}
	//--------------------COLLISION DETECTION AND RESPONSE-----------------------------
	///------------PLAYER & ALIEN-------------
	auto& tp = *this->_player;
	for (auto& te : this->_list_alien)
	{
			bool tcc = te.Collidable && tp.Collidable;
			if (tcc && te.Enemy.getGlobalBounds().intersects(tp.Player.getGlobalBounds()))
			{
				te.Collidable = false;
				te.Updatable = false;
				te.Visible = false;
				
				if (this->immune <= 0)
				{
					this->_game_world.reduceLives();
				}
				else
				{
					this->immune--;
					if (this->immune == 0)
						this->_game_world.setImmune();
				}
			}
		
	}
	///------------PLAYER & PICKUPS

	for (auto& tpi : this->_list_pickup)
	{
		bool tcc = tpi.Collidable && tp.Collidable;
		if (tcc && tpi.pickUp.getGlobalBounds().intersects(tp.Player.getGlobalBounds()))
		{
			switch (tpi.type)
			{
			case LJMUPickupType::HEALTH :
					this->_game_world.increaseLives();
					break;
			case LJMUPickupType::SHIELD:
				this->immune = 3;
				this->_game_world.setImmune();
				break;
			}
			tpi.Collidable = false;
			tpi.Updatable = false;
			tpi.Visible = false;
		}
	}

	//------------ALIEN & WEAPON----------------------
	for (auto& tpb : this->_list_bullets)
	{
		for (auto& te : this->_list_alien)
		{
			bool tcc = te.Collidable && tpb.Collidable;
			if (tcc && te.Enemy.getGlobalBounds().intersects(tpb.Bullet.getGlobalBounds()))
			{
				//Set the State of the Enemy
				tpb.Collidable = false;
				tpb.Visible = false;
				tpb.Updatable = false;

				te.Collidable = false;
				te.Updatable = false;
				te.Visible = false;
				int teval = te.score;
				this->_game_world.increaseScore(teval);
			}
		}
	}
	for (auto& tpb : this->_list_grenades)
	{
		for (auto& te : this->_list_alien)
		{
			if (tpb.explode == true && te.Collidable)
			{
				sf::Vector2f currentPosition = tpb.pos; //npc position
				sf::Vector2f vector = te.Enemy.getPosition() - currentPosition;
				float distance = sqrt(vector.x * vector.x + vector.y * vector.y);
				if (distance < tpb.range)
				{
					te.Collidable = false;
					te.Updatable = false;
					te.Visible = false;
					int teval = te.score;
					this->_game_world.increaseScore(teval);
				}
			}
		}
	}
	
	if ((this->_game_world.tdisptime % this->waveTime == 0) && (this->_game_world.tdisptime >10))
	{
		if (this->waveCoolDown <= 0)
		{
			this->_list_alien.clear();
			this->_list_pickup.clear();
			this->_list_bullets.clear();
			this->_list_grenades.clear();
			this->setupAliens();
			this->setupPickup();
 			this->_game_world.GameWave++;
			 this->waveCoolDown = 100;
		}
		else
			this->waveCoolDown -= 1;
	}

	//----------GAME WORLD CONTROL LOGIC------------------------------------------------
	//Calculate the Winning and Losing Condition.
	bool tloss = this->_game_world.GameLives <= 0U;
	bool twin = tenemycount <= 0U;

	//Change our Gameplay State based on these conditions
	if (twin)
	{
		this->_game_world.GameMode = LJMUGamePlayMode::GAME_WON;
		//this->exitScreen();
		this->_game_world.GameEndTimeStart = ttotal;
	}

	//Call update on our Game World Object - this currently processes the changes in game mode 
	//Can we use the screen manager instead?
	this->_game_world.update(ptpf, ptotal);
	int lives = this->_game_world.returnLives();
	if (this->_game_world.GameLives <= 0 || this->_game_world.GamePlayTime >= 200)
	{
		this->cleanup();
		this->exitScreen();
	}

	//---------------------CLEAN UP THE REDUNDANT RESOURCES----------------------------


	//--------DEBUG OUTPUT-----------------------------------------------------------
#ifdef _DEBUG
	//Monitor the lists by outputting the size to the console
	//sf::err() << "No Aliens: " << this->_list_aliens.size() << std::endl;
	//sf::err() << "No P.Bullets: " << this->_list_bullets.size() << std::endl;
	//sf::err() << "No E.Bullets: " << this->_list_enemy_bullets.size() << std::endl;
#endif

}

//////////////////////////////////////////
//  Holds the rendering logic to draw 
//  the screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::render()
{
	//Get Access to the Window via the Weak Pointer. 
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	//------RENDER THE GAMEPLAY LAYERS---------------------------------

	//Setup the Camera
	twndw.setView(this->_game_world.CameraGame);

	//Draw the Level
	for (auto& tbg : this->_game_world.WorldLevel)
	{
		twndw.draw(tbg);
	}
	for (auto& te : this->_list_alien)
	{
		if (te.Visible)
			twndw.draw(te.Enemy);
	}
	if (this->_player->Visible)
			twndw.draw(this->_player->Player);
	
	//Draw the Player Bullets
	for (auto& tb : this->_list_bullets)
	{
		if (tb.Visible)
			twndw.draw(tb.Bullet);
	}
	for (auto& tg : this->_list_grenades)
	{
		if (tg.Visible)
			twndw.draw(tg.Grenade);
	}
	for (auto& tpi : this->_list_pickup)
	{
		if(tpi.Visible)
		twndw.draw(tpi.pickUp);
	}

	//----------RENDER THE 2D HUD USING A SECOND CAMERA--------------
	twndw.setView(this->_game_world.CameraHUD);

	for (auto& tt : this->_game_world.WorldHUD)
		twndw.draw(tt.second);
}

///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::cleanup()
{
	this->_list_alien.clear();
	this->_list_bullets.clear();
	this->_list_grenades.clear();
	this->_game_world.destroy();
}


//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

void LJMU::LJMUGameScreenMain::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	int index = 0;
	//Get Access to the Window via the Weak Pointer. 
	auto ttotal = this->getLJMUSFMLManager().lock()->getTotalElapsedTime();

	auto& tp = *this->_player;

	tp.Controls.setFlag(pkey, ppressed);

		if (tp.Controls.getKey(LJMUPlayerActions::ANIM_INC_FRAME) == pkey && ppressed)
			tp.Player.incrementFrame(ttotal, false);
		else if (tp.Controls.getKey(LJMUPlayerActions::ANIM_DEC_FRAME) == pkey && ppressed)
			tp.Player.decrementFrame(ttotal, false);

		if (tp.Controls.getKey(LJMUPlayerActions::SINGLE_BULLET) == pkey && ppressed)
		{
			weapon = 1;
		}
		if (tp.Controls.getKey(LJMUPlayerActions::FIRE_MULTI_BULLET) == pkey && ppressed)
		{
			weapon = 2;
		}
		if (tp.Controls.getKey(LJMUPlayerActions::GRANADE) == pkey && ppressed)
		{
			weapon = 3;
		}
		if (tp.Controls.getKey(LJMUPlayerActions::WAVE_BULLET) == pkey && ppressed)
		{
			weapon = 4;
		}
		if (tp.Controls.getKey(LJMUPlayerActions::FIRE_BULLET) == pkey && ppressed && (coolDown <=0))
		{
			this->fire(index);
			coolDown = 50;
		}
		if (tp.Controls.getKey(LJMUPlayerActions::PAUSE) == pkey && ppressed)
		{
			this->getLJMUSFMLManager().lock()->addScreen(std::shared_ptr<ILJMUScreenBase>(new LJMUGameScreenMenuPause()), 4);
		}
		index++;
	this->_game_world.CameraControl.setFlag(pkey, ppressed);

	// Pause screen 

	/*if (pkey == sf::Keyboard::Key::Escape && !ppressed)
	{
		this->getLJMUSFMLManager().lock()->addScreen(std::shared_ptr<ILJMUScreenBase>(new LJMUGameScreenMenuPause()), 6);
	} */
}


void LJMU::LJMUGameScreenMain::fireBullet(int pindex, sf::Vector2f pdir, BulletColour col, LJMU::BulletMotion mo)
{
	sf::Sprite tbullet;
	tbullet.setTexture(this->_game_world.ResourceSprites.get(LJMUSIAssets::BULLET));
	tbullet.setScale(sf::Vector2f(1.0f, 1.0f));
	
	if(col == BulletColour::WHITE)
	tbullet.setColor(sf::Color(255, 255, 255));
	else if (col == BulletColour::GREEN)
		tbullet.setColor(sf::Color(50, 255, 50));
	else 
		tbullet.setColor(sf::Color(255, 0, 0));
	sf::setOriginCentre(tbullet);
	sf::Vector2f tpos(this->_player->Player.getPosition());
	sf::Vector2f toffset(tbullet.getLocalBounds().width, 0);
	sf::Vector2f tdir = pdir;

	LJMUBullet tbulletobj(tbullet, tdir, tpos + toffset, this->_manager.lock()->getTotalElapsedTime(), mo);
	this->_list_bullets.push_back(tbulletobj);
}
void LJMU::LJMUGameScreenMain::fireGrenade(int pindex, sf::Vector2f pdir)
{
	sf::Sprite tgrenade;
	tgrenade.setTexture(this->_game_world.ResourceSprites.get(LJMUSIAssets::GRENADE));
	tgrenade.setScale(sf::Vector2f(1.5f, 1.5f));
	tgrenade.setColor(sf::Color(255, 255, 255));
	sf::setOriginCentre(tgrenade);
	sf::Vector2f tpos(this->_player->Player.getPosition());
	sf::Vector2f toffset(tgrenade.getLocalBounds().width, 0);
	sf::Vector2f tdir = pdir;

	LJMUGrenade tgranobj(tgrenade, tdir, tpos + toffset, this->_manager.lock()->getTotalElapsedTime());
	this->_list_grenades.push_back(tgranobj);
}
void LJMU::LJMUGameScreenMain::fire(int pindex)
{
	switch (weapon)
	{
	case 1:
	this->fireBullet(pindex, sf::Vector2f(1, 0), BulletColour::WHITE);
	break;
	case 2:
		this->fireBullet(pindex, sf::Vector2f(1, -0.5f), BulletColour::RED);
		this->fireBullet(pindex, sf::Vector2f(1, 0),BulletColour::RED);
		this->fireBullet(pindex, sf::Vector2f(1, 0.5f),BulletColour::RED);
		break;
	case 3:
		this->fireGrenade(pindex, sf::Vector2f(1, 0));
		break;
	case 4:
		this->fireBullet(pindex, sf::Vector2f(1, 0), BulletColour::GREEN, BulletMotion::SINUSOIDAL);

		break;
	}
}
/////////////////////////////////////////////////////////
// Setup the Player Sprites
/////////////////////////////////////////////////////////
void LJMU::LJMUGameScreenMain::setupPlayer()
{
	//Setup the Animated Sprite and the Animation Sequence Objects
	sf::LJMUAnimSprite tplayer;
	sf::LJMUAnimSeq tanim;

	//Create the Sequence
	tanim.setSpriteSheet(this->_game_world.ResourceSprites.get(LJMUSIAssets::PLAYER_ANIM));
	for (int i = 0; i < 2336; i += 292)
	{
		tanim.addFrame(sf::IntRect(i, 0, 292, 160));
	}

	//Define the Player Properties and Bind the Animation
	tplayer.setScale(sf::Vector2f(0.5f, 0.5f));
	tplayer.setAnimation(tanim);
	sf::setOriginCentre(tplayer);

	//Define the Spawn Position
	sf::Vector2f tpos(100, this->_game_world.GameWorldBounds.height / 2.0f);
	//Define the Primary Control Scheme
	LJMUPlayerControls tplyrctrl(true);

	//Setup the First Player Game Object
	this->_player = std::make_shared<LJMUPlayer>(tplayer, tplyrctrl, tpos);
	this->_player->IdleFrame = 3;
	this->_player->Player.setFrame(3);

	//Remove the Camera Controls.
	//this->_game_world.CameraControl.clearDefaults();
}

/////////////////////////////////////////////////////////
// Setup the Starting State of the Aliens
/////////////////////////////////////////////////////////
void LJMU::LJMUGameScreenMain::setupAliens()
{	int NO_ALIENS = 200;
	const sf::Vector2f tscreencentre = this->_game_world.GameWorldSize * 0.5f;

	//Manually Create the Animation sequence and add to the list
	sf::LJMUAnimSeq tanimtemplate;
	tanimtemplate.addFrame(sf::IntRect(0, 0, 128, 128));
	tanimtemplate.addFrame(sf::IntRect(128, 0, 128, 128));

	srand(time(NULL));
	//Use a Counter-Based loop to build the Alients
	for (int i = 0; i < NO_ALIENS; i++)
	{
		int randAnim = rand() % 3;
		//Create the Sprite for the Enemy
		sf::LJMUAnimSprite ta;
		sf::LJMUAnimSeq tanim = tanimtemplate;

		switch (randAnim)
		{
		case 0:
			tanim.setSpriteSheet(this->_game_world.ResourceSprites.get(LJMU::LJMUSIAssets::ALIEN_ONE_A));
			break;
		case 1:
			tanim.setSpriteSheet(this->_game_world.ResourceSprites.get(LJMU::LJMUSIAssets::ALIEN_TWO));
			break;
		case 2:
			tanim.setSpriteSheet(this->_game_world.ResourceSprites.get(LJMU::LJMUSIAssets::ALIEN_THREE));
			break;
		}
		ta.setAnimation(tanim);
		ta.setLooping(true);
		ta.setFrameTime(sf::seconds(1.0f));
		

		ta.setScale(sf::Vector2f(0.4f, 0.4f));
		ta.play();

		sf::setOriginCentre(ta);
		LJMUEnemy te(ta, sf::Vector2f(200.0f, 200.0f), sf::seconds(0));
		this->_list_alien.push_back(te);
	}
	float tstartime = this->_game_world.GameStartTime + 1.0f;
	sf::Vector2f tstartpos = sf::Vector2f(1500.0f, 100.0f);
	sf::Vector2f talienpos = tstartpos;

	//setup variables for randomised alien spawns.
	//srand(time(NULL));
	int randGroup = rand() % 3 + 1; //aliens can be in groups of 1, 2,3,4
	int randMovType = rand() % 4 + 1; //randomise 1 of the 4 movement types
	int randSpawnPos = rand() % 640; //randomise y spawn coordinate (0 - 900)

	int alienCount = 0;
	int loopStartAliens = 0;
	while (alienCount <= 100)
	{
		randMovType = rand() % 4 + 1;
		randGroup = rand() % 3 + 1;
		randSpawnPos = rand() % 640;
		talienpos.x += (200 / (this->diffuclty +1));
		talienpos.y += (randSpawnPos + 20);

		for (loopStartAliens; loopStartAliens < (alienCount + randGroup); loopStartAliens++)
		{
			auto& ta = this->_list_alien[loopStartAliens];
			ta.SpawnPos = sf::Vector2f(talienpos);
			ta.SpawnTime = sf::seconds(tstartime);

			if (randMovType == 1)
				ta.MotionType = LJMUEnemyMotion::CIRCULAR;
			else if (randMovType == 2)
				ta.MotionType = LJMUEnemyMotion::SINUSOIDAL;
			else if (randMovType == 3)
				ta.MotionType = LJMUEnemyMotion::LINEAR;
			else if (randMovType == 4)
				ta.MotionType = LJMUEnemyMotion::WAVE;

			talienpos.y += 60.0f;
			int value = rand() % 50;
			ta.score = value;
		}
		alienCount = loopStartAliens;
		talienpos.y = 0.0f;
	}
}

void LJMU::LJMUGameScreenMain::setupPickup()
{
	sf::LJMUAnimSeq tanimtemplate;
	tanimtemplate.addFrame(sf::IntRect(0, 0, 128, 128));
	tanimtemplate.addFrame(sf::IntRect(128, 0, 128, 128));
	srand(time(NULL));
	sf::Vector2f tstartpos = sf::Vector2f(3500.0f, 500.0f);
	int no_pickups;
	switch (this->diffuclty)
	{
	case 0:
		no_pickups = 6;
		break;
	case 1:
		no_pickups = 4;
		break;
	case 2: 
		no_pickups = 2;
		break;
	}
	float pick_gap = 20000 / no_pickups;
	for (int i = 0; i < no_pickups; i++)
	{
		int randType = rand() % 2 + 1;

		sf::LJMUAnimSprite ta;
		sf::LJMUAnimSeq tanim = tanimtemplate;
		LJMUPickupType type;
		switch (randType)
		{
		case 1:
			tanim.setSpriteSheet(this->_game_world.ResourceSprites.get(LJMU::LJMUSIAssets::HEALTH));
			type = LJMUPickupType::HEALTH;
			break;
		case 2:
			tanim.setSpriteSheet(this->_game_world.ResourceSprites.get(LJMU::LJMUSIAssets::SHIELD));
			type = LJMUPickupType::SHIELD;
			break;
		}

		ta.setAnimation(tanim);
		ta.setLooping(true);
		ta.setFrameTime(sf::seconds(1.0f));
		ta.setColor(sf::Color::White);

		ta.setScale(sf::Vector2f(0.5f, 0.5f));
		ta.play();

		sf::Vector2f tpickPos;
		int randSpawnPos = rand() % 640;
		tpickPos.x = tstartpos.x;
		tpickPos.y = randSpawnPos + 20;

	
		sf::setOriginCentre(ta);
		LJMUPickup te(ta, tpickPos, sf::seconds(0), type);
		this->_list_pickup.push_back(te);

		tstartpos.x += pick_gap;
	}

}