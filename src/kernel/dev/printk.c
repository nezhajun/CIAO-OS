/*
 *  linux/kernel/printk.c
 *
 *  (C) 1991  Linus Torvalds
 */

/*
 * When in kernel-mode, we cannot use printf, as fs is liable to
 * point to 'interesting' things. Make a printf with fs-saving, and
 * all is well.
 */
#include <stdarg.h>
#include "printk.h"
#include "cpu_instr.h"

// 目标用串口，参考资料：https://wiki.osdev.org/Serial_Ports
#define COM1_PORT           0x3F8       // RS232端口0初始化

/**
 * @brief 初始化日志输出
 */
void out_init (void) {
    outb(COM1_PORT + 1, 0x00);    // Disable all interrupts
    outb(COM1_PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(COM1_PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(COM1_PORT + 1, 0x00);    //                  (hi byte)
    outb(COM1_PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(COM1_PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
  
    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(COM1_PORT + 4, 0x0F);
}


void putchar(const char c)
{
    uint32_t if_status = cTaskEnterCritical();
    // asm volatile ("cli");
    const char ch=c;
	while ( (inb(COM1_PORT + 5) & (1 << 6)) == 0);
	outb(COM1_PORT, ch);
    // asm volatile ("sti");
    cTaskExitCritical(if_status);
}


void puts(const char *s)
{
	const char * p = s;
    while(*p != '\0')
    {
        putchar(*p);
        p++;
    }
}

static void print_num(const char* num_s,long num,int num_f,int base,int ladjust,      \
                        int width,int precision,int neg_flag,int caps);

static void print_char(const char* num_s,long num,int num_f,int base,int ladjust,      \
                        int width,int precision,int neg_flag,int caps);

static void print_str(const char* num_s,long num,int num_f,int base,int ladjust,      \
                        int width,int precision,int neg_flag,int caps);


int width; // 标记输出宽度
int precision; //标记输出精度
int long_flag; // 标记是否为 long 型
int neg_flag; // 标记是否为负数
int ladjust; // 标记是否左对齐
/*

%[flags][width][.precision][length]specifier

flag 描述
- 在给定的宽度 (width) 上左对齐输出，默认为右对齐(默认右对齐时，给定宽度不同时填充空格)
0 当输出宽度和指定宽度不同的时候，在空白位置填充 0

width 描述
数字 指定了要打印数字的最小宽度，当这个值大于要输出数字的
宽度，则对多出的部分填充空格，但当这个值小于要输出数
字的宽度的时候则不会对数字进行截断。

.precision 描述
. 数字 指定了精度，不同标识符下有不同的意义，但在我们实验的
版本中这个值只进行计算而没有具体意义，所以不赘述。

length
Specifier
   d D           b o O u U x X
l long int     unsigned long int

Specifier 输出 例子
b       无符号二进制数  110
d D     十进制数 920
o O     无符号八进制数 777
u U     无符号十进制数 920
x       无符号十六进制数，字母小写 1ab
X       无符号十六进制数，字母大写 1AB
c       字符 a
s       字符串 sample

*/

void printk(const char *fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    vprintfmt(ap,fmt);
    va_end(ap);
}


void outputk(fmt_callback_t callback_fun,const char* num_s,long num,int num_f,int base,int ladjust,      \
                        int width,int precision,int neg_flag,int caps)
{
    callback_fun(num_s,num,num_f,base,ladjust,      \
                        width,precision,neg_flag,caps);
}

void vprintfmt(va_list ap,const char *fmt)
{
    const char *p = fmt;
    long num1;
    // double num_f;
    char num_c;
    const char* num_s = NULL;

    for(;;)
    {
        //每次循环更新参数默认值
        ladjust = 0; // 标记是否左对齐
        width = 0; // 标记输出宽度
        precision = -1; //标记输出精度(负数代表整型数，非负数代表浮点数)
        long_flag = 0; // 标记是否为 long 型
        neg_flag = 0; // 标记是否为负数

        while( *p !='%' && *p != '\0')
        {
            putchar(*p);
            p++;
        }
        if( *p == '\0')break;
        p++;//指向%的下一个符号

        if(*p == '-')//判断标记是否左对齐(使用空格填充)
        {
            ladjust = 1;
            p++;
        }
        else if(*p == '0')//右对齐且使用'0'填充
        {
            ladjust = 2;
            p++;
        }

        if( *p >= '0' && *p <= '9')// 标记输出宽度
        {
            width = *p - '0';
            p++;
        }

        if( *p == '.')//标记输出精度
        {
            p++;
            if( *p >='0' && *p <='9')
            {
                precision = *p - '0';
                p++;
            }
        }

        if( *p == 'l' )// 标记是否为 long 型
        {
            long_flag = 1;
            p++;
        }
        // else if(*p == 'll')
        // {
        //     long_flag = 2;
        //     p++;
        // }
        else if (*p == 'h')
        {
            long_flag = 3;
            p++;            
        }else ;

        switch (*p)
        {
        case 'b':
        if( long_flag == 1)
            num1 = va_arg(ap,long int);
        else if ( long_flag == 2){}
        else if ( long_flag == 3){}
        else num1 = va_arg(ap,int);
        if(num1<0)neg_flag = 1;
        else neg_flag = 0;
        outputk(print_num,NULL,num1,0,2,ladjust,width,-1,0,0);
        break;
        
        case 'd':
        case 'D':
        if( long_flag == 1)
            num1 = va_arg(ap,long int);
        else if ( long_flag == 2){}
        else if ( long_flag == 3){}
        else num1 = va_arg(ap,int);
        if(num1<0)neg_flag = 1;
        else neg_flag = 0;
        outputk(print_num,NULL,num1,0,10,ladjust,width,-1,neg_flag,0);
        break;
        
        case 'f'://这是浮点数的情况
        case 'F':
        // num_f = va_arg(ap,double);
        // if(num_f<0)neg_flag = 1;
        // else neg_flag = 0;
        // if(precision < 0)precision = 0;
        // outputk(print_num,NULL,0,num_f,10,ladjust,width,precision,neg_flag,0);
        break;
        
        case 'o':
        case 'O':
        if( long_flag == 1)
            num1 = va_arg(ap,long int);
        else if ( long_flag == 2){}
        else if ( long_flag == 3){}
        else num1 = va_arg(ap,int);
        if(num1<0)neg_flag = 1;
        else neg_flag = 0;
        outputk(print_num,NULL,num1,0,8,ladjust,width,-1,0,0);
            break;

        case 'u':
        case 'U':
        if( long_flag == 1)
            num1 = va_arg(ap,long int);
        else if ( long_flag == 2){}
        else if ( long_flag == 3){}
        else num1 = va_arg(ap,int);
        if(num1<0)neg_flag = 1;
        else neg_flag = 0;
        outputk(print_num,NULL,num1,0,10,ladjust,width,precision,0,0);
            break;

        case 'x':
        if( long_flag == 1)
            num1 = va_arg(ap,long int);
        else if ( long_flag == 2){}
        else if ( long_flag == 3){}
        else num1 = va_arg(ap,int);
        if(num1<0)neg_flag = 1;
        else neg_flag = 0;
        outputk(print_num,NULL,num1,0,16,ladjust,width,-1,0,0); 
            break;

        case 'X':
        if( long_flag == 1)
            num1 = va_arg(ap,long int);
        else if ( long_flag == 2){}
        else if ( long_flag == 3){}
        else num1 = va_arg(ap,int);
        if(num1<0)neg_flag = 1;
        else neg_flag = 0;
        outputk(print_num,NULL,num1,0,16,ladjust,width,-1,0,1); 
            break;

        case 'c':
        num_c = va_arg(ap,int);
        outputk(print_char,NULL,num_c,0,0,ladjust,width,-1,0,0); 
            break;

        case 's':
        num_s = va_arg(ap,char *);
        outputk(print_str,num_s,0,0,0,ladjust,width,-1,0,0); 
            break;

        case '\0':
            break;

        default:
            putchar(*p);
            break;
        }
        p++;
    }
    
}


static void print_num(const char* num_s,long num,int num_f,int base,int ladjust,      \
                        int width,int precision,int neg_flag,int caps)
{
    char buf[80];
    char temp;
    unsigned int num_bak=0;
    int i=0;

    if( precision >= 0 ) //浮点数特殊处理
    {

    }
    else //整型数处理
    {
        if(neg_flag)//负数 只有d/D时才需要处理负数
            num_bak = 0-num; //先转成正数
        else num_bak = (unsigned int)num;
        
        if( num_bak == 0)
        {
            buf[0] = '0';
            i++;
        }

        while (num_bak)
        {
            temp = num_bak % base;
            if( (temp+'0') > '9') // 16进制大于9的数
            {
                if( caps ) //大写
                    buf[i] = temp + 'A' -10;
                else //小写
                    buf[i] = temp + 'a' -10;
                i++;
            }
            else // 2,8,10进制和16进制10以内的数
            {
                buf[i] = temp+'0';
                i++;
            }
            num_bak = num_bak / base;
        }

        // buff已经处理完，接下来取出字符打印
        width = width - i;
        if(width<0)width=0;

        if( ladjust == 1)//左对齐，多余的用空格补齐
        {
            if(neg_flag) //负数要打印负号
                putchar('-');
            for(int k=i-1;k>=0;k--)
                putchar(buf[k]);
            while (width--) //空格补齐
                putchar(' ');
        }
        else if (ladjust == 2)//右对齐，空余用0补齐
        {
            if(neg_flag) //负数要打印负号,先打印负号
                putchar('-');
            while (width--) //0补齐
                putchar('0');
            for(int k=i-1;k>=0;k--)
                putchar(buf[k]);
        }
        else //右对齐，空余用空格补齐
        {
            while (width--) //空格补齐
                putchar(' ');
            if(neg_flag) //负数要打印负号,先打印负号
                putchar('-');
            for(int k=i-1;k>=0;k--)
                putchar(buf[k]);
        }

    }
    
}

static void print_char(const char* num_s,long num,int num_f,int base,int ladjust,      \
                        int width,int precision,int neg_flag,int caps)
{
    if(width <= 0)width=0;
    else width --;

    if(ladjust == 1) //左对齐，多余的用空格补齐
    {
        putchar(num);
        for(int i=0;i<width;i++)
            putchar(' ');
    }
    else if(ladjust == 2)//右对齐，空余用0补齐
    {
        for(int i=0;i<width;i++)
            putchar('0');
        putchar(num);
    }
    else //右对齐，空余用空格补齐
    {
        for(int i=0;i<width;i++)
            putchar(' ');
        putchar(num);
    }
}

static void print_str(const char* num_s,long num,int num_f,int base,int ladjust,      \
                        int width,int precision,int neg_flag,int caps)
{
    const char *p=num_s;
    int length=0;
    while (*p != '\0')
    {
        p++;
        length++;
    }
    width = width - length;
    if(width<0)width=0;

    if(ladjust == 1) //左对齐，多余的用空格补齐
    {
        puts(num_s);
        for(int i=0;i<width;i++)
            putchar(' ');
    }
    else if(ladjust == 2)//右对齐，空余用0补齐
    {
        for(int i=0;i<width;i++)
            putchar('0');
        puts(num_s);
    }
    else //右对齐，空余用空格补齐
    {
        for(int i=0;i<width;i++)
            putchar(' ');
        puts(num_s);
    }    
}


void pannic(const char * file, int line , const char * func, const char * cond)
{
    printk(BOLD RED"ASSERT Failed !!!"RESET"\r\n" );
    printk(RED"%s:%d:%s: %s"RESET"\r\n",file, line, func, cond);
    for (;;){
        printk(BOLD YELLOW"cpu hlt..."RESET"\r\n");
        asm volatile ("hlt"::);
    };
}






