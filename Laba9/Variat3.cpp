#include <iostream>
#include <algorithm>
#include <array>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum class ComponentState
{
    Broken,
    Working
};

enum class ComputerState
{
    Broken,
    Repairing,
    Ready
};

struct Component
{
    string name;
    ComponentState state;
};

struct Computer
{
    Component processor;
    Component gpu;
    ComputerState state;
};

struct Shop
{
    Computer* computer = nullptr;
    int currentDay = 0;
    int repairDay = 0;
};

// Ремонт одной детали
void repair(Component* component)
{
    if (component == nullptr)
        return;

    component->state = ComponentState::Working;

    cout << component->name << " has been repaired!" << endl;
}

// Проверка состояния компьютера
void updateComputerState(Computer* computer)
{
    if (computer == nullptr)
        return;

    if (computer->processor.state == ComponentState::Working &&
        computer->gpu.state == ComponentState::Working)
    {
        computer->state = ComputerState::Ready;
    }
    else
    {
        computer->state = ComputerState::Repairing;
    }
}

// Приём компьютера в мастерскую
void acceptComputer(Shop* shop, Computer* computer)
{
    if (shop == nullptr || computer == nullptr)
        return;

    shop->computer = computer;
    shop->repairDay = shop->currentDay + 7;

    computer->state = ComputerState::Repairing;

    cout << "Computer accepted for repair." << endl;
    cout << "Repair ticket issued." << endl;
    cout << "Estimated repair completion: day "
         << shop->repairDay << endl;
}

// Передача времени
void passTime(Shop* shop)
{
    if (shop == nullptr || shop->computer == nullptr)
        return;

    shop->currentDay++;

    cout << "\nDay " << shop->currentDay << endl;

    // Процессор ремонтируется
    if (shop->computer->processor.state == ComponentState::Broken &&
        shop->currentDay >= shop->repairDay)
    {
        repair(&shop->computer->processor);
    }

    // Видеокарта ремонтируется
    if (shop->computer->gpu.state == ComponentState::Broken &&
        shop->currentDay >= shop->repairDay)
    {
        repair(&shop->computer->gpu);
    }

    updateComputerState(shop->computer);

    if (shop->computer->state == ComputerState::Ready)
    {
        cout << "Computer is ready!" << endl;
    }
}

// Выдача компьютера клиенту
void giveBackComputer(Shop* shop)
{
    if (shop == nullptr || shop->computer == nullptr)
        return;

    if (shop->computer->state == ComputerState::Ready)
    {
        cout << "\nComputer successfully returned to the client!"
             << endl;

        shop->computer = nullptr;
    }
    else
    {
        cout << "\nComputer is not ready yet. "
             << "The client has to wait." << endl;
    }
}

// Вывод информации о компьютере
void printComputer(const Computer& computer)
{
    cout << "\nComputer information:" << endl;

    cout << "Processor: "
         << (computer.processor.state == ComponentState::Working
             ? "Working" : "Broken") << endl;

    cout << "GPU: "
         << (computer.gpu.state == ComponentState::Working
             ? "Working" : "Broken") << endl;

    cout << "Status: ";

    switch (computer.state)
    {
        case ComputerState::Broken:
            cout << "Broken";
            break;

        case ComputerState::Repairing:
            cout << "Repairing";
            break;

        case ComputerState::Ready:
            cout << "Ready";
            break;
    }

    cout << endl;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // Создаём компьютер с неисправными деталями
    Computer computer
    {
        {"Processor", ComponentState::Broken},
        {"GPU", ComponentState::Broken},
        ComputerState::Broken
    };

    // Создаём мастерскую
    Shop shop;

    cout << "COMPUTER REPAIR SHOP" << endl;

    printComputer(computer);

    // Клиент приносит компьютер
    cout << "\nClient brings the computer to the shop."
         << endl;

    acceptComputer(&shop, &computer);

    // Случайный день возвращения клиента: от 3 до 10
    int clientReturnDay = 3 + rand() % 8;

    cout << "\nThe client plans to return on day "
         << clientReturnDay << "." << endl;

    // Каждый день проходит время
    while (shop.computer != nullptr)
    {
        passTime(&shop);

        // Проверяем, пришёл ли клиент
        if (shop.currentDay == clientReturnDay)
        {
            cout << "\nClient arrives to pick up the computer!"
                 << endl;

            giveBackComputer(&shop);

            // Если компьютер ещё не готов, клиент придёт позже
            if (shop.computer != nullptr)
            {
                clientReturnDay = shop.currentDay + 1 + rand() % 5;

                cout << "The client will return on day "
                     << clientReturnDay << "." << endl;
            }
        }

        // Если клиент уже не пришёл, но компьютер готов,
        // мастерская продолжает ждать его
    }

    cout << "\nWORK COMPLETED" << endl;

    return 0;
}