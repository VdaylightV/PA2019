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

size_t str_to_int(char* str) {
    size_t value = 0;
	while(*str) {
		value += *str - '0';
		value = value*10;
	}
	return value;
}

int printf(const char *fmt, ...) {
/*
  char *out = "";

  va_list ap;

  va_start(ap, fmt);

  int ret = vsprintf(out, fmt, ap);

  va_end(ap);

  return ret;
*/
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
				 
//				 char* fill_width = "0";
//				 size_t len_zero = strlen(fill_width);

				 char *result = int_to_str(val, head);
				 size_t len = strlen(result);
//
/*				 if(len < 2) {

                     result = strcpy(fill_width, result);
					 size_t fill_result_len = strlen(result);

//					 for(size_t i = 0; i < len_zero; i ++) {
//					     temp_out ++;
					 }
//
					 temp_out = strcpy(temp_out, result);
				     for(size_t i = 0; i < fill_result_len; i ++) {
				         temp_out ++;
				     }
					 fmt ++;

					 break;
				 }
*/
//				 else {

					temp_out = strcpy(temp_out, result);

					for(size_t i = 0; i < len; i ++) {
						temp_out ++;
					}
					fmt ++;

					break;
//					}
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

/*           default :
				{
				char *fill_content = "";

				*fill_content = *fmt;

				*(fill_content + 1) = '\0';

				size_t para_width = 0;
               
                const char* temp_fmt = fmt;

				while(*temp_fmt != 'd') {
					para_width ++;
	                temp_fmt ++;
				}

			   char *width_num = "";

			   for(size_t i = 0; i < para_width - 1; i ++) {
				   width_num = strcat(width_num, fill_content);
			   }

			   size_t print_width = str_to_int(width_num);
			   
			   int val = va_arg(ap, int);

			   char temp[65535];
			   char *head = temp;
   
			   char *result = int_to_str(val, head);
			   size_t len = strlen(result);

			   char* the_whole_fill = "";

			  for(size_t i = 0; i < print_width - len; i ++) {
			      the_whole_fill = strcat(the_whole_fill, fill_content);
			  } 

              the_whole_fill = strcat(the_whole_fill, result);

			  temp_out = strcpy(temp_out, the_whole_fill);

			  for(size_t i = 0; i < print_width; i ++) {
			      temp_out ++;
			  }

			  while(*fmt != 'd') {
			      fmt ++;
			  }

			  fmt ++;

			  break;
*/


				
/*			case '0':
				{
					fmt ++;

					int width = *fmt - '0';

					char *fill_width = "";

					for(int i = 0; i < width - 1; i ++) {
						
					    
					}
*/					
//				}
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
