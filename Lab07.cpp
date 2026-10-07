#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h> 
//2.3.2 version
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));
	
	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 300));
	ball.setRadius(30);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(0.7,0.7));


	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setFillColor(Color(200, 300, 200));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	
	// Create walls
	PhysicsRectangle leftwall;
	leftwall.setSize(Vector2f(20, 560));
	leftwall.setCenter(Vector2f(10, 300));
	leftwall.setFillColor(Color(255, 100, 200));
	leftwall.setStatic(true);
	world.AddPhysicsBody(leftwall);
	leftwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	PhysicsRectangle rightwall;
	rightwall.setSize(Vector2f(20, 560));
	rightwall.setCenter(Vector2f(790, 300));
	rightwall.setFillColor(Color(255, 150, 150));
	rightwall.setStatic(true);
	world.AddPhysicsBody(rightwall);
	rightwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	// Create the roof
	PhysicsRectangle roof;
	roof.setSize(Vector2f(800, 20));
	roof.setCenter(Vector2f(400, 10));
	roof.setFillColor(Color(200, 150, 100));
	roof.setStatic(true);
	world.AddPhysicsBody(roof);
	roof.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	// Create the middle platform
	PhysicsRectangle middle;
	middle.setSize(Vector2f(300, 30));
	middle.setCenter(Vector2f(400, 400));
	middle.setFillColor(Color(250, 100, 250));
	middle.setStatic(true);
	world.AddPhysicsBody(middle);
	int bangCount(0);
	middle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "BANG " << bangCount << endl;
		bangCount++;
		if (bangCount == 3) {
			exit(0);
		}
		};


	Clock clock;
	
	Time lastTime(clock.getElapsedTime());
	

	
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(20, 20, 20));
		window.draw(ball);
		window.draw(floor);
		window.draw(leftwall);
		window.draw(rightwall);
		window.draw(roof);
		window.draw(middle);
		window.display();
	}
}
