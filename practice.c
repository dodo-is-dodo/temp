#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned float_i2f(int x) {
  unsigned ux = x;
  unsigned fraction = 0;
  int sign = (ux >> 31);
  int exponent = 0;
  int bias = (1 << 7) - 1;
  printf("bias : %d\n", bias);
  if (sign) {
    ux = ~ux + 1;
    printf("x : %d\n", ux);
  }
  printf("sign : %d\n", sign);
  while (ux >> 1) {
    exponent = exponent + 1;
    fraction = (fraction >> 1) | ((ux & 1) << 31);
    ux = ux >> 1;
  }
  
  printf("exponent : %d\n", exponent);
  printf("fraction : %d\n", fraction);
  if (!ux)
    return 0;
  return sign << 31 | ((exponent + bias) << 23) | fraction >> 9;
}
int isGreater(int x, int y) {
  int s1 = ~((x  ^ y ) >> 31);
  int s2 =  ~((((x + ~y + 1)  ^ x ) >> 31));
  int diff = x + ~y + 1;
  int subOk = s1 | s2;
  printf("sub ok : %d\n", subOk);
  printf("diff : %d\n", diff);
  printf("diff : %d\n", !!diff);
  printf("final : %d\n", !(diff >> 31));
  return (subOk & (!!diff) & (!(diff >> 31))) | (~subOk & !(x >> 31));
  /* int s = (x ^ y) >> 31; */
  /* int x_y_sign = s & ~(x >> 31); */
  /* int diff = !((x + ~y + 1) >> 31); */
}

void print_bits(unsigned int x)
{
  int i;
  for(i=8*sizeof(x)-1; i>=0; i--) {
    (x & (1 << i)) ? putchar('1') : putchar('0');
  }
  printf("\n");
}
int main(int argc, char *argv[])
{
  int x, y;
  x = INT_MAX;
  y = 1 << 31;
  float f = INT_MIN + 1;
  /* int s1 = !!((x ^ y) >> 31); */
  /* int s2 = !(((x + y) ^ x) >> 3/\* 1); *\/ */
  /* print_bits(-822083584); */
  /* print_bits(float_i2f(INT_MIN + 1)); */
  /* printf("%d\n", float_i2f(INT_MIN)); */
  /* printf("%d\n", INT_MIN>>31); */
  /* printf("%d\n", isGreater(INT_MIN, 0)); */
  print_bits(-35);
  print_bits(-3);
  /* return 0 */;
}
