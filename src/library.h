
#ifndef LIBRARY_H
#define LIBRARY_H

#include <SFML/Graphics.hpp> // to open a renderwindow and draw stuff
#include "Triangulation.hpp" // where is defined triangulation() function
#include <string>
#include <vector>
#include <iostream>

// Window manipulation

namespace lib
{
	sf::RenderWindow * window = NULL;
	double xPos = 0, yPos = 0;
	double penWidth = 10;
	double fontSize = 80;
	sf::Color penColor(0, 0, 0);

	std::string font = "C:/Windows/Fonts/arial.ttf";
	sf::Text text; // used for writing text

	// arrays used polygon triangulation 
	std::vector<sf::Vector2f> points; // a dynamic array that will store the points of the polygon you want to triangulate
	std::vector<sf::Vector2f> theshape; /* a dynamic array that will store the points of the triangles : if the triangle n is (An Bn Cn), then the points will be stored as  [A1,B1,C1,
																																								        	  A2,B2,C2,
																																								        	  A3,B3,C3...] */
}

namespace color {

	static const sf::Color black(0, 0, 0), white(255, 255, 255), grey(192, 192, 192),
		light_grey(224, 224, 224), dark_grey(144, 144, 144), brown(139, 69, 19),
		red(255, 0, 0), green(0, 255, 0), blue(0, 0, 255), yellow(255, 255, 0),
		magenta(255, 0, 255), cyan(0, 255, 255), pink(255, 186, 193),
		orange(255, 148, 0), dark_green(0, 128, 0), indigo(72, 61, 139),
		violet(112, 0, 144), mauve(138, 43, 226), purple(183, 21, 133),
		lime_green(154, 205, 50), dark_blue(0, 0, 144), sodium_d(255, 215, 0),
		light_blue(144, 206, 255), dark_red(192, 0, 0), light_green(128, 255, 128),
		light_red(255, 128, 128);
}

void make_window(const unsigned int w, const unsigned int h, std::string title = "A Window")
{
	lib::window = new sf::RenderWindow(sf::VideoMode(w, h), title.c_str());
	lib::window->clear(sf::Color(245, 245, 245));

	// setting up fonts
	sf::Font newFont;
	newFont.loadFromFile(lib::font.c_str()); // this is windows specific...
	lib::text.setFont(newFont);
	lib::text.setPosition(lib::xPos, lib::yPos);
	lib::text.setString(" ");
	lib::text.setCharacterSize(lib::penWidth);
	lib::text.setFillColor(lib::penColor);
	lib::window->draw(lib::text);
}

void make_window(const unsigned int w, const unsigned int h, const int x, const int y, std::string title = "A Window")
{
	make_window(w, h, title);
	lib::window->setPosition(sf::Vector2i(x, y));
}

// object manipulation

void draw()
{
	lib::window->display();
	while (lib::window->isOpen())
	{
		sf::Event event;
		while (lib::window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				lib::window->close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					lib::window->close();
					break;
				}
			}
		}
	}
}

double point_angle(const double x1, const double y1, const double x2, const double y2)
{
	const double angle = (atan2(y2 - y1, x2 - x1) * 180 / acos(-1));
	return (angle < 0) ? 360 + angle : angle;
}

double point_distance(const double x1, const double y1, const double x2, const double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void draw_point(const double x, const double y, const double radius, sf::Color color)
{
	if (lib::window == NULL && !lib::window->isOpen())
		return;

	sf::CircleShape circle;
	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setPosition(x - radius, y - radius);

	lib::window->draw(circle);
}

void draw_point()
{
	draw_point(lib::xPos, lib::yPos, lib::penWidth, lib::penColor);
}

void draw_line(const double x1, const double y1, const double length, const double angle, const double pen_width, sf::Color color)
{
	if (lib::window == NULL && !lib::window->isOpen())
		return;

	const int x2 = length * cos(angle* (acos(-1) / 180.0));
	const int y2 = length * sin(angle* (acos(-1) / 180.0));

	// makes line edges look smooth
	draw_point(x1, y1, pen_width / 2, color);
	draw_point(x1 + x2, y1 + y2, pen_width / 2, color);

	// draws rectangle
	sf::RectangleShape rectangle;
	rectangle.setFillColor(color);
	rectangle.setPosition(x1, y1 - (pen_width / 2)); // x, y
	rectangle.setSize(sf::Vector2f(length, pen_width)); // x2, y2

	// transforms the line to the specified angle
	sf::Transform transform;
	transform.rotate(angle, sf::Vector2f(x1, y1));

	lib::window->draw(rectangle, transform);
}

void draw_line_segment(const double x1, const double y1, const double x2, const double y2, const int pen_width, sf::Color color)
{
	if (lib::window == NULL && !lib::window->isOpen())
		return;

	const double length = point_distance(x1, y1, x2, y2);
	const double angle = point_angle(x1, y1, x2, y2);
	draw_line(x1, y1, length, angle, pen_width, color);
}

void set_pen_width(const double w)
{
	lib::penWidth = w;
}

void set_pen_color(const sf::Color c)
{
	lib::penColor = c;
}

void move_to(const double x, const double y)
{
	lib::xPos = x;
	lib::yPos = y;
}

void draw_to(const double x, const double y)
{
	draw_line_segment(lib::xPos, lib::yPos, x, y, lib::penWidth, lib::penColor);
	move_to(x, y);
}

// text  manipulation

void set_font_size(const double size)
{
	lib::fontSize = size;
}

void set_font(const std::string name)
{
	lib::font = "C:/Windows/Fonts/" + name + ".ttf"; // this is windows specific...
	sf::Font font;
	if (!font.loadFromFile(lib::font.c_str()))
		return;
	lib::text.setFont(font);
}

void set_font(const std::string name, const double size)
{
	set_font(name);
	set_font_size(size);
}

void write_string(const std::string str)
{
	if (lib::window != NULL && !lib::window->isOpen())
		return;

	sf::Font newFont;
	newFont.loadFromFile(lib::font.c_str());

	lib::text.setPosition(lib::xPos, lib::yPos);
	lib::text.setString(str.c_str());
	lib::text.setCharacterSize(lib::fontSize);
	lib::text.setFont(newFont);
	lib::text.setFillColor(lib::penColor);
	lib::window->draw(lib::text);
}

// Polygon Triangulation draw funtions

// gets the shape ready to be drawn
void start_shape()
{
	lib::points.clear();
	lib::theshape.clear();
}

// notes the position of the pen
void note_position()
{
	sf::Vector2f position(lib::xPos, lib::yPos);
	// only push back if empty or if distance is greater than 10
	if(lib::points.empty() || vectorDistance(position, lib::points.back()) > 10) // vectorDistance() is defined in Triangulation.h
		lib::points.push_back(position); // push back current position
}

// draws the shape
void draw_shape()
{
	sf::VertexArray trianglesVA(sf::Triangles); // a vertex array that will draw the triangles for us (SFML feature)

	lib::theshape = triangulate(lib::points); // triangulate() is defined in Triangulation.h

	for (int i(0); i < lib::theshape.size(); i++) // we copy the points triangulated into the vertex arrays in order to draw the polygon and its wireframe
	{
		sf::Vertex vertex(lib::theshape[i]);
		vertex.color = lib::penColor;
		trianglesVA.append(vertex);
	}
	// draw triangles!
	lib::window->draw(trianglesVA);
}





#endif /* LIBRARY_H */
