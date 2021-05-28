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
protected:
    std::string mana;
public:
    landCard(std::string n, std::string t, std::string m):Card(n, t), mana(m){

    }
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
    creatureCard(std::string n, std::string t, int attPow, std::string manaCo, std::string c, int hP):Card(n,t),attackPower(attPow), manaCost(manaCo), color(c), maxHP(hP){
        hp = maxHP;
    }
};
class Effect{

};
class enchantmentCard: public Card{
protected:
    std::string manaCost;
    std::string color;
    Effect effect;
    enchantmentCard(std::string n, std::string t, std::string manaCo, std::string c, Effect e):Card(n,t), manaCost(manaCo), color(c), effect(e){

    }
};

class sorceryCard: public Card{
protected:
    std::string manaCost;
    std::string color;
    Effect effect;
public:
    sorceryCard(std::string n, std::string t, std::string m, std::string c, Effect e) : Card(n, t), manaCost(m), effect(e), color(c) {

    }
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
void createDecks(){
    Effect effect;
    Player player1;
    std::vector<Card> player1Cards;
    //Creature Cards
    player1Cards.push_back(creatureCard("Soldier", "Creature", 1, "W", "White", 1));
    player1Cards.push_back(creatureCard("Soldier", "Creature", 1, "W", "White", 1));
    player1Cards.push_back(creatureCard("Soldier", "Creature", 1, "W", "White", 1));
    player1Cards.push_back(creatureCard("Armored Pegasus", "Creature", 1, "1W", "White", 2));
    player1Cards.push_back(creatureCard("Armored Pegasus", "Creature", 1, "1W", "White", 2));
    player1Cards.push_back(creatureCard("White Knight", "Creature", 2, "WW", "White", 2));
    player1Cards.push_back(creatureCard("White Knight", "Creature", 2, "WW", "White", 2));
    player1Cards.push_back(creatureCard("Angry Bear", "Creature", 3, "2G", "Green", 2));
    player1Cards.push_back(creatureCard("Guard", "Creature", 2, "2WW", "White", 5));
    player1Cards.push_back(creatureCard("Werewolf", "Creature", 4, "2GW", "Green", 6));
    //Sorcery Cards
    player1Cards.push_back(sorceryCard("Disenchant", "Sorcery", "White", "1W", effect));
    player1Cards.push_back(sorceryCard("Lightning Bolt", "Sorcery", "Green", "1G", effect));
    player1Cards.push_back(sorceryCard("Flood", "Sorcery", "Flood", "1GW", effect));
    player1Cards.push_back(sorceryCard("Flood", "Sorcery", "Flood", "1GW", effect));
    //Enchantment Card
    player1Cards.push_back(sorceryCard("Rage", "Enchantment", "Green", "G", effect));
    player1Cards.push_back(sorceryCard("Holy War", "Enchantment", "White", "1W", effect));
    player1Cards.push_back(sorceryCard("Holy Light", "Enchantment", "White", "1W", effect));
    //Land Card
    player1Cards.push_back(landCard("Plains", "Land", "W"));
    player1Cards.push_back(landCard("Plains", "Land", "W"));
    player1Cards.push_back(landCard("Plains", "Land", "W"));
    player1Cards.push_back(landCard("Plains", "Land", "W"));
    player1Cards.push_back(landCard("Plains", "Land", "W"));
    player1Cards.push_back(landCard("Forest", "Land", "G"));
    player1Cards.push_back(landCard("Forest", "Land", "G"));
    player1Cards.push_back(landCard("Forest", "Land", "G"));
    player1Cards.push_back(landCard("Island", "Land", "L"));

    for(int i = 0;i<player1Cards.capacity();i++){
        player1.addCardToDeck(player1Cards[i]);
    }

    Player player2;
    std::vector<Card> player2Cards;
    //Creature Cards
    player2Cards.push_back(creatureCard("Soldier", "Creature", 1, "W", "White", 1));
    player2Cards.push_back(creatureCard("Soldier", "Creature", 1, "W", "White", 1));
    player2Cards.push_back(creatureCard("Soldier", "Creature", 1, "W", "White", 1));
    player2Cards.push_back(creatureCard("Armored Pegasus", "Creature", 1, "1W", "White", 2));
    player2Cards.push_back(creatureCard("Armored Pegasus", "Creature", 1, "1W", "White", 2));
    player2Cards.push_back(creatureCard("White Knight", "Creature", 2, "WW", "White", 2));
    player2Cards.push_back(creatureCard("White Knight", "Creature", 2, "WW", "White", 2));
    player2Cards.push_back(creatureCard("Angry Bear", "Creature", 3, "2G", "Green", 2));
    player2Cards.push_back(creatureCard("Guard", "Creature", 2, "2WW", "White", 5));
    player2Cards.push_back(creatureCard("Werewolf", "Creature", 4, "2GW", "Green", 6));
    //Sorcery Cards
    player1Cards.push_back(sorceryCard("Reanimate", "Sorcery", "Black", "B", effect));
    player1Cards.push_back(sorceryCard("Plague", "Sorcery", "Black", "2B", effect));
    player1Cards.push_back(sorceryCard("Terror", "Sorcery", "Black", "1B", effect));
    player1Cards.push_back(sorceryCard("Terror", "Sorcery", "Black", "1B", effect));
    //Enchantment Card
    player1Cards.push_back(sorceryCard("Unholy War", "Land", "Black", "1B", effect));
    player1Cards.push_back(sorceryCard("Restrain", "Enchantment", "Red", "2R", effect));
    player1Cards.push_back(sorceryCard("Slow", "Enchantment", "Black", "B", effect));
    //Land Card
    player1Cards.push_back(landCard("Swamp", "Land", "B"));
    player1Cards.push_back(landCard("Swamp", "Land", "B"));
    player1Cards.push_back(landCard("Swamp", "Land", "B"));
    player1Cards.push_back(landCard("Swamp", "Land", "B"));
    player1Cards.push_back(landCard("Swamp", "Land", "B"));
    player1Cards.push_back(landCard("Mountain", "Land", "R"));
    player1Cards.push_back(landCard("Mountain", "Land", "R"));
    player1Cards.push_back(landCard("Mountain", "Land", "R"));
    player1Cards.push_back(landCard("Island", "Land", "L"));
    for(int i = 0;i<player2Cards.capacity();i++){
        player2.addCardToDeck(player2Cards[i]);
    }

    player1Cards.clear();
    player2Cards.clear();
}
int turn = 0;
void playGame(){
    createDecks();

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
