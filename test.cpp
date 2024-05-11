#include<iostream>
#include<vector>
#include<valarray>
#include<unordered_set>
#include<bitset>
#include<string>
#include<regex>
#include<algorithm>
#include<random>
#include<ctime>
#include<cassert>
using namespace std;

string stripSuits(string& hand);
string stripVals(string& hand);

bool fiveOfAKind(string& hand){
    string s = stripSuits(hand);
    unordered_set<char> ht;
    for (int i = 0; i < s.size(); i++) ht.insert(s[i]);
    return (ht.size() == 2 and ht.count('w'));
}
bool fullHouse(string& hand){

    string s = stripSuits(hand);
    valarray<unsigned int> v;
    v.resize(13, 0);
    unordered_set<char> ht;
    for (int i = 0; i < s.size(); i++) ht.insert(s[i]);

    if (ht.count('w')){
        for (int i = 0; i < s.size(); i++){
            if (s[i] == 'a') v[0]++;
            else if (s[i] == 'j') v[11]++;
            else if (s[i] == 'q') v[12]++;
            else if (s[i] == 'k') v[13]++;
            else if (s[i] == 'w') continue;
            else v[((int)s[i])-47]++;
        }
        if (v.max() == 3) return true;
        for (int i = 0; i < v.size(); i++){
            if (v[i] == 2){
                v[i]--;
                if (v.max() == 2) return true;
                else return false;
            }
        }
        return false;
    }

    for (int i = 0; i < s.size(); i++){
        if (s[i] == 'a') v[0]++;
        else if (s[i] == 'j') v[11]++;
        else if (s[i] == 'q') v[12]++;
        else if (s[i] == 'k') v[13]++;
        else if (s[i] == 'w') continue;
        else v[((int)s[i])-47]++;
    }

    for (int i = 0; i < v.size(); i++){
        if (v[i] == 3){
            for (int ii = 0; ii < v.size(); ii++){
                if (v[ii] == 2) return true;
            }
        }
    }
    return false;
}
int main(){

    // string s = "as1s0d3cww";
    // cout<<stripSuits(s)<<endl;
    // if (testFun(s)) cout<<"true!\n";

    srand(time(0));

    // initialize deck
    string suits = "cshd"; // cshd = clubs spades hearts diamonds
    vector <string> deck;
    for (int i = 0; i < 4; i++){
        deck.push_back("a" + suits.substr(i, 1)); // aces
        for (int ii = 0; ii < 9; ii++){
            deck.push_back(to_string(ii + 1) + suits.substr(i, 1));
        }
        deck.push_back("j" + suits.substr(i, 1)); // jacks
        deck.push_back("q" + suits.substr(i, 1)); // queens
        deck.push_back("k" + suits.substr(i, 1)); // kings
    }
    deck.push_back("ww");

    unsigned int counter = 0;

    for (int i = 0; i < 10000000; i++){
        string hand = "";
        for (int ii = 0; ii < 50; ii++) swap(deck[rand()%deck.size()], deck[rand()%deck.size()]); // this loop randomly shuffles the deck
        for (int ii = 0; ii < 5; ii++) hand += deck[ii]; // this loop draws five cards from the deck to the hand
        assert(hand.size() == 10);

        if (fullHouse(hand)){
            counter++;
            printf("%s\n", stripSuits(hand).c_str());
        }
    }
    printf("matches: %d\n", counter);
}
//--
string stripSuits(string& hand){return (hand.substr(0, 1) + hand.substr(2, 1) + hand.substr(4, 1) + hand.substr(6, 1) + hand.substr(8, 1));}
string stripVals(string& hand){return (hand.substr(1, 1) + hand.substr(3, 1) + hand.substr(5, 1) + hand.substr(7, 1) + hand.substr(9, 1));}