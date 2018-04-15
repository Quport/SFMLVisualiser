#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class DeviceHandler {
public:
	DeviceHandler(sf::RenderWindow& _wind);
	
	// gather all events
	void pollEvents();
	
	std::vector<sf::Event> getEventList(); // get all events
	std::vector<sf::Event> getEventList(sf::Event::EventType type); // get events of type 'type'
	
	 // get event of the specific action
	sf::Event getKeyPressedEvent(sf::Keyboard::Key code);
	sf::Event getKeyReleasedEvent(sf::Keyboard::Key code);
	
	sf::Event getMouseButtonPressedEvent(sf::Mouse::Button button);
	sf::Event getMouseButtonReleasedEvent(sf::Mouse::Button button);
	
	sf::Event getMouseWheelScrolledEvent();
	sf::Event getMouseMovedEvent();
	
	
	bool keyPressed(sf::Keyboard::Key code);
	bool keyHeld(sf::Keyboard::Key code);
	bool keyReleased(sf::Keyboard::Key code);

	bool mouseButtonPressed(sf::Mouse::Button button);
	bool mouseButtonHeld(sf::Mouse::Button button);
	bool mouseButtonReleased(sf::Mouse::Button button);
	
	bool mouseWheelScrolled();
	
	bool mouseMoved();
	
	bool closePressed();

	sf::Vector2i getMousePosition();

private:
	std::map<sf::Event::EventType, std::map<int, sf::Event>> devh; // storing events (get to specific event)
	std::map<sf::Event::EventType, std::vector<sf::Event>> events; // storing events (get event list of specific type)
	std::map<sf::Keyboard::Key, bool> keyhold; // for storing currently held keys
	std::map<sf::Mouse::Button, bool> buttonhold; // for storing currently held mouse buttons

	sf::Event getEvent(sf::Event::EventType type, int code = -1);
	bool isActive(sf::Event::EventType type, int code = -1);

	sf::RenderWindow& wind;
};
