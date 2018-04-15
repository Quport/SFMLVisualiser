#pragma once
#include <SFML/Graphics.hpp>
#include "descriptive_shape.h"

class DescCircle : public DescShape<sf::CircleShape> {
public:
	DescCircle();
	DescCircle(float radius, const sf::Font& font, unsigned int characterSize = 400, size_t pointCount = 90);
	
	////////// getters
	
	float getRadius() const;
	size_t getPointCount() const;
	sf::Vector2f getPoint(size_t index) const;
	
	////////// setters
	
	void setRadius(float radius);
	void setPointCount(size_t count);
	void setOutlineThickness(float thickness);
	
private:
	void setup(float radius, size_t pointCount); // setup default options
	
	float radius;
	const float default_radius = 10;
	const float default_out_thickness = 0;
	const size_t default_point_count = 90;
	const sf::Color default_out_color = sf::Color::Black;
	const sf::Color default_fill_color = sf::Color::Red;
};
