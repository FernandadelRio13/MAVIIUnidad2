#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    const float PIXELS_PER_METER = 30.0f;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(13.0f, 2.0f);
    b2Body* ground = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(13.0f, 0.5f);

    b2FixtureDef groundFixture;
    groundFixture.shape = &groundBox;
    groundFixture.friction = 0.5f;
    ground->CreateFixture(&groundFixture);

    b2BodyDef boxDef;
    boxDef.type = b2_dynamicBody;
    boxDef.position.Set(13.0f, 5.0f);
    b2Body* box = world.CreateBody(&boxDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1.0f, 1.0f);

    b2FixtureDef boxFixture;
    boxFixture.shape = &boxShape;
    boxFixture.density = 1.0f;
    boxFixture.friction = 0.5f;
    box->CreateFixture(&boxFixture);

    b2BodyDef leftWallDef;
    leftWallDef.position.Set(0.0f, 6.0f);
    b2PolygonShape leftWallShape;
    leftWallShape.SetAsBox(0.5f, 10.0f);
    b2Body* leftWall = world.CreateBody(&leftWallDef);
    leftWall->CreateFixture(&leftWallShape, 0.0f);

    b2BodyDef rightWallDef;
    rightWallDef.position.Set(26.0f, 6.0f);
    b2PolygonShape rightWallShape;
    rightWallShape.SetAsBox(0.5f, 10.0f);
    b2Body* rightWall = world.CreateBody(&rightWallDef);
    rightWall->CreateFixture(&rightWallShape, 0.0f);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Caja deslizándose con fricción");
    window.setFramerateLimit(60);

    sf::RectangleShape boxRect(sf::Vector2f(2.0f * PIXELS_PER_METER, 2.0f * PIXELS_PER_METER));
    boxRect.setFillColor(sf::Color::Blue);
    boxRect.setOrigin(PIXELS_PER_METER, PIXELS_PER_METER);

    sf::RectangleShape groundRect(sf::Vector2f(26.0f * PIXELS_PER_METER, 1.0f * PIXELS_PER_METER));
    groundRect.setFillColor(sf::Color(150, 75, 0));
    groundRect.setOrigin(13.0f * PIXELS_PER_METER, 0.5f * PIXELS_PER_METER);
    groundRect.setPosition(13.0f * PIXELS_PER_METER, SCREEN_HEIGHT - 2.0f * PIXELS_PER_METER);

    sf::RectangleShape leftWallRect(sf::Vector2f(1.0f * PIXELS_PER_METER, 20.0f * PIXELS_PER_METER));
    leftWallRect.setFillColor(sf::Color::Black);
    leftWallRect.setOrigin(0.5f * PIXELS_PER_METER, 10.0f * PIXELS_PER_METER);
    leftWallRect.setPosition(0.0f * PIXELS_PER_METER, SCREEN_HEIGHT - 6.0f * PIXELS_PER_METER);

    sf::RectangleShape rightWallRect = leftWallRect;
    rightWallRect.setPosition(26.0f * PIXELS_PER_METER, SCREEN_HEIGHT - 6.0f * PIXELS_PER_METER);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            box->ApplyForceToCenter(b2Vec2(50.0f, 0.0f), true);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            box->ApplyForceToCenter(b2Vec2(-50.0f, 0.0f), true);
        }

        world.Step(1.0f / 60.0f, 8, 3);

        b2Vec2 pos = box->GetPosition();
        float angle = box->GetAngle();
        boxRect.setPosition(pos.x * PIXELS_PER_METER, SCREEN_HEIGHT - pos.y * PIXELS_PER_METER);
        boxRect.setRotation(-angle * 180.0f / b2_pi);

        window.clear(sf::Color::White);
        window.draw(groundRect);
        window.draw(leftWallRect);
        window.draw(rightWallRect);
        window.draw(boxRect);
        window.display();
    }

    return 0;
}