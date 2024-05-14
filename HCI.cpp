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
    vector<double> standardHierarchy {0.000004529,	0.000008347,	0.000056965,	0.001086659,	0.002284332,	0.002723625,	0.00653874,	0.047844165,	0.043049401,	0.442177652,	0.454225585};
    vector<double> noHierarchy {0.000004436, 0.000008401, 0.000065988,	0.001093295, 0.003156132, 0.002789670, 0.006602532,	0.050996123, 0.075134997, 0.540739594, 0.454266599};
    vector<double> rearrangedNoHierarchy {0.000004542, 0.000008275,	0.000057327,	0.001087418,	0.002283222,	0.002726397,	0.006534768,	0.047841617,	0.043052757,	0.442132879,	0.454270798};
    vector<double> gadboisFirstHierarchy {0.000025, 0.000027, 0.000152, 0.002960, 0.003620, 0.009657, 0.073860, 0.039068, 0.455481, 0.412192};
    vector<double> alternativeHierarchy {0.000004606,	0.000008354,	0.00005726,	0.001088428,	0.002283817,	0.002724699,	0.006533194,	0.071763359,	0.019133941,	0.513699582,	0.38270276};
    vector<double> gadboisSecondHierarchy {0.000025, 0.000027, 0.000152, 0.002960, 0.002960, 0.003620, 0.009657, 0.095565, 0.017363, 0.520404, 0.347268};
    vector<double> hypothesisTest {0.000004532,	0.00000843,	0.000057387,	0.001087093,	0.002726406,	0.002282098,	0.006537292,	0.047851567,	0.043057334,	0.442157286,	0.454230575};
    // cout<<consistency(noHierarchy)<<endl;
    // cout<<consistency(standardHierarchy)<<endl;
    // cout<<consistency(rearrangedNoHierarchy)<<endl;
    cout<<consistency(hypothesisTest)<<endl;
}