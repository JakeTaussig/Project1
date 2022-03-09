//
// Created by nt101 on 2/25/2022.
//

#include "Problem2.h"

void Problem2::FindString(int k, vector<int> s) {
    int m = s.size();

    queue<int> Q; // initialize queue

    // initialize the rest of the variables
    bool found = false;
    int PARENT[k];
    int LABEL[k];
    bool VISITED[k];
    int FINAL[k];

    // set initial values
    for(int j = 0; j < k; j++){
        VISITED[j] = false;
        PARENT[j] = -1;
        LABEL[j] = 0;
        FINAL[j] = -1;
    }
    FINAL[0] = 0; // accepting state

    // fill in values for inputs
    int x = 0;
    int next;
    for (x = 0; x < m; x++) {
        next = Delta(0, s[x]) % k; // transition function
        VISITED[next] = true;
        PARENT[next] = 0;
        LABEL[next] = s[x];
        Q.push(next);
    }

    int current = 0;
    while(!Q.empty() && !found){
        current = Q.front(); // hold front of queue
        Q.pop(); // delete from queue
        for(int t = 0; t < m; t++){
            next = Delta(current, s[t]) % k; // transition function
            if (FINAL[next] == 0) { // if accepting state is reached
                LABEL[next] = s[t];
                PARENT[next] = current;
                found = true;
                break;
            }
            else {
                if (VISITED[next]== 0) {
                    PARENT[next] = current;
                    VISITED[next] = true;
                    LABEL[next] = s[t];
                    Q.push(next);
                }
            }
        }
    }
    if (!found) { // if we reached the end of the queue and did not reach accepting state
        cout << "No solution" << endl;
    } else { // print solution by going through each label that matches next parent
        vector<int> solution;
        int x = 0;
        solution.push_back(LABEL[x]);
        x = PARENT[x];
        while (x != 0){
            solution.push_back(LABEL[x]);
            x = PARENT[x];
        }
        int y;
        for(y = solution.size() - 1; y >= 0; y--) {
            cout << solution[y];
        }
        cout << endl;
    }
    return;
}

int Problem2::Delta(int p, int a){ // compute transition function
    return (p * 10) + a;
}