# NullX Accelerated C++ Math Library
##### Full Documentation: people.rit.edu/kah4525/NullX
NullX is a C++ SIMD-optimized mathematics library made for use in graphics rendering and game programming.
The aim for the library is to provide a simple guide to SIMD optimization, while maintaining an efficient use of the 
CPU's hardware. Development will be done in phases, with each phase bringing major improvements to the speed and 
potency of the library.

#### Phase 1 - Initial Architecture (Completed - 6/15/16)
- Functionality for Vector2, Vector3, Vector4 & Matrix4x4
- Commonly used functions (Clamp, Floor, Ceiling, etc.)

#### Phase 2 - Quaternions & Doxygen (Completed 6/20/16)
- Implement the magic of Quaternions
- Doxygen documentation in NullX header

#### Phase 3 - SIMD Vectors (Completed 6/22/16)
- Implement intrinsics for Vector2, Vector3 & Vector4 classes
- Fully test newly implemented functionality

#### Phase 4 - SIMD Matrices & Quaternions (Completed 6/28/16)
- Implement intrinsics for Matrix4x4 and Quaternion classes
- Fully test newly implemented functionality


#Post Mortem
NullX was a very fun project to work on, and I'm not sure if I've ever been so dedicated to a project in my life.  On average I figure I spent at least 3 hours per day working on it.  It introduced me to avenues of mathematics I never knew existed, and taught a great deal about the process of decoding formulas in order to translate them into optimized C++ code.  

## Overview
I started the project on June 15th, and was hoping to get finished with the initial architecture of the library within the following two weeks.  Two weeks turned into one, and I kept the momentum flowing when I transitioned into converting everything to SIMD.  I thought that SIMD optimization would take another two weeks, as I had failed previously with an attempt at learning how it works.  But this time, I thankfully got through it and figured out that it wasn't really so complicated after all.  One more week passed, and nearly everything was completely SIMD optimized.  The only algorithms remaining that aren't accelerated are the LU Decomposition and Inverse matrix functions, which at this moment don't seem like they could even be optimized.

## Hardest Algorithm
By far the hardest algorithm to implement was the matrix LU-Decomposition function; I spent around 4 hours sitting in Penfield Wegmans carefully analyzing and implementing the formula for the factorization.  It provides a huge speed-up for the determinant and inverse matrix calculations.  That experience taught me a lot about myself, and helped justify that I may have a knack for this programming thing.

## Unfinished
The only lingering issue with the library is the quaternion functionality.  I tested against Unity's Quaternion class, and for days I couldn't seem to get any calculations to match Unity's.  I plan to come back to work on the NullX quaternion class once I've found a textbook outlining every detail about them.  I'm going to take the dangerous journey of actually understanding quaternions, and to all those who know that struggle, wish me luck!

## Summary
NullX will be the 3D math library I use in every one of my future personal projects, and it will be tweaked and improved over time as new optimizations are discovered.  I've truly enjoyed working on transforming mathematics into code, and look forward to expanding it's functionality and improving its speed in the years to come.
