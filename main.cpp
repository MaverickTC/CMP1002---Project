#include <iostream>
#include <vector>

using namespace std;
class Card {
protected:
    string name;
    string type;
    bool isTapped;
public:
    Card(string name, string type )
    {
        this->name = name;
        this->type = type;
    }

    virtual void Play() = 0; // Pure Virtual Function Yaptım.

    virtual void Tap()
    {
        isTapped = true;
    }

    virtual void printInfo()
    {
        cout << name << " " << type;
    }
};

class Player {
protected:
    vector<shared_ptr<Card>> library, hand, inPlay, discard;
    bool hasWon;
    int playerMana;
    int hp;

public:
    Player()
    {
        hp = 15;
        playerMana = 0;
        hasWon = false;
    }
    bool getHasWon()
    {
        return hasWon;
    }

    void setMana(int mana)
    {
        playerMana = mana;
    }

    void addCardToDeck(shared_ptr<Card>& C1) {
        library.push_back(C1);
    }

    void addCardToHand(shared_ptr<Card>& C1){
        if(std::find(library.begin(), library.end(), C1) != library.end()) {
            library.erase(std::remove(library.begin(), library.end(), C1), library.end());
            hand.push_back(C1);
        }
    }

//    void addCardToDiscard(const Card &card)
//    {
//        discard.push_back(card);
//    }

    void printHand()
    {
        library[0]->printInfo(); //vectors first item(öylesine denemek amaçlı)
    }
};

class LandCard : public Card {
protected:
   string mana;
   bool isTapped;
   //Player playerM;
public:
    std::shared_ptr<Player> p1;
    LandCard(string name, string type, string mana,std::shared_ptr<Player> p1) :Card(name, type)
    {
        this->mana = mana;
        isTapped = false;
        this-> p1 = p1;
    }

    //LandCard():Card()
    //{

    //}

    void Play()
    {
        isTapped = true;
        p1->setMana(1); // tek mana yapıyor, manayı get ile artrabilirz de (öylesine :P)

    }
     void Tap()
    {
         isTapped = true;
    }

};


class CreatureCard : public Card {
protected:
    int attackPower;
    int maxHP;
    int hp;
    bool hasFirstStrike = false;
    string manaCost;
    string color;
    bool isTapped;
    bool isDestroyed;

public:
    CreatureCard(string name, string type, int attackPower, string manaCost, string color, int hp) :Card(name, type)
    {
        this->attackPower = attackPower;
        this->manaCost = manaCost;
        this->color = color;
        this->hp = hp;
        isTapped = false;
        isDestroyed = false;
    }
    void attack() {
        hp = maxHP;
    }
    void Tap()
    {

    }
    void Play()
    {

    }
     void printInfo()
     {
         cout << name << " " << type << " " << attackPower << " " << manaCost << " " << color << " " << hp << endl;
     }
        
};


class Effect {

};


class EnchantmentCard : public Card {
protected:
    string manaCost;
    string color;
    Effect effect;

public:
    EnchantmentCard(string name, string type, string manaCost, string color, Effect &effect ) :Card(name, type)
    {
        this->manaCost = manaCost;
        this->color = color;
        this->effect = effect;
    }
    void Tap()
    {

    }
    void Play()
    {

    }
};

class SorceryCard : public Card {
protected:
    string manaCost;
    string color;
    Effect effect;
public:
    SorceryCard(string name, string type, string manaCost, string color, Effect& effect) :Card(name, type)
    {
        this->manaCost = manaCost;
        this->color = color;
        this->effect = effect;
    }
    void Play()
    {

    }
};



vector<Player> players; 


