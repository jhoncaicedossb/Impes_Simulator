//+
Point(1) = {0, 0, 0};
Point(2) = {100, 0, 0};
Point(3) = {100, 100, 0};
Point(4) = {0, 100, 0};
//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 1};
//+
Line Loop(1) = {1, 2, 3, 4};
//+
Plane Surface(1) = {1};
//+
Physical Line("Inlet") = {2};
//+
Physical Line("Outlet") = {4};
//+
Physical Line("Impervious") = {3, 1};
//+
Physical Surface("Domain") = {1};
