#include "Game.h"


using namespace sf;
using namespace std;




int main()
{
	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "FRANK");

	Game game;
	game.Init(window);

	Clock clock;

	// Start the game loop 
	while (window.isOpen())
	{
		// Process events
			//Event event;
			//while (window.pollEvent(event))
			//{
			//	// Close window: exit
			//	if (event.type == Event::Closed)
			//	{
			//		window.close();
			//	}
			//}

		// Clear screen
		window.clear();

		float elapsed = clock.getElapsedTime().asSeconds();
		clock.restart();
		game.Update(window, elapsed);
		game.Render(window, elapsed);
		
		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
