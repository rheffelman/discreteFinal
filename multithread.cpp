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
#include<thread>
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
void simthread();

const long unsigned int iterations = 10000000;
const unsigned int shuffles = 53;
valarray<unsigned int> tallies;

int main(){

    tallies.resize(11, 0);
    const unsigned int threads = 10;
    vector<thread> t;
    for (int i = 0; i < threads; i++){
        t.push_back(thread(simthread));
    }
    for (int i = 0; i < threads; i++){
        t[i].join();
    }
    printf("threads: %d\n", threads);
    printf("iterations: %ld\n", iterations * threads);
    printf("non-junk matches: %d\n", tallies.sum() - tallies[10]);
    printf("five of a kinds: %d\n", tallies[9]);
    printf("royal flushes: %d\n", tallies[2]);
    printf("straight flushes: %d\n", tallies[4]);
    printf("two pairs: %d\n", tallies[8]);
    printf("full houses: %d\n", tallies[3]);
    printf("flushes: %d\n", tallies[1]);
    printf("straights: %d\n", tallies[0]);
    printf("four of a kinds: %d\n", tallies[7]);
    printf("three of a kinds: %d\n", tallies[6]);
    printf("junk: %d\n", tallies[10]);
    printf("one pairs: %d\n", tallies[5]);
}
//--
void simthread(){
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
    
    for (int i = 0; i < iterations; i++){
        string hand = "";
        for (int ii = 0; ii < shuffles; ii++) swap(deck[rand()%deck.size()], deck[rand()%deck.size()]); // this loop randomly shuffles the deck
        for (int ii = 0; ii < 5; ii++) hand += deck[ii]; // this loop draws five cards from the deck to the hand
        assert(hand.size() == 10);

        bitset<11> bs;
        bs[0] = straight(hand);
        bs[1] = flush(hand);
        bs[2] = royalFlush(hand);
        bs[3] = fullHouse(hand);
        bs[4] = straightFlush(hand);
        bs[5] = onePair(hand);
        bs[6] = twoPair(hand);
        bs[7] = threeOfAKind(hand);
        bs[8] = fourOfAKind(hand);
        bs[9] = fiveOfAKind(hand);
        if (!bs.count()) bs[10] = true;
        for (int i = 0; i < 11; i++) if(bs[i]) tallies[i]++;
    }
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

    for (int i = 0; i < s.size(); i++){
        if (ht.count(s[i])){
            ht.erase(s[i]);
            for (int ii = i++; ii < s.size(); ii++){
                if (ht.count(s[ii]) or s[ii] == 'w' or ht.count('w')) return true;
                ht.insert(s[ii]);
            }
            return false;
        }
        ht.insert(s[i]);
    }
    return false;
}
//--
bool threeOfAKind(string& hand){
    string s = stripSuits(hand);
    unordered_set<char> ht;
    for (int i = 0; i < s.size(); i++) ht.insert(s[i]);
    valarray<unsigned int> v;
    v.resize(13, 0);

    for (int i = 0; i < s.size(); i++){
        if (s[i] == 'a') v[0]++;
        else if (s[i] == 'j') v[11]++;
        else if (s[i] == 'q') v[12]++;
        else if (s[i] == 'k') v[13]++;
        else v[((int)s[i])-47]++;
    }
    return (v.max() == 3 or (v.max() == 2 and ht.count('w')));
}
//--
bool fourOfAKind(string& hand){
    string s = stripSuits(hand);
    unordered_set<char> ht;
    for (int i = 0; i < s.size(); i++) ht.insert(s[i]);
    valarray<unsigned int> v;
    v.resize(13, 0);

    for (int i = 0; i < s.size(); i++){
        if (s[i] == 'a') v[0]++;
        else if (s[i] == 'j') v[11]++;
        else if (s[i] == 'q') v[12]++;
        else if (s[i] == 'k') v[13]++;
        else v[((int)s[i])-47]++;
    }
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
//--
string stripSuits(string& hand){return (hand.substr(0, 1) + hand.substr(2, 1) + hand.substr(4, 1) + hand.substr(6, 1) + hand.substr(8, 1));}
string stripVals(string& hand){return (hand.substr(1, 1) + hand.substr(3, 1) + hand.substr(5, 1) + hand.substr(7, 1) + hand.substr(9, 1));}