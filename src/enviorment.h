#ifndef ENV_H
#define ENV_H
#include<vector>
#include"rabbit.h"

class enviorment
{
	private:
		// rabbit colony
		std::vector<rabbit*> rabbits;
		// enviorment
		int predator_types;
		int land_type;
		int veg_food_amount;
		int meat_food_amount; // only for carniverous
		int temperature;
		int rabbit_type;
	public:
		int generation_num = 0;

		enviorment(); // custom ... won't work until everything else is done
		enviorment(int, int); // preset colony and rabbit type

		// Food Obtaining
		void rabbits_eat();
		void strong_rabbits_take_food();
		void rabbits_starve();

		// Preditors Eat Rabbits
		void predators_eat();

		// Enviorment Kills Rabbits
		void rabbits_temperature();
		void rabbits_drown();
		
		// enough alive to make babys?
		bool enough_to_reproduce();

		// rabbits alive?
		bool all_dead();
		
		// shuffle the rabbits around in the vector to randomize who mates 
		void rabbit_shuffle();

		// Reproduce - Handles Mutations too!
		void rabbits_reproduce();

		//display stat chart for all rabbits
		void display_stat_chart();

};
#endif
