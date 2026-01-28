#include "JAGE/math.h"

#include "log.h"

#include <glm/glm.hpp>

namespace JAGE
{
    namespace Math
    {
        SHA1::SHA1()
        : h0 { 0x67452301 }
        , h1 { 0xEFCDAB89 }
        , h2 { 0x98BADCFE }
        , h3 { 0x10325476 }
        , h4 { 0xC3D2E1F0 }
        , buffer_len {}
        , bit_len {}
        {}

        void SHA1::update(const u8* data, size_t len)
        {
            for (size_t i {}; i < len; i++)
            {
                buffer[buffer_len++] = data[i];
                bit_len += 8;

                if (buffer_len == 64)
                {
                    process_block(buffer);
                    buffer_len = 0;
                }
            }
        }

        void SHA1::final(u8 out[20])
        {
            buffer[buffer_len++] = 0x80;

            if (buffer_len > 56)
            {
                while (buffer_len < 64) buffer[buffer_len++] = 0;
                process_block(buffer);
                buffer_len = 0;
            }

            while (buffer_len < 56) buffer[buffer_len++] = 0;

            for (int i { 7 }; i >= 0; i--)
            {
                buffer[buffer_len++] = (bit_len >> (i * 8)) & 0xFF;
            }

            process_block(buffer);

            write_be(out, h0);
            write_be(out + 4, h1);
            write_be(out + 8, h2);
            write_be(out + 12, h3);
            write_be(out + 16, h4);
        }

        u32 SHA1::rotate_left(u32 x, u32 n) { return (x << n) | (x >> (32 - n)); }

        u32 SHA1::read_be(const u8* src) { return (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3]; }

        void SHA1::write_be(u8* dst, u32 val)
        {
            dst[0] = (val >> 24) & 0xFF;
            dst[1] = (val >> 16) & 0xFF;
            dst[2] = (val >> 8) & 0xFF;
            dst[3] = val & 0xFF;
        }

        void SHA1::process_block(const u8 block[64])
        {
            u32 w[80];

            for (int i = 0; i < 16; ++i)
                w[i] = read_be(block + i * 4);

            for (int i = 16; i < 80; ++i)
                w[i] = rotate_left(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

            u32 a = h0, b = h1, c = h2, d = h3, e = h4;

            for (int i = 0; i < 80; ++i)
            {
                u32 f, k;
                if (i < 20)
                {
                    f = (b & c) | (~b & d);
                    k = 0x5A827999;
                } else if (i < 40)
                {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                } else if (i < 60)
                {
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                } else
                {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }

                u32 temp { rotate_left(a, 5) + f + e + k + w[i] };
                e = d;
                d = c;
                c = rotate_left(b, 30);
                b = a;
                a = temp;
            }

            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
            h4 += e;
        }
    }
}