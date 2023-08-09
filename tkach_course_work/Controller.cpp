#include "Controller.h"

Controller::Controller()
{
	active_figure = nullptr;
	active_composite = nullptr;
}

Controller::~Controller()
{
	figures.clear();
	temporary_container.clear();

	delete active_figure;
	delete active_composite;
}

Controller* Controller::instance = 0;

Controller* Controller::get_instance()
{
	if (instance == 0) {
		instance = new Controller();
	}
	return instance;
}


void Controller::add_figure(FigureType figure_type)
{
	switch (figure_type)
	{
	case CircleType:
		figures.push_back(new Circle(50.0f, get_random_color()));
		break;
	case PolygonType:
		figures.push_back(new Polygon(50.0f, 6, get_random_color()));
		break;
	case RectangleType:
		figures.push_back(new Rectangle(50.0f, 100.0f, get_random_color()));
		break;
	case SquareType:
		figures.push_back(new Square(100.0f, get_random_color()));
		break;
	case TriangleType:
		figures.push_back(new Triangle(50.0f, get_random_color()));
		break;
	default:
		break;
	}

	activate_figure(figures[figures.size() - 1]);
}

void Controller::remove_active_figure()
{
	if (is_empty() || !temporary_container.empty()) {
		return;
	}

	int figure_index;
	bool is_exist = get_figure_index(active_figure, figure_index);
	
	if (!is_exist) {
		return;
	}

	activate_next_figure();

	figures.erase(figures.begin() + figure_index, figures.begin() + figure_index + 1);
	
	if (is_empty())
		active_figure = nullptr;
}

bool Controller::get_figure_index(Figure* figure, int& figure_index)
{
	if (is_empty())
		return false;


	std::size_t figures_count = figures.size();

	for (int i = 0; i < figures_count; i++)
	{
		if (figures[i] == figure)
		{
			figure_index = i;
			return true;
		}
	}
	return false;
}


void Controller::activation_helper(Figure* changing_figure, bool is_activation)
{
	sf::String figure_name = typeid(*changing_figure).name();
	figure_name = figure_name.substring(6);

	if (figure_name == "Composite")
	{
		Composite* composite = dynamic_cast<Composite*>(changing_figure);

		for (int i = 0; i < composite->figures.size(); i++)
		{
			activation_helper(composite->figures[i], is_activation);
		}
	}
	else
	{
		sf::Color color = changing_figure->get_color();

		if (color.a == 0)
		{
			changing_figure->set_color(sf::Color(color.r, color.g, color.b, 0));
			changing_figure->set_outline(sf::Color::Black, 0.0f);
		}
		else
		{
			if (is_activation)
			{
				changing_figure->set_color(sf::Color(color.r, color.g, color.b, 255));
				changing_figure->set_outline(sf::Color::Black, 0.5f);
			}
			else
			{
				changing_figure->set_color(sf::Color(color.r, color.g, color.b, 125));
				changing_figure->set_outline(sf::Color::Black, 0.0f);
			}
		}
	}
}

void Controller::activate_figure(Figure* figure)
{
	if (is_empty())
		return;

	int figure_index;
	bool is_exist = get_figure_index(figure, figure_index);

	if (!is_exist) {
		return;
	}

	if (active_figure != nullptr)
	{
		activation_helper(active_figure, false);
	}

	active_figure = figure;
	activation_helper(active_figure, true);
}

void Controller::activate_next_figure()
{
	if (active_figure == figures[figures.size() - 1]) {
		activate_figure(figures[0]);
	}
	else {
		int figure_index;
		bool is_exist = get_figure_index(active_figure, figure_index);

		if (is_exist)
			activate_figure(figures[figure_index + 1]);
	}
}

void Controller::activate_previous_figure()
{
	if (active_figure == figures[0]) {
		activate_figure(figures[figures.size() - 1]);
	}
	else {
		int figure_index;
		bool is_exist = get_figure_index(active_figure, figure_index);

		if (is_exist)
			activate_figure(figures[figure_index - 1]);
	}
}


void Controller::clear()
{
	if (is_empty())
		return;

	figures.clear();
	temporary_container.clear();
	active_figure = nullptr;
	active_composite = nullptr;
}

