#ifndef RABBIT_H
#define RABBIT_H

#include<string>
#include<stack>

class rabbit
{
	private:
		// Customizable Attributes
		std::string name;
		int fur[8];
		int color[8];
		int strength[8];
		int speed[8];
		int swimming[8];

		int fur_dec;
		int color_dec;
		int strength_dec;
		int speed_dec;
		int swimming_dec;

		// Health Related Stuff
		bool has_food;
		bool food_type; // True = Veg, False = Meat
		
		// Special Hidden Mutations
		bool nocturnal;
		bool carniverous;
		bool cannibalistic; // carniverous must be mutated first
		
		std::stack<int> init_stat(int);
		
		// random rabbit id, used for debugging
		char id_char;
		int id_int;
	public:
		rabbit();
		rabbit(int);

		void show_stats();
		void print_id();
		
		int* get_fur();
		int* get_color();
		int* get_strength();
		int* get_speed();
		int* get_swimming();

		int* get_dec_fur();
		int* get_dec_color();
		int* get_dec_strength();
		int* get_dec_speed();
		int* get_dec_swimming();

		bool* get_nocturnal();
		bool* get_carniverous();
		bool* get_cannibalistic();

		bool* has_eaten();
		bool* veg_food();

};

#endif
