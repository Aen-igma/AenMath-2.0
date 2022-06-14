#include"AenMath.h"
#include<SFML\Graphics.hpp>

#define PRINT(x) std::cout << x
#define END std::cout << std::endl


int main() {

 //   float AAng = 0.f;
 //   Aen::Vec2f APos(0.f, 0.f);
 //   Aen::Vec2f ASize(1.f, 1.f);
 //   Aen::Vec2f AOffset(0.5f, 0.5f);
 //   Aen::Vec2f dir = Aen::Vec2f(2.f, -1.f).Normalized();
 //   Aen::Vec2f p;

 //   Aen::Vec2f CPos(0.f, 0.f);

 //   sf::RectangleShape RA;
 //   sf::RectangleShape ray;
 //   sf::RectangleShape normal;
 //   sf::CircleShape circle;
 //   sf::CircleShape dot;
 //   dot.setFillColor(sf::Color::Red);
 //   dot.setOrigin(2.f, 2.f);
 //   dot.setRadius(2.f);
 //   
 //   normal.setFillColor(sf::Color::Yellow);
 //   normal.setSize(sf::Vector2f(10.f, 2.f));
 //   normal.setOrigin(0.f, 1.f);

	//sf::RenderWindow window(sf::VideoMode(600, 400), "window");
 //   sf::Vector2f size(window.getSize());

 //   sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(size.x, -size.y));
 //   window.setView(view);

 //   
 //    // Start the game loop
 //   while(window.isOpen()) {
 //       // Process events
 //       sf::Event event;
 //       while(window.pollEvent(event)) {
 //           // Close window: exit
 //           if(event.type == sf::Event::Closed)
 //               window.close();

 //           if(event.type == sf::Event::MouseWheelMoved)
 //               AAng += event.mouseWheelScroll.wheel * 5.f;
 //       }

 //       if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
 //           p.x = (sf::Mouse::getPosition(window).x - 300.f) / 50.f;
 //           p.y = -(sf::Mouse::getPosition(window).y - 200.f) / 50.f;
 //           dir = p - Aen::Vec2f(-2.f, 2.f);
 //       }

 //       if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
 //           APos.x = (sf::Mouse::getPosition(window).x - 300.f) / 50.f;
 //           APos.y = -(sf::Mouse::getPosition(window).y - 200.f) / 50.f;
 //       }

 //       if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
 //           CPos.x = (sf::Mouse::getPosition(window).x - 300.f) / 50.f;
 //           CPos.y = -(sf::Mouse::getPosition(window).y - 200.f) / 50.f;
 //       }

 //       Aen::Tracer2 tracer(Aen::Vec2f(-2.f, 2.f), dir.Normalized());
 //       Aen::ORect a(APos, ASize, AAng);
 //       Aen::Circle c(CPos, 0.5f);
 //       a.offset = AOffset;

 //       RA.setSize(sf::Vector2f(a.size.x, a.size.y) * 50.f);
 //       RA.setPosition(a.origin.x * 50.f, a.origin.y * 50.f);
 //       RA.setOrigin(a.offset.x * 50.f, a.offset.y * 50.f);
 //       RA.setRotation(a.rot);
 //      
 //       circle.setPosition(c.origin.x * 50.f, c.origin.y * 50.f);
 //       circle.setOrigin(c.radius * 50.f, c.radius * 50.f);
 //       circle.setRadius(c.radius * 50.f);
 //       
 //       float rRot = Aen::RadToDeg(std::atan2f(tracer.GetDirection().y, tracer.GetDirection().x));
 //       ray.setOrigin(0.f, 1.f);
 //       ray.setRotation(rRot);

 //       if(Aen::Intersect(c, tracer)) {
 //           circle.setFillColor(sf::Color::White);
 //           ray.setFillColor(sf::Color::White);

 //           ray.setPosition(tracer.GetOrigin().x * 50.f, tracer.GetOrigin().y * 50.f);
 //           ray.setSize(sf::Vector2f(tracer.GetDistance() * 50.f, 2.f));

 //           dot.setPosition(tracer.GetHitPos().x * 50.f, tracer.GetHitPos().y * 50.f);

 //           float nAng = Aen::RadToDeg(std::atan2f(tracer.GetHitNormal().y, tracer.GetHitNormal().x));
 //           normal.setPosition(tracer.GetHitPos().x * 50.f, tracer.GetHitPos().y * 50.f);
 //           normal.setSize(sf::Vector2f(tracer.GetHitNormal().Magnitude() * 10.f, 2.f));
 //           normal.setRotation(nAng);

 //       } else {
 //           ray.setFillColor(sf::Color::Red);
 //           circle.setFillColor(sf::Color::Blue);
 //       }

 //       if(Aen::Intersect(tracer, a)) {
 //           RA.setFillColor(sf::Color::White);
 //           ray.setFillColor(sf::Color::White);

 //           float rRot = Aen::RadToDeg(std::atan2f(tracer.GetDirection().y, tracer.GetDirection().x));
 //           ray.setPosition(tracer.GetOrigin().x * 50.f, tracer.GetOrigin().y * 50.f);
 //           ray.setSize(sf::Vector2f(tracer.GetDistance() * 50.f, 2.f));

 //           dot.setPosition(tracer.GetHitPos().x * 50.f, tracer.GetHitPos().y * 50.f);

 //           float nAng = Aen::RadToDeg(std::atan2f(tracer.GetHitNormal().y, tracer.GetHitNormal().x));
 //           normal.setPosition(tracer.GetHitPos().x * 50.f, tracer.GetHitPos().y * 50.f);
 //           normal.setSize(sf::Vector2f(tracer.GetHitNormal().Magnitude() * 10.f, 2.f));
 //           normal.setRotation(nAng);

 //       } else { 
 //           ray.setFillColor(sf::Color::Red);
 //           RA.setFillColor(sf::Color::Blue);
 //       }

 //       window.clear();
 //       
 //       window.draw(RA);
 //       window.draw(ray);
 //       window.draw(dot);
 //       window.draw(circle);
 //       window.draw(normal);

 //       window.display();
 //   }
    return 0;
}