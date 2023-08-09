#pragma once
#include <iostream>
#include <fstream>
#include "Memento.h"

class Controller;

class MementoHandler
{
public:
	MementoHandler(std::string file_name);

	std::string get_file_name();
	void set_file_name(std::string file_name);

	void save_state(const Controller* controller);
	void load_state(Controller* controller);

private:
	static std::string file_name;
	Memento* memento;
};
