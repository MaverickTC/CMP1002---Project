#include <iostream>
#include <vector>

using namespace std;

class Card {
protected:
    string name;
    string type;
    bool isTapped;
    int hp;
    int maxHP;
    bool hasFirstStrike;
    bool hasTrample;
public:
    Card()
    {
        name = "no name";
        type = "null type";
        isTapped = false;
    }

    Card(string name, string type)
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
    virtual void Untap()
    {
        isTapped = false;
    }

    virtual void printInfo()
    {
        cout << name << " " << type;
    }

    virtual bool getStatus()
    {
        return isTapped;
    }

    virtual void activateAbility(int a)
    {

    }
    virtual int getHp()
    {
        return 1;
    }

    virtual int getMaxHP()
    {
        return 1;
    }
    virtual bool isDead()
    {
        return true;
    }

    virtual void setHp(int a)
    {

    }

    virtual string getName() {
        return name;

    }

    virtual int getAttackPower()
    {
        return 1;
    }


   virtual bool getHasFirstStrike()
    {
        return hasFirstStrike;
    }

    virtual bool getHasTrample()
    {
        return hasTrample;
    }
};
void setVectorSize(vector<int>* v) { //Vektör boşsa içine 5 tane 0 ekliyor. (Mana ücretleri için)
    if (v->size() == 0) {
        for (int i = 0; i < 5; i++) {
            v->push_back(0);
        }
    }
}
class Player {
protected:

    bool hasWon;
    int hp;

public:
    vector<shared_ptr<Card>> library, hand, inPlay, discard;
    vector<int> manaCount; //White, Green, Black, Red, Blue, Colorless
    Player()
    {
        hp = 15;
        hasWon = false;
        setVectorSize(&manaCount);
    }
    bool getHasWon()
    {
        return hasWon;
    }

    int getHp()
    {
        return hp;
    }

    void setHp(int a)
    {
        hp = a;

    }

    void setManaVector(string manaType)
    {
            if (manaType == "W")
            {
                manaCount[0]++;
            }

            else if (manaType == "G")
            {
                manaCount[1]++;
            }
            else if (manaType == "B")
            {
                manaCount[2]++;
            }
            else if (manaType == "R")
            {
                manaCount[3]++;
            }
             else if (manaType == "L")
            {
                manaCount[4]++;
            }
    }

    void SetManaToZero()
    {           //Oyunun turnlerinden birinde bütün kartlar untap oluyor, manayı sıfırlamak için.
        for (int i = 0; i < manaCount.size(); i++)
        {
            manaCount[i] = 0;
        }
    }

    void untapAllinPlay()
    {
        for (int i = 0; i < inPlay.size(); i++)
        {
            (inPlay[i])->Untap();

            cout << "index: " << i << '\t';
        }
    }

    void printManaVector()
    {
        for (int i = 0;i<5; i++)
        {
            cout << manaCount[i];
        }
        cout << endl;
    }

    int getLibraryElementCount() {
        return library.size();
    }

    int getHandElementCount() {
        return hand.size();
    }

    void addCardToDeck(shared_ptr<Card> &C1) {
        library.push_back(C1);
    }

    void drawCard(shared_ptr<Card> &C1) {
        if (find(library.begin(), library.end(), C1) != library.end()) {
            hand.push_back(C1);
            library.erase(remove(library.begin(), library.end(), C1), library.end());
        }
    }
    void addCardToinPlay(shared_ptr<Card> &C1)
    {
        if (find(hand.begin(), hand.end(), C1) != hand.end()) {
            inPlay.push_back(C1);
            hand.erase(remove(hand.begin(), hand.end(), C1), hand.end());
        }
    }

    void addCardToDiscard(shared_ptr<Card>& C1)
    {
        if (find(hand.begin(), hand.end(), C1) != hand.end()) {
            discard.push_back(C1);
            hand.erase(remove(hand.begin(), hand.end(), C1), hand.end());

        }
        else if (find(inPlay.begin(), inPlay.end(), C1) != inPlay.end()) {
            discard.push_back(C1);
            inPlay.erase(remove(inPlay.begin(), inPlay.end(), C1), inPlay.end());

        }
    }

    void addCardToHandByInt(int id) {
        hand.push_back(library[id]);
        library.erase(library.begin() + id);
    }

