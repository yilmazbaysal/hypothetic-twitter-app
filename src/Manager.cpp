#include "Manager.h"
#include "Post.h"
#include <stdlib.h>

Manager::Manager() {
    io->openFiles();

    users = new LinkedList<User>();
}

void Manager::operateInputs() {
    string operation;
    string userName1;

    while(!io->isEndOfFile()) {
        stringstream ss(io->readLine());

        ss >> operation >> userName1;

        if(operation == "AddUser") {
            string comment;
            ss >> comment;
            addUser(userName1, comment);
        }
        else if(!users->isContain(userName1)) { // Control if the user1 exists or not
            io->writeError("the user '" + userName1 + "' could not be found");
        }
        else if(operation == "AddPost") {
            string postId, tweet, image;

            ss >> postId >> tweet;

            if(ss >> image) { // If it is a ImagePost
                users->get(userName1)->addPost(postId, tweet, calcImageSize(image));
            }
            else { // If it is a TextPost
                users->get(userName1)->addPost(postId, tweet);
            }
        }
        else if(operation == "ViewUser") {
            viewUser(userName1);
        }
        else { // All operations that need a user2
            string userName2;
            ss >> userName2;

            if(!users->isContain(userName2)) { // Check if the user2 exists or not
                io->writeError("the user '" + userName2 + "' could not be found");
            }
            else if(operation == "FollowUser") {
                users->get(userName1)->followUser(users->get(userName2));
            }
            else if(operation == "UnfollowUser") {
                users->get(userName1)->unFollowUser(users->get(userName2));
            }
            else if(operation == "BlockUser") {
                users->get(userName1)->blockUser(users->get(userName2));
            }
            else { // All operations that need a postId
                string postId;
                ss >> postId;

                if(operation == "LikePost") {
                    users->get(userName1)->likePost(users->get(userName2), postId);
                }
                else if(operation == "Repost") {
                    users->get(userName1)->repost(users->get(userName2), postId);
                }
            }
        }
    }
}

void Manager::addUser(string userName, string personalComments) {
    if(users->isContain(userName)) { // Check if a user exists with the same id
        io->writeError("The user " + userName + " has already been created");
        return;
    }

    User* user = new User(userName, personalComments); // (Will be deallocated in LinkedList's free() method)
    users->add(user);

    io->writeLine("User '" + userName + "' has been created");
}

void Manager::viewUser(string userName) {
    io->writeLine(users->get(userName)->toString());
}

// Calculates size of the string that is formatted as "AxB" (value of A*B)
// A represents width and B represents height
int Manager::calcImageSize(string image) {
    string width, height;
    bool isWidthEnd = false;

    for(int i = 0; (unsigned)i < image.length(); i++) {
        if(image[i] == 'x') { // Pass the 'x' character
            isWidthEnd = true;
            i++;
        }

        if(!isWidthEnd) {
            width += image[i];
        }
        else {
            height += image[i];
        }
    }

    return atoi(width.c_str())*atoi(height.c_str());
}

Manager::~Manager() {
    io->closeFiles();

    users->free();
    delete users;
}
