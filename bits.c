/*
 * CS:APP Data Lab
 *
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
  /*
    양수의 경우 logical shift나 arithmetic shift가 동일하기에 음수의 경우만 처리해주면 된다
    먼저 arith 변수에 arithmetic 쉬프트한 변수를 넣는다.
    그리고 inverse_n 변수에 32 - n을 수를 담는다.
    이 inverse_n을 활용하여 논리 이동 후 남을 비트만큼을 마스킹하여 그 결과를 not_zero에 저장한다.
    통상적으로는 not_zero가 결과값이 될 수 있으나 n이 0인 경우 의도치 않은 쉬프트가 일어나기에
    n_zero를 통해 n이 0인 경우 x의 값을 그대로 출력하도록 한다.
  */
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
  /*
    조금 복잡해보이지만 기존의 addOk를 응용한 것이다.
    add_ok 변수는 기존의 addOk 함수의 로직 그대로 이용하여 더하기 시에 오버플로우 여부를 확인한다.
    이때 오버 플로우가 안 일어날 시 그 값을 그대로 출력한다.
    오버 플로우가 일어날 시 x의 부호를 확인하여 양수일 경우 양의 최대값을 음의 경우 음의 최대값을 출력하도록 한다.
    이는 min_int를 이용해 최소 정수를 만들어 x가 음일 때 이 값이 출력되도록 하며,
    x가 양일 때는 min_int를 negate하여 양의 최대값을 출력하도록 한다.
  */
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
  /*
    기본적으로 n번째 비트 밑의 비트를 출력하는 것이 목적이다.
    이때 x가 양수일 경우 큰 문제 없이 마스킹을 통해 구할 수 있다.
    하지만 음수일 경우 나머지 비트를 1로 채워줘야하며 동시에 나머지가 영인 경우에는 아무것도 넣어주지 말아야한다.
    이 과정을 nega_maks가 수행한다.
   */
  int sign = x >> 31;
  int remain = (~(~0 << n) & x);
  int nega_mask = ~((!!remain) << n) + 1;
  return remain + (nega_mask & sign);
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
  count = ((x >> 1) & mask) + count;            //each byte's second bit get and sum
  count = ((x >> 2) & mask) + count;            //each byte's third bit get and sum
  count = ((x >> 3) & mask) + count;            //each byte's forth bit get and sum
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
  /*
    로직은 두 위치의 바이트를 따로 저장 후, 각 위치의 바이트를 0으로 바꾸고 다시 대입하는 것이다.
    이를 위해 n_t에는 n 위치의 바이트를 저장하고, m_t에는 m위치의 바이트를 저장한다.
    이후 각 위치의 값을 0으로 바꾼다.
    마지막으로 바꿀 위치에 각 바이트를 다시 입력한다.
  */
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
  /*
    다 완성하지 못 하였습니다.
  */
  unsigned ux = x;
  unsigned fraction = 0;
  int sign = (ux >> 31);
  int exponent = 0;
  int bias = 127;
  if (sign) {
    ux = ~ux + 1;
  }
  while (ux >> 1) {
    exponent = exponent + 1;
    fraction = (fraction >> 1) | ((ux & 1) << 31);
    ux = ux >> 1;
  }
  if (!ux)
    return 0;
  return sign << 31 | ((exponent + bias) << 23) | fraction >> 9;
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
  /*
    로직은 다음과 같다. 먼저 비트에서 사인을 추출하고, exp, frac 부분을 추출해낸다.
    이후 exp를 확인하여 정상 숫자가 아닌 경우 그대로 출력한다.
    이외의 경우 exp를 1 올려 곱하기 2를 달성한다.
    이때 만약 exp의 값이 0인 경우 denomalized의 경우이므로 frac만을 비트 왼쪽으로 쉬프르 하여 곱하기를 달성한다.
    이때 만약 frac이 denomalized의 최대값인 경우 노말라이즈 되도록 exp를 올려주고 frac을 1 감소시킨다.
   */
  unsigned exp, sign, frac, frac_mask;
  exp = (uf >> 23) & 0xFF;
  sign = !!(uf >> 31);
  frac_mask = ~0;
  frac_mask = frac_mask >> 9;
  frac = uf & frac_mask;
  if (exp == 255 || (exp == 0 && frac == 0))
    return uf;
  if (exp) {
    exp++;
  } else if (frac == frac_mask) {
    frac--;
    exp++;
  } else {
    frac <<= 1;
  }

  return (sign<<31) | (exp << 23) | (frac);
}
