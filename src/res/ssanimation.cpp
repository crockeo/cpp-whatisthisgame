#include "ssanimation.hpp"

//////////
// Code //

// Getting the current frame of the animation.
std::tuple<int, int> SSAnimation::getCurrentFrame() const {
    int index = this->timer->getTime() / this->frameLength;
    int col, row;

    row = index / this->spritesheet.getCols();
    col = index - this->spritesheet.getCols() * row;

    return std::make_tuple(col, row);
}

// Constructing an animation from a spritesheet explicitly saying whether or
// not it loops.
SSAnimation::SSAnimation(Spritesheet spritesheet, float frameLength, bool loop) :
        spritesheet(spritesheet) {
    this->frameLength = frameLength;
    this->timer = std::make_shared<Timer>(this->spritesheet.getCols() * this->spritesheet.getRows() * this->frameLength);
    this->loop = loop;
}

// Constructing an animation from a spritesheet.
SSAnimation::SSAnimation(Spritesheet ss, float frameLength) :
        SSAnimation(ss, frameLength, true) { }

// Getting the texture ID of the SSAnimation.
GLuint SSAnimation::getID() const { return this->spritesheet.getID(); }

// Getting the texture coordinates of this thingy.
std::vector<GLfloat> SSAnimation::getTextureCoords() const {
    auto t = this->getCurrentFrame();
    return this->spritesheet.getTextureCoordsAt(std::get<0>(t), std::get<1>(t));
}

// Getting the timer for this animation.
std::shared_ptr<Timer> SSAnimation::getTimer() { return this->timer; }
