#include <iostream>

#include "table.h"
#include "formatter.h"

using namespace omni;

int main() {
	
	// Define your table here
    Table table;
	
	// Set Alignment (optional) 
    table.set_alignment(Alignment::center);
	// Set a fixed maximum width for columns. (optional) 
	table.set_max_column_width(10);
	// Enable tables border style (optional)
	table.enable_border_style(format::style::red | format::style::faint);
	// All columns will be centered
	table.enable_vertical_centering(true);

	// Populate your table
    table[0][0] = "Make";
    table[0][1] = "Model";
    table[0][2] = "Hp";

	// Modify the styling for the whole row
	table[0].set_row_style(format::style::magenta | format::style::bold);

    // Cars table
    table[1][0] = "Toyota";
    table[1][1] = "Camry";
    table[1][2] = 203;

    table[2][0] = "Honda";
    table[2][1] = "Civic";
    table[2][2] = 158;
	// Modify the styling for that particular cell
	table[2][1].set_cell_style(format::style::yellow | format::style::bold);

	// Alternative way to array subscript operator for adding a row with columns 
	table.add_row({"Audi", "A5", "320"});

	Row fifth_row = {"BMW", "M5", 480};
	table.add_row(fifth_row);

	// Print your table to the console
    table.print();

    return 0;
}
