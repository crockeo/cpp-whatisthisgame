#ifndef _RES_ANIMATION_HPP_
#define _RES_ANIMATION_HPP_

//////////////
// Includes //
#include <memory>
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
    std::shared_ptr<Timer> timer;
    float frameLength;
    bool isOriginal;
    bool doesLoop;

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

    // Getting the timer that exists
    std::shared_ptr<Timer> getTimer();

    // Getting the current frame of an animation.
    Texture getCurrentFrame() const;

    // Getting the current texture ID.
    GLuint getID() const override;

    // Getting the texture coordinates.
    std::vector<GLfloat> getTextureCoords() const override;
};

#endif
