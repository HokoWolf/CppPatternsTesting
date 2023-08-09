#include "Polygon.h"

Polygon::Polygon()
{
	polygon = new sf::CircleShape(50.0f, 6);
	polygon->setOrigin(50.0f, 50.0f);
	polygon->setPosition(sf::Vector2f(50.0f, 50.0f));
	polygon->setFillColor(sf::Color::Blue);
	default_color = sf::Color::Blue;
}

Polygon::Polygon(float radius, int count, sf::Color color)
{
	polygon = new sf::CircleShape(radius, count);
	polygon->setOrigin(radius, radius);
	polygon->setPosition(sf::Vector2f(radius, radius));
	polygon->setFillColor(color);
	default_color = color;
}

Polygon::~Polygon()
{
	delete polygon;
}


sf::FloatRect Polygon::get_global_bounds()
{
	sf::Vector2f scale = polygon->getScale();
	sf::FloatRect global_bounds;
	global_bounds.left = polygon->getPosition().x - polygon->getRadius() * scale.x;
	global_bounds.top = polygon->getPosition().y - polygon->getRadius() * scale.y;
	global_bounds.width = 2 * polygon->getRadius() * scale.x;
	global_bounds.height = 2 * polygon->getRadius() * scale.y;
	return global_bounds;
	//return polygon->getGlobalBounds();
}

bool Polygon::check_intersection(Figure* figure)
{
	return polygon->getGlobalBounds().intersects(figure->get_global_bounds());
}

bool Polygon::check_intersection(float x, float y)
{
	return polygon->getGlobalBounds().contains(sf::Vector2f(x, y));
}

bool Polygon::check_window_collision(sf::RenderWindow& window)
{
	sf::Vector2u window_size = window.getSize();
	sf::FloatRect rect_global_bounds = this->get_global_bounds();

	bool is_x_in = rect_global_bounds.left >= 0 && rect_global_bounds.left <= window_size.x - rect_global_bounds.width;
	bool is_y_in = rect_global_bounds.top >= 0 && rect_global_bounds.top <= window_size.y - rect_global_bounds.height;

	return !(is_x_in && is_y_in);
}


sf::Vector2f Polygon::get_position()
{
	return polygon->getPosition();
}

void Polygon::set_position(float x, float y)
{
	polygon->setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Polygon::get_scale()
{
	return polygon->getScale();
}

void Polygon::set_scale(float x, float y)
{
	polygon->setScale(x, y);
}

float Polygon::get_rotation()
{
	return polygon->getRotation();
}

void Polygon::set_rotation(float angle)
{
	polygon->setRotation(angle);
}


sf::Color Polygon::get_color()
{
	return polygon->getFillColor();
}

void Polygon::set_color(sf::Color color)
{
	return polygon->setFillColor(color);
}

sf::Color Polygon::get_outline_color()
{
	return polygon->getOutlineColor();
}

float Polygon::get_outline_thickness()
{
	return polygon->getOutlineThickness();
}

void Polygon::set_outline(sf::Color color, float thickness)
{
	polygon->setOutlineColor(color);
	polygon->setOutlineThickness(thickness);
}

void Polygon::reset()
{
	polygon->setScale(sf::Vector2f(1.0f, 1.0f));
	polygon->setRotation(0.0f);
	polygon->setPosition(polygon->getRadius(), polygon->getRadius());
	polygon->setFillColor(default_color);
	polygon->setOutlineColor(sf::Color::White);
	polygon->setOutlineThickness(0);
}


void Polygon::move(float move_x, float move_y)
{
	polygon->move(move_x, move_y);
}

void Polygon::draw(sf::RenderWindow& window)
{
	window.draw(*polygon);
}


// Prototype
Figure* Polygon::clone()
{
	Figure* new_polygon = new Polygon(polygon->getRadius(), polygon->getPointCount(), polygon->getFillColor());
	new_polygon->set_scale(polygon->getScale().x, polygon->getScale().y);
	new_polygon->set_rotation(polygon->getRotation());
	new_polygon->move(-1 * new_polygon->get_global_bounds().left,
		-1 * new_polygon->get_global_bounds().top);

	return new_polygon;
}


// Memento
const std::string Polygon::serialize()
{
	std::stringstream str;

	str << '*' << ' '
		<< FigureType::PolygonType << ' '
		<< polygon->getRadius() << ' '
		<< polygon->getPointCount() << ' '
		<< (int)default_color.r << ' '
		<< (int)default_color.g << ' '
		<< (int)default_color.b << ' '
		<< (int)default_color.a << ' '
		<< (int)visible << ' '
		<< (int)trail_movement << ' '
		<< (int)auto_movement << ' '
		<< polygon->getPosition().x << ' '
		<< polygon->getPosition().y << ' '
		<< polygon->getScale().x << ' '
		<< polygon->getScale().y << ' '
		<< polygon->getRotation() << ' '
		<< (int)polygon->getFillColor().r << ' '
		<< (int)polygon->getFillColor().g << ' '
		<< (int)polygon->getFillColor().b << ' '
		<< (int)polygon->getFillColor().a << ' '
		<< polygon->getOutlineThickness() << ' '
		<< (int)polygon->getOutlineColor().r << ' '
		<< (int)polygon->getOutlineColor().g << ' '
		<< (int)polygon->getOutlineColor().b << ' '
		<< (int)polygon->getOutlineColor().a << ' ';

	return str.str();
}

Figure* Polygon::deserialize(std::string object_info)
{
	std::stringstream str(object_info);
	char determinant;
	int type;
	float radius;
	int points_count;
	
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
		>> points_count
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

	Figure* figure = new Polygon(radius, points_count, fig_default_color);

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
