#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>

struct Zadanie
{
    int x;
    int y;
};

struct Otvet
{
    int znachenie;
};

struct PravilniiOtvet
{
    int znachenie;
};

struct Ocenka
{
    int raznica;
    int ball;
};

struct Ucebnic
{
    std::array<Zadanie, 5> spisokZadanii;
};

struct Student
{
    int oshibka;
};

struct Prepod
{
    const Ucebnic* ucebnic;
    int minBall;
    int maxBall;
};

// Преподаватель берет задание из учебника (номер с 0)
Zadanie datiZadanie(const Prepod* prepod, int indeksZadaniya)
{
    return prepod->ucebnic->spisokZadanii[indeksZadaniya];
}

PravilniiOtvet poluchitPravilniiOtvet(Zadanie zadanie)
{
    PravilniiOtvet otvet{ .znachenie = zadanie.x + zadanie.y };
    return otvet;
}

// Студент решает верно, но добавляет свою ошибку
Otvet reshitZadanie(const Student* student, Zadanie zadanie)
{
    Otvet otvet{ .znachenie = zadanie.x + zadanie.y + student->oshibka };
    return otvet;
}

// Преподаватель создает оценку - новую самостоятельную сущность
Ocenka sozdatOcenku(
    const Prepod* prepod,
    PravilniiOtvet pravilniiOtvet,
    Otvet otvet)
{
    int raznica{ std::abs(pravilniiOtvet.znachenie - otvet.znachenie) };

    Ocenka ocenka{
        .raznica = raznica,
        .ball = std::max(prepod->minBall, prepod->maxBall - raznica),
    };
    return ocenka;
}

void vyvestiOcenku(const Ocenka& ocenka)
{
    std::cout << "Raznica otvetov: " << ocenka.raznica << '\n';
    std::cout << "Ocenka: " << ocenka.ball << '\n';
}

int main()
{
    Ucebnic ucebnic{
        .spisokZadanii = {{
            {2, 3},
            {5, 5},
            {7, 4},
            {10, 8},
            {15, 6},
        }},
    };

    Prepod prepod{
        .ucebnic = &ucebnic,
        .minBall = 1,
        .maxBall = 10,
    };

    Student student{
        .oshibka = 5,
    };

    int kolichestvoZadanii{ static_cast<int>(ucebnic.spisokZadanii.size()) };

    std::cout << "Spisok zadanii:\n";
    for (int i = 0; i < kolichestvoZadanii; i++)
    {
        std::cout << i + 1 << ". "
                  << ucebnic.spisokZadanii[i].x << " + "
                  << ucebnic.spisokZadanii[i].y << '\n';
    }

    int nomerZadaniya;
    std::cout << "\nPrepod vyberaet zadanie (1-"
              << kolichestvoZadanii << "): ";
    std::cin >> nomerZadaniya;

    if (nomerZadaniya < 1 || nomerZadaniya > kolichestvoZadanii)
    {
        std::cout << "Neverniy nomer zadaniya!\n";
        return 1;
    }

    Zadanie zadanie{ datiZadanie(&prepod, nomerZadaniya - 1) };

    std::cout << "\nPrepod dal zadanie: "
              << zadanie.x << " + " << zadanie.y << " = ?\n";

    PravilniiOtvet pravilniiOtvet{ poluchitPravilniiOtvet(zadanie) };
    Otvet otvet{ reshitZadanie(&student, zadanie) };
    Ocenka ocenka{ sozdatOcenku(&prepod, pravilniiOtvet, otvet) };

    std::cout << "\nRezultat\n";
    std::cout << "Pravilniy otvet: " << pravilniiOtvet.znachenie << '\n';
    std::cout << "Otvet studenta: " << otvet.znachenie << '\n';
    vyvestiOcenku(ocenka);

    return 0;
}