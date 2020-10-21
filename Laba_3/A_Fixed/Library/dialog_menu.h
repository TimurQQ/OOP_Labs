#pragma once
#ifndef _BIG_INTEGER_DIALOG_MENU_INCLUDED_
#define _BIG_INTEGER_DIALOG_MENU_INCLUDED_
#include "big_integer.h"
#include "utilities.h"

namespace bigint_ns {

    void PlaceSample(BigInteger& sample, const char* msg) {
        std::cout << msg;
        while (!(sample.Input(std::cin))) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Error!" << std::endl << msg;
        }
        std::cout << "Done!" << std::endl;
    }

    void PlaceSample(BigInteger& sample) {
        PlaceSample(sample, "Enter a new value: ");
    }

    void AddBigInteger(BigInteger& sample) {
        BigInteger tmp;
        PlaceSample(tmp, "Enter the value to add: ");
        sample = sample.Plus(tmp);
        std::cout << "Done!" << std::endl;
    }

    void SubtractBigInteger(BigInteger& sample) {
        BigInteger tmp;
        PlaceSample(tmp, "Enter the subtracted value: ");
        sample = sample.Minus(tmp);
        std::cout << "Done!" << std::endl;
    }

    void PrintBigInteger(BigInteger& sample) {
        std::cout << "Value: ";
        sample.Print(std::cout);
        std::cout << "Done!" << std::endl;
    }

    void SetSign(BigInteger& sample) {
        int x = 0;
        x = GetNumber("Enter a new value: ");
        sample.set_sign(x);
        std::cout << "Done!" << std::endl;
    }

    void IncreaseOrder(BigInteger& sample) {
        int x = 0;
        x = GetNumber("Enter a new value: ");
        sample.IncreaseOrder(x);
        std::cout << "Done!" << std::endl;
    }

    void DecreaseOrder(BigInteger& sample) {
        int x = 0;
        x = GetNumber("Decrease Oreder by: ");
        sample.DecreaseOrder(x);
        std::cout << "Done!" << std::endl;
    }
}

#endif // _BIG_INTEGER_DIALOG_MENU_INCLUDED_