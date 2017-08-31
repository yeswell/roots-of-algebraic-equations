#include <vector>



using namespace std;



#ifndef SOLVER_H
#define SOLVER_H



class Solver
{
    public:

        struct Roots
        {
            int number;
            double x_1;
            double x_2;
            double x_3;
            double x_4;

            vector <double> to_vector();
        };

        static Roots solve_linear   (double a, double b);                               // Ax + B = 0
        static Roots solve_quadratic(double a, double b, double c);                     // Ax^2 + Bx + C = 0
        static Roots solve_cubic    (double a, double b, double c, double d);           // Ax^3 + Bx^2 + Cx + D = 0
        static Roots solve_quartic  (double a, double b, double c, double d, double e); // Ax^4 + Bx^3 + Cx^2 + Dx + E = 0
};



#endif // SOLVER_H
