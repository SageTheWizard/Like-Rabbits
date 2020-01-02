#include <iostream>
#include <algorithm>
#include <stack>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>
#include "rabbit.h"

rabbit::rabbit()
{
	// custom rabbit coming later
}
rabbit::rabbit(int choice)
{
	int default_init[8]         = {0,1,1,0,0,1,1,0}; // 102
	
	int ninja_init_spd_fur[8]   = {1,0,0,1,0,1,1,0}; // 150
	int ninja_init_col[8]       = {1,1,1,1,1,0,1,0}; // 250
	
	int fluff_init_fur[8]       = {1,1,0,0,1,0,0,0}; // 200
	int fluff_init_spd[8]       = {0,1,0,1,0,0,0,0}; // 80
	int fluff_init_col[8]       = {0,0,0,1,1,0,0,0}; // 24

	int ninja_init_spd_fur_dec  = 150;
	int ninja_init_col_dec      = 250;
	
	int fluff_init_fur_dec      = 200;
	int fluff_init_spd_dec      = 80;
	int fluff_init_col_dec      = 24;

	int default_init_dec        = 102;
	srand(time(NULL));
	
	switch (choice) // standard Rabbit
	{
		case 0:
			std::cout << "Generating Standard Rabbit...\n";
			for (int i = 0; i < 8; i++)
			{
				fur[i] = color[i] = strength[i] = speed[i] = swimming[i] = default_init[i];
			}
			fur_dec = color_dec = strength_dec = speed_dec = swimming_dec = default_init_dec;
			has_food       = false;
			food_type      = true;
			nocturnal      = false;
			carniverous    = false;
			cannibalistic  = false;
			// Until i fix the rng this will need ot be used to delay 
			std::this_thread::sleep_for (std::chrono::seconds(1));
			id_char = (char) ((rand() % 26) + 65);
			id_int = (rand() % 90) + 10;

			break;
			
		case 1: // ninja rabbit
			std::cout << "Generating Ninja Rabbit...\n";
			for (int i = 0; i < 8; i++)
			{
				fur[i] = speed[i] = ninja_init_spd_fur[i];
				color[i] = ninja_init_col[i];
				strength[i] = swimming[i] = default_init[i];
			}
			fur_dec = speed_dec = ninja_init_spd_fur_dec;
			color_dec = ninja_init_col_dec;
			strength_dec = swimming_dec = default_init_dec;
			has_food       = false;
			food_type      = true;
			nocturnal      = true;
			carniverous    = false;
			cannibalistic  = false;
			// fix rng pls
			std::this_thread::sleep_for (std::chrono::seconds(1));
			id_char = (char) ((rand() % 26) + 65);
			id_int  = (rand() % 90) + 10;
			
			break;

		case 2: // fluff rabbit
			std::cout << "Generating Fluffy Rabbit...\n";
			for (int i = 0; i < 8; i++)
			{
				fur[i]      = fluff_init_fur[i];
				speed[i]    = fluff_init_spd[i];
				color[i]    = fluff_init_col[i];
				
				strength[i] = swimming[i] = default_init[i];
			}

			fur_dec   = fluff_init_fur_dec;
			color_dec = fluff_init_col_dec;
			speed_dec = fluff_init_spd_dec;

			swimming_dec = strength_dec = default_init_dec;

			has_food       = false;
			food_type      = true;
			nocturnal      = false;
			carniverous    = false;
			cannibalistic  = false;
			// fixrng pls
			std::this_thread::sleep_for (std::chrono::seconds(1));
			id_char = (char) ((rand() % 26) + 65);
			id_int  = (rand() % 90) + 10;

			break;
	}

}
void rabbit::show_stats()
{
	int dummy = fur_dec;
	/*
	 * FUR DISPLAY
	 */
	std::cout << "Fur Length: ";
	std::cout << dummy << " | ";

	if (dummy == 0)
		std::cout << " Bald.\n";
	else if ( (1 <= dummy) && (dummy <= 64) )
		std::cout << "Light Fur.\n";
	else if ( (65 <= dummy) && (dummy <= 128) )
		std::cout << "Medium Fur.\n";
	else if ( (129 <= dummy) && (dummy <= 192) )
		std::cout << "Heavy Fur.\n";
	else if ( (193 <= dummy) && (dummy <= 255) )
		std::cout << "Very Heavy Fur.\n";
	else
		std::cout << "ULTRA MEGA FUR!!!\n";
	
	dummy = color_dec;
	
	/*
	 * COLOR DISPLAY
	 */
    std::cout << "Color Shade: ";
    std::cout << dummy << " | ";

    if (dummy == 0)
        std::cout << " White.\n";
    else if ( (1 <= dummy) && (dummy <= 64) )
        std::cout << "Light Gray.\n";
    else if ( (65 <= dummy) && (dummy <= 128) )
        std::cout << "Gray.\n";
    else if ( (129 <= dummy) && (dummy <= 192) )
        std::cout << "Dark Gray.\n";
    else if ( (193 <= dummy) && (dummy <= 255) )
        std::cout << "Charcoal.\n";
    else
        std::cout << "Black.\n";
    
	dummy = strength_dec;
	/*
	 * STRENGTH DISPLAY
	 */

    std::cout << "Strength: ";
    std::cout << dummy << " | ";

    if (dummy == 0)
        std::cout << "Really Weak.\n";
    else if ( (1 <= dummy) && (dummy <= 64) )
        std::cout << "Weak.\n";
    else if ( (65 <= dummy) && (dummy <= 128) )
        std::cout << "Average.\n";
    else if ( (129 <= dummy) && (dummy <= 192) )
        std::cout << "Muscular.\n";
    else if ( (193 <= dummy) && (dummy <= 255) )
        std::cout << "Strong.\n";
    else
        std::cout << "SUPER STRONG.\n";
	
	dummy = speed_dec;
	/*
	 * SPEED DISPLAY
	 */

    std::cout << "Speed: ";
    std::cout << dummy << " | ";

    if (dummy == 0)
        std::cout << "VERY Slow.\n";
    else if ( (1 <= dummy) && (dummy <= 64) )
        std::cout << "Slow.\n";
    else if ( (65 <= dummy) && (dummy <= 128) )
        std::cout << "Average.\n";
    else if ( (129 <= dummy) && (dummy <= 192) )
        std::cout << "Quick.\n";
    else if ( (193 <= dummy) && (dummy <= 255) )
        std::cout << "Very Quick.\n";
    else
        std::cout << "Sonic the Rabbit.\n";
	
	dummy = swimming_dec;

	/*
	 * SWIMMING SKILLS
	 */ 
    
    std::cout << "Swimming Ability: ";
    std::cout << dummy << " | ";

    if (dummy == 0)
        std::cout << "Sinks like a Rock.\n";
    else if ( (1 <= dummy) && (dummy <= 64) )
        std::cout << "Poor.\n";
    else if ( (65 <= dummy) && (dummy <= 128) )
        std::cout << "Functional.\n";
    else if ( (129 <= dummy) && (dummy <= 192) )
        std::cout << "Good.\n";
    else if ( (193 <= dummy) && (dummy <= 255) )
        std::cout << "Very Good.\n";
    else
        std::cout << "Swims better than it can run!\n";

    dummy = 0;
	std::cout << "\n";
	
	/*
	 * Spec Mutations Display
	 */ 
	if (nocturnal)
		std::cout << "This Rabbit is Nocturnal.\n";
	if (carniverous)
	 	std::cout << "This Rabbit is Carniverous.\n";
	if (cannibalistic)
		std::cout << "Uh Oh! This rabbit is cannibalistic!\n";
	
	return;
}

void rabbit::print_id()
{
	std::cout << id_char << id_int;
}

int* rabbit::get_fur()
{
	return fur;
}
int* rabbit::get_dec_fur()
{
	return &fur_dec;
}

int* rabbit::get_color()
{
	return color;
}
int* rabbit::get_dec_color()
{
	return &color_dec;
}
int* rabbit::get_strength()
{
	return strength;
}
int* rabbit::get_dec_strength()
{
	return &strength_dec;
}

int* rabbit::get_speed()
{
	return speed;
}
int* rabbit::get_dec_speed()
{
	return &speed_dec;
}

int* rabbit::get_swimming()
{
	return swimming;
}
int* rabbit::get_dec_swimming()
{
	return &swimming_dec;
}

bool* rabbit::has_eaten()
{
	return &has_food;
}

bool* rabbit::veg_food()
{
	return &food_type;
}

bool* rabbit::get_nocturnal()
{
	return &nocturnal;
}

bool* rabbit::get_carniverous()
{
	return &carniverous;
}

bool* rabbit::get_cannibalistic()
{
	return &cannibalistic;
}
