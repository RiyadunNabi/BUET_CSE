#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// A struct to represent a point in the plane
struct Point {
    int x, y;
};

// Utility function to calculate the distance between two points
double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute force method to find the closest pair of points in a small set of points
double bruteForce(vector<Point>& points, int left, int right) {
    double minDist = DBL_MAX; // Initialize with a very large number
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j < right; ++j) {
            minDist = min(minDist, distance(points[i], points[j]));
        }
    }
    return minDist;
}

// Function to find the closest pair of points in a strip (within the divide boundary)
double stripClosest(vector<Point>& strip, double d) {
    double minDist = d;
    for (int i = 0; i < strip.size(); ++i) {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            minDist = min(minDist, distance(strip[i], strip[j]));
        }
    }
    return minDist;
}

// Utility function to sort points by their x-coordinate
bool compareX(Point p1, Point p2) {
    return p1.x < p2.x;
}

// Utility function to sort points by their y-coordinate
bool compareY(Point p1, Point p2) {
    return p1.y < p2.y;
}

// Recursive function to find the closest pair of points
double closestUtil(vector<Point>& points, int left, int right, vector<Point>& temp) {
    if (right - left <= 3) {
        return bruteForce(points, left, right);  // Use brute force for small datasets
    }

    int mid = (left + right) / 2;
    Point midPoint = points[mid];

    // Recursively find the closest pair in the left and right halves
    double dl = closestUtil(points, left, mid, temp);
    double dr = closestUtil(points, mid + 1, right, temp);
    
    double d = min(dl, dr); // The minimum distance from both halves

    // Merge step: Create a strip to check the closest pair that may straddle the dividing line
    vector<Point> strip;
    for (int i = left; i <= right; ++i) {
        if (abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    // Sort the strip points by their y-coordinate
    sort(strip.begin(), strip.end(), compareY);

    // Return the minimum of the closest pair found in left, right, and the strip
    return min(d, stripClosest(strip, d));
}

// Main function to find the closest pair of points
double closestPair(vector<Point>& points) {
    // Sort points by x-coordinate
    sort(points.begin(), points.end(), compareX);

    // Temporary array to store points sorted by y-coordinate
    vector<Point> temp(points.size());
    
    return closestUtil(points, 0, points.size() - 1, temp);
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    cout << "The closest distance is " << closestPair(points) << endl;
    return 0;
}



/*
Function Closest_Pair(points):
    1. Sort points by x-coordinates.

    2. Call Closest_Pair_Recursive(points)

Function Closest_Pair_Recursive(points_sorted_x):
    1. If number of points ≤ 3:
        - Use brute-force method to find closest pair.
        - Return closest pair and their distance.

    2. Divide the points into two halves:
        - Find the middle index.
        - Divide points into left half and right half.

    3. Recursively find:
        - Closest pair in the left half.
        - Closest pair in the right half.

    4. Find the minimum distance `d` from both halves.

    5. Create a **strip region**:
        - Include points within distance `d` from the middle dividing line.
        - Sort these points by y-coordinates.

    6. Find closest pair in the strip (Only check next 7 points for each point).

    7. Return the closest pair among:
        - Left half closest pair
        - Right half closest pair
        - Closest pair in the strip

Function Brute_Force(points):
    1. Set `min_distance = ∞`
    2. Check all pairs of points and compute distance.
    3. Return the pair with the smallest distance.

Function Strip_Closest(strip, min_distance):
    1. Sort points in the strip by y-coordinate.
    2. For each point, check at most next 7 points.
    3. Return the closest pair found in the strip.


*/