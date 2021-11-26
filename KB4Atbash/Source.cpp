#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

string encode(string line, string alphaUpp, string alphaLow) {
	string res = "";
	for (int i = 0; i < line.length(); i++) {
		char upp = toupper(line[i]);
		char low = tolower(line[i]);
		if ((line[i] != ' ') && (string("^[._^%$#!~@,-]+$").find(line[i]) == string::npos)) {
			if ((low != line[i]) && (upp != line[i])) return " ";
			int indLow = alphaLow.find(low);
			int indUpp = alphaUpp.find(upp);
			if (indLow != -1) {
				res += alphaLow[alphaLow.size() - indLow - 1];
			}
			else {
				res += alphaUpp[alphaUpp.size() - indUpp - 1];
			}
		}
		else {
			res += line[i];
		}
	}
	return res;
}

int main() {
	system("chcp 1251");
	setlocale(LC_ALL, "RUS");
	cout << (string("abc").find("5") == string::npos) << "\n";
	string urlAlphabet;
	cout << "Url to alphabet file\n";
	cin >> urlAlphabet;
	ifstream alphabet;
	alphabet.open(urlAlphabet);
	string alphaLetters = "";
	getline(alphabet, alphaLetters);
	cout << alphaLetters << "\n";
	string alphaLettersUpp = alphaLetters.substr();
	std::transform(alphaLettersUpp.begin(), alphaLettersUpp.end(), alphaLettersUpp.begin(), toupper);
	string alphaLettersLow = alphaLetters.substr();
	std::transform(alphaLettersLow.begin(), alphaLettersLow.end(), alphaLettersLow.begin(), tolower);
	string urlIn, urlOut;
	cout << "Url to input file\n";
	cin >> urlIn;
	cout << "Url to output file\n";
	cin >> urlOut;
	ifstream input;
	input.open(urlIn);
	vector<string> inS = {};
	while (!input.eof()) {
		string temp;
		getline(input, temp);
		inS.push_back(temp);
	}
	input.close();
	ofstream output;
	output.open(urlOut);
	string res = "";
	vector<string> enc = {};
	bool fl = false;
	for (int i = 0; i < inS.size(); i++)
	{
		string temp = encode(inS[i], alphaLettersUpp, alphaLettersUpp);
		if (temp.compare(" ") == 0) fl = true;
		res += temp;
	}
	cout << res << "\n";
	if (fl) {
		cout << "Failed to complete the task";
		output << "Failed to complete the task";
	}
	else {
		output << res << "\n";
		cout << res << "\n";
	}
	output.close();
	return 0;
}