#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <random>

using namespace std;

class Card {
public:    
    char suit; // ♠ ♥ ♦ ♣
    string rank;      
    unordered_set<int> modifiers;

    Card(char suit, char rank) { 
        this->suit=suit;
        this->rank=rank;
    }

    void add_modifier(int modifier_id) {
        this->modifiers.insert(modifier_id);
    }
};

class Deck {
public:
    vector<Card> cards;

    Deck() {
        char suits[] = {'H', 'D', 'C', 'S'};
        string ranks[] = {'2','3','4','5','6','7','8','9','10','J','Q','K'}
        for (char s : suits) {
            for (char r : ranks) {
                Card new_card = new Card(val,suit);
                cards.push_back(new_card);
            }
        }
        shuffle();
    }

    void shuffle() {
        random_device rd;
        mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    Card draw() {
        if (cards.empty()) {
            throw runtime_error("Deck is empty!");
        }
        Card c = cards.back();
        cards.pop_back();
        return c;
    }

    bool isEmpty() const {
        return cards.empty();
    }
};

class Hand {
public:
    vector<Card> cards;

    void add(Card c) {
        cards.push_back(c);
    }
};
