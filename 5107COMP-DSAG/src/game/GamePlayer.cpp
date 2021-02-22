#include "GamePlayer.h"

//--------------------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------------

/////////////////////////////////////////////
//
/////////////////////////////////////////////
LJMU::LJMUPlayer::LJMUPlayer(sf::LJMUAnimSprite psprite, LJMUPlayerControls pcontrols, sf::Vector2f pspawnpos)
:ILJMUObjectState(),
Player(psprite),
Controls(pcontrols),
SpawnPos(pspawnpos),
Direction(0.0f,0.0f),
Speed(static_cast<float>(DEF_SPEED)),
Lives(DEF_LIVES),
IdleFrame(0),
LastChange(sf::seconds(0))
{
	this->Player.setPosition(pspawnpos);
}

/////////////////////////////////////////////
//
/////////////////////////////////////////////
LJMU::LJMUPlayer::~LJMUPlayer()
{

}

//---------------------PUBLIC METHODS---------------------------------------------------------------

/////////////////////////////////////////////
// Update the Position of the Bullets. 
/////////////////////////////////////////////
void LJMU::LJMUPlayer::update(sf::Time& ptpf,sf::Time& ptotal)
{
	sf::Vector2f tvel(0, 0);
	if (this->Controls.isActive(LJMUPlayerActions::MOVE_UP))
		tvel.y -= 1.0f;
	if (this->Controls.isActive(LJMUPlayerActions::MOVE_RIGHT))
		tvel.x += 1.0f;
	if (this->Controls.isActive(LJMUPlayerActions::MOVE_LEFT))
		tvel.x -= 1.0f;
	if (this->Controls.isActive(LJMUPlayerActions::MOVE_DOWN))
		tvel.y += 1.0f;

	this->Direction = tvel;
	if (sf::squaredLength(this->Direction) > 0)
	{
		this->Direction = sf::unitVector(this->Direction);
	}

	this->Player.move(this->Direction * this->Speed * ptpf.asSeconds());

	//
	//Keep player ship in world bounds
	if (this->Player.getPosition().x > 1600)
	{
		tvel = sf::Vector2f(-1, 0);

		this->Direction = tvel;
		if (sf::squaredLength(this->Direction) > 0)
		{
			this->Direction = sf::unitVector(this->Direction);
		}

		this->Player.move(this->Direction * this->Speed * ptpf.asSeconds());
	}
	if (this->Player.getPosition().x < _game_world.GameWorldBounds.left)
	{
		tvel = sf::Vector2f(1, 0);

		this->Direction = tvel;
		if (sf::squaredLength(this->Direction) > 0)
		{
			this->Direction = sf::unitVector(this->Direction);
		}

		this->Player.move(this->Direction * this->Speed * ptpf.asSeconds());
	}
	if (this->Player.getPosition().y > 900)
	{
		tvel = sf::Vector2f(0, -1);

		this->Direction = tvel;
		if (sf::squaredLength(this->Direction) > 0)
		{
			this->Direction = sf::unitVector(this->Direction);
		}

		this->Player.move(this->Direction * this->Speed * ptpf.asSeconds());
	}
	if (this->Player.getPosition().y < _game_world.GameWorldBounds.top)
	{
		tvel = sf::Vector2f(0, 1);

		this->Direction = tvel;
		if (sf::squaredLength(this->Direction) > 0)
		{
			this->Direction = sf::unitVector(this->Direction);
		}

		this->Player.move(this->Direction * this->Speed * ptpf.asSeconds());
	}
	//
	//Animation Block
	this->LastChange += ptpf;
	if (this->LastChange > sf::seconds(0.05f))
	{
		if (this->Controls.isActive(LJMUPlayerActions::MOVE_UP))
		{
			this->Player.incrementFrame(ptotal, false);
			this->LastChange = sf::seconds(0);
		}
		else if (this->Controls.isActive(LJMUPlayerActions::MOVE_DOWN))
		{
			this->Player.decrementFrame(ptotal, false);
			this->LastChange = sf::seconds(0);
		}
		else
		{
			int tdiff = this->Player.getFrameNo() - this->IdleFrame;
			if (tdiff > 0)
			{
				this->Player.decrementFrame(ptotal, false);
				this->LastChange = sf::seconds(0);
			}
			else if (tdiff < 0)
			{
				this->Player.incrementFrame(ptotal, false);
				this->LastChange = sf::seconds(0);
			}
		}
	}
}