#include "framework.h"
#include "Library/CartesianFolium.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace Laba2;

int _tmain(int argc, _TCHAR* argv[]) {
	system("chcp 1251 && cls");
	CartesianFolium folium;
	int fl1 = 1;
	double factor;
	while (fl1) {
		folium.printParams();
		int fl2 = 1;
		while (fl2) {
			std::cout << "Enter alphaRad for calculate value r(alphaRad) or press ctrl+Z to quit:" << std::endl;
			double alphaRad;
			std::cin >> alphaRad;
			fl2 = std::cin.good();
			if (!fl2)
				continue;
			std::cout << "r = " << std:: fixed
				<< std::setprecision(5) << folium.distToCenter(alphaRad);
		}
		std::cin.clear();
		std::cout << "Enter new {factor} to continue or press ctrl+Z to quit:" << std::endl;
		std::cin >> factor;
		if (std::cin.good()) {
			folium.setFactor(factor);
		}
		else
			fl1 = 0;
	}
	return 0;
}