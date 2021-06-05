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

    virtual int getHp()
    {
        return 1;
    }

    virtual string getManaCost() = 0;

    bool isDead()
    {
        getHp();


        if (getHp() <= 0)
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
        cout << CYAN << name << " " << YELLOW << type << RESET;
    }

    virtual bool getStatus()
    {
        return isTapped;
    }

    virtual void activateAbility(int a)
    {

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
    virtual void useEffect(shared_ptr<Card> c) = 0;

};
void setVectorSize(vector<int>* v) { //Vektör boşsa içine 5 tane 0 ekliyor. (Mana ücretleri için)
    if (v->size() == 0) {
        for (int i = 0; i < 6; i++) {
            v->push_back(0);
        }
    }
}
class Player {
protected:
    bool hasWon;
    int hp;
    vector<shared_ptr<Card>> library, hand, inPlay, discard;
    vector<int> manaCount; //White, Green, Black, Red, Blue, Colorless
    string playerName;
public:
    Player()
    {
        hp = 15;
        hasWon = false;
        setVectorSize(&manaCount);
        playerName = "";
    }
    Player(string name)
    {
        hp = 15;
        hasWon = false;
        setVectorSize(&manaCount);
        playerName = name;

    }
    bool getHasWon()
    {
        return hasWon;
    }

    void getHealthInfo()
    {
        cout << GREEN << playerName << "'s health is: " << RED << getHp() << RESET << endl;
    }
    int getHp()
    {
        return hp;
    }

    void setHp(int a)
    {
        hp = a;
    }

    vector<shared_ptr<Card>> returnCard(int which) {
        if (which == 0) {
            return library;
        }
        else if (which == 1) {
            return hand;
        }
        else if (which == 2) {
            return inPlay;
        }
        else if (which == 3) {
            return discard;
        }
    }

