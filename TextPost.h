#ifndef TEXTPOST_H_
#define TEXTPOST_H_

#include "Post.h"

class TextPost: public Post {
public:
	TextPost(string, string);
	TextPost() { };

	string toString();
	string getType();
};

#endif /* TEXTPOST_H_ */
