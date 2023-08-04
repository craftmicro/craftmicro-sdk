--
-- Create a layered sprite, compatible with the CraftMicro SDK
--

-- There must be a sprite
local sprite = app.activeSprite
if sprite == nil then
    return app.alert("ERROR: There is no active sprite")
end
if sprite.colorMode ~= ColorMode.INDEXED then
    return app.alert("ERROR: Only indexed sprites are supported at this time")
end

-- Individual parts
local parts = {}

-- Number of pixels across all parts
local partsArea = 0

-- Animations
local animations = {}

-- Slugify a string
slugify = function(str)
    return string.gsub(string.gsub(string.lower(str),"[^ a-z0-9]",""),"[ ]+","-")
end

-- Function to compare images
ImageCompare = {
    Different = -1,
    Same = 0,
    FlipH = 1,
    FlipV = 2,
    Rot90 = 4,
}
pixelFromIndex = function(index, image)
    local y = math.floor(index/image.width)
    local x = index - y * image.width
    return image:getPixel(x, y)
end
compareImagePixels = function(source, dest, destStart, destStep, destStride)
    local total = source.width * source.height
    local steps = source.width
    local sourcePos = 0
    local destPos = destStart
    while total > 0 do
        if pixelFromIndex(sourcePos, source) ~= pixelFromIndex(destPos, dest) then
            return false
        end
        steps = steps - 1
        sourcePos = sourcePos + 1
        destPos = destPos + destStep
        if steps == 0 then
            steps = source.width
            destStart = destStart + destStride
            destPos = destStart
        end
        total = total - 1
    end
    return true
end
compareImages = function(part, compare)
    -- Check if image is right-side or possibly rotated based on size
    local checkNonRotated = false
    local checkRotated = false
    if part.image.width == compare.width and part.image.height == compare.height then 
        checkNonRotated = true
        if compare.width == compare.height then
            checkRotated = true
        end
    elseif part.image.width == compare.height and part.image.height == compare.width then 
        -- rotated
        checkRotated = true
    else
        return ImageCompare.Different;
    end

    -- Check right-side first
    if checkNonRotated then
        if compareImagePixels(part.image, compare, 0, 1, compare.width) then
            return ImageCompare.Same
        end
        if compareImagePixels(part.image, compare, compare.width-1, -1, compare.width) then
            return ImageCompare.FlipH
        end
        if compareImagePixels(part.image, compare, compare.width*(compare.height-1), 1, -compare.width) then
            return ImageCompare.FlipV
        end
        if compareImagePixels(part.image, compare, compare.width*compare.height-1, -1, -compare.width) then
            return ImageCompare.FlipH | ImageCompare.FlipV
        end
    end
    -- Check rotated second
    if checkRotated then
        if compareImagePixels(part.image, compare, compare.width-1, compare.width, -1) then
            return ImageCompare.Rot90
        end
        if compareImagePixels(part.image, compare, 0, compare.width, 1) then
            return ImageCompare.Rot90 | ImageCompare.FlipH
        end
        if compareImagePixels(part.image, compare, compare.width*compare.height-1, -compare.width, -1) then
            return ImageCompare.Rot90 | ImageCompare.FlipV
        end
        if compareImagePixels(part.image, compare, compare.width*(compare.height-1), -compare.width, 1) then
            return ImageCompare.Rot90 | ImageCompare.FlipH | ImageCompare.FlipV
        end
    end

    return ImageCompare.Different;
end

--
-- Step through all animations
--
-- If there are no tags, just one animation will be created of the entire sprite
-- If there are tags, parts of the sprite with no tag will be skipped. So either
-- ensure that you use tags for all animations, or no tags at all!