    void checkManaCost(string s) { //Stringi gerekli olan mana ücretleri için vektöre çeviriyor
        vector<int> requiredMana;
        setVectorSize(&requiredMana);
        for (int i = 0; i < s.length(); i++) {
            if (isdigit(s[i])) {
                requiredMana[5] += ((int)s[i] - 48);
            }
            else {
                if (s[i] == 'W') {
                    requiredMana[0]++;
                } if (s[i] == 'G') {
                    requiredMana[1]++;
                } if (s[i] == 'B') {
                    requiredMana[2]++;
                } if (s[i] == 'R') {
                    requiredMana[3]++;
                } if (s[i] == 'L') {
                    requiredMana[4]++;
                }
            }
        }
        cout << payMana(requiredMana) << endl; //Denemek için print ediyor normalde etmeyecek satış işlemi olduysa 1 print ediyor.

        for (int i = 0; i < requiredMana.size(); i++)
        {
            cout << requiredMana[i];
        }
        cout << endl;

    }

    bool payMana(vector<int> manaCost) { //Vektörü alıp paramız yetiyor mu diye kontrol ediyor.
        vector<int> manaAfterPayment;
        setVectorSize(&manaAfterPayment);
        bool status = true;
        for (int i = 0; i < 6; i++) {
            if (manaCount[i] < manaCost[i]) {
                if (i == 5) {
                    int totalManaToUse = 0;
                    bool possibleToBuy = false;
                    for (int x = 0; x < 5; x++) {
                        if (totalManaToUse + manaAfterPayment[x] >= manaCost[i]) {
                            manaAfterPayment[x] = manaCost[i] - totalManaToUse;
                            possibleToBuy = true;
                        }
                        else {
                            totalManaToUse += manaAfterPayment[x];
                            manaAfterPayment[x] = 0;
                        }
                    }
                    if (!possibleToBuy) {
                        status = false;
                    }
                }
                else {
                    status = false;
                }
            }
            else {
                manaAfterPayment[i] = (manaCount[i] - manaCost[i]);
            }
        }

        if (status == true) {
            for (int i = 0; i < manaAfterPayment.size(); i++) {
                manaCount[i] = manaAfterPayment[i];
            }
        }
        return status;
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
        for (int i = 0; i < inPlay.size(); i++)
        {
            (inPlay[i])->printInfo();
            cout << '\t';
            cout << "index: " << i << '\t';
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

    void printLibrary()
    {
        //cout << "CARDS IN LIBRARY: " << endl;
        for (int i = 0; i < library.size(); i++)
        {
            cout << "index: " << i << '\t';
            (library[i])->printInfo();
            cout << endl;
        }
    }

    shared_ptr<Card> getAndPrintLibraryVector(){
        cout << "Please enter an index number to draw a card." << endl;
        for (int i = 0; i < library.size(); i++)
        {
            cout << "Index:" << i << " " << library[i]->getName() << " ";
        }
        int selection=-1;
        while(selection<0||selection>=library.size()){
            cout << "Please enter a valid number" << endl;
            cin >> selection;
        }
        return library[selection];
    }

    void activateAbility(int a)
    {

        inPlay[a]->Play();

    }

    void playItemAtHand(int a) {

        if (hand[a]->getType() == "Sorcery")
        {
            hand[a]->Play();
            addCardToDiscard(hand[a]);
        }
        else
        {
            addCardToinPlay(hand[a]);
        }
    }

    void HealAllCreatures()
    {//Her turn başında creatureların canlarını fullemek için
        for (int i = 0; i < inPlay.size(); i++)
        {
            if (inPlay[i]->getType() == "Creature")
            {
                inPlay[i]->setHp(inPlay[i]->getMaxHP());
            }

        }
    }

};

void selectRandomCardsFromLibraryToPutIntoHand(std::shared_ptr<Player> p1) {
    vector<int> possibleCards;
    const int elementCount = p1->getLibraryElementCount();
    for (int i = 0; i < p1->getLibraryElementCount(); i++) {
        possibleCards.push_back(i);
    }
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        int key = rand() % elementCount;
        p1->addCardToHandByInt(key + 1);
    }
}

class Effect {

};

class LandCard : public Card {
protected:
    string mana;
    bool isTapped;
    std::shared_ptr<Player> p1;
    bool isPlayed;

public:
    LandCard(string name, string type, string mana, std::shared_ptr<Player> p1) :Card(name, type)
    {
        this->mana = mana;
        isTapped = false;
        this->p1 = p1;
        isPlayed = true;
    }
    LandCard() :Card()
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

    void Untap()
    {
        isTapped = false;
        p1->SetManaToZero();
    }