void turnLoop() {

}
void createDecks(std::shared_ptr<Player> p1,std::shared_ptr<Player> p2) {
    Effect effect;

    //Creature Cards
    shared_ptr<Card>C1 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1);
    shared_ptr<Card>C2 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1);
    shared_ptr<Card>C3 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1);
    shared_ptr<Card>C4 = make_shared<CreatureCard>("Armored Pegasus", "Creature", 1, "1W", "White", 2);
    shared_ptr<Card>C5 = make_shared<CreatureCard>("Armored Pegasus", "Creature", 1, "1W", "White", 2);
    shared_ptr<Card>C6 = make_shared<CreatureCard>("White Knight", "Creature", 2, "WW", "White", 2);
    shared_ptr<Card>C7 = make_shared<CreatureCard>("White Knight", "Creature", 2, "WW", "White", 2);
    shared_ptr<Card>C8 = make_shared<CreatureCard>("Angry Bear", "Creature", 3, "2G", "Green", 2);
    shared_ptr<Card>C9 = make_shared<CreatureCard>("Guard", "Creature", 2, "2WW", "White", 5);
    shared_ptr<Card>C10 = make_shared<CreatureCard>("Werewolf", "Creature", 4, "2GW", "Green", 6);
    //Sorcery Cards
    shared_ptr<Card>C11 = make_shared<SorceryCard>("Disenchant", "Sorcery", "White", "1W", effect);
    shared_ptr<Card>C12 = make_shared<SorceryCard>("Lightning Bolt", "Sorcery", "Green", "1G", effect);
    shared_ptr<Card>C13 = make_shared<SorceryCard>("Flood", "Sorcery", "Flood", "1GW", effect);
    shared_ptr<Card>C14 = make_shared<SorceryCard>("Flood", "Sorcery", "Flood", "1GW", effect);
    //Enchantment Card
    shared_ptr<Card>C15 = make_shared<SorceryCard>("Rage", "Enchantment", "Green", "G", effect);
    shared_ptr<Card>C16 = make_shared<SorceryCard>("Holy War", "Enchantment", "White", "1W", effect);
    shared_ptr<Card>C17 = make_shared<SorceryCard>("Holy Light", "Enchantment", "White", "1W", effect);
    //Land Card
    shared_ptr<Card>C18 = make_shared<LandCard>("Plains", "Land", "W",p1);
    shared_ptr<Card>C19 = make_shared<LandCard>("Plains", "Land", "W",p1);
    shared_ptr<Card>C20 = make_shared<LandCard>("Plains", "Land", "W",p1);
    shared_ptr<Card>C21 = make_shared<LandCard>("Plains", "Land", "W",p1);
    shared_ptr<Card>C22 = make_shared<LandCard>("Plains", "Land", "W",p1);
    shared_ptr<Card>C23 = make_shared<LandCard>("Forest", "Land", "G",p1);
    shared_ptr<Card>C24 = make_shared<LandCard>("Forest", "Land", "G",p1);
    shared_ptr<Card>C25 = make_shared<LandCard>("Forest", "Land", "G",p1);
    shared_ptr<Card>C26 = make_shared<LandCard>("Island", "Land", "L",p1);

    p1->addCardToDeck(C1);
    p1->addCardToDeck(C2);
    p1->addCardToDeck(C3);
    p1->addCardToDeck(C4);
    p1->addCardToDeck(C5);
    p1->addCardToDeck(C6);
    p1->addCardToDeck(C7);
    p1->addCardToDeck(C8);
    p1->addCardToDeck(C9);
    p1->addCardToDeck(C10);
    p1->addCardToDeck(C11);
    p1->addCardToDeck(C12);
    p1->addCardToDeck(C13);
    p1->addCardToDeck(C14);
    p1->addCardToDeck(C15);
    p1->addCardToDeck(C16);
    p1->addCardToDeck(C17);
    p1->addCardToDeck(C18);
    p1->addCardToDeck(C19);
    p1->addCardToDeck(C20);
    p1->addCardToDeck(C21);
    p1->addCardToDeck(C22);
    p1->addCardToDeck(C23);
    p1->addCardToDeck(C24);
    p1->addCardToDeck(C25);
    p1->addCardToDeck(C26);
  
    //Creature Cards
    C1 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1);
    C2 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1);
    C3 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1);
    C4 = make_shared<CreatureCard>("Armored Pegasus", "Creature", 1, "1W", "White", 2);
    C5 = make_shared<CreatureCard>("Armored Pegasus", "Creature", 1, "1W", "White", 2);
    C6 = make_shared<CreatureCard>("White Knight", "Creature", 2, "WW", "White", 2);
    C7 = make_shared<CreatureCard>("White Knight", "Creature", 2, "WW", "White", 2);
    C8 = make_shared<CreatureCard>("Angry Bear", "Creature", 3, "2G", "Green", 2);
    C9 = make_shared<CreatureCard>("Guard", "Creature", 2, "2WW", "White", 5);
    C10 = make_shared<CreatureCard>("Werewolf", "Creature", 4, "2GW", "Green", 6);
    //Sorcery Cards
    C11 = make_shared<SorceryCard>("Reanimate", "Sorcery", "Black", "B", effect);
    C12 = make_shared<SorceryCard>("Plague", "Sorcery", "Black", "2B", effect);
    C13 = make_shared<SorceryCard>("Terror", "Sorcery", "Black", "1B", effect);
    C14 = make_shared<SorceryCard>("Terror", "Sorcery", "Black", "1B", effect);
    //Enchantment Card
    C15 = make_shared<EnchantmentCard>("Unholy War", "Land", "Black", "1B", effect);
    C16 = make_shared<EnchantmentCard>("Restrain", "Enchantment", "Red", "2R", effect);
    C17 = make_shared<EnchantmentCard>("Slow", "Enchantment", "Black", "B", effect);
    //Land Card
    C18 = make_shared<LandCard>("Swamp", "Land", "B",p2);
    C19 = make_shared<LandCard>("Swamp", "Land", "B",p2);
    C20 = make_shared<LandCard>("Swamp", "Land", "B",p2);
    C21 = make_shared<LandCard>("Swamp", "Land", "B",p2);
    C22 = make_shared<LandCard>("Swamp", "Land", "B",p2);
    C23 = make_shared<LandCard>("Mountain", "Land", "R",p2);
    C24 = make_shared<LandCard>("Mountain", "Land", "R",p2);
    C25 = make_shared<LandCard>("Mountain", "Land", "R",p2);
    C26 = make_shared<LandCard>("Island", "Land", "L",p2);

    p2->addCardToDeck(C1);
    p2->addCardToDeck(C2);
    p2->addCardToDeck(C3);
    p2->addCardToDeck(C4);
    p2->addCardToDeck(C5);
    p2->addCardToDeck(C6);
    p2->addCardToDeck(C7);
    p2->addCardToDeck(C8);
    p2->addCardToDeck(C9);
    p2->addCardToDeck(C10);
    p2->addCardToDeck(C11);
    p2->addCardToDeck(C12);
    p2->addCardToDeck(C13);
    p2->addCardToDeck(C14);
    p2->addCardToDeck(C15);
    p2->addCardToDeck(C16);
    p2->addCardToDeck(C17);
    p2->addCardToDeck(C18);
    p2->addCardToDeck(C19);
    p2->addCardToDeck(C20);
    p2->addCardToDeck(C21);
    p2->addCardToDeck(C22);
    p2->addCardToDeck(C23);
    p2->addCardToDeck(C24);
    p2->addCardToDeck(C25);
    p2->addCardToDeck(C26);
}
int turn = 0;
void playGame() {
    bool isGameFinished = false;

    while (!isGameFinished) {
        turnLoop();
        turn = (turn == 0) ? turn = 1 : turn = 0;

        isGameFinished = true;
    }
}
void setupGame(){
    shared_ptr<Player> p1 = make_shared<Player>();
    shared_ptr<Player> p2 = make_shared<Player>();

    createDecks(p1, p2);

    p1->printHand();

    playGame();
}

int main() {
    setupGame();
    
    return 0;
}
