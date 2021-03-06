
#include <malloc.h>
#include <sys/mman.h>
#include <linux/mman.h>
#include <assert>
#include "GMS_error_macros.h"
#include "GMS_malloc.h"
#include "GMS_config.h"
#include "GMS_avxvecf32.h"
#include "GMS_avx512vecf32.h"
#include "GMS_avxc8f32.h"








// ----------------- IMPORTANT ------------------------------
// ALLOCA can not be used that way!! It must be used to allocate
// dynamically on stack only inside computational functions.!!
// ---------------------------------------------------------------
/*double *
gms::common::
gms_dalloca_u(_In_ const std::size_t len) {
#if (GMS_DEBUG_ON) == 1
      _ASSERTE(len > 0ULL);
#endif
      return (reinterpret_cast<double*>(_alloca(len*sizeof(double)));// aligned on 16-bytes
}

float *
gms::common::
gms_falloca_u(_In_ const std::size_t len) {
#if (GMS_DEBUG_ON) == 1
       _ASSERTE(len > 0ULL);
#endif
      return (reinterpret_cast<float*>(_alloca(len*sizeof(float))));
}

int32_t *
gms::common::
gms_ialloca_u(_In_ const std::size_t len) {
#if (GMS_DEBUG_ON) == 1
      _ASSERTE(len > 0ULL)
#endif
      return (reinterpret_cast<int32_t*>(_alloca(len*sizeof(int32_t))));
}

double *
gms::common::
gms_dalloca_a(_In_ const std::size_t len,
              _In_ const std::size_t align) { // align must have a value of  32 or 64
#if (GMS_DEBUG_ON) == 1
      _ASSERTE(len > 0ULL);
#endif
    const std::size_t nbytes = len * sizeof(double);
    void * p = _alloca(nbytes+align-1);
    double * dptr = (double*)(((UINT_PTR)p+(align-1)) & ~(align-1));
    return (dptr);
}

float *
gms::common::
gms_falloca_a(_In_ const std::size_t len,
              _In_ const std::size_t align) {
#if (GMS_DEBUG_ON) == 1
      _ASSERTE(len > 0ULL);
#endif
    const std::size_t nbytes = len * sizeof(float);
    void * p = _alloca(nbytes+align-1);
    float * fptr = (float*)(((UINT_PTR)p + (align-1)) & ~(align-1));
    return (fptr);
}*/



















double *
gms::common::
gms_dmallocu(const std::size_t len) {
#if (GMS_DEBUG_ON) == 1
	assert(len > 0ULL);
#endif
	return (reinterpret_cast<double*>(malloc(len*sizeof(double))));
}

float *
gms::common::
gms_fmallocu(const std::size_t len) {
#if (GMS_DEBUG_ON) == 1
	assert(len > 0ULL);
#endif
	return (reinterpret_cast<float*>(malloc(len*sizeof(float))));
}     

int32_t *
gms::common::
gms_imallocu(const std::size_t len) {
#if (GMS_DEBUG_ON) == 1
	assert(len > 0ULL);
#endif
	return (reinterpret_cast<int32_t*>(malloc(len*sizeof(int32_t))));
}

double * 
gms::common::
gms_dmalloca(const std::size_t len,
	     const int32_t alignment) {
#if (GMS_DEBUG_ON) == 1
	assert(len > 0ULL);
#endif
#if (ADD_PADDING_64B_LOOP_PEEL) == 1
	return (reinterpret_cast<double*>(_mm_malloc(len*sizeof(double) + padding64B,alignment)));
#else
	return (reinterpret_cast<double*>(_mm_malloc(len*sizeof(double),alignment)));
#endif
}

float * 
gms::common::
gms_fmalloca(const std::size_t len,
	     const int32_t alignment) {
#if (GMS_DEBUG_ON) == 1
	assert(len > 0ULL);
#endif
#if (ADD_PADDING_64B_LOOP_PEEL) == 1
	return (reinterpret_cast<float*>(_mm_malloc(len*sizeof(float) + padding64B,alignment)));
#else
	return (reinterpret_cast<float*>(_mm_malloc(len*sizeof(float),alignment)));
#endif
}

int32_t * 
gms::common::
gms_imalloca(const std::size_t len,
	     const int32_t alignment) {
#if (GMS_DEBUG_ON) == 1
	assert(len > 0ULL);
#endif
#if (ADD_PADDING_64B_LOOP_PEEL) == 1
	return (reinterpret_cast<int32_t*>(_mm_malloc(len*sizeof(int32_t) + padding64B,alignment)));
#else
	return (reinterpret_cast<int32_t*>(_mm_malloc(len*sizeof(int32_t),alignment)));
#endif
}

