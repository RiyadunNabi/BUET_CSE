#include <iostream>
using namespace std;
#include <vector>

struct Result
{
    int maxSum;
    int start;
    int end;
    int length;
};

// Result baseCase(const vector<int> & scores, int left, int right )
// {
//     if(left==right)
//     {
//         return {scores[left],left,right,1};
//     }
// }

Result findCrossingStreak(const vector<int> &scores, int left, int mid,int right)
{
    int leftSum=INT16_MIN;
    int sum=0;
    int leftIdx=mid;
    for (int i = mid; i>=left; i--)
    {
        sum+=scores[i];
        if(sum>leftSum)
        {
            leftSum=sum;
            leftIdx=i;
        }
    }

    int rightSum=INT16_MIN;
    sum=0;
    int rightIdx=mid+1;
    for (int i = mid+1; i <= right; i++)
    {
        sum+=scores[i];
        if(sum>rightSum)
        {
            rightSum=sum;
            rightIdx=i;
        }
    }
    
    return {leftSum+rightSum, leftIdx,rightIdx, rightIdx-leftIdx+1};

}

Result findHottestStreak(const vector<int> &scores, int left, int right)
{
    if(left==right)
    {
        return {scores[left],left,right,1};
    }

    int mid=left+(right-left)/2;
    Result leftResult=findHottestStreak(scores, left, mid);
    Result rightResult=findHottestStreak(scores, mid+1, right );

    // return leftResult;
    Result crossResult = findCrossingStreak(scores, left, mid, right);

    Result bestResult=leftResult;

    if(bestResult.maxSum<rightResult.maxSum || (bestResult.maxSum== rightResult.maxSum && bestResult.length > rightResult.length))
    {
        bestResult=rightResult;
    }

    
    if(bestResult.maxSum<crossResult.maxSum || (bestResult.maxSum== crossResult.maxSum && bestResult.length > crossResult.length))
    {
        bestResult=crossResult;
    }

    return bestResult;
}

int main()
{
    vector<int> scores={6, 3, -7, 3, -2, 5, -1, 4, -3, 2};


    
    Result result = findHottestStreak(scores, 0, scores.size() - 1);

    cout << "Hottest streak: [";
    for (int i = result.start; i <= result.end; i++) {
        cout << scores[i];
        if (i != result.end) cout << ", ";
    }
    cout << "] with a sum of " << result.maxSum << endl;
    

    return 0;
}