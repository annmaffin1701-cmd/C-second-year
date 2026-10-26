//*У телефона есть заряд в процентах.
//Каждая минута на зарядке добавляет 1%, но заряд не может стать больше 100.
//Сделайте функцию зарядки, которая ничего не возвращает -
//ее единственный результат это изменение состояния батареи.

#include <algorithm>
#include <iostream>

struct Zareadka
{
int batarea;
};

void zareadTelefona(Zareadka* zaread, int minutes)
{
zaread->batarea = std::min(100, zaread->batarea+ minutes);
}

int main()
{
 Zareadka zaread{
.batarea = 50,
};

zareadTelefona(&zaread, 30);

std::cout
<< "Zaryad telefona: "
 << zaread.batarea
<< " procentov"
 << std::endl;
}