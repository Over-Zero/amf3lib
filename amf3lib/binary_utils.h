#ifndef BINARY_CONSTANTS_H
#define BINARY_CONSTANTS_H

#define HEX__(_x) 0x##_x##LU

#define B8__(_x) \
    ((_x & 0x0000000FLU) ? 0x01 : 0) + \
    ((_x & 0x000000F0LU) ? 0x02 : 0) + \
    ((_x & 0x00000F00LU) ? 0x04 : 0) + \
    ((_x & 0x0000F000LU) ? 0x08 : 0) + \
    ((_x & 0x000F0000LU) ? 0x10 : 0) + \
    ((_x & 0x00F00000LU) ? 0x20 : 0) + \
    ((_x & 0x0F000000LU) ? 0x40 : 0) + \
    ((_x & 0xF0000000LU) ? 0x80 : 0)

#define B8(_x) ((unsigned char)B8__(HEX__(_x)))

#define B16(_x1, _x2) (((unsigned short)B8(_x1) << 8) + B8(_x2))

#define B24(_x1, _x2, _x3) (\
    ((unsigned long)B8(_x1) << 16) + \
    ((unsigned long)B8(_x2) << 8) + \
    B8(_x3))

#define B32(_x1, _x2, _x3, _x4) (\
    ((unsigned long)B8(_x1) << 24) + \
    ((unsigned long)B8(_x2) << 16) + \
    ((unsigned long)B8(_x3) << 8) + \
    B8(_x4))

#endif // BINARY_CONSTANTS_H
