#include <iostream>
#include "lib/IntegerChannel.h"
#include "lib/IntegerSemaphore.h"

using namespace std;

int main() {
    int bakeryFlour = 0; // произведенная мука в запасе
    int maxBakeryFlour = 5; // максимальная вместимость запаса муки
    int buns = 0; // произведенные будочки
    int maxBuns = 10; // максимальная вместимость запаса булочек
    int ping = 1000; // время одного цикла работ

    cout << "Bakery start!\n";

    IntegerSemaphore endSemaphore("end_game");
    BinarySemaphore marketHasPlaceForBuns("market_has_place_for_buns", 1);
    IntegerChannel howManyFlourToBakery("hManyFlourF2B");
    IntegerChannel sendFlourToBakery("sendFlourF2B");
    IntegerChannel howManyBunsToBurger("hManyBunsB2B");
    IntegerChannel sendBunsToBurger("sendBunsB2B");

    while (true) {
        Sleep(ping);

        // отправляем булочки в бургерную
        int k = howManyBunsToBurger.getData();
        if (k) {
            int b = min(buns, k);
            if (b) {
                buns -= b;
                sendBunsToBurger.setData(b);
                printf("Bakery: send %d buns\n", b);
            }
        }

        // просим муку у фермы
        if (bakeryFlour < maxBakeryFlour) {
            k = (maxBakeryFlour - bakeryFlour);
            howManyFlourToBakery.setData(k);
            printf("Bakery: need %d flour from Farm\n", k);
        }

        // забираем муку у фермы
        k = sendFlourToBakery.getData();
        if (k) {
            bakeryFlour += k;
            if (bakeryFlour > maxBakeryFlour) {
                bakeryFlour = maxBakeryFlour;
            }
            printf("Bakery: get %d flour from Farm\n", k);
        }

        // делаем булочки
        if (bakeryFlour >= 2) {
            int b = bakeryFlour / 2;
            if (b) {
                if (buns < maxBuns) {
                    bakeryFlour -= b * 2;
                    buns += b;
                    printf("Bakery: create %d buns\n", b);
                }
            }
        }


        // продаем единицу булочек
        if (buns > maxBuns) {
            if (marketHasPlaceForBuns.Down(1)) {
                printf("Transfer buns on market.\n");
                buns -= 1;
            }
        }
        // выбрасываем булочки
        if (buns > maxBuns) {
            printf("Transfer buns on trash.");
            buns -= 1;
        }


        // конец игры
        if (endSemaphore.Down(100)) {
            break;
        }
    }

    cout << "Bakery end!\n";

    return 0;
}
