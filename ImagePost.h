#ifndef IMAGEPOST_H_
#define IMAGEPOST_H_

#include "Post.h"

class ImagePost: public Post {
public:
	ImagePost(string, string, int);
	ImagePost() { };

	string toString();
	string getType();

private:
	int imageSize;
};

#endif /* IMAGEPOST_H_ */
