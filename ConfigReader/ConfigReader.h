#ifndef EIRE_CONFIG_READER_H
#define EIRE_CONFIG_READER_H

/** \class eire::ConfigReader
 * 
 * \brief ConfigReader allows to read in ASCII configuration files and provides an interface to the information.
 *
 * ASCII configuration files can have the following form:\n
 * [section:mother_section]\n
 * var1 = abcd\n
 * var2 = 5.\n
 * var3 = true\n
 *
 * With ConfigReader the information is provided which value a certain variable
 * in a certain section has. Boolean values can be checked as well as text
 * values. For double values a conversion before usage with
 * atof(string_value.c_str()) or atoi(string_value.c_str()) is necessary.
 * Inheritance among sections is allowed with a colon and the mother section
 * listed in the section header. All sections inherit from default.
 *
 * \authors walsh, klein
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <boost/xpressive/xpressive.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include <sys/stat.h> 
#include <cstdlib>

namespace eire{
	class ConfigReader{
		public:
			ConfigReader();
			~ConfigReader();

			/*!
			 * \brief Read list from ASCII file.
			 *
			 * Each line will be filled to a new entry in a vector<string>.
			 */
			void read_list_from_file(std::string filename);
			/// get list produced with read_list_from_file
			inline std::vector<std::string> *get_list(){ return list_from_file; };

			/// Read in config from file. Returns true if success.
			bool read_config_from_file(std::string filename, bool do_not_clear=false); //jl 21.01.11: bool fcn
			/*!
			 * \brief Return value for variable in given section.
			 *
			 * If need_var = true and the variable is not available,
			 * exit program. If need_var = false and variable not
			 * availabe, return empty string.
			 */
			std::string get_var(std::string name, std::string section="global",bool need_var = true);
			/// Transform variables to bool values. Accepted strings: true/false/True/False
			bool get_bool_var(std::string name, std::string section="global", bool need_var = true);
			/*!
			 * \brief Return vector of variables.
			 *
			 * The input format in the ASCII file is: var1 = value1:value2:value3:valu4:...
			 */
			std::vector<std::string> get_vec_var(std::string name, std::string section="global",bool need_var=true);
			void print_config();
			/// return all available sections found inconfiguration
			std::vector<std::string> *get_sections();
			/// return all available variables for a given section
			std::vector<std::string> get_variables_for_section(std::string section);

			bool variable_set(std::string variable, std::string section="global");
			bool section_defined(std::string section="global");
		private:
			bool FileExists(std::string strFilename);
			std::string lookup_var(std::string name, std::string section,bool need_var = true);
			void tokenise(std::string input, std::string seperators, std::vector<std::string> &output);

			std::map<std::string,std::map<std::string,std::string> > config;
			std::vector<std::string> *list_from_file;
			std::vector<std::string> *sections;	// sections in config, only filled on demand

			std::map<std::string, std::string> inheritance;	// section->inherits from
	};
}

#endif
