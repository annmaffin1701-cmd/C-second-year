// Файл содержит пять строк, для каждой известно количество
// символов. Добавьте символы в выбранную строку и
// поменяйте местами две выбранные строки.

#include <array>
#include <cstddef>
#include <iostream>

struct Stroka
{
    int simbvoli;
};

struct File
{
    std::array<Stroka, 5> slots;
};

void addSimvoli(File *file, size_t slotIndex, int kolicestvo)
{
    file->slots[slotIndex].simbvoli += kolicestvo;
}

void changeStroki(File *file, size_t firstIndex, size_t secondIndex)
{
    int a = file->slots[firstIndex].simbvoli; // 4
    int b = file->slots[secondIndex].simbvoli; // 2
    int temp = a; 
    a = b;
    b = temp;

}

int main()
{
    File file{
        std::array<Stroka, 5>{Stroka{1}, Stroka{2}, Stroka{3}, Stroka{4}, Stroka{5}}};
    addSimvoli(&file, 2, 5);
    changeStroki(&file, 0, 3);
    std::cout << file.slots[0].simbvoli << std::endl;
    std::cout << file.slots[1].simbvoli << std::endl;
    std::cout << file.slots[2].simbvoli << std::endl;
}