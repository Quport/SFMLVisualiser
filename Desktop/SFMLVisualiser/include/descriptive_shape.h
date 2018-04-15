#pragma once
#include <SFML/Graphics.hpp>
#include "legend.h"
#include "useful.h" // usunac

template<class ShapeClass>
class DescShape : public sf::Drawable {
public:
	DescShape();
	DescShape(const sf::Font& font, unsigned int characterSize = 400);
	
	////////// shape getters
	
	const sf::Vector2f& getPosition() const;
	
	const sf::Color& getFillColor() const;
	const sf::Color& getOutlineColor() const;
	
	float getOutlineThickness() const;
	
	const sf::Vector2f& getScale() const;
	sf::Vector2f getOrigin() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	
	const sf::Texture* getTexture() const;
	const sf::IntRect& getTextureRect() const;
	
	float getRotation() const;
	
	////////// shape setters
	
	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f& offset);
	
	void setTexture(const sf::Texture* texture, bool resetRect = false);
	void setTextureRect(const sf::IntRect& rect);
	
	void setFillColor(const sf::Color& color);
	void setOutlineColor(const sf::Color& color);

	void setScale(float factorX, float factorY);
	void setScale(const sf::Vector2f& factors);
	void scale(float factorX, float factorY);
	void scale(const sf::Vector2f& factor);
	void setOrigin(float x, float y);
	void setOrigin(const sf::Vector2f& origin);
	void setRotation(float rot);
	void rotate(float rot);
	
	////////// text getters
	
	std::pair<sf::String, sf::String> getTag(size_t pos) const;
	sf::String getSymbol(size_t pos) const;
	sf::String getValue(size_t pos) const;
	int getNumberOfTags() const;
	
	const sf::String& getString() const;
	const sf::Font* getFont() const;
	const sf::Color& getTextBackgroundColor() const;
	const sf::Color& getTextColor() const;
	unsigned int getCharacterSize() const;
	sf::Uint32 getStyle() const;
	
	////////// text setters
	
	void addTag(const sf::String& symbol, const sf::String& value);
	void addValue(const sf::String& value);
	
	void setTag(size_t pos, const sf::String& symbol, const sf::String& value);
	void setTag(const sf::String& pos, const sf::String& symbol, const sf::String& value);
	
	void setSymbol(size_t pos, const sf::String& symbol);
	void setSymbol(const sf::String& pos, const sf::String& symbol);
	
	void setValue(size_t pos, const sf::String& symbol);
	void setValue(const sf::String& pos, const sf::String& symbol);
	
	void deleteTag(size_t pos);
	
	void setFont(const sf::Font& font);
	void setTextBackgroundColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setCharacterSize(unsigned int size);
	void setStyle(sf::Uint32 style);
	
	////////// text other
	
	void toggleTextVisibility();
	void fixTextBox(); // forces text to cover whole shape
protected:
	ShapeClass shape;
	Legend text;
	sf::Vector2f adjust_origin;
	sf::Vector2f real_origin;
	
	void setOutlineThickness(float thickness);
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	const int box_lines = 5; // number of lines in a shape before scaling
	const int text_inter = 5; // distance between back rectangle and text
	
};

//////////////////////////////////////////////////////////////// shape getters

template<class ShapeClass>
DescShape<ShapeClass>::DescShape() {}

template<class ShapeClass>
DescShape<ShapeClass>::DescShape(const sf::Font& font, unsigned int characterSize)
	: text(font, characterSize) {}


template<class ShapeClass>
const sf::Vector2f& DescShape<ShapeClass>::getPosition() const {
	return shape.getPosition();
}


template<class ShapeClass>
const sf::Color& DescShape<ShapeClass>::getFillColor() const {
	return shape.getFillColor();
}

template<class ShapeClass>
const sf::Color& DescShape<ShapeClass>::getOutlineColor() const {
	return shape.getOutlineColor();
}


template<class ShapeClass>
float DescShape<ShapeClass>::getOutlineThickness() const {
	return shape.getOutlineThickness();
}


