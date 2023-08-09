#include "Composite.h"

Composite::Composite()
{
	composite_scale.x = 1.0f;
	composite_scale.y = 1.0f;
	composite_angle = 0.0f;
}

Composite::Composite(Figure* figure)
{
	figures.push_back(figure);

	composite_scale.x = 1.0f;
	composite_scale.y = 1.0f;
	composite_angle = 0.0f;
}

Composite::~Composite()
{
	figures.clear();
}


void Composite::add_figure(Figure* figure)
{
	figures.push_back(figure);
}

void Composite::remove_figure(Figure* figure)
{
	int figure_index = -1;

	for (int i = 0; i < figures.size(); i++)
	{
		if (figures[i] == figure)
		{
			figure_index = i;
			break;
		}
	}

	figures.erase(figures.begin() + figure_index);
}


void Composite::hide()
{
	for (int i = 0; i < figures.size(); i++)
	{
		figures[i]->hide();
	}
	visible = false;
}

void Composite::show()
{
	for (int i = 0; i < figures.size(); i++)
	{
		figures[i]->show();
	}
	visible = true;
}


sf::FloatRect Composite::get_global_bounds()
{
	sf::FloatRect global_bounds;
	global_bounds.left = figures[0]->get_global_bounds().left;
	global_bounds.top = figures[0]->get_global_bounds().top;
	float right = global_bounds.left + figures[0]->get_global_bounds().width;
	float bottom = global_bounds.top + figures[0]->get_global_bounds().height;

	for (int i = 1; i < figures.size(); i++)
	{
		sf::FloatRect fig_bounds = figures[i]->get_global_bounds();

		global_bounds.left = std::min(global_bounds.left, fig_bounds.left);
		global_bounds.top = std::min(global_bounds.top, fig_bounds.top);
		right = std::max(right, fig_bounds.left + fig_bounds.width);
		bottom = std::max(bottom, fig_bounds.top + fig_bounds.height);
	}

	global_bounds.width = right - global_bounds.left;
	global_bounds.height = bottom - global_bounds.top;

	return global_bounds;
}

bool Composite::check_intersection(Figure* figure)
{
	bool result = false;

	for (int i = 0; i < figures.size(); i++)
	{
		if (figures[i]->get_global_bounds().intersects(figure->get_global_bounds()));
		{
			result = true;
			break;
		}
	}

	return result;
}

bool Composite::check_intersection(float x, float y)
{
	bool result = false;

	for (int i = 0; i < figures.size(); i++)
	{
		if (figures[i]->get_global_bounds().contains(sf::Vector2f(x, y)));
		{
			result = true;
			break;
		}
	}

	return result;
}

bool Composite::check_window_collision(sf::RenderWindow& window)
{
	bool result = false;

	for (int i = 0; i < figures.size(); i++)
	{
		if (figures[i]->check_window_collision(window))
		{
			result = true;
			break;
		}
	}

	return result;
}


sf::Vector2f Composite::get_position()
{
	sf::FloatRect global_bounds = this->get_global_bounds();

	sf::Vector2f position(global_bounds.left + global_bounds.width / 2, 
		global_bounds.top + global_bounds.height / 2);

	return position;
}

void Composite::set_position(float x, float y)
{
	float move_x = x - this->get_position().x;
	float move_y = y - this->get_position().y;

	for (int i = 0; i < figures.size(); i++)
	{
		figures[i]->move(move_x, move_y);
	}
}

sf::Vector2f Composite::get_scale()
{
	return composite_scale;
}

void Composite::set_scale(float x, float y)
{
	sf::Vector2f position = get_position();

	for (int i = 0; i < figures.size(); i++)
	{
		sf::Vector2f fig_scale = figures[i]->get_scale();
		figures[i]->set_scale(x / composite_scale.x * fig_scale.x, y / composite_scale.y * fig_scale.y);

		sf::Vector2f fig_pos = figures[i]->get_position();
		float move_x = (fig_pos.x - position.x) * x / composite_scale.x
			- (fig_pos.x - position.x);
		float move_y = (fig_pos.y - position.y) * y / composite_scale.y
			- (fig_pos.y - position.y);
		figures[i]->move(move_x, move_y);
	}

	composite_scale = sf::Vector2f(x, y);
}

float Composite::get_rotation()
{
	return composite_angle;
}

