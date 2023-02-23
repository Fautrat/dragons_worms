#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"

class Entity;

class EntityManager {
public:
	EntityManager() = default;
	~EntityManager() = default;

	void draw(sf::RenderTarget* renderwindow);
	void update(const float& deltaTime);
	void refresh();

	void addEntity(Entity* player);
	void eraseEntity(Entity* player);
	Entity* cloneEntity(Entity* player);

private:
	std::vector<std::unique_ptr<Entity>> entities;


};