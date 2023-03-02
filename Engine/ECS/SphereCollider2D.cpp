#include "SphereCollider2D.h"

bool SphereCollider2D::init()
{
	if (entity->hasComponent<Transform>() && entity->hasComponent<Rigidbody>() && entity->hasComponent<SpriteRenderer>())
	{
		const auto& transform = entity->getComponent<Transform>();
		auto& rb = *entity->getComponent<Rigidbody>();
		auto& sr = *entity->getComponent<SpriteRenderer>();
		m_radius = rb.getRadius();

		m_radius = sr.getSprite()->getGlobalBounds().width / 2;
		float area = m_radius * m_radius * PI;

		/*if (area < world.getMinBodySize()) { std::cout << "Circle radius is too small. Min circle area is " << world.getMinBodySize() << std::endl; }
		if (area > world.getMaxBodySize()) { std::cout << "Circle radius is too large. Max circle area is " << world.getMinBodySize() << std::endl; }
		if (density < world.getMinDensity()) { std::cout << "Density is too small. Min density is " << world.getMinDensity() << std::endl; }
		if (density > world.getMaxDensity()) { std::cout << "Density is too big. Max density is " << world.getMaxDensity() << std::endl; }*/

		float restitution = vecMath.Clamp(rb.restitution, 0.f, 1.f);
		restitution = vecMath.Clamp(restitution, 0.f, 1.f);
		float mass = (area * rb.density) / 1000;

		rb.InitValues(transform->position, mass, restitution, area);

		return true;
	}
	else
	{
		std::cout << "Problème d'initialisation component SphereCollider" << std::endl;
		std::cout << "You need to addComponent the Rigidbody before SphereCollider" << std::endl;
		std::cout << "You need to addComponent the Transform before SphereCollider" << std::endl;
		return false;
	}
}