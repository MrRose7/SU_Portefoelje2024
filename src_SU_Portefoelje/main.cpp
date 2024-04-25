#include <iostream>
#include "hero.h"
#include "enemy.h"

int main()
{
    Hero mickeyMouse("Mickey Mouse");
    mickeyMouse.print();

    Enemy joeBiden("Joe Biden", 1, 1, 100);
    joeBiden.print();

    return 0;
}
