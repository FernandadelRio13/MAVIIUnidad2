#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    const float PIXELS_PER_METER = 30.0f;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    b2BodyDef ballDef;
    ballDef.type = b2_dynamicBody;
    ballDef.position.Set(10.0f, 10.0f);
    b2Body* ball = world.CreateBody(&ballDef);

    b2CircleShape shape;
    shape.m_radius = 1.0f;

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.restitution = 1.0f;
    fixture.friction = 0.0f;
    ball->CreateFixture(&fixture);

    b2BodyDef wallDef;
    b2PolygonShape wallShape;
    b2Body* wall;

    wallShape.SetAsBox(13.0f, 0.5f);
    wallDef.position.Set(13.0f, 0.0f);
    wall = world.CreateBody(&wallDef);
    wall->CreateFixture(&wallShape, 0.0f);
    wallDef.position.Set(13.0f, 20.0f);
    wall = world.CreateBody(&wallDef);
    wall->CreateFixture(&wallShape, 0.0f);

    wallShape.SetAsBox(0.5f, 10.0f);
    wallDef.position.Set(0.0f, 10.0f);
    wall = world.CreateBody(&wallDef);
    wall->CreateFixture(&wallShape, 0.0f);
    wallDef.position.Set(26.0f, 10.0f);
    wall = world.CreateBody(&wallDef);
    wall->CreateFixture(&wallShape, 0.0f);

    b2BodyDef obstacleDef;
    obstacleDef.position.Set(13.0f, 10.0f);
    b2PolygonShape obstacleShape;
    obstacleShape.SetAsBox(2.0f, 0.5f);
    b2Body* obstacle1 = world.CreateBody(&obstacleDef);
    obstacle1->CreateFixture(&obstacleShape, 0.0f);

    obstacleDef.position.Set(6.0f, 5.0f);
    obstacleShape.SetAsBox(1.5f, 0.5f);
    b2Body* obstacle2 = world.CreateBody(&obstacleDef);
    obstacle2->CreateFixture(&obstacleShape, 0.0f);

    ball->SetLinearVelocity(b2Vec2(5.0f, 4.0f));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pelota rebotando con obstaculos");
    window.setFramerateLimit(60);

    sf::CircleShape circle(shape.m_radius * PIXELS_PER_METER);
    circle.setFillColor(sf::Color::Green);
    circle.setOrigin(shape.m_radius * PIXELS_PER_METER, shape.m_radius * PIXELS_PER_METER);

    sf::RectangleShape obsRect1(sf::Vector2f(4.0f * PIXELS_PER_METER, 1.0f * PIXELS_PER_METER));
    obsRect1.setFillColor(sf::Color::Red);
    obsRect1.setOrigin(2.0f * PIXELS_PER_METER, 0.5f * PIXELS_PER_METER);
    obsRect1.setPosition(13.0f * PIXELS_PER_METER, SCREEN_HEIGHT - 10.0f * PIXELS_PER_METER);

    sf::RectangleShape obsRect2(sf::Vector2f(3.0f * PIXELS_PER_METER, 1.0f * PIXELS_PER_METER));
    obsRect2.setFillColor(sf::Color::Blue);
    obsRect2.setOrigin(1.5f * PIXELS_PER_METER, 0.5f * PIXELS_PER_METER);
    obsRect2.setPosition(6.0f * PIXELS_PER_METER, SCREEN_HEIGHT - 5.0f * PIXELS_PER_METER);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Step(1.0f / 60.0f, 8, 3);

        b2Vec2 pos = ball->GetPosition();
        circle.setPosition(pos.x * PIXELS_PER_METER, SCREEN_HEIGHT - pos.y * PIXELS_PER_METER);

        window.clear();
        window.draw(circle);
        window.draw(obsRect1);
        window.draw(obsRect2);
        window.display();
    }

    return 0;
}