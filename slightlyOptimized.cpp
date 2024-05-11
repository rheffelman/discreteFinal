#include<iostream>
#include<vector>
#include<valarray>
#include<unordered_set>
#include<string>
#include<regex>
#include<algorithm>
#include<random>
#include<ctime>
#include<cassert>
using namespace std;

bool straight(string& hand);
bool flush(string& hand);
bool royalFlush(string& hand);
bool fullHouse(string& hand);
bool straightFlush(string& hand);
bool onePair(string& hand);
bool twoPair(string& hand);
bool threeOfAKind(string& hand);
bool fourOfAKind(string& hand);
bool fiveOfAKind(string& hand);
string stripSuits(string& hand);
string stripVals(string& hand);

int main(){

    const long unsigned int iterations = 1000000;
    const unsigned int shuffles = 53;
    srand(time(0));

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

    valarray<unsigned int> tallies;
    tallies.resize(11, 0);
    for (int i = 0; i < iterations; i++){
        string hand = "";
        for (int ii = 0; ii < shuffles; ii++) swap(deck[rand()%deck.size()], deck[rand()%deck.size()]); // this loop randomly shuffles the deck
        for (int ii = 0; ii < 5; ii++) hand += deck[ii]; // this loop draws five cards from the deck to the hand
        assert(hand.size() == 10);
        
        string noSuits = hand.substr(0, 1) + hand.substr(2, 1) + hand.substr(4, 1) + hand.substr(6, 1) + hand.substr(8, 1);
        string noVals = hand.substr(1, 1) + hand.substr(3, 1) + hand.substr(5, 1) + hand.substr(7, 1) + hand.substr(9, 1);
        bitset<11> bs;
        bs[0] = straight(noSuits);
        bs[1] = flush(noVals);
        bs[2] = (bs[1] and royalFlush(hand));
        bs[3] = fullHouse(noSuits);
        bs[4] = (bs[0] and bs[1]);
        bs[5] = onePair(noSuits);
        bs[6] = twoPair(noSuits);
        bs[7] = threeOfAKind(noSuits);
        bs[8] = fourOfAKind(noSuits);
        bs[9] = fiveOfAKind(noSuits);
        if (!bs.count()) bs[10] = true;
        for (int i = 0; i < 11; i++) if(bs[i]) tallies[i]++;
    }
    printf("no hierarchy:\n");
    printf("iterations: %ld\n", iterations);
    for (int i = 0; i < tallies.size(); i++){
        printf("%d\n", tallies[i]);
    }
}
//--
bool onePair(string &hand){
    unordered_set<char> ht;
    for (int i = 0; i < hand.size(); i++){
        if (ht.count(hand[i]) or hand[i] == 'w') return true;
        ht.insert(hand[i]);
    }
    return false;
}
//--
bool twoPair(string &hand){
    unordered_set<char> ht;

    for (int i = 0; i < hand.size(); i++){
        if (ht.count(hand[i])){
            for (int ii = i++; ii < hand.size(); ii++){
                if (ht.count(hand[ii] and hand[ii] != hand[i]) or hand[ii] == 'w' or ht.count('w')) return true;
                ht.insert(hand[ii]);
            }
            return false;
        }
        ht.insert(hand[i]);
    }
    return false;
}
//--
bool threeOfAKind(string& hand){
    unordered_set<char> ht;
    valarray<unsigned int> v;
    v.resize(13, 0);

    for (int i = 0; i < hand.size(); i++){
        ht.insert(hand[i]);
        if (hand[i] == 'a') v[0]++;
        else if (hand[i] == 'j') v[11]++;
        else if (hand[i] == 'q') v[12]++;
        else if (hand[i] == 'k') v[13]++;
        else v[((int)hand[i])-47]++;
    }
    return (v.max() == 3 or (v.max() == 2 and ht.count('w')));
}
//--
bool fourOfAKind(string& hand){
    unordered_set<char> ht;
    valarray<unsigned int> v;
    v.resize(13, 0);

    for (int i = 0; i < hand.size(); i++){
        ht.insert(hand[i]);
        if (hand[i] == 'a') v[0]++;
        else if (hand[i] == 'j') v[11]++;
        else if (hand[i] == 'q') v[12]++;
        else if (hand[i] == 'k') v[13]++;
        else v[((int)hand[i])-47]++;
    }
    return (v.max() == 4 or (v.max() == 3 and ht.count('w')));
}
//--
bool fiveOfAKind(string& hand){
    unordered_set<char> ht;
    for (int i = 0; i < hand.size(); i++) ht.insert(hand[i]);
    return (ht.size() == 2 and ht.count('w'));
}
//--
bool straight(string &hand){
    unordered_set<char> ht;
    for (int i = 0; i < hand.size(); i++) ht.insert(hand[i]);
    vector <string> cases {"a0123", "01234", "12345", "23456", "34567", "45678", "56789", "6789j", "789jq", "89jqk"};
    bool hasW = ht.count('w');

    for (int i = 0; i < cases.size(); i++){
        bitset<5> bs;
        for (int ii = 0; ii < cases[i].size(); ii++){
            if (ht.count(cases[i][ii])) bs[ii] = true;
        }
        if ((bs.count() == 5) or ((bs.count() == 4) and (hasW))) return true;
    }
    return false;
}
//--
bool flush(string &hand){
    unordered_set<char> ht;
    for (int i = 0; i < hand.size(); i++) ht.insert(hand[i]);
    return(ht.size() == 1 or (ht.size() == 2 and ht.count('w')));
}
//--
bool straightFlush(string& hand){
    return (straight(hand) and flush(hand));
}
//--
bool royalFlush(string &hand){
    unordered_set<char> ht;
    for (int i = 0; i < hand.size(); i++) ht.insert(hand[i]);
    string rf = "a9kqj";
    unsigned int counter = 0;
    for (int i = 0; i < 5; i++) if (ht.count(rf[i])) counter++;
    return (counter == 5 or (counter == 4 and ht.count('w')));
}
//--
bool fullHouse(string& hand){
    valarray<unsigned int> v;
    v.resize(13, 0);
    unordered_set<char> ht;
    for (int i = 0; i < hand.size(); i++) ht.insert(hand[i]);

    if (ht.count('w')){
        for (int i = 0; i < hand.size(); i++){
            if (hand[i] == 'a') v[0]++;
            else if (hand[i] == 'j') v[11]++;
            else if (hand[i] == 'q') v[12]++;
            else if (hand[i] == 'k') v[13]++;
            else if (hand[i] == 'w') continue;
            else v[((int)hand[i])-47]++;
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

    for (int i = 0; i < hand.size(); i++){
        if (hand[i] == 'a') v[0]++;
        else if (hand[i] == 'j') v[11]++;
        else if (hand[i] == 'q') v[12]++;
        else if (hand[i] == 'k') v[13]++;
        else if (hand[i] == 'w') continue;
        else v[((int)hand[i])-47]++;
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
//--
string stripSuits(string& hand){return (hand.substr(0, 1) + hand.substr(2, 1) + hand.substr(4, 1) + hand.substr(6, 1) + hand.substr(8, 1));}
string stripVals(string& hand){return (hand.substr(1, 1) + hand.substr(3, 1) + hand.substr(5, 1) + hand.substr(7, 1) + hand.substr(9, 1));}