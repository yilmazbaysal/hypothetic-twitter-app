#include "User.h"

#include "TextPost.h"
#include "ImagePost.h"

User::User(string userName, string personalComment) {
    this->userName = userName;
    this->personalComment = personalComment;

    posts = new LinkedList<Post>();
    following = new LinkedList<User>();
    blocked = new LinkedList<User>();
}

string User::getId() {
    return userName;
}

LinkedList<Post>* User::getPosts() {
    return posts;
}

// Add text post
void User::addPost(string id, string tweet) {
    if(posts->isContain(id)) {
        io->writeError("the post had already been added");
        return;
    }

    Post* newPost = new TextPost(id, tweet); //It will deallocated in LinkedList
    posts->add(newPost);
}

// Add image post
void User::addPost(string id, string tweet, int imageSize) {
    if(posts->isContain(id)) {
        io->writeError("the post had already been added");
        return;
    }

    Post* newPost = new ImagePost(id, tweet, imageSize); //It will deallocated in LinkedList
    posts->add(newPost);
}

void User::followUser(User* user2) {
    if(user2->blocked->isContain(userName)) { // If the user2 had blocked user1
        io->writeError("the user '" + user2->getId() + "' had blocked '" + userName + "'");
    }
    else if(following->isContain(user2->getId())) {
        io->writeError(userName + " has already followed " + user2->getId());
    }
    else if(user2->getId() == userName) {
        io->writeError("You cannot follow yourself");
    }
    else {
        following->add(user2);

        io->writeLine(userName + " followed " + user2->getId());
    }
}

void User::unFollowUser(User* user2) {
    if(!following->isContain(user2->getId())) {
        io->writeError(user2->getId() + " has already been unfollowed by you!"
                + " You cannot unfollow again");
        return;
    }

    following->deleteItem(user2->getId()); //Unfollow

    io->writeLine(user2->getId() + " has been unfollowed by " + userName);
}

void User::blockUser(User* user2) {
    if(blocked->isContain(user2->getId())) {
        io->writeError(userName + " has already blocked " + user2->getId());
        return;
    }
    else if(user2->getId() == this->userName) {
        io->writeError("You (" + userName + ") cannot block yourself");
        return;
    }
    blocked->add(user2);

    // Delete the likes of blocked user
    for(int i = 0; i < posts->getNumberOfItems(); i++) {
        posts->getByIndex(i)->getLikedUsers()->deleteItem(user2->getId());
    }

    // If the blocked user following this user, remove the connection
    if(user2->following->isContain(this->userName)) {
        user2->following->deleteItem(this->userName);
    }

    io->writeLine(userName + " has blocked " + user2->getId());
}

void User::likePost(User* likedUser, string likedPostId) {
    //Check if the post exists or not
    if(!likedUser->getPosts()->isContain(likedPostId)) {
        io->writeError(likedUser->getId() + "'s post could not be found");
    }
    //Check if the post already liked by this user or not
    else if(likedUser->getPosts()->get(likedPostId)->getLikedUsers()->isContain(userName)) {
        io->writeError(likedUser->getId() + "'s post had already been liked");
    }
    //Check if user2 blocked this user or not
    else if(likedUser->blocked->isContain(userName)) {
        io->writeError("The user '" + likedUser->getId() + "' had blocked '" + userName
                + "'. You cannot like a post of '" + likedUser->getId() + "'");
    }
    //If there is no error, like the post
    else {
        likedUser->posts->get(likedPostId)->likedBy(this);

        io->writeLine(userName + " has liked " + likedUser->getId() + "'s post");
    }
}

void User::repost(User* repostedUser, string repostedId) {
    //Check if the post exists or not
    if(!repostedUser->getPosts()->isContain(repostedId)) {
        io->writeError(repostedUser->getId() + "'s post could not be found");
    }
    //Check if this user has a post with the same id
    else if(posts->isContain(repostedId)) {
        io->writeError("The user '" + userName + "' already has a post with the same id");
    }
    //Check if user2 blocked this user
    else if(repostedUser->blocked->isContain(this->userName)) {
        io->writeError("The user '" + repostedUser->getId() + "' had blocked '" + this->userName
                + "'. You cannot repost a post of '" + repostedUser->getId() + "'");
    }
    //If there is no error, repost it
    else {
        Post* newPost;

        if(repostedUser->posts->get(repostedId)->getType() == "TextPost") {
            newPost = new TextPost();
        }
        else if(repostedUser->posts->get(repostedId)->getType() == "ImagePost") {
            newPost = new ImagePost();
        }

        *newPost = *repostedUser->posts->get(repostedId);
        newPost->returnInitial(); // Delete the likes of new post
        posts->add(newPost); // Add the new post to the list

        io->writeLine(userName + " has reposted " + repostedUser->getId() + "'s post");
    }
}

string User::toString() {
    ostringstream oss;
    oss << endl << "------------------------------------------------" << endl;
    oss << userName << " following [" << following->getNumberOfItems();
    oss << "] - blocked [" << blocked->getNumberOfItems() << "] users - [";
    oss << posts->getNumberOfItems() << "] posts." << endl;
    oss << personalComment << endl;
    oss << "---------------------Tweets---------------------" << endl;
    oss << posts->toString();
    oss << "------------------------------------------------";
    return oss.str();
}

User::~User() {
    posts->free(); //Free the allocated memory for each Node

    delete posts;
    delete blocked;
    delete following;
}
