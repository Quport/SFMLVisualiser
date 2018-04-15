#include "../include/coordinate_lines.h"
#include <iostream>
using namespace sf;
using namespace std;

CordLines::CordLines(const sf::Font& _font, const sf::RenderWindow& _wind) 
	: resol(_wind.getSize()), wind(_wind), font(_font) {
	hor_line.setPoint1(0, resol.y);
	hor_line.setPoint2(resol.x, resol.y);
	ver_line.setPoint1(resol.x, 0);
	ver_line.setPoint2(resol.x, resol.y);
}

DescCircle::DescCircle(float _radius, const Font& font, unsigned int characterSize, size_t pointCount) 
		: DescShape<CircleShape>(font, characterSize) {
	setup(_radius, pointCount);
}

void DescCircle::setup(float _radius, size_t pointCount) {
	setOutlineColor(default_out_color);
	setRadius(_radius);
	setPointCount(pointCount);
	setFillColor(default_fill_color);
	setOutlineThickness(default_out_thickness);
}

////////////////////////////////////////////////////////////////getters

float DescCircle::getRadius() const {
	return shape.getRadius() + 2 * getOutlineThickness();
}

size_t DescCircle::getPointCount() const {
	return shape.getPointCount();
}

Vector2f DescCircle::getPoint(size_t index) const {
	return shape.getPoint(index);
}

//////////////////////////////////////////////////////////////// setters

void DescCircle::setRadius(float _radius) {
	shape.setRadius(_radius - 2 * getOutlineThickness());
	radius = _radius;
	fixTextBox();
}

void DescCircle::setPointCount(size_t count) {
	shape.setPointCount(count);
}

void DescCircle::setOutlineThickness(float thickness) {
	DescShape::setOutlineThickness(thickness);
	setRadius(radius);
}
