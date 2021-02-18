#include <bits/stdc++.h>


using namespace std;




int main() {
   
    for(int i = 0; i < 24; ++i) {
        for(int j = 0; j < 24; ++j) {
            printf("P(%d,%d,i) = P_%d_%d(i, 2);\n", i+1, j+1, i, j);
        }
    }
}
