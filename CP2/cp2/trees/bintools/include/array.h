/*
 * Copyright (c) 2009, 2014 David A. Holland.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Author nor the names of any contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef ARRAY_H
#define ARRAY_H

//#include <assert.h>
#include "mem.h"


/*
 * Typed resizeable array.
 */

#define ARRAYS_CHECKED

#ifdef ARRAYS_CHECKED
#define ARRAYASSERT assert
#else
#define ARRAYASSERT(x) ((void)(x))
#endif

/*
 * Usage:
 *
 *    DECLARRAY_FULL(NAME, T, INLINE)
 *
 * Define the type "struct NAME", which is an array of type T, and
 * declare its methods using storage class INLINE.
 *
 *    DECLARRAY(T, INLINE)
 *    DECLBASEARRAY(ST, T, INLINE)
 *
 * These are shortcut forms for the common cases: DECLARRAY produces
 * an array of pointers to T, and calls it "struct Tarray";
 * DECLBASEARRAY produces an array of T, where T is a base type, and
 * calls it "struct STarray", where ST should generally be a
 * single-word version of T. (e.g. uint, longdouble).
 *
 * To convert old code that uses DECLARRAY_BYTYPE, change
 *    DECLARRAY_BYTYPE(NAME, T, INLINE)
 * to
 *    DECLARRAY_FULL(NAME, T *, INLINE)
 *
 * The corresponding DEFARRAY forms define the array operations.
 *
 * INLINE should be used as follows:
 *
 *    - for a file-static array, use "static UNUSED inline" (or just
 *      "static UNUSED") and put both the DECL and DEF in the source
 *      file.
 *
 *    - for no inlining at all, use "" as the INLINE argument, put
 *      the DECL in a header file, and the DEF in a source file.
 *
 *    - for full inlining, including for older gcc, in foo.h put
 *         #ifndef FOO_INLINE
 *         #define FOO_INLINE C99INLINE
 *         #endif
 *         DECLARRAY(foo, FOO_INLINE);
 *         DEFARRAY(foo, FOO_INLINE);
 *      and in foo.c put
 *         #define FOO_INLINE
 *         #include "foo.h"
 *
 * ... I think. This is all very complicated because of the mess gcc
 * made.
 *
 * The operations are:
 *    init - initialize a preallocated array
 *    cleanup - deinitialize a preallocated array; array must be empty
 *    create - allocate and call init
 *    destroy - call cleanup and deallocate
 *    num - get the number of elements
 *    get - get the ith element
 *    set - set the ith element
 *    setsize - adjust the size up or down
 *    addx - add to the end and return the index
 *    add - add to the end
 *    insert - insert a slot and shift subsequent entries up
 *    remove - remove a slot and shift subsequent entries down
 *
 * Newly added slots are not initialized; the caller should do that.
 * Likewise, removed slots are overwritten/discarded; if cleanup is
 * needed the caller should do this first. (The restriction that only
 * empty arrays may be destroyed is to help make sure this gets done.)
 *
 * Note that insert and remove are expensive if done often.
 */

////////////////////////////////////////////////////////////
// external untyped helper operations
// (do not call these directly)

void *array_realloc(void *ptr, size_t elemsize, unsigned num, unsigned *max);
void array_shiftright(void *ptr, size_t elemsize, unsigned lp, unsigned rp);
void array_shiftleft(void *ptr, size_t elemsize, unsigned lp, unsigned rp);

////////////////////////////////////////////////////////////
// declare an array

#define DECLARRAY_FULL(ARRAY, T, INL) \
	struct ARRAY {							\
	   T *v;							\
	   unsigned num, max;						\
	};								\
									\
	INL void ARRAY##_init(struct ARRAY *a);				\
	INL void ARRAY##_cleanup(struct ARRAY *a);			\
	INL struct ARRAY *ARRAY##_create(void);				\
	INL void ARRAY##_destroy(struct ARRAY *a);			\
	INL unsigned ARRAY##_num(const struct ARRAY *a);		\
	INL T *ARRAY##_getdata(const struct ARRAY *a);			\
	INL T ARRAY##_get(const struct ARRAY *a, unsigned index);	\
	INL T *ARRAY##_getptr(const struct ARRAY *a, unsigned index);	\
	INL void ARRAY##_set(struct ARRAY *a, unsigned index, T val);	\
	INL void ARRAY##_setsize(struct ARRAY *a, unsigned num);	\
	INL void ARRAY##_addx(struct ARRAY *a, T val, unsigned *index_ret); \
	INL void ARRAY##_add(struct ARRAY *a, T val);			\
	INL void ARRAY##_insert(struct ARRAY *a, unsigned index);	\
	INL void ARRAY##_remove(struct ARRAY *a, unsigned index)

