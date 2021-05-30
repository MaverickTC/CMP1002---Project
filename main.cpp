#include <iostream>
#include <vector>

using namespace std;

class Card {
protected:
    string name;
    string type;
    bool isTapped;
public:
    Card()
    {
        name = "no name";
        type = "null type";
        isTapped = false;
    }

    Card(string name, string type )
    {
        this->name = name;
        this->type = type;
        isTapped = false;
    }

    virtual void Play() = 0;

    virtual string getType()
    {
        return type;
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
    
    bool hasWon;
    int playerMana;
    int hp;

public:
    vector<shared_ptr<Card>> library, hand, inPlay, discard;
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

    int getMana()
    {
        return playerMana;
    }
    
    int getHp()
    {
        return hp;
    }

    void addMana(int mana)
    {
        playerMana = mana;
    }

    void addCardToDeck(shared_ptr<Card>& C1) {
        library.push_back(C1);
    }

    void drawCard(shared_ptr<Card>& C1) {  
        if (find(library.begin(), library.end(), C1) != library.end()) {
            library.erase(remove(library.begin(), library.end(), C1), library.end());
            hand.push_back(C1);
        }
    }
    void addCardToinPlay(shared_ptr<Card>& C1)
    {
        if (find(hand.begin(), hand.end(), C1) != hand.end()) {
            hand.erase(remove(hand.begin(), hand.end(), C1), hand.end());
            inPlay.push_back(C1);
        }
    }

    void addCardToDiscard(shared_ptr<Card>& C1)
    {
        if (find(hand.begin(), hand.end(), C1) != hand.end()) {
            hand.erase(remove(hand.begin(), hand.end(), C1), hand.end());
            discard.push_back(C1);
        }

        else if (find(inPlay.begin(), inPlay.end(), C1) != inPlay.end()) {
            inPlay.erase(remove(inPlay.begin(), inPlay.end(), C1), inPlay.end());
            discard.push_back(C1);
        }
    }

    void printHand()
    {
        cout << "CARDS IN YOUR HAND: " << endl;
        for (int i = 0; i < hand.size(); i++)
        {
            (hand[i])->printInfo();
            cout << '\t';
            cout << "index: " << i << '\t';
        }
        cout << endl;
    }

    void printInplay()
    {
        cout << "CARDS IN PLAY: " << endl;
        for (int i=0 ; i<inPlay.size(); i++)
        {
            (inPlay[i])->printInfo();
            cout << '\t';
        }
        cout << endl;
    }

    void printDiscard()
    {
        cout << "CARDS IN DISCARD PILE: " << endl;
        for (int i = 0; i < discard.size(); i++)
        {
            (discard[i])->printInfo();
            cout << '\t';
        }
        cout << endl;
    }

    void printLibrary()//test etmek için funtion, ileride silinecek.
    {
        cout << "CARDS IN LIBRARY: " << endl;
        for (int i = 0; i < library.size(); i++)
        {
            (library[i])->printInfo();
            cout << endl;
        }

    }
    void playItemAtHand(int a) {
        //int index;
        //if (a > 6)
        //{
        //    cout << "please enter a correct index";
        //    cin >> index;
        //    playItemAtHand(index);
        //}

        hand[a]->Play();

        if (hand[a]->getType() == "Sorcery")
        {
            addCardToDiscard(hand[a]);
        }
        else
        {
            addCardToinPlay(hand[a]);
        }
    }

};

class Effect {

};

class LandCard : public Card {
protected:
   string mana;
   bool isTapped;
   std::shared_ptr<Player> p1;
   
public:
    LandCard(string name, string type, string mana, std::shared_ptr<Player> p1) :Card(name, type)
    {
        this->mana = mana;
        isTapped = false;
        this->p1 = p1;
    }
    LandCard():Card()
    {
        mana = "no mana ";
        isTapped = false;

    }
    void printInfo()
    {
        cout << name << " " << type << " " << mana;
    }
    void Tap()
    {
        isTapped = true;
        
    }
    void Play()
    {   
    
     p1->addMana(p1->getMana()+1);
     //shared_ptr<Card>LandPlayed = make_shared<LandCard>(name, type, mana, p1);//burası değişmeli sanırım, in play'e kart gitmiyor elden.

    }

    string getType()
    {
        return type;
    }


};

class CreatureCard : public Card {
protected:
    int attackPower;
    int maxHP;
    int hp;
    bool hasFirstStrike = false;
    bool hasTrample = false;
    string manaCost;
    string color;
    bool isTapped;
    bool isDestroyed;
    std::shared_ptr<Player> p1;
public:
   
    CreatureCard():Card(){
        attackPower =0;
        manaCost = "null cost";
        color = "no color";
        hp = 0;
        isTapped = false;
        isDestroyed = false;
    }

