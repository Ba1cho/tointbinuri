#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int binaryToDecimal(const string& binary) {
	int decimal = 0;
	int len = binary.length();

	for (int i = 0; i < len; ++i) {
		if (binary[i] == '1') {
			decimal += pow(2, len - i - 1);
		}
		else if (binary[i] != '0') {
			return -1;
		}
	}

	return decimal;
}

int main() {
	ifstream inputFile("os27_tolmachev_task1.csv");
	if (!inputFile.is_open()) {
		cout << "Unable to open input file." << endl;
		return 1;
	}

	ofstream outputFile("result2.csv");
	if (!outputFile.is_open()) {
		cout << "Unable to create output file." << endl;
		return 1;
	}

	string line;
	bool flag = false;
	while (getline(inputFile, line)) {
		stringstream ss(line);
		vector<string> tokens;

		while (ss.good()) {
			string token;
			getline(ss, token, ',');
			tokens.push_back(token);
		}

		if (tokens.size() != 1) {
			outputFile << line << ",Error: Incorrect format" << endl;
			continue;
		}

		string binaryNumber = tokens[0];
		if (binaryNumber[0] == '1') {
			flag = true;
			binaryNumber[0] = '0';
		}

		int decimalNumber = binaryToDecimal(binaryNumber);
		if (flag)
			decimalNumber *= -1;

		if (decimalNumber >= 0) {

			outputFile << line << "," << fixed << setprecision(2) << decimalNumber << endl;
		}
		else {
			outputFile << line << ",Error: Invalid binary number" << endl;
		}
		flag = false;
	}

	inputFile.close();
	outputFile.close();

	return 0;
}