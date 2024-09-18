#ifndef _PRINK_H
#define _PRINK_H

#include "types.h"
#include "stdarg.h"

// 颜色重置
#define RESET   "\033[0m"

// 前景色
#define BLACK   "\033[30m"   // 黑色
#define RED     "\033[31m"   // 红色
#define GREEN   "\033[32m"   // 绿色
#define YELLOW  "\033[33m"   // 黄色
#define BLUE    "\033[34m"   // 蓝色
#define MAGENTA "\033[35m"   // 洋红色
#define CYAN    "\033[36m"   // 青色
#define WHITE   "\033[37m"   // 白色

// 背景色
#define BG_BLACK   "\033[40m"   // 黑色背景
#define BG_RED     "\033[41m"   // 红色背景
#define BG_GREEN   "\033[42m"   // 绿色背景
#define BG_YELLOW  "\033[43m"   // 黄色背景
#define BG_BLUE    "\033[44m"   // 蓝色背景
#define BG_MAGENTA "\033[45m"   // 洋红色背景
#define BG_CYAN    "\033[46m"   // 青色背景
#define BG_WHITE   "\033[47m"   // 白色背景

#define BOLD "\033[1m"

void putchar(char c);
void puts(const char *s);

typedef void (*fmt_callback_t)(const char* num_s,long num,int num_f,int base,int ladjust,      \
                        int width,int precision,int neg_flag,int caps);

void printk(const char *fmt,...);
void vprintfmt(va_list ap,const char *fmt);

void outputk(fmt_callback_t callback_fun,const char* num_s,long num,int num_f,int base,int ladjust,      \
                        int width,int precision,int neg_flag,int caps);
void out_init();
void pannic(const char * file, int line , const char * func, const char * cond);

#define ASSERT(expr) do { \
    if( !(expr) ) { \
        pannic(__FILE__, __LINE__, __func__, #expr ); \
    } \
} while(0)
    
#endif // !_PRINK_H