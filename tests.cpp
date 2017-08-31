#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include "solver.h"
#include "tests.h"



using namespace std;



bool check_the_roots(vector <double> coefs, vector <double> roots, double eps)
{
    int number = coefs.size();

    if ( (number < 2) or (number > 5) )
    {
        return false;
    }

    int shift = 5 - number;
    vector <double> all_coefs = {0, 0, 0, 0, 0};

    for (int i = shift; i < 5; ++i)
    {
        all_coefs[i] = coefs[i - shift];
    }

    bool res = true;
    double a, b, c, d, e;

    a = all_coefs[0];
    b = all_coefs[1];
    c = all_coefs[2];
    d = all_coefs[3];
    e = all_coefs[4];

    for (int i = 0; i < int(roots.size()); ++i)
    {
        double x = roots[i];
        double y = (((a*x + b)*x + c)*x + d)*x + e;

        res &= (fabs(y) < eps);
    }

    return res;
}

double seconds_for_N_solutions(int degree, int N)
{
    long long clocks = 0;
    Solver::Roots roots;

    fstream fout;
    fout.open("out.txt", ios_base::out);

    srand( time(NULL) );

    for (int i = 0; i < N; ++i)
    {
        double a, b, c, d, e;
        clock_t t_1, t_2;

        a = rand() - (RAND_MAX / 2);
        b = rand() - (RAND_MAX / 2);
        c = rand() - (RAND_MAX / 2);
        d = rand() - (RAND_MAX / 2);
        e = rand() - (RAND_MAX / 2);

        switch (degree)
        {
            case 1:
                t_1 = clock();
                roots = Solver::solve_linear(a, b);
                t_2 = clock();
            break;

            case 2:
                t_1 = clock();
                roots = Solver::solve_quadratic(a, b, c);
                t_2 = clock();
            break;

            case 3:
                t_1 = clock();
                roots = Solver::solve_cubic(a, b, c, d);
                t_2 = clock();
            break;

            case 4:
                t_1 = clock();
                roots = Solver::solve_quartic(a, b, c, d, e);
                t_2 = clock();
            break;

            default:
                t_1 = clock();
                roots = Solver::Roots {0, 0, 0, 0, 0};
                t_2 = clock();
            break;
        }

        clocks += t_2 - t_1;

        fout << roots.number;
    }

    fout.close();

    return (double(clocks) / CLOCKS_PER_SEC);
}

void eternal_solver()
{
    double a, b, c, d, e;

    while (true)
    {
        cin >> a >> b >> c >> d >> e;

        auto roots = Solver::solve_quartic(a, b, c, d, e).to_vector();

        int number = roots.size();

        if (number > 0)
        {
            cout << number << " root" << ((number > 1) ? ("s: ") : (": "));
        }
        else
        {
            cout << "No roots.";
        }

        for (int i = 0; i < number; ++i)
        {
            cout << roots[i] << ((i < (number - 1)) ? (", ") : ("."));
        }

        cout << endl;

        cout << ( check_the_roots({a, b, c, d, e}, roots) ? "True." : "False." );

        cout << endl << endl;
    }
}
