#include "InputOutput.h"

ifstream iFile;
ofstream oFile;

void InputOutput::openFiles() {
    iFile.open("input.txt");
	oFile.open("out.txt");
}

// Writes the given string to both file and console as a line
void InputOutput::writeLine(string line) {
    cout << line << endl;
    oFile << line << endl;
}

// Writes the given error message to both file and console as a line
void InputOutput::writeError(string line) {
    cout << "Err: " << line << "!" << endl;
    oFile << "Err: " << line << "!" << endl;
}

string InputOutput::readLine() {
    string str;
    getline(iFile, str);
    return str;
}

// Returns true, if iFile pointer reaches at the end of the file
bool InputOutput::isEndOfFile() {
    return iFile.eof();
}

void InputOutput::closeFiles() {
	iFile.close();
	oFile.close();
}

