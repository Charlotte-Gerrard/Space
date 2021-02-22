#include "GameGrenade.h"

//-----------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------

/////////////////////////////////////////////
// Constructor for the Bullet Class. 
/////////////////////////////////////////////
LJMU::LJMUGrenade::LJMUGrenade(sf::Sprite psprite, sf::Vector2f pdir, sf::Vector2f pspawnpos, sf::Time pspawntime) :
	ILJMUObjectState(),
	Grenade(psprite),
	Direction(pdir),
	SpawnPos(pspawnpos),
	SpawnTime(pspawntime),
	Speed(static_cast<float>(DEF_SPEED)),
	LifeTime(0.0f),
	Alpha(DEF_ALPHA),
	explode(false),
	range(200),
	flash(false)
{
	this->Grenade.setPosition(pspawnpos);
	sf::Color tcolour = this->Grenade.getColor();
	tcolour.a = Alpha;
	this->Grenade.setColor(tcolour);
}

/////////////////////////////////////////////
// Destructor for the Bullet Classs
/////////////////////////////////////////////
LJMU::LJMUGrenade::~LJMUGrenade()
{

}

//------------PUBLIC METHODS---------------------------------------------------------

/////////////////////////////////////////////
// Update the Position of the Bullets. 
/////////////////////////////////////////////
void LJMU::LJMUGrenade::update(sf::Time& ptpf, sf::Time& ptotal)
{
	float ttpf = ptpf.asSeconds();
	this->LifeTime += ttpf;
	if (this->Updatable)
		if (this->LifeTime < 0.8f)
		{
			explode = false;
			this->Grenade.move(this->Direction * this->Speed * ttpf);
			pos = this->Grenade.getPosition();
		}
		else if ((this->LifeTime > 0.8f) && (this->LifeTime < 2.0f))
		{
			explode = true;
			if (flash == true)
				this->Grenade.setColor(sf::Color(255, 0, 0));
			else
				this->Grenade.setColor(sf::Color(255, 255, 255));

			flash = !flash;
		}
		else
		{
			explode = false;
			this->Collidable = false;
			this->Visible = false;
			this->Updatable = false;
		}
}
