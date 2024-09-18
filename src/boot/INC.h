#ifndef _INC_H
#define _INC_H


#define LOAR_ADDR  0x7E00

/*
* 选择子属性
*/
#define RPL0        0b00
#define RPL1        0b01
#define RPL2        0b10
#define RPL3        0b11
#define TI_GDT      0b000
#define TI_LDT      0b100

#define SELECTOR_CODE   ((0x0001<<3) + TI_GDT + RPL0)    //相当于(CODE_DESC - GDT_BASE)/8 + TI_GDT + RPL0
#define SELECTOR_DATA   ((0x0002<<3) + TI_GDT + RPL0) //同上
#define SELECTOR_VIDEO  ((0x0003<<3) + TI_GDT + RPL0)  //同上

/*
 * gdt描述符属性
 */
#define DESC_G_4K                      0b100000000000000000000000
#define DESC_D_32                      0b10000000000000000000000
#define DESC_L	                        0b0000000000000000000000	// 64位代码标记，此处标记为0便可。
#define DESC_AVL                       0b000000000000000000000	   //cpu不用此位，暂置为0  
#define DESC_LIMIT_CODE2               0b11110000000000000000
#define DESC_LIMIT_DATA2               DESC_LIMIT_CODE2
#define DESC_LIMIT_VIDEO2              0b0000000000000000000
#define DESC_P                         0b1000000000000000
#define DESC_DPL_0                     0b000000000000000
#define DESC_DPL_1                     0b010000000000000
#define DESC_DPL_2                     0b100000000000000
#define DESC_DPL_3                     0b110000000000000
#define DESC_S_COD                     0b1000000000000
#define DESC_S_DATA                    DESC_S_CODE
#define DESC_S_sys                     0b0000000000000
#define DESC_TYPE_CODE                 0b100000000000   //;x=1,c=0,r=0,a=0 代码段是可执行的,非依从的,不可读的,已访问位a清0.  
#define DESC_TYPE_DATA                 0b001000000000  //;x=0,e=0,w=1,a=0 数据段是不可执行的,向上扩展的,可写的,已访问位a清0.

#define DESC_CODE_HIGH4      (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_CODE2 + DESC_P + DESC_DPL_0 + DESC_S_CODE + DESC_TYPE_CODE + 0x00
#define DESC_DATA_HIGH4      (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_DATA2 + DESC_P + DESC_DPL_0 + DESC_S_DATA + DESC_TYPE_DATA + 0x00
#define DESC_VIDEO_HIGH4     (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_VIDEO2 + DESC_P + DESC_DPL_0 + DESC_S_DATA + DESC_TYPE_DATA + 0x0b



#endif // !_INC_H
