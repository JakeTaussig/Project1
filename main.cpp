#include <iostream>
#include <queue>
#include "Problem2.h"
using namespace std;

int main() {
    int k;
    vector<int> s;
    int temp;
    
    cout << "Enter k: \n";
    cin >> k;

    // input allowed digits into a vector until a non-numeric value is entered
    cout << "Enter digits permitted: \n";
    int i = 0;
    while(cin >> temp){
        s.push_back(temp);
        i++;
    }
    
    // call FindString from .cpp file
    Problem2 q;
    q.FindString(k, s);

    return 0;
}
