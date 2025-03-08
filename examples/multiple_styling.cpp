#include <iostream>

#include "table.h"
#include "formatter.h"

using namespace omni;

int main() {

	std::cout << "\n\n\n";
	
	// Define your table here
    Table table;
	
	// Set Alignment (optional) 
    table.set_alignment(Alignment::center);
	// Set a fixed maximum width for columns. (optional) 
	table.set_max_column_width(7);
	// Enable tables border style (optional)
	table.enable_border_style(format::style::faint);
	// All columns will be centered
	table.enable_vertical_centering(true);

	// Populate your table
	table[0][0] = "Make";
	table[0][1] = "Model";
	table[0][2] = "Price";
	table[0][3] = "Hp";
	table[0][4] = "Year";
	
	// Set the style for the whole first row
	table[0].set_row_style(format::style::bold | format::style::green);

	// Cars table
	table[1][0] = "Toyota";
	table[1][1] = "Camry";
	table[1][2] = "$24,500";
	table[1][3] = 203;
	table[1][4] = 2020;

	table[2][0] = "Honda";
	table[2][1] = "Civic";
	table[2][2] = "$21,000";
	table[2][3] = 158;
	table[2][4] = 2018;

	table[3][0] = "Ford";
	table[3][1] = "Mustang";
	table[3][2] = "$56,000";
	table[3][3] = 310;
	table[3][4] = 2021;

	// Set a style for individual cell
	table[3][2].set_cell_style(format::style::italic | format::style::blue);

	table[4][0] = "BMW";
	table[4][1] = "3 Series M3 competition";
	table[4][2] = "$41,000";
	table[4][3] = 698;
	table[4][4] = 2022;

	table[5][0] = "Audi";
	table[5][1] = "A4";
	table[5][2] = "$39,000";
	table[5][3] = 248;
	table[5][4] = 2019;

	// Print your table to the console
    table.print();

	std::cout << "\n\n\n";

    return 0;
}
