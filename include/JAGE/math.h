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

            void update(const uint8_t* data, size_t len);
            void final(uint8_t out[20]);
        private:
            uint32_t h0, h1, h2, h3, h4;
            uint8_t buffer[64];
            size_t buffer_len;
            uint64_t bit_len;

            uint32_t rotate_left(uint32_t x, uint32_t n);

            uint32_t read_be(const uint8_t* src);
            void write_be(uint8_t* dst, uint32_t val);

            void process_block(const uint8_t block[64]);
        };

    }
}
