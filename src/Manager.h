#ifndef MANAGER_H_
#define MANAGER_H_

#include "InputOutput.h"
#include "LinkedList.h"
#include "User.h"

#include <string>

using namespace std;

class Manager {
    public:
        Manager();
        virtual ~Manager();

        void operateInputs();
        void addUser(string, string);
        void viewUser(string);

    private:
        LinkedList<User>* users;
        InputOutput* io;

        int calcImageSize(string);
};

#endif /* MANAGER_H_ */
