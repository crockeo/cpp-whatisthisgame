#ifndef _RES_ANIMATION_HPP_
#define _RES_ANIMATION_HPP_

//////////////
// Includes //
#include <vector>

#include "../timer.hpp"
#include "texable.hpp"
#include "texture.hpp"

//////////
// Code //

// A class to represent an animation.
class Animation : public Texable {
private:
    std::vector<Texture> textures;
    float frameLength;
    bool isOriginal;
    bool doesLoop;
    Timer* timer;

    // Calculating the current frame index.
    unsigned int calcCurrentFrameIndex() const;

public:
    // Creating a new animation with its frames, its frame length, and if it
    // ought to loop.
    Animation(std::vector<Texture>, float, bool);

    // Creating a new animation with all of the above, assuming that it will
    // want to loop.
    Animation(std::vector<Texture>, float);

    // Overriding the default copy constructor.
    Animation(const Animation&);

    // Destroying this thingy.
    ~Animation();

    // Getting the timer that exists
    Timer* getTimer();

    // Getting the current frame of an animation.
    Texture getCurrentFrame() const;

    // Getting the current texture ID.
    GLuint getID() const override;
};

#endif
