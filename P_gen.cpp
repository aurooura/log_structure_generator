#include <bits/stdc++.h>


using namespace std;


int main() {
    string func = "SelectMagFusion";
    string model = "SM";
    int sm = 29;
    int start = 7;
    int md = 0;
    for(int i = 0; i < 24; ++i) {
        for(int j = 0; j < 24; ++j) {
            if(md == 0 || md%15 == 0) {
                if(md) cout << "END\n";
                cout << model << "_" << sm << " SM" << sm << endl;
                cout << func << start++ << endl;
                sm++;
            }
            printf("float P[%d][%d]\n", i, j);
            md++;
        }
    }
    cout << "END\n";
}