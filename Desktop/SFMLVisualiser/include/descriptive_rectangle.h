#pragma once
#include <SFML/Graphics.hpp>
#include "descriptive_shape.h"

class DescRect : public DescShape<sf::RectangleShape> {
public:
	DescRect();
	DescRect(const sf::Vector2f& size, const sf::Font& font, unsigned int characterSize = 400);
	
	////////// getters
	
	sf::Vector2f getSize() const;
	size_t getPointCount() const;
	sf::Vector2f getPoint(size_t index) const;
	
	////////// setters
	
	void setSize(const sf::Vector2f& size);
	void setSize(float width, float height);
	void setOutlineThickness(float thickness);

private:
	void setup(const sf::Vector2f& size); // setup default options
	
	sf::Vector2f size;
	const sf::Vector2f default_size = {20, 20};
	const float default_out_thickness = 0;
	const sf::Color default_out_color = sf::Color::Black;
	const sf::Color default_fill_color = sf::Color::Red;
};
