#include "../include/legend.h"
#include <iostream>
#include "../include/useful.h"
using namespace sf;
using namespace std;

Legend::Legend() {
	setup();
}

Legend::Legend(const Font& font, unsigned int characterSize)
	: BetterText("", font, characterSize) {
	setup();
}

void Legend::setup() {
	setColor(default_text_color);
	setBackgroundColor(default_back_color);
	setBackgroundColor(default_back_color);
	visible = true;
	back_pos_fixed = false;
	back_siz_fixed = false;
}

//////////////////////////////////////////////////////////////// getters

pair<String, String> Legend::getTag(size_t pos) const {
	if (tags.size() > pos)
		return tags[pos];
	else {
		cerr << "WARNING, Legend: tried to getTag(" << pos << ") but size of tags is " << tags.size() << endl;
		return {"", ""};
	}
}

String Legend::getSymbol(size_t pos) const {
	if (tags.size() > pos)
		return tags[pos].first;
	else {
		cerr << "WARNING, Legend: tried to getSymbol(" << pos << ") but size of tags is " << tags.size() << endl;
		return "";
	}
}

String Legend::getValue(size_t pos) const {
	if (tags.size() > pos)
		return tags[pos].second;
	else {
		cerr << "WARNING, Legend: tried to getValue(" << pos << ") but size of tags is " << tags.size() << endl;
		return "";
	}
}

int Legend::getNumberOfTags() const {
	return tags.size();
}

const sf::Color& Legend::getBackgroundColor() const {
	return back_fill_color;
}

//////////////////////////////////////////////////////////////// setters

void Legend::addTag(const String& symbol, const String& value) {
	tags.emplace_back(symbol, value);
	updateString();
}

void Legend::addValue(const String& value) {
	addTag("", value);
}

void Legend::setTag(size_t pos, const String& symbol, const String& value) {
	if (tags.size() > pos)
		tags[pos] = {symbol, value};
	else
		cerr << "WARNING, Legend: tried to setTag(" << pos << ", \"" << string(symbol) << "\", \"" 
	        << string(value) << "\") but size of tags is " << tags.size() << endl;
	updateString();
}

void Legend::setSymbol(size_t pos, const String& symbol) {
	if (tags.size() > pos)
		tags[pos].first = symbol;
	else
		cerr << "WARNING, Legend: tried to setSymbol(" << pos << ", \"" << string(symbol) << "\") but size of tags is " 
	        << tags.size() << endl;
	updateString();
}

void Legend::setValue(size_t pos, const String& value) {
	if (tags.size() > pos)
		tags[pos].second = value;
	else
		cerr << "WARNING, Legend: tried to setValue(" << pos << ", \"" << string(value) << "\") but size of tags is " 
	        << tags.size() << endl;
	updateString();
}

void Legend::deleteTag(size_t pos) {
	if (tags.size() > pos)
		tags.erase(tags.begin() + pos);
	else
		cerr << "WARNING, Legend: tried to deleteTag(" << pos << "\") but size of tags is " << tags.size() << endl;
	updateString();
}

void Legend::setTag(const String& pos, const String& symbol, const String& value) {
	for (auto& i : tags) {
		if (i.first == pos) {
			i = {symbol, value};
			updateString();
			return;
		}
	}
	cerr << "WARNING, Legend: tried to setTag(\"" << string(pos) << "\", \"" << string(symbol) << "\", \"" 
	     << string(value) << "\") but couldn't find any tag with a given symbol" << endl;
}

void Legend::setSymbol(const String& pos, const String& symbol) {
	for (auto& i : tags) {
		if (i.first == pos) {
			i.first = symbol;
			updateString();
			return;
		}
	}
	cerr << "WARNING, Legend: tried to setSymbol(\"" << string(pos) << "\", \"" << string(symbol) 
	     << "\") but couldn't find any tag with a given symbol" << endl;
}

void Legend::setValue(const String& pos, const String& value) {
	for (auto& i : tags) {
		if (i.first == pos) {
			i.second = value;
			updateString();
			return;
		}
	}
	cerr << "WARNING, Legend: tried to setValue(\"" << string(pos) << "\", \"" << string(value) 
	     << "\") but couldn't find any tag with a given symbol" << endl;
}

void Legend::deleteTag(const String& pos) {
	for (size_t i = 0; i < tags.size(); i++) {
		if (tags[i].first == pos) {
			tags.erase(tags.begin() + i);
			updateString();
			return;
		}
	}
	cerr << "WARNING, Legend: tried to deleteTag(\"" << string(pos) << "\") but couldn't find any tag with a given symbol" << endl;
}

void Legend::setBackgroundColor(Color color) {
	back_fill_color = color;
}

//////////////////////////////////////////////////////////////// other

void Legend::toggleVisibility() {
	visible ^= 1;
}

void Legend::fixBackgroundPosition(const Vector2f &pos) {
	back_pos = pos;
	back_pos_fixed = true;
}

void Legend::fixBackgroundPosition(float x, float y) {
	fixBackgroundPosition({x, y});
}

void Legend::fixBackgroundSize(const Vector2f &siz) {
	back_siz = siz;
	back_siz_fixed = true;
}

void Legend::fixBackgroundSize(float width, float height) {
	fixBackgroundSize({width, height});
}

void Legend::setBackgroundOrigin(const Vector2f &ori) {
	back_ori = ori;
}

void Legend::setBackgroundOrigin(float x, float y) {
	setBackgroundOrigin({x, y});
}

void Legend::unfixBackgroundPosition() {
	back_pos_fixed = false;
}

void Legend::unfixBackgroundSize() {
	back_siz_fixed = false;
}

void Legend::updateString() {
	setString(mergeStrings());
}

String Legend::mergeStrings() {
	String ret;
	for (auto &i : tags) {
		if (!ret.isEmpty())
			ret += '\n';
		if (i.first.isEmpty())
			ret += adjustString(i.second, 0);
		else {
			String symbol = i.first + ": ";
			ret += symbol + adjustString(i.second, symbol.getSize());
		}
	}
	return ret;
}

RectangleShape Legend::createBackRect() const {
	RectangleShape back;
	auto tm = getGlobalBounds();
	
	if (back_pos_fixed)
		back.setPosition(back_pos.x - back_ori.x, back_pos.y - back_ori.y);
	else
		back.setPosition(tm.left - back_ori.x, tm.top - back_ori.y);
	
	if (back_siz_fixed)
		back.setSize(back_siz);
	else
		back.setSize({tm.width, tm.height});
	
	back.setFillColor(back_fill_color);
	back.setOutlineColor(default_back_out_color);
	back.setOutlineThickness(default_back_out_thickness);
	return back;
}

void Legend::draw(RenderTarget& target, RenderStates states) const {
	if (visible) {
		target.draw(createBackRect(), states);
		target.draw(getText(), states);
	}
}

String Legend::adjustString(const String& tex, int interval) {
	String ret;
	for (const char& i : tex) {
		ret += i;
		if (i == '\n')
			for (int j = 0; j < interval; j++)
				ret += ' ';
	}
	return ret;
}
