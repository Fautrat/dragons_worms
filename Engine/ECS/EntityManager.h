#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "../Physics/World.h"
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

protected:
	std::vector<std::unique_ptr<Entity>> entities;
	std::unique_ptr<World> worldPtr = std::make_unique<World>();
};