    void Play()
    {   //player classında activate ile çağrılıyor.
        Tap();
        isPlayed = true;
        p1->setManaVector(getMana());

    }

    bool getStatus()
    {
        return isTapped;
    }

    string getType()
    {
        return type;
    }

    string getMana()
    {
        return mana;
    }

    bool isAlreadyPlayed()
    {
        return isPlayed;
    }
};

class CreatureCard : public Card {
protected:
    int attackPower;
    int maxHP;
    int hp;
    bool hasFirstStrike;
    bool hasTrample;
    string manaCost;
    string color;
    bool isTapped;
    bool isDestroyed;
    std::shared_ptr<Player> p1;
public:

    CreatureCard() :Card() {
        attackPower = 0;
        manaCost = "null cost";
        color = "no color";
        hp = 0;
        maxHP = hp;
        isTapped = false;
        isDestroyed = false;
    }

    CreatureCard(string name, string type, int attackPower, string manaCost, string color, int hp, std::shared_ptr<Player> p1) :Card(name, type)
    {
        this->attackPower = attackPower;
        this->manaCost = manaCost;
        this->color = color;
        this->hp = hp;
        maxHP = hp;
        isTapped = false;
        isDestroyed = false;
        this->p1 = p1;

        if (name == "Angry Bear"||name=="Werewolf")
        {
            hasTrample = true;
            hasFirstStrike = false;
        }

        else if (name == "White Knight" || name == "Black Knight")
        {
            hasFirstStrike = true;
            hasTrample = false;
        }
    }

    int getHp()
    {
        return hp;
    }

    int getMaxHP()
    {
        return maxHP;
    }

    int getAttackPower()
    {
        return attackPower;
    }

    bool isDead()
    {
        if (hp <= 0)
        {
            isDestroyed = true;
        }
        else
        {
            isDestroyed = false;
        }

        return isDestroyed;
    }


    void setHp(int a)
    {
        hp = a;
    }

    void Tap()
    {
        isTapped = true;
    }
    void Play()
    {
          //  attack() gibi bir şey olacak.
    }

    void printInfo()
    {
        cout << name << " " << type << " " << attackPower << " " << manaCost << " " << color << " " << hp;
    }

    string getType()
    {
        return type;
    }
    string getManaCost()
    {
        return manaCost;
    }
    string getColor()
    {
        return color;
    }

   bool getHasFirstStrike()
    {
       return hasFirstStrike;
    }

