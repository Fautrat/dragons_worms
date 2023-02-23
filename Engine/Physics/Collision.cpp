#include "Collision.h"
#include <math.h>

//bool Collision::BoxAndBox(const sf::Rect<int>& recA, const sf::Rect<int>& recB)
//{
//	return (recA.left + recA.width >= recB.left &&
//		recB.left + recB.width >= recA.left &&
//		recA.top + recA.height >= recB.top &&
//		recB.top + recB.height >= recA.top);
//}

bool Collision::BoxAndBox(const BoxCollider2D& colA, const BoxCollider2D& colB) {

	return (colA.box.left + colA.box.width >= colB.box.left &&
		colB.box.left + colB.box.width >= colA.box.left &&
		colA.box.top + colA.box.height >= colB.box.top &&
		colB.box.top + colB.box.height >= colA.box.top);

}

bool Collision::SphereAndBox(const SphereCollider2D& colA, const BoxCollider2D& colB)
{
	int cx = colA.circle_position.x;
	int cy = colA.circle_position.y;
	int radius = colA.m_radius;

	int rx = colB.box.left;
	int ry = colB.box.top;
	int rw = colB.box.width;
	int rh = colB.box.height;

	int testX = cx;
	int testY = cy;

	// which edge is closest?
	if (cx < rx)         testX = rx;      // test left edge
	else if (cx > rx + rw) testX = rx + rw;   // right edge
	if (cy < ry)         testY = ry;      // top edge
	else if (cy > ry + rh) testY = ry + rh;   // bottom edge

	// get distance from closest edges
	float distX = cx - testX;
	float distY = cy - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the radius, collision!
	if (distance <= radius) {
		return true;
	}
	return false;

}

bool Collision::TriangleAndSphere(const TriangleCollider2D& colA, const SphereCollider2D& colB)
{
	for (auto line : colA.m_lines)
	{
		// is either end INSIDE the circle?
		// if so, return true immediately
		bool inside1 = pointCircle(line.x.x, line.x.y, colB.circle_position.x, colB.circle_position.y, colB.m_radius);
		bool inside2 = pointCircle(line.y.x, line.y.y, colB.circle_position.x, colB.circle_position.y, colB.m_radius);
		if (inside1 || inside2) return true;

		// get length of the line
		float distX = line.x.x - line.y.x;
		float distY = line.x.y - line.y.y;
		float len = sqrt((distX * distX) + (distY * distY));

		// get dot product of the line and circle
		float dot = (((colB.circle_position.x - line.x.x) * (line.y.x - line.x.x)) + ((colB.circle_position.y - line.x.y) * (line.y.y - line.x.y))) / pow(len, 2);

		// find the closest point on the line
		float closestX = line.x.x + (dot * (line.y.x - line.x.x));
		float closestY = line.x.y + (dot * (line.y.y - line.x.y));

		// is this point actually on the line segment?
		// if so keep going, but if not, return false
		bool onSegment = linePoint(line.x.x, line.x.y, line.y.x, line.y.y, closestX, closestY);
		if (!onSegment) continue;

		// optionally, draw a circle at the closest
		// point on the li

		// get distance to closest point
		distX = closestX - colB.circle_position.x;
		distY = closestY - colB.circle_position.y;
		float distance = sqrt((distX * distX) + (distY * distY));

		if (distance <= colB.m_radius) {
			return true;
		}

	}
	return false;

}

bool Collision::linePoint(float x1, float y1, float x2, float y2, float px, float py)
{
	// get distance from the point to the two ends of the line
	float d1 = dist(px, py, x1, y1);
	float d2 = dist(px, py, x2, y2);

	// get the length of the line
	float lineLen = dist(x1, y1, x2, y2);

	// since floats are so minutely accurate, add
	// a little buffer zone that will give collision
	float buffer = 0.1;    // higher # = less accurate

	// if the two distances are equal to the line's
	// length, the point is on the line!
	// note we use the buffer here to give a range,
	// rather than one #
	if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer) {
		return true;
	}
	return false;

}

bool Collision::pointCircle(float px, float py, float cx, float cy, float r)
{
	// get distance between the point and circle's center
	// using the Pythagorean Theorem
	float distX = px - cx;
	float distY = py - cy;
	float distance = std::sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the circle's
	// radius the point is inside!
	if (distance <= r) {
		return true;
	}
	return false;
}

bool Collision::BoxAndTriangle(const BoxCollider2D& colA, const TriangleCollider2D& colB)
{
	int increment = 0;
	for (auto line : colB.m_lines)
	{
		increment++;
		
		// check if the line has hit any of the rectangle's sides
		// uses the Line/Line function below
		float x1 = line.x.x;      // points for line (controlled by mouse)
		float y1 = line.x.y;
		float x2 = line.y.x;      // static point
		float y2 = line.x.y;

		float rx = colA.box.left;    // square position
		float ry = colA.box.top;
		float rw = colA.box.width;    // and size
		float rh = colA.box.height;

		bool left = LineAndLine(x1, y1, x2, y2, rx, ry, rx, ry + rh);
		bool right = LineAndLine(x1, y1, x2, y2, rx + rw, ry, rx + rw, ry + rh);
		bool top = LineAndLine(x1, y1, x2, y2, rx, ry, rx + rw, ry);
		bool bottom = LineAndLine(x1, y1, x2, y2, rx, ry + rh, rx + rw, ry + rh);

		// if ANY of the above are true, the line
		// has hit the rectangle
		if (left || right || top || bottom) {
			return true;
		}
	}
	return false;
}

bool Collision::LineAndLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	// calculate the direction of the lines
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
		return true;
	}
	return false;
}

float Collision::dist(float x1, float y1, float x2, float y2)
{

	return std::sqrt(std::pow(x2-x1,2)+std::pow(y2-y1,2));
}
