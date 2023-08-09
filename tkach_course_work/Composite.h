#pragma once
#include "Figure.h"
#include "Circle.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Square.h"
#include "Triangle.h"

#include <vector>
#include <algorithm>

class Composite : public Figure
{
public:
	Composite();
	Composite(Figure* figure);
	~Composite();

	void add_figure(Figure* figure);
	void remove_figure(Figure* figure);

	void hide() override;
	void show() override;

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

	void move(float move_x, float move_y) override;
	void auto_move(float elapsed_time) override;
	void draw(sf::RenderWindow& window) override;

	friend class Controller;

	// Prototype:
	Figure* clone() override;

	// Memento
	const std::string serialize() override;
	static Figure* deserialize(std::string object_info);


private:
	std::vector<Figure*> figures;

	sf::Vector2f composite_scale;
	float composite_angle;

	sf::Color get_color() override { return sf::Color::White; };
	void set_color(sf::Color color) override {};
	void reset() override {};

	sf::Color get_outline_color() override { return sf::Color::Black; };
	float get_outline_thickness() override { return 0.0f; };
	void set_outline(sf::Color color, float thickness) override {};
};
