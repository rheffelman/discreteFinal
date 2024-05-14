#include<iostream>
#include<vector>
using namespace std;

double consistency(vector<double>& data){
    double total = 0;
    for (int i = 0; i < data.size() - 1; i++){
        if (data[i] > data[i + 1]){
            total += data[i] - data[i + 1];
        }
    }
    return total;
}
//--
int main(){
    vector<double> data {0.000004436, 0.000008401, 0.000065988,	0.001093295, 0.003156132, 0.002789670, 0.006602532,	0.050996123, 0.075134997, 0.540739594, 0.454266599};
    cout<<consistency(data)<<endl;
}