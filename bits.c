/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * <이도현(Dohyun Lee) 2012313610>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  /*
    목표는 두 숫자의 부호가 같지만 더한 값은 다르다는 것을 확인하는 것이다.
    s1는 두 숫자의 부호가 같으면 0, 다르면 1이 된다.
    s2 두 숫자의 합과 x의 부호가 같으면 1, 다르면 0이 되도록 했다.
    결국 s1도 0이고 s2도 0이라면 오버플로우가 발생했다는 것을 확인할 수 있다.
   */
  int s1 = !!((x ^ y) >> 31);
  int s2 = !(((x + y) ^ x) >> 31);
  return s1 | s2;
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  /*
    목표는 두 숫자의 부호가 같지만 더한 값은 다르다는 것을 확인하는 것이다.
    s1는 두 숫자의 부호가 같으면 0, 다르면 1이 된다.
    s2 두 숫자의 합과 x의 부호가 같으면 1, 다르면 0이 되도록 했다.
    결국 s1도 0이고 s2도 0이라면 오버플로우가 발생했다는 것을 확인할 수 있다.
  */
  int s1 = ((x  ^ y ) >> 31) + 1;
  int s2 =  !((((x + ~y + 1)  ^ x ) >> 31));
  return s1 | s2;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int n_zero = !n + (~0);
  int arith = (x >> n);
  int inverse_n = (32 + (~n + 1));
  int not_zero =  arith & (~((~0) << inverse_n));
  return (n_zero & not_zero) | (~n_zero & x);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /* int s1 = ~((x  ^ y ) >> 31); */
  /* int s2 =  ~((((x + ~y + 1)  ^ x ) >> 31)); */
  /* int diff = x + ~y + 1; */
  /* int subOk = s1 | s2; */
  int msbx = ((x>>31)&0x01);
  int msby = ((y>>31)&0x01); 
  int samesign = !(msbx^msby);        //To check if both numbers are of same sign
  int resultmask = !samesign + (~0);
  int result1 = (!((x+(~y)+1)>>31)&0x01)&(!!(x^y));
  int result2 = !msbx;
    
  return ((resultmask&result1)|(~resultmask&result2)); /* return (subOk & (!!diff) & (!(diff >> 31))) | (~subOk & !(x >> 31)); */
}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  int s1 = (x ^ y) >> 31;
  int s2 = ~(((x + y) ^ x) >> 31);
  int add_ok = s1 | s2;
  int x_sign = x >> 31;
  int min_int = 1 << 31;
  int sum = (x + y);
  return (sum & add_ok) | (((min_int & x_sign) | (~min_int & ~x_sign)) & ~add_ok);
}
/* 
 * rempwr2 - Compute x%(2^n), for 0 <= n <= 30
 *   Negative arguments should yield negative remainders
 *   Examples: rempwr2(15,2) = 3, rempwr2(-35,3) = -3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int rempwr2(int x, int n) {
  /* int s = (x >> 31); */
  /* int remain = (~(~0 << n) & x); */
  /* int chk_zero = ((!!remain) << 31) >> 31; */
  /* /\* printf("s : %d\n", s); *\/ */
  /* /\* printf("remain : %d\n", remain); *\/ */
  /* /\* printf("chk_zero : %d\n", chk_zero); *\/ */
  /* return (~s & remain) | (chk_zero & s & (remain | s)); */
  int power = (1 << n) + ~0;  // 2^n - 1
  int mask = x >> 31;
  int result = x & power;
  return (x & power) + (((~((!!result) << n)) + 1) & mask);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
      int mask = 0x11, count, checker = 0x0f, result;			//variable declaration
    mask = (mask << 8) + mask;								//mask = 0001 0001 0001 0001
    mask = (mask << 16) + mask;								//mask = 0001 0001 0001 0001 0001 0001 0001 0001 0001 0001
	count = x&mask;											//each byte's first bit get
	count = ((x >> 1) & mask) + count; 						//each byte's second bit get and sum
	count = ((x >> 2) & mask) + count; 						//each byte's third bit get and sum
	count = ((x >> 3) & mask) + count; 						//each byte's forth bit get and sum
	result = (count & checker);								//sum 1st byte's number of bits
	result = ((count >> 4) & checker) + result;				//sum 2nd byte's number of bits
	result = ((count >> 8) & checker) + result;				//sum 3rd byte's number of bits
	result = ((count >> 12) & checker) + result;			//sum 4th byte's number of bits
	result = ((count >> 16) & checker) + result;			//sum 5th byte's number of bits
	result = ((count >> 20) & checker) + result;			//sum 6th byte's number of bits
	result = ((count >> 24) & checker) + result;			//sum 7th byte's number of bits
	result = ((count >> 28) & checker) + result;			//sum 8th byte's number of bits
	return result;   //return value
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int nb = n << 3;
  int mb = m << 3;
  int n_t = (x >> nb) & 0xff;
  int m_t = (x >> mb) & 0xff;
  x = x & (~(0xff << nb) & ~(0xff << mb));
  x = x + ((n_t << mb) | (m_t << nb));
  return x;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  /* unsigned ux = x; */
  /* unsigned fraction = 0; */
  /* int sign = (ux >> 31); */
  /* int exponent = 0; */
  /* int bias = 127; */
  /* if (sign) { */
  /*   ux = ~ux + 1; */
  /* } */
  /* while (ux >> 1) { */
  /*   exponent = exponent + 1; */
  /*   fraction = (fraction >> 1) | ((ux & 1) << 31); */
  /*   ux = ux >> 1; */
  /* } */
  /* if (!ux) */
  /*   return 0; */
  /* return sign << 31 | ((exponent + bias) << 23) | fraction >> 9; */
  unsigned sign, fraction, exponent = 150, temp, b = 2, top, bottom;
  if (x == 0) return 0;
  if (x == 0x80000000) return 3472883712u;
  sign = (x & 0x80000000);
  fraction = (sign) ? (-x) : (x);

  temp = fraction;
  while (temp & 0xFF000000) {
    /* standard rounding */
    temp = (fraction + (b / 2)) / (b);
    b <<= 1;
    exponent++;
  }
  while (temp <= 0x007FFFFF) {
    temp <<= 1;
    exponent--;
  }
  if (fraction & 0xFF000000) {
    b = 1 << (exponent - 150);

    temp = fraction / b;
    bottom = fraction % b;
    top = b - bottom;

    /* if temp is closer to fraction/b than fraction/b + 1, or its odd,
       round up */
    if ((top < bottom) || ((top == bottom) & temp))
      ++temp;

    fraction = temp;
  } else {
    while (fraction <= 0x007FFFFF)
      fraction <<= 1;
  }

  return (sign) | (exponent << 23) | (fraction & 0x007FFFFF);
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  unsigned expn = (uf >> 23) & 0xFF;
  unsigned sign = uf & 0x80000000;
  unsigned frac = uf & 0x007FFFFF;
  if (expn == 255 || (expn == 0 && frac == 0))
    return uf;

  if (expn) {
    expn++;
  } else if (frac == 0x7FFFFF) {
    frac--;
    expn++;
  } else {
    frac <<= 1;
  }

  return (sign) | (expn << 23) | (frac);
}
