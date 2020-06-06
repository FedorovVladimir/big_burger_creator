#include <iostream>
#include "lib/IntegerChannel.h"
#include "lib/IntegerSemaphore.h"

using namespace std;

int main() {
    int stockFlour = 0; // произведенная мука в запасе
    int maxStockFlour = 10; // максимальная вместимость запаса муки
    int flourOfCycle = 0; // произведенная мука за цикл мука
    int stockMeat = 0; // произведеное мясо в запасе
    int maxStockMeat = 10; // максимальная вместимость запаса мяса
    int meatOfCycle = 0; // произведенные за цикл мясо
    int ping = 1000; // время одного цикла работ

    cout << "Farm start!\n";

    IntegerSemaphore endSemaphore("end_game");
    BinarySemaphore marketHasPlaceForFlour("market_has_place_for_flour", 1);
    BinarySemaphore marketHasPlaceForMeat("market_has_place_for_meat", 1);
    IntegerChannel howManyFlourToBakery("hManyFlourF2B");
    IntegerChannel sendFlourToBakery("sendFlourF2B");
    IntegerChannel howManyMeatToBakery("hManyMeatF2B");
    IntegerChannel sendMeatToBakery("sendMeatF2B");

    while (true) {
        Sleep(ping);

        // отправляем муку в пекарню
        int k = howManyFlourToBakery.getData();
        if (k) {
            int flour = min(stockFlour, k);
            if (flour) {
                stockFlour -= flour;
                sendFlourToBakery.setData(flour);
                printf("Farm: send %d flour\n", flour);
            }
        }
        // отправляем мясо в пекарню
        k = howManyMeatToBakery.getData();
        if (k) {
            int meat = min(stockMeat, k);
            if (meat) {
                stockMeat -= meat;
                sendMeatToBakery.setData(meat);
                printf("Farm: send %d meat\n", meat);
            }
        }


        // производство муки
        flourOfCycle = 1;
        string msg = "Farm: Create 1 floor. ";
        // передаем муку в запас
        if (stockFlour < maxStockFlour) {
            stockFlour += 1;
            flourOfCycle = 0;
            msg += "Transfer floor on stock.";
        }
        // продаем единицу муки
        if (flourOfCycle && marketHasPlaceForFlour.Down(1)) {
            flourOfCycle = 0;
            msg += "Transfer floor on market.";
        }
        // выбрасываем муку
        if (flourOfCycle) {
            flourOfCycle = 0;
            msg += "Transfer floor on trash.";
        }


        // производство мяса
        meatOfCycle = 1;
        msg += " | Create 1 vegetables. ";
        // передаем мясо в запас
        if (stockMeat < maxStockMeat) {
            stockMeat += 1;
            meatOfCycle = 0;
            msg += "Transfer floor on stock.";
        }
        // продаем единицу мяса
        if (meatOfCycle && marketHasPlaceForMeat.Down(1)) {
            meatOfCycle = 0;
            msg += "Transfer floor on market.";
        }
        // выбрасываем мясо
        if (meatOfCycle) {
            meatOfCycle = 0;
            msg += "Transfer floor on trash.";
        }


        cout << msg + "\n";


        // конец игры
        if (endSemaphore.Down(100)) {
            break;
        }
    }

    cout << "Farm end!\n";

    return 0;
}
