#include "GamePickup.h"
#include <GameEnums.h>
//-----------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------

/////////////////////////////////////////////
// Constructor for the Bullet Class. 
/////////////////////////////////////////////
LJMU::LJMUPickup::LJMUPickup(sf::LJMUAnimSprite psprite, sf::Vector2f pspawnpos, sf::Time pspawntime, LJMUPickupType ptype) :
	ILJMUObjectState(),
	pickUp(psprite),
	SpawnPos(pspawnpos),
	SpawnTime(pspawntime),
	Speed(static_cast<float>(DEF_SPEED)),
	LifeTime(0.0f),
	Alpha(DEF_ALPHA),
	type(ptype)
{
	this->pickUp.setPosition(pspawnpos);
	
}
LJMU::LJMUPickup::LJMUPickup()
{

}

/////////////////////////////////////////////
// Destructor for the Bullet Classs
/////////////////////////////////////////////
LJMU::LJMUPickup::~LJMUPickup()
{

}

//------------PUBLIC METHODS---------------------------------------------------------

/////////////////////////////////////////////
// Update the Position of the Bullets. 
/////////////////////////////////////////////
void LJMU::LJMUPickup::update(sf::Time& ptpf, sf::Time& ptotal)
{
	float ttpf = ptpf.asSeconds();
	this->LifeTime += ttpf;
	if (this->Updatable)
	{
		this->pickUp.move(this->Direction * this->Speed * ttpf);
	}
	float Parameter1 = -200.0f; //Linear speed
	Parameter1 *= this->LifeTime;

	this->LifeTime += ttpf;
	sf::Vector2f tpos_at_t;
	tpos_at_t.x = Parameter1;
	tpos_at_t.y = tpos_at_t.y;

	tpos_at_t += this->SpawnPos;
	this->pickUp.setPosition(tpos_at_t);
	this->pickUp.update(ptpf);
}