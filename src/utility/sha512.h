/*
 * Copyright (C) 2015 Southern Storm Software, Pty Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef CRYPTO_SHA512_h
#define CRYPTO_SHA512_h

#include <inttypes.h>
#include <stddef.h>

void clean(void *dest, size_t size);

template <typename T>
inline void clean(T &var)
{
    clean(&var, sizeof(T));
}

bool secure_compare(const void *data1, const void *data2, size_t len);

class SHA512{
public:
    SHA512();
    virtual ~SHA512();

    size_t hashSize() const;
    size_t blockSize() const;

    void reset();
    void update(const void *data, size_t len);
    void finalize(void *hash, size_t len);

    void clear();

    void resetHMAC(const void *key, size_t keyLen);
    void finalizeHMAC(const void *key, size_t keyLen, void *hash, size_t hashLen);

private:
    struct {
        uint64_t h[8];
        uint64_t w[16];
        uint64_t lengthLow;
        uint64_t lengthHigh;
        uint8_t chunkSize;
    } state;

    void processChunk();

protected:
    void formatHMACKey(void *block, const void *key, size_t len, uint8_t pad);

};

#endif
