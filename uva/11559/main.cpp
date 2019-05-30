
#include <iostream>

/**
 * UVa 11559 - Event Planning
 *
 * Time complexity:
 *  Linear: O(n), where n is the number of hotels
 *
 * Space complexity:
 *  Linear: O(n), where n is the number of hotels
 * */

#define MAX_NUM_OF_PARTICIPANTS 200
#define MAX_PRICE_OF_BED_FOR_WEEKEND 10000
#define MAX_NUM_OF_AVAILABLE_BEDS_PER_WEEKEND 1000
#define MAX_POSSIBLE_COST MAX_NUM_OF_PARTICIPANTS * MAX_PRICE_OF_BED_FOR_WEEKEND

typedef unsigned short int short_t;

using namespace std;

double findMinCostOfEventPlanning(short_t numOfParticipants,
    double budget, short_t numOfHotels, short_t numOfWeeks,
    double* priceOfBedForWeekendByHotel, short_t* minValidNumOfBedsByHotel)
{
    double minHotelCost = MAX_POSSIBLE_COST + 1, currentCost;
    for (int hotelIndex = 0; hotelIndex < numOfHotels; hotelIndex++)
    {
        if (minValidNumOfBedsByHotel[hotelIndex] > MAX_NUM_OF_AVAILABLE_BEDS_PER_WEEKEND)
            continue;

        currentCost = numOfParticipants * priceOfBedForWeekendByHotel[hotelIndex];

        if (currentCost <= budget && currentCost < minHotelCost)
            minHotelCost = currentCost;
    }
    return minHotelCost;
}

void printFormattedCost(double cost)
{
    if (cost > MAX_POSSIBLE_COST)
        cout << "stay home" << endl;
    else
        cout << cost << endl;
}

int main()
{
    short_t numOfParticipants, numOfHotels, numOfWeeks, numOfBeds;
    double budget;
    while (cin >> numOfParticipants >> budget >> numOfHotels >> numOfWeeks)
    {
        double priceOfBedForWeekendByHotel[numOfHotels];

        short_t minValidNumOfBedsByHotel[numOfHotels];

        for (int hotelIndex = 0; hotelIndex < numOfHotels; hotelIndex++)
        {
            minValidNumOfBedsByHotel[hotelIndex] = MAX_NUM_OF_AVAILABLE_BEDS_PER_WEEKEND + 1;
            cin >> priceOfBedForWeekendByHotel[hotelIndex];
            for (int weekendIndex = 0; weekendIndex < numOfWeeks; weekendIndex++)
            {
                cin >> numOfBeds;
                if (numOfParticipants <= numOfBeds && numOfBeds < minValidNumOfBedsByHotel[hotelIndex])
                    minValidNumOfBedsByHotel[hotelIndex] = numOfBeds;
            }
        }
        double minCost = findMinCostOfEventPlanning(numOfParticipants,
            budget, numOfHotels, numOfWeeks, priceOfBedForWeekendByHotel,
            minValidNumOfBedsByHotel);
        printFormattedCost(minCost);
    }
    return 0;
}
