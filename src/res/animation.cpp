#include "animation.hpp"

//////////
// Code //

// Calculating the current frame index.
unsigned int Animation::calcCurrentFrameIndex() const {
    int frame = this->timer->getTime() / frameLength;
    if (frame >= this->textures.size())
        return this->textures.size() - 1;
    return frame;
}

// Creating a new animation with its frames, its frame length, and if it
// ought to loop.
Animation::Animation(std::vector<Texture> textures, float frameLength, bool doesLoop) {
    this->textures    = textures;
    this->frameLength = frameLength;
    this->isOriginal  = true;
    this->doesLoop    = doesLoop;

    if (this->doesLoop)
        this->timer = std::make_shared<Timer>(this->textures.size() * this->frameLength);
    else
        this->timer = std::make_shared<Timer>();
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
    this->timer       = anim.timer;
}

// Getting the timer that exists
std::shared_ptr<Timer> Animation::getTimer() { return this->timer; }

// Getting the current frame of an animation.
Texture Animation::getCurrentFrame() const {
    return this->textures.at(this->calcCurrentFrameIndex());
}

// Getting the current texture ID.
GLuint Animation::getID() const { return this->getCurrentFrame().getID(); }

// Getting the texture coordinates.
std::vector<GLfloat> Animation::getTextureCoords() const {
    return this->getCurrentFrame().getTextureCoords();
}