bool Controller::is_empty()
{
	return figures.empty();
}



void Controller::set_active_figure_position(float move_x, float move_y)
{
	if (is_empty())
		return;

	active_figure->set_position(move_x, move_y);
}

void Controller::auto_move_active_figure(float elapsed_time)
{
	if (is_empty())
		return;

	active_figure->auto_move(elapsed_time);
}

void Controller::scale_active_figure(float scale_x, float scale_y)
{
	if (is_empty())
		return;

	float x = active_figure->get_scale().x + scale_x;
	float y = active_figure->get_scale().y + scale_y;

	if (x >= 0.25f && y >= 0.25f && x <= 10.0f && y <= 10.0f)
		active_figure->set_scale(x, y);
}

void Controller::rotate_active_figure(float angle)
{
	if (is_empty())
		return;

	active_figure->set_rotation(active_figure->get_rotation() + angle);
}


bool Controller::is_active_figure_visible()
{
	if (is_empty())
		return false;

	return active_figure->is_visible();
}

void Controller::hide_active_figure()
{
	if (is_empty())
		return;

	active_figure->hide();
}

void Controller::show_active_figure()
{
	if (is_empty())
		return;

	active_figure->show();
}


sf::FloatRect Controller::get_active_figure_global_bounds()
{
	if (is_empty())
		return sf::FloatRect(-1, -1, -1, -1);

	return active_figure->get_global_bounds();
}

sf::String Controller::get_active_figure_type()
{
	sf::String figure_name = typeid(*active_figure).name();
	figure_name = figure_name.substring(6);
	return figure_name;
}

bool Controller::get_active_figure_trail_movement()
{
	if (is_empty())
		return false;

	return active_figure->get_trail_movement();
}

void Controller::set_active_figure_trail_movement(bool trail_move)
{
	if (is_empty())
		return;

	active_figure->set_trail_movement(trail_move);
}

bool Controller::get_active_figure_auto_movement()
{
	if (is_empty())
		return false;

	return active_figure->get_auto_movement();
}

void Controller::set_active_figure_auto_movement(bool auto_move)
{
	if (is_empty())
		return;

	active_figure->set_auto_movement(auto_move);
}


bool Controller::check_active_figure_window_collision(GUI& gui)
{
	return active_figure->check_window_collision(*gui.get_window());
}

void Controller::intersection_change_helper(Figure* changing_figure, Figure* influence_figure)
{
	sf::String figure_name = typeid(*influence_figure).name();
	figure_name = figure_name.substring(6);

	if (figure_name == "Composite")
	{
		Composite* composite = dynamic_cast<Composite*>(influence_figure);

		for (int i = 0; i < composite->figures.size(); i++)
		{
			if (changing_figure->check_intersection(composite->figures[i]))
			{
				intersection_change_helper(changing_figure, composite->figures[i]);
				composite = nullptr;
				return;
			}
		}
	}
	else
	{
		figure_name = typeid(*changing_figure).name();
		figure_name = figure_name.substring(6);

		if (figure_name == "Composite")
		{
			Composite* composite = dynamic_cast<Composite*>(changing_figure);

			for (int i = 0; i < composite->figures.size(); i++)
			{
				if (composite->figures[i]->check_intersection(influence_figure))
				{
					intersection_change_helper(composite->figures[i], influence_figure);
					composite = nullptr;
					return;
				}
			}
		}
		else
		{
			sf::Color color = influence_figure->get_color();
			changing_figure->set_color(sf::Color(color.r, color.g, color.b));
		}
	}
}

void Controller::active_figure_intersection_change()
{
	for (int i = 0; i < figures.size(); i++)
	{
		if (active_figure != figures[i] && active_figure->check_intersection(figures[i]))
		{
			intersection_change_helper(active_figure, figures[i]);
			break;
		}
	}
}


sf::Color Controller::get_random_color()
{
	srand(time(NULL));

	sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);

	while (color.r < 10 && color.g < 10 && color.b < 10) {
		color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	}

	return color;
}