template<class ShapeClass>
const sf::Vector2f& DescShape<ShapeClass>::getScale() const {
	return shape.getScale();
}

template<class ShapeClass>
sf::Vector2f DescShape<ShapeClass>::getOrigin() const {
	return real_origin;
}

template<class ShapeClass>
sf::FloatRect DescShape<ShapeClass>::getLocalBounds() const {
	return shape.getLocalBounds();
}

template<class ShapeClass>
sf::FloatRect DescShape<ShapeClass>::getGlobalBounds() const {
	return shape.getGlobalBounds();
}


template<class ShapeClass>
const sf::Texture* DescShape<ShapeClass>::getTexture() const {
	return shape.getTexture();
}

template<class ShapeClass>
const sf::IntRect& DescShape<ShapeClass>::getTextureRect() const {
	return shape.getTextureRect();
}

template<class ShapeClass>
float DescShape<ShapeClass>::getRotation() const {
	return shape.getRotation();
}

//////////////////////////////////////////////////////////////// shape setters

template<class ShapeClass>
void DescShape<ShapeClass>::setPosition(const sf::Vector2f& position) {
	shape.setPosition(position);
	fixTextBox();
}

template<class ShapeClass>
void DescShape<ShapeClass>::setPosition(float x, float y) {
	setPosition({x, y});
}

template<class ShapeClass>
void DescShape<ShapeClass>::move(const sf::Vector2f& offset) {
	setPosition(shape.getPosition() + offset);
}

template<class ShapeClass>
void DescShape<ShapeClass>::move(float offsetX, float offsetY) {
	setPosition(shape.getPosition() + sf::Vector2f(offsetX, offsetY));
}


