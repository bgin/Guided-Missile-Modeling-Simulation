
#ifndef __GMS_COMMON_H__
#define __GMS_COMMON_H__

namespace file_info {

	
        const unsigned int gGMS_COMMON_MAJOR = 1;

	const unsigned int gGMS_COMMON_MINOR = 1;

	const unsigned int gGMS_COMMON_MICRO = 0;

	const unsigned int gGMS_COMMON_FULLVER = 
	 1000U*gGMS_COMMON_MAJOR+100U*gGMS_COMMON_MINOR+10U*gGMS_COMMON_MICRO;

	const char * const pgGMS_COMMON_CREATE_DATE = "27-09-2019 20:05 +00200 (FRI 27 SEP 2019 GMT+2)";

	const char * const pgGMS_COMMON_BUILD_DATE = "00-00-0000 00:00";

	const char * const pgGMS_COMMON_AUTHOR = "Programmer: Bernard Gingold, contact: beniekg@gmail.com";

	const char * const pgGMS_COMMON_SYNOPSIS = "GMS common functions.";
}


#if !defined (MEMMOVE_1ELEM)
#define MEMMOVE_1ELEM 1
#endif

#if !defined (MEMMOVE_16ELEMS)
#define MEMMOVE_16ELEMS 16
#endif

#if !defined (MEMMOVE_32ELEMS)
#define MEMMOVE_32ELEMS 32
#endif

#if !defined (MEMMOVE_64ELEMS)
#define MEMMOVE_64ELEMS 64
#endif

#if !defined (MEMMOVE_128ELEMS)
#define MEMMOVE_128ELEMS 128
#endif

#if !defined (MEMMOVE_256ELEMS)
#define MEMMOVE_256ELEMS 256
#endif
// float type (4-bytes)
#define YMM_LEN (8)
#define ZMM_LEN (16)

#if !defined (PAGE4KiB)
#define PAGE4KiB 4096
#endif

#if !defined (MAXFLOATSPERPAGE4KiB)
#define MAXFLOATSPERPAGE4KiB 1024
#endif

#if !defined (min_val)
#define min_val(A,B) ((A)<(B)?(A):(B))
#endif

#include <cstdint>
#include "GMS_config.h"

class AVXVec8;
class AVXc8f32;
class AVX512Vec16;

namespace gms{
	namespace common {

		// Degree to radian conversion

		// 256-bit vector
		//const __m256d vrad4_to_deg = _mm256_set1_pd(57.29577951308092);

		// 512-bit vector
		//const __m512d vrad8_to_deg = _mm512_set1_pd(57.29577951308092);

		// Zero-valued vector 256-bit
		//const __m256d vzero4 = _mm256_set1_pd(0.0);

		// Zero-valued vector 512-bit
		///const __m512d vzero8 = _mm512_setzero_pd();

		// D. Knuth safe floating-point comparison

		bool approximately_equalf64( const double,
					     const double,
					     const double);

		bool essentialy_equalf64( const double,
					  const double,
					  const double);

		bool definitely_greaterf64( const double,
					    const double,
					    const double);

		bool definitely_lessf64( const double,
					 const double,
					 const double);

		bool approximately_equalf32(const float,
					    const float,
					    const float);

		bool essentialy_equalf32(const float,
					 const float,
					 const float);

		bool definitely_greaterf32(const float,
					   const float,
					   const float);

		bool definitely_lessf32(const float,
					const float,
					const float);

		

		// Pointer alignment
		bool Is_ptr_aligned32(_In_ const int64_t * __restrict);
					

		bool Is_ptr_aligned32(_In_ const double * __restrict);

		bool Is_ptr_aligned64(_In_ const int64_t * __restrict);

		bool Is_ptr_aligned64(_In_ const double * __restrict);

		template<typename PTR, uint32_t Alignment,
			     typename = std::enable_if<(std::is_pointer<PTR>::value &&
							std::is_floating_point<PTR>::value) ||
							(std::is_pointer<PTR>::value &&
							std::is_integral<PTR>::value),bool>::type>
							Is_ptr_aligned(PTR * ptr) {
			       if ((reinterpret_cast<uintptr_t>(ptr) & Alignment) == 0ULL){
							  return (true);
					}
						 else {
							 return (false);
						 }
			}

