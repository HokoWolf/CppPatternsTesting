#include "Rectangle.h"

Rectangle::Rectangle()
{
	rectangle = new sf::RectangleShape(sf::Vector2f(50.0f, 100.0f));
	rectangle->setOrigin(25.0f, 50.0f);
	rectangle->setPosition(sf::Vector2f(25.0f, 50.0f));
	rectangle->setFillColor(sf::Color::Blue);
	default_color = sf::Color::Blue;
}

Rectangle::Rectangle(float width, float height, sf::Color color)
{
	rectangle = new sf::RectangleShape(sf::Vector2f(width, height));
	rectangle->setOrigin(width / 2, height / 2);
	rectangle->setPosition(sf::Vector2f(width / 2, height / 2));
	rectangle->setFillColor(color);
	default_color = color;
}

Rectangle::~Rectangle()
{
	delete rectangle;
}


sf::FloatRect Rectangle::get_global_bounds()
{
	return rectangle->getGlobalBounds();
}

bool Rectangle::check_intersection(Figure* figure)
{
	return rectangle->getGlobalBounds().intersects(figure->get_global_bounds());
}

bool Rectangle::check_intersection(float x, float y)
{
	return rectangle->getGlobalBounds().contains(sf::Vector2f(x, y));
}

bool Rectangle::check_window_collision(sf::RenderWindow& window)
{
	sf::Vector2u window_size = window.getSize();
	sf::FloatRect rect_global_bounds = this->get_global_bounds();;

	bool is_x_in = rect_global_bounds.left >= 0 && rect_global_bounds.left <= window_size.x - rect_global_bounds.width;
	bool is_y_in = rect_global_bounds.top >= 0 && rect_global_bounds.top <= window_size.y - rect_global_bounds.height;

	return !(is_x_in && is_y_in);
}


sf::Vector2f Rectangle::get_position()
{
	return rectangle->getPosition();
}

void Rectangle::set_position(float x, float y)
{
	rectangle->setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Rectangle::get_scale()
{
	return rectangle->getScale();
}

void Rectangle::set_scale(float x, float y)
{
	rectangle->setScale(x, y);
}

float Rectangle::get_rotation()
{
	return rectangle->getRotation();
}

void Rectangle::set_rotation(float angle)
{
	rectangle->setRotation(angle);
}


sf::Color Rectangle::get_color()
{
	return rectangle->getFillColor();
}

void Rectangle::set_color(sf::Color color)
{
	return rectangle->setFillColor(color);
}

sf::Color Rectangle::get_outline_color()
{
	return rectangle->getOutlineColor();
}

float Rectangle::get_outline_thickness()
{
	return rectangle->getOutlineThickness();
}

void Rectangle::set_outline(sf::Color color, float thickness)
{
	rectangle->setOutlineColor(color);
	rectangle->setOutlineThickness(thickness);
}

void Rectangle::reset()
{
	rectangle->setScale(sf::Vector2f(1.0f, 1.0f));
	rectangle->setRotation(0.0f);
	rectangle->setPosition(rectangle->getSize().x / 2, rectangle->getSize().y / 2);
	rectangle->setFillColor(default_color);
	rectangle->setOutlineColor(sf::Color::White);
	rectangle->setOutlineThickness(0);
}


void Rectangle::move(float move_x, float move_y)
{
	rectangle->move(move_x, move_y);
}

void Rectangle::draw(sf::RenderWindow& window)
{
	window.draw(*rectangle);
}


// Prototype
Figure* Rectangle::clone()
{
	Figure* new_rectangle = new Rectangle(rectangle->getSize().x, rectangle->getSize().y, rectangle->getFillColor());
	new_rectangle->set_scale(rectangle->getScale().x, rectangle->getScale().y);
	new_rectangle->set_rotation(rectangle->getRotation());
	new_rectangle->move(-1 * new_rectangle->get_global_bounds().left,
		-1 * new_rectangle->get_global_bounds().top);

	return new_rectangle;
}


// Memento
const std::string Rectangle::serialize()
{
	std::stringstream str;

	str << '*' << ' '
		<< FigureType::RectangleType << ' '
		<< rectangle->getSize().x << ' '
		<< rectangle->getSize().y << ' '
		<< (int)default_color.r << ' '
		<< (int)default_color.g << ' '
		<< (int)default_color.b << ' '
		<< (int)default_color.a << ' '
		<< (int)visible << ' '
		<< (int)trail_movement << ' '
		<< (int)auto_movement << ' '
		<< rectangle->getPosition().x << ' '
		<< rectangle->getPosition().y << ' '
		<< rectangle->getScale().x << ' '
		<< rectangle->getScale().y << ' '
		<< rectangle->getRotation() << ' '
		<< (int)rectangle->getFillColor().r << ' '
		<< (int)rectangle->getFillColor().g << ' '
		<< (int)rectangle->getFillColor().b << ' '
		<< (int)rectangle->getFillColor().a << ' '
		<< rectangle->getOutlineThickness() << ' '
		<< (int)rectangle->getOutlineColor().r << ' '
		<< (int)rectangle->getOutlineColor().g << ' '
		<< (int)rectangle->getOutlineColor().b << ' '
		<< (int)rectangle->getOutlineColor().a << ' ';

	return str.str();
}

Figure* Rectangle::deserialize(std::string object_info)
{
	std::stringstream str(object_info);
	char determinant;
	int type;
	float size_x, size_y;
	
	sf::Color fig_default_color;
	int r1, g1, b1, a1;

	bool fig_visible;
	bool fig_trail_movement;
	bool fig_auto_movement;

	float pos_x, pos_y;
	float scale_x, scale_y;
	float angle;

	sf::Color fill_color;
	int r2, g2, b2, a2;

	float outline_thickness;
	sf::Color outline_color;
	int r3, g3, b3, a3;

	str >> determinant
		>> type
		>> size_x >> size_y
		>> r1
		>> g1
		>> b1
		>> a1
		>> fig_visible
		>> fig_trail_movement
		>> fig_auto_movement
		>> pos_x >> pos_y
		>> scale_x >> scale_y
		>> angle
		>> r2
		>> g2
		>> b2
		>> a2
		>> outline_thickness
		>> r3
		>> g3
		>> b3
		>> a3;

	fig_default_color = sf::Color(r1, g1, b1, a1);
	fill_color = sf::Color(r2, g2, b2, a2);
	outline_color = sf::Color(r3, g3, b3, a3);

	Figure* figure = new Rectangle(size_x, size_y, fig_default_color);
	
	if (fig_visible) {
		figure->hide();
	}
	else {
		figure->show();
	}

	figure->set_trail_movement(fig_trail_movement);
	figure->set_auto_movement(fig_auto_movement);
	figure->set_position(pos_x, pos_y);
	figure->set_scale(scale_x, scale_y);
	figure->set_rotation(angle);
	figure->set_color(fill_color);
	figure->set_outline(outline_color, outline_thickness);

	return figure;
}
