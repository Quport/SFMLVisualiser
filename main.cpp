#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "include/all.h"
using namespace std;
using namespace sf;

#define ST first
#define ND second
#define EB emplace_back

typedef Vector2i V2i;
typedef Vector2f V2f;
typedef pair<int, int> PII;

///////////////////////////////////////////////////////////////////////////////

RenderWindow window;
HudRenderWindow hud_window(window);

V2i RES(1280, 720);
Color BACKGROUND(127, 127, 127);

Font ubuntu_mono, arial;

// fps
Clock cl; // frame clock
const int fps_limit = 60; // max fps
double real_fps = fps_limit; // measured fps

ViewMoving vm(fps_limit, window);
Legend legend(ubuntu_mono);
DeviceHandler dev(window);
TextureHandler tex("icons");

///////////////////////////////  GAME FUNCTIONS  //////////////////////////////

void handleEvents() {
	dev.pollEvents();

	if (dev.closePressed() || dev.keyPressed(Keyboard::Escape))
		window.close();
	
	// show legend
	if (dev.keyPressed(Keyboard::L))
		legend.toggleVisibility();
	
	// view moving
	if (dev.mouseButtonPressed(Mouse::Right))
		vm.setMouseHeld(true);
	if (dev.mouseButtonReleased(Mouse::Right))
		vm.setMouseHeld(false);
	vm.mouseMove();
	
	if (dev.keyHeld(Keyboard::S))
		vm.keyMove({0, 1});
	if (dev.keyHeld(Keyboard::W))
		vm.keyMove({0, -1});
	if (dev.keyHeld(Keyboard::A))
		vm.keyMove({-1, 0});
	if (dev.keyHeld(Keyboard::D))
		vm.keyMove({1, 0});
	
	// view zooming
	if (dev.mouseWheelScrolled()) {
		Event tm = dev.getMouseWheelScrolledEvent();
		if (tm.mouseWheelScroll.delta > 0)
			vm.zoom();
		else if (tm.mouseWheelScroll.delta < 0)
			vm.outzoom();
	}
	
}

void frameEnd() {
	real_fps = 1.0 / cl.getElapsedTime().asSeconds();	
	BetterText fps_txt(to_stringp(real_fps, 0), ubuntu_mono);
	fps_txt.setPosition(2, 2);
	fps_txt.setLineHeight(20);
	
	draw(hud_window, legend, fps_txt);
	
	cl.restart();
	window.display();
	window.clear(BACKGROUND);
}

///////////////////////////////  MAIN PART  ///////////////////////////////

void initVisualization() {
	window.create(VideoMode(RES.x, RES.y), "Visual");
	window.setFramerateLimit(fps_limit);
	assert(ubuntu_mono.loadFromFile("fonts/ubuntu_mono.ttf"));
	assert(arial.loadFromFile("fonts/arial.ttf"));
}

int main() {
	initVisualization();
	
	
	LineShape xxx({-100, -100}, {-200, -200});
	xxx.setPoint2({-300, 200});
	xxx.setThickness(10);
	xxx.setFillColor(Color::Yellow);
	
	legend.setPosition(8, 60);
	legend.setLineHeight(25);
	legend.addTag("L", "zmien widocznosc\nlegendy");
	legend.addTag("P", "zmien widocznosc\nnapisow na figurach");
	legend.addTag("e", "jakis dlugi napis\nrozbity na\nkilka wierszy");
	legend.addValue("124523452");
	
	vector<DescCircle> v(10);
	for (int i = 0; i < 10; i++) {
		v[i].setFont(ubuntu_mono);
		v[i].setRadius(50);
		v[i].setPosition(100, 100 * (i + 1));
		v[i].addValue(to_string(i));
		// v[i].setTexture(tex.getTexture("fitness/003-burger.png"));
	}
	
	int n = 20, m = 20;
	vector<vector<DescRect>> v2(n, vector<DescRect>(m, DescRect({100, 100}, ubuntu_mono)));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			v2[i][j].setPosition(250 + 100 * j, 100 + 100 * i);
			v2[i][j].addTag("x", to_string(j));
			v2[i][j].addTag("y", to_string(i));
			v2[i][j].addTag("heat", to_stringp((float)(i + 1) * (j + 1) / (n * m)));
			v2[i][j].setFillColor(heatMapColor((float)(i + 1) * (j + 1) / (n * m)));
			// v2[i][j].setTexture(tex.getTexture("fitness/003-burger.png"));
		}
	
	while (window.isOpen()) {
		handleEvents();
		legend.setSymbol(3, to_string(rand() % 10));
		
		draw(window, v, v2, xxx);
		
		if (dev.keyPressed(Keyboard::P)) {
			for (auto &i : v)
				i.toggleTextVisibility();
			for (auto &i : v2)
				for (auto &j : i) 
					j.toggleTextVisibility();
		}
		
		if (dev.keyPressed(Keyboard::N)) {
			for (auto &i : v2)
				for (auto &j : i) 
					j.setOutlineThickness(j.getOutlineThickness() + 1);
		}
		if (dev.keyPressed(Keyboard::M)) {
			for (auto &i : v2)
				for (auto &j : i) 
					j.setOutlineThickness(j.getOutlineThickness() - 1);
		}
		
		frameEnd();
	}

	return 0;
}
/*
*/

