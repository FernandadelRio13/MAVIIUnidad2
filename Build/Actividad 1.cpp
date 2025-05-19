#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(4.0f, 10.0f);
    b2Body* dynamicBody = world.CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    dynamicBody->CreateFixture(&fixtureDef);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(4.0f, 0.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(10.0f, 1.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Caída del bloque");

    sf::RectangleShape block(sf::Vector2f(2.0f * 30.0f, 2.0f * 30.0f));
    block.setFillColor(sf::Color::Red);
    block.setOrigin(30.0f, 30.0f);

    sf::RectangleShape ground(sf::Vector2f(20.0f * 30.0f, 2.0f * 30.0f));
    ground.setFillColor(sf::Color::Blue);
    ground.setOrigin(300.0f, 30.0f);
    ground.setPosition(4.0f * 30.0f, 600 - 0.0f * 30.0f);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Step(1.0f / 60.0f, 8, 3);

        b2Vec2 pos = dynamicBody->GetPosition();
        float angle = dynamicBody->GetAngle();

        block.setPosition(pos.x * 30.0f, 600 - pos.y * 30.0f);
        block.setRotation(-angle * 180.0f / b2_pi);

        window.clear();
        window.draw(ground);
        window.draw(block);
        window.display();
    }

    return 0;
}