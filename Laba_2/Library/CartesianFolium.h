#ifndef _CARTESIAN_FOLIUM_H_
#define _CARTESIAN_FOLIUM_H_

namespace Laba2 {
	class CartesianFolium {
	public:
		CartesianFolium(double a = 1.0); // �������� factor �������� ����� �������
		double getFactor() const; // ������
		void setFactor(double newFactor); // ������
		double maxChordLen() const; // ���������� ����� �����
		double distToCenter(double alphaRad) const; // ���������� �� ������ � ����������� �� ����
		double getRx() const; // ������ �������� � ������� �����
		double getR0() const; // ������ �������� � ������� �����
		double getS() const; // ������� ����� �����
		double getDiameter() const; // ����� ����������� �����������
		double getDiamdist0() const; // ���������� �� ���� �� ����������� �����������
		void printParams();
	private:
		double factor; // �������� ��������� ��� ��������� �����
	};
}

#endif // _CARTESIAN_FOLIUM_H_