		//
		// Array of type float/double scalar initialization.
		//
		void init_array( double* __restrict, 
		                 const int64_t, 
			         const double);

		void init_array( float* __restrict,
				 const int64_t,
				 const float);

		//
		// Array of type uint64_t scalar initialization
		//
		void init_array(uint64_t* __restrict, 
		                const int64_t, 
				const uint64_t);

		void init_array(int64_t* __restrict,
		                const int64_t,
				const int64_t);

		void init_array(int32_t* __restrict,
				const int64_t,
				const int32_t);

		//
		// Array of type unsigned char scalar initialization
		//
		void init_array(unsigned char* __restrict,
				const int64_t,
				const unsigned char);
		//
		//	Array of type double vectorised initialization
		//
		void init_varray(double* __restrict,
				 const int64_t,
				 const double );

		void init_varray(float* __restrict,
				 const int64_t,
				 const float);

		void init_unroll2x_cmplxr4(std::complex<float> * __restrict __ATTR_ALIGN__(64),
					   const int64_t,
					   const std::complex<float>) __ATTR_COLD__ __ATTR_ALIGN__(64);
		
		void init_unroll4x_cmplxr4(std::complex<float> * __restrict __ATTR_ALIGN__(64),
					   const int64_t,
					   const std::complex<float>) __ATTR_COLD__ __ATTR_ALIGN__(64);

		void init_unroll8x_cmplxr4(std::complex<float> * __restrict __ATTR_ALIGN__(64),
					   const int64_t,
					   const std::complex<float>) __ATTR_COLD__ __ATTR_ALIGN__(64);

		void avxvec8_init_unroll2x(AVXVec8 * __restrict __ATTR_ALIGN__(64),
		                           const int64_t,
					   const AVXVec8 ) __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avxvec8_init_unroll4x(AVXVec8 * __restrict __ATTR_ALIGN__(64),
		                           const int64_t,
					   const AVXVec8) __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avxvec8_init_unroll8x(AVXVec8 * __restrict __ATTR_ALIGN__(64),
		                           const int64_t,
					   const AVXVec8) __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avxvec8_copy_unroll2x(AVXVec8 * __restrict __ATTR_ALIGN__(64),
					   const AVXVec8 * __restrict __ATTR_ALIGN__(64),
					   const int64_t) __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avxvec8_copy_unroll4x(AVXVec8 * __restrict __ATTR_ALIGN__(64),
					   const AVXVec8 * __restrict __ATTR_ALIGN__(64),
					   const int64_t)  __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avxvec8_copy_unroll8x(AVXVec8 * __restrict __ATTR_ALIGN__(64),
					   const AVXVec8 * __restrict __ATTR_ALIGN__(64),
					   const int64_t)  __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avxvec8_copy_from_r4(AVXVec8     * __restrict __ATTR_ALIGN__(64),
				          const float * __restrict __ATTR_ALIGN__(64),
					  const int64_t) __ATTR_COLD__ __ATTR_ALIGN__(32);

                void avx512vec16_init_unroll2x(AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
					       const int64_t,
					       const AVX512Vec16) __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avx512vec16_init_unroll4x(AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
					       const int64_t,
					       const AVX512Vec16) __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avx512vec16_init_unroll8x(AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
					       const int64_t,
					       const AVX512Vec16) __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avx512vec16_copy_unroll2x(AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
					       const AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
					       const int64_t) __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avx512vec16_copy_unroll4x(AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
					       const AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
					       const int64_t) __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avx512vec16_copy_unroll8x(AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
					       const AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
					       const int64_t) __ATTR_COLD__ __ATTR_ALIGN__(32);




                void r4_copy_from_avxvec8(float * __restrict __ATTR_ALIGN__(64),
		                          const AVXVec8 * __restrict __ATTR_ALIGN__(64),
					  const int64_t ) __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avxvec8_copy_from_r4(AVXVec8 * __restrict __ATTR_ALIGN__(64),
		                          const float * __restrict __ATTR_ALIGN__(64),
					  const int64_t) __ATTR_COLD__ __ATTR_ALIGN__(32);
#if defined __AVX512F__

	        void r4_copy_from_avx512vec16(float * __restrict __ATTR_ALIGN__(64),
		                              const AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
					      const int64_t)  __ATTR_COLD__ __ATTR_ALIGN__(32);

