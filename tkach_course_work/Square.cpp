#include "Square.h"

Square::Square()
{
	square = new sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
	square->setOrigin(50.0f, 50.0f);
	square->setPosition(sf::Vector2f(50.0f, 50.0f));
	square->setFillColor(sf::Color::Blue);
	default_color = sf::Color::Blue;
}

Square::Square(float side, sf::Color color)
{
	square = new sf::RectangleShape(sf::Vector2f(side, side));
	square->setOrigin(side / 2, side / 2);
	square->setPosition(sf::Vector2f(side / 2, side / 2));
	square->setFillColor(color);
	default_color = color;
}

Square::~Square()
{
	delete square;
}


sf::FloatRect Square::get_global_bounds()
{
	return square->getGlobalBounds();
}

bool Square::check_intersection(Figure* figure)
{
	return square->getGlobalBounds().intersects(figure->get_global_bounds());
}

bool Square::check_intersection(float x, float y)
{
	return square->getGlobalBounds().contains(sf::Vector2f(x, y));
}

bool Square::check_window_collision(sf::RenderWindow& window)
{
	sf::Vector2u window_size = window.getSize();
	sf::FloatRect rect_global_bounds = this->get_global_bounds();;

	bool is_x_in = rect_global_bounds.left >= 0 && rect_global_bounds.left <= window_size.x - rect_global_bounds.width;
	bool is_y_in = rect_global_bounds.top >= 0 && rect_global_bounds.top <= window_size.y - rect_global_bounds.height;
	return !(is_x_in && is_y_in);
}


sf::Vector2f Square::get_position()
{
	return square->getPosition();
}

void Square::set_position(float x, float y)
{
	square->setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Square::get_scale()
{
	return square->getScale();
}

void Square::set_scale(float x, float y)
{
	square->setScale(x, y);
}

float Square::get_rotation()
{
	return square->getRotation();
}

void Square::set_rotation(float angle)
{
	square->setRotation(angle);
}


sf::Color Square::get_color()
{
	return square->getFillColor();
}

void Square::set_color(sf::Color color)
{
	return square->setFillColor(color);
}

sf::Color Square::get_outline_color()
{
	return square->getOutlineColor();
}

float Square::get_outline_thickness()
{
	return square->getOutlineThickness();
}

void Square::set_outline(sf::Color color, float thickness)
{
	square->setOutlineColor(color);
	square->setOutlineThickness(thickness);
}

void Square::reset()
{
	square->setScale(sf::Vector2f(1.0f, 1.0f));
	square->setRotation(0.0f);
	square->setPosition(square->getSize().x / 2, square->getSize().y / 2);
	square->setFillColor(default_color);
	square->setOutlineColor(sf::Color::White);
	square->setOutlineThickness(0);
}


void Square::move(float move_x, float move_y)
{
	square->move(move_x, move_y);
}

void Square::draw(sf::RenderWindow& window)
{
	window.draw(*square);
}


// Prototype
Figure* Square::clone()
{
	Figure* new_square = new Square(square->getSize().x, square->getFillColor());
	new_square->set_scale(square->getScale().x, square->getScale().y);
	new_square->set_rotation(square->getRotation());
	new_square->move(-1 * new_square->get_global_bounds().left,
		-1 * new_square->get_global_bounds().top);

	return new_square;
}


// Memento
const std::string Square::serialize()
{
	std::stringstream str;

	str << '*' << ' '
		<< FigureType::SquareType << ' '
		<< square->getSize().x << ' '
		<< square->getPosition().x << ' '
		<< square->getPosition().y << ' '
		<< square->getScale().x << ' '
		<< square->getScale().y << ' '
		<< square->getRotation() << ' '
		<< (int)square->getFillColor().r << ' '
		<< (int)square->getFillColor().g << ' '
		<< (int)square->getFillColor().b << ' '
		<< (int)square->getFillColor().a << ' '
		<< square->getOutlineThickness() << ' '
		<< (int)square->getOutlineColor().r << ' '
		<< (int)square->getOutlineColor().g << ' '
		<< (int)square->getOutlineColor().b << ' '
		<< (int)square->getOutlineColor().a << ' ';

	return str.str();
}

Figure* Square::deserialize(std::string object_info)
{
	std::stringstream str(object_info);
	char determinant;
	int type;
	float side;
	
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
		>> side
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

	Figure* figure = new Square(side, fig_default_color);
	
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
