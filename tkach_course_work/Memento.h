#pragma once
#include <sstream>
#include <iostream>

class Memento
{
public:
	friend class Controller;
	friend class MementoHandler;

private:
	std::string controller_state;
};