std::complex<float> *
gms::common::
gms_cmplxr4_malloca(const std::size_t len,
		    const int32_t alignment) {
#if (GMS_DEBUG_ON) == 1
  assert(len > 0ULL);
#endif
     return (reinterpret_cast<std::complex<float>*>(_mm_malloc(len*sizeof(std::complex<float>),alignment)));     
}

AVXVec8 * 
gms::common::
gms_avxvec8_malloca(const std::size_t len,
		    const int32_t alignment) {
#if (GMS_DEBUG_ON) == 1
      assert(len > 0ULL);
#endif
     return (reinterpret_cast<AVXVec8*>(_mm_malloc(len*sizeof(AVXVec8),alignment)));
}

AVX512Vec16 *
gms::common::
gms_avx512vec16_malloca(const std::size_t len,
			const int32_t alignment) {
#if (GMS_DEBUG_ON) == 1
      assert(len > 0ULL);
#endif
     return (reinterpret_cast<AVX512Vec16*>(_mm_malloc(len*sizeof(AVX512Vec16),alignment)));
}

AVXc8f32 *
gms::common::
gms_avxc8f32_malloca(const std::size_t len,
		    const int32_t alignment) {
#if (GMS_DEBUG_ON) == 1
      assert(len > 0ULL);
#endif
      return (reinterpret_cast<AVXc8f32*>(_mm_malloc(len*sizeof(AVXc8f32),alignment)));
}

double * 
gms::common::
gms_edmalloca(const std::size_t len, 
	      const int32_t alignment,
	      const bool lock_mem) {
  typedef double * __restrict __attribute__((align(64))) aligned64_r8ptr;
	aligned64_r8ptr real_ptr = NULL;
#if (ADD_PADDING_64B_LOOP_PEEL) == 1
	 real_ptr = reinterpret_cast<double*>(_mm_malloc(len*sizeof(double) + padding64B,alignment));
#else
	 real_ptr = reinterpret_cast<double*>(_mm_malloc(len*sizeof(double), alignment));
#endif
	
	if (NULL == real_ptr && len != 0ULL) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << " Not implemented yet!!";
#endif
	    ABORT_ON_ERROR("gms_edmalloca -- !!! Memory Allocation Failure !!!", MALLOC_FAILED)
	}
#if (ADD_PADDING_64B_LOOP_PEEL) == 1
     if(lock_mem) {
        int32_t res = mlock(real_ptr,len*sizeof(double)+padding64B);
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
#else
     if(lock_mem) {
        int32_t res = mlock(real_ptr,len*sizeof(double));
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
#endif
	return (real_ptr);
}

float * 
gms::common::
gms_efmalloca(const std::size_t len,
	      const int32_t alignment,
	      const bool lock_mem) {
  typedef float * __restrict __attribute__((align(64)))  aligned64_r4ptr;
	aligned64_r4ptr real_ptr = NULL; 
#if (ADD_PADDING_64B_LOOP_PEEL) == 1
	real_ptr = reinterpret_cast<float*>(_mm_malloc(len*sizeof(float) + padding64B,alignment));
#else
	real_ptr = reinterpret_cast<float*>(_mm_malloc(len*sizeof(float), alignment));
#endif
	if (NULL == real_ptr && len != 0ULL) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << " Not implemented yet!!"
#endif
		ABORT_ON_ERROR("gms_efmalloca -- !!! Memory Allocation Failure !!! ", MALLOC_FAILED)
	}
#if (ADD_PADDING_64B_LOOP_PEEL) == 1
     if(lock_mem) {
        int32_t res = mlock(real_ptr,len*sizeof(float)+padding64B);
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
#else
     if(lock_mem) {
        int32_t res = mlock(real_ptr,len*sizeof(float));
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
#endif	
	return (real_ptr);
}

int32_t * 
gms::common::
gms_eimalloca4(const std::size_t len,
	       const int32_t alignment,
	       const bool lock_mem) {
  typedef int32_t * __restrict __attribute__((align(64))) aligned64_i4ptr;
	aligned64_i4ptr i4_ptr = NULL; 
#if (ADD_PADDING_64B_LOOP_PEEL) == 1
	i4_ptr = 	reinterpret_cast<int32_t*>(_mm_malloc(len*sizeof(int32_t) + padding64B,alignment));
#else
	i4_ptr =    reinterpret_cast<int32_t*>(_mm_malloc(len*sizeof(int32_t), alignment));
#endif
	if (NULL == i4_ptr && len != 0ULL) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << " Not implemented yet!!";
#endif
			ABORT_ON_ERROR("gms_eimalloca4 -- !!! Memory Allocation Failure !!! ", MALLOC_FAILED)
	}
#if (ADD_PADDING_64B_LOOP_PEEL) == 1
     if(lock_mem) {
        int32_t res = mlock(i4_ptr,len*sizeof(int32_t)+padding64B);
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
#else
     if(lock_mem) {
        int32_t res = mlock(i4_ptr,len*sizeof(int32_t));
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
#endif
	return (i4_ptr);
}


std::complex<float> *
gms::common::
gms_cmplxr4_emalloca(const std::size len,
                     const int32_t alignment,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
     assert(len > 0ULL);
#endif
    std::complex<float> * ptr = NULL;
    ptr = reinterpret_cast<std::complex<float>*>(_mm_malloc(len*sizeof(std::complex<float>),alignment));
    if(NULL == ptr && len != 0ULL) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
       std::cerr << "Not implemented yet" << std::endl;
#endif
       ABORT_ON_ERROR("gms_cmplxr4_emalloca -- !!! Memory Allocation Failure !!! ", MALLOC_FAILED) 
    }
    if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(std::complex<float>));
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
    return (ptr);
}

AVXVec8 *
gms::common::
gms_avxvec8_emalloca(const std::size_t len,
                     const int32_t alignment) {
#if (GMS_DEBUG_ON) == 1
     assert(len > 0ULL);
#endif
     AVXVec8 * ptr = NULL;
     ptr = reinterpret_cast<AVXVec8*>(_mm_malloc(len*sizeof(AVXVec8),alignment));
     if(NULL == ptr && len != 0ULL) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
         std::cerr << "Not implemented yet!!" << std::endl;
#endif
         ABORT_ON_ERROR("gms_avxvec8_emalloca -- !!! Memory Allocation Failure !!! ", MALLOC_FAILED)
     }
     if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVXVec8));
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

