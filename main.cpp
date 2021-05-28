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

    virtual void Play() {

    }
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
    vector<shared_ptr<Card>> deck, hand, inPlay, discard;
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
        deck.push_back(C1);
    }

//    void addCardToDiscard(const Card &card)
//    {
//        discard.push_back(card);
//    }

    void printHand()
    {
        deck[0]->printInfo(); //vectors first item(öylesine denemek amaçlı)
    }
};

class LandCard : public Card {
protected:
   string mana;
   bool isTapped;
   //Player playerM;
public:
	Player *p1;
    LandCard(string name, string type, string mana,Player *p1) :Card(name, type)
    {
        this->mana = mana;
        isTapped = false;
        this-> p1 = p1;
    }

    LandCard():Card()
    {

    }

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

};



vector<Player> players; 


void turnLoop() {

}
void createDecks(Player *p1,Player *p2) {
    Effect effect;

    Player* player1;
    Player* player2;
    player1 = p1;
    player2 = p2;

    shared_ptr<Card>C1= make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1);
    shared_ptr<Card>C2 = make_shared<LandCard>("Forest", "Land", "G",player1);
   
    p1->addCardToDeck(C2); //sadece land'i ekledim





    //Creature Cards

//    p1.addCardToDeck(CreatureCard("Soldier", "Creature", 1, "W", "White", 1));
//    p1.addCardToDeck(CreatureCard("Soldier", "Creature", 1, "W", "White", 1));
//    p1.addCardToDeck(CreatureCard("Soldier", "Creature", 1, "W", "White", 1));
//    p1.addCardToDeck(CreatureCard("Armored Pegasus", "Creature", 1, "1W", "White", 2));
//    p1.addCardToDeck(CreatureCard("Armored Pegasus", "Creature", 1, "1W", "White", 2));
//    p1.addCardToDeck(CreatureCard("White Knight", "Creature", 2, "WW", "White", 2));
//    p1.addCardToDeck(CreatureCard("White Knight", "Creature", 2, "WW", "White", 2));
//    p1.addCardToDeck(CreatureCard("Angry Bear", "Creature", 3, "2G", "Green", 2));
//    p1.addCardToDeck(CreatureCard("Guard", "Creature", 2, "2WW", "White", 5));
//    p1.addCardToDeck(CreatureCard("Werewolf", "Creature", 4, "2GW", "Green", 6));
    //Sorcery Cards
//   p1.addCardToDeck(SorceryCard("Disenchant", "Sorcery", "White", "1W", effect));
//    p1.addCardToDeck(SorceryCard("Lightning Bolt", "Sorcery", "Green", "1G", effect));
//    p1.addCardToDeck(SorceryCard("Flood", "Sorcery", "Flood", "1GW", effect));
//    p1.addCardToDeck(SorceryCard("Flood", "Sorcery", "Flood", "1GW", effect));
    //Enchantment Card
//   p1.addCardToDeck(SorceryCard("Rage", "Enchantment", "Green", "G", effect));
//    p1.addCardToDeck(SorceryCard("Holy War", "Enchantment", "White", "1W", effect));
//   p1.addCardToDeck(SorceryCard("Holy Light", "Enchantment", "White", "1W", effect));
    //Land Card
//    p1.addCardToDeck(LandCard("Plains", "Land", "W"));
//    p1.addCardToDeck(LandCard("Plains", "Land", "W"));
//    p1.addCardToDeck(LandCard("Plains", "Land", "W"));
 //   p1.addCardToDeck(LandCard("Plains", "Land", "W"));
//    p1.addCardToDeck(LandCard("Plains", "Land", "W"));
//    p1.addCardToDeck(LandCard("Forest", "Land", "G"));
 //   p1.addCardToDeck(LandCard("Forest", "Land", "G"));
 //   p1.addCardToDeck(LandCard("Forest", "Land", "G"));
  //  p1.addCardToDeck(LandCard("Island", "Land", "L"));
    
  
    //Creature Cards
   // p2.addCardToDeck(CreatureCard("Soldier", "Creature", 1, "W", "White", 1));
   // p2.addCardToDeck(CreatureCard("Soldier", "Creature", 1, "W", "White", 1));
   // p2.addCardToDeck(CreatureCard("Soldier", "Creature", 1, "W", "White", 1));
 //   p2.addCardToDeck(CreatureCard("Armored Pegasus", "Creature", 1, "1W", "White", 2));
  //  p2.addCardToDeck(CreatureCard("Armored Pegasus", "Creature", 1, "1W", "White", 2));
  //  p2.addCardToDeck(CreatureCard("White Knight", "Creature", 2, "WW", "White", 2));
 //   p2.addCardToDeck(CreatureCard("White Knight", "Creature", 2, "WW", "White", 2));
  //  p2.addCardToDeck(CreatureCard("Angry Bear", "Creature", 3, "2G", "Green", 2));
  //  p2.addCardToDeck(CreatureCard("Guard", "Creature", 2, "2WW", "White", 5));
 //   p2.addCardToDeck(CreatureCard("Werewolf", "Creature", 4, "2GW", "Green", 6));
    //Sorcery Cards
   // p2.addCardToDeck(SorceryCard("Reanimate", "Sorcery", "Black", "B", effect));
  //  p2.addCardToDeck(SorceryCard("Plague", "Sorcery", "Black", "2B", effect));
  //  p2.addCardToDeck(SorceryCard("Terror", "Sorcery", "Black", "1B", effect));
  //  p2.addCardToDeck(SorceryCard("Terror", "Sorcery", "Black", "1B", effect));
    //Enchantment Card
 //   p2.addCardToDeck(SorceryCard("Unholy War", "Land", "Black", "1B", effect));
  //  p2.addCardToDeck(SorceryCard("Restrain", "Enchantment", "Red", "2R", effect));
 //   p2.addCardToDeck(SorceryCard("Slow", "Enchantment", "Black", "B", effect));
    //Land Card
 //   p2.addCardToDeck(LandCard("Swamp", "Land", "B"));
 //   p2.addCardToDeck(LandCard("Swamp", "Land", "B"));
 //   p2.addCardToDeck(LandCard("Swamp", "Land", "B"));
 //   p2.addCardToDeck(LandCard("Swamp", "Land", "B"));
 //   p2.addCardToDeck(LandCard("Swamp", "Land", "B"));
  //  p2.addCardToDeck(LandCard("Mountain", "Land", "R"));
 //   p2.addCardToDeck(LandCard("Mountain", "Land", "R"));
 //   p2.addCardToDeck(LandCard("Mountain", "Land", "R"));
 //   p2.addCardToDeck(LandCard("Island", "Land", "L"));

}
int turn = 0;
void playGame() {
    Player *p1;
    Player *p2;

    p1=new Player();
    p2=new Player();

    createDecks(p1,p2);
    bool isGameFinished = false;
    

    while (!isGameFinished) {
        turnLoop();
        turn = (turn == 0) ? turn = 1 : turn = 0;

        isGameFinished = true;

    }

    p1.printHand();
    
}
int main() {
    playGame();

    
    
    return 0;
}
