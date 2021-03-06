/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017-2020 Light Transport Entertainment, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef NANOSTL_ALLOCATOR_H_
#define NANOSTL_ALLOCATOR_H_

#include "nanocommon.h"

#ifdef NANOSTL_DEBUG
#if !defined(__CUDACC__)
#include <iostream>
#endif
#endif

namespace nanostl {

typedef unsigned long long size_type;

#ifdef __clang__
#pragma clang diagnostic push
#if __has_warning("-Wzero-as-null-pointer-constant")
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif
#endif

///
/// allocator class implementaion without libc function
///
template <typename T>
class allocator {
 public:
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;

  NANOSTL_HOST_AND_DEVICE_QUAL allocator() {}

  NANOSTL_HOST_AND_DEVICE_QUAL T* allocate(size_type n, const void* hint = 0) {
    (void)hint;  // Ignore `hint' for a while.
    if (n < 1) {
      return 0;
    }

#ifdef NANOSTL_DEBUG
#if defined(__CUDACC__)
    printf("allocator::allocate: %u\n", n);
#else
    std::cerr << "allocator::allocate: n " << n << std::endl;
#endif
#endif

    return new T[n];
  }

  NANOSTL_HOST_AND_DEVICE_QUAL void deallocate(T* p, size_type n) {
    (void)n;
    delete[] p;
  }

 private:
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif

}  // namespace nanostl

#endif  // NANOSTL_ALLOCATOR_H_