AVX512Vec16 *
gms::common::
gms_avx512vec16_emalloca(const std::size_t len,
                         const int32_t alignment) {
#if (GMS_DEBUG_ON) == 1
     assert(len > 0ULL);
#endif
     AVX512Vec16 * ptr = NULL;
     ptr = reinterpret_cast<AVX512Vec16*>(_mm_malloc(len*sizeof(AVX512Vec16),alignment));
     if(NULL == ptr && len != 0ULL) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
         std::cerr << "Not implemented yet!!" << std::endl;
#endif
         ABORT_ON_ERROR("gms_avx512vec16_emalloca -- !!! Memory Allocation Failure !!! ", MALLOC_FAILED)
     }
     if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVX512Vec16));
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

AVXc8f32 *
gms::common::
gms_avxc8f32_emalloca(const std::size_t len,
                         const int32_t alignment) {
#if (GMS_DEBUG_ON) == 1
     assert(len > 0ULL);
#endif
     AVXc8f32 * ptr = NULL;
     ptr = reinterpret_cast<AVXc8f32*>(_mm_malloc(len*sizeof(AVXc8f32),alignment));
     if(NULL == ptr && len != 0ULL) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
         std::cerr << "Not implemented yet!!" << std::endl;
#endif
         ABORT_ON_ERROR("gms_avxc8f32_emalloca -- !!! Memory Allocation Failure !!! ", MALLOC_FAILED)
     }
     if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVXc8f32));
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

float *
gms::common
::gms_efmalloca_padded2D(const int32_t dim1,
			 const int32_t dim2,
			 const int32_t alignment,
			 int32_t & pad) { // pad will contain either 0 or padding, use it later in flat array indexing (i+pad*j)
	
	asssert(0 == pad && 64 == alignment);
	typedef float * __restrict __attribute__((align(64))) align64_r4ptr;
	align64_r4ptr ptr = NULL;
	const int32_t misalign = dim2 % 16;
	if (misalign) {
		pad = dim2 + (misalign == 0 ? 0 : 16 - misalign);
		ptr = reinterpret_cast<float*>(_mm_malloc(sizeof(float)*dim1*dim2*pad,alignment));
		if (NULL == ptr &&  (dim1*dim2*pad) != 0) { goto failed;}
		return (ptr);
	}	
	else {
		ptr = reinterpret_cast<float*>(_mm_malloc(sizeof(float)*dim1*dim2, alignment));
		if (NULL == ptr && ((dim1*dim2) != 0)) { goto failed;}
		return (ptr);
	}
failed: {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << " Not implemented yet!!"
#endif
		ABORT_ON_ERROR("gms_efmalloca_padded2D -- !!! Memory Allocation Failure !!! ", MALLOC_FAILED)
     }
}


