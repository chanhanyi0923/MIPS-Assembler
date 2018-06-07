#include <iostream>
#include <fstream>
#include <cerrno>

#include "R_Format.h"
#include "I_Format.h"
#include "J_Format.h"
#include "Label.h"
#include "Text.h"
#include "AssembleException.h"

// static variables in classes
std::map<std::string, int> Label::address_table;
R_Format Statement::R;
I_Format Statement::I;
J_Format Statement::J;

int main(int argc, char *argv[])
{
	if (argc != 4) {
		std::cerr << "Invalid number of arguments" << std::endl;
		return 1;
	}

	const char *input_filename = argv[1];
	const char *output_type = argv[2];
	const char *output_filename = argv[3];

	Text text;

	if (string(output_type) == string("-bin")) {
		text.setOutputType(Text::bin);
	} else if (string(output_type) == string("-coe")) {
		text.setOutputType(Text::coe);
	} else {
		std::cerr << "Unknown output type." << std::endl;
		return 1;
	}

	std::fstream input, output;

	input.exceptions(std::fstream::badbit);
	output.exceptions(std::fstream::badbit);

	try {
		input.open(input_filename, std::fstream::in | std::fstream::binary);
		if (!input) {
			throw std::system_error{ errno, std::generic_category() };
		}
		input >> text;
	} catch (AssembleException const & e) {
		std::cerr << e.what() << std::endl;
		return 1;
	} catch (std::system_error const & e) {
		std::cerr << "Input: " << e.code() << " - " << e.what() << std::endl;
		return 1;
	} catch (std::exception const & e) {
		std::cerr << "Input: " << e.what() << std::endl;
		return 1;
	}
	
	input.close();

	try {
		text.process();
	} catch (AssembleException const & e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	try {
		output.open(output_filename, std::fstream::out | std::fstream::binary);
		if (!output) {
			throw std::system_error{ errno, std::generic_category() };
		}
		output << text;
	} catch (AssembleException const & e) {
		std::cerr << e.what() << std::endl;
		return 1;
	} catch (std::system_error const & e) {
		std::cerr << "Output: " << e.code() << " - " << e.what() << std::endl;
		return 1;
	} catch (std::exception const & e) {
		std::cerr << "Output: " << e.what() << std::endl;
		return 1;
	}

	output.close();

	return 0;
}

