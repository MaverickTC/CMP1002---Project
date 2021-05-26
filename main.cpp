#include <iostream>
#include <vector>

class Card{
protected:
    std::string name;
    std::string type;
    virtual void Play(){

    }
    Card(std::string n, std::string t):name(n),type(t){} ;
};
class landCard: public Card{

};
class creatureCard: public Card{
protected:
    int attackPower;
    int maxHP;
    int hp;
    bool hasFirstStrike;
    std::string manaCost;
    std::string color;
    void attack(){
        hp = maxHP;
    }

public:
    creatureCard(std::string n, std::string t, int attPow, std::string manaCo, std::string c):Card(n,t),attackPower(attPow), manaCost(manaCo), color(c){
        maxHP = 15;
        hp = maxHP;
    }
};
class enchantmentCard: public Card{
protected:
    int manaCost;
    std::string color;
};
class sorceryCard: public Card{
protected:
    int manaCost;
    std::string color;
};
class Effect{

};
class Player{
protected:
    std::vector<Card> deck, hand, inPlay, discard;
public:
    void addCardToDeck(Card card){
        deck.push_back(card);
    }
};

std::vector<Player> players;
void turnLoop(){

}
int turn = 0;
void playGame(){
    Player player1;
    creatureCard c1("Soldier", "Creature", 1, "W", "White");
    creatureCard c2("Soldier", "Creature", 1, "W", "White");
    creatureCard c3("Soldier", "Creature", 1, "W", "White");
    player1.addCardToDeck(c1);
    player1.addCardToDeck(c2);
    player1.addCardToDeck(c3);

    bool isGameFinished = false;
    while(!isGameFinished){
        turnLoop();
        turn = (turn==0) ? turn=1:turn=0;
    }
}
int main() {
    playGame();
    return 0;
}
