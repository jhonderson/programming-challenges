
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define MAX_ANSWER 1500 * 16

/**
 * UVA 10911: Forming quiz teams
 *
 * Time complexity:
 *  C(16,2) * C(14,2) * ... * C(2,2)
 *
 * Space complexity:
 *  N
 * */

using namespace std;

double find_distance(int* x, int* y, unsigned int i, unsigned int j)
{
    return sqrt((x[j]-x[i]) * (x[j]-x[i]) + (y[j]-y[i]) * (y[j]-y[i]));
}

double find_minimum_distance_sum_recursivelly(double distances[20][20], unsigned int n, bool* visited_points, unsigned int accum_distance)
{
    double answer = MAX_ANSWER;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n && !visited_points[i]; j++)
        {
            if (visited_points[j])
                continue;
            visited_points[i] = true;
            visited_points[j] = true;

            double points_distance = distances[i][j];
            if (accum_distance + points_distance  < answer) {
                double current_answer = points_distance + find_minimum_distance_sum_recursivelly(distances, n, visited_points, accum_distance + points_distance);
                answer = min(answer, current_answer);
            }

            visited_points[i] = false;
            visited_points[j] = false;
        }
    }
    return answer == MAX_ANSWER ? 0 : answer;
}

double find_minimum_distance_sum(int* x, int* y, unsigned int n)
{
    bool visited_points[n];
    for (int i = 0; i < n; i++)
        visited_points[i] = false;

    double distances[20][20];
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            distances[i][j] = find_distance(x, y, i, j);

    return find_minimum_distance_sum_recursivelly(distances, n, visited_points, 0);
}

int main()
{
    unsigned int caseNumber = 0;
    unsigned int n;

    string name;

    while(cin >> n)
    {
        if (n <= 0)
            break;

        caseNumber++;
        n *= 2;

        unsigned i = 0;
        int x[n], y[n];

        while(i < n)
        {
            cin >> name >> x[i] >> y[i];
            i++;
        }

        double answer = find_minimum_distance_sum(x, y, n);

        printf("Case %d: %.2lf\n", caseNumber, answer);
    }
    return 0;
}