    vector<int> getMana() {
        return manaCount;
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

            //cout << "index: " << i << '\t';
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


    void addCardToHandbyCard(shared_ptr<Card>& C1)
    {
        if (find(discard.begin(), discard.end(), C1) != discard.end()) {
            hand.push_back(C1);
            discard.erase(remove(discard.begin(), discard.end(), C1), discard.end());

        }
    }

    bool checkManaCost(string s) { //Stringi gerekli olan mana ücretleri için vektöre çeviriyor
        vector<int> requiredMana;
        setVectorSize(&requiredMana);
        for (int i = 0; i < s.length(); i++) {
            if (isdigit(s[i])) {
                requiredMana[5] += ((int)s[i] - 48);
            }
            else {
                if (s[i] == "W"[0]) {
                    requiredMana[0]++;
                } if (s[i] == "G"[0]) {
                    requiredMana[1]++;
                } if (s[i] == "B"[0]) {
                    requiredMana[2]++;
                } if (s[i] == "R"[0]) {
                    requiredMana[3]++;
                } if (s[i] == "L"[0]) {
                    requiredMana[4]++;
                }
            }
        }
        return payMana(requiredMana);
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
        cout << BOLDBLUE << "CARDS IN " << playerName << "'s " << "HAND" << RESET << endl;
        for (int i = 0; i < hand.size(); i++)
        {
            cout << RED << "index: " << BOLDWHITE << i << '\t' << RESET;
            (hand[i])->printInfo();
            cout << endl;
        }
        if (hand.size() == 0) {
            cout << RED << "It is empty." << RESET << endl;
        }
    }

    void printInplay()
    {
        cout << BOLDBLUE << "CARDS IN " << playerName << "'s " << "PLAY" << RESET << endl;
        for (int i = 0; i < inPlay.size(); i++)
        {
            cout << BLUE << "index: " << WHITE << i << '\t' << RESET;
            (inPlay[i])->printInfo();
            cout << endl;

        }
        if (inPlay.size() == 0) {
            cout << RED << "It is empty." << RESET << endl;
        }
    }

    void printDiscard()
    {
        cout << "CARDS IN DISCARD PILE: " << endl;
        for (int i = 0; i < discard.size(); i++)
        {
            cout << "index: " << i << '\t';
            (discard[i])->printInfo();
        }
        cout << endl;
    }

    void printLibrary()
    {
        //cout << "CARDS IN LIBRARY: " << endl;
        for (int i = 0; i < library.size(); i++)
        {
            //cout << "index: " << i << '\t';
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
                    cout << BOLDRED << "Index:" << number << " " << RESET;
                    hand[i]->printInfo();
                    cout << endl;
                    cards.push_back(hand[i]);
                    number++;
                }
            }
            else {
                if (hand[i]->getType() != "Land") {
                    cout << BOLDRED << "Index:" << number << " " << RESET;
                    hand[i]->printInfo();
                    cout << endl;
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
        while ((selection < 0 || selection >= cards.size()) && cards.size() > 0) {
            cout << BOLDMAGENTA << "Please enter an index number to play" << str << "card or enter -1 to skip" << RESET << endl;
            cin >> selection;
            if (selection == -1 || cards.size() <= 1) {
                stop = true;
                selection = 0; //Daha iyi bir yol bulunabilir.
                break;
            }
            else if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                selection = -1;
            }
        }
        if ((stop && !isLand) || selection < 0) {
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
                landCards.push_back(inPlay[i]);
                number++;
            }
            i++;
        }
        int selection = -1;

        while (((selection >= 0 && selection <= landCards.size()) || selection == -1) && landCards.size() > 0) {
            for (int i = 0; i < landCards.size(); i++) {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                landCards[i]->printInfo();
                cout << " " << endl;
            }

            if ((selection<0 || selection>=landCards.size())) {
                cout << BOLDMAGENTA << "Please enter an index number to tap card or enter -1 to skip." << RESET << endl;
                cin >> selection;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if ((selection >= 0 && selection < landCards.size())) {
                landCards[selection]->Play();
                landCards.erase(landCards.begin() + selection);
                selection = -1;
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
                hand[index]->useEffect(hand[index]);
                hand[index]->Play();
                addCardToDiscard(hand[index]);
            }
            else if (hand[index]->getType() == "Enchantment") {
                hand[index]->useEffect(hand[index]);
                addCardToinPlay(index);
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
public:
    virtual void use(shared_ptr<Card>& C) = 0;
};

class DestroyEffect : public Effect {
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
        if (targetPlayer->returnCard(2).size() < 1) {
            return;  //Eğer inPlay boşsa soruya gerek yok.
        }

        if (C->getName() == "Disenchant")
        {
            //target enchantment
            for (int i = 0; i < targetPlayer->returnCard(2).size(); i++)
            {
                if (targetPlayer->returnCard(2)[i]->getType() == "Enchantment") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    targetPlayer->returnCard(2)[i]->printInfo();
                    cards.push_back(targetPlayer->returnCard(2)[i]);
                }
            }

            int selectionIndex;
            for (int i = 0; i < cards.size(); i++)
            {
                cout << endl;
                cout << "index: " << i << " ";
                cards[i]->printInfo();


            }
            cout << endl;
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

            for (int i = 0; i < targetPlayer->returnCard(2).size(); i++)
            {
                if (targetPlayer->returnCard(2)[i]->getType() == "Land") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    targetPlayer->returnCard(2)[i]->printInfo();
                    cards.push_back(targetPlayer->returnCard(2)[i]);
                }
            }
            int selectionIndex;
            for (int i = 0; i < cards.size(); i++)
            {
                cout << endl;
                cout << "index: " << i << " ";
                cards[i]->printInfo();


            }
            cout << endl;
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
            for (int i = 0; i < targetPlayer->returnCard(2).size(); i++)
            {
                if (targetPlayer->returnCard(2)[i]->getType() == "Creature") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    targetPlayer->returnCard(2)[i]->printInfo();
                    cards.push_back(targetPlayer->returnCard(2)[i]);
                }
            }

            int selectionIndex;
            for (int i = 0; i < cards.size(); i++)
            {
                cout << endl;
                cout << "index: " << i << " ";
                cards[i]->printInfo();


            }
            cout << endl;

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
        if (targetPlayer->returnCard(2).size() < 1) {
            return;
        }
        string selection;
        cout << "Do you want to deal damage to the player or the creature? (C / P) ";
        cin >> selection;

        if (selection == "C" || selection == "c")
        {
            for (int i = 0; i < targetPlayer->returnCard(2).size(); i++)
            {
                if (targetPlayer->returnCard(2)[i]->getType() == "Creature") {
                    cout << BOLDRED << "Index:" << i << " " << RESET;
                    targetPlayer->returnCard(2)[i]->printInfo();
                    cards.push_back(targetPlayer->returnCard(2)[i]);

                }
            }
            int damageIndex;

            for (int i = 0; i < cards.size(); i++)
            {
                cout << endl;
                cout << "index: " << i << " ";
                cards[i]->printInfo();


            }
            cout << endl;

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
public:void use(shared_ptr<Card>& C) {

    vector<shared_ptr<Card>> p1cards;
    vector<shared_ptr<Card>> p2cards;

    //p1 creatures
    for (int i = 0; i < p1->returnCard(2).size(); i++)
    {
        if (p1->returnCard(2)[i]->getType() == "Creature") {
            cout << BOLDRED << "Index:" << i << " " << RESET;
            p1->returnCard(2)[i]->printInfo();
            p1cards.push_back(p1->returnCard(2)[i]);

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
    for (int i = 0; i < p2->returnCard(2).size(); i++)
    {
        if (p2->returnCard(2)[i]->getType() == "Creature") {
            cout << BOLDRED << "Index:" << i << " " << RESET;
            p2->returnCard(2)[i]->printInfo();
            p2cards.push_back(p2->returnCard(2)[i]);
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
        for (int i = 0; i < p1->returnCard(2).size(); i++)
        {
            if (p1->returnCard(2)[i]->getType() == "Creature" && p1->returnCard(2)[i]->getColor() == "White") {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                p1->returnCard(2)[i]->printInfo();
                cardsP1.push_back(p1->returnCard(2)[i]);
            }
        }
        for (int i = 0; i < cardsP1.size(); i++)
        {
            cardsP1[i]->setHp(cardsP1[i]->getHp() + 1);
            cardsP1[i]->setAttack(cardsP1[i]->getAttackPower() + 1);
        }
        cardsP1.empty();
        //p2 whites
        for (int i = 0; i < p2->returnCard(2).size(); i++)
        {
            if (p2->returnCard(2)[i]->getType() == "Creature" && p2->returnCard(2)[i]->getColor() == "White") {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                p2->returnCard(2)[i]->printInfo();
                cardsP2.push_back(p2->returnCard(2)[i]);
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
        for (int i = 0; i < p1->returnCard(2).size(); i++)
        {
            if (p1->returnCard(2)[i]->getType() == "Creature" && p1->returnCard(2)[i]->getColor() == "Black") {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                p1->returnCard(2)[i]->printInfo();
                cardsP1.push_back(p1->returnCard(2)[i]);
            }
        }
        for (int i = 0; i < cardsP1.size(); i++)
        {
            cardsP1[i]->setAttack(cardsP1[i]->getAttackPower() + 2);
        }
        cardsP1.empty();

        //p2 blacks
        for (int i = 0; i < p2->returnCard(2).size(); i++)
        {
            if (p2->returnCard(2)[i]->getType() == "Creature" && p2->returnCard(2)[i]->getColor() == "Black") {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                p2->returnCard(2)[i]->printInfo();
                cardsP2.push_back(p2->returnCard(2)[i]);
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
        for (int i = 0; i < p1->returnCard(2).size(); i++)
        {
            if (p1->returnCard(2)[i]->getType() == "Creature" && p1->returnCard(2)[i]->getColor() == "Black") {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                p1->returnCard(2)[i]->printInfo();
                cardsP1.push_back(p1->returnCard(2)[i]);
            }
        }
        for (int i = 0; i < cardsP1.size(); i++)
        {
            cardsP1[i]->setAttack(cardsP1[i]->getAttackPower() - 1);
            cardsP1[i]->setAttack(cardsP1[i]->getAttackPower() - 1);
            if (cardsP1[i]->isDead() == true)
            {
                p1->addCardToDiscard(cardsP1[i]);
            }
        }
        cardsP1.empty();

        //p2 blacks
        for (int i = 0; i < p2->returnCard(2).size(); i++)
        {
            if (p2->returnCard(2)[i]->getType() == "Creature" && p2->returnCard(2)[i]->getColor() == "Black") {
                cout << BOLDRED << "Index:" << i << " " << RESET;
                p2->returnCard(2)[i]->printInfo();
                cardsP2.push_back(p2->returnCard(2)[i]);
            }
        }
        for (int i = 0; i < cardsP2.size(); i++)
        {
            cardsP2[i]->setAttack(cardsP2[i]->getAttackPower() - 1);
            cardsP2[i]->setAttack(cardsP2[i]->getAttackPower() - 1);
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

    for (int i = 0; i < targetPlayer->returnCard(3).size(); i++)
    {
        if (targetPlayer->returnCard(3)[i]->getType() == "Creature") {
            cout << BOLDRED << "Index:" << i << " " << RESET;
            targetPlayer->returnCard(3)[i]->printInfo();
            cards.push_back(targetPlayer->returnCard(3)[i]);
        }
    }

    if (cards.size() > 0)
    {
        int selectionIndex;
        cout << "Please enter an index of a creature to return it back to life.";
        cin >> selectionIndex;

        if (selectionIndex >= 0 && selectionIndex < cards.size()) {
            cards[selectionIndex]->setAttack(cards[selectionIndex]->getMaxAttack());
            cards[selectionIndex]->setHp(cards[selectionIndex]->getMaxHP());
            targetPlayer->addCardToHandbyCard(cards[selectionIndex]);
        }
        else {
            return; //please enter a valid index?
        }

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
    if (targetPlayer->returnCard(2).size() < 1) {//////////////////??
        return;
    }

    for (int i = 0; i < targetPlayer->returnCard(2).size(); i++)
    {
        if (targetPlayer->returnCard(2)[i]->getType() == "Creature" && targetPlayer->returnCard(2)[i]->getHasTrample() == false) {
            cout << BOLDRED << "Index:" << i << " " << RESET;
            targetPlayer->returnCard(2)[i]->printInfo();
            cards.push_back(targetPlayer->returnCard(2)[i]);
        }
    }

    if (cards.size() > 0)
    {
        int selectionIndex;
        for (int i = 0; i < cards.size(); i++)
        {
            cout << endl;
            cout << "index: " << i << " ";
            cards[i]->printInfo();


        }
        cout << endl;
        cout << "Please enter creature index of which you want to add trample." << endl;
        cin >> selectionIndex;

        if (selectionIndex >= 0 && selectionIndex < cards.size()) {
            cards[selectionIndex]->setTrample(true);
        }
        else {
            return; //"please enter a valid index?"
        }

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
    if (targetPlayer->returnCard(2).size() < 1) {//////////////////??
        return;
    }

    for (int i = 0; i < targetPlayer->returnCard(2).size(); i++)
    {
        if (targetPlayer->returnCard(2)[i]->getType() == "Creature" && targetPlayer->returnCard(2)[i]->getHasTrample() == true && targetPlayer->returnCard(2)[i]->getColor() == "Green") {
            cout << BOLDRED << "Index:" << i << " " << RESET;
            targetPlayer->returnCard(2)[i]->printInfo();
            cards.push_back(targetPlayer->returnCard(2)[i]);
        }
        else {
            return; //? başka adıma mı atlanmalı
        }
    }

    if (cards.size() > 0)
    {
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
    if (targetPlayer->returnCard(2).size() < 1) {//////////////////??
        return;
    }

    for (int i = 0; i < targetPlayer->returnCard(2).size(); i++)
    {
        if (targetPlayer->returnCard(2)[i]->getType() == "Creature" && targetPlayer->returnCard(2)[i]->getHasFirstStrike() == true) {
            cout << BOLDRED << "Index:" << i << " " << RESET;
            targetPlayer->returnCard(2)[i]->printInfo();
            cards.push_back(targetPlayer->returnCard(2)[i]);
        }
    }


    if (cards.size() > 0)
    {
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
        cout << CYAN << name << " " << YELLOW << type << " " << GREEN << mana << RESET;
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
        p1->setManaVector(getManaCost());
    }

    bool getStatus()
    {
        return isTapped;
    }

    string getType()
    {
        return type;
    }

    string getManaCost()
    {
        return mana;
    }

    bool isAlreadyPlayed()
    {
        return isPlayed;
    }

    void useEffect(shared_ptr<Card> c) {

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
    string trample = "";
    string first_strike = "";
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

            trample = "'HAS TRAMPLE'";

        }

        else if (name == "White Knight" || name == "Black Knight")
        {
            hasFirstStrike = true;
            hasTrample = false;
            first_strike = "'HAS FIRST STRIKE'";
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

    bool getStatus()
    {
        return isTapped;
    }

    void printInfo()
    {
        cout << CYAN << name << YELLOW << " ATTACK: " << attackPower << " " << GREEN << "HP: " << hp << " " << CYAN << "COSTS:" << manaCost << YELLOW << " MANA: " << GREEN << "COLOR: " << CYAN << color << " " << YELLOW << trample << GREEN << " " << first_strike << RESET;
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

    void useEffect(shared_ptr<Card> c) {

    }

};


class EnchantmentCard : public Card {
protected:
    string manaCost;
    string color;
    Effect* effect;
    std::shared_ptr<Player> p1;
    string enchantmentText;
public:

    EnchantmentCard() :Card()
    {
        manaCost = "no cost";
        color = "no color";
        enchantmentText = "";
    }

    EnchantmentCard(string name, string type, string manaCost, string color, std::shared_ptr<Player> p1, Effect* effect) :Card(name, type)
    {

        this->manaCost = manaCost;
        this->effect = effect;
        this->color = color;
        this->p1 = p1;

        if (name == "Rage")
        {
            enchantmentText = "'1 Target creature gains Trample'";
        }
        else if (name == "Holy War")
        {
            enchantmentText = "'All white creatures gain +1/+1'";
        }
        else if (name == "Holy Light")
        {
            enchantmentText = "'All black creatures gain -1/-1'";
        }
        else  if (name == "Unholy War")
        {
            enchantmentText = "'All black creatures gain +2/+0'";
        }
        else if (name == "Restrain")
        {
            enchantmentText = "'All green creatures lose Trample'";
        }
        else if (name == "Slow")
        {
            enchantmentText = "'1 Target creature loses First Strike'";
        }
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
        cout << CYAN << name << " " << YELLOW << type << GREEN << " COST: " << manaCost << CYAN << " COLOR: " << color << YELLOW << " TEXT: " << enchantmentText << RESET;
    }

    void useEffect(shared_ptr<Card> c) {
        effect->use(c);
    }
};

class SorceryCard : public Card {
protected:
    string manaCost;
    string color;
    Effect* effect;
    string sorceryText;
public:
    std::shared_ptr<Player> p1;
    SorceryCard(string name, string type, string manaCost, string color, shared_ptr<Player> p1, Effect* effect) :Card(name, type)
    {

        this->manaCost = manaCost;
        this->effect = effect;
        this->color = color;
        this->p1 = p1;
        if (name == "Disenchant")
        {
            sorceryText = "'Destroy 1 Target Enchantment'";
        }
        else if (name == "Lightning Bolt")
        {
            sorceryText = "'All white creatures gain +1/+1'";
        }
        else if (name == "Flood")
        {
            sorceryText = "'Destroy 1 Target Land'";
        }
        else  if (name == "Reanimate")
        {
            sorceryText = "'Return 1 creature from discard into to your hand'";
        }
        else if (name == "Plague")
        {
            sorceryText = "'Deal 1 damage to all creatures.'";
        }
        else if (name == "Terror")
        {
            sorceryText = "'Destroy 1 Target Creature'";
        }
    }
    SorceryCard() :Card()
    {
        manaCost = "no cost";
        color = "no color";
    }

    void Play()
    {

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
        cout << CYAN << name << YELLOW << " COST: " << manaCost << GREEN << " COLOR: " << color << CYAN << " TEXT: " << sorceryText;
    }

    void useEffect(shared_ptr<Card> c) {
        effect->use(c);
    }

};
void combat(shared_ptr<Card>& attackingCreature, shared_ptr<Player>& attakingPlayer, shared_ptr<Card>& defendingCreature, shared_ptr<Player >& defendingPlayer)
{
    attackingCreature->Tap();

    if (attackingCreature->getHasFirstStrike() == true && defendingCreature->getHasFirstStrike() == true)
    {   //İKİSİNDE DE FIRST STRIKE VARSA NORMAL COMBAT

      //  cout << defendingCreature->getName() << "(defending) creature has first strike and " << attackingCreature->getName() << "(attacking) has first strike. normal combat" << endl;


        defendingCreature->setHp(defendingCreature->getHp() - attackingCreature->getAttackPower());
        attackingCreature->setHp(attackingCreature->getHp() - defendingCreature->getAttackPower());

        cout << "ATTACKING CREATURE HAS : " << attackingCreature->getHp() << "HP LEFT." << endl;
        cout << "DEFENDING CREATURE HAS : " << defendingCreature->getHp() << "HP LEFT." << endl;

        if (defendingCreature->isDead())
        {
            cout << defendingCreature->getName() << " (DEFENDER) HAS DIED." << endl;
            defendingPlayer->addCardToDiscard(defendingCreature);
        }

        if (attackingCreature->isDead())
        {
            cout << attackingCreature->getName() << " (ATTACKER) HAS DIED." << endl;

            attakingPlayer->addCardToDiscard(attackingCreature);
        }

        cout << "DEFENDING PLAYER HAS " << defendingPlayer->getHp() << "HP LEFT." << endl;
        cout << "ATTACKING PLAYER HAS " << attakingPlayer->getHp() << "HP LEFT." << endl;

    }


    else if (attackingCreature->getHasFirstStrike() == true && defendingCreature->getHasFirstStrike() == false)
    {
        defendingCreature->setHp(defendingCreature->getHp() - attackingCreature->getAttackPower());
        cout << "DEFENDING CREATURE HAS : " << defendingCreature->getHp() << "HP LEFT." << endl;

        if (defendingCreature->isDead())
        {
            cout << defendingCreature->getName() << " (DEFENDER) HAS DIED." << endl;
            defendingPlayer->addCardToDiscard(defendingCreature);
        }

        else
        {
            attackingCreature->setHp(attackingCreature->getHp() - defendingCreature->getAttackPower());
            cout << "ATTACKING CREATURE HAS : " << attackingCreature->getHp() << "HP LEFT." << endl;

            if (attackingCreature->isDead())
            {
                cout << attackingCreature->getName() << " (ATTACKER) HAS DIED." << endl;
                attakingPlayer->addCardToDiscard(attackingCreature);
            }

        }

        cout << "DEFENDING PLAYER HAS " << defendingPlayer->getHp() << "HP LEFT." << endl;
        cout << "ATTACKING PLAYER HAS " << attakingPlayer->getHp() << "HP LEFT." << endl;

    }
    else if (defendingCreature->getHasFirstStrike() == true && attackingCreature->getHasFirstStrike() == false)
    {
        // cout << defendingCreature->getName() << "(defending) creature has first strike and " << attackingCreature->getName() << "(attacking) doesnt have it." << endl;
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
                cout << defendingCreature->getName() << " (DEFENDER) HAS DIED." << endl;
                defendingPlayer->addCardToDiscard(defendingCreature);
            }

        }

        cout << "DEFENDING PLAYER HAS " << defendingPlayer->getHp() << "HP LEFT." << endl;
        cout << "ATTACKING PLAYER HAS " << attakingPlayer->getHp() << "HP LEFT." << endl;

    }


    else if (attackingCreature->getHasTrample() == true)
    {
        //attacking'de trample varsa.
        //cout << attackingCreature->getName() << "(attacking) has trample." << endl;

        int excess_damage;

        excess_damage = attackingCreature->getAttackPower() - defendingCreature->getHp();

        defendingCreature->setHp(defendingCreature->getHp() - attackingCreature->getAttackPower());
        attackingCreature->setHp(attackingCreature->getHp() - defendingCreature->getAttackPower());

        if (defendingCreature->isDead())
        {
            cout << defendingCreature->getName() << " (DEFENDER) HAS DIED." << endl;
            defendingPlayer->addCardToDiscard(defendingCreature);
        }

        if (attackingCreature->isDead())
        {
            cout << attackingCreature->getName() << " (ATTACKER) HAS DIED." << endl;

            attakingPlayer->addCardToDiscard(attackingCreature);
        }

        defendingPlayer->setHp(defendingPlayer->getHp() - excess_damage);

        cout << "DEFENDING PLAYER HAS " << defendingPlayer->getHp() << "HP LEFT." << endl;
        cout << "ATTACKING PLAYER HAS " << attakingPlayer->getHp() << "HP LEFT." << endl;
    }

    else {



        defendingCreature->setHp(defendingCreature->getHp() - attackingCreature->getAttackPower());

        attackingCreature->setHp(attackingCreature->getHp() - defendingCreature->getAttackPower());

        cout << "ATTACKING CREATURE HAS : " << attackingCreature->getHp() << "HP LEFT." << endl;
        cout << "DEFENDING CREATURE HAS : " << defendingCreature->getHp() << "HP LEFT." << endl;


        if (defendingCreature->isDead())
        {
            cout << defendingCreature->getName() << " (DEFENDER) HAS DIED." << endl;
            defendingPlayer->addCardToDiscard(defendingCreature);
        }

        if (attackingCreature->isDead())
        {
            cout << attackingCreature->getName() << " (ATTACKER) HAS DIED." << endl;

            attakingPlayer->addCardToDiscard(attackingCreature);
        }
        cout << "DEFENDING PLAYER HAS " << defendingPlayer->getHp() << "HP LEFT." << endl;
        cout << "ATTACKING PLAYER HAS " << attakingPlayer->getHp() << "HP LEFT." << endl;
    }

}

void combatNoDefendingPlayer(shared_ptr<Card>& attackingCreature, shared_ptr<Player>& attakingPlayer, shared_ptr<Player >& defendingPlayer)
{
    attackingCreature->Tap();

    defendingPlayer->setHp(defendingPlayer->getHp() - attackingCreature->getAttackPower());
    cout << "DEFENDING PLAYER HAS " << defendingPlayer->getHp() << "HP LEFT." << endl;
    cout << "ATTACKING PLAYER HAS " << attakingPlayer->getHp() << "HP LEFT." << endl;

}

bool isGameFinished = false;
int roundCounter = 1;
void turnLoop() {
    shared_ptr<Player> ourPlayer;

    shared_ptr<Player> targetPlayer;

    if (p1->getHp() <= 0)
    {
        cout << GREEN << "PLAYER 2 HAS WON WITH " << p2->getHp() << " HP LEFT." << RESET << endl;
        isGameFinished = true;
    }
    else if (p2->getHp() <= 0)
    {
        cout << GREEN << "PLAYER 1 HAS WON WITH " << p1->getHp() << " HP LEFT." << RESET << endl;
        isGameFinished = true;
    }


    if (turn == 0) {
        cout << BLUE << "------ It is the turn of the player " << BOLDBLUE << "1 ------" << RESET << endl;
        ourPlayer = p1;
        //cout << "P1 hand:" << endl;
        //p1->printHand();

    }
    else if (turn == 1) {
        cout << BLUE << "------ It is the turn of the player " << BOLDBLUE << "2 ------" << RESET << endl;
        ourPlayer = p2;
        //cout << "P2 hand:" << endl;
        //p2->printHand();
    }



    if (turn == 0) {
        targetPlayer = p2;
    }
    else if (turn == 1) {
        targetPlayer = p1;
    }





    ////Draw
    cout << GREEN << "Draw Phase" << RESET << endl;
    shared_ptr<Card> selection;

    //cout <<ourPlayer->getHandElementCount() << endl;

    if (ourPlayer->getLibraryElementCount() > 0) {
        if (ourPlayer->getHandElementCount() < 7) {
            srand(time(0));
            //cout << rand() % ourPlayer->returnCard(0).size() << endl;
            ourPlayer->drawCard(ourPlayer->returnCard(0)[rand() % ourPlayer->returnCard(0).size()]);
        }
        else {

        }
    }
    else {
        isGameFinished = true;

        ourPlayer->setHp(0);

        if (p1->getHp() <= 0)
        {
            cout << GREEN << "PLAYER 2 HAS WON WITH " << p2->getHp() << " HP LEFT." << RESET << endl;
        }
        else if (p2->getHp() <= 0)
        {
            cout << GREEN << "PLAYER 1 HAS WON WITH " << p1->getHp() << " HP LEFT." << RESET << endl;
        }
    }


    ////Untap
    ourPlayer->untapAllinPlay();

    ////Land

    bool isPlayedLandCard = false;
    ourPlayer->printHand();

    ourPlayer->printInplay();
    targetPlayer->printInplay();

    if (turn == 0) {
        ourPlayer->getHealthInfo();
        targetPlayer->getHealthInfo();
    }
    else {
        targetPlayer->getHealthInfo();
        ourPlayer->getHealthInfo();
    }

    string answer;

    if (ourPlayer->returnCard(1).size() > 0) {
        cout << BOLDMAGENTA << "Do you want to play a land card? " << BOLDBLUE << "(Y/N)" << RESET << endl;

        cin >> answer;

        if (answer == "Y" || answer == "y") {
            selection = (ourPlayer->getAndPrintHandVector(true));
            ourPlayer->playItemAtHand(selection);
            isPlayedLandCard = true;
        }
    }

    ////Tap
    ourPlayer->tapSelectedLandCards();


    ////Non Land
    bool stop = false;
    while (!stop) {
        selection = (ourPlayer->getAndPrintHandVector(false));
        if (selection == nullptr) {
            stop = true;
        }
        else {
            bool isCompleted = ourPlayer->checkManaCost(selection->getManaCost());
            if (isCompleted) {
                ourPlayer->playItemAtHand(selection);
                cout << GREEN << "You played: " << RESET << selection->getName();
                cout << endl;
            }
            else {
                cout << RED << "Your mana is not enough for " << WHITE << selection->getName() << RED << " !" << RESET;
                cout << endl;
            }
        }
    }

    //destroy
    DestroyEffect d;
    // d.use(card);

    ////Combat



    vector<shared_ptr<Card>> ourCards, otherCards;
    vector<shared_ptr<Card>> usedAttackCards, usedDefendCards;

    int attackCardCount = 0;

    int i = 0, number = 0;

    while (i < ourPlayer->returnCard(2).size())
    {
        if (ourPlayer->returnCard(2)[i]->getType() == "Creature") {
            ourCards.push_back(ourPlayer->returnCard(2)[i]);
            number++;
        }
        i++;
    }

    i = 0, number = 0;

    while (i < targetPlayer->returnCard(2).size())
    {
        if (targetPlayer->returnCard(2)[i]->getType() == "Creature" && targetPlayer->returnCard(2)[i]->getStatus() == false) {
            otherCards.push_back(targetPlayer->returnCard(2)[i]);
            number++;
            cout << "number is " << number;
        }
        i++;
    }

    if (ourCards.size() > 0) {
        int s = -1;
        while ((s >= 0 && s < ourCards.size()) || s == -1) {
            for (int j = 0; j < ourCards.size(); j++) {
                cout << BOLDRED << "Index:" << j << " " << RESET;
                ourCards[j]->printInfo();
                cout << " " << endl;
            }

            cout << BOLDMAGENTA << "Please enter an index number for a creature." << RESET << endl;
            cin >> s;
            if (s == -1) {
                break;
            }
            //if ((s >= 0 && s < ourCards.size())) {
            if (find(ourCards.begin(), ourCards.end(), ourCards[s]) != ourCards.end()) {
                usedAttackCards.push_back(ourCards[s]);
                ourCards.erase(remove(ourCards.begin(), ourCards.end(), ourCards[s]), ourCards.end());
                attackCardCount++;
            }
            //}
        }
    }
    if (attackCardCount > 0 && otherCards.size() > 0) {
        int s = -1;
        int defendCardCount = -1;

        while (!(defendCardCount >= 0 && defendCardCount <= attackCardCount) || defendCardCount == -1) {
            cout << "How many defending card do you want to use? (Max: " << attackCardCount << ")" << endl;
            cin >> defendCardCount;
        }
        for (int j = 0; j < otherCards.size(); j++) {
            cout << BOLDRED << "Index:" << j << " " << RESET << otherCards[j]->getName() << " " << endl;
        }

        int sToDefend = -1;
        while (((sToDefend >= 0 && sToDefend < defendCardCount) || sToDefend == -1) && otherCards.size() > 0 && usedDefendCards.size() < defendCardCount) {

            cout << BOLDMAGENTA << "Please enter an index to defend." << RESET << endl;
            cin >> sToDefend;

            cout << "other cards size is : " << otherCards.size();


            if (sToDefend == -1 || otherCards.size() < 1) {
                break;
            }


            usedDefendCards.push_back(otherCards[sToDefend]);
            otherCards.erase(otherCards.begin() + sToDefend);
            defendCardCount++;

        }
    }


    if (usedAttackCards.size() > usedDefendCards.size()) {
        for (int i = 0; i < usedAttackCards.size(); i++) {
            if (i < usedDefendCards.size()) {
                combat(usedAttackCards[i], ourPlayer, usedDefendCards[i], targetPlayer);


            }
            else {
                combatNoDefendingPlayer(usedAttackCards[i], ourPlayer, targetPlayer);

            }
        }
    }
    else if (usedAttackCards.size() == usedDefendCards.size()) {
        for (int i = 0; i < usedAttackCards.size(); i++) {
            combat(usedAttackCards[i], ourPlayer, usedDefendCards[i], targetPlayer);

        }
    }


    ////Play2
    if (isPlayedLandCard) {
        cout << BOLDRED << "You can't play land card anymore for this turn." << RESET << endl;
    }
    else {
        cout << BOLDMAGENTA << "Do you want to play a land card? " << BOLDBLUE << "(Y/N)" << RESET << endl;
        cin >> answer;

        if (answer == "Y" || answer == "y") {
            selection = (ourPlayer->getAndPrintHandVector(true));
            ourPlayer->playItemAtHand(selection);
        }
    }
    ////Cleanup
    for (int i = 0; i < ourPlayer->getMana().size(); i++) {
        ourPlayer->getMana()[i] = 0;
    }

    ourPlayer->HealAllCreatures();
    targetPlayer->HealAllCreatures();
    cout << "End of round " << roundCounter << endl;

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
    shared_ptr<Card>C11 = make_shared<SorceryCard>("Disenchant", "Sorcery", "1W", "White", player1, &destroyEffect);
    shared_ptr<Card>C12 = make_shared<SorceryCard>("Lightning Bolt", "Sorcery", "1G", "Green", player1, &dealDamageEffect);
    shared_ptr<Card>C13 = make_shared<SorceryCard>("Flood", "Sorcery", "1GW", "Green", player1, &destroyEffect);
    shared_ptr<Card>C14 = make_shared<SorceryCard>("Flood", "Sorcery", "1GW", "Green", player1, &destroyEffect);

    ////Enchantment Cards
    shared_ptr<Card>C15 = make_shared<EnchantmentCard>("Rage", "Enchantment", "G", "Green", player1, &gainTrampleEffect);
    shared_ptr<Card>C16 = make_shared<EnchantmentCard>("Holy War", "Enchantment", "1W", "White", player1, &gainStatsEffect);
    shared_ptr<Card>C17 = make_shared<EnchantmentCard>("Holy Light", "Enchantment", "1W", "White", player1, &gainStatsEffect);

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
    C1 = make_shared<CreatureCard>("Skeleton", "Creature", 1, "B", "Black", 1, player2);
    C2 = make_shared<CreatureCard>("Skeleton", "Creature", 1, "B", "Black", 1, player2);
    C3 = make_shared<CreatureCard>("Skeleton", "Creature", 1, "B", "Black", 1, player2);
    C4 = make_shared<CreatureCard>("Ghost", "Creature", 2, "1B", "Black", 1, player2);
    C5 = make_shared<CreatureCard>("Ghost", "Creature", 2, "1B", "Black", 1, player2);
    C6 = make_shared<CreatureCard>("Black Knight", "Creature", 2, "BB", "Black", 2, player2);
    C7 = make_shared<CreatureCard>("Black Knight", "Creature", 2, "BB", "Black", 2, player2);
    C8 = make_shared<CreatureCard>("Orc Maniac", "Creature", 4, "2R", "Red", 1, player2);
    C9 = make_shared<CreatureCard>("Hobgoblin", "Creature", 3, "1RB", "Red", 3, player2);
    C10 = make_shared<CreatureCard>("Vampire", "Creature", 6, "3B", "Black", 3, player2);

    //Sorcery Cards
    C11 = make_shared<SorceryCard>("Reanimate", "Sorcery", "B", "Black", player2, &returnCreatureToLife);
    C12 = make_shared<SorceryCard>("Plague", "Sorcery", "2B", "Black", player2, &dealDamageToAllEffect);
    C13 = make_shared<SorceryCard>("Terror", "Sorcery", "1B", "Black", player2, &destroyEffect);
    C14 = make_shared<SorceryCard>("Terror", "Sorcery", "1B", "Black", player2, &destroyEffect);

    //Enchantment Card
    C15 = make_shared<EnchantmentCard>("Unholy War", "Enchantment", "1B", "Black", player2, &gainStatsEffect);
    C16 = make_shared<EnchantmentCard>("Restrain", "Enchantment", "2R", "Red", player2, &loseGreenTrampleEffect);
    C17 = make_shared<EnchantmentCard>("Slow", "Enchantment", "B", "Black", player2, &loseFirstStrikeEffect);

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





void playGame() {

    while (!isGameFinished) {
        turnLoop();
        turn = (turn == 0) ? turn = 1 : turn = 0;
        if (turn == 0) {
            roundCounter++;
        }
    }
}

void setupGame() {
    p1 = make_shared<Player>("Player 1");
    p2 = make_shared<Player>("Player 2");

    for (int i = 0; i < 8; i++) {
        switch (i) {
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
        case 2: {
            DealDamageToAllEffect dealDamageToAllEffect;
            //allEffects.push_back(dealDamageToAllEffect);
            break;
        }
        case 3: {
            GainStatsEffect gainStatsEffect;
            //allEffects.push_back(gainStatsEffect);
            break;
        }
        case 4: {
            ReturnCreatureToLifeEffect returnCreatureToLifeEffect;
            //allEffects.push_back(returnCreatureToLifeEffect);
            break;
        }
        case 5: {
            GainTrampleEffect gainTrampleEffect;
            //allEffects.push_back(gainTrampleEffect);
            break;
        }
        case 6: {
            LoseGreenTrampleEffect loseGreenTrampleEffect;
            //allEffects.push_back(loseGreenTrampleEffect);
            break;
        }
        case 7: {
            LoseFirstStrikeEffect loseFirstStrikeEffect;
            //allEffects.push_back(loseFirstStrikeEffect);
            break;
        }
        }
    }

    createDecks(p1, p2);

    selectRandomCardsFromLibraryToPutIntoHand(p1);
    selectRandomCardsFromLibraryToPutIntoHand(p2);

    // buraya kartla nasıl yapıcaz ?? destroyEffect.use(p1->returnCard(0)[0]);

    playGame();
}
int main() {
    setupGame();

    return 0;
}