#include "Triangulation.hpp"

// calculates the determinant of two vectors
float determinant(const sf::Vector2f & u, const sf::Vector2f & v)
{ return u.x*v.y - u.y*v.x; }

// calculates the distance between the two vectors
float vectorDistance(const sf::Vector2f & v1, const sf::Vector2f & v2)
{ return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2)); }

// tests if triangle abc contains a point within it
// this is done by calculating if the point is at the left side of each edge
// going arround in a counter clockwise direction
bool pointIsWithinTriangle(const sf::Vector2f & a, const sf::Vector2f & b, 
	                       const sf::Vector2f & c, const sf::Vector2f & point)
{ bool ab = determinant(b - a, point - a) > 0;
  bool bc = determinant(c - b, point - b) > 0;
  bool ca = determinant(a - c, point - c) > 0;
  return (ab && bc && ca) ? true : false; }

// Triangulates a simple complex polygon into multiple triangles
std::vector<sf::Vector2f> triangulate(const std::vector<sf::Vector2f> & initialPoints) 
{ // An array of points that will store all the triangles that are clipped,
  // each triangle is composed of three points, the first triangle will be
  // the first 3 points and so on...
  std::vector<sf::Vector2f> triangles;

  // if you cant make a triangle return an empty point vector
  if(initialPoints.size() < 3) 
    return triangles;

  // creates a copy of the points that will be modified 
  // as the ears are extracted
  std::vector<sf::Vector2f> points = initialPoints;

  // bool impossibleToTriangulate = false;
  bool triangleFound = true;

  // keep extracting triangles until there are no more points
  while(points.size() != 0)
  { // if there are no more triangles to extract return all the triangles
	// TODO fix bug were if you don't find a triangle on the first run
	//      the algorithm stops or when you have complex polygons
	if (!triangleFound)
	  return triangles;

	// set triangleFound to false to find a new ear within every loop
	triangleFound = false;

	// check if 3 consecutive counter clockwise points form an ear
	for(int i = 0; i < points.size() - 2; i++)
	{ // if the triangle if formed in the countrer clockwise direction
	  if (determinant(points[i + 1] - points[i], points[i + 2] - points[i + 1]) < 0)
	  { triangleFound = true;
		// check to see if there's a point within the triangle
		for (int j = 0; j < initialPoints.size(); j++)
		  // if a point is within it its not an ear
		  if (pointIsWithinTriangle(points[i + 2], points[i + 1], points[i], initialPoints[j]))
		    triangleFound = false; }

	  // if an ear is found, add the triangle to triangles and 
	  // erase the point that forms the ear in points
	  if(triangleFound)
	  { // push back the points
		triangles.push_back(points[i]);
		triangles.push_back(points[i + 1]);
		triangles.push_back(points[i + 2]);

		// erase the point in the vector
		points.erase(points.begin() + i + 1); 
		break; } } }

  // return the array of triangles
  return triangles; }

