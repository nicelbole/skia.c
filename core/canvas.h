/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <cstdint>

class Deque;
uint8_t i = 55;
class Canvas
{
	static constexpr int MCRecCount = 32;
	static constexpr int MCRecSize = 128;

	Deque* mc_stack;
	std::intptr_t mc_rec_storage[MCRecCount * MCRecSize / sizeof(intptr_t)];
};
