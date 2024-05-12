#include <iostream>

#include "table.h"

using namespace cctable;

int main() {

    std::cout << "\n\n\n";

    Table table;

    // table.set_alignment(Alignment::left);
    // table.set_alignment(Alignment::right);
    table.set_alignment(Alignment::center);

    table[0][0] = Cell{"cell 1"};
    table[0][1] = Cell{"cell 2"};
    table[0][2] = Cell{"cell 3"};

    table[1][0] = Cell{"cell 4"};
    table[1][1] = Cell{"Long cell 55"};
    table[1][2] = Cell{"cell 6"};

    table[2][2] = Cell{"cell 6"};
    table[2][3] = 66;
    table[2][4] = 2.33;

    table[2][6] = "xx";

    table[3][0] = Cell{"xx"};
    table[3][4] = Cell{"Big Cell in [3][4] xx"};

    table[4][6] = Cell{"Medium Cell"};

    table.print();

    std::cout << "\n\n\n";

    return 0;
}
