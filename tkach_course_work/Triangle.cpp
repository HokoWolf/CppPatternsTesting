#include "Triangle.h"

Triangle::Triangle()
{
	triangle = new sf::CircleShape(50.0f, 3);
	triangle->setOrigin(50.0f, 50.0f);
	triangle->setPosition(sf::Vector2f(50.0f, 50.0f));
	triangle->setFillColor(sf::Color::Blue);
	default_color = sf::Color::Blue;
}

Triangle::Triangle(float height, sf::Color color)
{
	triangle = new sf::CircleShape(height, 3);
	triangle->setOrigin(height, height);
	triangle->setPosition(sf::Vector2f(height, height));
	triangle->setFillColor(color);
	default_color = color;
}

Triangle::~Triangle()
{
	delete triangle;
}


sf::FloatRect Triangle::get_global_bounds()
{
	return triangle->getGlobalBounds();
}

bool Triangle::check_intersection(Figure* figure)
{
	return triangle->getGlobalBounds().intersects(figure->get_global_bounds());
}

bool Triangle::check_intersection(float x, float y)
{
	return triangle->getGlobalBounds().contains(sf::Vector2f(x, y));
}

bool Triangle::check_window_collision(sf::RenderWindow& window)
{
	sf::Vector2u window_size = window.getSize();
	sf::FloatRect rect_global_bounds = this->get_global_bounds();

	bool is_x_in = rect_global_bounds.left >= 0 && rect_global_bounds.left <= window_size.x - rect_global_bounds.width;
	bool is_y_in = rect_global_bounds.top >= 0 && rect_global_bounds.top <= window_size.y - rect_global_bounds.height;

	return !(is_x_in && is_y_in);
}


sf::Vector2f Triangle::get_position()
{
	return triangle->getPosition();
}

void Triangle::set_position(float x, float y)
{
	triangle->setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Triangle::get_scale()
{
	return triangle->getScale();
}

void Triangle::set_scale(float x, float y)
{
	triangle->setScale(x, y);
}

float Triangle::get_rotation()
{
	return triangle->getRotation();
}

void Triangle::set_rotation(float angle)
{
	triangle->setRotation(angle);
}


sf::Color Triangle::get_color()
{
	return triangle->getFillColor();
}

void Triangle::set_color(sf::Color color)
{
	return triangle->setFillColor(color);
}

sf::Color Triangle::get_outline_color()
{
	return triangle->getOutlineColor();
}

float Triangle::get_outline_thickness()
{
	return triangle->getOutlineThickness();
}

void Triangle::set_outline(sf::Color color, float thickness)
{
	triangle->setOutlineColor(color);
	triangle->setOutlineThickness(thickness);
}

void Triangle::reset()
{
	triangle->setScale(sf::Vector2f(1.0f, 1.0f));
	triangle->setRotation(0.0f);
	triangle->setPosition(triangle->getRadius(), triangle->getRadius());
	triangle->setFillColor(default_color);
	triangle->setOutlineColor(sf::Color::White);
	triangle->setOutlineThickness(0);
}


void Triangle::move(float move_x, float move_y)
{
	triangle->move(move_x, move_y);
}

void Triangle::draw(sf::RenderWindow& window)
{
	window.draw(*triangle);
}


// Prototype
Figure* Triangle::clone()
{
	Figure* new_triangle = new Triangle(triangle->getRadius(), triangle->getFillColor());
	new_triangle->set_scale(triangle->getScale().x, triangle->getScale().y);
	new_triangle->set_rotation(triangle->getRotation());
	new_triangle->move(-1 * new_triangle->get_global_bounds().left, 
		-1 * new_triangle->get_global_bounds().top);

	return new_triangle;
}


// Memento
const std::string Triangle::serialize()
{
	std::stringstream str;

	str << '*' << ' '
		<< FigureType::TriangleType << ' '
		<< triangle->getRadius() << ' '
		<< (int)default_color.r << ' '
		<< (int)default_color.g << ' '
		<< (int)default_color.b << ' '
		<< (int)default_color.a << ' '
		<< (int)visible << ' '
		<< (int)trail_movement << ' '
		<< (int)auto_movement << ' '
		<< triangle->getPosition().x << ' '
		<< triangle->getPosition().y << ' '
		<< triangle->getScale().x << ' '
		<< triangle->getScale().y << ' '
		<< triangle->getRotation() << ' '
		<< (int)triangle->getFillColor().r << ' '
		<< (int)triangle->getFillColor().g << ' '
		<< (int)triangle->getFillColor().b << ' '
		<< (int)triangle->getFillColor().a << ' '
		<< triangle->getOutlineThickness() << ' '
		<< (int)triangle->getOutlineColor().r << ' '
		<< (int)triangle->getOutlineColor().g << ' '
		<< (int)triangle->getOutlineColor().b << ' '
		<< (int)triangle->getOutlineColor().a << ' ';

	return str.str();
}

Figure* Triangle::deserialize(std::string object_info)
{
	std::stringstream str(object_info);
	char determinant;
	int type;
	float height;

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
		>> height
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

	Figure* figure = new Triangle(height, fig_default_color);
	
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
