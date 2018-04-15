#include "../include/device_handler.h"
using namespace std;
using namespace sf;

DeviceHandler::DeviceHandler(RenderWindow& _wind)
	: wind(_wind) {}

void DeviceHandler::pollEvents() {
	Event event;
	devh.clear();
	while (wind.pollEvent(event)) {
		events[event.type].emplace_back(event);
		if (event.type == Event::KeyPressed) {
			keyhold[event.key.code] = true;
			devh[event.type][event.key.code] = event;
		}
		else if (event.type == Event::KeyReleased) {
			keyhold[event.key.code] = false;
			devh[event.type][event.key.code] = event;
		}
		else if (event.type == Event::MouseButtonPressed) {
			buttonhold[event.mouseButton.button] = true;
			devh[event.type][event.key.code] = event;
		}
		else if (event.type == Event::MouseButtonReleased) {
			buttonhold[event.mouseButton.button] = false;
			devh[event.type][event.key.code] = event;
		}
		else
			devh[event.type][-1] = event;
	}
}

vector<Event> DeviceHandler::getEventList() {
	vector<Event> ret;
	for (auto& i : events)
		for (auto& j : i.second)
			ret.emplace_back(j);
	return ret;
}

vector<Event> DeviceHandler::getEventList(Event::EventType type) {
	vector<Event> ret;
	for (auto& i : events[type])
		ret.emplace_back(i);
	return ret;
}

Event DeviceHandler::getEvent(Event::EventType type, int code) {
	Event ret;
	auto& ref = devh[type];
	if (ref.find(code) != ref.end())
		ret = ref[code];
	return ret;
}

Event DeviceHandler::getKeyPressedEvent(Keyboard::Key code) {
	return getEvent(Event::KeyPressed, code);
}
Event DeviceHandler::getKeyReleasedEvent(Keyboard::Key code) {
	return getEvent(Event::KeyReleased, code);
}

Event DeviceHandler::getMouseButtonPressedEvent(Mouse::Button button) {
	return getEvent(Event::MouseButtonPressed, button);
}
Event DeviceHandler::getMouseButtonReleasedEvent(Mouse::Button button) {
	return getEvent(Event::MouseButtonReleased, button);
}

Event DeviceHandler::getMouseWheelScrolledEvent() {
	return getEvent(Event::MouseWheelScrolled);
}
Event DeviceHandler::getMouseMovedEvent() {
	return getEvent(Event::MouseMoved);
}

bool DeviceHandler::isActive(Event::EventType type, int code) {
	auto& ref = devh[type];
	return ref.find(code) != ref.end();
}

bool DeviceHandler::keyPressed(Keyboard::Key code) {
	return isActive(Event::KeyPressed, code);
}
bool DeviceHandler::keyHeld(Keyboard::Key code) {
	return keyhold[code];
}
bool DeviceHandler::keyReleased(Keyboard::Key code) {
	return isActive(Event::KeyReleased, code);
}

bool DeviceHandler::mouseButtonPressed(Mouse::Button button) {
	return isActive(Event::MouseButtonPressed, button);
}
bool DeviceHandler::mouseButtonHeld(Mouse::Button button) {
	return buttonhold[button];
}
bool DeviceHandler::mouseButtonReleased(Mouse::Button button) {
	return isActive(Event::MouseButtonReleased, button);
}

bool DeviceHandler::mouseWheelScrolled() {
	return isActive(Event::MouseWheelScrolled);
}

bool DeviceHandler::mouseMoved() {
	return isActive(Event::MouseMoved);
}

bool DeviceHandler::closePressed() {
	return isActive(Event::Closed);
}

sf::Vector2i DeviceHandler::getMousePosition() {
	return Mouse::getPosition();
}