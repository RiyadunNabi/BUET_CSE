#include <iostream>
#include <climits>
using namespace std;

struct Answer
{
    int sum;
    int start;
    int end;
    int length;
};

Answer findCrossing(int scores[], int left, int mid, int right)
{
    int leftSum=INT_MIN;
    int sum=0;
    int leftIndex=mid;
    for (int i = mid; i >= left; i--)
    {
        sum+=scores[i];
        if(sum>leftSum)
        {
            leftSum=sum;
            leftIndex=i;
        }
    }

    int rightSum=INT_MIN;
    sum=0;
    int rightIndex=mid+1;
    for (int i = mid+1; i <= right; i++)
    {
        sum+=scores[i];
        if(sum>rightSum)
        {
            rightSum=sum;
            rightIndex=i;
        }
    }
    
    return {leftSum+rightSum, leftIndex,rightIndex, rightIndex-leftIndex+1};

}

Answer findStreak(int scores[], int left, int right)
{
    if(left>=right)
    {
        return {scores[left],left,right,1};
    }

    int mid=left+(right-left)/2;
    Answer leftAns=findStreak(scores,left,mid);
    Answer rightAns=findStreak(scores,mid+1,right);

    Answer crossAns=findCrossing(scores, left, mid, right);


    Answer bestAns=leftAns;

    if(bestAns.sum<rightAns.sum || (bestAns.sum== rightAns.sum && bestAns.length > rightAns.length))
    {
        bestAns=rightAns;
    }

    
    if(bestAns.sum<crossAns.sum || (bestAns.sum== crossAns.sum && bestAns.length > crossAns.length))
    {
        bestAns=crossAns;
    }

    return bestAns;
}

int main()
{
    int n;
    cin>>n;
    int scores[n];
    for (int i = 0; i < n; i++)
    {
        cin>>scores[i];
    }

    Answer ans=findStreak(scores,0,n-1);

    cout << "[";
    for (int i = ans.start; i <= ans.end; i++) {
        cout << scores[i];
        if (i != ans.end) cout << ", ";
    }
    cout << "] with a sum of " << ans.sum << endl;
    
}