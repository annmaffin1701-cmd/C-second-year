// 17. Панель быстрого доступа
// В рюкзаке хранятся инструменты с запасом прочности.
// Три ячейки панели быстрого доступа ссылаются на эти инструменты.
//  Назначьте один инструмент двум ячейкам.
//  Используйте его через одну заданную ячейку,
// уменьшив его прочность на заданную величину.
// Покажите, что обе ячейки видят изменение инструмента в рюкзаке.

#include <array>
#include <iostream>
#include <algorithm>

struct Tool
{
    int strength;
};

struct Slot
{
    Tool* tool;
};

struct Panel
{
    std::array<Slot, 3> slots;
};

void Assign(Tool& tool, Panel& panel, int index)
{
    panel.slots[index].tool = &tool;
}

void Use(Panel& panel, int index, int wear)
{
    Tool& tool = *panel.slots[index].tool;
    tool.strength = std::max(0, tool.strength - wear);
}

int main()
{
    std::array<Tool, 2> backpack = {{{100}, {50}}};
    Panel panel;

    Assign(backpack[0], panel, 0);
    Assign(backpack[0], panel, 2);

    Use(panel, 0, 10);

    std::cout << "Рюкзак: " << backpack[0].strength << '\n';
    std::cout << "Ячейка 0: " << panel.slots[0].tool->strength << '\n';
    std::cout << "Ячейка 2: " << panel.slots[2].tool->strength << '\n';

    return 0;
}