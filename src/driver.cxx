#include <iostream>
#include <vector>
//#include "rabbit.h"
#include "enviorment.h"

int out_title();
int pick_rabbit();
int pick_env();
int num_of_generations();
int post_gen_input();
int gen_no_out_input();
void rip();
void clear();
void start_game();
void about();

int main()
{
	int choice;
	do
	{
		clear();
		choice = out_title();
		switch(choice)
		{
			case 1: 
				start_game();
				break;
			case 2: 
				// doesn't do anything rn until file loading works
				break;
			case 3:
				clear();
				about();
				break;
			case 4:
				// end
				break;
		}
	}while (choice != 4);
	
	return 0;
}

int out_title() 
{
    std::cout << "()()     ()()      ()()\n";
    std::cout << "(>.>)    (o.o)    (<.<)\n";
    std::cout << "(,,,)    (,,,)    (,,,)\n";
    std::cout << "-----------------------\n";
    std::cout << "...:::LIKE RABBITS:::..\n";
    std::cout << "_______________________\n";
	std::cout << " 1 - Start Evolution\n";
	std::cout << " 2 - Load Evolution\n"; 
	std::cout << " 3 - About\n";
	std::cout << " 4 - Exit\n";
    
	int input;
    do
    {
        std::cin.clear();
        std::cout<< "Select an option (1 - 4): ";
        std::cin >> input;
		std::cin.get();
    } while ( (input < 1) || (input > 4) );
	return input;
}
void clear()
{
	for (int i = 0; i < 50; i++) 
	{
		std::cout << "\n\n\n\n\n\n\n\n";
	}
	return;
}
void start_game()
{
	int rabbit_choice;
	int enviorment_choice;
	int generations;
	int gen_count;
	int post_gen_choice;
	int gen_until_next_input;

	rabbit_choice        = pick_rabbit();
	enviorment_choice    = pick_env();
	generations          = num_of_generations();
	gen_count            = 0;
	gen_until_next_input = 0;
	post_gen_choice      = 0;

	enviorment env = enviorment(enviorment_choice, rabbit_choice);
	
	clear();
	
	for (int i = 0; i < generations; i++) 
	{
		env.rabbits_eat();
		env.strong_rabbits_take_food();
		env.rabbits_starve();
		env.predators_eat();
		env.rabbits_temperature();
		env.rabbits_drown(); // useless rn
		env.increase_alive_time();
	
		if (env.enough_to_reproduce())
		{
			env.rabbit_shuffle();
			env.rabbits_reproduce();
		}
	
		if (env.all_dead())
		{
			rip();
			return;
		}
	
		std::cout << "Generation " << env.generation_num << " complete!\n";
		env.generation_num++;
		env.display_stat_chart();
		
		if (gen_count >= gen_until_next_input)
		{
			gen_count = 0;
			do
			{
				post_gen_choice = post_gen_input();
				
				switch (post_gen_choice)
				{
					case 1:
						clear();
						env.clear_logs();
						break;
					case 2:
						env.print_logs(0);
						break;
					case 3:
						env.print_logs(1);
						break;
					case 4:
						gen_until_next_input = gen_no_out_input();
						break;
					case 5:
						rip();
						return;
						
				}

			}while (post_gen_choice != 1);
		}
		gen_count++;
		
	}
	return;
	
}
int gen_no_out_input()
{
	int input;
    do
    {
        std::cin.clear();
		std::cout << "Enter number of generations until next input [0 - 10]: ";
        std::cin >> input;
        std::cin.get();
    } while ( (input < 0) || (input > 10) );
    return input;

}
int pick_rabbit()
{
	clear();
	std::cout << "=======================\n";
	std::cout << " 0 - Standard Rabbit \n";
	std::cout << "        ()()   \n";
	std::cout << "        (o.o)  \n";
	std::cout << "        (,,,)  \n";
	std::cout << " ----------------------\n";
	std::cout << " 1 - Ninja Rabbit   \n";
	std::cout << "        {}{}   \n";
	std::cout << "       ~{===}  \n";
	std::cout << "        {;;;}  \n";
	std::cout << "-----------------------\n";
	std::cout << " 2 - Fluffy Rabbit \n ";
	std::cout << "        {}{} \n";
	std::cout << "       {(o.o)} \n";
	std::cout << "       {(,,,)} \n";
	std::cout << "=======================\n";
	std::cout << "\n";
	
    int input;
    do
    {
        std::cin.clear();
        std::cout<< "Select an option (0 - 2): ";
        std::cin >> input;
        std::cin.get();
    } while ( (input < 0) || (input > 2) );
    return input;
}
int pick_env()
{
	clear();
	std::cout << "===========================\n";
	std::cout << " 0 - Standard Enviorment\n";
	std::cout << "  ___                    \n";
	std::cout << " |   | __                \n";
	std::cout << "  --- /  \\/---    nnnnnnn \n";
	std::cout << "      ------n--   (::::::)\n";
	std::cout << "                   (::::) \n";
	std::cout << "                    \\||/\n";
	std::cout << "                     ||\n";
	std::cout << " ...#.......@..#.....||......\n";
	std::cout << " :::|:::::::|::|:::::||::::::\n";
	std::cout << "-----------------------------\n";
	std::cout << " 1 - Snow Enviorment  \n";
	std::cout << "  ___                   \n";
	std::cout << " |   |   *    *   *  *    *  \n";
	std::cout << "  ---  *  * *   *      *  * *\n";
	std::cout << " * *    *     *   /\\  *   * \n";
	std::cout << "      *    *     // \\  *  *\n";
	std::cout << "  **    *    *  /////\\   * *\n";
	std::cout << "*     *    *    --||--  *  * \n";
	std::cout << " *****************||*********\n";
	std::cout << "=============================\n";
    
	int input;
    do
    {
        std::cin.clear();
        std::cout<< "Select an option (0 - 1): ";
        std::cin >> input;
        std::cin.get();
    } while ( (input < 0) || (input > 1) );
	return input;
}
int num_of_generations()
{
    int input;
    do
    {
        std::cin.clear();
		std::cout << "How many Generations would like like to run this for?\n";
        std::cout << "[10 - 999]: ";
        std::cin >> input;
        std::cin.get();
    } while ( (input < 10) || (input > 999) );
    
	return input;
}

