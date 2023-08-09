#include "EventHandler.h"

EventHandler::EventHandler()
{
	memento_handler = new MementoHandler("save.bin");

	timer = new sf::Clock();
	trail.setPrimitiveType(sf::LinesStrip);
}

EventHandler::~EventHandler()
{
	delete memento_handler;
}


void EventHandler::action_event(GUI& gui)
{
	gui.clear();

	if (Controller::get_instance()->get_active_figure_trail_movement()) {

		sf::FloatRect bounds = Controller::get_instance()->get_active_figure_global_bounds();
		trail.append(sf::Vertex(sf::Vector2f(bounds.left + bounds.width / 2, 
			bounds.top + bounds.height / 2), sf::Color::Black));

		gui.get_window()->draw(trail);
	}

	if (Controller::get_instance()->get_active_figure_auto_movement())
	{
		Controller::get_instance()->auto_move_active_figure(timer->getElapsedTime().asSeconds());
		Controller::get_instance()->active_figure_intersection_change();

		if (Controller::get_instance()->check_active_figure_window_collision(gui))
		{
			Controller::get_instance()->set_active_figure_auto_movement(false);
			timer->restart();

			sf::String figure_name = Controller::get_instance()->get_active_figure_type();
			gui.set_status_label_text(	figure_name + "'s auto movement stopped");
			gui.set_auto_moving_label_text("Auto Movement: disabled");
		}
	}
	else
	{
		timer->restart();
	}

	Controller::get_instance()->draw(gui);
	gui.draw();
	gui.display();
}


