#include "ConfigReader.h"

eire::ConfigReader::ConfigReader()
{
	list_from_file = new std::vector<std::string>();
	sections = new std::vector<std::string>();
}

eire::ConfigReader::~ConfigReader()
{
	if(list_from_file){
		delete list_from_file;
		list_from_file = NULL;
	}
	if(sections){
		delete sections;
		sections = NULL;
	}
}

void eire::ConfigReader::read_list_from_file(std::string filename)
{
	list_from_file->clear();

        std::string line;
	std::ifstream infile;
	infile.open(filename.c_str());
        while(!infile.eof()) // To get you all the lines.
        {
	        getline(infile,line); // Saves the line in STRING.
		if(line.size() > 0)
			list_from_file->push_back(line);
        }
	infile.close();
}

void eire::ConfigReader::print_config()
{
	for(std::map<std::string,std::map<std::string, std::string> >::iterator section = config.begin();
		section != config.end();
		++section){
		std::cout << "[" << section->first << "]" << std::endl;
		for(std::map<std::string, std::string>::iterator entry = section->second.begin();
			entry != section->second.end();
			++entry){
			std::cout << entry->first << " = " << entry->second << std::endl;
		}
	}
}

//jl 21.01.11: make fcn bool
bool eire::ConfigReader::read_config_from_file(std::string filename, bool do_not_clear)
{
	if(!FileExists(filename)){
		std::cerr << "ERROR: config file " << filename << " does not exist! " << std::endl;
		return false;
	}
	if(!do_not_clear) config.clear();	

	std::string section = "global";

        std::string line;
	std::ifstream infile;
	infile.open(filename.c_str());
        while(!infile.eof()) // To get you all the lines.
        {
	        getline(infile,line); // Saves the line in STRING.

		boost::xpressive::sregex re = boost::xpressive::sregex::compile("#.*");                // find all occurrences of "" ...
		std::string replacement("");                // ... and replace them with ""
		if(line.find("\\#") != std::string::npos){
			re = boost::xpressive::as_xpr("\\#");
			replacement = "#";                // ... and replace them with ""
		}
		line = boost::xpressive::regex_replace(line, re, replacement );

		re = boost::xpressive::sregex::compile(";.*");
		line = boost::xpressive::regex_replace(line, re, replacement );

		std::string sre; // regular expression
		sre = "\\[(.*)\\]";
        	boost::regex match_re;        // boost regular expression object
        	boost::cmatch matches;  // vector with the matches for the regex
        	match_re.assign(sre, boost::regex_constants::icase);  // asssign string to regex, make regex case insensitive
        	// match regex
        	bool matched = boost::regex_match(line.c_str(), matches, match_re);
       		// return error if hist name didn't match
       		if(matched && matches.size() == 2){
			// define new section
			std::string match(matches[1].first, matches[1].second);
			section = match;
			boost::trim(section);

			if(section.find(":") != std::string::npos){
				int colon_pos = section.find(":");	
				std::string parent = section.substr(colon_pos+1,section.size());
				section = section.substr(0,colon_pos);
				inheritance[section] = parent;
			}
        	}else{
			sre = "(.*)=(.*)";
        		match_re.assign(sre, boost::regex_constants::icase);  // asssign string to regex, make regex case insensitive
        		matched = boost::regex_match(line.c_str(), matches, match_re);
       			if(matched && matches.size() == 3){
				std::string key(matches[1].first, matches[1].second);
				std::string value(matches[2].first, matches[2].second);
				boost::trim(key);
				boost::trim(value);
				config[section][key] = value;
			}
		}
        	// after regex match we have one vector with the different matches,
        	// fill those to different strings of class
        }
	infile.close();
	return true;
}

std::string eire::ConfigReader::get_var(std::string name, std::string section,bool need_var)
{
	return lookup_var(name, section,need_var);
}


bool eire::ConfigReader::FileExists(std::string strFilename){
  struct stat stFileInfo;
  bool blnReturn;
  int intStat;

  // Attempt to get the file attributes
  intStat = stat(strFilename.c_str(),&stFileInfo);
  if(intStat == 0) {
    // We were able to get the file attributes
    // so the file obviously exists.
    blnReturn = true;
  } else {
    // We were not able to get the file attributes.
    // This may mean that we don't have permission to
    // access the folder which contains this file. If you
    // need to do that level of checking, lookup the
    // return values of stat which will give you
    // more details on why stat failed.
    blnReturn = false;
  }
  
  return(blnReturn);
}