void Composite::set_rotation(float angle)
{
	float rotation_angle = (angle - composite_angle) / 180 * 3.14159265f;

	sf::Vector2f this_position = this->get_position();

	for (int i = 0; i < figures.size(); i++)
	{
		figures[i]->set_rotation(figures[i]->get_rotation() + angle - composite_angle);
		
		float x = figures[i]->get_position().x - this_position.x;
		float y = figures[i]->get_position().y - this_position.y;

		float new_x = x * std::cos(rotation_angle) - y * std::sin(rotation_angle);
		float new_y = x * std::sin(rotation_angle) + y * std::cos(rotation_angle);

		new_x += this_position.x;
		new_y += this_position.y;

		figures[i]->set_position(new_x, new_y);
	}

	composite_angle = angle;
	
	if (composite_angle > 360) {
		composite_angle -= 360;
	}
	else if (composite_angle < 360) {
		composite_angle += 360;
	}
}


void Composite::move(float move_x, float move_y)
{
	for (int i = 0; i < figures.size(); i++)
	{
		figures[i]->move(move_x, move_y);
	}
}

void Composite::auto_move(float elapsed_time)
{
	for (int i = 0; i < figures.size(); i++)
	{
		figures[i]->auto_move(elapsed_time);
	}
}


void Composite::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < figures.size(); i++)
	{
		figures[i]->draw(window);
	}
}


// Prototype
Figure* Composite::clone()
{
	Composite* composite = new Composite(this->figures[0]->clone());

	composite->figures[0]->set_position(this->figures[0]->get_position().x, 
		this->figures[0]->get_position().y);

	for (int i = 1; i < this->figures.size(); i++)
	{
		composite->add_figure(figures[i]->clone());

		composite->figures[i]->set_position(this->figures[i]->get_position().x,
			this->figures[i]->get_position().y);
	}

	sf::FloatRect comp_bounds = composite->get_global_bounds();
	composite->set_position(comp_bounds.width / 2, comp_bounds.height / 2);

	composite->composite_scale = composite_scale;
	composite->composite_angle = composite_angle;

	Figure* figure = composite;
	return figure;
}


// Memento
const std::string Composite::serialize()
{
	std::stringstream str;

	str << '*' << ' '
		<< FigureType::CompositeType << ' '
		<< this->get_position().x << ' '
		<< this->get_position().y << ' '
		<< composite_scale.x << ' '
		<< composite_scale.y << ' '
		<< composite_angle << ' '
		<< '#' << ' ';

	for (int i = 0; i < figures.size(); i++)
	{
		str << figures[i]->serialize();
	}
	
	str << '#' << ' ';

	return str.str();
}

Figure* Composite::deserialize(std::string object_info)
{
	std::stringstream str(object_info);
	char comp_determinant;
	int comp_type;
	float comp_pos_x, comp_pos_y;
	float comp_scale_x, comp_scale_y;
	float comp_angle;

	str >> comp_determinant
		>> comp_type
		>> comp_pos_x >> comp_pos_y
		>> comp_scale_x >> comp_scale_y
		>> comp_angle;

	str >> comp_determinant >> comp_determinant;
	

	std::string figure_info;
	Composite* composite = new Composite();
	
	while (std::getline(str, figure_info, '*'))
	{
		figure_info = "*" + figure_info;
		std::stringstream figure_str(figure_info);
		char determinant;
		int type;

		figure_str >> determinant >> type;

		FigureType fig_type = (FigureType)type;
		std::string add_str;

		switch (fig_type)
		{
		case CircleType:
			composite->figures.push_back(Circle::deserialize(figure_info));
			break;
		case PolygonType:
			composite->figures.push_back(Polygon::deserialize(figure_info));
			break;
		case RectangleType:
			composite->figures.push_back(Rectangle::deserialize(figure_info));
			break;
		case SquareType:
			composite->figures.push_back(Square::deserialize(figure_info));
			break;
		case TriangleType:
			composite->figures.push_back(Triangle::deserialize(figure_info));
			break;
		case CompositeType:
			std::getline(str, add_str, '#');
			figure_info += "*" + add_str;
			std::getline(str, add_str, '*');
			figure_info += add_str.substr(1);
			composite->figures.push_back(Composite::deserialize(figure_info));
			break;
		default:
			break;
		}
	}

	composite->set_position(comp_pos_x, comp_pos_y);
	composite->composite_scale = sf::Vector2f(comp_scale_x, comp_scale_y);
	composite->composite_angle = comp_angle;

	Figure* figure = composite;
	return figure;
}