void EventHandler::poll_event(GUI& gui, const sf::Event& event)
{
	sf::String figure_name;

	switch (event.type)
	{
	case sf::Event::Closed:
	{
		gui.get_window()->close();
		break;
	}
	case sf::Event::KeyPressed:
	{
		// Get Help
		switch (event.key.code)
		{
			case sf::Keyboard::Escape:
			{
				gui.flag_help_menu();
				break;
			}
			case sf::Keyboard::F1:
			{
				gui.flag_help_menu();
				break;
			}
			default:
			{
				break;
			}
		}

		if (gui.is_help_menu_enabled())
		{
			break;
		}

		switch (event.key.code)
		{
		// Crating figures
		case sf::Keyboard::C:
		{
			if (!is_composite_mode_active)
			{
				Controller::get_instance()->add_figure(FigureType::CircleType);
				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_main_label_text("< " + figure_name + " >");
				gui.set_status_label_text("Creating " + figure_name);
				gui.set_trail_moving_label_text("Trail Movement: disabled");
				gui.set_auto_moving_label_text("Auto Movement: disabled");
			}
			break;
		}
		case sf::Keyboard::P:
		{
			if (!is_composite_mode_active)
			{
				Controller::get_instance()->add_figure(FigureType::PolygonType);
				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_main_label_text("< " + figure_name + " >");
				gui.set_status_label_text("Creating " + figure_name);
				gui.set_trail_moving_label_text("Trail Movement: disabled");
				gui.set_auto_moving_label_text("Auto Movement: disabled");
			}
			break;
		}
		case sf::Keyboard::R:
		{
			if (!is_composite_mode_active)
			{
				Controller::get_instance()->add_figure(FigureType::RectangleType);
				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_main_label_text("< " + figure_name + " >");
				gui.set_status_label_text("Creating " + figure_name);
				gui.set_trail_moving_label_text("Trail Movement: disabled");
				gui.set_auto_moving_label_text("Auto Movement: disabled");
			}
			break;
		}
		case sf::Keyboard::S:
		{
			if (!is_composite_mode_active)
			{
				Controller::get_instance()->add_figure(FigureType::SquareType);
				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_main_label_text("< " + figure_name + " >");
				gui.set_status_label_text("Creating " + figure_name);
				gui.set_trail_moving_label_text("Trail Movement: disabled");
				gui.set_auto_moving_label_text("Auto Movement: disabled");
			}
			break;
		}
		case sf::Keyboard::T:
		{
			if (!is_composite_mode_active)
			{
				Controller::get_instance()->add_figure(FigureType::TriangleType);
				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_main_label_text("< " + figure_name + " >");
				gui.set_status_label_text("Creating " + figure_name);
				gui.set_trail_moving_label_text("Trail Movement: disabled");
				gui.set_auto_moving_label_text("Auto Movement: disabled");
			}
			break;
		}


		// Editing controller content
		case sf::Keyboard::Delete:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				if (!is_composite_mode_active)
				{
					Controller::get_instance()->clear();
					gui.set_main_label_text("< Create new Figure >");
					gui.set_status_label_text("All figures was deleted");
					gui.set_trail_moving_label_text("");
					gui.set_auto_moving_label_text("");
				}
			}
			else
			{
				if (!Controller::get_instance()->is_empty() && !is_composite_mode_active)
				{
					figure_name = Controller::get_instance()->get_active_figure_type();
					Controller::get_instance()->remove_active_figure();

					if (Controller::get_instance()->is_empty())
					{
						gui.set_main_label_text("< Create new Figure >");
						gui.set_status_label_text(figure_name + " was deleted. All figures was deleted");
						gui.set_trail_moving_label_text("");
						gui.set_auto_moving_label_text("");
					}
					else
					{
						gui.set_status_label_text(figure_name + " was deleted");
						figure_name = Controller::get_instance()->get_active_figure_type();
						gui.set_main_label_text("< " + figure_name + " >");

						if (Controller::get_instance()->get_active_figure_trail_movement()) {
							gui.set_trail_moving_label_text("Trail Movement: enabled");
						}
						else {
							gui.set_trail_moving_label_text("Trail Movement: disabled");
						}

						if (Controller::get_instance()->get_active_figure_auto_movement()) {
							gui.set_auto_moving_label_text("Auto Movement: enabled");
						}
						else {
							gui.set_auto_moving_label_text("Auto Movement: disabled");
						}
					}
				}
			}
			break;
		}
		case sf::Keyboard::Left:
		{
			if (!Controller::get_instance()->is_empty())
			{
				Controller::get_instance()->activate_previous_figure();

				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_main_label_text("< " + figure_name + " >");
				gui.set_status_label_text(figure_name + " is selected");

				if (Controller::get_instance()->get_active_figure_trail_movement()) {
					gui.set_trail_moving_label_text("Trail Movement: enabled");
				}
				else {
					gui.set_trail_moving_label_text("Trail Movement: disabled");
				}

				if (Controller::get_instance()->get_active_figure_auto_movement()) {
					gui.set_auto_moving_label_text("Auto Movement: enabled");
				}
				else {
					gui.set_auto_moving_label_text("Auto Movement: disabled");
				}

				trail.clear();
			}
			break;
		}
		case sf::Keyboard::Right:
		{
			if (!Controller::get_instance()->is_empty())
			{
				Controller::get_instance()->activate_next_figure();

				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_main_label_text("< " + figure_name + " >");
				gui.set_status_label_text(figure_name + " is selected");

				if (Controller::get_instance()->get_active_figure_trail_movement()) {
					gui.set_trail_moving_label_text("Trail Movement: enabled");
				}
				else {
					gui.set_trail_moving_label_text("Trail Movement: disabled");
				}

				if (Controller::get_instance()->get_active_figure_auto_movement()) {
					gui.set_auto_moving_label_text("Auto Movement: enabled");
				}
				else {
					gui.set_auto_moving_label_text("Auto Movement: disabled");
				}

				trail.clear();
			}
			break;
		}


		// Editing active figure
		case sf::Keyboard::H:
		{
			if (!Controller::get_instance()->is_empty())
			{
				figure_name = Controller::get_instance()->get_active_figure_type();

				if (Controller::get_instance()->is_active_figure_visible())
				{
					Controller::get_instance()->hide_active_figure();

					gui.set_status_label_text(figure_name + " is hidden");
				}
				else
				{
					Controller::get_instance()->show_active_figure();

					gui.set_status_label_text(figure_name + " is shown");
				}
			}
			break;
		}
		case sf::Keyboard::Q:
		{
			if (!Controller::get_instance()->is_empty())
			{
				Controller::get_instance()->set_active_figure_random_color();

				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_status_label_text(figure_name + "'s color changed");
			}
			break;
		}
		case sf::Keyboard::Z:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				if (!Controller::get_instance()->is_empty())
				{
					Controller::get_instance()->reset_active_figure();

					figure_name = Controller::get_instance()->get_active_figure_type();
					gui.set_status_label_text(figure_name + " is resetted");
				}
			}
			break;
		}
		case sf::Keyboard::G:
		{
			if (!Controller::get_instance()->is_empty())
			{
				figure_name = Controller::get_instance()->get_active_figure_type();

				if (Controller::get_instance()->get_active_figure_trail_movement()) {
					Controller::get_instance()->set_active_figure_trail_movement(false);

					gui.set_status_label_text(figure_name + "'s trail movement disabled");
					gui.set_trail_moving_label_text("Trail Movement: disabled");
				}
				else {
					Controller::get_instance()->set_active_figure_trail_movement(true);

					gui.set_status_label_text(figure_name + "'s trail movement enabled");
					gui.set_trail_moving_label_text("Trail Movement: enabled");
				}

				trail.clear();
			}
			break;
		}
		case sf::Keyboard::M:
		{
			if (!Controller::get_instance()->is_empty())
			{
				figure_name = Controller::get_instance()->get_active_figure_type();

				if (Controller::get_instance()->get_active_figure_auto_movement()) {
					Controller::get_instance()->set_active_figure_auto_movement(false);

					gui.set_status_label_text(figure_name + "'s auto movement stopped");
					gui.set_auto_moving_label_text("Auto Movement: disabled");
				}
				else {
					Controller::get_instance()->set_active_figure_auto_movement(true);

					gui.set_status_label_text(figure_name + " is auto moving");
					gui.set_auto_moving_label_text("Auto Movement: enabled");
				}
			}
			break;
		}
		case sf::Keyboard::Add:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				if (!Controller::get_instance()->is_empty())
				{
					Controller::get_instance()->scale_active_figure(0.25f, 0.25f);

					figure_name = Controller::get_instance()->get_active_figure_type();
					gui.set_status_label_text(figure_name + " was scaled");
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				if (!Controller::get_instance()->is_empty())
				{
					Controller::get_instance()->rotate_active_figure(8.0f);

					figure_name = Controller::get_instance()->get_active_figure_type();
					gui.set_status_label_text(figure_name + " was rotated");
				}
			}
			break;
		}
		case sf::Keyboard::Subtract:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				if (!Controller::get_instance()->is_empty())
				{
					Controller::get_instance()->scale_active_figure(-0.25f, -0.25f);

					figure_name = Controller::get_instance()->get_active_figure_type();
					gui.set_status_label_text(figure_name + " was scaled");
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				if (!Controller::get_instance()->is_empty())
				{
					Controller::get_instance()->rotate_active_figure(-8.0f);

					figure_name = Controller::get_instance()->get_active_figure_type();
					gui.set_status_label_text(figure_name + " was rotated");
				}
			}
			break;
		}


		// Work with Composite
		case sf::Keyboard::U:
		{
			if (!Controller::get_instance()->is_empty())
			{
				if (!is_composite_mode_active)
				{
					figure_name = Controller::get_instance()->get_active_figure_type();
					
					Controller::get_instance()->create_composite();
					is_composite_mode_active = true;

					gui.set_main_label_text("< Composite >");
					gui.set_status_label_text("Composite was created from " + figure_name);
				}
			}
			break;
		}
		case sf::Keyboard::E:
		{
			if (!Controller::get_instance()->is_empty())
			{
				if (Controller::get_instance()->is_active_figure_composite())
				{
					Controller::get_instance()->activate_composite();
					is_composite_mode_active = true;

					gui.set_status_label_text("Composite was activated");
				}
			}
			break;
		}
		case sf::Keyboard::Enter:
		{
			if (!Controller::get_instance()->is_empty())
			{
				if (is_composite_mode_active)
				{
					Controller::get_instance()->deactivate_composite();
					is_composite_mode_active = false;

					gui.set_status_label_text("Composite was saved");
				}
			}
		}
		case sf::Keyboard::A:
		{
			if (is_composite_mode_active && !Controller::get_instance()->is_empty())
			{
				figure_name = Controller::get_instance()->get_active_figure_type();
				
				Controller::get_instance()->add_active_figure_to_composite();

				gui.set_main_label_text("< Composite >");
				gui.set_status_label_text("Composite was created from " + figure_name);
			}
			break;
		}
		case sf::Keyboard::I:
		{
			if (!Controller::get_instance()->is_empty() && 
				Controller::get_instance()->is_active_figure_composite())
			{
				Controller::get_instance()->activate_composite();
				is_composite_mode_active = true;

				Controller::get_instance()->go_inside_composite();

				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_main_label_text("< " + figure_name + " >");
				gui.set_status_label_text(figure_name + " is selected");

				if (Controller::get_instance()->get_active_figure_trail_movement()) {
					gui.set_trail_moving_label_text("Trail Movement: enabled");
				}
				else {
					gui.set_trail_moving_label_text("Trail Movement: disabled");
				}

				if (Controller::get_instance()->get_active_figure_auto_movement()) {
					gui.set_auto_moving_label_text("Auto Movement: enabled");
				}
				else {
					gui.set_auto_moving_label_text("Auto Movement: disabled");
				}
			}
			break;
		}
		case sf::Keyboard::D: 
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				if (is_composite_mode_active)
				{
					figure_name = Controller::get_instance()->get_active_figure_type();

					Controller::get_instance()->delete_active_figure_from_composite();

					gui.set_status_label_text(figure_name + " in Composite was deleted");
				
					figure_name = Controller::get_instance()->get_active_figure_type();
					gui.set_main_label_text("< " + figure_name + " >");
				}
			}
			else
			{
				if (is_composite_mode_active)
				{
					figure_name = Controller::get_instance()->get_active_figure_type();
					
					Controller::get_instance()->remove_active_figure_from_composite();
			
					gui.set_status_label_text(figure_name + " from Composite was deleted");

					figure_name = Controller::get_instance()->get_active_figure_type();
					gui.set_main_label_text("< " + figure_name + " >");
				}
			}
			break;
		}


		// Prototype realization
		case sf::Keyboard::V:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				if (!Controller::get_instance()->is_empty() && !is_composite_mode_active)
				{
					Controller::get_instance()->duplicate_active_figure();
				}
			}
			break;
		}


		// Memento
		case sf::Keyboard::F5:
		{
			memento_handler->save_state(Controller::get_instance());
			gui.set_status_label_text("Controller was saved to " + memento_handler->get_file_name());

			break;
		}
		case sf::Keyboard::F9:
		{
			memento_handler->load_state(Controller::get_instance());
			gui.set_status_label_text("Controller was loaded from " + memento_handler->get_file_name());

			figure_name = Controller::get_instance()->get_active_figure_type();
			gui.set_main_label_text("< " + figure_name + " >");

			if (Controller::get_instance()->get_active_figure_trail_movement()) {
				gui.set_trail_moving_label_text("Trail Movement: enabled");
			}
			else {
				gui.set_trail_moving_label_text("Trail Movement: disabled");
			}

			if (Controller::get_instance()->get_active_figure_auto_movement()) {
				gui.set_auto_moving_label_text("Auto Movement: enabled");
			}
			else {
				gui.set_auto_moving_label_text("Auto Movement: disabled");
			}

			break;
		}

		default:
		{
			break;
		}
		}
		break;
	}
	case sf::Event::MouseWheelMoved:
	{
		if (gui.is_help_menu_enabled())
		{
			break;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			if (!Controller::get_instance()->is_empty())
			{
				Controller::get_instance()->scale_active_figure(event.mouseWheel.delta * 0.25f, event.mouseWheel.delta * 0.25f);

				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_status_label_text(figure_name + " was scaled");
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (!Controller::get_instance()->is_empty())
			{
				Controller::get_instance()->rotate_active_figure((float)event.mouseWheel.delta * (-15));

				figure_name = Controller::get_instance()->get_active_figure_type();
				gui.set_status_label_text(figure_name + " was rotated");
			}
		}
		break;
	}
	case sf::Event::MouseMoved:
	{
		if (gui.is_help_menu_enabled())
		{
			break;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!Controller::get_instance()->is_empty() &&
				!Controller::get_instance()->get_active_figure_auto_movement())
			{
				float mouse_x = (float)sf::Mouse::getPosition(*gui.get_window()).x;
				float mouse_y = (float)sf::Mouse::getPosition(*gui.get_window()).y;

				sf::FloatRect global_bounds = Controller::get_instance()->get_active_figure_global_bounds();
				bool is_in_range_x = mouse_x > global_bounds.left &&
					event.mouseMove.x < (global_bounds.left + global_bounds.width);
				bool is_in_range_y = mouse_y > global_bounds.top &&
					event.mouseMove.y < (global_bounds.top + global_bounds.height);

				if (is_in_range_x && is_in_range_y)
				{
					sf::Cursor cursor;
					cursor.loadFromSystem(sf::Cursor::Type::Hand);
					gui.get_window()->setMouseCursor(cursor);

					bool is_in_window_x = mouse_x - global_bounds.width / 2 >= 0 &&
						mouse_x + global_bounds.width / 2 <= gui.get_window()->getSize().x;
					bool is_in_window_y = mouse_y - global_bounds.height / 2 >= 0 &&
						mouse_y + global_bounds.height / 2 <= gui.get_window()->getSize().y;

					if (is_in_window_x && is_in_window_y)
					{
						Controller::get_instance()->set_active_figure_position(mouse_x, mouse_y);
						Controller::get_instance()->active_figure_intersection_change();
					}

					figure_name = Controller::get_instance()->get_active_figure_type();
					gui.set_status_label_text(figure_name + " is grabbed and moving");
				}
			}
		}
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		if (gui.is_help_menu_enabled())
		{
			break;
		}

		sf::Cursor cursor;
		cursor.loadFromSystem(sf::Cursor::Type::Arrow);
		gui.get_window()->setMouseCursor(cursor);
		break;
	}

	default:
	{
		break;
	}
	}
}
