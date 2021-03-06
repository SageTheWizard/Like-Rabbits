#include<iostream>
#include<stack>
#include<math.h>
#include<string>
#include<stdlib.h>
#include<time.h>
#include"enviorment.h"
#include"rabbit_log.h"

enviorment::enviorment() {} // coming later

enviorment::enviorment(int env, int rab)
{
	std::string rabbit_out = "ERROR";
	std::string enviorment_out = "ERROR";
	rabbit_type = rab;
	longest_alive_rabbit = 0;

	planet_id += (char) ( (rand() % 26) + 65 );
	planet_id.append(std::to_string((rand() % 90) + 10));
	planet_id += (char) ( (rand() % 26) + 65 );
	planet_id.append(std::to_string((rand() % 10000) + 1000));

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
		case 2:
			rabbit_out = "Big Fluff Rabbits, specifically created to surivive cold winters";
			break;
	}

	switch (env)
	{
		case 0: // standard
			predator_types    = 0;
			land_type         = 0;
			veg_food_amount   = 20;
			meat_food_amount  = 10;
			temperature       = 18;
			
			enviorment_out = "Green grass land with considerable number of trees home to squirrel-like creatures.\nA few foxes seem to roam about but not many predators roam this area...\nThe temperature is moderate.\n";
			break;

		case 1: // snow
			predator_types    = 0;
			land_type         = 1;
			veg_food_amount   = 5;
			meat_food_amount  = 10;
			temperature       = 1;
			
			enviorment_out = "Snow Tundra... Not much greenery, a few conifer trees covered in snow.\nAfew small animals scuttle around.\nA few snow foxes roam about but not many predators are around...\nThe temperature is very cold.\n";
			break;
	}
	
	srand(time(NULL));
	std::cout << "You and you team launch your team of " << rabbit_out << " into interstellar space...\n" 
	          << "You hear a signal that the FTL Drive on the ship has kicked in and await anxiously for the notification that the ship has arrived at its destination...\n"
			  << "Once the ship has arrived at the Planet " << planet_id << " the ships cameras kick on..\n"
			  << "You see ... \n" << enviorment_out << "The rabbits begin their journey.\n\n"
			  << "RABBIT STARTING STATS AT GENERATION 0: \n";
	
	std::cin.get();
	for (int i = 0; i < 20; i++)
	{
		std::cout << "RABBIT ";
		rabbits[i] -> print_id();
		std::cout << "\n";
		rabbits[i] -> show_stats();
	}
	std::cin.get();
}

