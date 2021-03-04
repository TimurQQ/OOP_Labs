#ifndef _CARTESIAN_FOLIUM_H_
#define _CARTESIAN_FOLIUM_H_

namespace Laba2 {
	class CartesianFolium {
	public:
		CartesianFolium(double a = 1.0); // Значение factor дефолтно равно единице
		double getFactor() const; // Геттер
		void setFactor(double newFactor); // Сеттер
		double maxChordLen() const; // Наибольшая хорда листа
		double distToCenter(double alphaRad) const; // Расстояние до центра в зависимости от угла
		double getRx() const; // Радиус кривизны в вершине листа
		double getR0() const; // Радиус кривизны в узловой точке
		double getS() const; // Площадь петли листа
		double getDiameter() const; // Длина наибольшего поперечника
		double getDiamdist0() const; // Расстояния от узла до наибольшего поперечника
		void printParams();
	private:
		double factor; // Значение параметра для Декартова Листа
	};
}

#endif // _CARTESIAN_FOLIUM_H_