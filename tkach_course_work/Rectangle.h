#pragma once
#include "Figure.h"

class Rectangle : public Figure
{
public:
	Rectangle();
	Rectangle(float width, float height, sf::Color color);
	~Rectangle();

	sf::FloatRect get_global_bounds() override;
	bool check_intersection(Figure* figure) override;
	bool check_intersection(float x, float y) override;
	bool check_window_collision(sf::RenderWindow& window) override;

	sf::Vector2f get_position() override;
	void set_position(float x, float y) override;
	sf::Vector2f get_scale() override;
	void set_scale(float x, float y) override;
	float get_rotation() override;
	void set_rotation(float angle) override;

	sf::Color get_color() override;
	void set_color(sf::Color color) override;
	sf::Color get_outline_color() override;
	float get_outline_thickness() override;
	void set_outline(sf::Color color, float thickness) override;

	void reset() override;

	void move(float move_x, float move_y) override;
	void draw(sf::RenderWindow& window) override;

	// Prototype:
	Figure* clone() override;

	// Memento
	const std::string serialize() override;
	static Figure* deserialize(std::string object_info);


private:
	sf::RectangleShape* rectangle;
};
