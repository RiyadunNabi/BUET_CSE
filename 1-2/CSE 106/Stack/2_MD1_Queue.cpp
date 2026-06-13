/*
Problem Statement: M/D/1 Queuing Model Simulation
The M/D/1 queue is a classic queuing model in which:

Arrivals follow a Poisson process with a rate of λ (lambda).
Service times are deterministic (constant), meaning each customer/service takes 1/μ (mu) units of time.
A single server processes requests in FIFO (First-In-First-Out) order.
Simulation Overview
This event-based simulation follows these steps:

Generate random arrivals using an exponential distribution with rate λ.
Process customers in a queue:
If a customer arrives before the current service ends, they are enqueued.
If no customers are waiting, the server remains idle.
The service time is fixed at 1/μ per customer.
Measure and record wait times for performance analysis using a histogram.

*/


#include <iostream>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate exponentially distributed random numbers (for inter-arrival times)
double expRandom(double lambda) {
    return -log(1.0 - (double)rand() / RAND_MAX) / lambda;
}

int main() {
    double lambda, mu;

    // Get user input for arrival rate (λ) and service rate (μ)
    cout << "Enter arrival rate (lambda): ";
    cin >> lambda;
    cout << "Enter service rate (mu): ";
    cin >> mu;

    queue<double> q;          // Queue to store arrival times
    int histogram[60] = {0};  // Histogram to store waiting time distribution

    srand(time(0));  // Seed for randomness

    double nextArrival = expRandom(lambda);  // First customer arrival
    double nextService = 1.0 / mu;           // Fixed service time

    while (true) {
        while (nextArrival < nextService) {  // Handle new arrivals
            q.push(nextArrival);
            nextArrival += expRandom(lambda);
        }

        if (!q.empty()) {
            double wait = nextService - q.front();
            q.pop();

            int waitTime = min(59, (int)wait); // Cap at 59 for histogram
            histogram[waitTime]++;

            nextService = nextArrival + (1.0 / mu);
        } else {
            nextService += (1.0 / mu);
        }
    }

    return 0;
}
