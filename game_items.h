#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <random>

using namespace std;

class Card { // Card class
public:    
    char suit; // ♠ ♥ ♦ ♣
    string rank;      
    unordered_set<int> modifiers;

    Card(char suit, string rank) { 
        this->suit=suit;
        this->rank=rank;
    }

    void add_modifier(int modifier_id) {
        this->modifiers.insert(modifier_id);
    }
};

class Deck { // Deck class
public:
    vector<Card> cards;
    vector<Card> discard_pile;

    Deck() { // Generates 52 cards on first run
        char suits[] = {'H', 'D', 'C', 'S'};
        string ranks[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
        for (char s : suits) {
            for (string r : ranks) {
                Card new_card = Card(s,r);
                cards.push_back(new_card);
            }
        }
        shuffle();
        discard_pile={};
    }

    void shuffle() { // shuffling the deck
        random_device rd;
        mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    Card draw() { // draw from deck
        if (cards.empty()) {
            throw runtime_error("Deck is empty!"); 
        }
        Card c = cards.back();
        cards.pop_back();
        return c;
    }

    void add(Card card) { // add card to deck
        cards.push_back(card);
    }

    void refresh() { // refresh from discard pile
        cards.insert(cards.end(), discard_pile.begin(), discard_pile.end());
        discard_pile.clear();
        shuffle();
    }

};

class Hand {
public:
    vector<Card> hand;
    unordered_set<int> stage; // selected cards

    Hand(Deck& deck, int hand_size=8) { // generate hand of specified size (helpful for modifiers)
        hand={};
        for (int i=0;i<hand_size;i++) {
            this->add(deck.draw());
        }
    }

    void add(Card c) { // adds card to hand
        hand.push_back(c);
    }
    
    void replace(Card c,int index) { // replace card
        hand[index]=c;
    }

    void generate(Deck& deck, int deck_size=8) { // generates hand at start of round
        for (int i=0;i<deck_size;i++) {
            this->add(deck.draw());
        }
    }
    void choose(int index) { // stage card
        if (0<=index && index<hand.size()) {
            if (stage.size()<5) {
                stage.insert(index);
            }
        }
    }
    void unchoose(int index) { // unstage card
        if (0<=index && index<hand.size()) {
            if (stage.size()>0) {
                stage.erase(index);
            }
        }
    }

    void refresh(Deck& deck) { // IMP: refresh hand before deck after round
        for (Card card : hand) {
            deck.discard_pile.push_back(card);
        }
        hand.clear();
        stage.clear();
    }

    vector<Card> play(Deck& deck) { // play out the staged cards
        vector<Card> res;
        if (stage.size()>0) {
            for (int index : stage) {
                res.push_back(hand[index]);
                this->replace(deck.draw(),index);
            }
        }
        stage.clear();
        return res;
    }

    
};

