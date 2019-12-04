//+
Point(1) = {22.696, 17.807, 0, 1.0};
//+
Point(2) = {11.126, 26.368, 0, 1.0};
//+
Point(3) = {9.545, 37.214, 0, 1.0};
//+
Point(4) = {8.968, 52.784, 0, 1.0};
//+
Point(5) = {9.3, 57.852, 0, 1.0};
//+
Point(6) = {11.618, 63.14, 0, 1.0};
//+
Point(7) = {14.98, 65.9, 0, 1.0};
//+
Point(8) = {18.193, 67.774, 0, 1.0};
//+
Point(9) = {19.816, 70.913, 0, 1.0};
//+
Point(10) = {23.653, 75.118, 0, 1.0};
//+
Point(11) = {29.79, 77.122, 0, 1.0};
//+
Point(12) = {35.565, 77.01, 0, 1.0};
//+
Point(13) = {41.471, 78.635, 0, 1.0};
//+
Point(14) = {46.687, 82.36, 0, 1.0};
//+
Point(15) = {54.401, 87.21, 0, 1.0};
//+
Point(16) = {60.022, 87.237, 0, 1.0};
//+
Point(17) = {66.379, 82.374, 0, 1.0};
//+
Point(18) = {70.917, 81.015, 0, 1.0};
//+
Point(19) = {76.72, 79.384, 0, 1.0};
//+
Point(20) = {81.524, 75.85, 0, 1.0};
//+
Point(21) = {84.47, 69.326, 0, 1.0};
//+
Point(22) = {85.399, 64.976, 0, 1.0};
//+
Point(23) = {84.233, 58.724, 0, 1.0};
//+
Point(24) = {80.971, 54.374, 0, 1.0};
//+
Point(25) = {79.883, 47.306, 0, 1.0};
//+
Point(26) = {83.417, 44.316, 0, 1.0};
//+
Point(27) = {85.864, 36.704, 0, 1.0};
//+
Point(28) = {86.64, 31.267, 0, 1.0};
//+
Point(29) = {85.669, 21.209, 0, 1.0};
//+
Point(30) = {81.863, 13.054, 0, 1.0};
//+
Point(31) = {74.021, 7.534, 0, 1.0};
//+
Point(32) = {62.237, 4.882, 0, 1.0};
//+
Point(33) = {51.891, 5.394, 0, 1.0};
//+
Point(34) = {44.475, 7.006, 0, 1.0};
//+
Point(35) = {35.446, 9.263, 0, 1.0};
//+
Point(36) = {28.674, 12.81, 0, 1.0};
//+
Point(37) = {15.116, 21.537, 0, 1.0};
//+
Line(1) = {3, 4};
//+
Line(2) = {5, 4};
//+
Line(3) = {5, 6};
//+
Line(4) = {6, 7};
//+
Line(5) = {7, 8};
//+
Line(6) = {8, 9};
//+
Line(7) = {9, 10};
//+
Line(8) = {10, 11};
//+
Line(9) = {11, 12};
//+
Line(10) = {12, 13};
//+
Line(11) = {13, 14};
//+
Line(12) = {14, 15};
//+
Line(13) = {15, 16};
//+
Line(14) = {16, 17};
//+
Line(15) = {17, 18};
//+
Line(16) = {18, 19};
//+
Line(17) = {19, 20};
//+
Line(18) = {20, 21};
//+
Line(19) = {21, 22};
//+
Line(20) = {22, 23};
//+
Line(21) = {23, 24};
//+
Line(22) = {24, 25};
//+
Line(23) = {25, 26};
//+
Line(24) = {26, 27};
//+
Line(25) = {27, 28};
//+
Line(26) = {28, 29};
//+
Line(27) = {29, 30};
//+
Line(28) = {30, 31};
//+
Line(29) = {31, 32};
//+
Line(30) = {32, 33};
//+
Line(31) = {33, 34};
//+
Line(32) = {34, 35};
//+
Line(33) = {35, 36};
//+
Line(34) = {36, 1};
//+
Line(35) = {1, 37};
//+
Line(36) = {37, 2};
//+
Line(37) = {2, 3};
//+
Curve Loop(1) = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 1, -2};
//+
Plane Surface(1) = {1};
//+
Physical Curve("Inlet") = {37, 36};
//+
Physical Curve("Outlet") = {13, 14, 15};
//+
Physical Curve("Impervious") = {35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 13, 12, 11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
