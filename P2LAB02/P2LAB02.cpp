#include "pch.h"
#include <iostream>
#include <map>
#include <string>
#include <regex>

using namespace std;

class BigNumber {
	string number;
	string text;
	static std::map<char, int> shortScale;

	static string TextToNumber(string input)
	{
		int scale = shortScale[input.back()];
		string convertedInput = input.substr(0, input.length() - 1);
		unsigned int dotPosition = convertedInput.find(".");
		vector<char> result;
		for (string::size_type i = 0; i < convertedInput.size(); ++i) {
			if (i > dotPosition)
			{
				scale--;
			}
			result.insert(result.end(), convertedInput[i]);
		}
		for (int i = 0; i < scale; i++)
		{
			result.insert(result.end(), '0');
		}
		return string(result.begin(), result.end());
	}
public:
	static void initializeMap()
	{
		shortScale['Y'] = 24;
		shortScale['Z'] = 21;
		shortScale['E'] = 18;
		shortScale['P'] = 15;
		shortScale['T'] = 12;
		shortScale['G'] = 9;
		shortScale['M'] = 6;
		shortScale['k'] = 3;
	}

	static bool isShortScaleChar(string &input)
	{
		char SIUnit = input.back();
		return shortScale.count(SIUnit) != 0;
	}

	static int getScaleFromUnitChar(char unit)
	{
		return shortScale.count(unit) != 0;
	}

	static bool isBigNumber(string &input)
	{
		const regex checker("([0-9]+)(|\\.[0-9]+|\\.)([a-zA-Z]{1}$)");
		return regex_match(input, checker);
	}

	BigNumber(string input)
	{
		text = input;
		number = TextToNumber(input);
	}

	string getNumber()
	{
		return number;
	}
	bool operator == (string comparedNumber)
	{
		return comparedNumber == number;
	}
};

std::map<char, int> BigNumber::shortScale;

 class Assert
{
public:
	static bool areEqual(string number, BigNumber object)
	{
		return object == number;
	}
};

int main()
{
	BigNumber::initializeMap();
	BigNumber trillionBig("1T");
	BigNumber millionBig("3M");
	cout << trillionBig.getNumber() << endl;
	cout << millionBig.getNumber() << endl;
	cout << Assert::areEqual("1000000", trillionBig) << endl;
	cout << Assert::areEqual("3000000", millionBig) << endl;
	cout << (millionBig == "1000000") << endl;
	cout << (millionBig == "3000000") << endl;
}