		void avx512vec16_copy_from_r4(AVX512Vec16 * __restrict __ATTR_ALIGN__(64),
		                              const float * __restrict __ATTR_ALIGB__(64),
					      const int64_t)  __ATTR_COLD__ __ATTR_ALIGN__(32);
#endif

                void avxc8f32_copy_from_r4(AVXc8f32 * __restrict __ATTR_ALIGN__(64),
		                           const float * __restrict __ATTR_ALIGN__(64),
					   const float * __restrict __ATTR_ALIGN__(64),
					   const int64_t)__ATTR_COLD__ __ATTR_ALIGN__(32)

                void r4_copy_from_avxc8f32(float * __restrict __ATTR_ALIGN__(64),
		                           float * __restrict __ATTR_ALIGN__(64),
					   const AVXc8f32 * __restrict __ATTR_ALIGN__(64),
					   const int64_t) __ATTR_COLD__ __ATTR_ALIGN__(32)


		//
		//	Array of type float/double vectorised initialization
		//  Unrolled 2x (using AVX)
		//  Array must be aligned on 64-bytes boundaries.
		//
		void avx256_init_unroll2x_pd( double * __restrict,
					   const  int64_t,
					   const double ) noexcept(true);

		void avx256_init_unroll2x_ps( float * __restrict,
					      const int64_t,
					      const float) noexcept(true);

		//
		//	Array of type float/double vectorised initialization
		//  Unrolled 2x (using AVX)
		//  Array must be aligned on 64-bytes boundaries.
		//
		void avx256_init_unroll4x_pd( double * __restrict,
					      const int64_t,
					      const double) noexcept(true);

		void avx256_init_unroll4x_ps( float * __restrict,
					      const int64_t,
					      const float) noexcept(true);
		
		//
		//	Array of type float/double vectorised initialization
		//  Unrolled 8x (using AVX)
		//  Array must be aligned on 64-bytes boundaries.
		//
		void avx256_init_unroll8x_pd( double * __restrict,
					   const int64_t,
					   const double) noexcept(true);

		void avx256_init_unroll8x_ps( float * __restrict,
					      const int64_t,
					      const float) noexcept(true);

		//
		//	Array of type float/double vectorised initialization
		//  Unrolled 8x (using AVX3)
		//  Array must be aligned on 64-bytes boundaries.
		//
#if defined __AVX512F__

                
		void avx512_init_unroll2x_pd( double * __restrict,
					      const int64_t,
					      const double);

		void avx512_init_unroll2x_ps( float * __restrict,
					      const int64_t,
					      const float);

		void avx512_init_unroll4x_pd( double * __restrict,
					      const int64_t,
					      const double);

		void avx512_init_unroll4x_ps( float * __restrict,
					      const int64_t,
					      const float);
		
		void avx512_init_unroll8x_pd( double * __restrict,
					      const int64_t,
					      const double) noexcept(true);

		void avx512_init_unroll8x_ps( float * __restrict,
					      const int64_t,
					      const float) noexcept(true);
#endif

	   //
	   // Check for zero (0.0) in arrays.
	   // Vectorised version.
	   // @Returns:
	   //			true if 0.0 is detected, 
	   //           otherwise false.
		bool vzero_check(_In_ double*  __restrict,
						 _In_ double*  __restrict,
						 _In_ const int64_t );

		//
		// Check for zero (0.0) in array.
		// Vectorised version.
		// @Returns:
		//			true if 0.0 is detected, 
		//           otherwise false.
		bool vzero_check1(_In_ const double* __restrict,
						 _In_ const int64_t);
						 

		//
		// Check for zero (0.0) in array 3D
		// Vectorised version
		// @Returns:
		//           true on first occurrence of 0.0,
		//			 otherwise false.
		// @Remark:
		//			 Data array should be of length which is: len%4 == 0
		bool vzero_check3D(_In_ const double* __restrict, 
						   _In_ const int64_t, 
						   _In_ const int64_t,
						   _In_ const int64_t);

		//
		// Check for zero (0.0) in array 3D
		// Vectorised version
		// @Returns:
		//           true on first occurrence of 0.0,
		//			 otherwise false.
		// @Remark:
		//			This overloaded version is called from 
		//			various code blocks which operates of fields arrays.
		bool vzero_check3D(_In_ const double* __restrict,
						   _In_ const int64_t,
						   _In_ const int64_t,
						   _In_ const int64_t,
						   _In_ const int64_t,
						   _In_ const int64_t,
						   _In_ const int64_t);

		
	   