sf::Color Controller::get_active_figure_color()
{
	if (is_empty() || is_active_figure_composite())
		return sf::Color::White;

	return active_figure->get_color();
}

void Controller::set_active_figure_color(sf::Color color)
{
	if (is_empty() || is_active_figure_composite())
		return;

	active_figure->set_color(color);
}

void Controller::set_active_figure_random_color()
{
	if (is_empty() || is_active_figure_composite())
		return;

	active_figure->set_color(this->get_random_color());
}


void Controller::reset_active_figure()
{
	if (is_empty() || is_active_figure_composite())
		return;

	active_figure->reset();
	activate_figure(active_figure);
}


void Controller::draw(GUI& gui)
{
	for (int i = 0; i < figures.size(); i++)
	{
		if (figures[i] != active_figure)
		{
			figures[i]->draw(*gui.get_window());
		}
	}

	if (active_figure != nullptr)
		active_figure->draw(*gui.get_window());
}


// methods for work with composite
bool Controller::is_active_figure_composite()
{
	if (is_empty())
		return false;

	return get_active_figure_type() == "Composite";
}

void Controller::create_composite()
{
	if (is_empty())
		return;

	Figure* composite = new Composite(active_figure);
	
	int index;
	bool is_exist = get_figure_index(active_figure, index);

	figures[index] = composite;
	activate_figure(composite);
	activate_composite();
}

void Controller::activate_composite()
{
	if (is_active_figure_composite())
	{
		active_composite = dynamic_cast<Composite*>(active_figure);
	}
}

void Controller::deactivate_composite()
{
	active_composite = nullptr;

	if (temporary_container.size() > 0)
	{
		figures = temporary_container;
		temporary_container.clear();
		activate_figure(figures[0]);
	}
}

void Controller::go_inside_composite()
{
	if (active_composite != nullptr && is_active_figure_composite())
	{
		if (temporary_container.empty())
		{
			temporary_container = figures;
		}

		figures = active_composite->figures;
		activate_figure(figures[0]);
	}
}

void Controller::add_active_figure_to_composite()
{
	if (active_figure != active_composite && active_composite != nullptr)
	{
		active_composite->add_figure(active_figure);
		remove_active_figure();
		activate_figure(active_composite);
	}
}


void Controller::remove_active_figure_from_composite()
{
	if (active_figure != active_composite && !temporary_container.empty())
	{
		Figure* removed_figure = active_figure;
		temporary_container.push_back(removed_figure);

		if (figures.size() <= 1)
		{
			int figure_index = -1;

			for (int i = 0; i < temporary_container.size(); i++)
			{
				if (temporary_container[i] == active_composite)
				{
					figure_index = i;
					break;
				}
			}

			temporary_container.erase(temporary_container.begin() + figure_index);
		}

		active_composite->remove_figure(removed_figure);
		figures = active_composite->figures;

		if (figures.empty())
		{
			deactivate_composite();
		}
		else
		{
			activate_figure(figures[0]);
		}
	}
}

void Controller::delete_active_figure_from_composite()
{
	if (active_figure != active_composite)
	{
		if (figures.size() <= 1)
		{
			int figure_index = -1;

			for (int i = 0; i < temporary_container.size(); i++)
			{
				if (temporary_container[i] == active_composite)
				{
					figure_index = i;
					break;
				}
			}

			temporary_container.erase(temporary_container.begin() + figure_index);
		}

		active_composite->remove_figure(active_figure);
		figures = active_composite->figures;

		if (figures.empty())
		{
			deactivate_composite();
		}
		else
		{
			activate_figure(figures[0]);
		}
	}
}


// prototype realization
void Controller::duplicate_active_figure()
{
	if (!is_empty() && active_composite == nullptr)
	{
		figures.push_back(active_figure->clone());
		activate_figure(figures[figures.size() - 1]);
	}
}


