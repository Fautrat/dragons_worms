#include "Collision.h"

bool Collision::BoxAndBox(const sf::Rect<int>& recA, const sf::Rect<int>& recB)
{
	return (recA.left + recA.width >= recB.left &&
		recB.left + recB.width >= recA.left &&
		recA.top + recA.height >= recB.top &&
		recB.top + recB.height >= recA.top);
}

bool Collision::BoxAndBox(const BoxCollider2D& colA, const BoxCollider2D& colB) {

	return (colA.box.left + colA.box.width >= colB.box.left &&
		colB.box.left + colB.box.width >= colA.box.left &&
		colA.box.top + colA.box.height >= colB.box.top &&
		colB.box.top + colB.box.height >= colA.box.top);

}