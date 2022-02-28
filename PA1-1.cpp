#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <random>

using namespace std;

int main(){

    // *******PROBLEM 1*******

    const int PROCESSES = 1000; // number of processes
    const double AVG_ARRIVAL_RATE = 2.0;  // arrival rate of 2/second
    const double AVG_SERVICE_TIME = 1.0; // average service time of 1 second
    double random_number[PROCESSES]; // array for random numbers
    double time_between[PROCESSES]; // array to hold times between arrivals
    double serviceTime[PROCESSES]; // array for service times
    double totalArrivalTime = 0; // tracks overall arrival time
    double totalServiceTime = 0; // tracks overall service time
    double averageServiceTime = 1; // average service time of 1 second

    srand(time(NULL));

    for(int i=0; i<PROCESSES; i++) {

        // generate random numbers to calculate time between process arrivals
        random_number[i] = ((double)rand() / (RAND_MAX));
        time_between[i] = -(1.0/AVG_ARRIVAL_RATE) * log(random_number[i]);

        cout << "ID: " << i+1 << " ";

        // keep track of total arrival time for calculations later
        totalArrivalTime = totalArrivalTime + time_between[i];
        cout << "Arrival Time: " << totalArrivalTime;

        // calculate random service time for each process
        serviceTime[i] = -AVG_SERVICE_TIME * log(1 -(double)rand() / (RAND_MAX));

        cout << " Requested Service Time: " << serviceTime[i] << endl;

        // keep track of the total service time for calculations later
        totalServiceTime = totalServiceTime + serviceTime[i];
    }

    cout << endl << endl;

    // calculate actual average arrival and service times
    cout << "Actual average arrival rate: " << totalArrivalTime/PROCESSES << endl;
    cout << "Actual average service time: " << totalServiceTime/PROCESSES << endl;

    return 0;
}