// memento
const std::string Controller::serialize()
{
	std::stringstream str;
	int active_figure_index = -1;
	int active_composite_index = -1;
	int active_composite_container = -1;

	for (int i = 0; i < figures.size(); i++)
	{
		str << figures[i]->serialize() << std::endl;

		if (figures[i] == active_figure) {
			active_figure_index = i;
		}

		if (figures[i] == active_composite) {
			active_composite_index = i;
			active_composite_container = 1;
		}
	}

	str << '@' << std::endl;
	
	for (int i = 0; i < temporary_container.size(); i++)
	{
		str << temporary_container[i]->serialize() << std::endl;

		if (figures[i] == active_composite) {
			active_composite_index = i;
			active_composite_container = 2;
		}
	}

	str << '@' << std::endl;
	str << active_figure_index << ' ' 
		<< active_composite_index << ' '
		<< active_composite_container;

	return str.str();
}

Controller* Controller::deserialize(std::string object_info)
{
	Controller* controller = new Controller();

	std::string figure_info;
	std::stringstream object_str(object_info);

	while (std::getline(object_str, figure_info))
	{
		if (figure_info == "@") {
			break;
		}

		std::stringstream str(figure_info);
		char delimeter;
		int type;
		str >> delimeter >> type;

		FigureType fig_type = (FigureType)type;

		switch (fig_type)
		{
		case CircleType:
			controller->figures.push_back(Circle::deserialize(figure_info));
			break;
		case PolygonType:
			controller->figures.push_back(Polygon::deserialize(figure_info));
			break;
		case RectangleType:
			controller->figures.push_back(Rectangle::deserialize(figure_info));
			break;
		case SquareType:
			controller->figures.push_back(Square::deserialize(figure_info));
			break;
		case TriangleType:
			controller->figures.push_back(Triangle::deserialize(figure_info));
			break;
		case CompositeType:
			controller->figures.push_back(Composite::deserialize(figure_info));
			break;
		default:
			break;
		}
	}

	while (std::getline(object_str, figure_info))
	{
		if (figure_info == "@") {
			break;
		}

		std::stringstream str(figure_info);
		char delimeter;
		int type;
		str >> delimeter >> type;

		FigureType fig_type = (FigureType)type;

		switch (fig_type)
		{
		case CircleType:
			controller->temporary_container.push_back(Circle::deserialize(figure_info));
			break;
		case PolygonType:
			controller->temporary_container.push_back(Polygon::deserialize(figure_info));
			break;
		case RectangleType:
			controller->temporary_container.push_back(Rectangle::deserialize(figure_info));
			break;
		case SquareType:
			controller->temporary_container.push_back(Square::deserialize(figure_info));
			break;
		case TriangleType:
			controller->temporary_container.push_back(Triangle::deserialize(figure_info));
			break;
		case CompositeType:
			controller->temporary_container.push_back(Composite::deserialize(figure_info));
			break;
		default:
			break;
		}
	}

	std::getline(object_str, figure_info);

	std::stringstream str(figure_info);
	int active_figure_index;
	int active_composite_index;
	int active_composite_container;

	str >> active_figure_index
		>> active_composite_index
		>> active_composite_container;

	if (active_figure_index > -1) {
		controller->activate_figure(controller->figures[active_figure_index]);
	}

	if (active_composite_index > -1)
	{
		if (active_composite_container == 1) {
			controller->active_composite = dynamic_cast<Composite*>(
				controller->figures[active_composite_index]);
		}
		else if (active_composite_container == 2) {
			controller->active_composite = dynamic_cast<Composite*>(
				controller->temporary_container[active_composite_index]);
		}
	}

	return controller;
}

void Controller::set_memento(Memento* memento) const
{
	memento->controller_state = this->instance->serialize();
}

void Controller::get_memento(const Memento* memento)
{
	instance = this->deserialize(memento->controller_state);
}

void MementoHandler::save_state(const Controller* controller)
{
	controller->set_memento(this->memento);

	std::ofstream file(this->file_name);
	file.clear();

	if (file.is_open())
	{
		file << memento->controller_state;
	}
	file.close();
}

void MementoHandler::load_state(Controller* controller)
{
	std::ifstream file(this->file_name);
	std::stringstream stream;
	std::string str;
	
	if (file.is_open())
	{
		while (std::getline(file, str))
		{
			stream << str << std::endl;
		}
	}
	file.close();

	this->memento->controller_state = stream.str();
	controller->get_memento(this->memento);
}
