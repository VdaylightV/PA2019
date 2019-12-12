#include "klib.h"
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

//static int i = 0;

int fac(int base, int exp) {
    int result = 1;
	for(int i = 0; i < exp; i ++) {
	    result *= base;
	}
	return result;

}

char* to_hex(int value, char* str) {

	unsigned int temp0 = (unsigned int)value;

	int len = 1;
	while(temp0 / 16 > 0) {
        temp0 = temp0 / 16;
		len ++;
	}

	unsigned int temp1 = (unsigned int)value;
	int bit;
	int count = 0;
	while(temp1 / 16 > 0) {
	    bit = temp1 % 16;
		temp1 = temp1 / 16;
		char c = '0' + bit;
		if ( c >= '0' && c <= '9' ) {
		    str[len - count - 1] = c;
		}

		else {
		    switch(bit) {
		        case 10: {c = 'a'; str[len - count - 1] = c; break;}
		        case 11: {c = 'b'; str[len - count - 1] = c; break;}
		        case 12: {c = 'c'; str[len - count - 1] = c; break;}
		        case 13: {c = 'd'; str[len - count - 1] = c; break;}
		        case 14: {c = 'e'; str[len - count - 1] = c; break;}
		        case 15: {c = 'f'; str[len - count - 1] = c; break;}
                default: {assert(0); break;}
		        }
		}

		count ++;
	}

	char first_c = '0' + temp1;
	if( first_c >= '0' && first_c <= '9') {
	    str[0] = first_c;
	}

	else{
	    switch(temp1) {
		    case 10: {first_c = 'a'; str[len - count - 1] = first_c; break;}
		    case 11: {first_c = 'b'; str[len - count - 1] = first_c; break;}
		    case 12: {first_c = 'c'; str[len - count - 1] = first_c; break;}
		    case 13: {first_c = 'd'; str[len - count - 1] = first_c; break;}
		    case 14: {first_c = 'e'; str[len - count - 1] = first_c; break;}
		    case 15: {first_c = 'f'; str[len - count - 1] = first_c; break;}
            default: {assert(0); break;}
		
		}
	}

	
	str[len] = '\0';

    return str;	

/*
    int temp0 = value;
	int len = 1;
	while(
       temp / 16 > 0;
	   temp = temp / 16;
	   len ++;
		 }

	int temp1 = value;
    char str[256];

	int bit;
*/
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
	while(*str != '\0') {
		value = value * 10;
		value += ((*str) - '0');
		str ++;
	}
	return value;
}

int printf(const char *fmt, ...) {
/*
	size_t len = strlen(fmt);

    size_t i = 0;    

	while(i < len) {
	    if(fmt[i] != '%') {
		    _putc(fmt[i]);
			i ++;
			continue;
		}

       char c = fmt[i];
       const char* temp_fmt = &fmt[i];
	   temp_ftm ++;

	}
*/


	//我的代码：
  //i ++;

  char out[158];

  char* start = &out[0];

  va_list ap;

  va_start(ap, fmt);
 
  vsprintf(start, fmt, ap);

//  _putc('\n');
// _putc(i + '0');
//  _putc('\n');

  va_end(ap);

  size_t len = strlen(start);
  for( size_t i = 0; i < len; i ++ ) {
      _putc(start[i]);
  }


  return 0;

}

