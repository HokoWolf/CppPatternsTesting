#include "GUI.h"

GUI::GUI(sf::RenderWindow* _window)
{
	window = _window;
	window->setFramerateLimit(120);

	background_color = sf::Color::White;

	icon = new sf::Image();
	icon->loadFromFile("img/icon.png");
	window->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());

	help_img = new sf::Texture();
	help_img->loadFromFile("img/help2.png");

	help_menu = new sf::Sprite();
	help_menu->setTexture(*help_img, false);

	font_heading = new sf::Font();
	font_heading->loadFromFile("fonts/Roboto/Roboto-Bold.ttf");

	font_regular = new sf::Font();
	font_regular->loadFromFile("fonts/Roboto/Roboto-Medium.ttf");

	main_label = new sf::Text();
	main_label->setString("HELLO");
	main_label->setFont(*font_heading);
	main_label->setCharacterSize(30);
	main_label->setFillColor(sf::Color::Black);
	main_label->setPosition((window->getSize().x - main_label->getGlobalBounds().width) / 2, 24);
	main_label->setLetterSpacing(1);
	main_label->setLineSpacing(1);
	main_label->setOutlineThickness(0);
	main_label->setScale(1, 1);

	status_label = new sf::Text();
	status_label->setString("HELLO");
	status_label->setFont(*font_regular);
	status_label->setCharacterSize(20);
	status_label->setFillColor(sf::Color::Black);
	status_label->setPosition(24, window->getSize().y - status_label->getGlobalBounds().height - 24);
	status_label->setLetterSpacing(1);
	status_label->setLineSpacing(1);
	status_label->setOutlineThickness(0);
	status_label->setScale(1, 1);

	help_label = new sf::Text();
	help_label->setString("HELLO");
	help_label->setFont(*font_regular);
	help_label->setCharacterSize(16);
	help_label->setFillColor(sf::Color::Black);
	help_label->setPosition(window->getSize().x - help_label->getGlobalBounds().width - 24,
		window->getSize().y - help_label->getGlobalBounds().height - 24);
	help_label->setLetterSpacing(1);
	help_label->setLineSpacing(1);
	help_label->setOutlineThickness(0);
	help_label->setScale(1, 1);

	auto_moving_label = new sf::Text();
	auto_moving_label->setString("HELLO");
	auto_moving_label->setFont(*font_regular);
	auto_moving_label->setCharacterSize(16);
	auto_moving_label->setFillColor(sf::Color::Black);
	auto_moving_label->setPosition(24, window->getSize().y - status_label->getGlobalBounds().height
		- auto_moving_label->getGlobalBounds().height - 48);
	auto_moving_label->setLetterSpacing(1);
	auto_moving_label->setLineSpacing(1);
	auto_moving_label->setOutlineThickness(0);
	auto_moving_label->setScale(1, 1);

	trail_moving_label = new sf::Text();
	trail_moving_label->setString("HELLO");
	trail_moving_label->setFont(*font_regular);
	trail_moving_label->setCharacterSize(16);
	trail_moving_label->setFillColor(sf::Color::Black);
	trail_moving_label->setPosition(24, window->getSize().y - status_label->getGlobalBounds().height
		- trail_moving_label->getGlobalBounds().height
		- auto_moving_label->getGlobalBounds().height - 60);
	trail_moving_label->setLetterSpacing(1);
	trail_moving_label->setLineSpacing(1);
	trail_moving_label->setOutlineThickness(0);
	trail_moving_label->setScale(1, 1);

	this->set_main_label_text("< Create new Figure >");
	this->set_status_label_text("Still waiting...");
	this->set_help_label_text("Press Esc or F1 to call Help");
	trail_moving_label->setString("");
	auto_moving_label->setString("");

	this->clear();
	this->draw();
	this->display();
}

GUI::~GUI() {}


sf::RenderWindow* GUI::get_window()
{
	return this->window;
}

void GUI::set_window(sf::RenderWindow*)
{
	this->window = window;
}


sf::Color GUI::get_background_color()
{
	return this->background_color;
}

void GUI::set_background_color(sf::Color color)
{
	this->background_color = color;
}


void GUI::set_main_label_text(const sf::String& text)
{
	main_label->setString(text);
	main_label->setPosition((window->getSize().x - main_label->getGlobalBounds().width) / 2, 24);
}

void GUI::set_status_label_text(const sf::String& text)
{
	status_label->setString(text);
}

void GUI::set_help_label_text(const sf::String& text)
{
	help_label->setString(text);
	help_label->setPosition(window->getSize().x - help_label->getGlobalBounds().width - 24,
		window->getSize().y - help_label->getGlobalBounds().height - 24);
}

void GUI::set_trail_moving_label_text(const sf::String& text)
{
	trail_moving_label->setString(text);
}

void GUI::set_auto_moving_label_text(const sf::String& text)
{
	auto_moving_label->setString(text);
}


bool GUI::is_help_menu_enabled()
{
	return help_menu_flag;
}

void GUI::flag_help_menu()
{
	help_menu_flag = !help_menu_flag;
}


void GUI::draw()
{
	if (!help_menu_flag)
	{
		window->draw(*main_label);
		window->draw(*status_label);
		window->draw(*help_label);
		window->draw(*trail_moving_label);
		window->draw(*auto_moving_label);
	}
	else
	{
		window->draw(*help_menu);
	}
}

void GUI::display()
{
	window->display();
}

void GUI::clear()
{
	window->clear(background_color);
}
