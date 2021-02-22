#include "GameBullet.h"
#include <GameEnums.h>
//-----------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------

/////////////////////////////////////////////
// Constructor for the Bullet Class. 
/////////////////////////////////////////////
LJMU::LJMUBullet::LJMUBullet(sf::Sprite psprite,sf::Vector2f pdir, sf::Vector2f pspawnpos, sf::Time pspawntime, LJMU::BulletMotion pmotion):
ILJMUObjectState(),
Bullet(psprite),
Direction(pdir),
SpawnPos(pspawnpos),
SpawnTime(pspawntime),
Speed(static_cast<float>(DEF_SPEED)),
LifeTime(0.0f),
Motion(pmotion),
Alpha(DEF_ALPHA)
{
	this->Bullet.setPosition(pspawnpos);	
	sf::Color tcolour = this->Bullet.getColor();
	tcolour.a = Alpha;
	this->Bullet.setColor(tcolour);
}

/////////////////////////////////////////////
// Destructor for the Bullet Classs
/////////////////////////////////////////////
LJMU::LJMUBullet::~LJMUBullet()
{

}

//------------PUBLIC METHODS---------------------------------------------------------

/////////////////////////////////////////////
// Update the Position of the Bullets. 
/////////////////////////////////////////////
void LJMU::LJMUBullet::update(sf::Time& ptpf, sf::Time& ptotal)
{	
    float ttpf = ptpf.asSeconds();
	this->LifeTime += ttpf;
	sf::Vector2f tpos_at_t;
	if (this->Updatable)
	{
		switch (this->Motion)
		{
		case LJMU::BulletMotion::LINEAR:
    			this->Bullet.move(this->Direction * this->Speed * ttpf);
			break;

		case LJMU::BulletMotion::SINUSOIDAL:
			
 			float Parameter2 = 100.0f; //amplitude
			float Parameter3= 2.0f; //revoltions
			float Parameter4 = this->Speed; //speed
			float Parameter1= 2 * sf::LJMUTrig<float>::pi() * Parameter3; //Calculate Radians Per Second

			Parameter1 *= this->LifeTime; //Scale by Time
			Parameter4 *= this->LifeTime; //Scale by Time

			tpos_at_t.x = Parameter4;
			tpos_at_t.y = std::sinf(Parameter1) * Parameter2;

			//this->Bullet.setPosition(tpos_at_t);
			tpos_at_t += this->SpawnPos;
			this->Bullet.setPosition(tpos_at_t);
			break;
		}
	}
}