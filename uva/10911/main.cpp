
#include <cmath>
#include <iostream>

#define MAX_ANSWER 1500 * 16
#define MAX_NUM_OF_STUDENTS 20

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

double find_minimum_distance_sum_recursivelly(double distances[MAX_NUM_OF_STUDENTS][MAX_NUM_OF_STUDENTS],
    unsigned int n, bool* visited_points)
{
    double answer = MAX_ANSWER;
    unsigned short int p1, p2;
    for (p1 = 0; p1 < n && visited_points[p1]; p1++)
        ;

    for (p2 = p1 + 1; p2 < n; p2++)
    {
        if (visited_points[p2])
            continue;

        visited_points[p1] = true;
        visited_points[p2] = true;

        double points_distance = distances[p1][p2];

        double current_answer = points_distance + find_minimum_distance_sum_recursivelly(distances, n, visited_points);
        answer = min(answer, current_answer);

        visited_points[p1] = false;
        visited_points[p2] = false;
    }
    return answer == MAX_ANSWER ? 0 : answer;
}

double find_minimum_distance_sum(int* x, int* y, unsigned int n)
{
    bool visited_points[n];
    for (int i = 0; i < n; i++)
        visited_points[i] = false;

    double distances[MAX_NUM_OF_STUDENTS][MAX_NUM_OF_STUDENTS];
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            distances[i][j] = find_distance(x, y, i, j);

    return find_minimum_distance_sum_recursivelly(distances, n, visited_points);
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
