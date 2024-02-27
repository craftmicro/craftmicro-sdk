# Ply Sprite

A Ply Sprite is a layered sprite format optimised for size.

Normally in sprite sheets, each frame of animation is one tile. For example, an 8-frame animation of a figure walking will have 8 tiles, each with the figure in a slightly different position. Here is an example of a sprite sheet with 3 animations: stand, scratch and walk, with 11 total frames. 

![Ninja as a Sprite Sheet](img/ninja-spritesheet.png?raw=true "Ninja as a Sprite Sheet")

_102x55 pixels (5,610 pixels)_

This is inefficient because large portions of the sprite remain the same between frames. The body goes up and down but remains the same, while only the eyes, arms and legs change between frames. In a Ply Sprite the body would be one layer (ply) and the moving parts are each layers on top of (or behind) the body as separate plys. The sprite sheet will only save one image of the body, and then only changes to the arms, legs and eyes animating, which are much smaller, saving a large amount of space and memory.

![Ninja as a Ply Sprite](img/ninja-plysprite.png?raw=true "Ninja as a Ply Sprite")

_31x30 pixels (930 pixels)_

As you can see, the ply sprite in this case is over 6 times smaller. A ply sprite can even re-use a part that has been mirrored and/or rotated. Only one image will be stored, and it will be transformed when it is rendered, saving even more space.

The script [ply-sprite.lua](ply-sprite.lua) lets you export Ply Sprites directly from Aseprite.

Of course, to create a ply sprite you need to draw it in a certain way to begin with.

## Example

- [See the Ply Sprite example here](/examples/011-ply-sprite/main.cpp)

## To add the script to Aseprite

- Open Aseprite
- Go to `File > Scripts > Open scripts folder`
- Copy `ply-sprite.lua` to the folder
- Go to `File > Scripts > Rescan scripts folder`
- The script is now available. To run it, go to `File > Scripts > ply-sprite`

## To draw and use a Ply Sprite

- Only indexed color mode is supported
- Draw each part of the animation on a different layer
- Draw all animations (stand, run, walk, etc) on the same timeline
- Create loop sections for each animation on the timeline, and give each a name (like Stand, Walk, Run, Fall etc)
- Optionally, check the sprite by running the script and export the ply sprite in `Sizzle - debug` format
    - An image and a JSON file are generated in the same folder as the aseprite file
    - Open the image and check that the plys are being re-used correctly
- Run the script and export the ply sprite in `CraftMicro SDK` format
    - A header file is generated in the same folder as the aseprite file
    - Copy it to your project, include it, and then use it when you create a Ply Sprite

![Aseprite screenshot](img/aseprite-screenshot-1.png?raw=true "Aseprite screenshot")

This screenshot of Aseprite shows a Ply Sprite being created. There is a separate layer for the body, the eyes (they blink) the arms and legs. You can also see three loop sections for three different animations - Stand, Scratch and Walk. This animation can be seen in action in the example above.

## Anchor

You can set the anchor point of each animation.

- Create a layer called `_anchor`
- For each loop section, draw a little 3x3 arrow pointing at the anchor point
    - It can point at any of the 4 corner directions
    - It may be any color (or multi-colored!)
    - But it must be the same shape as in the image below

![Aseprite anchor screenshot](img/aseprite-screenshot-2.png?raw=true "Aseprite anchor screenshot")
