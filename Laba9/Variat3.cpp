 //комп процессор видеокарта каждыцй может сломаться и ты несешь для починки 
 // шоп выдает талон вернуться через неделю 
 // через неделю забираешь почин комп

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>

struct Breakdown
{
    bool isBroken;
};

struct Pochinka
{
    bool isDone;
};

struct Processor
{
    Breakdown breakdown;
    Pochinka pochinka;
};

struct VideoCard
{
    Breakdown breakdown;
    Pochinka pochinka;
};

struct Computer
{
    Breakdown breakdown;
    Pochinka pochinka;
    Processor processor;
    VideoCard videoCard;
};

struct Talon
{
    int returnDay;
};

struct Shop
{
    int currentDay;
    int repairDays;
    int readyDay;
    bool hasComputer;
    Computer computerInRepair;
};

// Результат выдачи: получилось ли отдать компьютер и сам компьютер
struct GiveBackResult
{
    bool isReady;
    Computer computer;
};

// Чинит одну часть: если сломана, убирает поломку и отмечает починку
void repair(Breakdown* breakdown, Pochinka* pochinka)
{
    if (breakdown->isBroken)
    {
        breakdown->isBroken = false;
        pochinka->isDone = true;
    }
}

void repairComputer(Computer* computer)
{
    repair(&computer->breakdown, &computer->pochinka);
    repair(&computer->processor.breakdown, &computer->processor.pochinka);
    repair(&computer->videoCard.breakdown, &computer->videoCard.pochinka);
}

// Магазин принимает компьютер и выдает талон
Talon acceptComputer(Shop* shop, Computer computer)
{
    shop->computerInRepair = computer;
    shop->hasComputer = true;
    shop->readyDay = shop->currentDay + shop->repairDays;

    Talon talon{ .returnDay = shop->readyDay };
    return talon;
}

// Проходит время; когда срок наступил, магазин чинит компьютер
void passTime(Shop* shop, int days)
{
    shop->currentDay += days;

    if (shop->hasComputer && shop->currentDay >= shop->readyDay)
    {
        repairComputer(&shop->computerInRepair);
    }
}

// Отдает компьютер по талону, если срок наступил
GiveBackResult giveBackComputer(Shop* shop, Talon talon)
{
    if (!shop->hasComputer || shop->currentDay < talon.returnDay)
    {
        GiveBackResult result{ .isReady = false, .computer = {} };
        return result;
    }

    GiveBackResult result{
        .isReady = true,
        .computer = shop->computerInRepair,
    };
    shop->hasComputer = false;
    return result;
}

void printPart(const char* name, Breakdown breakdown, Pochinka pochinka)
{
    std::cout << name << ": ";

    if (breakdown.isBroken)
    {
        std::cout << "broken";
    }
    else if (pochinka.isDone)
    {
        std::cout << "repaired";
    }
    else
    {
        std::cout << "ok";
    }

    std::cout << '\n';
}

void printComputer(const Computer& computer)
{
    printPart("Computer", computer.breakdown, computer.pochinka);
    printPart("Processor",
              computer.processor.breakdown, computer.processor.pochinka);
    printPart("VideoCard",
              computer.videoCard.breakdown, computer.videoCard.pochinka);
}

int main()
{
    Computer computer{
        .breakdown = { .isBroken = false },
        .pochinka = { .isDone = false },
        .processor = {
            .breakdown = { .isBroken = true },
            .pochinka = { .isDone = false },
        },
        .videoCard = {
            .breakdown = { .isBroken = true },
            .pochinka = { .isDone = false },
        },
    };

    Shop shop{
        .currentDay = 0,
        .repairDays = 7,
        .readyDay = 0,
        .hasComputer = false,
        .computerInRepair = {},
    };

    std::cout << "Day " << shop.currentDay
              << ": client brings computer\n";
    printComputer(computer);

    Talon talon{ acceptComputer(&shop, computer) };
    std::cout << "Talon: come back on day " << talon.returnDay << "\n\n";

    passTime(&shop, 3);
    std::cout << "Day " << shop.currentDay << ": client comes\n";

    GiveBackResult result{ giveBackComputer(&shop, talon) };
    if (!result.isReady)
    {
        std::cout << "Not ready yet\n\n";
    }

    passTime(&shop, 4);
    std::cout << "Day " << shop.currentDay << ": client comes\n";

    result = giveBackComputer(&shop, talon);
    if (result.isReady)
    {
        std::cout << "Computer is ready:\n";
        printComputer(result.computer);
    }

    return 0;
}