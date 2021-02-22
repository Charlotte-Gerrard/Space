#include "GameEnemy.h"


//--------------------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------------

/////////////////////////////////////////////
// Constructor for our Enemy Class
/////////////////////////////////////////////
LJMU::LJMUEnemy::LJMUEnemy(sf::LJMUAnimSprite psprite, sf::Vector2f pspawnpos,sf::Time pspawntime):
ILJMUObjectState(),
Enemy(psprite),
SpawnPos(pspawnpos),
SpawnTime(pspawntime),
LifeTime(0.0f),
Parameter1(0.0f),
Parameter2(0.0f),
Parameter3(0.0f),
Parameter4(0.0f),
MotionType(LJMUEnemyMotion::CIRCULAR)
{
	this->Enemy.setPosition(pspawnpos);
	timer = 0;
	multiplier = 1;
	zigUp = true;
	spin = true;
}


/////////////////////////////////////////////
// Destructor for our Enemy Class
/////////////////////////////////////////////
LJMU::LJMUEnemy::~LJMUEnemy()
{

}

//---------------------PUBLIC METHODS---------------------------------------------------------------

/////////////////////////////////////////////
// Update the Enemy object represented by this class. 
/////////////////////////////////////////////
void LJMU::LJMUEnemy::update(sf::Time& ptpf,sf::Time& ptotal)
{
	const float ttpf = ptpf.asSeconds();

	//If we are not updatable, return 
	if (!this->Updatable)
		return; 

	//If we have not spawned, return 
	if (this->SpawnTime > ptotal)
		return;

	this->LifeTime += ttpf;
	sf::Vector2f tpos_at_t;

	if (this->MotionType == LJMUEnemyMotion::CIRCULAR)
	{
		this->Parameter2 = 300.0f; //The Radius of our circle
		this->Parameter3 = -0.3f;   //Revolutions Per Second
		this->Parameter4 = sf::LJMUTrig<float>::pi();
		this->Parameter1 = 2 * sf::LJMUTrig<float>::pi() * this->Parameter3; //Calculate Radians Per Second
		this->Parameter1 *= this->LifeTime; //Scale by Time
		this->Parameter1 += this->Parameter4;
		this->Parameter2 += 20 * ttpf;

		tpos_at_t.x = (std::cosf(this->Parameter1) * this->Parameter2) - 200 * this->LifeTime;
		tpos_at_t.y = std::sinf(this->Parameter1) * this->Parameter2;
	}
	else if (this->MotionType == LJMUEnemyMotion::SINUSOIDAL)
	{
		this->Parameter2 = 200.0f; //Amplitiude
		this->Parameter3 = -0.3f;   //Revolutions Per Second
		this->Parameter4 = -200.0f; //Speed of Linear Movement
		this->Parameter1 = 2 * sf::LJMUTrig<float>::pi() * this->Parameter3; //Calculate Radians Per Second
		this->Parameter1 *= this->LifeTime; //Scale by Time
		this->Parameter4 *= this->LifeTime; //Scale by Time

		tpos_at_t.x = this->Parameter4;
		tpos_at_t.y = std::sinf(this->Parameter1) * this->Parameter2;
	}
	else if (this->MotionType == LJMUEnemyMotion::LINEAR)
	{
		this->Parameter1 = -200.0f; //Linear speed
		this->Parameter1 *= this->LifeTime;

		tpos_at_t.x = this->Parameter1;
		tpos_at_t.y = tpos_at_t.y;
	}
	
	else if (this->MotionType == LJMUEnemyMotion::WAVE)
	{
		this->Parameter2 = 280.0f; //Amplitiude
		this->Parameter3 = -0.2f;   //Revolutions Per Second
		this->Parameter4 = -140.0f; //Speed of Linear Movement
		this->Parameter1 = 2 * sf::LJMUTrig<float>::pi() * this->Parameter3; //Calculate Radians Per Second
		this->Parameter1 *= this->LifeTime; //Scale by Time
		this->Parameter4 *= this->LifeTime; //Scale by Time

		tpos_at_t.x = (std::cosf(this->Parameter1) * this->Parameter2) + this->Parameter4;
		tpos_at_t.y = std::cosf(this->Parameter1) * this->Parameter2;

	}
	else if (this->MotionType == LJMUEnemyMotion::QUADRATIC)
	{
		this->Parameter4 = 0.005f;
		this->Parameter3 = 300;
		this->Parameter2 = 300;
		this->Parameter1 = -this->LifeTime * 300.0f;

		tpos_at_t.x = this->SpawnPos.x + this->Parameter1;
		tpos_at_t.y = this->Parameter4 * powf(tpos_at_t.x - this->Parameter3, 2) + this->Parameter2;
		tpos_at_t -= this->SpawnPos;
	}
	tpos_at_t += this->SpawnPos;
	this->Enemy.setPosition(tpos_at_t);

	//-------------------------------------------------------
	
	//Update the Sprite Sheet.
	this->Enemy.update(ptpf);
}