#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace LJMU
{
	////////////////////////////
	// Class to represent some 
	// In Game Text.
	////////////////////////////
	class GameHUDElemBasic
	{

	public:
		//--------CONSTRUCTORS/DESTRUCTORS---------------------------------
		explicit GameHUDElemBasic() : _name(), _text(), _layer(0) { }
		virtual ~GameHUDElemBasic() {};

		//----------GETTERS/SETTERS----------------------------------------
		inline sf::Text& getText() { return this->_text; };
		inline const sf::Text& getTextRO() { return this->_text; };
		inline sf::Text  getTextCopy() { return this->_text; }
		inline void setText(sf::Text psprite) { this->_text = psprite; }
		inline std::string getName() { return this->_name; }
		inline void setName(std::string pname) { this->_name = pname; }

		//----------PUBLIC FUNCTIONS---------------------------------------
		void render(sf::RenderWindow& pwndw);
		inline int getLayer() { return this->_layer; }
		inline void setLayer(int player) { this->_layer = player; }


	protected:
		//----------MEMBER DATA--------------------------------------------
		std::string _name;
		sf::Text    _text;
		int		    _layer;
	};

}