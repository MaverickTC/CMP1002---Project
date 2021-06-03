#include <iostream>
#include <vector>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


using namespace std;



class Card {
protected:
    string name;
    string type;
    bool isTapped;
    bool isDestroyed;
    int hp;
    int maxHP;
    bool hasFirstStrike;
    bool hasTrample;
    string color;
public:
    Card()
    {
        name = "no name";
        type = "null type";
        isTapped = false;
        isDestroyed = false;
    }

    Card(string name, string type)
    {
        this->name = name;
        this->type = type;
        isTapped = false;
        isDestroyed = false;
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

    void destroyCard() {
        isDestroyed = true;
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

    virtual int getMaxAttack()
    {
        return 1;
    }

    virtual void setHp(int a)
    {

    }

    virtual void setAttack(int a)
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

    virtual void setFirstStrike(bool a)
    {

    }
    virtual void setTrample(bool a)
    {

    }

    virtual bool getHasTrample()
    {
        return hasTrample;
    }
    virtual string getColor()
    {
        return color;
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
        for (int i = 0; i < 5; i++)
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

    void addCardToDeck(shared_ptr<Card>& C1) {
        library.push_back(C1);
    }

    void drawCard(shared_ptr<Card>& C1) {
        if (find(library.begin(), library.end(), C1) != library.end()) {
            hand.push_back(C1);
            library.erase(remove(library.begin(), library.end(), C1), library.end());
        }
    }
    void addCardToinPlay(int a)
    {
        inPlay.push_back(hand[a]);
        hand.erase(hand.begin() + a);
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

    void addCardToPlaybyCard(shared_ptr<Card>& C1)
    {
        if (find(hand.begin(), hand.end(), C1) != hand.end()) {
            inPlay.push_back(C1);
            hand.erase(remove(hand.begin(), hand.end(), C1), hand.end());

        }
        else if (find(discard.begin(), discard.end(), C1) != discard.end()) {
            inPlay.push_back(C1);
            discard.erase(remove(discard.begin(), discard.end(), C1), discard.end());

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



    shared_ptr<Card> getAndPrintLibraryVector() {
        for (int i = 0; i < library.size(); i++)
        {
            cout << BOLDRED << "Index:" << i << " " << RESET << library[i]->getName() << " ";
        }
        cout << endl;
        int selection = -1;
        while (selection < 0 || selection >= library.size()) {
            cout << BOLDMAGENTA << "Please enter a valid index number to draw a card." << RESET << endl;
            cin >> selection;
        }
        return library[selection];
    }

    shared_ptr<Card> getAndPrintHandVector(bool isLand) {
        int i = 0, number = 0;
        vector<shared_ptr<Card>> cards;

        while (i < hand.size())
        {
            if (isLand) {
                if (hand[i]->getType() == "Land") {
                    cout << BOLDRED << "Index:" << number << " " << RESET << hand[i]->getName() << " " << endl;
                    cards.push_back(hand[i]);
                    number++;
                }
            }
            else {
                if (hand[i]->getType() != "Land") {
                    cout << BOLDRED << "Index:" << number << " " << RESET << hand[i]->getName() << " " << endl;
                    cards.push_back(hand[i]);
                    number++;
                }
            }

            i++;
        }

        int selection = -1;
        string str = "";
        bool stop = false;
        str = (isLand) ? str = " land " : " non land ";
        while (selection < 0 || selection >= cards.size()) {
            cout << BOLDMAGENTA << "Please enter an index number to play" << str << "card or enter -1 to skip" << RESET << endl;
            cin >> selection;
            if (selection == -1) {
                stop = true;
                selection = 0; //Daha iyi bir yol bulunabilir.
                break;
            }
        }
        if (stop && !isLand) {
            return nullptr;
        }
        else {
            return cards[selection];
        }
    }



    void tapSelectedLandCards() {
        vector<shared_ptr<Card>> landCards;
        //cout << hand.size() << endl;
        int i = 0, number = 0;

        while (i < inPlay.size())
        {
            if (inPlay[i]->getType() == "Land") {
                cout << BOLDRED << "Index:" << number << " " << RESET << inPlay[i]->getName() << " " << endl;
                landCards.push_back(inPlay[i]);
                number++;
            }
            i++;
        }
        int selection = -1;
        while ((selection >= 0 && selection < landCards.size()) || selection == -1) {
            cout << BOLDMAGENTA << "Please enter an index number to tap card or enter -1 to skip." << RESET << endl;
            cin >> selection;
            if ((selection >= 0 && selection < landCards.size())) {
                landCards[selection]->Tap();
            }
            else {
                return;
            }
        }
    }

    void activateAbility(int a)
    {

        inPlay[a]->Play();

    }

    void playItemAtHand(shared_ptr<Card>& C1)
    {
        auto it = find(hand.begin(), hand.end(), C1);

        if (it != hand.end())
        {
            int index = it - hand.begin();

            if (hand[index]->getType() == "Sorcery")
            {
                hand[index]->Play();
                addCardToDiscard(hand[index]);
            }
            else
            {
                addCardToinPlay(index);
            }
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

    for (int i = 0; i < p1->getLibraryElementCount(); i++) {
        possibleCards.push_back(i);
    }
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        int key = rand() % p1->getLibraryElementCount();

        p1->addCardToHandByInt(key);
    }
}

int turn = 0;
shared_ptr<Player> p1, p2;

class Effect {
    virtual void use(shared_ptr<Card>& C) = 0;
};

class DestroyEffect : public Effect {
public:
    void use(shared_ptr<Card>&C) {
       
        shared_ptr<Player> targetPlayer;
        vector<shared_ptr<Card>> cards;
        if (turn == 0) {
            targetPlayer = p2;
        }
        else {
            targetPlayer = p1;
        }
        if (targetPlayer->inPlay.size() < 1) {
            return;  //Eğer inPlay boşsa soruya gerek yok.
        }

        if (C->getName() == "Disenchant")
        {
            //target enchantment
            for (int i = 0; i < targetPlayer->inPlay.size(); i++)
            {
                if (targetPlayer->inPlay[i]->getType() == "Enchantment") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    targetPlayer->inPlay[i]->printInfo();
                    cards.push_back(targetPlayer->inPlay[i]);
                }
            }

            int selectionIndex;
            cout << "Please enter enchantment index of which you want to destroy." << endl;
            //burada ve alttaki effectlerde cards printlenebilir.
            cin >> selectionIndex;

            if (selectionIndex >= 0 && selectionIndex < cards.size()) {
                cards[selectionIndex]->destroyCard();
                targetPlayer->addCardToDiscard(cards[selectionIndex]);
            }
            else {
                return; //"please enter a valid index?"
            }
            cards.empty();
        }
        
        else if (C->getName() == "Flood")
        {
            //target land
              
            for (int i = 0; i < targetPlayer->inPlay.size(); i++)
            {
                if (targetPlayer->inPlay[i]->getType() == "Land") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    targetPlayer->inPlay[i]->printInfo();
                    cards.push_back(targetPlayer->inPlay[i]);
                }
            }
            int selectionIndex;
            cout << "Please enter land index of which you want to destroy." << endl;
            cin >> selectionIndex;

            if (selectionIndex >= 0 && selectionIndex < cards.size()) {
                cards[selectionIndex]->destroyCard();
                targetPlayer->addCardToDiscard(cards[selectionIndex]);
            }
            else {
                return; //"please enter a valid index?"
            }
            cards.empty();
        }
        
        else if (C->getName() == "Terror")
        {
            //target Creature
            for (int i = 0; i < targetPlayer->inPlay.size(); i++)
            {
                if (targetPlayer->inPlay[i]->getType() == "Creature") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    targetPlayer->inPlay[i]->printInfo();
                    cards.push_back(targetPlayer->inPlay[i]);
                }
            }
            int selectionIndex;
            cout << "Please enter creature index of which you want to destroy." << endl;
            cin >> selectionIndex;
            if (selectionIndex >= 0 && selectionIndex < cards.size()) {
                cards[selectionIndex]->destroyCard();
                targetPlayer->addCardToDiscard(cards[selectionIndex]);
            }
            else {
                return; //"please enter a valid index?"
            }
            cards.empty();
        }
        
    }
};

    class DealDamageEffect : public Effect {
public: 
    void use(shared_ptr<Card>& C) {
           
        shared_ptr<Player> targetPlayer;
        vector<shared_ptr<Card>> cards;
        if (turn == 0) {
            targetPlayer = p2;
        }
        else {
            targetPlayer = p1;
        }
        if (targetPlayer->inPlay.size() < 1) {
            return;
        }
        string selection;
        cout << "Do you want to deal damage to the player or the creature? (C / P) ";
        cin >> selection;

        if (selection == "C" || selection == "c")
        {
            for (int i = 0; i < targetPlayer->inPlay.size(); i++)
            {
                if (targetPlayer->inPlay[i]->getType() == "Creature") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    targetPlayer->inPlay[i]->printInfo();
                    cards.push_back(targetPlayer->inPlay[i]);

                }
            }
            int damageIndex;
            cout << BOLDMAGENTA << "Please enter an index number of creature to deal 2 damage." << RESET << endl;
            cin >> damageIndex;

            if (damageIndex >= 0 && damageIndex < cards.size()) 
            {
                cards[damageIndex]->setHp(cards[damageIndex]->getHp() - 2);
                  if (cards[damageIndex]->isDead() == true)
                    {
                        targetPlayer->addCardToDiscard(cards[damageIndex]);
                    }
                    else {
                        return;
                    }
            }
        }

        else if (selection == "P" || selection == "p")
        {
            targetPlayer->setHp(targetPlayer->getHp() - 2);
        }

        else {
            cout << "please enter valid index" << endl; //error den sonra bişey yapmak gerek.
        }
     }
 };

    class DealDamageToAllEffect : public Effect
    {
    public :void use(shared_ptr<Card>& C) {
            
            vector<shared_ptr<Card>> p1cards;
            vector<shared_ptr<Card>> p2cards;

            //p1 creatures
            for (int i = 0; i < p1->inPlay.size(); i++)
            {
                if (p1->inPlay[i]->getType() == "Creature") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    p1->inPlay[i]->printInfo();
                    p1cards.push_back(p1->inPlay[i]);

                }
            }

            for (int i = 0; i < p1cards.size(); i++)
            {
                p1cards[i]->setHp(p1cards[i]->getHp() - 1);
                if (p1cards[i]->isDead() == true)
                {
                    p1->addCardToDiscard(p1cards[i]);
                }
            }
            p1cards.empty();

            //p2 creatures
            for (int i = 0; i < p2->inPlay.size(); i++)
            {
                if (p2->inPlay[i]->getType() == "Creature") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    p2->inPlay[i]->printInfo();
                    p2cards.push_back(p2->inPlay[i]);
                }
            }
            for (int i = 0; i < p2cards.size(); i++)
            {
                p2cards[i]->setHp(p2cards[i]->getHp() - 1);
                if (p2cards[i]->isDead() == true)
                {
                    p2->addCardToDiscard(p2cards[i]);
                }
            }
            p2cards.empty();

        }

    };

