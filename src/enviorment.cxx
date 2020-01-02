#include<iostream>
#include<stack>
//#include<vector>
#include<math.h>
#include<string>
#include<stdlib.h>
#include<time.h>
#include"enviorment.h"
//#include"rabbit.h"

enviorment::enviorment() {} // coming later

enviorment::enviorment(int env, int rab)
{
	std::string rabbit_out = "ERROR";
	std::string enviorment_out = "ERROR";
	rabbit_type = rab;
	for (int i = 0; i < 20; i++)
	{
		rabbits.push_back(new rabbit(rab));
	}

	switch (rab)
	{
		case 0: 
			rabbit_out = "Standard Rabbits";
			break;
		case 1:
			rabbit_out = "Ninja Rabbits, specially created to be nocturnal, the color of the night and fast";
			break;
	}

	switch (env)
	{
		case 0:
			predator_types    = 0;
			land_type         = 0;
			veg_food_amount   = 20;
			meat_food_amount  = 10;
			temperature       = 18;
			
			enviorment_out = "Green grass land with considerable number of trees home to squirrel-like creatures.\nA few foxes seem to roam about but not many predators roam this area...\nThe temperature is moderate.\n";
			break;

	}
	
	srand(time(NULL));
	std::cout << "You and you team launch your team of " << rabbit_out << " into interstellar space...\n" 
	          << "You hear a signal that the FTL Drive on the ship has kicked in and await anxiously for the notification that the ship has arrived at its destination...\n"
			  << "Once the ship has arrived at the Planet " << (char) ( (rand() % 26) + 65 ) << (rand() % 90) + 10  << (char) ( (rand() % 26) + 65 ) << (rand() % 10000) + 1000 << " the ships cameras kick on..\n"
			  << "You see ... \n" << enviorment_out << "The rabbits begin their journey.\n\n"
			  << "RABBIT STARTING STATS AT GENERATION 0: \n";
	
	for (int i = 0; i < 20; i++)
	{
		std::cout << "RABBIT ";
		rabbits[i] -> print_id();
		std::cout << "\n";
		rabbits[i] -> show_stats();
	}
}