double * 
gms::common::
gms_edmalloca_padded2D(const int32_t dim1,
		       const int32_t dim2,
		       const int32_t alignment,
		       int32_t & pad) { // pad will contain either 0 or padding, use it later in flat array indexing (i+pad*j)
	assert(0 == pad && 64 == alignment);
	typedef double * __restrict __attribute__((align(64))) align64_r8ptr;
	align64_r8ptr ptr = NULL;
	const int32_t misalign = dim2 % 8;
	if (misalign) {
		pad = dim2 + (misalign == 0 ? 0 : 8 - misalign);
		ptr = reinterpret_cast<double*>(_mm_malloc(sizeof(double)*dim1*dim2*pad,alignment));
		if (NULL == ptr && (dim1*dim2*pad) != 0) {goto failed;}
		return (ptr);
	}
	else {
		ptr = reinterpret_cast<double*>(_mm_malloc(sizeof(double)*dim1*dim2, alignment));
		if (NULL == ptr && (dim1*dim2) != 0) { goto failed;}
		return (ptr);
	}

failed:   {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << " Not implemented yet!!"
#endif
		ABORT_ON_ERROR("gms_edmalloca_padded2D -- !!! Memory Allocation Failure !!! ", MALLOC_FAILED)
	}
}

int32_t *
gms::common
::gms_eimalloca4_padded2D(const int32_t dim1,
			  const int32_t dim2,
			  const int32_t alignment,
			  int32_t & pad) {
	assert(0 == pad && 64 == alignment);
	typedef int32_t * __restrict __attribute__((align(64))) align64_i4ptr;
	align64_i4ptr ptr = NULL;
	const int32_t misalign = dim2 % 16;
	if (misalign) {
		pad = dim2 + (misalign == 0 ? 0 : 16 - misalign);
		ptr = reinterpret_cast<int32_t*>(_mm_malloc(sizeof(int32_t)*dim1*dim2*pad,alignment));
		if (NULL == ptr && (dim1*dim2*pad) != 0) { goto failed;}
		return (ptr);
	}
	else {
		ptr = reinterpret_cast<int32_t*>(_mm_malloc(sizeof(int32_t)*dim1*dim2,alignment));
		if (NULL == ptr && (dim1*dim2) != 0) { goto failed; }
		return (ptr);
	}
failed:  {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << " Not implemented yet!!"
#endif
		ABORT_ON_ERROR("gms_eimalloca4_padded2D -- !!! Memory Allocation Failure !!! ", MALLOC_FAILED)
	}
}



#if !defined (MMAP_FUNC_4KIB_BODY)
#define MMAP_FUNC_4KIB_BODY(type)  \   
            do{       \                        
                  (type) * ptr = nullptr;  \
                  int32_t n4KiB_pages = 0;     \
                  int32_t len = 0;             \
                  len = static_cast<int32_t>(length);  \
                  n4KiB_pages = len/4096;              \
                  if(len != n4KiB_pages*4096) {        \
                      n4KiB_pages++;                    \
                  }                                    \
                  len = n4KiB_pages*4096;                \
                  ptr = reinterpret_cast<(type)*>(mmap(NULL,static_cast<std::size_t>(len),  \
                  prot,flag,fd,offset));  \
            }while(0)
#endif    

#if !defined (MMAP_FUNC_2MIB_BODY)
#define MMAP_FUNC_2MIB_BODY(type)     \
           do{         \
              (type) * ptr = nullptr;  \
               int32_t n2MiB_pages = 0;  \
               int32_t len = 0;  \
               len = static_cast<int32_t>(length);  \
               n2MiB_pages = len/2097152; \
               if(len != n2MiB_pages*2097152) { \
                  n2MiB_pages++; \
               } \
               len = n2MiB_pages*2097152; \
               ptr = reinterpret_cast<(type)*>(mmap(NULL,static_cast<std::size_t>(len), \
               prot,flag,fd,offset)); \
           }while(0)   
#endif

#if !defined (MMAP_FUNC_1GIB_BODY)
#define MMAP_FUNC_1GIB_BODY(type) \
           do{ \
              (type) * ptr = nullptr; \
              int32_t n1GiB_pages = 0; \
              int32_t len = 0;    \
              len = static_cast<int32_t>(length); \
              n1GiB_pages = len/1073741824; \
              if(len != n1GiB_pages*1073741824) { \
                 n1GiB_pages++;  \
              } \
              len = n1GiB_pages*1073741824;
              ptr = reinterpret_cast<(type)*>(mmap(NULL,static_cast<std::size_t>(len), \
              prot,flag,fd,offset)); \
           }while(0)