bool eire::ConfigReader::get_bool_var(std::string name, std::string section, bool need_var)
{
	std::string var = lookup_var(name, section,need_var);
	if(var == "true" || var == "True")
		return true;
	if(var == "false" || var == "False")
		return false;
	else{
		if(need_var){
			std::cout << "WARNING: ConfigReader::get_bool_var() variable: " << name << " section " << section << " not of type bool: " << var << std::endl;
			exit(1);
		}
		return false;
	}
}

std::string eire::ConfigReader::lookup_var(std::string name, std::string section,bool need_var)
{
	if(config.find(section) == config.end()){
		std::cerr << "eire::ConfigReader::lookup_var(): invalid section: " << section << std::endl;
		return "";
	}
	if(config[section].find(name) == config[section].end()){
		if(section != "global") //check if var is in global
			if(inheritance.find(section) != inheritance.end())
				return lookup_var(name,inheritance[section],need_var);
			else
				return lookup_var(name,"global",need_var);
		else{
			if(need_var){
				std::cerr << "ERROR: eire::ConfigReader::lookup_var(): invalid variable: " << name << " section: " << section << std::endl;
				exit(1);
			}
			return "";
		}
	}

	return config[section][name];
}

// specify variables in the format
// var = part1:part2:part3:part4
// returns for variable "var" vector[0] = "part1", vector[1] = "part2", ...
std::vector<std::string> eire::ConfigReader::get_vec_var(std::string name, std::string section,bool need_var)
{
	std::vector<std::string> tokens;
	std::string variable = lookup_var(name, section, need_var);

	tokenise(variable, ",:", tokens);

	return tokens;
}

// reads in string, breaks it apart according to seperators and fills everything to output vector
void eire::ConfigReader::tokenise(std::string input, std::string seperators, std::vector<std::string> &output)
{
	// clear old tokens
	output.clear();
	
	std::string str = input;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(seperators.c_str());
	tokenizer tokens(str, sep);
	for (tokenizer::iterator tok_iter = tokens.begin();
	     tok_iter != tokens.end(); ++tok_iter){
		output.push_back(*tok_iter);
	}
}

std::vector<std::string> *eire::ConfigReader::get_sections()
{
	sections->clear();
	for(std::map<std::string,std::map<std::string, std::string> >::iterator section = config.begin();
		section != config.end();
		++section){
		sections->push_back(section->first);
	}
	
	return sections;
}

std::vector<std::string> eire::ConfigReader::get_variables_for_section(std::string section)
{
	std::vector<std::string> variables;

	if(config.find(section) != config.end()){
		for(std::map<std::string, std::string>::iterator variable = config[section].begin();
			variable != config[section].end();
			++variable){
			variables.push_back(variable->first);
		}
		if(inheritance.find(section) != inheritance.end()){
			std::vector<std::string> inherited_variables = get_variables_for_section(inheritance[section]);
			std::map<std::string,bool> merged_variables;
			for(std::vector<std::string>::iterator inherited_variable = inherited_variables.begin();
				inherited_variable != inherited_variables.end();
				++inherited_variable){
				merged_variables[*inherited_variable] = true;
			}
			for(std::vector<std::string>::iterator variable = variables.begin();
				variable != variables.end();
				++variable){
				merged_variables[*variable] = true;
			}
			variables.clear();
			for(std::map<std::string,bool>::iterator var = merged_variables.begin();
				var != merged_variables.end();
				++var){
				variables.push_back(var->first);
			}
		}
	}else{
		std::cerr << "WARNING: eire::ConfigReader::get_variables_for_section(): cound not find section: " << section << std::endl;
	}

	return variables;
}

bool eire::ConfigReader::variable_set(std::string variable, std::string section)
{
	if(get_var(variable,section,false) != "")
		return true;
	else
		return false;
}

bool eire::ConfigReader::section_defined(std::string section)
{
	if(config.find(section) != config.end())
		return true;
	else
		return false;
}