		//
		//	Copy memory (AVX unrolled version) from source to destination
		//  Both source and destination are flat arrays.
		//	@Returns: nothing
		//  @Remark:  
		//			  Memory must be aligned on 64-byte boundary.
		//            This version uses stream stores.
		//		      Be sure , that recently stored data will
		//			  not be used soon.
		//			  Unrolled 2x
		//			  This version should be used on data
		//			  being ~ 1/2 size of L3 cache.
		//
	   
		void avx256_memcpy2x_nt_pd(double * __restrict,
					const double * __restrict,
					const int64_t);

		void avx256_memcpy2x_nt_ps(float * __restrict,
					   const float * __restrict,
					   const int64_t);

		//
		//	Copy memory (AVX unrolled version) from source to destination
		//   Both source and destination are flat arrays.
		//	@Returns: nothing
		//   @Remark:  
		//			  Memory must be aligned on 64-byte boundary.
		//            This version uses stream stores.
		//			  Be sure, that recently stored data will
		//			  not be used soon.
		//			  Unrolled 2x
		//			  This version should be used on data
		//			  being ~ 1/2 size of L3 cache.
		//

		void avx256_memcpy4x_nt_pd(double * __restrict,
					const double * __restrict,
					const int64_t);

		void avx256_memcpy4x_nt_ps(float * __restrict,
					   const float * __restrict,
					   const int64_t);

	   //
	   //	Copy memory (AVX unrolled version) from source to destination
	   //   Both source and destination are flat arrays.
	   //	@Returns: nothing
	   //   @Remark:  
	   //			  Memory must be aligned on 64-byte boundary.
	   //             This version uses stream stores.
	   //			  Be sure, that recently stored data will
	   //			  not be used soon.
	   //			  Unrolled 8x
	   //			  This version should be used on data
	   //			  being ~ 1/2 size of L3 cache.
	   //

		void  avx256_memcpy8x_nt_pd(double * __restrict,
					 const double * __restrict,
					 const int64_t);

		void avx256_memcpy8x_nt_ps(float * __restrict,
					   const float * __restrict,
					   const int64_t);

		//
		//  Copy memory (AVX unrolled version) from source to destination
		//  Both source and destination are flat arrays.
		//	@Returns: nothing
		//  @Remark:  
		//			  Memory must be aligned on 64-byte boundary.
		//			  Unrolling 2x
		//

		void avx256_memcpy2x_pd(double * __restrict,
				     const double * __restrict,
				     const int64_t);

		void avx256_memcpy2x_ps(float * __restrict,
					const float * __restrict,
					const int64_t);

		//
		//  Copy memory (AVX unrolled version) from source to destination
		//  Both source and destination are flat arrays.
		//	@Returns: nothing
		//  @Remark:  
		//			  Memory must be aligned on 64-byte boundary.
		//			  Unrolling 4x
		//

		void avx256_memcpy4x_pd(double * __restrict,
				     const double * __restrict,
				     const int64_t);

		void avx256_memcpy4x_ps(float * __restrict,
					const float * __restrict,
					const int64_t);

		//
		//  Copy memory (AVX unrolled version) from source to destination
		//  Both source and destination are flat arrays.
		//	@Returns: nothing
		//  @Remark:  
		//			  Memory must be aligned on 64-byte boundary.
		//			  Unrolling 8x
		//

		void avx256_memcpy8x_pd(double * __restrict,
				       const double * __restrict,
				       const int64_t );

		void avx256_memcpy8x_ps(float * __restrict,
					const float * __restrict,
					const int64_t);

		void avx256_cached_memmove(void * __restrict,
					   const void * __restrict,
					   const int32_t);

		void avx256_uncached_memmove(void * __restrict,
					     const void * __restrict,
					     const int32_t);
#if defined __AVX512F__

		void avx512_cached_memmove(void * __restrict ,
					   const void * __restrict,
					   const int32_t);

		void avx512_uncached_memmove(void * __restrict,
					     const void * __restrict,
					     int32_t);

#endif		

		
							
	}
}

#endif /*__GMS_COMMON_H__*/
