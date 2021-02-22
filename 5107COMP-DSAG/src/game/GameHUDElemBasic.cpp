#include <GameHUDElemBasic.h>

void LJMU::GameHUDElemBasic::render(sf::RenderWindow & pwndw)
{
	pwndw.draw(this->getTextRO());
}
