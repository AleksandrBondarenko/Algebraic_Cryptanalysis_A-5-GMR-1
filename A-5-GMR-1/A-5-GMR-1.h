#pragma once
#include <iostream>
void rotate_1(unsigned int &reg_1)
{
reg_1 = ((reg_1 << 1) | (((reg_1 >> 18) ^ (reg_1 >> 17) ^ (reg_1 >> 16) ^ (reg_1 >> 13)) & 1)) & 0x7ffff;
}
void rotate_2(unsigned int &reg_2)
{
reg_2 = ((reg_2 << 1) | (((reg_2 >> 21) ^ (reg_2 >> 20) ^ (reg_2 >> 16) ^ (reg_2 >> 12)) & 1)) & 0x3fffff;
}
void rotate_3(unsigned int &reg_3)
{
reg_3 = ((reg_3 << 1) | (((reg_3 >> 22) ^ (reg_3 >> 21) ^ (reg_3 >> 18) ^ (reg_3 >> 17)) & 1)) & 0x7fffff;
}
void rotate_4(unsigned int &reg_4)
{
reg_4 = ((reg_4 << 1) | (((reg_4 >> 16) ^ (reg_4 >> 13) ^ (reg_4 >> 12) ^ (reg_4 >> 8)) & 1)) & 0x1ffff;
}
unsigned int rotate_1234(unsigned int &reg_1, unsigned int &reg_2,
unsigned int &reg_3, unsigned int &reg_4)
{
unsigned int ctrl = (((reg_4 >> 15) & 1) << 2) | (((reg_4 >> 6) & 1) << 1) | (((reg_4 >> 1) & 1) << 0);
if (((0xE8 >> ctrl) & 1) == ((reg_4 >> 15) & 1))
{
rotate_1(reg_1);
}
if (((0xE8 >> ctrl) & 1) == ((reg_4 >> 6) & 1))
{
rotate_2(reg_2);
}
if (((0xE8 >> ctrl) & 1) == ((reg_4 >> 1) & 1))
{
rotate_3(reg_3);
}
unsigned int sum_1 = (((reg_1 >> 15) & 1) << 2) | (((reg_1 >> 6) & 1) << 1) | (((reg_1 >> 1) & 1) << 0);
unsigned int sum_2 = (((reg_2 >> 14) & 1) << 2) | (((reg_2 >> 8) & 1) << 1) | (((reg_2 >> 3) & 1) << 0);
unsigned int sum_3 = (((reg_3 >> 19) & 1) << 2) | (((reg_3 >> 15) & 1) << 1) | (((reg_3 >> 4) & 1) << 0);
rotate_4(reg_4);
return ((0xE8 >> sum_1) & 1) ^ ((0xE8 >> sum_2) & 1) ^ ((0xE8 >> sum_3) & 1) ^ ((reg_1 >> 11) & 1) ^ ((reg_2 >> 1) & 1) ^ ((reg_3 >> 0) & 1);
}
void init_1234(unsigned int &reg_1, unsigned int &reg_2,
unsigned int &reg_3, unsigned int &reg_4, unsigned __int64 key)
{
for (unsigned int i = 0; i < 64; i++)
{
rotate_1(reg_1);
rotate_2(reg_2);
rotate_3(reg_3);
rotate_4(reg_4);
reg_1 ^= ((unsigned int)((key >> i) & 1));
reg_2 ^= ((unsigned int)((key >> i) & 1));
reg_3 ^= ((unsigned int)((key >> i) & 1));
reg_4 ^= ((unsigned int)((key >> i) & 1));
}
reg_1 |= 1;
reg_2 |= 1;
reg_3 |= 1;
reg_4 |= 1;
for (int i = 0; i < 250; i++)
{
rotate_1(reg_1);
rotate_2(reg_2);
rotate_3(reg_3);
rotate_4(reg_4);
}
}
