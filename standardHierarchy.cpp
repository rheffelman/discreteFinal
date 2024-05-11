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

    const long unsigned int iterations = 1000000000;
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
        bitset<11> bs;
        if (fiveOfAKind(hand)) bs[0] = 1;
        else if (royalFlush(hand)) bs[1] = 1;
        else if (straightFlush(hand)) bs[2] = 1;
        else if (fourOfAKind(hand)) bs[3] = 1;
        else if (fullHouse(hand)) bs[4] = 1;
        else if (flush(hand)) bs[5] = 1;
        else if (straight(hand)) bs[6] = 1;
        else if (threeOfAKind(hand)) bs[7] = 1;
        else if (twoPair(hand)) bs[8] = 1;
        else if (onePair(hand)) bs[9] = 1;
        else bs[10] = 1;
        assert(bs.count() == 1);
        for (int ii = 0; ii < 11; ii++) if(bs[ii]) tallies[ii]++;
    }

    printf("standard poker hierarchy:\n");
    printf("iterations: %ld\n", iterations);
    printf("five-of-a-kinds: %d\n", tallies[0]);
    printf("royal flushes: %d\n", tallies[1]);
    printf("straight flushes: %d\n", tallies[2]);
    printf("four-of-a-kinds: %d\n", tallies[3]);
    printf("full houses: %d\n", tallies[4]);
    printf("flushes: %d\n", tallies[5]);
    printf("straight: %d\n", tallies[6]);
    printf("three-of-a-kinds: %d\n", tallies[7]);
    printf("two pairs: %d\n", tallies[8]);
    printf("one pairs: %d\n", tallies[9]);
    printf("junk: %d\n", tallies[10]);

}
//--
bool onePair(string &hand){
    string s = stripSuits(hand);
    unordered_set<char> ht;
    for (int i = 0; i < s.size(); i++){
        if (ht.count(s[i]) or s[i] == 'w') return true;
        ht.insert(s[i]);
    }
    return false;
}
//--
bool twoPair(string &hand){
    string s = stripSuits(hand);
    unordered_set<char> ht;
    valarray<unsigned int> v;
    v.resize(14, 0);

    for (int i = 0; i < s.size(); i++){
        ht.insert(s[i]);
        if (s[i] == 'a') v[0]++;
        else if (s[i] == 'j') v[11]++;
        else if (s[i] == 'q') v[12]++;
        else if (s[i] == 'k') v[13]++;
        else v[((int)s[i])-47]++;
    }
    if (v.max() >= 4 or (v.max() >= 2 and ht.count('w'))) return true;
    else{
        bool onePair = false;
        for (int i = 0; i < v.size(); i++){
            if (v[i] == 2 or v[i] == 3){
                if (onePair)return true;
                else onePair = true;
            }
        }
    }
    return false;
}
//--
bool threeOfAKind(string& hand){
    string s = stripSuits(hand);
    unordered_set<char> ht;
    valarray<unsigned int> v;
    v.resize(14, 0);

    for (int i = 0; i < s.size(); i++){
        ht.insert(s[i]);
        if (s[i] == 'a') v[0]++;
        else if (s[i] == 'j') v[11]++;
        else if (s[i] == 'q') v[12]++;
        else if (s[i] == 'k') v[13]++;
        else v[((int)s[i])-47]++;
    }
    // if (!(v.max() == 3 or (v.max() == 2 and ht.count('w')))){
    //     for (int i = 0; i < v.size(); i++) printf("%d  ", v[i]);
    //     printf("\n%s\n", s.c_str());
    // }
    return (v.max() == 3 or (v.max() == 2 and ht.count('w')));
}
//--
bool fourOfAKind(string& hand){
    string s = stripSuits(hand);
    unordered_set<char> ht;
    valarray<unsigned int> v;
    v.resize(14, 0);

    for (int i = 0; i < s.size(); i++){
        ht.insert(s[i]);
        if (s[i] == 'a') v[0]++;
        else if (s[i] == 'j') v[11]++;
        else if (s[i] == 'q') v[12]++;
        else if (s[i] == 'k') v[13]++;
        else v[((int)s[i])-47]++;
    }
    // if (!(v.max() == 4 or (v.max() == 3 and ht.count('w')))){
    //     for (int i = 0; i < v.size(); i++) printf("%d  ", v[i]);
    //     printf("\n%s\n", s.c_str());
    // }
    return (v.max() == 4 or (v.max() == 3 and ht.count('w')));
}
//--
bool fiveOfAKind(string& hand){
    string s = stripSuits(hand);
    unordered_set<char> ht;
    for (int i = 0; i < s.size(); i++) ht.insert(s[i]);
    return (ht.size() == 2 and ht.count('w'));
}
//--
bool straight(string &hand){
    string s = stripSuits(hand);
    unordered_set<char> ht;
    for (int i = 0; i < s.size(); i++) ht.insert(s[i]);
    vector <string> cases {"a0123", "01234", "12345", "23456", "34567", "45678", "56789", "6789j", "789jq", "89jqk", "9jqka"};
    bool hasW = ht.count('w');

    for (int i = 0; i < cases.size(); i++){
        bitset<5> bs;
        for (int ii = 0; ii < cases[i].size(); ii++){
            if (ht.count(cases[i][ii])) bs[ii] = 1;
        }
        if ((bs.count() == 5) or ((bs.count() == 4) and (hasW))) return true;
    }
    
    return false;
}
//--
bool flush(string &hand){
    string s = stripVals(hand);
    unordered_set<char> ht;
    for (int i = 0; i < s.size(); i++) ht.insert(s[i]);
    return(ht.size() == 1 or (ht.size() == 2 and ht.count('w')));
}
//--
bool straightFlush(string& hand){
    return (straight(hand) and flush(hand));
}
//--
bool royalFlush(string &hand){
    if (flush(hand)){
        string s = stripSuits(hand);
        unordered_set<char> ht;
        for (int i = 0; i < s.size(); i++) ht.insert(s[i]);
        string rf = "a9kqj";
        unsigned int counter = 0;
        for (int i = 0; i < 5; i++) if (ht.count(rf[i])) counter++;
        return (counter == 5 or (counter == 4 and ht.count('w')));
    }
    return false;
}
//--
bool fullHouse(string& hand){
    string s = stripSuits(hand);
    valarray<unsigned int> v;
    v.resize(14, 0);
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
//--
string stripSuits(string& hand){return (hand.substr(0, 1) + hand.substr(2, 1) + hand.substr(4, 1) + hand.substr(6, 1) + hand.substr(8, 1));}
string stripVals(string& hand){return (hand.substr(1, 1) + hand.substr(3, 1) + hand.substr(5, 1) + hand.substr(7, 1) + hand.substr(9, 1));}