////////////////////////////////////////////////////////////
// define an array

#define DEFARRAY_FULL(ARRAY, T, INL) \
	INL void ARRAY##_init(struct ARRAY *a) {		\
	   a->v = NULL;						\
	   a->num = a->max = 0;					\
	}							\
								\
	INL void ARRAY##_cleanup(struct ARRAY *a) {		\
	   ARRAYASSERT(a->num == 0);				\
	   dofree(a->v, a->max * sizeof(a->v[0]));		\
	}							\
								\
	INL struct ARRAY *ARRAY##_create(void) {		\
	   struct ARRAY *a = domalloc(sizeof(*a));		\
	   ARRAY##_init(a);					\
	   return a;						\
	}							\
								\
	INL void ARRAY##_destroy(struct ARRAY *a) {		\
	   ARRAY##_cleanup(a);					\
	   dofree(a, sizeof(*a));				\
	}							\
								\
	INL unsigned ARRAY##_num(const struct ARRAY *a) {	\
	   return a->num;					\
	}							\
								\
	INL T *ARRAY##_getdata(const struct ARRAY *a) {		\
	   return a->v;						\
	}							\
								\
	INL T ARRAY##_get(const struct ARRAY *a, unsigned index) { \
	   ARRAYASSERT(index < a->num);				\
	   return a->v[index];					\
	}							\
								\
	INL T *ARRAY##_getptr(const struct ARRAY *a, unsigned index) { \
	   ARRAYASSERT(index < a->num);				\
	   return &a->v[index];					\
	}							\
								\
	INL void ARRAY##_set(struct ARRAY *a, unsigned index, T val) { \
	   ARRAYASSERT(index < a->num);				\
	   a->v[index] = val;					\
	}							\
								\
	INL void ARRAY##_setsize(struct ARRAY *a, unsigned num) { \
	   if (num > a->max) {					\
	      a->v = array_realloc(a->v, sizeof(a->v[0]), num, &a->max); \
	   }							\
	   a->num = num;					\
	}							\
								\
	INL void ARRAY##_addx(struct ARRAY *a, T val, unsigned *index_ret) { \
	   unsigned index = a->num;				\
	   ARRAY##_setsize(a, index+1);				\
	   a->v[index] = val;					\
	   if (index_ret != NULL) {				\
	      *index_ret = index;				\
	   }							\
	}							\
								\
	INL void ARRAY##_add(struct ARRAY *a, T val) { 		\
	   ARRAY##_addx(a, val, NULL);				\
	}							\
								\
	INL void ARRAY##_insert(struct ARRAY *a, unsigned index) { \
	   unsigned oldnum = a->num;				\
	   ARRAY##_setsize(a, oldnum + 1);			\
	   array_shiftright(a->v, sizeof(a->v[0]), index, oldnum); \
	}							\
								\
	INL void ARRAY##_remove(struct ARRAY *a, unsigned index) { \
	   array_shiftleft(a->v, sizeof(a->v[0]), index+1, a->num); \
	   ARRAY##_setsize(a, a->num - 1);			\
	}

////////////////////////////////////////////////////////////
// short forms

#define DECLARRAY(T, I)		DECLARRAY_FULL(T##array, struct T *, I)
#define DECLBASEARRAY(T, S, I)	DECLARRAY_FULL(S##array, T, I)

#define DEFARRAY(T, I)		DEFARRAY_FULL(T##array, struct T *, I)
#define DEFBASEARRAY(T, S, I)	DEFARRAY_FULL(S##array, T, I)

////////////////////////////////////////////////////////////
// additional operations

/*
 * destroyall - call FUNC (normally T##_destroy) on all elements and
 * set the size to 0. This tends to only make sense for arrays of
 * pointers, so no BASE forms of the macros are provided.
 */
#define DECLARRAY_DESTROYALL_FULL(ARRAY, INL) \
	INL void ARRAY##_destroyall(struct ARRAY *a);
#define DEFARRAY_DESTROYALL_FULL(ARRAY, FUNC, INL) \
	INL void ARRAY##_destroyall(struct ARRAY *a) {		\
	   unsigned i, num;					\
	   num = ARRAY##_num(a);				\
	   for (i=0; i<num; i++) {				\
	      FUNC(ARRAY##_get(a, i));				\
	   }							\
	   ARRAY##_setsize(a, 0);				\
	}

