#include <GameObjectBasic.h>

void LJMU::GameObjectBasic::render(sf::RenderWindow & pwndw)
{
	pwndw.draw(this->getSpriteRO());
}
