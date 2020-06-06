#include <iostream>
#include "lib/IntegerChannel.h"
#include "lib/IntegerSemaphore.h"

using namespace std;

void endGame(IntegerSemaphore &endSemaphore);

int main() {
    int burgerJointCutlet = 0; // запас котлет
    int maxBurgerJointCutlet = 5; // максимальная вместимость запаса котлет
    int burgerJointBuns = 0; // запас булочек
    int maxBurgerJointBuns = 5; // максимальная вместимость запаса булочек
    int burger = 0; // сейчас
    int maxBurger = 5; // цель игры
    int ping = 1000; // время одного цикла работ

    cout << "BurgerJoint start!\n";

    IntegerSemaphore endSemaphore("end_game");
    IntegerChannel howManyBunsToBurger("hManyBunsB2B");
    IntegerChannel sendBunsToBurger("sendBunsB2B");
    IntegerChannel howManyCutletToBurger("hManyCutletM2B");
    IntegerChannel sendCutletToBurger("sendCutletM2B");

    while (true) {
        Sleep(ping);


        // просим котлеты
        if (burgerJointCutlet < maxBurgerJointCutlet) {
            int k = (maxBurgerJointCutlet - burgerJointCutlet);
            howManyCutletToBurger.setData(k);
            printf("Burger_joint: need %d cutlet\n", k);
        }

        // забираем котлеты
        int k = sendCutletToBurger.getData();
        if (k) {
            burgerJointCutlet += k;
            if (burgerJointCutlet > maxBurgerJointCutlet) {
                burgerJointCutlet = maxBurgerJointCutlet;
            }
            printf("Burger_joint: get %d meat cutlet\n", k);
        }


        // просим булочки
        if (burgerJointBuns < maxBurgerJointBuns) {
            int c = (maxBurgerJointBuns - burgerJointBuns);
            howManyBunsToBurger.setData(c);
            printf("Burger_joint: need %d cutlet\n", c);
        }

        // забираем булочки
        k = sendBunsToBurger.getData();
        if (k) {
            burgerJointBuns += k;
            if (burgerJointBuns > maxBurgerJointBuns) {
                burgerJointBuns = maxBurgerJointBuns;
            }
            printf("Burger_join: get %d meat cutlet\n", k);
        }


        // конец игры
        if (endSemaphore.Down(100)) {
            break;
        }

        printf("!!!%d %d\n", burgerJointBuns, burgerJointCutlet);
        if (burgerJointCutlet && burgerJointBuns) {
            burger += 1;
            burgerJointCutlet -= 1;
            burgerJointBuns -= 1;
            printf("Burger_join: create burger\n", k);
        }

        if (burger == maxBurger) {
            endGame(endSemaphore);
        }
    }

    cout << "BurgerJoint end!\n";

    return 0;
}

void endGame(IntegerSemaphore &endSemaphore) {
    endSemaphore.Up(5);
}
