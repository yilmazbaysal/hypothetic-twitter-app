#ifndef POST_H_
#define POST_H_

#include <string>
#include <sstream>

#include "LinkedList.h"
class User;

using namespace std;

class Post {
public:
	Post(string, string);
	Post() { };
	virtual ~Post();

	virtual string toString() = 0;
	virtual string getType() = 0;

	string getId();
	void setId(int);
    LinkedList<User>* getLikedUsers();

	void likedBy(User* user);

	void returnInitial();

protected:
	string id;
	string tweet;

	LinkedList<User>* likedUsers;
};

#endif /* POST_H_ */
