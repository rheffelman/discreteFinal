#include<iostream>
#include<unordered_set>
#include<valarray>
#include<bitset>
using namespace std;

int main(){
    bitset<8> test;
    test[0] = 1;
    test[5] = test[5] + 1;
    for (int i = 0; i < 8; i++){
        if (test[i]) printf("true!\n");
        else printf("false!\n");
    }
}
// a0123456789jqk