#include <iostream>
#include <random>

using namespace std;

int const SIMULATIONS = 10000; // number of simulations to run
enum EventType {ARR, DEP}; // defining event types arrival and departure

struct event {
    EventType type; // type of event
    float time; // time of event
    event* nextEvent; // points to next event
};

double systemClock; // used to keep track of clock
bool serverIdle; // indicates if server is idle or not
double arrivalRate; // average arrival time passed by command line
double serviceTime; // average service time passed by command line
int readyQueueCount; // events in ready queue
float t; // time for each event
event* eq_head;

void Init() {

    systemClock = 0;
    serverIdle = true;
    readyQueueCount = 0;
    eq_head = NULL;
    t = (1 / arrivalRate);

}

void schedule_event(EventType type, double time, event head) {

    event* e = new event;
    e->type = type;
    e->time = time;
    e->nextEvent = NULL;


}

void arr_handler(event* e) {

    if(serverIdle == true) {
        serverIdle = false;
    } else {
        readyQueueCount++;
    }
}

void dep_handler(event* e) {

    if(readyQueueCount == 0) {
        serverIdle = true;
    } else {
        readyQueueCount--;
    }
}

int main(int argc, char* argv[]) {

sscanf(argv[1],"%lf",&arrivalRate);
sscanf(argv[2],"%lf",&serviceTime);

    // initialize conditions

    Init();

    // create events list

    int arrivalEvent = 1; // used to keep track of arrival events
    int departureEvent = 1; // used to keep track of departure events

    while(!(arrivalEvent > SIMULATIONS) || !(departureEvent > SIMULATIONS)) {

        event* eventPtr; // to traverse list

        if(arrivalEvent <= SIMULATIONS) {
            event* e = new event;
            e->type = ARR;
            e->time = arrivalEvent * t;
            e->nextEvent = NULL;

            if(eq_head == NULL) {
                eq_head = e;
            } else {
                eventPtr = eq_head;

                while(eventPtr->nextEvent) {
                    eventPtr = eventPtr->nextEvent;
                }

                eventPtr->nextEvent = e;
            }

            arrivalEvent++;
        }

        if(departureEvent*t+serviceTime <= (arrivalEvent*t)
           || arrivalEvent >= SIMULATIONS) {
            event* e = new event;
            e->type = DEP;
            e->time = departureEvent*t + serviceTime;
            e->nextEvent = NULL;

            eventPtr = eq_head;

            while(eventPtr->nextEvent) {
                eventPtr = eventPtr->nextEvent;
            }

            eventPtr->nextEvent = e;

            departureEvent++;
        }
    }

    // run simulation

    event* eventPtr = eq_head;
    double duration;
    double old_clock;
    while(eventPtr != NULL) {

        event* e = eq_head;
        float temp_busy = 0;
        old_clock = systemClock; // used to calculate CPU utilization
        systemClock = e->time; // current time
        duration = systemClock - old_clock;

        if(!serverIdle) {
            temp_busy += duration;
        }

        switch(e->type) {
            case ARR:
                arr_handler(e);
                break;

            case DEP:
                dep_handler(e);
                break;
        }

        // delete e from event queue

        eventPtr = eq_head->nextEvent;
        delete eq_head;
        eq_head = eventPtr;

    }

    float total_time = systemClock;

    // report metrics

    double avgUtilization = arrivalRate* serviceTime;
    double avgInside = avgUtilization / (1-avgUtilization);
    double avgWaiting = avgInside - avgUtilization;
    double avgWaitingTime = avgWaiting / arrivalRate;
    double avgTurnaround = serviceTime + avgWaitingTime;

    double throughput;

    if(avgUtilization <= 1) {
        throughput = arrivalRate;
    } else {
        throughput = 1 / serviceTime;
    }

    cout << "Average turnaround time: " << avgTurnaround << endl;
    cout << "Total throughput: " << throughput << endl;
    cout << "Average CPU utilization: " << avgUtilization << endl;
    cout << "Average number of processes in the ready queue: "
         << avgWaiting<< endl;

    return 0;
}
