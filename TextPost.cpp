#include "TextPost.h"

TextPost::TextPost(string id, string tweet): Post(id, tweet) {
}

string TextPost::toString() {
	ostringstream oss;
    oss << tweet << " - Likes: " << likedUsers->getNumberOfItems();
	return oss.str();
}

string TextPost::getType() {
	return "TextPost";
}
