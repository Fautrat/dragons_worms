#include "Collision.h"

bool Collision::BoxAndBox(const sf::Rect<int>& recA, const sf::Rect<int>& recB)
{
	return (recA.left + recA.width >= recB.left &&
		recB.left + recB.width >= recA.left &&
		recA.top + recA.height >= recB.top &&
		recB.top + recB.height >= recA.top);
}

//bool Collision::BoxAndBox(const BoxCollider2D& colA, const BoxCollider2D& colB) {
//	return BoxAndBox(colA.box, colB.box);
//}