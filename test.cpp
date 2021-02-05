#include <bits/stdc++.h>


using namespace std;


void change(const vector<int> &v) {

    for(int i = 0; i < 3; ++i) v[i] /= 3;

}


int main() {
    vector<int> v = {3,3, 3};
    change(v);

    for(int x : v) cout << x << endl;
}