#include <iostream>

#include "table.h"
#include "formatter.h"

using namespace gctable;

int main() {

	// tabluxe
	// omni-table


    std::cout << "\n\n\n";

    Table table;

    table.set_alignment(Alignment::center);
	table.set_max_column_width(10);
	table.enable_border_style(format::style::red | format::style::faint);
	table.enable_vertical_centering(true);

    // Header
    table[0][0] = "No";
    table[0][1] = "Make";
    table[0][2] = "Model";
    table[0][3] = "Year";
    table[0][4] = "Hp";
    table[0][5] = "Price";
    table[0][6] = "";
	
	// Apply custom style to the whole row
	table[0].set_row_style(format::style::green | format::style::bold);

   
    // Cars table
    table[1][0] = 1;
    table[1][1] = "Toyota";
    table[1][2] = "Camry";
    table[1][3] = 2018;
    table[1][4] = 203;
    table[1][5] = "$24,425";

    table[2][0] = 2;
    table[2][1] = "Honda";
    table[2][1].set_cell_style(format::style::yellow | format::style::bold);
    table[2][2] = "Civic";
    table[2][3] = 2020;
    table[2][4] = 158;
    table[2][5] = "$21,050";

    table[3][0] = 3;
    table[3][1] = "Ford";
    table[3][2] = "Mustang XXL The best";
    table[3][3] = 2019;
    table[3][4] = 310;
    table[3][5] = "$26,670";

    table[4][0] = 4;
    table[4][1] = "Chevrolet Camaro";
    table[4][2] = "Silverado orestis is the best";
    table[4][3] = 2021;
    table[4][3].set_cell_style(format::style::yellow | format::style::italic | format::style::faint);
    table[4][4] = 355;
    table[4][5] = "$36,195";

	table[4].set_row_style(format::style::magenta | format::style::faint);

    table[5][0] = 5;
    table[5][1] = "BMW";
    table[5][2] = "3 Series";
    table[5][3] = 2022;
    table[5][4] = 255;
    table[5][5] = "$41,450";
	
	table[6].set_row_style(format::style::cyan);
    table[6][0] = 6;
    table[6][1] = "Audi";
    table[6][2] = "A4";
    table[6][3] = 2017;
    table[6][4] = 190;
    table[6][5] = "$34,900";

    table[7][0] = 7;
    table[7][1] = "Mercedes";
    table[7][2] = "C-Class";
    table[7][3] = 2018;
    table[7][4] = 241;
    table[7][5] = "$41,400";

    table[8][0] = 8;
    table[8][1] = "Subaru";
    table[8][2] = "Outback";
    table[8][3] = 2020;
    table[8][4] = 182;
    table[8][5] = "$26,645";   

    table[9][0] = 9;
    table[9][1] = "Hyundai";
    table[9][2] = "Elantra";
    table[9][3] = 2021;
    table[9][4] = 147;
    table[9][5] = "$19,650";

    table[10][0] = "";

    table.print();

    std::cout << "\n\n\n";

    return 0;
}
