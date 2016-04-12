#ifndef USER_H_
#define USER_H_

#include "InputOutput.h"
#include "LinkedList.h"
#include "Post.h"
#include "ImagePost.h"
#include "TextPost.h"

#include <string>
#include <sstream>

using namespace std;

class User {
public:
	User(string, string);
	User() { };
	virtual ~User();

	string getId();
	LinkedList<Post>* getPosts();

	void addPost(string, string); // Text post
	void addPost(string, string, int); // Image post
	void followUser(User*);
	void unFollowUser(User*);
	void blockUser(User*);
	void repost(User*, string);
	void likePost(User*, string);

	string toString();

private:
	string userName;
	string personalComment;

	LinkedList<Post>* posts;

	LinkedList<User>* following;
	LinkedList<User>* blocked;

	InputOutput* io;
};

#endif /* USER_H_ */
