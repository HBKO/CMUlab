/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
//1
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  return ~((~x)&(~y));
}
/* 
 * specialBits - return bit pattern 0xffca3fff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 3
 *   Rating: 1
 */
int specialBits(void) {

//return (~0x00)^(0xd7<<14);


 //   return ~(0x0035c000);
  return ~(0xd7<<14);

}
//2
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  return !x;
}
/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
    int mask=(0x55<<8)+0x55;
    mask=(mask<<16)+mask;
    return !!(x&mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2 
 */
int negate(int x) {

  return (~x)+1;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {

  return ((~x)+1)&x;
}
//3
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  int side=0x21+~n;

  int mask=(0x1<<n)+~0x0;//make the mask
//  return ((x << n) | ((y >> side)&mask));
  return ((x<<n)|((x>>side)&(mask)));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int mask=(1<<n)+~0;
  int ispositive=(x>>31)&mask;  
  return (x+ispositive)>>n;    //if x is negative ,then and -1<=> (11111)=(-1)
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
  int sign_x=x>>31;
  int sign_y=y>>31;
  int mask=sign_x^sign_y;
  int a=(x+(~y+1))>>31;
  int b=!(sign_y);
  //A control-loke statement.((statement & a)|((statement|(b))))
  //Returns a if statement=11111111
  //Returns (b&1) if statement=00000000
  return ((mask&b)|((~mask&a)&1));
}
//4
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  int mask_1=!!x;//tell if x==zero
  int mask_2=x>>31;  // tell if x==negative
  int mask_3=(mask_2^1)&mask_1;   
  int Power2=!((x&(~x+1))^x);////tell if x has at most a bit of 1
  return (mask_3&Power2);
}
/*
 * bitReverse - Reverse bits in a 32-bit word
 *   Examples: bitReverse(0x80000002) = 0x40000001
 *             bitReverse(0x89ABCDEF) = 0xF7D3D591
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 45
 *   Rating: 4
 */
int bitReverse(int x) {
  //divide and conquer
  int mask=0x55;
     mask=(mask<<8)+0x55;
     mask=(mask<<16)+mask;   
  x=(((x&mask)<<1)|((x>>1)&mask));
  mask=0x33;
  mask=(mask<<8)+0x33;
  mask=(mask<<16)+mask; 
  x=(((x&mask)<<2)|((x>>2)&mask));
  mask=0x0f;
  mask=(mask<<8)+0x0f;
  mask=(mask<<16)+mask;
  x=(((x&mask)<<4)|((x>>4)&mask));
 // mask=0xff;
 // mask=(mask<<8)+0x00;
 // mask=(mask<<16)+mask;
  mask=(0xff<<16)+0xff;
  x=(((x&mask)<<8)|((x>>8)&mask));
  mask=(0xff<<8)+0xff;
  x=(((x&mask)<<16)|((x>>16)&mask));
  return x;
}
//float
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  int mask_1=0x7fffffff;
  int mask_2=0x7f800000;
  int mask_3=0x007fffff;
  if((!((uf&mask_2)^mask_2))&&(!!(uf&mask_3))) return uf;
  else return uf&mask_1;
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
  int sign=(x&0x80000000);
  int exp;
  int frac=0;
  int frac_mask=0x7fffff;
  int delta;
  int i=30;
  if(x==0) return 0;
  else if(x==0x80000000) exp=158;
  else{

    if(!!sign) x=-x;
    while(!(x>>i))
      i--;
    exp=i+127;//get the exp
    x=x<<(31-i); //clean the zero
    frac=(x>>8)&frac_mask; //get the frac
    x=x&0xff;
    delta=(x>128)||((x==128)&&(frac&1)); //round
    frac+=delta;
    if(frac>>23)
    {
      frac=frac&frac_mask;
      exp=exp+1;
    }
  }
  return (sign)|(exp<<23)|frac;
}
/* 
 * float_times64 - Return bit-level equivalent of expression 64*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 35
 *   Rating: 4
 */
unsigned float_times64(unsigned uf) {
   int sign=uf&0x80000000;
   int exp=(uf&0x7f800000)>>23;
   int frac=uf&0x7fffff;
   int exp_add=6;
   if(exp==0)
   {
    if(frac==0) return uf;   //uf==0
    else                    //uf==denormal
    {
      while(exp_add>0)
      {
        frac=frac<<1;
        if(frac>0x7fffff)
        {
          exp=exp+exp_add;
          exp_add=0;
        }
        else
          exp_add=exp_add+0xffffffff;
      }
      frac=frac&0x7fffff;
    }
  }
  else if(exp==0xff)   //exp=0x111111...
  {
        if(!!frac)  return uf;   //uf==NaN
  }
   else            //normal
   {
        exp=exp+exp_add;
        if(exp>254) //overflow
        {
          exp=255;
          frac=0;
        } 
   }
   return sign|(exp<<23)|frac;
}
