#include "../include/descriptive_rectangle.h"
#include <iostream>
using namespace sf;
using namespace std;

DescRect::DescRect() {
	setup(default_size);
}

DescRect::DescRect(const Vector2f& _size, const Font& font, unsigned int characterSize) 
		: DescShape<RectangleShape>(font, characterSize) {
	setup(_size);
}

void DescRect::setup(const Vector2f& _size) {
	setOutlineThickness(default_out_thickness);
	setOutlineColor(default_out_color);
	setSize(_size);
	setFillColor(default_fill_color);
}

////////////////////////////////////////////////////////////////getters

Vector2f DescRect::getSize() const {
	return shape.getSize() + Vector2f(2 * getOutlineThickness(), 2 * getOutlineThickness());
}

size_t DescRect::getPointCount() const {
	return shape.getPointCount();
}

Vector2f DescRect::getPoint(size_t index) const {
	return shape.getPoint(index);
}

//////////////////////////////////////////////////////////////// setters

void DescRect::setSize(const Vector2f& _size) {
	shape.setSize({_size.x - 2 * getOutlineThickness(), _size.y - 2 * getOutlineThickness()});
	size = _size;
	fixTextBox();
}

void DescRect::setSize(float width, float height) {
	setSize({width, height});
}

void DescRect::setOutlineThickness(float thickness) {
	DescShape::setOutlineThickness(thickness);
	setSize(size);
}
