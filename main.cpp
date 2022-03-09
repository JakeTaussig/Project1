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

    cout << "Enter digits permitted: \n";
    int i = 0;
    while(cin >> temp){
        s.push_back(temp);
        i++;
    }
    // test to see if vector is working
    // for(int j = 0; j < i; j++){ cout << s[j]; }

    Problem2 q;
    q.FindString(k, s);

    return 0;
}
