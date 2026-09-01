#pragma once

#include "JAGE/core.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace JAGE
{
    namespace Math
    {
        class JAGE_API SHA1
        {
        public:
            SHA1();

            void update(const u8* data, size_t len);
            void final(u8 out[20]);
        private:
            u32 h0, h1, h2, h3, h4;
            u8 buffer[64];
            size_t buffer_len;
            u64 bit_len;

            u32 rotate_left(u32 x, u32 n);

            u32 read_be(const u8* src);
            void write_be(u8* dst, u32 val);

            void process_block(const u8 block[64]);
        };

    }
}