#endif

double *
gms::common
::gms_edmmap_4KiB(   const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_4KIB_BODY(double)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(double));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}


float *
gms::common
::gms_efmmap_4KiB(   const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_4KIB_BODY(float)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(float));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);

}



int32_t *
gms::common
::gms_immap_4KiB(    const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_4KIB_BODY(int32_t)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(int32_t));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

std::complex<float> *
gms::common
::gms_ec4mmap_4KiB(  const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_4KIB_BODY(std::complex<float>)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(std::complex<float>));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

AVXc8f32 *
gms::common
::gms_avxc8f32_mmap_4KiB( const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_4KIB_BODY(AVXc8f32)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVXc8f32));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

#if defined __AVX512F__
AVX512Vec16 * 
gms::common
::gms_avx512vec16_mmap_4KiB(const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
     assert(length > 0ULL);
#endif
       MMAP_FUNC_4KIB_BODY(AVX512Vec16)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVX12Vec16));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}
#endif

AVXVec8 * 
gms::common
::gms_avxvec8_mmap_4KiB(const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
     assert(length > 0ULL);
#endif
       MMAP_FUNC_4KIB_BODY(AVXVec8)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVXVec8));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);    
}

double *
gms::common
::gms_edmmap_2MiB(   const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_2MIB_BODY(double)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(double));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

float *
gms::common
::gms_efmmap_2MiB(   const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_2MIB_BODY(float)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(float));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);

}

int32_t *
gms::common
::gms_immap_2MiB(    const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_2MIB_BODY(int32_t)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(int32_t));
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

std::complex<float> *
gms::common
::gms_ec4mmap_2MiB(  const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_2MIB_BODY(std::complex<float>)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(std::complex<float>));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

AVXc8f32 *
gms::common
::gms_avxc8f32_mmap_2MiB( const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_2MIB_BODY(AVXc8f32)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVXc8f32));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

#if defined __AVX512F__
AVX512Vec16 * 
gms::common
::gms_avx512vec16_mmap_2MiB(const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
     assert(length > 0ULL);
#endif
       MMAP_FUNC_2MIB_BODY(AVX512Vec16)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVX512Vec16));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}
#endif

AVXVec8 * 
gms::common
::gms_avxvec8_mmap_2MiB(const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
     assert(length > 0ULL);
#endif
       MMAP_FUNC_2MIB_BODY(AVXVec8)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVXVec8));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);    
}

double *
gms::common
::gms_edmmap_1GiB(   const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_1GIB_BODY(double)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(double));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

float *
gms::common
::gms_efmmap_1GiB(   const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_1GIB_BODY(float)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
     if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(float));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);

}

int32_t *
gms::common
::gms_immap_1GiB(    const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_1GIB_BODY(int32_t)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(int32_t));
	if(res) { std::cerr << "mlock() -- failed to lock memory" << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

std::complex<float> *
gms::common
::gms_ec4mmap_1GiB(  const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_1GIB_BODY(std::complex<float>)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(std::complex<float>));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

AVXc8f32 *
gms::common
::gms_avxc8f32_mmap_1GiB( const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
      assert(length > 0ULL);
#endif
      MMAP_FUNC_1GIB_BODY(AVXc8f32)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVXc8f32));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}

#if defined __AVX512F__
AVX512Vec16 * 
gms::common
::gms_avx512vec16_mmap_1GiB(const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
     assert(length > 0ULL);
#endif
       MMAP_FUNC_1GIB_BODY(AVX512Vec16)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVX512Vec16));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);
}
#endif

AVXVec8 * 
gms::common
::gms_avxvec8_mmap_1GiB(const std::size_t length,
		     const int32_t prot,
		     const int32_t flags,
		     const int32_t fd,
		     const off_t offset,
		     const bool lock_mem) {
#if (GMS_DEBUG_ON) == 1
     assert(length > 0ULL);
#endif
       MMAP_FUNC_1GIB_BODY(AVXVec8)
      if((ptr == (void*)(-1))) {
#if (PRINT_CALLSTACK_ON_ERROR) == 1
	  std::cerr << "Requested stack-backtrace -- not implemented yet!!"
#endif
		ABORT_ON_ERROR(__PRETTY_FUNCTION__, MALLOC_FAILED)
      }
      if(lock_mem) {
        int32_t res = mlock(ptr,len*sizeof(AVXVec8));
	if(res) { std::cerr << "mlock() -- failed to lock memory in: " << __PRETTY_FUNCTION__;}
     }
      return (ptr);    
}



