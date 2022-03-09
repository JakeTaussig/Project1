// Created By: Jake Taussig
// To complile: main.cpp, and then ./a.out

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <string>
using namespace std;

vector<vector<string>> createDFA();
void createDFARows(vector<vector<string>> &dfa, int row);
bool isValid(string s);
void printVecRow(vector<vector<string>> dfa, int row);
void printIntRow(vector<vector<int>> dfa, int row);
int convertStringToNum(string s);
vector<vector<int>> convertToNum(vector<vector<string>> dfa);
int delta(vector<vector<string>> dfa, int state, char next);
int count(vector<vector<int>> dfa, vector<vector<string>> strDfa, int n);
vector<int> convertToCurrent(vector<vector<int>> dfa);

int main()
{
    int n;
    cout << "Enter n:" << endl;
    cin >> n;
    vector<vector<string>> temp = createDFA();
    // dfa has state 0 - 1365 with 0 being start state, aka nullstr and 1365 being the error state
    vector<vector<int>> dfa = convertToNum(temp);
    int c = 0;
    c = count(dfa, temp, n);
    cout << "The number of strings of length " << n << "accepted by the DFA is " << c << endl;
}

// Counts the number of strings of length n accepted by a DFA
// The way I did this needs both the int and string versions of the dfa to be passed.
int count(vector<vector<int>> dfa, vector<vector<string>> strDfa,  int n) {
    int temp = 0;
    vector<int> current = convertToCurrent(dfa);
    vector<int> next(current.size(), 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < current.size(); j++) {
            temp = 0;
            for(int k = 0; k < 4; k++) {
                if(k == 0) {
                    temp = temp + current.at(delta(strDfa, j, 'a'));
                }
                else if(k == 1) {
                    temp = temp + current.at(delta(strDfa, j, 'b'));
                }
                else if(k == 2) {
                    temp = temp + current.at(delta(strDfa, j, 'c'));
                }
                else if(k == 3) {
                    temp = temp + current.at(delta(strDfa, j, 'd'));
                }
            }
            next[j] = temp;
    
        }
        for(int s = 0; s < current.size(); s++) {
            current[s] = next[s];
        }
        for(int t = 0; t < next.size(); t++) {
            next[t] = 0;
        }
    }
    return current.at(0);
}

vector<vector<string>> createDFA()
{
    // a = 1, b = 2, c = 3, d = 4
    vector<string> states = {"a", "b", "c", "d"};
    vector<vector<string>> dfa;
    dfa.push_back({""});
    dfa.push_back(states);
    // Making dfa entries of size 2:
    int row = 1;
    // Creating rows of size 2
    createDFARows(dfa, row);
    int size = dfa.size();
    // Creating rows of size 3
    for (int i = 2; i < size; i++)
    {
        row = i;
        createDFARows(dfa, row);
    }
    size = dfa.size();
    // Creating rows of size 4
    for (int i = 6; i < size; i++)
    {
        row = i;
        createDFARows(dfa, row);
    }
    size = dfa.size();
    // Creating rows of size 5
    for (int i = 22; i < size; i++)
    {
        row = i;
        createDFARows(dfa, row);
    }
    dfa.push_back({"e"});
    return dfa;
}

void createDFARows(vector<vector<string>> &dfa, int row)
{
    vector<string> temp;
    int size = dfa[row].at(0).size();
    for (int i = 0; i < 4; i++)
    {
        string s = dfa[row].at(i);
        temp.push_back(s + "a");
        temp.push_back(s + "b");
        temp.push_back(s + "c");
        temp.push_back(s + "d");
        dfa.push_back(temp);
        temp.clear();
    }
}


bool isValid(string s)
{
    if (s.length() < 6)
        return true;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    for (int i = 0; i < 6; i++)
    {
        char ch = s.at(i);
        if (ch == 'a')
            a += 1;
        else if (ch == 'b')
            b += 1;
        else if (ch == 'c')
            c += 1;
        else if(ch == 'd')
            d += 1;
    }
    if (a == 0 || b == 0 || c == 0 || d == 0)
        return false;
    else
        return true;
}

vector<vector<int>> convertToNum(vector<vector<string>> dfa)
{
    
    vector<vector<int>> newDFA = {{0}, {1, 2, 3, 4}};
    int counter = 0;
    int num = 0;
    vector<int> newRow;
    vector<string> dfaRow;
    for (int i = 2; i < dfa.size() - 1; i++)
    {
        dfaRow = dfa.at(i);
        for (int j = 0; j < 4; j++)
        {
            string s = dfaRow.at(j);
            counter = 0;
            counter = convertStringToNum(s);
            newRow.push_back(counter);
        }

        newDFA.push_back(newRow);
        newRow.clear();
        dfaRow.clear();
    }
    newDFA.push_back({1365});
    return newDFA;
}
    
// Converts DFA to all 1s for current, since they are all accepting states
vector<int> convertToCurrent(vector<vector<int>> dfa) {
     vector<int> newDFA = {1, 1, 1, 1, 1};
        vector<string> dfaRow;
        for (int i = 2; i < dfa.size() - 1; i++)
        {
            for(int j = 0; j < 4; j++) {
                newDFA.push_back(1);
            }
        }
        newDFA.push_back(0);
        return newDFA;
}

int convertStringToNum(string s)
{
    int counter = 0;
    int num = 0;
    char c = 'e';
    for (int k = 0; k < s.length(); k++)
    {
        c = s.at(k);
        if (c == 'a')
            num = 1;
        else if (c == 'b')
            num = 2;
        else if (c == 'c')
            num = 3;
        else if (c == 'd')
            num = 4;
        counter += num * pow(4, k + (s.length() - 1) - (2 * k));
    }
    return counter;
}

int delta(vector<vector<string>> dfa, int state, char next)
{
    string strState = "";
    if (state == 1365)
        return 1365;
    if(state > 0) {
        strState = dfa.at(((state -1) / 4) + 1).at((state - 1) % 4);
    }
    string s = strState + next;
    if (isValid(s))
    {
        if (s.length() > 5)
        {
            s = s.erase(0, 1);
            int newState = convertStringToNum(s);
            return newState;
        }
        else
        {
            return convertStringToNum(s);
        }
    }
    return 1365;
}

void printVecRow(vector<vector<string>> dfa, int row)
{
    cout << dfa.at(row).at(0) << endl
         << dfa.at(row).at(1) << endl
         << dfa.at(row).at(2) << endl
         << dfa.at(row).at(3) << endl;
}

void printIntRow(vector<vector<int>> dfa, int row)
{
    cout << dfa.at(row)[0] << endl
         << dfa.at(row).at(1) << endl
         << dfa.at(row).at(2) << endl
         << dfa.at(row).at(3) << endl;
}
