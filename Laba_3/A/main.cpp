#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "framework.h"
#include "Library/dialog_menu.h"
#include "Library/utilities.h"
#include "Library/big_integer.h"

void ClearConsole(bigint_ns::BigInteger&) { system("cls"); }

const char* kMsgs[] = {
        "0. Exit",
        "1. Change number",
        "2. Add number (+=)",
        "3. Subtract number (-=)",
        "4. Print number",
        "5. Change sign",
        "6. Increase by 10^n times",
        "7. Decrease by 10^n times",
        "8. Clear digits",
        "9. Clear console"
};
constexpr int kN = sizeof(kMsgs) / sizeof(kMsgs[0]);

void(*fptr[])(bigint_ns::BigInteger&) = {
    nullptr,
    bigint_ns::PlaceSample,
    bigint_ns::AddBigInteger,
    bigint_ns::SubtractBigInteger,
    bigint_ns::PrintBigInteger,
    bigint_ns::SetSign,
    bigint_ns::IncreaseOrder,
    bigint_ns::DecreaseOrder,
    bigint_ns::ClearDigits,
    ClearConsole
};

void dialog(bigint_ns::BigInteger& sample) {
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
    bigint_ns::BigInteger sample;
    while (true) {
        try {
            dialog(sample);
            return 0;
        }
        catch (std::range_error& msg) {
            std::cout << "[Range Error]: " << msg.what() << std::endl;
        }
        catch (std::invalid_argument& msg) {
            std::cout << "[Invalid Argument]: " << msg.what() << std::endl;
        }
        catch (std::overflow_error& msg) {
            std::cout << "[Overflow Error]: " << msg.what() << std::endl;
        }
        catch (...) {
            std::cout << "Something went wrong. Exit..." << std::endl;
            return 1;
        }
    }
}