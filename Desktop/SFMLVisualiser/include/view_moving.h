#pragma once
#include <SFML/Graphics.hpp>

class ViewMoving {
public:
	// wind - reference to window (to change view)
	ViewMoving(int fps, sf::RenderWindow& wind);
	
	void setZoomSpeed(double speed);
	void setMoveSpeed(double speed);
	void setMouseHeld(bool b); // is mouse held
	
	double getZoomSpeed();
	double getMoveSpeed();
	
	void outzoom();
	void zoom();
	
	void mouseMove();
	void keyMove(const std::pair<int, int>& dir);

private:
	bool mouse_held; // is right mouse button hold
	sf::Vector2i mouse_beg; // position of mouse at the beggining of mouse holding

	double zoom_speed;
	double zoom_val; // current zoom
	double move_speed; // speed of moving with WSAD [pixels/second] 
	int fps; // expected framerate (for moving with WSAD)
	sf::RenderWindow &wind;
	
	void zoom(double zoom);
	
	const double default_zoom_speed = 1.1;
	const double default_zoom_val = 1;
	const double default_move_speed = 900;
};
