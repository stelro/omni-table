#include <iostream>

#include "table.h"
#include "formatter.h"

using namespace omni;

int main() {

	std::cout << "\n\n\n";
	
	// Define your table here
    Table table;
	
	// Set Alignment (optional) 
    table.set_alignment(Alignment::left);
	// Set a fixed maximum width for columns. (optional) 
	table.set_max_column_width(16);
	// All columns will be centered
	//table.enable_vertical_centering(true);

	table.set_border_style(omni::BorderStyle::none);
	
	// Header
	table.add_row({"Brand", "Model", "Price"});
	table[0].set_row_style(format::style::bold | format::style::magenta);

	table.add_row({"Gibson", "Les Paul", 2000});
	table.add_row({"Fender", "Stratocaster", 1500});
	table.add_row({"Ibanez", "RG", 1200});
	table.add_row({"PRS", "Custom 24", 2500});
	table.add_row({"Epiphone", "Les Paul Standard", 800});
	table.add_row({"Yamaha", "Pacifica", 500});


	// Print your table to the console
    table.print();

	std::cout << "\n\n\n";

    return 0;
}
