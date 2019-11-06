#include "klib.h"
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int fac(int base, int exp) {
    int result = 1;
	for(int i = 0; i < exp; i ++) {
	    result *= base;
	}
	return result;

}

char *int_to_str(int val, char* str) {
    char *temp = str;
	int num = val;
    
	int len = 1;
	while((num/10) > 0) {
		len ++;
		num = num / 10;
	}
    
	num = val;
	int division = 1;
	int bit;
	char c;

	for(int i = 0; i < len; i ++) {
        division = fac(10, len-i-1);
		bit = num / division;
	    c = '0' + bit;
	    *temp = c;	
		temp ++;
		num = num % division;
	}
	*temp = '\0';

	return str;

}

int printf(const char *fmt, ...) {
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
	char *temp_out = out;
//	const char* temp_fmt;
//	va_start(ap, fmt);

	while(*fmt) {
		if(*fmt != '%'){
			*temp_out = *fmt;
			temp_out ++;
			fmt ++;
			continue;
		}

		fmt ++;

		switch(*fmt) {
		    case 'd': 
				{
				 int val = va_arg(ap, int);

				 char temp[65535];
				 char *head = temp;

				 char *result = int_to_str(val, head);
				 size_t len = strlen(result);

				 if(len<2) {
				     *temp_out = '0';
					 temp_out ++;

					 temp_out = strcpy(temp_out, result);
				     for(size_t i = 0; i < len; i ++) {
				         temp_out ++;
				     }

					 fmt ++;
					 break;
				 }

				 else {

					temp_out = strcpy(temp_out, result);

					for(size_t i = 0; i < len; i ++) {
						temp_out ++;
					}
					fmt ++;

					break;
					}
				}

			case 's':
			   	{
				 char* c; 
				 c = va_arg(ap, char*);
              
				 size_t len = strlen(c);

/*
				 for(size_t i = 0; i < len; i ++) {
				     *temp_out = *c;
					 temp_out ++;
					 c ++;
				 }
*/
				 

				 temp_out = strcpy(temp_out, c);
				 for(size_t i = 0; i < len; i ++) {
				     temp_out ++;
				 }
				 
				 fmt ++;

				 break;

				}
		}
	}
	*temp_out = '\0';

  return 0;
}

int sprintf(char *out, const char *fmt, ...) {
  
  va_list ap;

  va_start(ap, fmt);

  int ret = vsprintf(out, fmt, ap);

  va_end(ap);

  return ret;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

#endif
