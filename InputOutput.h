#ifndef INPUTOUTPUT_H_
#define INPUTOUTPUT_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class InputOutput {
public:
    void openFiles();
    void writeLine(string);
    void writeError(string);
    string readLine();
    bool isEndOfFile();
	void closeFiles();
};

#endif /* INPUTOUTPUT_H_ */