    CreatureCard(string name, string type, int attackPower, string manaCost, string color, int hp, std::shared_ptr<Player> p1) :Card(name, type)
    {
        this->attackPower = attackPower;
        this->manaCost = manaCost;
        this->color = color;
        this->hp = hp;
        isTapped = false;
        isDestroyed = false;
        this->p1 = p1;
      
    }
    void attack() {
        hp = maxHP;
    }
     void Tap()
    {
         isTapped = true;
    }
     void Play()
     {
         //shared_ptr<Card>CreaturePlayed = make_shared<CreatureCard>(name, type, attackPower,manaCost,color,hp ,p1);//burası değişmeli sanırım, in play'e kart gitmiyor elden.
         //p1->addCardToinPlay(CreaturePlayed);
     }
     
     void printInfo()
     {
         cout << name << " " << type << " " << attackPower << " " << manaCost << " " << color << " " << hp;
     }

     string getType()
     {
         return type;
     }
    
        
};

class EnchantmentCard : public Card {
protected:
    string manaCost;
    string color;
    Effect effect;
    std::shared_ptr<Player> p1;
public:
    
    EnchantmentCard() :Card()
    {
        manaCost = "no cost";
        color = "no color";
    }

    EnchantmentCard(string name, string type, string manaCost, string color, std::shared_ptr<Player> p1, Effect &effect ) :Card(name, type)
    {
        
        this->manaCost = manaCost;
        this->color = color;
        this->effect = effect;
        this->p1 = p1;
       
    }

    void ActivateEnchantment()
    {

    }
     void Play()
     {
     /*    shared_ptr<Card>EnchantmentPlayed = make_shared<EnchantmentCard>(name, type, manaCost, color, p1, effect);
         p1->addCardToinPlay(EnchantmentPlayed);*/

     }

     string getType()
     {
         return type;
     }
};

class SorceryCard : public Card {
protected:
    string manaCost;
    string color;
    Effect effect;
    
public:
    std::shared_ptr<Player> p1;
    SorceryCard(string name, string type, string manaCost, string color, std::shared_ptr<Player> p1, Effect& effect) :Card(name, type)
    {

        this->manaCost = manaCost;
        this->color = color;
        this->effect = effect;
        this->p1 = p1;
    }
    SorceryCard() :Card()
    {
        manaCost = "no cost";
        color = "no color";
    }

    void Play()
    {
        //shared_ptr<Card>SorceryPlayed = make_shared<SorceryCard>(name, type, manaCost, color, p1, effect); //burası değişmeli, in play'e kart gitmiyor elden çünkü farklı bir obje..
        //p1->addCardToDiscard(SorceryPlayed);//sorcery oynanınca discard'a gidiyor.
    }

