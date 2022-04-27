#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

class Index {
    int a, c, Xn;
    int Xcurrent;
public:
    Index(int a, int c, int Xn) : a(a), c(c), Xn(Xn) {
        Xcurrent = Xn;
    }

    int getNext(int m) {
        Xcurrent = (a * Xcurrent + c) % m;
        return Xcurrent;
    }

};

class Card {
    std::string symbol;
    short unsigned number;
public:
    Card(std::string symbol, short unsigned number) : symbol(symbol), number(number) {}

    void print() {
        std::cout << number << "," << symbol << std::endl;
    }

    void test_print() {
        std::cout << number << "(" << symbol << "), ";
    }

    bool isGenuine() {
        return symbol == "negru" || symbol == "rosu" || symbol == "trefla" ||
               symbol == "romb" && number > 1 && number < 15;
    }

    short unsigned getNumber() const {
        return number;
    }
};

class PackOfCards {
    std::vector<Card> cards;
    short unsigned currentCardToDraw = 0;
public:
    PackOfCards() {
        cards.clear();
    }

    void add(const Card &card) { //maybe error
        cards.push_back(card);
    }

    void check_cards() {
        bool isPackOk = true;
        for (auto card : cards) {
            if (!card.isGenuine()) {
                isPackOk = false;
                break;
            }
        }
        if (isPackOk) {
            if (cards.size() == 52) {
                std::cout << "Pachet OK" << std::endl;
            } else {
                std::cout << "Pregatit pentru Blackjack" << std::endl;
            }
        } else {
            std::cout << "Pachet masluit" << std::endl;
        }
    }

    void shuffle_cards(Index &first, Index &second) {
        currentCardToDraw = 0;
        for (int i = 0; i < 50; i++) {
            int firstIndex = first.getNext(cards.size());
            int secondIndex = second.getNext(cards.size());
            Card aux = cards[firstIndex];
            cards[firstIndex] = cards[secondIndex];
            cards[secondIndex] = aux;
        }
    }

    void print() {
        for (auto card : cards) {
            card.print();
        }
    }

    void standard_pack() {
        std::vector<std::string> symbols = {"rosu", "negru", "romb", "trefla"};
        for (auto symbol : symbols) {
            for (int i = 2; i <= 14; i++) {
                if (i == 11) {
                    continue;
                }
                cards.emplace_back(symbol, i);
            }
        }
    }

    Card getCard() {
        Card card = cards[currentCardToDraw];
        currentCardToDraw++;
        return card;
    }
};

class Player {
    std::string name;
    double money;
    std::vector<Card> cards;
    bool outOfTable = false;
    bool stand = false;
public:
    Player(std::string name, double money) : name(name), money(money) {
        cards.clear();
    }

    Player() {
        name = "Dealer";
        money = 1000;
        cards.clear();
    }

    void print() {
        std::cout << name << ": " << money << std::endl;
    }

    void first_hand(Card a, Card b) {
        cards.push_back(a);
        cards.push_back(b);
        if(get_score() >= 17) {
            stand = true;
        }
    }

    int get_score() {
        int score = 0;
        for (auto &card : cards) {
            if (card.getNumber() == 12 || card.getNumber() == 13 || card.getNumber() == 14) {
                score += 10;
            } else {
                score += card.getNumber();
            }
        }
        return score;
    }

    void draw_card(Card card) {
        cards.push_back(card);
        if(get_score() >= 17) {
            stand = true;
        }
    }

    void lost() {
        money -= 10;
        if (money < 10) {
            outOfTable = true;
        }
    }

    void won() {
        money += 10;
    }

    void reset() {
        cards.clear();
        stand = false;
    }

    bool isOutOfTable() const {
        return outOfTable;
    }

    bool isStand() const {
        return stand;
    }
};

void read_cards(PackOfCards &pack) {
    short unsigned cardNumber;
    std::string cardSymbol;

    while (std::cin >> cardNumber) {
        getchar();
        std::cin >> cardSymbol;
        Card card(cardSymbol, (int) cardNumber);
        pack.add(card);
    }
}

int main() {

    std::string command;
    std::cin >> command;

    PackOfCards packOfCards;


    if (command == "check_cards") {
        read_cards(packOfCards);
        packOfCards.check_cards();
    } else if (command == "shuffle_cards") {
        int a, c, Xn;
        std::cin >> a >> c >> Xn;
        Index firstIndex(a, c, Xn);
        std::cin >> a >> c >> Xn;
        Index secondIndex(a, c, Xn);
        read_cards(packOfCards);
        packOfCards.shuffle_cards(firstIndex, secondIndex);
        packOfCards.print();
    } else if (command == "play_game") {
        std::vector<Player> players;
        int noOfPlayers;
        std::cin >> noOfPlayers;
        for (int i = 0; i < noOfPlayers; i++) {
            std::string name;
            double money;
            std::cin >> name >> money;
            players.emplace_back(name, money);
        }
        int a, c, Xn;
        packOfCards.standard_pack();
        while (std::cin >> a >> c >> Xn) {
            Index firstIndex(a, c, Xn);
            std::cin >> a >> c >> Xn;
            Index secondIndex(a, c, Xn);
            packOfCards.shuffle_cards(firstIndex, secondIndex);

            for (auto &player : players) {
                if (player.isOutOfTable()) {
                    continue;
                }
                player.first_hand(packOfCards.getCard(), packOfCards.getCard());
            }

            Player dealer;
            dealer.first_hand(packOfCards.getCard(), packOfCards.getCard());

            for (auto &player : players) {
                if (player.isOutOfTable()) {
                    continue;
                }
                while (!player.isStand()) {
                    player.draw_card(packOfCards.getCard());
                }
            }

            while (dealer.get_score() < 17) {
                dealer.draw_card(packOfCards.getCard());
            }

            for (auto &player : players) {
                if (player.isOutOfTable()) {
                    continue;
                }
                if (player.get_score() > 21) {
                    player.lost();
                } else if (dealer.get_score() <= 21) {
                    if (player.get_score() > dealer.get_score()) {
                        player.won();
                    } else if (player.get_score() < dealer.get_score()) {
                        player.lost();
                    }
                } else {
                    player.won();
                }

                if (!player.isOutOfTable()) {
                    player.reset();
                }
            }
            dealer.reset();
        }
        for (auto player : players) {
            if (!player.isOutOfTable()) {
            player.print();
            }
        }

    }
    return 0;
}
