#ifndef BIT_MATH_H
#define BIT_MATH_H

// Macros for bit manipulation
#define Set_Bit(REG,BIT)        (REG |= (1 << BIT))
#define Clr_Bit(REG,BIT)        (REG &= ~(1 << BIT))
#define Toggle_Bit(REG,BIT)     (REG ^= (1 << BIT))
#define Get_Bit(REG,BIT)        ((REG >> BIT) & 1)

#endif // BIT_MATH_H