    class GainStatsEffect : public Effect {
    public: void use(shared_ptr<Card>& C) {

        vector<shared_ptr<Card>> cardsP1;
        vector<shared_ptr<Card>> cardsP2;

        cardsP1.empty();
        cardsP2.empty();
        //HOLY WAR
        if (C->getName() == "Holy War")
        {
            
            //p1 whites
            for (int i = 0; i < p1->inPlay.size(); i++)
            {
                if (p1->inPlay[i]->getType() == "Creature" && p1->inPlay[i]->getColor() == "White") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    p1->inPlay[i]->printInfo();
                    cardsP1.push_back(p1->inPlay[i]);
                }
            }
            for (int i = 0; i < cardsP1.size(); i++)
            {
                cardsP1[i]->setHp(cardsP1[i]->getHp() + 1);
                cardsP1[i]->setAttack(cardsP1[i]->getAttackPower() + 1);
            }
            cardsP1.empty();
             //p2 whites
            for (int i = 0; i < p2->inPlay.size(); i++)
            {
                if (p2->inPlay[i]->getType() == "Creature" && p2->inPlay[i]->getColor() == "White") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    p2->inPlay[i]->printInfo();
                    cardsP2.push_back(p2->inPlay[i]);
                }
            }
            for (int i = 0; i < cardsP2.size(); i++)
            {
                cardsP2[i]->setHp(cardsP2[i]->getHp() + 1);
                cardsP2[i]->setAttack(cardsP2[i]->getAttackPower() + 1);
             }
            cardsP2.empty();
        }
        //UNHOLY WAR
        else if (C->getName() == "Unholy War")
        {
            ////p1 blacks
             for (int i = 0; i < p1->inPlay.size(); i++)
             {
                if (p1->inPlay[i]->getType() == "Creature" && p1->inPlay[i]->getColor() == "Black") {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                p1->inPlay[i]->printInfo();
                cardsP1.push_back(p1->inPlay[i]);
                 }
             }
            for (int i = 0; i < cardsP1.size(); i++)
            {
                 cardsP1[i]->setAttack(cardsP1[i]->getAttackPower() + 2);
            }
            cardsP1.empty();

            //p2 blacks
            for (int i = 0; i < p2->inPlay.size(); i++)
            {
                if (p2->inPlay[i]->getType() == "Creature" && p2->inPlay[i]->getColor() == "Black") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    p2->inPlay[i]->printInfo();
                    cardsP2.push_back(p2->inPlay[i]);
                }
            }
            for (int i = 0; i < cardsP2.size(); i++)
            {
            cardsP2[i]->setAttack(cardsP2[i]->getAttackPower() + 2);
            }
            cardsP2.empty();

        }
        ///HOLY LIGHT
        else if (C->getName() == "Holy Light")
        {
            ////p1 blacks
            for (int i = 0; i < p1->inPlay.size(); i++)
            {
                if (p1->inPlay[i]->getType() == "Creature" && p1->inPlay[i]->getColor() == "Black") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    p1->inPlay[i]->printInfo();
                    cardsP1.push_back(p1->inPlay[i]);
                }
            }
            for (int i = 0; i < cardsP1.size(); i++)
            {
                cardsP1[i]->setAttack(cardsP1[i]->getAttackPower() -1);
                cardsP1[i]->setAttack(cardsP1[i]->getAttackPower() -1);
                if (cardsP1[i]->isDead() == true)
                {
                    p1->addCardToDiscard(cardsP1[i]);
                }
            }
            cardsP1.empty();

            //p2 blacks
            for (int i = 0; i < p2->inPlay.size(); i++)
            {
                if (p2->inPlay[i]->getType() == "Creature" && p2->inPlay[i]->getColor() == "Black") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    p2->inPlay[i]->printInfo();
                    cardsP2.push_back(p2->inPlay[i]);
                }
            }
            for (int i = 0; i < cardsP2.size(); i++)
            {
                cardsP2[i]->setAttack(cardsP2[i]->getAttackPower() -1);
                cardsP2[i]->setAttack(cardsP2[i]->getAttackPower() -1);
                if (cardsP2[i]->isDead() == true)
                {
                    p2->addCardToDiscard(cardsP2[i]);
                }
            }
            cardsP2.empty();

        }

    }

    };

    class ReturnCreatureToLifeEffect : public Effect {
    public: void use(shared_ptr<Card>& C) {
            
            shared_ptr<Player> targetPlayer;
            vector<shared_ptr<Card>> cards;

            if (turn == 0) {
                targetPlayer = p1;
            }
            else {
                targetPlayer = p2;
            }
            
            for (int i = 0; i < p1->discard.size(); i++)
            {
                if (targetPlayer->discard[i]->getType() == "Creature" ) {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    p1->discard[i]->printInfo();
                    cards.push_back(p1->discard[i]);
                }
            }

            int selectionIndex;
            cout << "Please enter an index of a creature to return it back to life.";
            cin >> selectionIndex;

            if (selectionIndex >= 0 && selectionIndex < cards.size()) {
                cards[selectionIndex]->setAttack(cards[selectionIndex]->getMaxAttack());
                cards[selectionIndex]->setHp(cards[selectionIndex]->getMaxHP());
                targetPlayer->addCardToPlaybyCard(cards[selectionIndex]);
            }
            else {
                return; //please enter a valid index?
            }
        }

    };

    class GainTrampleEffect : public Effect {
    public: void use(shared_ptr<Card>& C) {
        shared_ptr<Player> targetPlayer;
        vector<shared_ptr<Card>> cards;

        if (turn == 0) {
            targetPlayer = p1;
        }
        else {
            targetPlayer = p2;
        }
        if (targetPlayer->inPlay.size() < 1) {//////////////////??
            return;
        }

        for (int i = 0; i < targetPlayer->inPlay.size(); i++)
        {
            if (targetPlayer->inPlay[i]->getType() == "Creature" && targetPlayer->inPlay[i]->getHasTrample() == false) {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                targetPlayer->inPlay[i]->printInfo();
                cards.push_back(targetPlayer->inPlay[i]);
            }
        }

        int selectionIndex;
        cout << "Please enter creature index of which you want to add trample." << endl;
        cin >> selectionIndex;

        if (selectionIndex >= 0 && selectionIndex < cards.size()) {
            cards[selectionIndex]->setTrample(true);
        }
        else {
            return; //"please enter a valid index?"
        }
    }


    };                              

    class LoseGreenTrampleEffect : public Effect {
        //bunu sadece green için yap.
    public: void use(shared_ptr<Card>& C) {
        shared_ptr<Player> targetPlayer;
        vector<shared_ptr<Card>> cards;

        if (turn == 0) {
            targetPlayer = p2;
        }
        else {
            targetPlayer = p1;
        }
        if (targetPlayer->inPlay.size() < 1) {//////////////////??
            return;
        }

        for (int i = 0; i < targetPlayer->inPlay.size(); i++)
        {
            if (targetPlayer->inPlay[i]->getType() == "Creature" && targetPlayer->inPlay[i]->getHasTrample() == true && targetPlayer->inPlay[i]->getColor()=="Green") {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                targetPlayer->inPlay[i]->printInfo();
                cards.push_back(targetPlayer->inPlay[i]);
            }
            else {
                return; //? başka adıma mı atlanmalı
            }
        }

        int selectionIndex;
        cout << "Please enter creature index of which you want to remove its trample." << endl;
        cin >> selectionIndex;

        if (selectionIndex >= 0 && selectionIndex < cards.size()) {
            cards[selectionIndex]->setTrample(false);
        }
        else {
            return; //"please enter a valid index?"
        }
    }

    };                          

    class LoseFirstStrikeEffect : public Effect {

public: void use(shared_ptr<Card>& C) {
            shared_ptr<Player> targetPlayer;
            vector<shared_ptr<Card>> cards;

            if (turn == 0) {
                targetPlayer = p2;
            }
            else {
                targetPlayer = p1;
            }
            if (targetPlayer->inPlay.size() < 1) {//////////////////??
                return;
            }

            for (int i = 0; i < targetPlayer->inPlay.size(); i++)
            {
                if (targetPlayer->inPlay[i]->getType() == "Creature"&& targetPlayer->inPlay[i]->getHasFirstStrike() == true) {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    targetPlayer->inPlay[i]->printInfo();
                    cards.push_back(targetPlayer->inPlay[i]);
                }
            }

            int selectionIndex;
            cout << "Please enter creature index of which you want to remove its first strike." << endl;
            cin >> selectionIndex;

            if (selectionIndex >= 0 && selectionIndex < cards.size()) {
                cards[selectionIndex]->setFirstStrike(false);
            }
            else {
                return; //"please enter a valid index?"
            }
        }
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
        int maxAttack;
        int hp;
        bool hasFirstStrike;
        bool hasTrample;
        string manaCost;
        string color;
        bool isTapped;
        std::shared_ptr<Player> p1;
    public:

        CreatureCard() :Card() {
            attackPower = 0;
            manaCost = "null cost";
            color = "no color";
            hp = 0;
            maxHP = hp;
            maxAttack = attackPower;
            isTapped = false;
        }

        CreatureCard(string name, string type, int attackPower, string manaCost, string color, int hp, std::shared_ptr<Player> p1) :Card(name, type)
        {
            this->attackPower = attackPower;
            this->manaCost = manaCost;
            this->color = color;
            this->hp = hp;
            maxHP = hp;
            maxAttack = attackPower;
            isTapped = false;
            this->p1 = p1;

            if (name == "Angry Bear" || name == "Werewolf")
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

       int getMaxAttack()
        {
            return maxAttack;
        }

        int getAttackPower()
        {
            return attackPower;
        }


        void setHp(int a)
        {
            hp = a;
        }

        void setAttack(int a)
        {
            attackPower = a;
        }

        void Tap()
        {
            isTapped = true;
        }
        void Play()
        {

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

         void setFirstStrike(bool a)
        {
             hasFirstStrike = a;
        }
         void setTrample(bool a)
        {
             hasTrample = a;
        }

    };

    class EnchantmentCard : public Card {
    protected:
        string manaCost;
        string color;
        Effect* effect;
        std::shared_ptr<Player> p1;
    public:

        EnchantmentCard() :Card()
        {
            manaCost = "no cost";
            color = "no color";
        }

        EnchantmentCard(string name, string type, string manaCost, string color, std::shared_ptr<Player> p1, Effect* effect) :Card(name, type)
        {

            this->manaCost = manaCost;
            this->effect = effect;
            this->color = color;
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
        Effect* effect;
    public:
        std::shared_ptr<Player> p1;
        SorceryCard(string name, string type, string manaCost, string color, shared_ptr<Player> p1, Effect* effect) :Card(name, type)
        {

            this->manaCost = manaCost;
            this->effect = effect;
            this->color = color;
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

    bool isGameFinished = false;
    void turnLoop() {
        shared_ptr<Player> ourPlayer;
        if (turn == 0) {
            cout << BLUE << "--- It is a turn of player " << BOLDBLUE << "1 ---" << RESET << endl;
            ourPlayer = p1;
        }
        else if (turn == 1) {
            cout << BLUE << "--- It is a turn of player " << BOLDBLUE << "2 ---" << RESET << endl;
            ourPlayer = p2;
        }

        ////Draw
        cout << GREEN << "Draw Phase" << RESET << endl;
        shared_ptr<Card> selection;

        //cout <<ourPlayer->getHandElementCount() << endl;

        if (ourPlayer->getLibraryElementCount() > 0) {
            if (ourPlayer->getHandElementCount() < 7) {
                selection = (ourPlayer->getAndPrintLibraryVector());
                ourPlayer->drawCard(selection);
            }
            else {

            }
        }
        else {
            //Lose The Game
            isGameFinished = true;
        }

        ////Untap
        ourPlayer->untapAllinPlay();

        ////Play
        bool isPlayedLandCard = false;
        cout << BOLDMAGENTA << "Do you want to play a land card? " << BOLDBLUE << "(Y/N)" << RESET << endl;
        string answer;
        cin >> answer;

        if (answer == "Y" || answer == "y") {
            selection = (ourPlayer->getAndPrintHandVector(true));
            ourPlayer->playItemAtHand(selection);
            isPlayedLandCard = true;
        }

        bool stop = false;
        while (!stop) {
            selection = (ourPlayer->getAndPrintHandVector(false));
            if (selection == nullptr) {
                stop = true;
            }
            else {
                ourPlayer->playItemAtHand(selection);
            }
        }

        //destroy 
        DestroyEffect d;
       // d.use(card);

        ////Tap
        ourPlayer->tapSelectedLandCards();

        ////Play2
        if(isPlayedLandCard){
            cout << BOLDRED << "You can't play land card anymore for this turn."  << RESET << endl;
        } else {
            cout << BOLDMAGENTA << "Do you want to play a land card? " << BOLDBLUE << "(Y/N)" << RESET << endl;
            cin >> answer;

            if (answer == "Y" || answer == "y") {
                selection = (ourPlayer->getAndPrintHandVector(true));
                ourPlayer->playItemAtHand(selection);
            }
        }
        ////Cleanup
        for(int i = 0;i<ourPlayer->manaCount.size();i++){
            ourPlayer->manaCount[i] = 0;
        }
    }

    DestroyEffect destroyEffect;
    DealDamageEffect dealDamageEffect;
    DealDamageToAllEffect dealDamageToAllEffect;
    GainStatsEffect gainStatsEffect;
    ReturnCreatureToLifeEffect returnCreatureToLife;
    GainTrampleEffect gainTrampleEffect;
    LoseGreenTrampleEffect loseGreenTrampleEffect;
    LoseFirstStrikeEffect loseFirstStrikeEffect;

    void createDecks(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
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
        shared_ptr<Card>C11 = make_shared<SorceryCard>("Disenchant", "Sorcery", "White", "1W", player1, &destroyEffect);
        shared_ptr<Card>C12 = make_shared<SorceryCard>("Lightning Bolt", "Sorcery", "Green", "1G", player1, &dealDamageEffect);
        shared_ptr<Card>C13 = make_shared<SorceryCard>("Flood", "Sorcery", "Flood", "1GW", player1, &destroyEffect);
        shared_ptr<Card>C14 = make_shared<SorceryCard>("Flood", "Sorcery", "Flood", "1GW", player1, &destroyEffect);

        ////Enchantment Cards
        shared_ptr<Card>C15 = make_shared<SorceryCard>("Rage", "Enchantment", "Green", "G", player1, &gainTrampleEffect);
        shared_ptr<Card>C16 = make_shared<SorceryCard>("Holy War", "Enchantment", "White", "1W", player1, &gainStatsEffect);
        shared_ptr<Card>C17 = make_shared<SorceryCard>("Holy Light", "Enchantment", "White", "1W", player1, &gainStatsEffect);

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
        C11 = make_shared<SorceryCard>("Reanimate", "Sorcery", "Black", "B", player2, &returnCreatureToLife);
        C12 = make_shared<SorceryCard>("Plague", "Sorcery", "Black", "2B", player2, &dealDamageToAllEffect);
        C13 = make_shared<SorceryCard>("Terror", "Sorcery", "Black", "1B", player2, &destroyEffect);
        C14 = make_shared<SorceryCard>("Terror", "Sorcery", "Black", "1B", player2, &destroyEffect);

        //Enchantment Card
        C15 = make_shared<EnchantmentCard>("Unholy War", "Land", "Black", "1B", player2, &gainStatsEffect);
        C16 = make_shared<EnchantmentCard>("Restrain", "Enchantment", "Red", "2R", player2, &loseGreenTrampleEffect);
        C17 = make_shared<EnchantmentCard>("Slow", "Enchantment", "Black", "B", player2, &loseFirstStrikeEffect);

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
        shared_ptr<Player> targetPlayer;
        vector<shared_ptr<Card>> cards;

        if (turn == 0) {
            targetPlayer = p1;
        }
        else {
            targetPlayer = p2;
        }
        if (targetPlayer->inPlay.size() < 1) {//////////////////??
            return;
        }

        for (int i = 0; i < targetPlayer->inPlay.size(); i++)
        {
            if (targetPlayer->inPlay[i]->getType() == "Creature") {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                targetPlayer->inPlay[i]->printInfo();
                cards.push_back(targetPlayer->inPlay[i]);
            }
        }

        if (turn == 0) {
            targetPlayer = p1;
        }
        else {
            targetPlayer = p2;
        }
        if (targetPlayer->inPlay.size() < 1) {//////////////////??
            return;
        }

        for (int i = 0; i < targetPlayer->inPlay.size(); i++)
        {
            if (targetPlayer->inPlay[i]->getType() == "Creature") {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                targetPlayer->inPlay[i]->printInfo();
                cards.push_back(targetPlayer->inPlay[i]);
            }
        }

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

            cout << "ATTACKING CREATURE HAS : " << attackingCreature->getHp() << "HP LEFT." << endl;
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
        }
    }

    void setupGame() {
        p1 = make_shared<Player>();
        p2 = make_shared<Player>();

        for(int i = 0;i<8;i++){
            switch (i){
                case 0: {
                    DestroyEffect destroyEffect;
                    //allEffects.push_back(destroyEffect);
                    break;
                }
                case 1: {
                    DealDamageEffect dealDamageEffect;
                    //allEffects.push_back(dealDamageEffect);
                    break;
                }
                case 2:{
                    DealDamageToAllEffect dealDamageToAllEffect;
                    //allEffects.push_back(dealDamageToAllEffect);
                    break;
                }
                case 3:{
                    GainStatsEffect gainStatsEffect;
                    //allEffects.push_back(gainStatsEffect);
                    break;
                }
                case 4:{
                    ReturnCreatureToLifeEffect returnCreatureToLifeEffect;
                    //allEffects.push_back(returnCreatureToLifeEffect);
                    break;
                }
                case 5:{
                    GainTrampleEffect gainTrampleEffect;
                    //allEffects.push_back(gainTrampleEffect);
                    break;
                }
                case 6:{
                    LoseGreenTrampleEffect loseGreenTrampleEffect;
                    //allEffects.push_back(loseGreenTrampleEffect);
                    break;
                }
                case 7:{
                    LoseFirstStrikeEffect loseFirstStrikeEffect;
                    //allEffects.push_back(loseFirstStrikeEffect);
                    break;
                }
            }
        }

        createDecks(p1, p2);

        selectRandomCardsFromLibraryToPutIntoHand(p1);
        selectRandomCardsFromLibraryToPutIntoHand(p2);

        cout << "p1 hand:" << endl;
        p1->printHand();

        cout << "p2 hand:" << endl;
        p2->printHand();

        playGame();
    }
    int main() {
        setupGame();

        return 0;
    }