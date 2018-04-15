#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureHandler {
public:
	TextureHandler(const std::string& dir = "");

	sf::Texture* getTexture(const std::string &name);
	
private:
	std::string icon_directory;
	std::map<std::string, sf::Texture> mp;
};