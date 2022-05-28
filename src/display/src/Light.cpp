#include "../Light.h"

namespace craft {

    Light* Light::Create(LightType type) {
        Light* l = MemoryPool<Light>::Create();
        l->type = type;
        return l;
    }

    void Light::reset() {
        type = LightType::Directional;
        color = 0xffffffff;
        strength = 1.0;
        direction = 0;
        attenuation = 0;
        x = 0;
        y = 0;
    }

    void Light::update() {
        _dx = cos(direction);
        _dy = sin(direction);
        _a = attenuation * attenuation;
    }

    void Light::calc(int16_t rx, int16_t ry, float_t& s, float_t& dx, float_t& dy) {
        s = strength;
        dx = _dx;
        dy = _dy;
    }

} // namespace craft
