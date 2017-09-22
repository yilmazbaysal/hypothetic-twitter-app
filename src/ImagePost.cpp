#include "ImagePost.h"

ImagePost::ImagePost(string id, string tweet, int imageSize): Post(id, tweet) {
    this->imageSize = imageSize;
}

string ImagePost::toString() {
    ostringstream oss;
    oss << tweet << " - TotalSize: [" << imageSize;
    oss << " pixels] - Likes: " << likedUsers->getNumberOfItems();
    return oss.str();
}

string ImagePost::getType() {
    return "ImagePost";
}
