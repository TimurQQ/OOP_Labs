// Testing.cpp : Defines the entry point for the Unit test
//
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <iostream>
#include "../Library/CartesianFolium.h"
#include "../framework.h"
#include "gtest/gtest.h"

using namespace Laba2;

TEST(FoliumConstructor, DefaultConstructor) {
	CartesianFolium folium;
	const double PI = 3.14159, err = 0.00001;
	ASSERT_NEAR(1.0, folium.getFactor(), err);
}

TEST(FoliumConstructor, InitConstructor) {
	CartesianFolium folium(3);
	const double PI = 3.14159, err = 0.00001;
	ASSERT_NEAR(3.0, folium.getFactor(), err);
}

TEST(FoliumMethods, Setter) {
	CartesianFolium folium;
	double factor1 = 2.5, err = 0.00001;
	folium.setFactor(factor1);
	ASSERT_NEAR(2.5, folium.getFactor(), err);
	double factor2 = -2.5;
	folium.setFactor(factor2);
	ASSERT_NEAR(-2.5, factor2, err);
	double factor3 = 0.0;
	folium.setFactor(0);
	ASSERT_NEAR(0.0, factor3, err);
}

TEST(FoliumMethods, DefaultParameters) {
	CartesianFolium folium;
	const double err = 0.00001, PI = 3.14159;
	ASSERT_NEAR(1.0, folium.getFactor(), err);
	ASSERT_NEAR(1 / sqrt(2), folium.maxChordLen(), err);
	ASSERT_NEAR(1 / (8 * sqrt(2)), folium.getRx(), err);
	ASSERT_NEAR(0.5, folium.getR0(), err);
	ASSERT_NEAR(1.0 / 6, folium.getS(), err);
	ASSERT_NEAR(sqrt(4 * sqrt(3) - 6) / 3, folium.getDiameter(), err);
	ASSERT_NEAR(1 / sqrt(6), folium.getDiamdist0(), err);
	ASSERT_NEAR(0.0, folium.distToCenter(PI / 4 + PI / 4), err);
	ASSERT_NEAR(0.0, folium.distToCenter(PI / 4 - PI / 4), err);
	ASSERT_NEAR(0.418593, folium.distToCenter(PI / 4 + PI / 8), err);
	ASSERT_NEAR(0.418593, folium.distToCenter(PI / 4 - PI / 8), err);
}

TEST(FoliumMethods, InitParameters) {
	CartesianFolium folium(3);
	const double err = 0.00001, PI = 3.14159;
	ASSERT_NEAR(3.0, folium.getFactor(), err);
	ASSERT_NEAR(3 / sqrt(2), folium.maxChordLen(), err);
	ASSERT_NEAR(3 / (8 * sqrt(2)), folium.getRx(), err);
	ASSERT_NEAR(1.5, folium.getR0(), err);
	ASSERT_NEAR(1.5, folium.getS(), err);
	ASSERT_NEAR(sqrt(4 * sqrt(3) - 6), folium.getDiameter(), err);
	ASSERT_NEAR(3 / sqrt(6), folium.getDiamdist0(), err);
	ASSERT_NEAR(0.0, folium.distToCenter(PI / 4 + PI / 4), err);
	ASSERT_NEAR(0.0, folium.distToCenter(PI / 4 - PI / 4), err);
	ASSERT_NEAR(3 * 0.418593, folium.distToCenter(PI / 4 + PI / 8), err);
	ASSERT_NEAR(3 * 0.418593, folium.distToCenter(PI / 4 - PI / 8), err);
}

TEST(FormulasComparison) {
	CartesianFolium folium;
	const double err = 0.00001;
	double checkFactors[3] = {
		2.5, -2.5, 0.0
	};
	for (int i = 0; i < sizeof(checkFactors) / sizeof(checkFactors[0]); i++) {
		double checkFactor = checkFactors[i];
		folium.setFactor(checkFactor);
		double l = folium.maxChordLen();
		ASSERT_NEAR(checkFactor, folium.getFactor(), err);
		ASSERT_NEAR(abs(folium.getFactor()) / sqrt(2), l, err);
		ASSERT_NEAR(l / 8, folium.getRx(), err);
		ASSERT_NEAR(l / sqrt(2), folium.getR0(), err);
		ASSERT_NEAR(l * l / 3.0, folium.getS(), err);
		ASSERT_NEAR(2 * l * sqrt(2 * sqrt(3) - 3) / 3, folium.getDiameter(), err);
		ASSERT_NEAR(l / sqrt(3), folium.getDiamdist0(), err);
	}
}

int _tmain(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}