int post_gen_input()
{
	int input;

	do
    {
        std::cout << "......................::: Control Panel :::..................\n";
		std::cout << "     1. Continue Run \n";
		std::cout << "     2. View Death Logs \n";
		std::cout << "     3. View Birth Logs \n";
		std::cout << "     4. Run for X Generations without Input \n";
		std::cout << "     5. Exit Run \n";
        std::cout << "Select an option (1 - 5): ";
        std::cin >> input;
        std::cin.get();


    } while ( (input < 1) || (input > 5) );

	return input;
}

void rip()
{
	clear();
	std::cout << "    ___\n";
	std::cout << "  /     \\     ()()\n";
	std::cout << " | r i p |   (x.x)\n";
	std::cout << " |_______|   (,,,)\n";
	std::cout << " ______________________ \n";
	std::cout << " ..::: GAME OVER :::... \n";
	std::cout << "  all your rabbits died!\n";
	std::cout << " ______________________\n";
	std::cin.get();
	return;
}
void about()
{
	std::cout << "A Genetic Algorithm made fun (at least I think so)\n";
	std::cout << "You send a colony of identical clones of rabbits to a distant planet of your choosing\n";
	std::cout << "Watch as they evolve to adapt to their new enviorment (or perish in it).\n\n";
	std::cout << "Developed by Jacob 'SageTheWizard' Gallucci\n";
	std::cout << "Version: .02 Alpha\n\n";
	std::cout << "Press any key to return to main menu....\n";
	std::cin.get();
	return;
}
