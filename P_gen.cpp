#include <bits/stdc++.h>


using namespace std;


int main(int argc, char *argv[]) {
    string func = argv[1];
    string model = argv[2];
    int sm = 0;
    int start = 0;
    int md = 0;
    for(int i = 0; i < 24; ++i) {
        for(int j = 0; j < 24; ++j) {
            if(md == 0 || md%15 == 0) {
                if(md) cout << "END\n";
                cout << model << "_" << sm << " " << model << sm << endl;
                cout << func << start++ << endl;
                sm++;
            }
            printf("float P[%d][%d]\n", i, j);
            md++;
        }
    }
    cout << "END\n";
}