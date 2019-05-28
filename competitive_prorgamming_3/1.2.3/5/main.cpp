
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, int> iii;

struct date_tuple_t
{
    unsigned int year;
    unsigned int month;
    unsigned int date;
};

void initDate(date_tuple_t &dateTuple, unsigned int year, unsigned int month, unsigned int date)
{
    dateTuple.year = year;
    dateTuple.month = month;
    dateTuple.date = date;
}

bool comparatorByDate(date_tuple_t date1, date_tuple_t date2)
{
    return date1.month == date2.month && date1.date < date2.date;
}

bool comparatorByMonth(date_tuple_t date1, date_tuple_t date2)
{
    return date1.month < date2.month;
}

bool comparatorByAge(date_tuple_t date1, date_tuple_t date2)
{
    return date1.month == date2.month && date1.date == date2.date && date1.year >  date2.year;
}

void printDates(vector<date_tuple_t> dates)
{
    for (int i = 0; i < dates.size(); i++)
        printf("(%d,%d,%d)\n", dates[i].date, dates[i].month, dates[i].year);
    cout << endl;
}

vector<date_tuple_t> sortDates(date_tuple_t* dates, unsigned int n)
{
    vector<date_tuple_t> data(dates, dates + n);

    sort(data.begin(), data.end(), comparatorByMonth);
    sort(data.begin(), data.end(), comparatorByDate);
    sort(data.begin(), data.end(), comparatorByAge);
    return data;
}

void bookCode()
{
    iii A = make_pair(ii(5, 24), -1982);
    iii B = make_pair(ii(5, 22), -1980);
    iii C = make_pair(ii(11, 13), -1983);
    iii D = make_pair(ii(5, 22), -1981);
    vector<iii> birthdays;
    birthdays.push_back(A);
    birthdays.push_back(B);
    birthdays.push_back(C);
    birthdays.push_back(D);
    sort(birthdays.begin(), birthdays.end());
    for (int i = 0; i < birthdays.size(); i++)
        printf("(%d,%d,%d)\n", birthdays[i].first.first, birthdays[i].first.second, birthdays[i].second);
}

int main()
{
    unsigned int n = 10;
    unsigned int i = 0;
    date_tuple_t dates[n];
    date_tuple_t dateTuple;
    initDate(dateTuple, 2010, 8, 9);
    dates[i++] = dateTuple;
    initDate(dateTuple, 2010, 8, 3);
    dates[i++] = dateTuple;
    initDate(dateTuple, 2011, 8, 2);
    dates[i++] = dateTuple;


    initDate(dateTuple, 2010, 4, 4);
    dates[i++] = dateTuple;
    initDate(dateTuple, 2010, 4, 3);
    dates[i++] = dateTuple;
    initDate(dateTuple, 2011, 4, 2);
    dates[i++] = dateTuple;


    initDate(dateTuple, 2010, 9, 9);
    dates[i++] = dateTuple;
    initDate(dateTuple, 2010, 9, 2);
    dates[i++] = dateTuple;
    initDate(dateTuple, 2012, 9, 1);
    dates[i++] = dateTuple;
    initDate(dateTuple, 2011, 9, 1);
    dates[i++] = dateTuple;

    vector<date_tuple_t> sortedDates = sortDates(dates, n);

    printDates(sortedDates);

    bookCode();

    return 0;
}
