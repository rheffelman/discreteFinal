#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

int main(){
    string a = "8315";
    string b = "53469";
    unordered_set < char > intersection;
    for (int i = 0; i < a.size(); i++) {
        if (b.find(a[i]) != string::npos){
            intersection.insert(a[i]);
        }
    }
}