#pragma once
#include "GUI.h"
#include "Controller.h"
#include "MementoHandler.h"

class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	void poll_event(GUI& gui, const sf::Event& event);
	void action_event(GUI& gui);

private:
	MementoHandler* memento_handler;

	sf::Clock* timer;
	sf::VertexArray trail;
	bool is_composite_mode_active = false;
};