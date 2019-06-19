#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> 
#include <cmath>


// calculates the determinant of two vectors
float determinant(const sf::Vector2f & u, const sf::Vector2f & v);

// calculates the distance between the two vectors
float vectorDistance(const sf::Vector2f & v1, const sf::Vector2f & v2);

// tests if triangle abc contains a point within it
// this is done by calculating if the point is at the left side of each edge
// going arround in a counter clockwise direction
bool pointIsWithinTriangle(const sf::Vector2f & a, const sf::Vector2f & b,
	const sf::Vector2f & c, const sf::Vector2f & point);

// convert a shape into a vector containing triangles
// every three entrees should be a triangle
std::vector<sf::Vector2f> triangulate(const std::vector<sf::Vector2f> & initialPoints);

