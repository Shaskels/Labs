#include "pch.h"
#include "..\PrisDillema\Modes.h"
#include "..\PrisDillema\Factory.h"

std::vector<std::string> x = { "321", "CCD", "DCC", "DDC", "CCC" };
std::vector<std::string> y = { "312", "CDD", "DCD", "DDC", "DDD" };


std::string diractory = "..";

TEST(Strateg, AlwaysSayYes_ReturnsYes) {
	alwaysSayYesFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = (*Prisoner).makeDecision(x, 1, diractory);
	ASSERT_EQ('C', answer);
}
TEST(Strateg, AlwaysSayNo_ReturnsNo) {
	alwaysSayNoFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1, diractory);
	ASSERT_EQ('D', answer);
}
TEST(Strateg, EyeForEyeFactory_ReturnsYes) {
	eyeForEyeFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1, diractory);
	ASSERT_EQ('C', answer);
}
TEST(Strateg, EyeForEyeFactory_ReturnsNo) {
	eyeForEyeFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(y, 1, diractory);
	ASSERT_EQ('D', answer);
}
TEST(Strateg, Statistician_ReturnsYes) {
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1, diractory);
	ASSERT_EQ('C', answer);
}
TEST(Strateg, Statistician_ReturnsNo) {
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(y, 1, diractory);
	ASSERT_EQ('D', answer);
}
TEST(Strateg, TheEqualizer_ReturnsYes) {
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1, diractory);
	ASSERT_EQ('C', answer);
}
TEST(Strateg, TheEqualizer_ReturnsNo) {
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(y, 2, diractory);
	ASSERT_EQ('D', answer);
}
TEST(Strateg, ThePredictor_ReturnsNo) {
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1, diractory);
	ASSERT_EQ('C', answer);
}
TEST(Strateg, ThePredictor_ReturnsYes) {
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(y, 1, diractory);
	ASSERT_EQ('D', answer);
}
TEST(Modes, MakePrisoners_Returns) {
	std::vector <Strategies*> Prisoner;
	std::vector <int> names = { 1,3,4 };
	alwaysSayYesFactory factory1;
	Prisoner.push_back(factory1.makeStrategies());
	randomFactory factory2;
	Prisoner.push_back(factory2.makeStrategies());
	eyeForEyeFactory factory3;
	Prisoner.push_back(factory3.makeStrategies());
	std::vector <Strategies*> P = MakePrisoners(names);
	ASSERT_EQ((*Prisoner[0]).makeDecision(x, 1, diractory), (*P[0]).makeDecision(x, 1, diractory));
	ASSERT_EQ((*Prisoner[1]).makeDecision(x, 1, diractory), (*P[1]).makeDecision(x, 1, diractory));
	ASSERT_EQ((*Prisoner[2]).makeDecision(x, 1, diractory), (*P[2]).makeDecision(x, 1, diractory));
}
TEST(Modes, IsDigit_ReturnsTrue) {
	std::string c = "535";
	bool k = isDigit(c);
	ASSERT_EQ(true, k);
}
TEST(Modes, IsDigit_ReturnsFalse) {
	std::string c = "5Fd";
	bool k = isDigit(c);
	ASSERT_EQ(false, k);
}
TEST(Modes, MakeGameMatrix_ReturnsError) {
	int k = MakeGameMatrix("GameMatrix2.txt");
	ASSERT_EQ(1, k);
}