   bool getHasTrample()
   {
       return hasTrample;
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

    EnchantmentCard(string name, string type, string manaCost, string color, std::shared_ptr<Player> p1, Effect& effect) :Card(name, type)
    {

        this->manaCost = manaCost;
        this->color = color;
        this->effect = effect;
        this->p1 = p1;

    }

    void ActivateEnchantment()
    {
        //Effect'i her neyse buraya girilecek.
    }

    void Play()
    {
        ActivateEnchantment();

    }

    string getType()
    {
        return type;
    }

    string getManaCost()
    {
        return manaCost;
    }

    void printInfo()
    {
        cout << name << " " << type << " " << manaCost << " " << color;
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
        //activate ability. effect falan
        cout << "sorcery is played" << endl;
    }

    string getType()
    {
        return type;
    }

    string getManaCost()
    {
        return manaCost;
    }
    void printInfo()
    {
        cout << name << " " << type << " " << manaCost << " " << color;
    }

};
int turn = 0;
shared_ptr<Player> p1, p2;
bool isGameFinished = false;
void turnLoop() {
    shared_ptr<Player> ourPlayer;
    if(turn==0){
        ourPlayer = p1;
    } else if(turn==1){
        ourPlayer = p2;
    }
    //Draw
    shared_ptr<Card> selection;
    cout <<ourPlayer->getHandElementCount() << endl;
    if(ourPlayer->getHandElementCount()<7){
        selection = (ourPlayer->getAndPrintLibraryVector());
        ourPlayer->drawCard(selection);
    } else {
        //Lose The Game
        isGameFinished = true;
    }

    //Untap
    ourPlayer->untapAllinPlay();

    //Play



}

void createDecks(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
    Effect effect;
    shared_ptr<Player> player1;
    shared_ptr<Player> player2;
    player1 = p1;
    player2 = p2;

    ////Creature Cards
    shared_ptr<Card>C1 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1, player1);
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
    shared_ptr<Card>C11 = make_shared<SorceryCard>("Disenchant", "Sorcery", "White", "1W", player1, effect);
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
    C1 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1, player2);
    C2 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1, player2);
    C3 = make_shared<CreatureCard>("Soldier", "Creature", 1, "W", "White", 1, player2);
    C4 = make_shared<CreatureCard>("Armored Pegasus", "Creature", 1, "1W", "White", 2, player2);
    C5 = make_shared<CreatureCard>("Armored Pegasus", "Creature", 1, "1W", "White", 2, player2);
    C6 = make_shared<CreatureCard>("White Knight", "Creature", 2, "WW", "White", 2, player2);
    C7 = make_shared<CreatureCard>("White Knight", "Creature", 2, "WW", "White", 2, player2);
    C8 = make_shared<CreatureCard>("Angry Bear", "Creature", 3, "2G", "Green", 2, player2);
    C9 = make_shared<CreatureCard>("Guard", "Creature", 2, "2WW", "White", 5, player2);
    C10 = make_shared<CreatureCard>("Werewolf", "Creature", 4, "2GW", "Green", 6, player2);

    //Sorcery Cards
    C11 = make_shared<SorceryCard>("Reanimate", "Sorcery", "Black", "B", player2, effect);
    C12 = make_shared<SorceryCard>("Plague", "Sorcery", "Black", "2B", player2, effect);
    C13 = make_shared<SorceryCard>("Terror", "Sorcery", "Black", "1B", player2, effect);
    C14 = make_shared<SorceryCard>("Terror", "Sorcery", "Black", "1B", player2, effect);

    //Enchantment Card
    C15 = make_shared<EnchantmentCard>("Unholy War", "Land", "Black", "1B", player2, effect);
    C16 = make_shared<EnchantmentCard>("Restrain", "Enchantment", "Red", "2R", player2, effect);
    C17 = make_shared<EnchantmentCard>("Slow", "Enchantment", "Black", "B", player2, effect);

    //Land Card
    C18 = make_shared<LandCard>("Swamp", "Land", "B", player2);
    C19 = make_shared<LandCard>("Swamp", "Land", "B", player2);
    C20 = make_shared<LandCard>("Swamp", "Land", "B", player2);
    C21 = make_shared<LandCard>("Swamp", "Land", "B", player2);
    C22 = make_shared<LandCard>("Swamp", "Land", "B", player2);
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