void enviorment::rabbits_eat() 
{
	std::string haves     = "RABBITS WHO HAVE EATEN: ";
	
	int fastest_still_hungry;
	int fastest_still_hungry_speed = -1;
	int temp_veg = veg_food_amount;
	int temp_meat = meat_food_amount;

	bool all_full = true;;
	
	/*
	 * All Rabbits would prefer to eat Vegitables than Meat
	 * Eat all Veggies until no more left / all rabbits are full
	 */
	do
	{
		all_full = true;

		for (int i = 0; i < rabbits.size(); i++)
		{
			if ( !(*(rabbits[i] -> has_eaten())) && !(*(rabbits[i] -> get_carniverous())) )
			{
				all_full = false;
				if (fastest_still_hungry_speed < *(rabbits[i] -> get_dec_speed()))
				{
					fastest_still_hungry = i;
					fastest_still_hungry_speed = *(rabbits[i] -> get_dec_speed());
				}
			}
		}
		
		if (!all_full)
		{
			*(rabbits[fastest_still_hungry] -> has_eaten()) = true;
			*(rabbits[fastest_still_hungry] -> veg_food())  = true;
			temp_veg--;
			std::cout << "Rabbit ";
			rabbits[fastest_still_hungry] -> print_id();
			std::cout << " has eaten!\n";
			fastest_still_hungry_speed = -1;
		}

	}while(!all_full && (temp_veg > 0) );
	
	/*
	 * Carniverous Rabbits without food will go and eat meat
	 * eat meat until none left / all rabbits have food
	 */
    do
    {
        all_full = true;
        
        for (int i = 0; i < rabbits.size(); i++)
        {   
            if ( (!(*(rabbits[i] -> has_eaten())) ) && *(rabbits[i] -> get_carniverous()) )
            {
                all_full = false;
                if (fastest_still_hungry_speed < *(rabbits[i] -> get_dec_speed()))
                {
                    fastest_still_hungry = i;
                    fastest_still_hungry_speed = *(rabbits[i] -> get_dec_speed());
                }
            }
        }

        if (!all_full)
        {   
            *(rabbits[fastest_still_hungry] -> has_eaten()) = true;
			*(rabbits[fastest_still_hungry] -> veg_food())  = false;
            temp_meat--;
            std::cout << "Rabbit ";
			rabbits[fastest_still_hungry] -> print_id();
			std::cout << " has eaten!\n";
            fastest_still_hungry_speed = -1;
        }
    
    }while(!all_full && (temp_meat > 0) );
	
	int victim_speed_chance;
	int victim_str_chance;
	int cannib_speed_roll;
	int cannib_str_roll;
	int eaten_ndx;
	int current_pop_size;
	bool one_eaten = false;

	/*
	 *    cannibal rabbit rolls between 0 -> 257000 on speed and asme on str
	 *                 the roll adds the cannibal rabbits speed_dec and str_dec * 10 to roll
	 *    victim's odds of not getting caught are speed_dec * 1000 (same w/ str)
	 *    if cannibal rolls higher than the number from above, on BOTH rolls, it eats the rabbit
	 *
	 *    These odds may be adjusted if it is too common for the cannibal to eat the others
	 */

	do
	{
		all_full = true;
		current_pop_size = rabbits.size();
		for (int i = 0; i < current_pop_size; i++)
		{
			if ( (!(*(rabbits[i] -> has_eaten())) ) && *(rabbits[i] -> get_cannibalistic()) )
			{
				all_full = false;
				for (int j = 0; j < current_pop_size; j++)
				{
					if (j != i)
					{
						victim_speed_chance = 1000 * *(rabbits[j] -> get_dec_speed());
						victim_str_chance   = 1000 * *(rabbits[j] -> get_dec_strength());
						cannib_speed_roll   = (rand() % 100) + (1000 * *(rabbits[i] -> get_dec_speed()));
						cannib_str_roll     = (rand() % 100) + (1000 * *(rabbits[i] -> get_dec_strength()));
						
						if ( (cannib_str_roll > victim_str_chance) && (cannib_speed_roll > victim_speed_chance) && !(one_eaten) )
						{
							all_full = true;
							*(rabbits[i] -> has_eaten()) = true;
							one_eaten = true;
							eaten_ndx = j;
							current_pop_size--;
						}
					}
				}

				if (one_eaten)
				{
					std::cout << "OH NO! Rabbit ";
					rabbits[i] -> print_id();
					std::cout << " has eaten Rabbit "; 
					rabbits[eaten_ndx] -> print_id();
					std::cout << " because of their Cannibalistic Trait!\n";
					rabbits.erase(rabbits.begin() + eaten_ndx);
					one_eaten = false;
				}
				else
				{
					all_full = true;
				}
			}
		}
	}while(!all_full && rabbits.size() > 1);
}

void enviorment::strong_rabbits_take_food() 
{
	int victim_strength_chance;
	int perp_strength_chance;
	bool acceptable_steal; // Based on food type
	/*
	 *  If a rabbit has no food it will attempt to take it from another with it
	 *      Rolls work the same way as the cannibal rabbit except it is entirely based on str
	 *   
	 */

	 for (int i = 0; i < rabbits.size(); i++)
	 {
	 	for (int j = 0; j < rabbits.size(); j++)
		{
			if (i != j)
			{
				if ( (!(*(rabbits[i] -> has_eaten()))) && (*(rabbits[j] -> has_eaten())) )
				{
					perp_strength_chance   = (rand() % 100) + (1000 * *(rabbits[i] -> get_dec_strength()));
					victim_strength_chance = 1000 * *(rabbits[j] -> get_dec_strength());
					
					if ( !(*(rabbits[i] -> get_carniverous())) )
					{
						acceptable_steal = *(rabbits[j] -> veg_food());
					}
					else
					{
						acceptable_steal = true;
					}

					if ( (perp_strength_chance > victim_strength_chance) && acceptable_steal )
					{
						*(rabbits[j] -> has_eaten()) = false;
						*(rabbits[i] -> has_eaten()) = true;
						std::cout << "Rabbit ";
						rabbits[i] -> print_id();
						std::cout << " stole Rabbit "; 
						rabbits[j] -> print_id(); 
						std::cout << "'s food!\n";
					}
				}
			}
		}
	 }
}

