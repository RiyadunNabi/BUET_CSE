#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum number of unit-length intervals covering all numbers in S
vector<pair<double, double>> findIntervals(vector<double>& S) {
    vector<pair<double, double>> intervals;
    
    // Sort the points (already sorted as per problem statement)
    sort(S.begin(), S.end());

    int n = S.size();
    int i = 0;
    
    while (i < n) {
        double left = S[i];           // Start of the interval
        double right = left + 1.0;     // Unit length interval [left, left + 1]
        intervals.push_back({left, right});

        // Move i to the first point that is outside the current interval
        while (i < n && S[i] <= right) {
            i++;
        }
    }
    
    return intervals;
}

int main() {
    vector<double> S = {0.5, 1.2, 2.0, 2.3, 3.1, 3.8, 4.0, 5.2, 6.0};  // Sample input
    vector<pair<double, double>> intervals = findIntervals(S);

    cout << "Minimum number of unit-length intervals: " << intervals.size() << endl;
    for (auto& interval : intervals) {
        cout << "[" << interval.first << ", " << interval.second << "]" << endl;
    }
    
    return 0;
}
