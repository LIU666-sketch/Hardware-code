#include "stdio.h"					// 标准C库函数头文件 
#include "string.h"
#include "LCD.h"
#include "ASCII.h"
#include "GB1616.h"	//16*16汉字字模
#include "lcm_font.h"
#include "math.h"

/***************************************************************************************
#define LCD_RS         	GPIO_PIN_3	//PE3连接至TFT --DC RS
#define LCD_CS        	GPIO_PIN_4 	//PE4连接至TFT --CS
#define LCD_RST     	  GPIO_PIN_1	//PE1连接至TFT --RST
#define LCD_SCL        	GPIO_PIN_2	//PE2连接至TFT --CLK
#define LCD_SDA        	GPIO_PIN_6	//PE6连接至TFT - SDI
#define LCD_SDO        	GPIO_PIN_5	//PE5连接至TFT - SDO
****************************************************************************************/


// void LCD_GPIO_Config(void)
//{
//	GPIO_InitTypeDef GPIO_Initure;
//	__HAL_RCC_GPIOE_CLK_ENABLE();					//开启GPIOB时钟


//	GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;		
//	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		//推挽输出
//	GPIO_Initure.Pull=GPIO_PULLUP;         			//上拉
//	GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//高速
//	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
//	
//	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_SET);

//}

/****************************************************************************
* 名    称：void Lcd_Reset(void)
* 功    能：液晶硬复位函数
* 入口参数：无
* 出口参数：无
* 说    明：液晶初始化前需执行一次复位操作
****************************************************************************/
void Lcd_Reset(void)
{
	LCD_RST_CLR;
	HAL_Delay(100);
	LCD_RST_SET;
	HAL_Delay(50);
}

