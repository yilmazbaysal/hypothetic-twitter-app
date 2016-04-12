#include "Post.h"
#include "User.h"

Post::Post(string id, string tweet) {
    likedUsers = new LinkedList<User>();

	this->id = id;
	this->tweet = tweet;
}

void Post::returnInitial() {
	delete likedUsers;
    likedUsers = new LinkedList<User>();
}

string Post::getId() {
	return id;
}

LinkedList<User>* Post::getLikedUsers() {
	return likedUsers;
}

// Adds the user who liked this post to the list
void Post::likedBy(User* user) {
    likedUsers->add(user);
}

Post::~Post() {
    delete likedUsers;
}

