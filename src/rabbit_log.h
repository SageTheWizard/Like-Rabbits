#ifndef LOG_H
#define LOG_H

#include<string>
#include<vector>

class rabbit_log
{
	private:
		// Death Log
		std::vector<std::string> deaths;
		// Birth Log
		std::vector<std::string> births;
	public:
		rabbit_log();
		void print_death_log();
		void print_birth_log();

		void clear_logs();
		
		// Adds a Death to the log, String = Rabbit ID, Int = Death Reason Code
		void add_death(std::string, int);
		// Adds a Birth to the log, String = Rabbit Born ID, String = Parent1 ID, String = Parent2 ID
		void add_birth(std::string, std::string, std::string);
		
};
#endif
