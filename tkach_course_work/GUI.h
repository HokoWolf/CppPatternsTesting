#pragma once
#include "SFML/Graphics.hpp"

class GUI
{
public:
	GUI(sf::RenderWindow* window);
	~GUI();

	sf::RenderWindow* get_window();
	void set_window(sf::RenderWindow*);

	sf::Color get_background_color();
	void set_background_color(sf::Color color);
	
	void set_main_label_text(const sf::String& text);
	void set_status_label_text(const sf::String& text);
	void set_help_label_text(const sf::String& text);
	void set_trail_moving_label_text(const sf::String& text);
	void set_auto_moving_label_text(const sf::String& text);

	void flag_help_menu();
	bool is_help_menu_enabled();

	void draw();
	void display();
	void clear();


private:
	sf::RenderWindow* window;
	sf::Image* icon;
	sf::Color background_color;

	sf::Texture* help_img;
	sf::Sprite* help_menu;
	bool help_menu_flag = false;

	sf::Text* main_label;
	sf::Text* status_label;
	sf::Text* help_label;
	sf::Text* trail_moving_label;
	sf::Text* auto_moving_label;

	sf::Font* font_heading;
	sf::Font* font_regular;
};

