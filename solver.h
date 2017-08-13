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
        };

        static Roots solve_linear   (double, double);
        static Roots solve_quadratic(double, double, double);
        static Roots solve_cubic    (double, double, double, double);
        static Roots solve_quartic  (double, double, double, double, double);
};



#endif // SOLVER_H