int vsprintf(char *out, const char *fmt, va_list ap) {
	char *temp_out = out;

	while(*fmt != '\0') {
		if(*fmt != '%'){
			*temp_out = *fmt;
			temp_out ++;
			fmt ++;
			continue;
		}
		//对于不需要替换的地方直接拷贝

		fmt ++;
		//遇到需要替换的地方了，fmt ++，则fmt指向%后年的东西
		//此时temp_out所指向的地方就是需要填参数的地方

		switch(*fmt) {
			case '0':
				{    
                    char fill_content[2] = "0";
					char whole_content[64] = "";

					char* head = &whole_content[0];

					int val = va_arg(ap, int);

					fmt ++;

					size_t para_width = 0;

					const char* temp_fmt = fmt;

					while(*temp_fmt != 'd' && *temp_fmt != 'x') {
					    para_width ++;
						temp_fmt ++;
					}

					char type = *temp_fmt;
        
                    temp_fmt = fmt;

					char width_num[para_width];
					for(size_t i = 0; i < para_width; i ++) {
					    width_num[i] = *temp_fmt;
						temp_fmt ++;
					}
					width_num[para_width] = '\0';

                    size_t width = str_to_int(&width_num[0]);

					char temp[32] = "";
					char* p_temp = &temp[0];

					char *result = NULL;

					switch(type) {
					    case 'd':
							{
					            result = int_to_str(val, p_temp);
								break;
							}
                        case 'x':
							{
					            result = to_hex(val, p_temp);
								break;
							}
                        default: {assert(0); break;}
					}

					size_t len = strlen(result);

					for(size_t i = 0; i < width - len; i ++) {
					    head = strcat(head, fill_content);
					}

					head = strcat(head, result);
  
					temp_out = strcpy(temp_out, head);

					for(size_t i = 0; i < width; i ++) {
					    temp_out ++;
					}

					while(*fmt != 'd' && *fmt != 'x') {
					    fmt ++;
					}

					fmt ++;

					break;

				}

		    case 'd': 
				{
				 int val = va_arg(ap, int);

                 char val_str[32] = "";

				 char* head_val_str = &val_str[0];

				 head_val_str = int_to_str(val, head_val_str);
				 size_t len = strlen(head_val_str);
				 //把整数直接换成字符串


				temp_out = strcpy(temp_out, head_val_str);
				for(size_t i = 0; i < len; i ++) {
					temp_out ++;
				}
				//此时temp_out又指向一个空位置
				fmt ++;
				//fmt此时指向了也是'd'后面的东西

				break;
				}
            case 'c':
			    {
                     char c;
					 c = va_arg(ap, int);

					 *temp_out = c;

					 temp_out ++;

					 fmt ++;

					 break;
     			}
			case 's':
			   	{
				 char* c; 
				 c = va_arg(ap, char*);
              
				 size_t len = strlen(c);
				 //先读取要填入的字符串的长度


                 // temp_out = strcpy(temp_out, c);
				 //把字符串直接拷贝到temp_out之后
				 for(size_t i = 0; i < len; i ++) {
					 *temp_out = *c;
					 c ++;
				     temp_out ++;
				 }
				 //temp_out指针增长，指向下一个空处
				 
				 fmt ++;
				 //fmt也增长，指向下一个字符

				 break;

				}
		   
		   case 'x':
				{ 
				 int val = va_arg(ap, int);
				 char temp[32] = "";
				 char *head = temp;

				 char *result = to_hex(val, head);
				 size_t len = strlen(result);
				
				 temp_out = strcpy(temp_out, result);

				 for(size_t i = 0; i < len; i ++) {
					 temp_out ++;
				 }

				 fmt ++;

				 break;
				}

		   case 'p':
			     {
				    int val = va_arg(ap, int);
				    //char temp[65535] = "";
					char temp[32] = "";
				    char *head = temp;

					char *result = to_hex(val, head);
					size_t len = strlen(result);

					char prefix[3] = "0x";
					char *head_prefix = prefix;

					if(len == 8) {
					    temp_out = strcpy(temp_out, head_prefix);
						temp_out ++;
						temp_out ++;

						temp_out = strcpy(temp_out, result);
						for(size_t i = 0; i < len; i ++) {
						    temp_out ++;
						}

						fmt ++;

						break;
					}

					else {
					    temp_out = strcpy(temp_out, head_prefix);
						temp_out ++;
						temp_out ++;

						for(size_t i = 0; i < 8 - len; i ++) {
						    *temp_out = '0';
							temp_out ++;
						}

						temp_out = strcpy(temp_out, result);

						for(size_t i = 0; i < len; i ++) {
						    temp_out ++;
						}

						fmt ++;

						break;
					}
				 
				 }

        default:{assert(0); break;}
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
