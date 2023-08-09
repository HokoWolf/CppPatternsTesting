#include "MementoHandler.h"

std::string MementoHandler::file_name = "";

MementoHandler::MementoHandler(std::string file_name)
{
	if (file_name.substr(file_name.size() - 4, 4) == ".txt")
	{
		this->file_name = file_name;
	}
	else
	{
		this->file_name = "save.txt";
	}

	memento = new Memento();
}

std::string MementoHandler::get_file_name()
{
	return this->file_name;
}

void MementoHandler::set_file_name(std::string file_name)
{
	if (file_name.substr(file_name.size() - 4, 4) == ".txt")
	{
		this->file_name = file_name;
	}
	else
	{
		this->file_name = "save.txt";
	}
}
