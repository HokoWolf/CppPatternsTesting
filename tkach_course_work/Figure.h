#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

enum FigureType
{
	CircleType,
	PolygonType,
	RectangleType,
	SquareType,
	TriangleType,
	CompositeType
};


class Figure
{
public:
	virtual ~Figure() {};

	bool get_trail_movement();
	void set_trail_movement(bool trail_move);

	bool get_auto_movement();
	void set_auto_movement(bool auto_move);

	bool is_visible();
	virtual void hide();
	virtual void show();

	virtual sf::FloatRect get_global_bounds() = 0;
	virtual bool check_intersection(Figure* figure) = 0;
	virtual bool check_intersection(float x, float y) = 0;
	virtual bool check_window_collision(sf::RenderWindow& window) = 0;

	virtual sf::Vector2f get_position() = 0;
	virtual void set_position(float x, float y) = 0;
	virtual sf::Vector2f get_scale() = 0;
	virtual void set_scale(float x, float y) = 0;
	virtual float get_rotation() = 0;
	virtual void set_rotation(float angle) = 0;

	virtual sf::Color get_color() = 0;
	virtual void set_color(sf::Color color) = 0;
	virtual sf::Color get_outline_color() = 0;
	virtual float get_outline_thickness() = 0;
	virtual void set_outline(sf::Color color, float thickness) = 0;

	virtual void reset() = 0;
	
	virtual void move(float move_x, float move_y) = 0;
	virtual void auto_move(float elapsed_time);
	virtual void draw(sf::RenderWindow& window) = 0;

	// Prototype
	virtual Figure* clone() = 0;

	// Memento
	virtual const std::string serialize() = 0;


protected:
	sf::Color default_color;

	sf::Color outline_color;
	float outline_thickness;

	bool visible = true;
	bool trail_movement = false;
	bool auto_movement = false;
};
