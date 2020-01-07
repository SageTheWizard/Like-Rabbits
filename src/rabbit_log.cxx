#include <iostream>
#include <string>
#include "rabbit_log.h"

rabbit_log::rabbit_log() 
{
	// nothing needed to be done to init
}

void rabbit_log::print_death_log()
{
	std::vector<std::string>::iterator iter;
	std::cout << "...::: RABBITS WHO DIED THIS GENERATION :::...\n";
	for (iter = deaths.begin(); iter != deaths.end(); )
	{
		std::cout << *iter << std::endl;
		++iter;
	}
}

void rabbit_log::print_birth_log()
{
	std::vector<std::string>::iterator iter;
	std::cout << "...::: RABBITS WHO WERE BORN THIS GENERATION :::...\n";
	for (iter = births.begin(); iter != births.end(); )
	{
		std::cout << *iter << std::endl;
		++iter;
	}
}

void rabbit_log::clear_logs()
{
	deaths.clear();
	births.clear();
}

void rabbit_log::add_death(std::string id, int death_code)
{
	std::string death_msg = "Rabbit ";

	death_msg.append(id);
	death_msg.append(" has died of ");

	switch (death_code)
	{
		case 0: // Hunger
			death_msg.append("hunger!");
			break;
		case 1: // Predator
			death_msg.append("being eaten by a predator!");
			break;
		case 2: // cannibalism
			death_msg.append("being eaten by another Rabbit!");
			break;
		case 3: // Hypothermia
			death_msg.append("hypothermia!");
			break;
		case 4: // heatstroke
			death_msg.append("heat stroke!");
			break;
		case 5: // drowning
			death_msg.append("drowning!");
			break;
	}

	deaths.push_back(death_msg);
}

void rabbit_log::add_birth(std::string born, std::string p1, std::string p2)
{
	std::string birth_msg = "Rabbit ";
	
	birth_msg.append(born);
	birth_msg.append(" of Parents ... Rabbit ");
	birth_msg.append(p1);
	birth_msg.append(" and Rabbit ");
	birth_msg.append(p2);

	births.push_back(birth_msg);
}

