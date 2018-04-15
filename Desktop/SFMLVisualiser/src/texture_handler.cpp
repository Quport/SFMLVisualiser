#include "../include/texture_handler.h"
#include <cassert>
#include <iostream>
using namespace sf;
using namespace std;

TextureHandler::TextureHandler(const string &dir) {
	icon_directory = dir;
}

Texture* TextureHandler::getTexture(const string &name) {
	if (mp.find(name) == mp.end())
		assert(mp[name].loadFromFile(icon_directory + '/' + name));
	return &mp[name];
}