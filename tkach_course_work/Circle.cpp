#include "Circle.h"

Circle::Circle()
{
	circle = new sf::CircleShape(50.0f);
	circle->setOrigin(50.0f, 50.0f);
	circle->setPosition(sf::Vector2f(50.0f, 50.0f));
	circle->setFillColor(sf::Color::Blue);
	default_color = sf::Color::Blue;
}

Circle::Circle(float radius, sf::Color color)
{
	circle = new sf::CircleShape(radius);
	circle->setOrigin(radius, radius);
	circle->setPosition(sf::Vector2f(radius, radius));
	circle->setFillColor(color);
	default_color = color;
}

Circle::~Circle()
{
	delete circle;
}


sf::FloatRect Circle::get_global_bounds()
{
	sf::Vector2f scale = circle->getScale();
	sf::FloatRect global_bounds;
	global_bounds.left = circle->getPosition().x - circle->getRadius() * scale.x;
	global_bounds.top = circle->getPosition().y - circle->getRadius() * scale.y;
	global_bounds.width = 2 * circle->getRadius() * scale.x;
	global_bounds.height = 2 * circle->getRadius() * scale.y;
	return global_bounds;
	//return circle->getGlobalBounds();
}

bool Circle::check_intersection(Figure* figure)
{
	return circle->getGlobalBounds().intersects(figure->get_global_bounds());
}

bool Circle::check_intersection(float x, float y)
{
	return circle->getGlobalBounds().contains(sf::Vector2f(x, y));
}

bool Circle::check_window_collision(sf::RenderWindow& window)
{
	sf::Vector2u window_size = window.getSize();
	sf::FloatRect rect_global_bounds = this->get_global_bounds();

	bool is_x_in = rect_global_bounds.left >= 0 && rect_global_bounds.left <= window_size.x - rect_global_bounds.width;
	bool is_y_in = rect_global_bounds.top >= 0 && rect_global_bounds.top <= window_size.y - rect_global_bounds.height;

	return !(is_x_in && is_y_in);
}


sf::Vector2f Circle::get_position()
{
	return circle->getPosition();
}

void Circle::set_position(float x, float y)
{
	circle->setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Circle::get_scale()
{
	return circle->getScale();
}

void Circle::set_scale(float x, float y)
{
	circle->setScale(x, y);
}

float Circle::get_rotation()
{
	return circle->getRotation();
}

void Circle::set_rotation(float angle)
{
	circle->setRotation(angle);
}


sf::Color Circle::get_color()
{
	return circle->getFillColor();
}

void Circle::set_color(sf::Color color)
{
	return circle->setFillColor(color);
}

sf::Color Circle::get_outline_color()
{
	return circle->getOutlineColor();
}

float Circle::get_outline_thickness()
{
	return circle->getOutlineThickness();
}

void Circle::set_outline(sf::Color color, float thickness)
{
	circle->setOutlineColor(color);
	circle->setOutlineThickness(thickness);
}

void Circle::reset()
{
	circle->setScale(sf::Vector2f(1.0f, 1.0f));
	circle->setRotation(0.0f);
	circle->setPosition(circle->getRadius(), circle->getRadius());
	circle->setFillColor(default_color);
	circle->setOutlineColor(sf::Color::White);
	circle->setOutlineThickness(0);
}


void Circle::move(float move_x, float move_y)
{
	circle->move(move_x, move_y);
}

void Circle::draw(sf::RenderWindow& window)
{
	window.draw(*circle);
}


// Prototype
Figure* Circle::clone()
{
	Figure* new_circle = new Circle(circle->getRadius(), circle->getFillColor());
	new_circle->set_scale(circle->getScale().x, circle->getScale().y);
	new_circle->set_rotation(circle->getRotation());
	new_circle->move(-1 * new_circle->get_global_bounds().left,
		-1 * new_circle->get_global_bounds().top);

	return new_circle;
}


// Memento
const std::string Circle::serialize()
{
	std::stringstream str;

	str << '*' << ' '
		<< FigureType::CircleType << ' '
		<< circle->getRadius() << ' '
		<< (int)default_color.r << ' '
		<< (int)default_color.g << ' '
		<< (int)default_color.b << ' '
		<< (int)default_color.a << ' '
		<< (int)visible << ' '
		<< (int)trail_movement << ' '
		<< (int)auto_movement << ' '
		<< circle->getPosition().x << ' '
		<< circle->getPosition().y << ' '
		<< circle->getScale().x << ' '
		<< circle->getScale().y << ' '
		<< circle->getRotation() << ' '
		<< (int)circle->getFillColor().r << ' '
		<< (int)circle->getFillColor().g << ' '
		<< (int)circle->getFillColor().b << ' '
		<< (int)circle->getFillColor().a << ' '
		<< circle->getOutlineThickness() << ' '
		<< (int)circle->getOutlineColor().r << ' '
		<< (int)circle->getOutlineColor().g << ' '
		<< (int)circle->getOutlineColor().b << ' '
		<< (int)circle->getOutlineColor().a << ' ';

	return str.str();
}

Figure* Circle::deserialize(std::string object_info)
{
	std::stringstream str(object_info);
	char determinant;
	int type;
	float radius;
	
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
		>> radius
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

	Figure* figure = new Circle(radius, fig_default_color);
	
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
