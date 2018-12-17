#include "Header.h"
#include "Actor.h"
#include "Player.h"
#include "ListNode.h"
#include "Enemies.h"

using namespace sf;

int randNum(int min, int max) {// creates random
	int x = rand() % (max - min + 1);
	return x;
}
int main()
{
	srand(time(NULL));
	const float FPS = 300.0f; //The desired FPS. (The number of updates each second).
	const float TIMETODESPAWN = 6.5;
	const float BULLETSPEED = 7; // Bullet speed
	const float lockON = 5;
	const int SCREENX = 1920;
	const int SCREENY = 1080;

	RenderWindow window(VideoMode(SCREENX, SCREENY, 32), "Hello");
	window.setFramerateLimit(FPS);

	CircleShape circle(10.0f);
	circle.setOrigin(0, 0);
	circle.setPosition(0, 0);

	myList<Bullet> * bulletList = new myList<Bullet>();
	myList<Monster> * monsterList = new myList<Monster>();

	Event event;
	bool dKey = false;
	bool aKey = false;
	bool wKey = false;
	bool sKey = false;
	bool mousePress = false;
	int counter = 0;

	sf::Font font;
	if (!font.loadFromFile("mainFont.ttf"));
	sf::Text text;
	text.setFont(font);

	sf::Texture texture;
	sf::Texture crosshair;
	sf::Texture bullet1;
	sf::Texture monster;
	texture.loadFromFile("ball.png");
	crosshair.loadFromFile("crosshair.png");
	bullet1.loadFromFile("bullet.png");
	monster.loadFromFile("monster.png");
	sf::Sprite sprite(texture);// loads sprite for the main player
	sf::Sprite crosshairSprite(crosshair);
	sf::Sprite bulletSprite(bullet1);
	sf::Sprite monsterSprite(monster);
	

	Player mainPlayer(sprite, SCREENX/2, SCREENY/2);// initializes the main player

	crosshairSprite.setOrigin(10, 10);// set x,y coordinates to the center of the cross-hair image

	window.setMouseCursorVisible(false);
	while (window.isOpen())
	{
		//int x = rand() % min + max;
		int shouldSpawn = randNum(0, 1920);
		int shouldSpawn2 = randNum(0, 1080);

		if (shouldSpawn < 30) {
			Monster testMonster(monsterSprite,shouldSpawn,shouldSpawn2);
			//monsterList->insertAtFront(testMonster);
		}

		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;
		Vector2f playerPosition = mainPlayer.sprite.getPosition();

		//std::string temp999 = std::to_string(mouseX) + "\n";
		//OutputDebugStringA(temp999.c_str());
		//Handle events
		while (window.pollEvent(event))// main game loop
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::D) {
					dKey = true;
				}
				if (event.key.code == sf::Keyboard::A) {
					aKey = true;
				}
				if (event.key.code == sf::Keyboard::S) {
					sKey = true;
				}
				if (event.key.code == sf::Keyboard::W) {
					wKey = true;
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::D) {
					dKey = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					aKey = false;
				}

				if (event.key.code == sf::Keyboard::S) {
					sKey = false;
				}
				if (event.key.code == sf::Keyboard::W) {
					wKey = false;
				}
			}
			if (event.type == Event::Closed) window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				mousePress = true;
				
				Monster testMonster(monsterSprite, mouseX, mouseY);
				std::cout << "Hello";
				
				//monsterList->insertAtFront(testMonster);
				//monsterList.push_front(testMonster);
				
				//text.setString(int 1);
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				mousePress = false;
				counter = 0;
			}
		}
		
		if (mousePress == true) {
			
			if (counter % 1 == 0) {
				counter = 0;
				Vector2f mousePos(mouseX, mouseY);
				Bullet bullet(bulletSprite, playerPosition, mousePos);
				bulletList->insertAtFront(bullet);
				float toRotate = bullet.angle;
				mainPlayer.setRotate(toRotate);
				
			}
			counter++;
		}
		int listLength = bulletList->length;
		if (bulletList->pHead != NULL) {// checks last bullet in the list to see if it should be destroyed based on how long its been present in the scene
			ListNode<Bullet> * checker = bulletList->getEndOfList();
			if (checker->object.framesAlive > FPS*TIMETODESPAWN ) {
				bulletList->deleteLastNode();
			}
		}
		if (monsterList->length > 0) {
			ListNode<Bullet> * tempBulletCollision = bulletList->pHead;// this block of code checks if a bullet intersects with an enemy and deletes the bullet, 
			while (tempBulletCollision != NULL) {					   //while also applying damage to the enemy and deleting it if its health is at or below 0
				FloatRect bulletBoundingBox = tempBulletCollision->object.sprite.getGlobalBounds();
				ListNode<Monster> * tempMonsterCollision = monsterList->pHead;
				while (tempMonsterCollision != NULL) {
					FloatRect monsterBoundingBox = tempMonsterCollision->object.sprite.getGlobalBounds();
					if (bulletBoundingBox.intersects(monsterBoundingBox)) {
						bulletList->deleteNode(tempBulletCollision);
						tempBulletCollision = bulletList->pHead;
						tempMonsterCollision->object.health -= mainPlayer.damage;

						if (tempMonsterCollision->object.health <= 0) {
							monsterList->deleteNode(tempMonsterCollision);
							break;// don't continue loop if monster was deleted
						}
						break;// don't continue loop if bullet was deleted
					}
					tempMonsterCollision = tempMonsterCollision->next;
				}

				if (tempBulletCollision != NULL) {
					tempBulletCollision = tempBulletCollision->next;
				}

			}
		}


		window.clear(Color(0, 0, 0));// clears screen to background color at the moment

		// Update Positions

		crosshairSprite.setPosition(mouseX, mouseY);
		if (dKey == true) {// sets key bools to true when key is released
			if (playerPosition.x < SCREENX) {
				mainPlayer.move(5, 0);
			}
		}
		if (aKey == true) {
			if (playerPosition.x > 0) {
				mainPlayer.move(-5, 0);
			}
		}
		if (sKey == true) {
			if (playerPosition.y < SCREENY) {
				mainPlayer.move(0, 5);
			}
		}
		if (wKey == true) {
			if (playerPosition.y > 0) {
				mainPlayer.move(0, -5);
			}
		}

		
		if (bulletList->length > 0) {// updates and draws every bullet
			ListNode<Bullet> * tempP = bulletList->pHead;
			while (tempP != NULL) {
				Bullet & tempBullet = tempP->object;
				
				
				float constant = .1*(log2(-1*(tempBullet.framesAlive)+150));
				float constant2 = .01*(pow(2, (-1 / 10)*tempBullet.framesAlive + 5));
				float constant3 = pow(.99,tempBullet.framesAlive);

				float SlopeX = mouseX - tempBullet.x;
				float SlopeY = mouseY - tempBullet.y;
				sf::Vector2f normal;
				normal.y = SlopeY;
				normal.x = SlopeX;
				sf::Vector2f finalV = normalizeV(normal);
				
				// need to use reference so that functions apply to bullets in the list and not a copy of bullet
				if (constant != 0) {
					tempBullet.move(tempBullet.direction.x*BULLETSPEED*constant3+finalV.x*lockON, tempBullet.direction.y*BULLETSPEED*constant3+ finalV.y*lockON);
				}
				tempBullet.draw(window);
				tempBullet.addFrame();
				tempP = tempP->next;	
			}
		}

		
		if (monsterList->length > 0) {//updates and draws every monster
			ListNode<Monster>* tempForIteration = monsterList->pHead;
			while (tempForIteration != NULL) {
				Monster & tempMonster = tempForIteration->object;
				tempMonster.setDirection(playerPosition);
				tempMonster.move(tempMonster.direction.x, tempMonster.direction.y);
				tempMonster.draw(window);
				tempForIteration = tempForIteration->next;
			}
		}



	

		//mainPlayer.draw(window);// draws main player
		window.draw(text);

		//////These need to be drawn last
		window.draw(crosshairSprite);// draws cross hair
		window.display();//displays screen
	}

	return 0;
}