void LCD_delay(int time)  //简单软件 延时函数
{
	unsigned short i,j;
	for(i=0;i<time;i++)
		for(j=0;j<1000;j++)	;
}
void LCD_WriteByteSPI(unsigned char byte) //SPI模拟函数，写一个8bit的数据
{
	  unsigned char buf;
    unsigned char i;
    for(i=0;i<8;i++) 
    {
        buf=(byte>>(7-i))&0x1;
				SPI_DCLK(0);
        SPI_SDA(buf);
        SPI_DCLK(1);
    }	
		
}
void LCD_WriteRegIndex(unsigned char Index) //写命令的参数
{
	SPI_CS(0);
	LCD_WriteByteSPI(0X70);
	LCD_WriteByteSPI(0);
	LCD_WriteByteSPI(Index);
	SPI_CS(1);
}
void LCD_WriteData(unsigned short dat) //写数据
{
	SPI_CS(0);
	LCD_WriteByteSPI(0X72);
  LCD_WriteByteSPI(dat>>8);		//	start byte RS=1,RW=0----Write a GRAM data
  LCD_WriteByteSPI(dat);
	SPI_CS(1);
}
/******************************************
函数名：Lcd写命令函数
功能：向Lcd指定位置写入应有命令或数据
入口参数：Index 要寻址的寄存器地址
          ConfigTemp 写入的数据或命令值
******************************************/
void LCD_WR_REG(unsigned int Index,unsigned int CongfigTemp)
{
	LCD_WriteRegIndex(Index);
	LCD_WriteData(CongfigTemp);
}
/*************************************************
函数名：Lcd光标起点定位函数
功能：指定320240液晶上的一点作为写数据的起始点
入口参数：x 坐标 0~239
          y 坐标 0~319
返回值：无
*************************************************/
void Lcd_SetCursor(unsigned short x,unsigned short y)
{ 
  LCD_WriteRegIndex(0x20);
  LCD_WriteData(x);//水平坐标
  LCD_WriteRegIndex(0x21);
  LCD_WriteData(y);//垂直坐标 
} 
/**********************************************
函数名：开窗函数

入口参数：XStart x方向的起点
          Xend   x方向的终点
					YStart y方向的起点
          Yend   y方向的终点

这个函数的意义是：开一个矩形框，方便接下来往这个框填充数据
***********************************************/
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend) 
{
	//ILI9328
	
	LCD_WR_REG(0x0050,Xstart);//水平GRAM起始位置
	LCD_WR_REG(0x0051,Xend); //水平GRAM终止位置
	LCD_WR_REG(0x0052,Ystart);//垂直 GRAM起始位置
	LCD_WR_REG(0x0053,Yend); //垂直GRAM终止位置
	
	Lcd_SetCursor(Xstart, Ystart);
	
  LCD_WriteRegIndex(0x022);

}
/**********************************************
函数名：Lcd矩形填充函数

入口参数：xStart x方向的起始点
          ySrart y方向的终止点
          xLong 要选定矩形的x方向长度
          yLong  要选定矩形的y方向长度
返回值：无
***********************************************/
void Lcd_ColorBox(unsigned int xStart,unsigned int yStart,unsigned int xLong,unsigned int yLong,unsigned int Color)
{
		unsigned int temp;

	BlockWrite(xStart,xStart+xLong-1,yStart,yStart+yLong-1);
	SPI_CS(0);
	LCD_WriteByteSPI(0X72);
	for (temp=0; temp<xLong*yLong; temp++)
	{
		LCD_WriteByteSPI(Color>>8);		//	start byte RS=1,RW=0----Write a GRAM data
		LCD_WriteByteSPI(Color);
	}
	SPI_CS(1);
}
void LCD_Initial(void) //LCD初始化函数
{
Lcd_Reset();
//************* Start Initial Sequence **********//
LCD_WR_REG(0x0001, 0x0000); // set SS and SM bit
LCD_WR_REG(0x0002, 0x0700); // set 1 line inversion
LCD_WR_REG(0x0003, 0x1030); // set GRAM write direction and BGR=1.  0001 0000 0011 0000
LCD_WR_REG(0x0004, 0x0000); // Resize register
LCD_WR_REG(0x0008, 0x0202); // set the back porch and front porch
LCD_WR_REG(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
LCD_WR_REG(0x000A, 0x0000); // FMARK function
LCD_WR_REG(0x000C, 0x0000); // RGB interface setting
LCD_WR_REG(0x000D, 0x0000); // Frame marker Position
LCD_WR_REG(0x000F, 0x0000); // RGB interface polarity
//*************Power On sequence ****************//
LCD_WR_REG(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
LCD_WR_REG(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
LCD_WR_REG(0x0012, 0x0000); // VREG1OUT voltage
LCD_WR_REG(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
LCD_WR_REG(0x0007, 0x0001);
HAL_Delay(200); // Dis-charge capacitor power voltage
LCD_WR_REG(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
LCD_WR_REG(0x0011, 0x0227); // Set DC1[2:0], DC0[2:0], VC[2:0]
HAL_Delay(50); // Delay 50ms
LCD_WR_REG(0x0012, 0x009D); // External reference voltage= Vci;
HAL_Delay(50); // Delay 50ms
LCD_WR_REG(0x0013, 0x1A00); // VDV[4:0] for VCOM amplitude
LCD_WR_REG(0x0029, 0x001D); // VCM[5:0] for VCOMH
LCD_WR_REG(0x002B, 0x000D); // Set Frame Rate
HAL_Delay(50); // Delay 50ms
LCD_WR_REG(0x0020, 0x0000); // GRAM horizontal Address
LCD_WR_REG(0x0021, 0x0000); // GRAM Vertical Address
// ----------- Adjust the Gamma Curve ----------//
LCD_WR_REG(0x0030, 0x0000);
LCD_WR_REG(0x0031, 0x0607);
LCD_WR_REG(0x0032, 0x0305);
LCD_WR_REG(0x0035, 0x0000);
LCD_WR_REG(0x0036, 0x1604);
LCD_WR_REG(0x0037, 0x0204);
LCD_WR_REG(0x0038, 0x0001);
LCD_WR_REG(0x0039, 0x0707);
LCD_WR_REG(0x003C, 0x0000);
LCD_WR_REG(0x003D, 0x000F);
//------------------ Set GRAM area ---------------//
LCD_WR_REG(0x0050, 0x0000); // Horizontal GRAM Start Address
LCD_WR_REG(0x0051, 0x00EF); // Horizontal GRAM End Address
LCD_WR_REG(0x0052, 0x0000); // Vertical GRAM Start Address
LCD_WR_REG(0x0053, 0x013F); // Vertical GRAM Start Address
LCD_WR_REG(0x0060, 0x2700); // Gate Scan Line  
LCD_WR_REG(0x0061, 0x0001); // NDL,VLE, REV

LCD_WR_REG(0x006A, 0x0000); // set scrolling line
//-------------- Partial Display Control ---------//
LCD_WR_REG(0x0080, 0x0000);
LCD_WR_REG(0x0081, 0x0000);
LCD_WR_REG(0x0082, 0x0000);
LCD_WR_REG(0x0083, 0x0000);
LCD_WR_REG(0x0084, 0x0000);
LCD_WR_REG(0x0085, 0x0000);
//-------------- Panel Control -------------------//
LCD_WR_REG(0x0090, 0x0010);
LCD_WR_REG(0x0092, 0x0600);
LCD_WR_REG(0x0007, 0x0133); // 262K color and display ON
HAL_Delay(10);

	//============从右到左从下到上============//
//	LCD_WR_REG(0x0001, 0x0100);
//	LCD_WR_REG(0x03,0x1008);//MX, MY, RGB mode

	//============从左到右从下到上============//
//	LCD_WR_REG(0x0001, 0x0100);
//	LCD_WR_REG(0x03,0x1018);//MX, MY, RGB mode

	//============从右到左从上到下============//
//	LCD_WR_REG(0x0001, 0x0100);
//	LCD_WR_REG(0x03,0x1028);//MX, MY, RGB mode

	//============从左到右从上到下============//
//	LCD_WR_REG(0x0001, 0x0100);
//	LCD_WR_REG(0x03,0x1038);//MX, MY, RGB mode

	
	//============从左到右从上到下============//
//	LCD_WR_REG(0x0001, 0x0100);// set SS and SM bit
//	LCD_WR_REG(0x03,0x1030);//MX, MY, RGB mode set GRAM write direction and BGR=1.
	
//	Lcd_Light_ON;//打开背光

//	LCD_WR_REG(0x0001, 0x0100);
//	LCD_WR_REG(0x03,0x1008);//MX, MY, RGB mode


}
/******************************************
函数名：Lcd图像填充
功能：向Lcd指定位置填充图像
入口参数：
					(x,y): 图片左上角起始坐标
					(pic_H,pic_V): 图片的宽高
					 pic  指向存储图片数组的指针
******************************************/
void LCD_Fill_Pic(unsigned int x, unsigned int y,unsigned int pic_H, unsigned int pic_V, const unsigned char*  pic)
{
	//DMA 方式
//	BlockWrite(x,x+pic_H-1,y,y+pic_V-1);
//	TK80_DMA_Init((u32)pic,pic_H*pic_V);//DMA初始化
//	while((DMA2->ISR & 0x20)==0);
//	DMA2->IFCR |=1<<5;gImage_insect
	
	//========= 轮询方式=========//
  unsigned long i;
	unsigned long j;
	BlockWrite(x,x+pic_H-1,y,y+pic_V-1);
	j= pic_H*pic_V*2;
	SPI_CS(0);
	LCD_WriteByteSPI(0X72);
	for (i = 0; i <j; i++) 
	{
		LCD_WriteByteSPI(pic[i]);
	}
	SPI_CS(1);
}
//=============== 在x，y 坐标上打一个颜色为Color的点 ===============
void DrawPixel(unsigned int x, unsigned int y, int Color)
{
	BlockWrite(x,x,y,y); 
  SPI_CS(0);
	LCD_WriteByteSPI(0X72);
	LCD_WriteByteSPI(Color>>8);
	LCD_WriteByteSPI(Color);
	SPI_CS(1);
}

/**********8*16字体 ASCII码 显示*************
(x,y): 显示字母的起始坐标
num:   要显示的字符:" "--->"~"
fColor 前景色
bColor 背景色
flag:  有背景色(1)无背景色(0)
*********************************************/
void SPILCD_ShowChar(unsigned short x,unsigned short y,unsigned char num, unsigned int fColor, unsigned int bColor,unsigned char flag) 
{       
	unsigned char temp;
	unsigned int pos,i,j;  

	num=num-' ';//得到偏移后的值
	i=num*16; 	
	for(pos=0;pos<16;pos++)
		{
			temp=nAsciiDot[i+pos];	//调通调用ASCII字体
			for(j=0;j<8;j++)
		   {                 
		        if(temp&0x80)
							DrawPixel(x+j,y,fColor);
						else 
							if(flag) DrawPixel(x+j,y,bColor); //如果背景色标志flag为1
							temp<<=1; 
		    }
			 y++;
		}		 
}  

/**********写一个16x16的汉字*****************
(x,y): 显示汉字的起始坐标
c[2]:  要显示的汉字
fColor 前景色
bColor 背景色
flag:  有背景色(1)无背景色(0)
*********************************************/
void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor,unsigned char flag)
{
	unsigned int i,j,k;
	unsigned short m;
	for (k=0;k<200;k++) { //64标示自建汉字库中的个数，循环查询内码
	  if ((codeGB_16[k].Index[0]==c[0])&&(codeGB_16[k].Index[1]==c[1]))
			{ 
    	for(i=0;i<32;i++) 
			{
				m=codeGB_16[k].Msk[i];
				for(j=0;j<8;j++) 
				{		
					if((m&0x80)==0x80) {
						DrawPixel(x+j,y,fColor);
						}
					else {
						if(flag) DrawPixel(x+j,y,bColor);
						}
					m=m<<1;
				} 
				if(i%2){y++;x=x-8;}
				else x=x+8;
		  }
		}  
	  }	
	}
/**********显示一串字*****************
(x,y): 字符串的起始坐标
*s:    要显示的字符串指针
fColor 前景色
bColor 背景色
flag:  有背景色(1)无背景色(0)
*********************************************/
void LCD_PutString(unsigned short x, unsigned short y, char *s, unsigned int fColor, unsigned int bColor,unsigned char flag) 
	{
		unsigned char l=0;
		while(*s) 
			{
				if( (unsigned char)*s < 0x80) 
						{
							SPILCD_ShowChar(x+l*8,y,*s,fColor,bColor,flag);
							s++;l++;
						}
				else
						{
							PutGB1616(x+l*8,y,(unsigned char*)s,fColor,bColor,flag);
							s+=2;l+=2;
						}
			}
	}
	
	
	void draw_circle(int x, int y ,int r, int color, int fill){
	//DrawPixel(x, y, color);
	if (!fill){
		for (int angle = 0; angle < 360; angle++) {
        double radian = angle * 3.14159 / 180.0;
        int x_point = x + r * cos(radian);
        int y_point = y + r * sin(radian);
				DrawPixel(x_point, y_point, color);
		}
	}
	if(fill){
		for(int radious=0;radious<=r;radious++){
			draw_circle(x, y, radious, color, 0);
		}
	}
}