void enviorment::rabbits_starve() 
{
	std::vector<rabbit*>::iterator iter;

	for(iter = rabbits.begin(); iter != rabbits.end(); )
	{
		if ( !( *((*iter) -> has_eaten()) ) )
		{
			std::cout << "Rabbit ";
			(*iter) -> print_id();
			std::cout << " could not obtain food... they have died of starvation...\n";
			iter = rabbits.erase(iter);	
		}
		else
		{
			++iter;
		}
	}

	for (int i = 0; i < rabbits.size(); i++)
	{
		*(rabbits[i] -> has_eaten()) = false;
	}

}
void enviorment::predators_eat() 
{
	std::vector<rabbit*>::iterator iter;
	
	int predator_speed_odds    = 0;
	int predator_color_odds    = 0;

	int rabbit_escape_odds     = 0;
	int rabbit_undetected_odds = 0;

	int temp_pred_color        = 0;

	switch (land_type)
	{
		case 0: // standard - middle gray best
			predator_color_odds = 125000;
			break;
		case 1: // snow - white best
			break;
		case 2: // swamp - dark gray best rabbit swimming matters here
			break;
		case 3: // desert - light gray best
			break;
	}
	switch (predator_types)
	{
		case 0: // standard - low preds
			predator_speed_odds = 100000;
			break;
		case 1: // no preditors
			break;
		case 2: // medium preditors
			break;
		case 3: // heavy preditors
			break;
	}

	for(iter = rabbits.begin(); iter != rabbits.end(); )
	{
		temp_pred_color = predator_color_odds;

		rabbit_escape_odds     = *((*iter) -> get_dec_speed()) * 1000 + (rand() % 200) - 2;
		rabbit_undetected_odds = *((*iter) -> get_dec_color()) * 1000 + (rand() % 200) - 100;
			
		if ( (*((*iter) -> get_nocturnal())) )
		{
			temp_pred_color = predator_color_odds * 2;	
		}
		if (land_type == 0)
		{
			if ( (rabbit_undetected_odds < (temp_pred_color + (rand() % 5000))) && ((temp_pred_color - (rand() % 5000)) < rabbit_undetected_odds) )
			{
				std::cout << "Predators did not notice Rabbit ";
				(*iter) -> print_id();
				std::cout << "...\n";
				++iter;
			}
			else
			{
				std::cout << "Predators spotted Rabbit ";
				(*iter) -> print_id();
				std::cout << "...\n";

				if (rabbit_escape_odds > predator_speed_odds)
				{
					std::cout << "Rabbit ";
					(*iter) -> print_id();
					std::cout << " escaped the predator!\n";
					++iter;
				}
				else
				{
					std::cout << "Rabbit ";
					(*iter) -> print_id();
					std::cout << " was eaten by the predator...\n";
					iter = rabbits.erase(iter);
				}
			}
		}
		else
		{
			// under construction
		}
	}
}
void enviorment::rabbits_temperature() 
{
	std::vector<rabbit*>::iterator iter;
	int temp_max = (40 - temperature) * 1000 + 2000;
	int temp_min = (40 - temperature) * 1000 - 2000;

	int rabbit_fur_temp = 0;

	for (iter = rabbits.begin(); iter != rabbits.end(); )
	{
		/*
		 *  If Rabbit is nocturnal the tempurature is colder (two ifs because different outputs)
		 */
		if ( *((*iter) -> get_nocturnal()) )
		{
			rabbit_fur_temp = *((*iter) -> get_dec_fur()) * 200 + (rand() % 2000) - 1000;
			
			if ( (((temp_min * 4) / 3) < rabbit_fur_temp) && (rabbit_fur_temp < ((temp_max * 4) / 3)) )
			{
				std::cout << "Rabbit "; (*iter) -> print_id(); std::cout << " was comfortable through the night...\n";
				++iter;
			}
			else
			{
				if (rabbit_fur_temp > (temp_max * 4) / 3)
				{
					std::cout << "Rabbit "; (*iter) -> print_id(); std::cout << " was too hot during the night and died of heat stroke...\n";
				}
				else
				{
					std::cout << "Rabbit "; (*iter) -> print_id(); std::cout << " was too cold during the night and died of hypothermia...\n";
				}

				iter = rabbits.erase(iter);
			}
		}
		/*
		 *  If Rabbit is not nocturnal temperature is standard
		 */
		else
		{
			rabbit_fur_temp = *((*iter) -> get_dec_fur()) * 200 + (rand() % 2000) - 1000;

			if ( (temp_min < rabbit_fur_temp) && (rabbit_fur_temp < temp_max) )
			{
				std::cout << "Rabbit "; (*iter) -> print_id(); std::cout << " was comfortable through the day...\n";
				++iter;
			}
			else
			{
				if (rabbit_fur_temp > temp_max)
				{
					std::cout << "Rabbit "; (*iter) -> print_id(); std::cout << " was too hot during the day and died of heat stroke...\n";
				}
				else
				{
					std::cout << "Rabbit "; (*iter) -> print_id(); std::cout << " was too cold during the day and died of hypothermia...\n";
				}
				
				iter = rabbits.erase(iter);
			}
		}

	}
}
void enviorment::rabbits_drown() 
{
	// no enviorment currently uses water so i'll add this in when I have a swamp biome going
}
bool enviorment::enough_to_reproduce() 
{
	return (rabbits.size() > 1);
}
bool enviorment::all_dead()
{
	return (rabbits.size() == 0);
}
void enviorment::rabbit_shuffle() 
{
	/*
	 *   Shuffles the Rabbits around in the vector 
	 *      So that it ensure the same rabbits don't keep reproducing together
	 */
	
	srand(time(NULL));
	int num_swaps    = (rabbits.size() / 2);
	int swap_count   = 0;
	int ndx1 = 0;
	int ndx2 = 0;
	
	std::cout << "Shuffling Rabbits.\n";

	do
	{
		do // ensure not swapping same rabbit
		{
			ndx1 = rand() % rabbits.size();
			ndx2 = rand() % rabbits.size();
		}while (ndx1 == ndx2);
		std::cout << "Swapping Rabbit at index " << ndx1 << " with Rabbit at index " << ndx2 << std::endl;

		std::swap(rabbits[ndx1], rabbits[ndx2]);
		swap_count++;
	}while (swap_count < num_swaps);
	
}
void enviorment::rabbits_reproduce()
{
	int split_ndx;
	int baby_start_ndx = rabbits.size();
	int mut_val;
	int mut_ndx;
	
	int dec;
	std::stack<int> dec_calc;
	
	
	for (int i = 0; i < baby_start_ndx - 1; i++)
	{
		rabbits.push_back(new rabbit(rabbit_type));
		split_ndx = rand() % 6 + 1;
		
		/*
		 *   Fur DNA split + mutation
		 */
		for (int j = 0; j < 8; j++)
		{
			if (j < split_ndx)
			{
				*((rabbits[baby_start_ndx + i] -> get_fur()) + j) = *((rabbits[i] -> get_fur()) + j);
			}
			else
			{
				*((rabbits[baby_start_ndx + i] -> get_fur()) + j) = *((rabbits[i + 1] -> get_fur()) + j);
			}

		}
		if (rand() % 10 == 0) // 10% chance of mutation
		{
			mut_ndx = rand() % 8;
			mut_val = *((rabbits[baby_start_ndx + i] -> get_fur()) + mut_ndx);

			if (mut_val == 1)
			{
				mut_val = 0;
			}
			else
			{
				mut_val = 1;
			}

			*((rabbits[baby_start_ndx + i] -> get_fur()) + mut_ndx) = mut_val;
		}

		for (int j = 0; j < 8; j++)
		{
			dec_calc.push(*((rabbits[baby_start_ndx + i] -> get_fur()) + j));
		}
		for (int j = 0; j < 8; j++)
		{
			dec += pow(2, j) * dec_calc.top();
			dec_calc.pop();
		}

		*(rabbits[baby_start_ndx + i] -> get_dec_fur()) = dec;
		dec = 0; 
	
	    split_ndx = rand() % 6 + 1;

        /*
         *   color DNA split + mutation
         */
        for (int j = 0; j < 8; j++)
        {
            if (j < split_ndx)
            {
                *((rabbits[baby_start_ndx + i] -> get_color()) + j) = *((rabbits[i] -> get_color()) + j);
            }
            else
            {
                *((rabbits[baby_start_ndx + i] -> get_color()) + j) = *((rabbits[i + 1] -> get_color()) + j);
            }

        }
        if (rand() % 10 == 0) // 10% chance of mutation
        {
            mut_ndx = rand() % 8;
            mut_val = *((rabbits[baby_start_ndx + i] -> get_color()) + mut_ndx);

            if (mut_val == 1)
            {
                mut_val = 0;
            }
            else
            {
                mut_val = 1;
            }

            *((rabbits[baby_start_ndx + i] -> get_color()) + mut_ndx) = mut_val;
        }

        for (int j = 0; j < 8; j++)
        {
            dec_calc.push(*((rabbits[baby_start_ndx + i] -> get_color()) + j));
        }
        for (int j = 0; j < 8; j++)
        {
            dec += pow(2, j) * dec_calc.top();
            dec_calc.pop();
        }

        *(rabbits[baby_start_ndx + i] -> get_dec_color()) = dec;
        dec = 0;

        split_ndx = rand() % 6 + 1;

        /*
         *   strength DNA split + mutation
         */
        for (int j = 0; j < 8; j++)
        {
            if (j < split_ndx)
            {
                *((rabbits[baby_start_ndx + i] -> get_strength()) + j) = *((rabbits[i] -> get_strength()) + j);
            }
            else
            {
                *((rabbits[baby_start_ndx + i] -> get_strength()) + j) = *((rabbits[i + 1] -> get_strength()) + j);
            }

        }
        if (rand() % 10 == 0) // 10% chance of mutation
        {
            mut_ndx = rand() % 8;
            mut_val = *((rabbits[baby_start_ndx + i] -> get_strength()) + mut_ndx);

            if (mut_val == 1)
            {
                mut_val = 0;
            }
            else
            {
                mut_val = 1;
            }

            *((rabbits[baby_start_ndx + i] -> get_strength()) + mut_ndx) = mut_val;
        }

        for (int j = 0; j < 8; j++)
        {
            dec_calc.push(*((rabbits[baby_start_ndx + i] -> get_strength()) + j));
        }
        for (int j = 0; j < 8; j++)
        {
            dec += pow(2, j) * dec_calc.top();
            dec_calc.pop();
        }

        *(rabbits[baby_start_ndx + i] -> get_dec_strength()) = dec;
        dec = 0;

        split_ndx = rand() % 6 + 1;

        /*
         *   speed DNA split + mutation
         */
        for (int j = 0; j < 8; j++)
        {
            if (j < split_ndx)
            {
                *((rabbits[baby_start_ndx + i] -> get_speed()) + j) = *((rabbits[i] -> get_speed()) + j);
            }
            else
            {
                *((rabbits[baby_start_ndx + i] -> get_speed()) + j) = *((rabbits[i + 1] -> get_speed()) + j);
            }

        }
        if (rand() % 10 == 0) // 10% chance of mutation
        {
            mut_ndx = rand() % 8;
            mut_val = *((rabbits[baby_start_ndx + i] -> get_speed()) + mut_ndx);

            if (mut_val == 1)
            {
                mut_val = 0;
            }
            else
            {
                mut_val = 1;
            }

            *((rabbits[baby_start_ndx + i] -> get_speed()) + mut_ndx) = mut_val;
        }

        for (int j = 0; j < 8; j++)
        {
            dec_calc.push(*((rabbits[baby_start_ndx + i] -> get_speed()) + j));
        }
        for (int j = 0; j < 8; j++)
        {
            dec += pow(2, j) * dec_calc.top();
            dec_calc.pop();
        }

        *(rabbits[baby_start_ndx + i] -> get_dec_speed()) = dec;
        dec = 0;

        split_ndx = rand() % 6 + 1;

        /*
         *   swimming DNA split + mutation
         */
        for (int j = 0; j < 8; j++)
        {
            if (j < split_ndx)
            {
                *((rabbits[baby_start_ndx + i] -> get_swimming()) + j) = *((rabbits[i] -> get_swimming()) + j);
            }
            else
            {
                *((rabbits[baby_start_ndx + i] -> get_swimming()) + j) = *((rabbits[i + 1] -> get_swimming()) + j);
            }

        }
        if (rand() % 10 == 0) // 10% chance of mutation
        {
            mut_ndx = rand() % 8;
            mut_val = *((rabbits[baby_start_ndx + i] -> get_swimming()) + mut_ndx);

            if (mut_val == 1)
            {
                mut_val = 0;
            }
            else
            {
                mut_val = 1;
            }

            *((rabbits[baby_start_ndx + i] -> get_swimming()) + mut_ndx) = mut_val;
        }

        for (int j = 0; j < 8; j++)
        {
            dec_calc.push(*((rabbits[baby_start_ndx + i] -> get_swimming()) + j));
        }
        for (int j = 0; j < 8; j++)
        {
            dec += pow(2, j) * dec_calc.top();
            dec_calc.pop();
        }

        *(rabbits[baby_start_ndx + i] -> get_dec_swimming()) = dec;
        dec = 0;
		
		/*
		 *    Special Mutations 
		 *           All -> Inherited if Both Parents are carriers
		 *           Nocturnal -> 2% Chance 
		 *           Carnivour -> 1% Chance
		 *           Cannibal -> 1% Chance if Carnivour trait is present in both parents (no roll otherwise)
		 */

		std::cout << "Rabbit "; (rabbits[i] -> print_id()); std::cout << " and Rabbit "; (rabbits[i+1] -> print_id()); 
		std::cout << "\n------> Rabbit "; (rabbits[baby_start_ndx + i] -> print_id()); std::cout << "\n";
		
		if ( *(rabbits[i] -> get_nocturnal()) && *(rabbits[i+1] -> get_nocturnal()) )
		{
			*(rabbits[baby_start_ndx + i] -> get_nocturnal()) = true;
		}
		else
		{
			if (rand() % 100 <= 1)
			{
				std::cout << "Baby Rabbit "; (rabbits[baby_start_ndx + i] -> print_id()); std::cout << " is Nocturnal!\n";
				*(rabbits[baby_start_ndx + i] -> get_nocturnal()) = true;
			}
		}

		if ( *(rabbits[i] -> get_carniverous()) && *(rabbits[i+1] -> get_carniverous()) )
		{
			*(rabbits[baby_start_ndx + i] -> get_carniverous()) = true;
			if (rand() % 100 == 0)
			{
				std::cout << "Oh Dear! Baby Rabbit "; (rabbits[baby_start_ndx + i] -> print_id()); std::cout << " is a Cannibal!\n";
				*(rabbits[baby_start_ndx + i] -> get_cannibalistic()) = true;
			}
		}
		else
		{
			if (rand() % 100 == 0)
			{
				std::cout << "Baby Rabbit "; (rabbits[baby_start_ndx + i] -> print_id()); std::cout << " is Carniverous!\n";
				*(rabbits[baby_start_ndx + i] -> get_carniverous()) = true;
			}
		}

		if ( *(rabbits[i] -> get_cannibalistic()) && *(rabbits[i+1] -> get_cannibalistic()) )
		{
			*(rabbits[baby_start_ndx + i] -> get_cannibalistic()) = true;
		}

	}
}
void enviorment::display_stat_chart()
{
	int dummy_out = 0;
	//              10 sp     5 
	std::cout << "RABBIT ID | FUR | COL | STR | SPD | SWM | NOC | CAR | CAN |\n";
	std::cout << "-----------------------------------------------------------\n";
	for (int i = 0; i < rabbits.size(); i++)
	{
		std::cout << " "; (rabbits[i] -> print_id()); std::cout << "      | ";
		dummy_out = *(rabbits[i] -> get_dec_fur());
		
		if (dummy_out < 10)
		{
			std::cout << dummy_out << "   | ";
		}
		else if (dummy_out < 100)
		{
			std::cout << dummy_out << "  | ";
		}
		else
		{
			std::cout << dummy_out << " | ";
		}

        dummy_out = *(rabbits[i] -> get_dec_color());

        if (dummy_out < 10)
        {
            std::cout << dummy_out << "   | ";
        }
        else if (dummy_out < 100)
        {
            std::cout << dummy_out << "  | ";
        }
        else
        {
            std::cout << dummy_out << " | ";
        }

        dummy_out = *(rabbits[i] -> get_dec_strength());

        if (dummy_out < 10)
        {
            std::cout << dummy_out << "   | ";
        }
        else if (dummy_out < 100)
        {
            std::cout << dummy_out << "  | ";
        }
        else
        {
            std::cout << dummy_out << " | ";
        }

        dummy_out = *(rabbits[i] -> get_dec_speed());

        if (dummy_out < 10)
        {
            std::cout << dummy_out << "   | ";
        }
        else if (dummy_out < 100)
        {
            std::cout << dummy_out << "  | ";
        }
        else
        {
            std::cout << dummy_out << " | ";
        }

        dummy_out = *(rabbits[i] -> get_dec_swimming());

        if (dummy_out < 10)
        {
            std::cout << dummy_out << "   | ";
        }
        else if (dummy_out < 100)
        {
            std::cout << dummy_out << "  | ";
        }
        else
        {
            std::cout << dummy_out << " | ";
        }

		if ( *(rabbits[i] -> get_nocturnal()) )
		{
			std::cout << " X  | ";
		}
		else
		{
			std::cout << "    | ";
		}

        if ( *(rabbits[i] -> get_carniverous()) )
        {
            std::cout << " X  | ";
        }
        else
        {
            std::cout << "    | ";
        }

        if ( *(rabbits[i] -> get_cannibalistic()) )
        {
            std::cout << " X  | ";
        }
        else
        {
            std::cout << "    | ";
        }

		std::cout << "\n";

	}
	std::cout << "-----------------------------------------------------------\n";
}
