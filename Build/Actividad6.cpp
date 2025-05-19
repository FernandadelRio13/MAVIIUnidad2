#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

const float PIXELS_PER_METER = 30.0f;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

float cannonAngle = 45.0f;

b2World world(b2Vec2(0.0f, -9.8f));

b2Body* createProjectile(float angleDeg) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(2.0f, 2.0f);
    b2Body* projectile = world.CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = 0.2f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.4f;
    projectile->CreateFixture(&fixtureDef);

    float angleRad = angleDeg * b2_pi / 180.0f;
    float speed = 15.0f;
    projectile->SetLinearVelocity(b2Vec2(speed * cos(angleRad), speed * sin(angleRad)));

    return projectile;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Juego del Cañón");
    window.setFramerateLimit(60);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(13.0f, 0.5f);
    b2Body* ground = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(13.0f, 0.5f);
    ground->CreateFixture(&groundBox, 0.0f);

    sf::RectangleShape groundRect(sf::Vector2f(26.0f * PIXELS_PER_METER, 1.0f * PIXELS_PER_METER));
    groundRect.setOrigin(13.0f * PIXELS_PER_METER, 0.5f * PIXELS_PER_METER);
    groundRect.setPosition(13.0f * PIXELS_PER_METER, SCREEN_HEIGHT - 0.5f * PIXELS_PER_METER);
    groundRect.setFillColor(sf::Color::Green);

    sf::RectangleShape cannon(sf::Vector2f(60, 10));
    cannon.setFillColor(sf::Color::Black);
    cannon.setOrigin(0, 5);
    cannon.setPosition(2.0f * PIXELS_PER_METER, SCREEN_HEIGHT - 2.0f * PIXELS_PER_METER);

    std::vector<b2Body*> projectiles;
    std::vector<sf::CircleShape> projectileShapes;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            cannonAngle += 1.0f;
            if (cannonAngle > 80.0f) cannonAngle = 80.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            cannonAngle -= 1.0f;
            if (cannonAngle < 10.0f) cannonAngle = 10.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            b2Body* p = createProjectile(cannonAngle);
            projectiles.push_back(p);

            sf::CircleShape shape(0.2f * PIXELS_PER_METER);
            shape.setFillColor(sf::Color::Red);
            shape.setOrigin(0.2f * PIXELS_PER_METER, 0.2f * PIXELS_PER_METER);
            projectileShapes.push_back(shape);
        }

        world.Step(1.0f / 60.0f, 8, 3);

        window.clear(sf::Color::White);
        window.draw(groundRect);

        cannon.setRotation(-cannonAngle);
        window.draw(cannon);

        for (size_t i = 0; i < projectiles.size(); ++i) {
            b2Vec2 pos = projectiles[i]->GetPosition();
            projectileShapes[i].setPosition(pos.x * PIXELS_PER_METER, SCREEN_HEIGHT - pos.y * PIXELS_PER_METER);
            window.draw(projectileShapes[i]);
        }

        window.display();
    }

    return 0;
}