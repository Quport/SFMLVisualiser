#pragma once
#include <SFML/Graphics.hpp>
#include "better_text.h"

class Legend : public BetterText {
public:
	Legend();
	Legend(const sf::Font& font, unsigned int characterSize = 400);
	
	/*
		tag:
			symbol: value
		example:
			L: hide this window
			   second line
			   and third
	*/
	
	////////// getters
	
	std::pair<sf::String, sf::String> getTag(size_t pos) const;
	sf::String getSymbol(size_t pos) const;
	sf::String getValue(size_t pos) const;
	int getNumberOfTags() const;
	
	const sf::Color& getBackgroundColor() const;
	
	////////// setters
	
	void addTag(const sf::String& symbol, const sf::String& value);
	void addValue(const sf::String& value);
	
	// search for a tag in position 'pos'
	void setTag(size_t pos, const sf::String& symbol, const sf::String& value);
	// search for a tag with symbol 'pos'
	void setTag(const sf::String& pos, const sf::String& symbol, const sf::String& value);
	
	void setSymbol(size_t pos, const sf::String& symbol);
	void setSymbol(const sf::String& pos, const sf::String& symbol);
	
	void setValue(size_t pos, const sf::String& symbol);
	void setValue(const sf::String& pos, const sf::String& symbol);
	
	void deleteTag(size_t pos);
	void deleteTag(const sf::String& pos);
	
	void setBackgroundColor(sf::Color color);
	
	// fixing size of background rectangle
	void fixBackgroundSize(const sf::Vector2f& siz);
	void fixBackgroundSize(float width, float height);
	void unfixBackgroundSize();
	
	// fixing position of background rectangle
	void fixBackgroundPosition(const sf::Vector2f& pos);
	void fixBackgroundPosition(float x, float y);
	void unfixBackgroundPosition();
	
	// setting origin of background rectangle
	void setBackgroundOrigin(const sf::Vector2f& ori);
	void setBackgroundOrigin(float x, float y);
	
	////////// other
	
	void toggleVisibility();
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void setup(); // setup default options
	
	void updateString(); // recalculate text string
	sf::String mergeStrings(); // merge strings in strings vector with adjusting
	
	/*
		adjust values, example:
		symbol: value1,
		        value2,
		        value3...
	*/
	sf::String adjustString(const sf::String& text, int interval);
	
	bool visible; // parameter to toggleVisibility()
	bool back_siz_fixed; // has background rectangle fixed size?
	bool back_pos_fixed; // has background rectangle fixed position?
	
	sf::Vector2f back_siz; // size of fixed background rectangle
	sf::Vector2f back_pos; // position of fixed background rectangle
	sf::Vector2f back_ori; // origin of fixed background rectangle
	
	sf::RectangleShape createBackRect() const;
	
	sf::Color back_fill_color;
	
	std::vector<std::pair<sf::String, sf::String>> tags; // storage for tags
	
	const float default_back_out_thickness = 2;
	const sf::Color default_back_out_color = sf::Color::Black;
	const sf::Color default_text_color = sf::Color::Black;
	const sf::Color default_back_color = sf::Color::Color(255, 255, 255, 200);
};