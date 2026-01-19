#pragma once

#include "JAGE/core.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace JAGE
{
    namespace Math
    {
        class JAGE_API SHA1
        {
        public:
            SHA1();

            void update(const ui8* data, size_t len);
            void final(ui8 out[20]);
        private:
            ui32 h0, h1, h2, h3, h4;
            ui8 buffer[64];
            size_t buffer_len;
            ui64 bit_len;

            ui32 rotate_left(ui32 x, ui32 n);

            ui32 read_be(const ui8* src);
            void write_be(ui8* dst, ui32 val);

            void process_block(const ui8 block[64]);
        };

    }
}