template<class ShapeClass>
void DescShape<ShapeClass>::setTexture(const sf::Texture* texture, bool resetRect) {
	shape.setTexture(texture, resetRect);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setTextureRect(const sf::IntRect& rect) {
	shape.setTextureRect(rect);
}


template<class ShapeClass>
void DescShape<ShapeClass>::setOutlineThickness(float thickness) {
	shape.setOutlineThickness(thickness);
	setOrigin(getOrigin());
	fixTextBox();
}


template<class ShapeClass>
void DescShape<ShapeClass>::setFillColor(const sf::Color& color) {
	shape.setFillColor(color);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setOutlineColor(const sf::Color& color) {
	shape.setOutlineColor(color);
}


template<class ShapeClass>
void DescShape<ShapeClass>::setScale(const sf::Vector2f& factors) {
	shape.setScale(factors);
	text.setScale(factors);
	fixTextBox();
}

template<class ShapeClass>
void DescShape<ShapeClass>::setScale(float factorX, float factorY) {
	setScale({factorX, factorY});
}

template<class ShapeClass>
void DescShape<ShapeClass>::scale(const sf::Vector2f& factor) {
	shape.scale(factor);
	text.setScale(factor);
	fixTextBox();
}

template<class ShapeClass>
void DescShape<ShapeClass>::scale(float factorX, float factorY) {
	scale({factorX, factorY});
}

template<class ShapeClass>
void DescShape<ShapeClass>::setOrigin(const sf::Vector2f& origin) {
	real_origin = origin;
	shape.setOrigin(real_origin - sf::Vector2f(getOutlineThickness(), getOutlineThickness()));
	fixTextBox();
}

template<class ShapeClass>
void DescShape<ShapeClass>::setOrigin(float x, float y) {
	setOrigin({x, y});
}

template<class ShapeClass>
void DescShape<ShapeClass>::setRotation(float rot) {
	shape.setRotation(rot);
	fixTextBox();
}

template<class ShapeClass>
void DescShape<ShapeClass>::rotate(float rot) {
	setRotation(getRotation() + rot);
}

//////////////////////////////////////////////////////////////// text getters

template<class ShapeClass>
std::pair<sf::String, sf::String> DescShape<ShapeClass>::getTag(size_t pos) const {
	return text.getTag(pos);
}

template<class ShapeClass>
sf::String DescShape<ShapeClass>::getSymbol(size_t pos) const {
	return getSymbol(pos);
}

template<class ShapeClass>
sf::String DescShape<ShapeClass>::getValue(size_t pos) const {
	return getValue(pos);
}

template<class ShapeClass>
int DescShape<ShapeClass>::getNumberOfTags() const {
	return text.getNumberOfTags();
}

template<class ShapeClass>
const sf::String& DescShape<ShapeClass>::getString() const {
	return text.getString();
}

template<class ShapeClass>
const sf::Font* DescShape<ShapeClass>::getFont() const {
	return text.getFont();
}



template<class ShapeClass>
const sf::Color& DescShape<ShapeClass>::getTextBackgroundColor() const {
	return text.getBackgroundColor();
}

template<class ShapeClass>
const sf::Color& DescShape<ShapeClass>::getTextColor() const {
	return text.getColor();
}

template<class ShapeClass>
unsigned int DescShape<ShapeClass>::getCharacterSize() const {
	return text.getCharacterSize();
}

template<class ShapeClass>
sf::Uint32 DescShape<ShapeClass>::getStyle() const {
	return text.getStyle();
}


//////////////////////////////////////////////////////////////// text setters

template<class ShapeClass>
void DescShape<ShapeClass>::addTag(const sf::String& symbol, const sf::String& value) {
	text.addTag(symbol, value);
}

template<class ShapeClass>
void DescShape<ShapeClass>::addValue(const sf::String& value) {
	text.addValue(value);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setTag(size_t pos, const sf::String& symbol, const sf::String& value) {
	text.setTag(pos, symbol, value);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setTag(const sf::String& pos, const sf::String& symbol, const sf::String& value) {
	text.setTag(pos, symbol, value);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setSymbol(size_t pos, const sf::String& symbol) {
	text.setSymbol(pos, symbol);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setSymbol(const sf::String& pos, const sf::String& symbol) {
	text.setSymbol(pos, symbol);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setValue(size_t pos, const sf::String& symbol) {
	text.setValue(pos, symbol);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setValue(const sf::String& pos, const sf::String& symbol) {
	text.setValue(pos, symbol);
}

template<class ShapeClass>
void DescShape<ShapeClass>::deleteTag(size_t pos) {
	text.deleteTag(pos);
}


template<class ShapeClass>
void DescShape<ShapeClass>::setFont(const sf::Font& font) {
	text.setFont(font);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setTextBackgroundColor(sf::Color color) {
	text.setBackgroundColor(color);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setTextColor(sf::Color color) {
	text.setColor(color);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setCharacterSize(unsigned int size) {
	text.setCharacterSize(size);
}

template<class ShapeClass>
void DescShape<ShapeClass>::setStyle(sf::Uint32 style) {
	text.setStyle(style);
}


//////////////////////////////////////////////////////////////// text other

template<class ShapeClass>
void DescShape<ShapeClass>::fixTextBox() {
	text.setPosition(getGlobalBounds().left + text_inter + getOutlineThickness(),
		              getGlobalBounds().top + text_inter + getOutlineThickness());
	text.fixBackgroundPosition(getGlobalBounds().left + getOutlineThickness(),
	                           getGlobalBounds().top + getOutlineThickness());
	text.setMaxSize(getGlobalBounds().width - 2 * getOutlineThickness() - 2 * text_inter,
		             getGlobalBounds().height - 2 * getOutlineThickness() - 2 * text_inter);
	text.fixBackgroundSize(getGlobalBounds().width - 2 * getOutlineThickness(),
		                    getGlobalBounds().height - 2 * getOutlineThickness());
	text.setLineHeight((getGlobalBounds().height - 2 * text_inter) / box_lines);
}

template<class ShapeClass>
void DescShape<ShapeClass>::toggleTextVisibility() {
	text.toggleVisibility();
}

template<class ShapeClass>
void DescShape<ShapeClass>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
	target.draw(text, states);
}