local tags = sprite.tags
if #tags == 0 then
    tags = {{
        name = "sprite",
        aniDir = AniDir.FORWARD,
        fromFrame = sprite.frames[1],
        toFrame = sprite.frames[#sprite.frames]
    }}
end

for _,tag in ipairs(tags) do
    animation = {direction = tag.aniDir, frames = {}}
    frame = tag.fromFrame
    while frame do
        layeredSprite = {index = frame.frameNumber - tag.fromFrame.frameNumber + 1, duration = frame.duration, parts = {}}

        -- Step through all layers
        for _,layer in ipairs(sprite.layers) do
            -- Get the cell
            local cel = layer:cel(frame.frameNumber)
            local bounds = cel.bounds

            -- Check against all parts to see if duplicate
            local part = nil
            local orientation = ImageCompare.Different
            for _, p in pairs(parts) do
                orientation = compareImages(p, cel.image)
                if orientation ~= ImageCompare.Different then
                    part = p
                    break
                end
            end

            if part == nil then
                -- Insert into parts
                part = {
                    index = #parts,
                    name = layer.name.."_"..frame.frameNumber,
                    layerName = layer.name,
                    frameNumber = frame.frameNumber,
                    image = cel.image
                }
                table.insert(parts, part)
                partsArea = partsArea + cel.image.width * cel.image.height
            end

            -- Add to layered sprite
            local sharedPart = {index = part.index, x = bounds.x, y = bounds.y, orientation = orientation}
            table.insert(layeredSprite.parts, sharedPart)
        end

        -- Add layered sprite to table
        table.insert(animation.frames, layeredSprite)

        -- Next frame
        frame = frame.next
        if frame and frame.frameNumber > tag.toFrame.frameNumber then
            frame = nil
        end
    end

    animations[tag.name] = animation
end

--
-- Prepare output file
--
local outputId = slugify(app.fs.fileTitle(sprite.filename))
local output = "#pragma once\n\n#include \"display/Sprite.h\"\n\nusing namespace craft;\n\n"

--
-- Output palette
--
-- TODO: Support non-indexed sprites by building a palette, including
-- matching/combining close colors (choose most frequently used match). 

local palette = sprite.palettes[1]
output = output.."// Palette ("..#palette.." entries)\n"
output = output.."static const uint32_t "..outputId.."_palette[] = {\n"
for i=0,#palette-1 do
    local c = palette:getColor(i)
    if i > 0 then
        output = output..",\n"
    end
    output = output.."\t0x"..string.format("%02x", c.alpha)..string.format("%02x", c.red)..string.format("%02x", c.green)..string.format("%02x", c.blue)
end
output = output.."\n};\n\n"

--
-- Output parts
--

for _, p in pairs(parts) do
    local count = 0
    local total = p.image.width * p.image.height
    output = output.."// "..p.name.." ("..total.." bytes)\n"
    output = output.."static const uint8_t "..outputId.."_part"..p.index.."_data[] = {\n"
    for y = 0, p.image.height-1 do
        for x = 0, p.image.width-1 do
            px = p.image:getPixel(x, y)
            if count % 16 == 0 then
                output = output.."\t"
            end
            output = output.."0x"..string.format("%02x", px)
            count = count + 1
            if count < total then
                output = output..","
            end
            if count % 16 == 0 then
                output = output.."\n"
            end
        end
    end
    if count % 16 ~= 0 then
        output = output.."\n"
    end
    output = output.."};\n"
end

output = output.."\n// Part array ("..#parts.." parts)\n"
output = output.."static const LayeredSpritePart "..outputId.."_parts[] = {\n"
for _, p in pairs(parts) do
    output = output.."\t{\n"
    output = output.."\t\t.width = "..p.image.width..",\n"
    output = output.."\t\t.height = "..p.image.height..",\n"
    output = output.."\t\t.anchorX = 0,\n"
    output = output.."\t\t.anchorY = 0,\n"
    output = output.."\t\t.partData = "..outputId.."_part"..p.index.."_data\n"
    output = output.."\t}"
    if p.index < (#parts-1) then
        output = output..","
    end
    output = output.."\n"
end
output = output.."};\n\n"

--
-- Animations
--

animDirectionEnum = function(index)
    if index == 1 then
        return "AnimationDirection::Reverse"
    elseif index == 2 then
        return "AnimationDirection::PingPong"
    end
    return "AnimationDirection::Forward"
end

animOrientationEnum = function(index)
    local s = {}
    if index & 1 then
        table.insert(s, "Transform::FlipH")
    end
    if index & 2 then
        table.insert(s, "Transform::FlipV")
    end
    if index & 4 then
        table.insert(s, "Transform::Rotate90")
    end
    if #s == 0 then
        table.insert(s, "Transform::None")
    end
    return table.concat(s, " | ")
end

local animIndex = 0
for name, a in pairs(animations) do
    local frameIndex = 0
    for _, f in ipairs(a.frames) do
        output = output.."\n// Animation '"..name.."' frame "..frameIndex.." layers ("..#f.parts.." layers)\n"
        output = output.."static const LayeredSpriteLayer "..outputId.."_anim"..animIndex.."_layer"..frameIndex.."_data[] = {\n"
        local count = 0
        for _, p in pairs(f.parts) do
            output = output.."\t{\n"
            output = output.."\t\t.partIndex = "..p.index..",\n"
            output = output.."\t\t.orientation = "..animOrientationEnum(p.orientation)..",\n"
            output = output.."\t\t.x = "..p.x..",\n"
            output = output.."\t\t.y = "..p.y.."\n"
            output = output.."\t}"
            count = count + 1
            if count < #f.parts then
                output = output..","
            end
            output = output.."\n"
        end
        output = output.."};\n\n"
        frameIndex = frameIndex + 1
    end

    output = output.."\n// Animation '"..name.."' frames array ("..#a.frames.." frames)\n"
    output = output.."static const LayeredSpriteFrame "..outputId.."_anim"..animIndex.."_frames[] = {\n"
    local count = 0
    local frameIndex = 0
    for _, f in pairs(a.frames) do
        output = output.."\t{\n"
        output = output.."\t\t.duration = "..math.floor(f.duration*1000)..",\n"
        output = output.."\t\t.layerCount = "..#f.parts..",\n"
        output = output.."\t\t.layerData = "..outputId.."_anim"..animIndex.."_layer"..frameIndex.."_data\n"
        output = output.."\t}"
        count = count + 1
        if count < #a.frames then
            output = output..","
        end
        output = output.."\n"
        frameIndex = frameIndex + 1
    end
    output = output.."};\n\n"
    animIndex = animIndex + 1
end
local animCount = animIndex

output = output.."// Animations array\n"
output = output.."static const LayeredSpriteAnim "..outputId.."_anims[] = {\n"
local animIndex = 0
local total = 0
for name, a in pairs(animations) do
    total = total + #name + 1
    output = output.."\t// Animation '"..name.."'\n"
    output = output.."\t{\n"
    output = output.."\t\t.direction = "..animDirectionEnum(a.direction)..",\n"
    output = output.."\t\t.frameCount = "..#a.frames..",\n"
    output = output.."\t\t.frameData = "..outputId.."_anim"..animIndex.."_frames\n"
    output = output.."\t}"
    animIndex = animIndex + 1
    if (animIndex < #animations) then
        output = output..","
    end
    output = output.."\n"
end
output = output.."};\n\n"

output = output.."// Animation names\n"
output = output.."static const uint8_t "..outputId.."_names[] = {\n"
local count = 0
for name, _ in pairs(animations) do
    if count % 16 == 0 then
        output = output.."\t"
    end
    output = output.."0x"..string.format("%02x", #name)
    count = count + 1
    if count < total then
        output = output..","
    end
    if count % 16 == 0 then
        output = output.."\n"
    end

    for c in name:gmatch"." do
        if count % 16 == 0 then
            output = output.."\t"
        end
        output = output.."0x"..string.format("%02x", (string.byte(c)))
        count = count + 1
        if count < total then
            output = output..","
        end
        if count % 16 == 0 then
            output = output.."\n"
        end
    end
end
if count % 16 ~= 0 then
    output = output.."\n"
end
output = output.."};\n\n"

--
-- Sprite data
--

output = output.."// Layered sprite\n"
output = output.."static const LayeredSpriteData "..outputId.." = {\n"
output = output.."\t.paletteCount = "..#palette..",\n"
output = output.."\t.paletteData = "..outputId.."_palette,\n"
output = output.."\t.partCount = "..#parts..",\n"
output = output.."\t.partData = "..outputId.."_parts,\n"
output = output.."\t.animCount = "..animCount..",\n"
output = output.."\t.animData = "..outputId.."_anims,\n"
output = output.."\t.animNames = "..outputId.."_names\n"
output = output.."};\n\n"

--
-- Write files
--

local file = io.open(app.fs.joinPath(app.fs.filePath(sprite.filename), outputId..".h"), "w")
file:write(output)
file:close()
print("Save sprite data to '"..outputId..".h'")
