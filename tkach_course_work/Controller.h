#pragma once
#include "GUI.h"
#include "Composite.h"

#include "Circle.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Square.h"
#include "Triangle.h"

#include "MementoHandler.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

class Controller
{
public:
	~Controller();

	static Controller* get_instance();

	void add_figure(FigureType figure_type);
	void remove_active_figure();

	void activate_next_figure();
	void activate_previous_figure();

	void clear();
	bool is_empty();

	void set_active_figure_position(float move_x, float move_y);
	void auto_move_active_figure(float elapsed_time);
	void scale_active_figure(float scale_x, float scale_y);
	void rotate_active_figure(float angle);

	bool is_active_figure_visible();
	void hide_active_figure();
	void show_active_figure();

	sf::FloatRect get_active_figure_global_bounds();
	sf::String get_active_figure_type();
	bool get_active_figure_trail_movement();
	void set_active_figure_trail_movement(bool trail_move);
	bool get_active_figure_auto_movement();
	void set_active_figure_auto_movement(bool auto_move);

	bool check_active_figure_window_collision(GUI& gui);
	void active_figure_intersection_change();

	sf::Color get_random_color();
	sf::Color get_active_figure_color();
	void set_active_figure_color(sf::Color color);
	void set_active_figure_random_color();

	void reset_active_figure();

	void draw(GUI& gui);

	// methods for work with composite
	bool is_active_figure_composite();
	void create_composite();
	void activate_composite();
	void deactivate_composite();
	void go_inside_composite();
	void add_active_figure_to_composite();
	void remove_active_figure_from_composite();
	void delete_active_figure_from_composite();

	// prototype realization
	void duplicate_active_figure();

private:
	std::vector<Figure*> figures;
	std::vector<Figure*> temporary_container;

	Figure* active_figure;
	Composite* active_composite;


	static Controller* instance;

	Controller();

	bool get_figure_index(Figure* figure, int& figure_index);
	void activate_figure(Figure* figure);
	void activation_helper(Figure* changing_figure, bool is_activation);
	void intersection_change_helper(Figure* changing_figure, Figure* influence_figure);


	// memento
	const std::string serialize();
	static Controller* deserialize(std::string object_info);

	friend void MementoHandler::save_state(const Controller* controller);
	friend void MementoHandler::load_state(Controller* controller);

	Controller(const Controller& controller);
	void set_memento(Memento* memento) const;
	void get_memento(const Memento* memento);
};