void combat(shared_ptr<Card> attackingCreature, shared_ptr<Player>& attakingPlayer, shared_ptr<Card> defendingCreature, shared_ptr<Player >& defendingPlayer)
{

    if (defendingCreature == nullptr)
    {
        //DEFENDER YOK ISE
        defendingPlayer->setHp(defendingPlayer->getHp() - attackingCreature->getAttackPower());

        cout << "DEFENDING PLAYER HAS " << defendingPlayer->getHp() << "HP LEFT." << endl;
    }

    else if (attackingCreature->getHasFirstStrike() == true && defendingCreature->getHasFirstStrike() == true)
    {   //İKİSİNDE DE FIRST STRIKE VARSA NORMAL COMBAT
        defendingCreature->setHp(defendingCreature->getHp() - attackingCreature->getAttackPower());

        attackingCreature->setHp(attackingCreature->getHp() - defendingCreature->getAttackPower());

        cout << "ATTACKING CREATURE HAS : " << attackingCreature->getHp() << "HP LEFT." << endl;
        cout << "DEFENDING CREATURE HAS : " << defendingCreature->getHp() << "HP LEFT." << endl;

        if (defendingCreature->isDead())
        {
            cout << "DEFENDING CREATURE HAS DIED." << endl;
            defendingPlayer->addCardToDiscard(defendingCreature);
        }

        if (attackingCreature->isDead())
        {
            cout << "ATTACKING CREATURE HAS DIED." << endl;

            attakingPlayer->addCardToDiscard(attackingCreature);
        }

    }


    else if (attackingCreature->getHasFirstStrike() == true)
    {
        defendingCreature->setHp(defendingCreature->getHp() - attackingCreature->getAttackPower());
        cout << "DEFENDING CREATURE HAS : " << defendingCreature->getHp() << "HP LEFT." << endl;

        if (defendingCreature->isDead())
        {
            cout << "DEFENDING CREATURE HAS DIED." << endl;
            defendingPlayer->addCardToDiscard(defendingCreature);
        }

        else
        {
            attackingCreature->setHp(attackingCreature->getHp() - defendingCreature->getAttackPower());
            cout << "ATTACKING CREATURE HAS : " << attackingCreature->getHp() << "HP LEFT." << endl;

            if (attackingCreature->isDead())
            {
                cout << "ATTACKING CREATURE HAS DIED." << endl;
                attakingPlayer->addCardToDiscard(attackingCreature);
            }

        }

    }
    else if (defendingCreature->getHasFirstStrike() == true)
    {
        //defending'de first strike varsa.
        attackingCreature->setHp(attackingCreature->getHp() - defendingCreature->getAttackPower());

        if (attackingCreature->isDead())
        {
            cout << "ATTACKING CREATURE HAS DIED." << endl;
            attakingPlayer->addCardToDiscard(attackingCreature);
        }

        else
        {
            defendingCreature->setHp(defendingCreature->getHp() - attackingCreature->getAttackPower());

            if (defendingCreature->isDead())
            {
                cout << "DEFENDING CREATURE HAS DIED." << endl;
                defendingPlayer->addCardToDiscard(defendingCreature);
            }

        }

    }


    else if (attackingCreature->getHasTrample() == true)
    {
        //attacking'de trample varsa.

        int excess_damage;

        excess_damage = attackingCreature->getAttackPower() - defendingCreature->getHp();

        defendingCreature->setHp(defendingCreature->getHp() - attackingCreature->getAttackPower());
        attackingCreature->setHp(attackingCreature->getHp() - defendingCreature->getAttackPower());

        if (defendingCreature->isDead())
        {
            cout << "DEFENDING CREATURE HAS DIED." << endl;
            defendingPlayer->addCardToDiscard(defendingCreature);
        }

        if (attackingCreature->isDead())
        {
            cout << "ATTACKING CREATURE HAS DIED." << endl;

            attakingPlayer->addCardToDiscard(attackingCreature);
        }

        defendingPlayer->setHp(defendingPlayer->getHp() - excess_damage);
    }

    else {
        //ikisi de normal creature'lar ise
        defendingCreature->setHp(defendingCreature->getHp() - attackingCreature->getAttackPower());

        attackingCreature->setHp(attackingCreature->getHp() - defendingCreature->getAttackPower());

        cout <<"ATTACKING CREATURE HAS : "<< attackingCreature->getHp() <<"HP LEFT." <<endl;
        cout << "DEFENDING CREATURE HAS : " << attackingCreature->getHp() << "HP LEFT." << endl;
        if (defendingCreature->isDead())
        {
            cout << "DEFENDING CREATURE HAS DIED." << endl;
            defendingPlayer->addCardToDiscard(defendingCreature);
        }

        if (attackingCreature->isDead())
        {
            cout << "ATTACKING CREATURE HAS DIED." << endl;

            attakingPlayer->addCardToDiscard(attackingCreature);
        }

    }

}


void playGame() {

    while (!isGameFinished) {
        turnLoop();
        turn = (turn == 0) ? turn = 1 : turn = 0;
        isGameFinished = true;

    }
}

void setupGame() {
    p1 = make_shared<Player>();
    p2 = make_shared<Player>();

    createDecks(p1, p2);

    selectRandomCardsFromLibraryToPutIntoHand(p1);
    selectRandomCardsFromLibraryToPutIntoHand(p2);

    //trample
    //p1->drawCard(p1->library[0]);
    //p2->drawCard(p2->library[7]);

    //firststrike
    //p1->drawCard(p1->library[7]);
    //p2->drawCard(p2->library[5]);

    //p1->drawCard(p1->library[8]);
    //p2->drawCard(p2->library[5]);

    //p2->drawCard(p2->library[5]);
    //p1->drawCard(p1->library[6]);


    cout << "p2 hand:" << endl;
    p2->printHand();

    cout << "p1 hand:" << endl;
    p1->printHand();

   // combat(p2->library[5], p2, NULL, p1);
    //combat(p2->hand[0], p2, p1->hand[0], p1);

    //cout << endl;




    //cout << "discard pile of p1: " << endl;
    //p1->printDiscard();

    //cout << "discard pile of p2: " << endl;
    //p2->printDiscard();


    //cout <<"p1 remaining health: ";
    //cout << p1->getHp() << endl;

    //cout << "p2 remaining health: ";
    //cout << p2->getHp() << endl;


    //p1->printManaVector();
    //
    //p1->activateAbility(0);
    //p1->activateAbility(1);
    //p1->activateAbility(2);


    //p1->printManaVector();

    //p1->checkManaCost("1WW");
    //p1->untapAllinPlay();

    //cout << endl;
    //p1->printManaVector();
    //p1->checkManaCost("1WW");

    playGame();
}
int main() {
    setupGame();

    return 0;
}