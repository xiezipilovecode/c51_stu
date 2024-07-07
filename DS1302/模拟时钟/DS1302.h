#ifndef __DS1302_H__
#define __DS1302_H__
typedef unsigned char u8;
extern char DSl302_Time[];  // 声明为外部变量，其他文件可以进行调用
void DS1302_Init();
u8 DS1302_ReadByte(u8 command);
void DS1302_WriteByte(u8 command, u8 write_data);
u8 Code8421_Decimal(unsigned char Data, mode);
void DS1302_SetTime();
#endif