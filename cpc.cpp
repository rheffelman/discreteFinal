#include<iostream>
#include<random>
#include<vector>
#include<string>
using namespace std;

int main(){

    srand(time(0));
    vector<string> v
    {
        "Geneology of Morals",
        "Ethics of Money/Capital",
        "The Nature of Happiness",
        "Free Will vs Determinism",
        "The Ethics of Artificial Intelligence",
        "The Meaning of Life",
        "The Nature of Reality",
        "The Value of Knowledge",
        "Ethics in Technology",
        "The Mind-Body Problem",
        "The Concept of Beauty",
        "The Role of Suffering"
    };
    
    printf("%s\n", v[rand() % (v.size())].c_str());

}