    string getType()
    {
        return type;
    }
};

void turnLoop() {

}
void createDecks(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
    Effect effect;
    shared_ptr<Player> player1;
    shared_ptr<Player>player2;
    player1 = p1;
    player2 = p2;

    ////Creature Cards
    shared_ptr<Card>C1 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1,player1);
    shared_ptr<Card>C2 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1, player1);
    shared_ptr<Card>C3 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1, player1);
    shared_ptr<Card>C4 = make_shared<CreatureCard>("Armored Pegasus", "Creature", 1, "1W", "White", 2, player1);
    shared_ptr<Card>C5 = make_shared<CreatureCard>("Armored Pegasus", "Creature", 1, "1W", "White", 2, player1);
    shared_ptr<Card>C6 = make_shared<CreatureCard>("White Knight", "Creature", 2, "WW", "White", 2, player1);
    shared_ptr<Card>C7 = make_shared<CreatureCard>("White Knight", "Creature", 2, "WW", "White", 2, player1);
    shared_ptr<Card>C8 = make_shared<CreatureCard>("Angry Bear", "Creature", 3, "2G", "Green", 2, player1);
    shared_ptr<Card>C9 = make_shared<CreatureCard>("Guard", "Creature", 2, "2WW", "White", 5, player1);
    shared_ptr<Card>C10 = make_shared<CreatureCard>("Werewolf", "Creature", 4, "2GW", "Green", 6, player1);

    ////Sorcery Cards
    shared_ptr<Card>C11 = make_shared<SorceryCard>("Disenchant", "Sorcery", "White", "1W",player1,  effect);
    shared_ptr<Card>C12 = make_shared<SorceryCard>("Lightning Bolt", "Sorcery", "Green", "1G", player1, effect);
    shared_ptr<Card>C13 = make_shared<SorceryCard>("Flood", "Sorcery", "Flood", "1GW", player1, effect);
    shared_ptr<Card>C14 = make_shared<SorceryCard>("Flood", "Sorcery", "Flood", "1GW", player1, effect);
     
    ////Enchantment Cards
    shared_ptr<Card>C15 = make_shared<SorceryCard>("Rage", "Enchantment", "Green", "G", player1, effect);
    shared_ptr<Card>C16 = make_shared<SorceryCard>("Holy War", "Enchantment", "White", "1W", player1, effect);
    shared_ptr<Card>C17 = make_shared<SorceryCard>("Holy Light", "Enchantment", "White", "1W", player1, effect);

    //Land Cards
    shared_ptr<Card>C18 = make_shared<LandCard>("Plains", "Land", "W", player1);
    shared_ptr<Card>C19 = make_shared<LandCard>("Plains", "Land", "W", player1);
    shared_ptr<Card>C20 = make_shared<LandCard>("Plains", "Land", "W", player1);
    shared_ptr<Card>C21 = make_shared<LandCard>("Plains", "Land", "W", player1);
    shared_ptr<Card>C22 = make_shared<LandCard>("Plains", "Land", "W", player1);
    shared_ptr<Card>C23 = make_shared<LandCard>("Forest", "Land", "G", player1);
    shared_ptr<Card>C24 = make_shared<LandCard>("Forest", "Land", "G", player1);
    shared_ptr<Card>C25 = make_shared<LandCard>("Forest", "Land", "G", player1);
    shared_ptr<Card>C26 = make_shared<LandCard>("Island", "Land", "L", player1);

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

    //////////////////////////////////////////////////////////////////////////////////////////////////

    //Creature Cards
    C1 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1,player2);
    C2 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1,player2);
    C3 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1,player2);
    C4 = make_shared<CreatureCard>("Armored Pegasus", "Creature", 1, "1W", "White", 2,player2);
    C5 = make_shared<CreatureCard>("Armored Pegasus", "Creature", 1, "1W", "White", 2,player2);
    C6 = make_shared<CreatureCard>("White Knight", "Creature", 2, "WW", "White", 2,player2);
    C7 = make_shared<CreatureCard>("White Knight", "Creature", 2, "WW", "White", 2,player2);
    C8 = make_shared<CreatureCard>("Angry Bear", "Creature", 3, "2G", "Green", 2,player2);
    C9 = make_shared<CreatureCard>("Guard", "Creature", 2, "2WW", "White", 5,player2);
    C10 = make_shared<CreatureCard>("Werewolf", "Creature", 4, "2GW", "Green", 6,player2);

    //Sorcery Cards
    C11 = make_shared<SorceryCard>("Reanimate", "Sorcery", "Black", "B", player2,effect);
    C12 = make_shared<SorceryCard>("Plague", "Sorcery", "Black", "2B",player2, effect);
    C13 = make_shared<SorceryCard>("Terror", "Sorcery", "Black", "1B",player2, effect);
    C14 = make_shared<SorceryCard>("Terror", "Sorcery", "Black", "1B", player2,effect);

    //Enchantment Card
    C15 = make_shared<EnchantmentCard>("Unholy War", "Land", "Black", "1B",player2, effect);
    C16 = make_shared<EnchantmentCard>("Restrain", "Enchantment", "Red", "2R", player2,effect);
    C17 = make_shared<EnchantmentCard>("Slow", "Enchantment", "Black", "B", player2,effect);
    
    //Land Card
    C18 = make_shared<LandCard>("Swamp", "Land", "B", player2);
    C19 = make_shared<LandCard>("Swamp", "Land", "B", player2);
    C20 = make_shared<LandCard>("Swamp", "Land", "B", player2);
    C21 = make_shared<LandCard>("Swamp", "Land", "B", player2);
    C22 = make_shared<LandCard>("Swamp", "Land", "B", player2 );
    C23 = make_shared<LandCard>("Mountain", "Land", "R", player2);
    C24 = make_shared<LandCard>("Mountain", "Land", "R", player2);
    C25 = make_shared<LandCard>("Mountain", "Land", "R", player2);
    C26 = make_shared<LandCard>("Island", "Land", "L", player2);

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
    //////////////////////////////////////////////////////////////////////////////////////////
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

void setupGame() {
    shared_ptr<Player> p1 = make_shared<Player>();
    shared_ptr<Player> p2 = make_shared<Player>();

    createDecks(p1, p2);
    p1->printLibrary();//bu fonksiyon kontrol için,kalkacak

    //burdan aşağısı loop'ta olucak tabii- biraz manuel denedim
    cout << endl;
    cout << "YOU HAVE: " << p1->getMana() << " MANA." << endl;
  
  

    p1->drawCard(p1->library[17]); //buralar tabi randomize olmalı. burada ilk item desteden çekiyorum
    p1->drawCard(p1->library[18]);
    p1->drawCard(p1->library[19]);//3 tane land çektim.
    p1->drawCard(p1->library[11]);

    p1->printHand();
    p1->printInplay();

    p1->playItemAtHand(3);//sorcery, discard pile'a gidiyor.
    p1->playItemAtHand(0);//land kart. in play'e gidiyor.

    p1->printHand();
    p1->printInplay();
    p1->printDiscard();

    cout << "YOU HAVE: " << p1->getMana() << " MANA." << endl;
    playGame();
}
int main() {
    setupGame();

    return 0;
}
