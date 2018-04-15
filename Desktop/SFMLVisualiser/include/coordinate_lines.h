#pragma once
#include <SFML/Graphics.hpp>
#include "line_shape.h"
#include "better_text.h"

class CordLines : public sf::Drawable {
public:
	CordLines(const sf::Font& font, const sf::RenderWindow& wind);
	
	void setHorizontalPartition(size_t part);
	void setVerticalPartition(size_t part);
	
private:
	size_t hor_part, ver_part;
	sf::Vector2i resol;
	
	LineShape hor_line, ver_line;
	
	mutable std::vector<BetterText> hor_nums, ver_nums;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	const sf::RenderWindow& wind;
	const sf::Font& font;
	
	const size_t default_hor_part = 7;
	const size_t default_ver_part = 5;
	const size_t default_thickness = 5;
	const size_t default_text_height = 15;
};
