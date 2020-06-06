#include <iostream>
#include "lib/IntegerChannel.h"
#include "lib/IntegerSemaphore.h"

using namespace std;

int main() {
    int meatProcessingPlantMeat = 0; // запас мяса
    int maxMeatProcessingPlantMeat = 5; // максимальная вместимость запаса мяса
    int cutlet = 0; // запас котлет
    int maxCutlet = 10; //  максимальная вместимость запаса котлет
    int ping = 1000; // время одного цикла работ

    cout << "MeatProcessingPlant start!\n";

    IntegerSemaphore endSemaphore("end_game");
    BinarySemaphore marketHasPlaceForCutlet("market_has_place_for_cutlet", 1);
    IntegerChannel howManyMeatToBakery("hManyMeatF2B");
    IntegerChannel sendMeatToBakery("sendMeatF2B");
    IntegerChannel howManyCutletToBurger("hManyCutletM2B");
    IntegerChannel sendCutletToBurger("sendCutletM2B");

    while (true) {
        Sleep(ping);


        // отправляем котлеты в бургерную
        int k = howManyCutletToBurger.getData();
        if (k) {
            int b = min(cutlet, k);
            if (b) {
                cutlet -= b;
                sendCutletToBurger.setData(b);
                printf("MeatProcessingPlant: send %d cutlet\n", b);
            }
        }


        // просим мясо у фермы
        if (meatProcessingPlantMeat < maxMeatProcessingPlantMeat) {
            k = (maxMeatProcessingPlantMeat - meatProcessingPlantMeat);
            howManyMeatToBakery.setData(k);
            printf("MeatProcessingPlant: need %d meat from Farm\n", k);
        }

        // забираем мясо у фермы
        k = sendMeatToBakery.getData();
        if (k) {
            meatProcessingPlantMeat += k;
            if (meatProcessingPlantMeat > maxMeatProcessingPlantMeat) {
                meatProcessingPlantMeat = maxMeatProcessingPlantMeat;
            }
            printf("MeatProcessingPlant: get %d meat from Farm\n", k);
        }


        // делаем котлеты
        if (meatProcessingPlantMeat >= 2) {
            int b = meatProcessingPlantMeat / 2;
            if (b) {
                if (cutlet < maxCutlet) {
                    meatProcessingPlantMeat -= b * 2;
                    cutlet += b;
                    printf("Bakery: create %d cutlet\n", b);
                }
            }
        }


        // продаем единицу булочек
        if (cutlet > maxCutlet) {
            if (marketHasPlaceForCutlet.Down(1)) {
                printf("Transfer cutlet on market.\n");
                cutlet -= 1;
            }
        }
        // выбрасываем булочки
        if (cutlet > maxCutlet) {
            printf("Transfer cutlet on trash.");
            cutlet -= 1;
        }


        // конец игры
        if (endSemaphore.Down(100)) {
            break;
        }
    }

    cout << "MeatProcessingPlant end!\n";

    return 0;
}
