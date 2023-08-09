// tkach_course_work.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>

#include "GUI.h"
#include "Controller.h"
#include "EventHandler.h"


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1200, 720), "Tkach Course Work", sf::Style::Titlebar | sf::Style::Close, settings);
	GUI gui(&window);

	sf::Event event;
	EventHandler event_handler;

	while (gui.get_window()->isOpen())
	{
		while (gui.get_window()->pollEvent(event))
		{
			event_handler.poll_event(gui, event);
		}

		event_handler.action_event(gui);
	}
}