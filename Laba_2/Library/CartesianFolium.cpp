#include "CartesianFolium.h"
#include <cmath>
#include <iostream>
#include <iomanip>

namespace Laba2 {

	CartesianFolium::CartesianFolium(double factor) {
		this->factor = factor;
	}

	double CartesianFolium::getFactor() const {
		return this->factor;
	}

	void CartesianFolium::setFactor(double newFactor) {
		this->factor = newFactor;
	}

	double CartesianFolium::maxChordLen() const {
		return abs(this->factor) / sqrt(2);
	}

	double CartesianFolium::distToCenter(double alphaRad) const {
		double sinA = sin(alphaRad);
		double cosA = cos(alphaRad);
		return abs(this->factor * cosA * sinA / ((sinA + cosA) * (1 - cosA * sinA)));
	}

	double CartesianFolium::getRx() const {
		return abs(this->factor) / (8 * sqrt(2));
	}

	double CartesianFolium::getR0() const {
		return abs(this->factor) / 2;
	}

	double CartesianFolium::getS() const {
		return this->factor * this->factor / 6;
	}

	double CartesianFolium::getDiameter() const {
		return abs(this->factor) * sqrt(4 * sqrt(3) - 6) / 3;
	}

	double CartesianFolium::getDiamdist0() const {
		return abs(this->factor) / sqrt(6);
	}

	void CartesianFolium::printParams() {
		std::cout.precision(5);
		std::cout << "Your figure is:" << std::endl;
		std::cout << "x^3 + y^3 = " << this->getFactor() << "xy" << std::endl;
		std::cout << "Наибольшая хорда: " << this->maxChordLen() << std::endl;
		std::cout << "Радиус кривизны в вершине: " << this->getRx() << std::endl;
		std::cout << "Радиус кривизны в узле: " << this->getR0() << std::endl;
		std::cout << "Площадь петли: " << this->getS() << std::endl;
		std::cout << "Длина наибольшего поперечника: " << this->getDiameter() << std::endl;
		std::cout << "Расстояние от узла до наибольшего поперечника: " << this->getDiamdist0() << std::endl;
	}
}