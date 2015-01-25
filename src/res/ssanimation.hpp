#ifndef _RES_SSANIMATION_HPP_
#define _RES_SSANIMATION_HPP_

//////////////
// Includes //
#include <memory>
#include <tuple>

#include "spritesheet.hpp"
#include "../timer.hpp"
#include "texable.hpp"

//////////
// Code //

// An animation class.
class SSAnimation : public Texable {
private:
    std::shared_ptr<Timer> timer;
    Spritesheet spritesheet;
    float frameLength;
    bool loop;

    // Getting the current frame of the animation.
    std::tuple<int, int> getCurrentFrame() const;

public:
    // Constructing an animation from a spritesheet explicitly saying whether or
    // not it loops.
    SSAnimation(Spritesheet, float, bool);

    // Constructing an animation from a spritesheet.
    SSAnimation(Spritesheet, float);

    // Getting the texture ID of the SSAnimation.
    GLuint getID() const override;

    // Getting the texture coordinates of this thingy.
    std::vector<GLfloat> getTextureCoords() const override;

    // Getting the timer for this animation.
    std::shared_ptr<Timer> getTimer();
};

#endif
