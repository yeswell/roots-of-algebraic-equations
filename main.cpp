#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include "solver.h"

using namespace std;

double seconds_for_N_solutions(int degree, int N)
{
    long long clocks = 0;

    double a, b, c, d, e;
    clock_t t_1, t_2;
    Solver::Roots roots;

    fstream fout;
    fout.open("out.txt", ios_base::out);

    srand( time(NULL) );

    for (int i = 0; i < N; ++i)
    {
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

    return double(clocks) / CLOCKS_PER_SEC;
}

void eternal_solver()
{
    double a, b, c, d, e;

    while (true)
    {
        cin >> a >> b >> c >> d >> e;

        auto roots = Solver::solve_quartic(a, b, c, d, e);

        int number = roots.number;
        double roots_arr[4] = { roots.x_1, roots.x_2, roots.x_3, roots.x_4 };

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
            cout << roots_arr[i] << ((i < (number - 1)) ? (", ") : ("."));
        }

        cout << endl << endl;
    }
}

int main()
{
    //eternal_solver();

    fstream fout("time.txt", ios_base::out);

    fout << "  1 2 3 4" << endl;

    for (int i = 0; i < 10; ++i)
    {
        fout << i+1 << " ";

        for (int j = 1; j < 5; ++j)
        {
            fout << seconds_for_N_solutions(j, 1e+7) << " ";
        }

        fout << endl;
    }

    fout.close();

    return 0;
}
