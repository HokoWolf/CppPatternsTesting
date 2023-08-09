#include "Figure.h"

bool Figure::get_trail_movement()
{
	return trail_movement;
}

void Figure::set_trail_movement(bool trail_move)
{
	trail_movement = trail_move;
}

bool Figure::get_auto_movement()
{
	return auto_movement;
}

void Figure::set_auto_movement(bool auto_move)
{
	this->auto_movement = auto_move;
}


bool Figure::is_visible()
{
	return visible;
}

void Figure::hide()
{
	sf::Color color = this->get_color();
	this->set_color(sf::Color(color.r, color.g, color.b, 0));

	outline_color = this->get_outline_color();
	outline_thickness = this->get_outline_thickness();
	this->set_outline(sf::Color::Black, 0.0f);

	visible = false;
}

void Figure::show()
{
	sf::Color color = this->get_color();
	this->set_color(sf::Color(color.r, color.g, color.b, 255));

	this->set_outline(outline_color, outline_thickness);

	visible = true;
}


void Figure::auto_move(float elapsed_time)
{
	this->move(cos(elapsed_time - 1) + 1, sin(elapsed_time));
}
