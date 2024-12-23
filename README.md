# An Algorithm for the Contiguous Art Gallery Problem

This repository contains an implementation of an algorithm for the Contiguous Art Gallery Problem as
described in the paper "The Contiguous Art Gallery Problem is Solvable in
Polynomial Time" submitted to the 2025 International Symposium on Computational Geometry (SoCG) by Magnus C. R. Merrild, 
Casper M. Rysgaard, Jens K. R. Schou, and Rolf Svenning.
Please cite the paper if you use the code.

For a simple input polygon, the algorithm finds the smallest partition of the boundary into polygonal chains, each 
chain visible to a guard in the polygon's interior.

## Dependencies and setup
The implementation uses the Computational Geometry Algorithms Library (CGAL) and the Boost Graph Library (BGL).
To install CGAL, follow the instructions on their website (https://doc.cgal.org/latest/Manual/general_intro.html).
Note the `Qt6` library is not required by default but is necessary for visualizations (the functions `CGAL::draw(A)`,
`drawArrangements`, and the include statement `#include <CGAL/draw_arrangement_2.h>`  are commented out in
`Helper.cpp` and `Algorithm1.cpp`).


On Windows, when using Vcpkg with CMake, the following CMake options might be needed:
`-DCMAKE_TOOLCHAIN_FILE=C:/Users/Bruger/vcpkg/scripts/buildsystems/vcpkg.cmake`
where `C:/Users/Bruger/vcpkg` should be replaced with the path to your vcpkg installation directory.



## Running the implementation
The main function takes a single argument, `n`, the number of vertices of the polygon.
By default, the implementation generates a random simple polygon.
The main function also includes commented code to generate two specific polygons.

Build the project using CMake and run the executable with the number of vertices as an argument.
For example, to run the implementation on a polygon with 10 vertices, run:
`./main 10`. By default, the results are written to the output.txt file.
To disable this, comment out the calls to `writeOutput` in the `Algorithms1.cpp` file.

Note that the number of greedy steps reported is the number of greedy steps before a repetition point is found, 
plus the number of greedy steps after the repetition to perform a single revolution around the polygon
and find an optimal solution.
For example, a solution with 2 guards and 7 greedy steps means that the algorithm found an
optimal endpoint (a repetition) after 5 greedy steps, and then performed 2 additional greedy steps to compute an
optimal solution.


## Degeneracies
We assume the input is in general position, i.e. no three points are collinear.
This simplifies the implementation, eg. we can assume that visibility polygons do not have 'needles'
(see https://doc.cgal.org/latest/Visibility_2/index.html#Chapter_2D_Visibility_Computation).
For inputs with collinear points, the computed feasible regions may be smaller than the actual feasible region,
leading to a greedy step that is shorter than it should be. The solution produced by the algorithm is still valid
but may use one more guard than is optimal.





