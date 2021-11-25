#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(auto & a : arr) {
        cin >> a;
    }
    int Max = INT_MIN;
    int sum = 0;
    for(auto & a : arr) {
        sum += a;
        Max = max(sum, Max);
        if(sum < 0)
            sum = 0;
    }
    cout << Max << endl;
}