
/*  random_pcg.h                                                         */

#ifndef RANDOM_PCG_H
#define RANDOM_PCG_H

#include "core/math/math_defs.h"

#include "thirdparty/misc/pcg.h"

#include <math.h>

#if defined(__GNUC__)
#define CLZ32(x) __builtin_clz(x)
#elif defined(_MSC_VER)
#include <intrin.h>
static int __bsr_clz32(uint32_t x) {
	unsigned long index;
	_BitScanReverse(&index, x);
	return 31 - index;
}
#define CLZ32(x) __bsr_clz32(x)
#else
#endif

#if defined(__GNUC__)
#define LDEXP(s, e) __builtin_ldexp(s, e)
#define LDEXPF(s, e) __builtin_ldexpf(s, e)
#else
#include <math.h>
#define LDEXP(s, e) ldexp(s, e)
#define LDEXPF(s, e) ldexp(s, e)
#endif

class RandomPCG {
	pcg32_random_t pcg;
	uint64_t current_seed; // seed with this to get the same state
	uint64_t current_inc;

public:
	static const uint64_t DEFAULT_SEED = 12047754176567800795U;
	static const uint64_t DEFAULT_INC = PCG_DEFAULT_INC_64;

	RandomPCG(uint64_t p_seed = DEFAULT_SEED, uint64_t p_inc = DEFAULT_INC);

	_FORCE_INLINE_ void seed(uint64_t p_seed) {
		current_seed = p_seed;
		pcg32_srandom_r(&pcg, current_seed, current_inc);
	}
	_FORCE_INLINE_ uint64_t get_seed() { return current_seed; }

	void randomize();
	_FORCE_INLINE_ uint32_t rand() {
		current_seed = pcg.state;
		return pcg32_random_r(&pcg);
	}

	// Obtaining floating point numbers in [0, 1] range with "good enough" uniformity.
	// These functions sample the output of rand() as the fraction part of an infinite binary number,
	// with some tricks applied to reduce ops and branching:
	// 1. Instead of shifting to the first 1 and connecting random bits, we simply set the MSB and LSB to 1.
	//    Provided that the RNG is actually uniform bit by bit, this should have the exact same effect.
	// 2. In order to compensate for exponent info loss, we count zeros from another random number,
	//    and just add that to the initial offset.
	//    This has the same probability as counting and shifting an actual bit stream: 2^-n for n zeroes.
	// For all numbers above 2^-96 (2^-64 for floats), the functions should be uniform.
	// However, all numbers below that threshold are floored to 0.
	// The thresholds are chosen to minimize rand() calls while keeping the numbers within a totally subjective quality standard.
	// If clz or ldexp isn't available, fall back to bit truncation for performance, sacrificing uniformity.
	_FORCE_INLINE_ double randd() {
#if defined(CLZ32)
		uint32_t proto_exp_offset = rand();
		if (unlikely(proto_exp_offset == 0)) {
			return 0;
		}
		uint64_t significand = (((uint64_t)rand()) << 32) | rand() | 0x8000000000000001U;
		return LDEXP((double)significand, -64 - CLZ32(proto_exp_offset));
#else
#pragma message("RandomPCG::randd - intrinsic clz is not available, falling back to bit truncation")
		return (double)(((((uint64_t)rand()) << 32) | rand()) & 0x1FFFFFFFFFFFFFU) / (double)0x1FFFFFFFFFFFFFU;
#endif
	}
	_FORCE_INLINE_ float randf() {
#if defined(CLZ32)
		uint32_t proto_exp_offset = rand();
		if (unlikely(proto_exp_offset == 0)) {
			return 0;
		}
		return LDEXPF((float)(rand() | 0x80000001), -32 - CLZ32(proto_exp_offset));
#else
#pragma message("RandomPCG::randf - intrinsic clz is not available, falling back to bit truncation")
		return (float)(rand() & 0xFFFFFF) / (float)0xFFFFFF;
#endif
	}

	_FORCE_INLINE_ double randfn(double p_mean, double p_deviation) {
		return p_mean + p_deviation * (cos(Math_TAU * randd()) * sqrt(-2.0 * log(randd()))); // Box-Muller transform
	}
	_FORCE_INLINE_ float randfn(float p_mean, float p_deviation) {
		return p_mean + p_deviation * (cos(Math_TAU * randf()) * sqrt(-2.0 * log(randf()))); // Box-Muller transform
	}

	double random(double p_from, double p_to);
	float random(float p_from, float p_to);
	real_t random(int p_from, int p_to) { return (real_t)random((real_t)p_from, (real_t)p_to); }
};

#endif // RANDOM_PCG_H
