#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <random>

using namespace std;

int main(){

    // *******PROBLEM 2a*******

    int const HOURS_IN_20_YEARS = 175200; // 20 yrs * 365 days * 24 hrs
    int const RESTORATION = 10; // restoration time is exactly 10 hrs
    int const MTBF = 500; // mean time before failure is 500 hrs
    int serverA[400]; // time between failures in server A
    int serverB[400]; // time between failures in server B
    int hour = 0; // tracks time of failures and restorations

    srand(time(NULL));

    // server A fail and restoration times

    cout << "Server A" << endl;
    cout << "---------------------------------------------------------------";
    cout << endl;

    int i=0;
    do{
        serverA[i] = -MTBF * log(1 -(double)rand() / (RAND_MAX));
        hour += serverA[i];
        cout << "Server A failed at hour: " << hour << ", ";
        hour = hour + RESTORATION;
        cout << "restored at hour: " << hour << endl;

        i++;

    }while(hour<HOURS_IN_20_YEARS);

    cout << "Actual MTBF for Server A: " <<  HOURS_IN_20_YEARS / i << " hours";
    cout << endl;

    // server B fail and restoration times

    cout << endl;
    cout << "Server B" << endl;
    cout << "---------------------------------------------------------------";
    cout << endl;

    hour = 0; // reset hour to 0
    int j=0;
    do{
        serverB[j] = -MTBF * log(1 -(double)rand() / (RAND_MAX));
        hour += serverB[j];
        cout << "Server B failed at hour: " << hour << ", ";
        hour = hour + RESTORATION;
        cout << "restored at hour: " << hour << endl;

        j++;

    }while(hour<HOURS_IN_20_YEARS);

    cout << "Actual MTBF for Server B: " <<  HOURS_IN_20_YEARS / j << " hours";
    cout << endl;


    // *******PROBLEM 2b*******

    int firstFailure=0;

    int n=0;
    do{
         if((serverA[n]-serverB[n]) <= 10 && (serverA[n]-serverB[n]) >= -10) {
            firstFailure= n;
        }
        n++;
    } while(firstFailure == 0);

    int bothFail = 0;

    for(int t=0; t<firstFailure; t++) {
        bothFail += serverA[t];
    }


    cout << endl << endl;
    bothFail = bothFail + (RESTORATION * firstFailure);

    cout << "Both servers fail at hour " << bothFail << endl;

    return 0;
}
