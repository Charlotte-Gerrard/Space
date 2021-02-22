#include "LJMUGameBase.h"
#include "GameScreenMain.h"
#include "GameScreenMenu.h"
#include <GameScreenMenuBG.h>
#include <GameScreenMenuPause.h>
#include <GameScreenMenuRoot.h>
#include <GameScreenMenuSub.h>
#include <GameScreenTest.h>

/////////////////////////////////////////
// Entry Point to our Application
// In this case it just needs to start
// our SFML Application.
//
// AUTHOR:  DR CHRIS CARTER
/////////////////////////////////////////
#ifdef _DEBUG
int main()
{
#else
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
#endif 
	try
	{
		//Construct our Game Instance as a Shared Pointer
		std::shared_ptr<sf::LJMUGameBase> tgame = std::make_shared<sf::LJMUGameBase>();	
		tgame->setupEngine();

		//Create our Initial Screen for the game.
		std::shared_ptr<sf::ILJMUScreenBase> tscreen(new LJMU::LJMUGameScreenMenuBG());
		tgame->addScreen(tscreen, 0);
		std::shared_ptr<sf::ILJMUScreenBase> tscreen2(new LJMU::LJMUGameScreenMenu());
		tgame->addScreen(tscreen2, 1);

		//Call Run on Our Game - when the game exits it will be cleaned up
		tgame->runGameLoop();
	}
	catch (std::runtime_error e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
		system("PAUSE");
	}
}

