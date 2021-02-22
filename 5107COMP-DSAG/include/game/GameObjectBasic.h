#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace LJMU
{
	class GameObjectBasic
	{
	public:
		//----------CONSTRUCTOR/DESTRUCTOR---------------------------------
		explicit GameObjectBasic() :_name(), _sprite(),_layer(0){};
		virtual ~GameObjectBasic() {};

	public:
		//----------GETTERS/SETTERS----------------------------------------
		inline sf::Sprite& getSprite() { return this->_sprite; };
		inline const sf::Sprite& getSpriteRO() { return this->_sprite; };
		inline sf::Sprite  getSpriteCopy() { return this->_sprite; }
		
		inline void setSprite(sf::Sprite psprite) { this->_sprite = psprite; }
		
		inline std::string getName() { return this->_name; }
		inline void setName(std::string pname) { this->_name = pname; }
		inline int getLayer() { return this->_layer;  }
		inline void setLayer(int player) { this->_layer = player; }

		//----------PUBLIC FUNCTIONS---------------------------------------
		void render(sf::RenderWindow& pwndw);

	protected:
		//----------MEMBER DATA---------------------------------------------
		std::string _name;
		sf::Sprite  _sprite;
		int			_layer; 
	};

}