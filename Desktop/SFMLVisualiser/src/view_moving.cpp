#include "../include/view_moving.h"
using namespace sf;
using namespace std;

ViewMoving::ViewMoving(int _fps, RenderWindow &_wind)
	: fps(_fps), wind(_wind) {
	zoom_speed = default_zoom_speed;
	zoom_val = default_zoom_val;
	move_speed = default_move_speed;
	mouse_held = false;
}

void ViewMoving::zoom(double zoom) {
	Vector2i mouse_new = Mouse::getPosition(wind);
	const Vector2f beforeCoord = wind.mapPixelToCoords(mouse_new);
	View view = wind.getView();
	zoom_val *= zoom;
	view.zoom(zoom);
	wind.setView(view);
	const Vector2f afterCoord = wind.mapPixelToCoords(mouse_new);
	const Vector2f offsetCoords = beforeCoord - afterCoord;
	view.move(offsetCoords);
	wind.setView(view);
}

void ViewMoving::setZoomSpeed(double speed) {
	zoom_speed = speed;
}

void ViewMoving::setMoveSpeed(double speed) {
	move_speed = speed;
}

void ViewMoving::setMouseHeld(bool b) {
	mouse_held = b;
	mouse_beg = Mouse::getPosition();
}

double ViewMoving::getZoomSpeed() {
	return zoom_speed;
}

double ViewMoving::getMoveSpeed() {
	return move_speed;
}

void ViewMoving::outzoom() {
	zoom(zoom_speed);
}

void ViewMoving::zoom() {
	zoom(1.0 / zoom_speed);
}

void ViewMoving::mouseMove() {
	View view = wind.getView();
	
	// vector<Keyboard::Key> code = {Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D};
	// vector<pair<int, int>> react = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	// for(int i = 0; i < 4; i++)
	// 	if(Keyboard::isKeyPressed(code[i]))
	// 		view.move(zoom_val * react[i].first * (move_speed / fps), zoom_val * react[i].second * (move_speed / fps));
	
	if(mouse_held) {
		Vector2i mouse_new = Mouse::getPosition();
		view.move(zoom_val * (mouse_beg.x - mouse_new.x), zoom_val * (mouse_beg.y - mouse_new.y));
		mouse_beg = Mouse::getPosition();
	}
	
	wind.setView(view);
}

void ViewMoving::keyMove(const pair<int, int> &dir) {
	View view = wind.getView();
	view.move(zoom_val * dir.first * (move_speed / fps), zoom_val * dir.second * (move_speed / fps));
	wind.setView(view);
}
