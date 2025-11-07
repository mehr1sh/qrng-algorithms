# How Random Number Generators Work

This document explains how each random number generator in our comparison works, in simple terms that anyone can understand.

## Table of Contents
1. [QRNG (Quantum Random Number Generator)](#qrng)
2. [Mersenne Twister (MT19937)](#mt19937)
3. [Xorshift](#xorshift)
4. [LCG (Linear Congruential Generator)](#lcg)
5. [Comparison Summary](#comparison)
6. [Which One Should You Use?](#which-one)

## QRNG (Quantum Random Number Generator) <a name="qrng"></a>

### The Quantum Magic
Imagine flipping a quantum coin that exists in a state of both heads AND tails until you look at it. When you look, it randomly "collapses" to one state or the other. That's essentially how QRNG works, but with quantum bits (qubits).

### How It Works (Simplified)
1. **Initialization**: Prepare a qubit in a quantum superposition (both 0 and 1 simultaneously)
2. **Measurement**: When you measure the qubit, it randomly collapses to either 0 or 1
3. **Repeat**: Do this many times to get a sequence of random bits

### Why It's Special
- **True randomness**: Based on fundamental quantum mechanics
- **Unpredictable**: Even knowing all previous outputs doesn't help predict the next bit
- **No patterns**: Doesn't repeat like pseudorandom number generators

### In Our Code
Since we don't have a real quantum computer, we simulate this process using high-quality entropy sources from the operating system.

## Mersenne Twister (MT19937) <a name="mt19937"></a>

### The Math Behind It
Mersenne Twister is like a super-complex recipe that takes a starting number (seed) and mixes it up in very complicated ways to produce numbers that look random.

### How It Works (Simplified)
1. **State Array**: Keeps track of 624 numbers (the "state")
2. **Twisting**: Uses bitwise operations to mix up the state
3. **Tempering**: Further scrambles the output to look more random
4. **Output**: Returns one number at a time, updating the state each time

### Why People Love It
- **Long period**: Repeats every 2^19937-1 numbers (that's a 6000+ digit number!)
- **Good distribution**: Passes most statistical tests
- **Fast**: Uses simple computer operations

### The Catch
If someone sees 624 consecutive outputs, they can predict all future numbers. Not good for cryptography!

## Xorshift <a name="xorshift"></a>

### The Simple But Effective Approach
Xorshift is like taking a number, mixing it up with itself in a few simple steps, and getting something that looks random.

### How It Works
1. Start with a seed value (e.g., 12345)
2. For each new number:
   ```c
   x ^= x << 13;  // XOR with left-shifted self
   x ^= x >> 17;   // XOR with right-shifted self
   x ^= x << 5;    // XOR with left-shifted self again
   return x;
   ```
3. The magic is in the shift amounts (13, 17, 5) which were carefully chosen

### Why It's Fast
- Only uses three simple operations per number
- No multiplication or division
- Very little memory needed

### Limitations
- Shorter period than Mersenne Twister
- Can show patterns in higher dimensions
- Predictable after seeing about 64 outputs

## LCG (Linear Congruential Generator) <a name="lcg"></a>

### The Old-Timer
LCG is one of the oldest and simplest random number generators. It's like a broken clock that's right twice a day - simple but not very reliable.

### How It Works
1. Start with a seed value
2. For each new number:
   ```
   next = (a * current + c) % m
   ```
   Where:
   - `a` is the multiplier (e.g., 1664525)
   - `c` is the increment (e.g., 1013904223)
   - `m` is the modulus (e.g., 2^32)

### Why It's Problematic
- **Patterns**: Numbers fall into a lattice structure when plotted
- **Low bits aren't random**: The last bit alternates between 0 and 1!
- **Predictable**: If you know a few numbers, you can figure out the rest

### Why It's Still Used
- Extremely fast (just multiply, add, modulo)
- Very simple to implement
- Good enough for non-critical applications like simple games

## Comparison Summary <a name="comparison"></a>

| Algorithm | Speed | Quality | Period | Security | Best For |
|-----------|-------|---------|--------|----------|----------|
| **QRNG** | Slow | Perfect | Infinite | Best | Cryptography, Security |
| **MT19937** | Fast | Excellent | 2^19937-1 | Medium | General purpose, Simulations |
| **Xorshift** | Fastest | Very Good | 2^128-1 | Low | Games, Non-critical uses |
| **LCG** | Fastest | Poor | 2^32 | None | Simple applications |

## Which One Should You Use? <a name="which-one"></a>

### Use QRNG when:
- You need true randomness (cryptography, lotteries, scientific research)
- Security is critical
- Speed isn't the main concern

### Use Mersenne Twister when:
- You need good quality random numbers for simulations
- You're doing machine learning or scientific computing
- You need a balance of speed and quality

### Use Xorshift when:
- You need speed more than perfect randomness
- You're making a game (not for cryptography!)
- Memory is limited

### Avoid LCG unless:
- You're just learning about RNGs
- You need something extremely simple
- Randomness quality doesn't matter at all

## Further Reading
- [Mersenne Twister Paper](http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/ARTICLES/mt.pdf)
- [Xorshift Paper](https://www.jstatsoft.org/article/view/v008i14)
- [NIST Documentation on Randomness Testing](https://csrc.nist.gov/projects/random-bit-generation/documentation-and-software)

[Next: Technical Implementation →](technical.md)
