#include <REGX52.H>

typedef unsigned char u8;

// 定义DS1302引脚
sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

// 配置命令
#define DS1302_SECOND   0x80
#define DS1302_MINUTE   0x82
#define DS1302_HOUR     0x84
#define DS1302_DATE     0x86
#define DS1302_MONTH    0x88
#define DS1302_DAY 		0x8A
#define DS1302_YEAR		0x8C
#define DS1302_WP		0x8E

u8 DSl302_Time[] = {24, 7, 4, 23, 59, 55, 4};  // 定义日期时间

/*
    *  @brief  初始化DS1302
    *  @param
    *  @retval 
*/
void DS1302_Init(){
	// 初始化引脚
	DS1302_SCLK = 0;
	DS1302_CE = 0;
}

/*
    *  @brief  读取DS1302数据
    *  @param  控制指令
    *  @retval 返回读取到的数据，一个字节
*/
u8 DS1302_ReadByte(u8 command){
	u8 i, read_data=0x00;
	command |= 0x01;  // 最低位为高电平表示读数据
	DS1302_CE = 1;
	
	// 首先读取命令，高电平触发
	for (i=0; i<8; ++i){
		DS1302_IO = command&(0x01<<i);  // 读取一个字节的指定为，例如，i=2，读取command第二位
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;  // 这里和写数据不一样
	}
	
	// 接下来读取数据，低电平触发
	for (i=0; i<8; ++i){
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if(DS1302_IO) {
			read_data |= (0x01<<i);  // 指定位置写入数据 
		}
	}
	
	DS1302_CE = 0;
	DS1302_IO = 0;
	return read_data;
}

/*
    *  @brief  向DS1302写入数据
    *  @param  控制命令、需要写入的数据
    *  @retval 
*/
void DS1302_WriteByte(u8 command, u8 write_data){
	u8 i;
	DS1302_CE = 1;
	// 首先读取命令，高电平触发
	for (i=0; i<8; ++i){
		DS1302_IO = command&(0x01<<i);  // 读取一个字节的指定为，例如，i=2，读取command第二位
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	// 接下来写入数据，高电平触发
	for (i=0; i<8; ++i){
		DS1302_IO = write_data&(0x01<<i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	DS1302_CE = 0;
}

/*
*  @brief  8421码转为十进制，这里适用于两位的BCD码
*  @param  Data:BCD码，mode: 0/1  mode为0表示BCD码转十进制，反之为十进制转为BCD码
*  @retval  转换为十进制的BCD码
*/
u8 Code8421_Decimal(unsigned char Data, mode){
	unsigned char result;
	if (mode)  result = Data / 16 * 10 + Data % 16;
	else result = (Data / 10) * 16 + Data % 10;
	return result;
}

/*
*  @brief  为DS1302设置初始日期时间
*  @param
*  @retval 
*/
void DS1302_SetTime(){
	// 设置时间
	DS1302_WriteByte(DS1302_WP, 0x00);  // 打开写保护
	// 年月日时分秒星期设置
	DS1302_WriteByte(DS1302_YEAR, Code8421_Decimal(DSl302_Time[0], 0));
	DS1302_WriteByte(DS1302_MONTH, Code8421_Decimal(DSl302_Time[1], 0)); 
	DS1302_WriteByte(DS1302_DAY, Code8421_Decimal(DSl302_Time[2], 0));
	DS1302_WriteByte(DS1302_HOUR, Code8421_Decimal(DSl302_Time[3], 0));
	DS1302_WriteByte(DS1302_MINUTE, Code8421_Decimal(DSl302_Time[4], 0));
	DS1302_WriteByte(DS1302_SECOND, Code8421_Decimal(DSl302_Time[5], 0));
	DS1302_WriteByte(DS1302_DATE, Code8421_Decimal(DSl302_Time[6], 0));
	DS1302_WriteByte(DS1302_WP, 0x80);  // 关闭写保护
}

/*
*  @brief  读取DS1302中的当前日期时间
*  @param
*  @retval 
*/
void DS1302_ReadTime() {
	// 读取数据保存到数组中，这里将BCD码转为十进制，方便显示
	DSl302_Time[0] = Code8421_Decimal(DS1302_ReadByte(DS1302_YEAR), 1); 
	DSl302_Time[1] = Code8421_Decimal(DS1302_ReadByte(DS1302_MONTH), 1); 
	DSl302_Time[2] = Code8421_Decimal(DS1302_ReadByte(DS1302_DAY), 1); 
	DSl302_Time[3] = Code8421_Decimal(DS1302_ReadByte(DS1302_HOUR), 1); 
	DSl302_Time[4] = Code8421_Decimal(DS1302_ReadByte(DS1302_MINUTE), 1); 
	DSl302_Time[5] = Code8421_Decimal(DS1302_ReadByte(DS1302_SECOND), 1); 
	DSl302_Time[6] = Code8421_Decimal(DS1302_ReadByte(DS1302_DATE), 1); 
}
