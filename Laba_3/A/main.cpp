#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "framework.h"
#include "Library/dialog_menu.h"
#include "Library/utilities.h"
#include "Library/big_integer.h"

using namespace bigint_ns;

void ClearConsole(BigInteger& nothing) { system("cls"); }

const char* kMsgs[] = {
        "0. Выйти",
        "1. Изменить исходное число",
        "2. Добавить к числу (+=)",
        "3. Вычесть из числа (-=)",
        "4. Вывести число в консоль",
        "5. Изменить знак числа",
        "6. Увеличить число в 10^n раз",
        "7. Уменьшить число в 10^n раз",
        "8. Очистить знаки числа",
        "9. Очистить консольный вывод"
};
constexpr int kN = sizeof(kMsgs) / sizeof(kMsgs[0]);

void(*fptr[])(BigInteger&) = {
    NULL,
    PlaceSample,
    AddBigInteger,
    SubtractBigInteger,
    PrintBigInteger,
    SetSign,
    IncreaseOrder,
    DecreaseOrder,
    ClearDigits,
    ClearConsole
};

void dialog(BigInteger& sample) {
    while(true) {
        for (int i = 0; i < kN; std::cout << kMsgs[i] << std::endl, i++);
        int choice = 0;
        choice = GetNumber("Your choice: ");
        if(!choice) {
            break;
        }
        else if (choice < 0 || choice > kN) {
            std::cout << "[WARNING] Wrong option" << std::endl << std::endl;
        }
        else {
            fptr[choice](sample);
        }
    }
}

void SetRusLang() { system("chcp 1251 && cls"); }

int _tmain(int argc, _TCHAR* argv[]) {
    SetRusLang();
    BigInteger sample;
    while (true) {
        try {
            dialog(sample);
            return 0;
        }
        catch (std::exception& msg) {
            std::cout << msg.what() << std::endl;
        }
        catch (...) {
            std::cout << "Something went wrong. Exit..." << std::endl;
            return 1;
        }
    }
}