#define DECLARRAY_DESTROYALL(T, I) DECLARRAY_DESTROYALL_FULL(T##array, I)
#define DEFARRAY_DESTROYALL(T, I) \
		DEFARRAY_DESTROYALL_FULL(T##array, T##_destroy, I)

/*
 * remunsorted - remove in an unsorted fashion. Unlike remove, this
 * doesn't shift things around; if the ordering of the array doesn't
 * matter it's much more efficient.
 */
#define DECLARRAY_REMUNSORTED_FULL(ARRAY, INL) \
	INL void ARRAY##_remunsorted(struct ARRAY *a, unsigned index);
#define DEFARRAY_REMUNSORTED_FULL(ARRAY, T, INL) \
	INL void ARRAY##_remunsorted(struct ARRAY *a, unsigned index) { \
	   unsigned num = ARRAY##_num(a);			\
	   ARRAYASSERT(index < num);				\
	   if (index < num - 1) {				\
	      ARRAY##_set(a, index, ARRAY##_get(a, num - 1));	\
	   }							\
	   ARRAY##_setsize(a, num - 1);				\
	}

#define DECLARRAY_REMUNSORTED(T, I) DECLARRAY_REMUNSORTED_FULL(T##array, I)
#define DEFARRAY_REMUNSORTED(T, I) \
		DEFARRAY_REMUNSORTED_FULL(T##array, struct T *, I)

/*
 * sort - sort.
 *
 * Because of various restrictions (e.g. qsort(3) doesn't accept a
 * data pointer to be passed through) the comparison function needs to
 * be compiled in; therefore this needs to be redefined for every
 * different sort function. For this reason it shouldn't be inlined;
 * INL should either be empty or "static".
 *
 * FUNC is the sort function and HOW should be empty if it's unique or
 * some identifier for it, e.g. byname.
 *
 * The resulting function is ARRAY##_sort##HOW, e.g.
 * objectarray_sortbyname.
 */
#define DECLARRAY_SORT_FULL(ARRAY, T, HOW, INL) \
	INL void ARRAY##_sort##HOW(struct ARRAY *a, \
					int (*cmp)(const T, const T));

#define DEFARRAY_SORT_FULL(ARRAY, T, HOW, FUNC, INL) \
	static int ARRAY##_sortcmp##HOW(const void *av, const void *bv) { \
	   T a = *(const T *)av;				\
	   T b = *(const T *)bv;				\
	   return FUNC(a, b);					\
	}							\
	INL void ARRAY##_sort##HOW(struct ARRAY *a) {		\
	   qsort(a->v, a->num, sizeof(a->v[0]), ARRAY##_sortcmp##HOW); \
	}

#define DECLARRAY_SORT(T, HOW, I) \
		DECLARRAY_SORT_FULL(T##array, struct T *, HOW, I)
#define DEFARRAY_SORT(T, HOW, FUNC, I) \
		DEFARRAY_SORT_FULL(T##array, struct T *, HOW, FUNC, I)

////////////////////////////////////////////////////////////
// basic array types

#ifndef ARRAYINLINE
#define ARRAYINLINE INLINE
#endif

#include <stdbool.h>

/* array of bool: boolarray */
DECLARRAY_FULL(boolarray, bool, ARRAYINLINE);
DEFARRAY_FULL(boolarray, bool, ARRAYINLINE);

/* array of int: intarray */
DECLARRAY_FULL(intarray, int, ARRAYINLINE);
DEFARRAY_FULL(intarray, int, ARRAYINLINE);

/* array of unsigned int: uintarray */
DECLARRAY_FULL(uintarray, unsigned, ARRAYINLINE);
DEFARRAY_FULL(uintarray, unsigned, ARRAYINLINE);

/* array of size_t: sizearray */
DECLARRAY_FULL(sizearray, size_t, ARRAYINLINE);
DEFARRAY_FULL(sizearray, size_t, ARRAYINLINE);

/* array of char *: stringarray */
DECLARRAY_FULL(stringarray, char *, ARRAYINLINE);
DEFARRAY_FULL(stringarray, char *, ARRAYINLINE);

/* array of void *: ptrarray */
DECLARRAY_FULL(ptrarray, void *, ARRAYINLINE);
DEFARRAY_FULL(ptrarray, void *, ARRAYINLINE);


#endif /* ARRAY_H */
