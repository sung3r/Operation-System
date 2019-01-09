#ifndef INCLUDE_STDIO_H_
#define INCLUDE_STDIO_H_

/* kernel printf */
int printk(const char *fmt, ...);

/* user printk */
int printf(const char *fmt, ...);

/* my printk with user printk, without interrupt*/
int my_printk(const char *fmt, ...);

#endif