void enviorment::rabbits_eat() 
{
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
	
	std::vector<rabbit*>::iterator iter1;
	std::vector<rabbit*>::iterator iter2;

	/*
	 *    cannibal rabbit rolls between 0 -> 257000 on speed and asme on str
	 *                 the roll adds the cannibal rabbits speed_dec and str_dec * 10 to roll
	 *    victim's odds of not getting caught are speed_dec * 1000 (same w/ str)
	 *    if cannibal rolls higher than the number from above, on BOTH rolls, it eats the rabbit
	 *
	 *    These odds may be adjusted if it is too common for the cannibal to eat the others
	 */

	for (iter1 = rabbits.begin(); iter1 != rabbits.end(); )
	{
		for (iter2 = rabbits.begin(); iter2 != rabbits.end(); )
		{
			if (std::distance(rabbits.begin(), iter1) != std::distance(rabbits.begin(), iter2))
			{
				if ( *((*iter1) -> get_cannibalistic()) && !(*((*iter1) -> has_eaten())) )
				{
					victim_speed_chance = *((*iter2) -> get_dec_speed()) * 1000;
					victim_str_chance = *((*iter2) -> get_dec_strength()) * 1000;
					
					cannib_speed_roll = *((*iter1) -> get_dec_speed()) * 1000;
					cannib_str_roll = *((*iter1) -> get_dec_strength()) * 1000;
						
					cannib_speed_roll += ((rand() % 2000) - 1000);
					cannib_str_roll += ((rand() % 2000) - 1000);

					if ( (cannib_speed_roll > victim_speed_chance) && (cannib_str_roll > victim_str_chance) )
					{
						*((*iter1) -> has_eaten()) = true;
						iter2 = rabbits.erase(iter2);
					}
					else
					{
						++iter2;
					}

				}
				else
				{
					++iter2;
				}
			}
			else
			{
				++iter2;
			}

			victim_speed_chance = victim_str_chance = cannib_speed_roll = cannib_str_roll = 0;
		}
		++iter1;
	}		
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
			logs.add_death((*iter) -> print_id(), 0);
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
			predator_color_odds = 24000;
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
				++iter;
			}
			else
			{
				if (rabbit_escape_odds > predator_speed_odds)
				{
					++iter;
				}
				else
				{
					logs.add_death((*iter) -> print_id(), 1);
					iter = rabbits.erase(iter);
				}
			}
		}
		else if (land_type == 1)
		{
			if (rabbit_undetected_odds < (temp_pred_color + (rand() % 6000) - 2000))
			{
				++iter;
			}
			else
			{
				if (rabbit_escape_odds > predator_speed_odds)
				{
					++iter;
				}
				else
				{
					logs.add_death((*iter) -> print_id(), 1);
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
				++iter;
			}
			else
			{
				if (rabbit_fur_temp > (temp_max * 4) / 3)
				{
					logs.add_death((*iter) -> print_id(), 4);
				}
				else
				{
					logs.add_death((*iter) -> print_id(), 3);
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
				++iter;
			}
			else
			{
				if (rabbit_fur_temp > temp_max)
				{
					logs.add_death((*iter) -> print_id(), 4);
				}
				else
				{
					logs.add_death((*iter) -> print_id(), 3);
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
	
	do
	{
		do // ensure not swapping same rabbit
		{
			ndx1 = rand() % rabbits.size();
			ndx2 = rand() % rabbits.size();
		}while (ndx1 == ndx2);

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
	
	int dec = 0;
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
		
		logs.add_birth(rabbits[baby_start_ndx + i] -> print_id(), rabbits[i] -> print_id(), rabbits[i+1] -> print_id());

		
		if ( *(rabbits[i] -> get_nocturnal()) && *(rabbits[i+1] -> get_nocturnal()) )
		{
			*(rabbits[baby_start_ndx + i] -> get_nocturnal()) = true;
		}
		else
		{
			if (rand() % 100 <= 1)
			{
				*(rabbits[baby_start_ndx + i] -> get_nocturnal()) = true;
			}
		}

		if ( *(rabbits[i] -> get_carniverous()) && *(rabbits[i+1] -> get_carniverous()) )
		{
			*(rabbits[baby_start_ndx + i] -> get_carniverous()) = true;
			if (rand() % 100 == 0)
			{
				*(rabbits[baby_start_ndx + i] -> get_cannibalistic()) = true;
			}
		}
		else
		{
			if (rand() % 100 == 0)
			{
				*(rabbits[baby_start_ndx + i] -> get_carniverous()) = true;
			}
		}

		if ( *(rabbits[i] -> get_cannibalistic()) && *(rabbits[i+1] -> get_cannibalistic()) )
		{
			*(rabbits[baby_start_ndx + i] -> get_cannibalistic()) = true;
		}

	}
}
void enviorment::increase_alive_time()
{
	int dummy = 0;

	for (int i = 0; i < rabbits.size(); i++)
	{
		dummy = rabbits[i] -> generations_alive;
		dummy++;
		rabbits[i] -> generations_alive = dummy;
	}
}
void enviorment::display_stat_chart()
{
	int dummy_out  = 0;
	int eldest_ndx = 0;

	//              10 sp     5 
	std::cout << "RABBIT ID | FUR | COL | STR | SPD | SWM | NOC | CAR | CAN | AGE | \n";
	std::cout << "-----------------------------------------------------------------\n";
	for (int i = 0; i < rabbits.size(); i++)
	{
		if ( (rabbits[eldest_ndx] -> generations_alive) < (rabbits[i] -> generations_alive) )
		{
			eldest_ndx = i;
		}
		
		std::cout << " " << (rabbits[i] -> print_id()) << "      | ";
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

		dummy_out = (rabbits[i] -> generations_alive);
        
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

		std::cout << "\n";

	}
	std::cout << "-----------------------------------------------------------------\n";
	std::cout << " Best Rabbit's Stats : \n";
	std::cout << "     ID:  " << (rabbits[eldest_ndx] -> print_id()) << "\n";
	std::cout << "     FUR: " << *(rabbits[eldest_ndx] -> get_dec_fur()) << "\n";
	std::cout << "     COL: " << *(rabbits[eldest_ndx] -> get_dec_color()) << "\n";
	std::cout << "     STR: " << *(rabbits[eldest_ndx] -> get_dec_strength()) << "\n";
	std::cout << "     SPD: " << *(rabbits[eldest_ndx] -> get_dec_speed()) << "\n";
	std::cout << "     SWM: " << *(rabbits[eldest_ndx] -> get_dec_swimming()) << "\n";
	std::cout << "     NOC: ";
	if ( *(rabbits[eldest_ndx] -> get_nocturnal()) )
	{
		std::cout << "YES\n";
	}
	else
	{
		std::cout << "NO\n";
	}
    std::cout << "     CAR: ";
    if ( *(rabbits[eldest_ndx] -> get_carniverous()) )
    {
        std::cout << "YES\n";
    }
    else
    {
        std::cout << "NO\n";
    }
    std::cout << "     CAN: ";
    if ( *(rabbits[eldest_ndx] -> get_cannibalistic()) )
    {
        std::cout << "YES\n";
    }
    else
    {
        std::cout << "NO\n";
    }
}

void enviorment::print_logs(int log_type)
{
	switch (log_type)
	{
		case 0:
			logs.print_death_log();
			break;
		case 1:
			logs.print_birth_log();
			break;
	}
}
void enviorment::clear_logs()
{
	logs.clear_logs();
}
