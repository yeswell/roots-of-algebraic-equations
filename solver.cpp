#include <cmath>

#include "solver.h"



Solver::Roots Solver::solve_linear(double a, double b)
{
    if (a == 0)
    {
        return Roots { ((b == 0) ? (1) : (0)), 0, 0, 0, 0};
    };

    return Roots {1, -b/a, 0, 0, 0};
}

Solver::Roots Solver::solve_quadratic(double a, double b, double c)
{
    if (a == 0)
    {
        return solve_linear(b, c);
    };

    double D = b*b - 4*a*c;

    if ( D < 0 )
    {
        return Roots {0, 0, 0, 0, 0};
    }
    else
    {
        double x_1 = -0.5 * (b - sqrt(D)) / a;
        double x_2 = -0.5 * (b + sqrt(D)) / a;

        return Roots { ((D == 0) ? (1) : (2)), x_1, x_2, 0, 0};
    };
}

Solver::Roots Solver::solve_cubic(double a, double b, double c, double d)
{
    if (a == 0)
    {
        return solve_quadratic(b, c, d);
    };

    double one_third = 1 / 3.0;

    double a_1 = 1 / a;
    double b_3a_1 = b * a_1 * one_third;
    double b_3a_2 = b_3a_1 * b_3a_1;

    double c_a = c * a_1;
    double d_a = d * a_1;

    double p = c_a - (3 * b_3a_2);
    double q = d_a - (1 * b_3a_1) * (c_a - 2 * b_3a_2);

    double p_3 = p * one_third;
    double q_2 = q * 0.5;

    double D = pow(p_3, 3) + pow(q_2, 2);

    int number = 0;
    double roots[3] = {0};

    if ( D > 0 )
    {
        number = 1;
        roots[0] = cbrt(sqrt(D) - q_2) - cbrt(sqrt(D) + q_2) - b_3a_1;
    }
    else
    {
        double phi = 0;
        double z = 2 * sqrt(-p_3);

        if ( D == 0 )
        {
            number = (p == 0) ? (1) : (2);
        }
        else
        {
            number = 3;
        }

        if ( q != 0 )
        {
            phi = atan2(sqrt(-D), -q_2) + ((q > 0) ? (M_PI) : (0));
        }
        else
        {
            phi = M_PI_2;
        }

        for (int i = 0; i < 3; ++i)
        {
            roots[i] = z * cos(one_third * (phi + 2*M_PI*i)) - b_3a_1;
        }
    }

    return Roots {number, roots[0], roots[1], roots[2], 0};
}

Solver::Roots Solver::solve_quartic(double a, double b, double c, double d, double e)
{
    if (a == 0)
    {
        return solve_cubic(b, c, d, e);
    };

    double a_1 = 1 / a;
    double b_4a_1 = 0.25 * b * a_1;
    double b_4a_2 = b_4a_1 * b_4a_1;

    double c_a = c * a_1;
    double d_a = d * a_1;
    double e_a = e * a_1;

    double p = c_a - (6 * b_4a_2);
    double q = d_a - (2 * b_4a_1) * (c_a - 4 * b_4a_2);
    double r = e_a - (1 * b_4a_1) * (d_a - 1 * b_4a_1 * (c_a - 3 * b_4a_2));

    Roots roots_2_arr[2] = { Roots {0, 0, 0, 0, 0}, Roots {0, 0, 0, 0, 0} };

    if (q == 0)
    {
        Roots roots_2 = solve_quadratic(1, p, r);

        double roots_arr[2] = {roots_2.x_1, roots_2.x_2};

        for (int i = 0; i < roots_2.number; ++i)
        {
            roots_2_arr[i] = solve_quadratic(1, 0, -roots_arr[i]);
        }
    }
    else
    {
        double p_2 = 0.5 * p;
        double q_4 = 0.25 * q;
        double z = 0;

        Roots roots_3 = solve_cubic(1, p, pow(p_2, 2) - r, -2 * pow(q_4, 2));

        switch ( roots_3.number )
        {
            case 0:
                z = -1;
            break;

            case 1:
                z = roots_3.x_1;
            break;

            case 2:
                z = fmax(roots_3.x_1, roots_3.x_2);
            break;

            case 3:
                z = fmax(roots_3.x_1, fmax(roots_3.x_2, roots_3.x_3));
            break;
        }

        if ( z < 0 )
        {
            return Roots {0, 0, 0, 0, 0};
        };

        double sqrt_2z = sqrt(2 * z);
        double q_z = 2 * q_4 / sqrt_2z;

        roots_2_arr[0] = solve_quadratic(1, - sqrt_2z, z + p_2 + q_z);
        roots_2_arr[1] = solve_quadratic(1, + sqrt_2z, z + p_2 - q_z);
    }

    int number = 0;
    double roots[4] = {0};

    for (int i = 0; i < 2; ++i)
    {
        switch ( roots_2_arr[i].number )
        {
            case 0:
                // Nothing;
            break;

            case 1:
                roots[number++] = roots_2_arr[i].x_1 - b_4a_1;
            break;

            case 2:
                roots[number++] = roots_2_arr[i].x_1 - b_4a_1;
                roots[number++] = roots_2_arr[i].x_2 - b_4a_1;
            break;
        }
    }

    return Roots {number, roots[0], roots[1], roots[2], roots[3]};
}

vector <double> Solver::Roots::to_vector()
{
    vector <double> roots = {x_1, x_2, x_3, x_4};

    for (int i = number; i < 4; ++i)
    {
        roots.pop_back();
    }

    return roots;
}
