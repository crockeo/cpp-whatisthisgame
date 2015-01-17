#include "animation.hpp"

//////////
// Code //

// Calculating the current frame index.
unsigned int Animation::calcCurrentFrameIndex() const {
    return 0;
}

// Creating a new animation with its frames, its frame length, and if it
// ought to loop.
Animation::Animation(std::vector<Texture> textures, float frameLength, bool doesLoop) {
    this->textures    = textures;
    this->frameLength = frameLength;
    this->isOriginal  = true;
    this->doesLoop    = doesLoop;
}

// Creating a new animation with all of the above, assuming that it will
// want to loop.
Animation::Animation(std::vector<Texture> textures, float frameLength) :
        Animation(textures, frameLength, true) { }

// Overriding the default copy constructor.
Animation::Animation(const Animation& anim) {
    this->textures    = anim.textures;
    this->frameLength = anim.frameLength;
    this->isOriginal  = false;
    this->doesLoop    = anim.doesLoop;
}

// Destroying this thingy.
Animation::~Animation() {
    if (this->isOriginal)
        delete this->timer;
}

// Getting the timer that exists
Timer* Animation::getTimer() { return this->timer; }

// Getting the current frame of an animation.
Texture Animation::getCurrentFrame() const {
    return this->textures.at(this->calcCurrentFrameIndex());
}

// Getting the current texture ID.
GLuint Animation::getID() const { return this->getCurrentFrame().getID(); }
