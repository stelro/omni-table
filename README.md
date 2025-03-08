omni-table
===========
![Build status (main)](https://github.com/stelro/omni-table/actions/workflows/linux_ubuntu.yml/badge.svg)
![Build status (main)](https://github.com/stelro/omni-table/actions/workflows/macos-latest.yml/badge.svg)
![Build status (main)](https://github.com/stelro/omni-table/actions/workflows/windows_latest.yml/badge.svg)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)


Omni-table is a lightweight C++ library designed to effortlessly transform 
your raw data into visually appealing ASCII grid tables directly in the console. 
Perfect for command-line applications, it provides a clean and customizable 
way to display tabular information, making data more accessible and easier to read.


Simple examples
---------------

![alt text](https://github.com/stelro/omni-table/blob/main/banner/banner.png)

The following code demonstrates how to create a simple 5x3 grid table, populate it, and apply optional styling modifications.

```c++
// Define your table object
Table table;

// Set the alignment (optional)
table.set_alignment(Alignment::center);

// Set a fixed maximum column width (optional)
table.set_max_column_width(10);

// Enable the table border style (optional)
table.enable_border_style(format::style::red | format::style::faint);

// Enable vertical centering for all columns
table.enable_vertical_centering(true);

// Populate the table header
table[0][0] = "Make";
table[0][1] = "Model";
table[0][2] = "Hp";

// Apply styling to the entire header row
table[0].set_row_style(format::style::magenta | format::style::bold);

// Populate the table with car data
table[1][0] = "Toyota";
table[1][1] = "Camry";
table[1][2] = 203;

table[2][0] = "Honda";
table[2][1] = "Civic";
table[2][2] = 158;

// Apply styling to a specific cell (Model column in the Honda row)
table[2][1].set_cell_style(format::style::yellow | format::style::bold);

// Add a new row using an initializer list
table.add_row({"Audi", "A5", "320"});

// Alternatively, create a Row object and add it to the table
Row fifth_row = {"BMW", "M5", 480};
table.add_row(fifth_row);

// Print the table to the console
table.print();

```

Supported features
------

Please see the API documention, on how to use the omni-table class.

* Access rows and cells using the subscript operator, and add new rows dynamically.
* Print the fully formatted table directly to the console.
* Cell Alignment - set a default alignment for cell content (left, center, or right).
* Supports multi-line cells and text wrapping
* Border Styles - Choose from various border styles (none, full, header, footer) and combine them using bitwise operators.
* Maximum Column Width - Specify a fixed maximum width for columns; cells wider than this limit will wrap automatically.
* Custom Border Characters - Define your own characters for vertical borders, horizontal lines, and intersections.
* ANSI Color & Styling - Enable ANSI colors and modifiers for borders.
* Vertical Centering - Optionally enable vertical centering for cell content.

Planned features
-------

These are not in particular order

* Define custom log sinks (export output to a designated file rather than the console).
* Support the creation of statically allocated tables.
* Enable compile-time table definitions.
* Provide export functionality to output the table in CSV format.
* Enable Unicode support on Windows.
* Ensure thread safety.
* Implement robust exception and error handling.
* Support cell merging (spanning across columns or rows) to accommodate more complex table layouts.
* Provide sorting and filtering capabilities, allowing users to sort rows by specific columns and filter rows based on criteria.
* Support custom formatting for different data types (e.g., numeric and date formatting) so that data is automatically formatted based on its type.
* Add support for iterators and integration with STL algorithms where feasible.
* Single header

Build and Requirements
-------
Currently this proejct relies on C++ 20. So any compiler that support C++ 20 should do.

This project requires CMake 3.22+ and Ninja.

Build the project on linux by using the *build.sh* script.

```
./build.sh [options]

Build options:
--dev : Builds only the Debug target with Address Sanitizer enabled (development build).
--rel : Builds only the Release target.
--no-clean : Prevents cleaning of existing build artifacts before building.
--test : Runs the unit tests instead of building the project. Tests are expected to be found in the build/debug/tests directory.

Simple usage:

./build.sh 

```

See additional examples int he examples/ directory.

License
-------

MIT license (© 2025 Rostislav Stelmach)


