#include "klib.h"
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

//static int i = 0;
//#define int fac(int base, int exp) {int result = 1; for(int i = 0; i < exp; i ++) {result*=base;} return result;}
//#define size_t str_to_int(char* str) {size_t value = 0; while(*str != '\0') {value *= 10; value += ((*str) - '0'); str ++;} return value;}


static inline size_t str_to_int(char* str) {
    size_t value = 0;
	while(*str != '\0') {
		value = value * 10;
		value += ((*str) - '0');
		str ++;
	}
	return value;
}



static inline int fac(int base, int exp) {
    int result = 1;
	for(int i = 0; i < exp; i ++) {
	    result *= base;
	}
	return result;
}



static inline char* to_hex(int value, char* str) {
	char table[17] = "0123456789abcdef";

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
		//char c = '0' + bit;
		str[len - count - 1] = table[bit];
/*	
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
		

*/
		count ++;
	}
	str[0] = table[temp1];
	
//	char first_c = '0' + temp1;
/*	if( first_c >= '0' && first_c <= '9') {
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
*/	

	
	str[len] = '\0';

    return str;	

}


static inline char *int_to_str(int val, char* str) {
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
	//我的代码：
  //i ++;

  char out[158];


  char* start = &out[0];

  va_list ap;

  va_start(ap, fmt);
 
  vsprintf(start, fmt, ap);

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
					char whole_content[128];

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

                 char val_str[16] = "";

				 char* head_val_str = &val_str[0];

				 head_val_str = int_to_str(val, head_val_str);
				 size_t len = strlen(head_val_str);
				 //把整数直接换成字符串


				//temp_out = strcpy(temp_out, head_val_str);
				for(size_t i = 0; i < len; i ++) {
					*temp_out = *head_val_str;
					temp_out ++;
					head_val_str ++;

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
					 _putc(*c);
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


/*
void my_itoa(char *str, unsigned digit, int base) {
    int count = 0;
	char buffer[30];
	char table[] = "0123456789abcde";
	    
	if (digit == 0) {
	    str[0] = '0';
		str[1] = '\0';
		return;
	}

	while (digit != 0) {
	    buffer[count] = table[digit % base];
		digit /= base;
		count ++;
	}

	for(int i = 0; i < 0; i ++) {
		str[i] = buffer[count - i - 1];
	}
	str[count] = '\0';
	return;
}

int printf(const char *fmt, ...) {
    char buf[200];
	va_list(ap);
	va_start(ap, fmt);
	int res = vsprintf(buf, fmt, ap);
	for(int i = 0; i < res; i ++) {
	    _putc(buf[i]);
	}
	return res;
}

int vsprintf(char *out, const char *fmt, va_list ap){
	*out = '\0';
	int index = 0;
	int count = 0;
	char *str;
	char val_str[50];
	char val_char;

	int val = 0;

	for(index = 0; fmt[index] != '\0'; index ++) {
	    if(fmt[index] != '%') {
		    out[count] = fmt[index];
			count ++;
			continue;
		}

		index ++;

		switch(fmt[index]) {
		    case 's':
				for(str = va_arg(ap, char*); *str!='\0'; str++) {
				    out[count] = *str;
					count ++;
				}
				break;

            case 'c':
                val_char = va_arg(ap, int);
				out[count] = (char)val_char;
				count ++;
				break;

		    case 'd':
				val = va_arg(ap, int);
				my_itoa(val_str, val, 10);
				for(int i = 0; val_str[i] != '\0'; i ++) {
				    out[count] = val_str[i];
					count ++;
				}
				break;

			case 'p':
				val = va_arg(ap, uint32_t);
				out[count] = '0'; count ++;
				out[count] = 'x'; count ++;
				my_itoa(val_str, val, 16);
				for(int i = 0; val_str[i] != '\0'; i ++) {
				    out[count] = val_str[i];
					count ++;
				}
				break;

			case 'x':
				val = va_arg(ap, uint32_t);
				out[count] = '0'; count ++;
				out[count] = 'x'; count ++;
				my_itoa(val_str, val, 16);
				for(int i = 0; val_str[i] != '\0'; i ++) {
				    out[count] = val_str[i];
					count ++;
				}
				break;

			default: assert(0);
		}
	}

	out[count] = '\0';
	return count;

}

*/

int sprintf(char *out, const char *fmt, ...) {
  
  va_list ap;

  va_start(ap, fmt);

  int ret = vsprintf(out, fmt, ap);

  va_end(ap);

  return ret;
}

/*
int printf(const char *fmt, ...) {
    va_list ap;
	va_start(ap, fmt);
#define MAX 200
	char buf[200];
	int i,n=vsnprintf(buf, -1, fmt, ap);
	assert(n<MAX);
#undef MAX
	for(i = 0; i < n; ++ i) {
	    _putc(buf[i]);
	}
	return i;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
    return vsnprintf(out, -1, fmt, ap);
}

int sprintf(char *out, const char * fmt, ...) {
    va_list ap;
	va_start(ap, fmt);
	return vsnprintf(out, -1, fmt, ap);
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
#define output(A) if(cnt<n-1){out[cnt++]=A;}else{va_end(ap);out[cnt]='\0';return cnt;}
	size_t cnt = 0;
	int i = 0;

	const char *p, *sval;
	char fill, num[10];
	int ival,fill_width;

	uintptr_t uval;
	char cval;
	for(p=fmt;*p!='\0';++p)
	{
		if(*p!='%') {
			output(*p);
			continue;
		}
		fill_width=0;
		fill = ' ';
		//p ++;
		if(*p == '0') {
		    fill = '0';
			++p;
		}
        fill_width = 0;
		++p;
		while(*p >= '0' && *p <= '9') {
		    fill_width *= 10;
			fill_width += *p - '0';
			++p;
		}
		switch(*p) {
		    case 'c':
				cval = va_arg(ap, int);
				output(cval);
				break;
			case 'u':
				uval = va_arg(ap, uint32_t);
				i = 0;
				while(uval > 0) {
				    num[i++] = uval % 10 + '0';
					uval /= 10;
				}
				while(fill_width > i) {
				   num[i++] = fill;
				}
                if(i == 0) {
				    output('0');
				}
				else {
				   while(i > 0) {
				      output(num[--i]);
				   }
				}
				break;
			case 'x':
			case 'p':
				uval = (uintptr_t) va_arg(ap, void*);
				i = 8;
				while(i>0) {
				    output(
							(uval >> ((sizeof(void*) << 3) -4)) < 10 ?
							(uval >> ((sizeof(void*) << 3) -4)) + '0':
							(uval >> ((sizeof(void*) << 3) -4)) - 10 + 'a');
					uval <<= 4;
					--i;

				}
				break;
			case 'd':
				ival = va_arg(ap, int);
				if(ival < 0) {
				   output('-');
				   ival = -ival;
				}
				while(ival > 0) {
				    num[i++] = ival % 10 + '0';
					ival /= 10;
				}
				while (fill_width > i) {
				    num[i++] = fill;
				}
				if(i == 0) {
				    output('0');
				} else {
				    while(i>0) {
					    output(num[--i]);
					}
				}
				break;
			case 's':
				for(sval = va_arg(ap, char*); *sval != '\0'; ++sval) {
				    output(*sval);
				}
				break;
			default:
				if(*p < '0' || *p > '9') {
				    output(*p);
					printf("%%%c not realized.\n");
					assert(0);
					cnt+=vsprintf(out+cnt, "not realized\n", ap);
					break;
				}

		}
	
	}
	va_end(ap);
	output('\0');
	return cnt-1;
#undef output
}
*/
int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

#endif
