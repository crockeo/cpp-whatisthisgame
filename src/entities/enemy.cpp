#include "enemy.hpp"

//////////////
// Includes //
#include "bulletcontroller.hpp"
#include "enemycontroller.hpp"

//////////
// Code //

// Creating a new enemy centered on an x & y coordinate with a given size.
Enemy::Enemy(float x, float y, float size, int index, void* controller) :
        Entity(Rectangle(x - size / 2,
                         y - size / 2,
                         size,
                         size)) {
    this->index = index;
    this->controller = controller;
}

// Updating this enemy.
void Enemy::update(GLFWwindow* window, const GameState& gs, float dt) {
    EnemyController* ec = (EnemyController*)this->controller;
    this->position().x -= Enemy::speed * dt;
    if (this->position().x < -this->position().w)
        ec->mark(this->index);

    BulletController* bc = (BulletController*)gs.getEntity("bulletcontroller");
    std::vector<Rectangle> rectangles = bc->getCollisionRectangles();

    for (auto it = rectangles.begin(); it != rectangles.end(); it++)
        if (this->position().collides(*it))
            ec->mark(this->index);
}
