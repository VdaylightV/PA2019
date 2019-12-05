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

  char out[128];

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
/*
	char c;
	char* temp_out = out;
	const char* temp_fmt = fmt;
	size_t i = 0;
	int j = 0;
	size_t len;
    int flag;
	int print_width;
	int num;
	char num_s[256];

	for(; *fmt; fmt ++) {
	    if(*fmt != '%') {
		    *temp_out = *fmt;
		   temp_out ++;
	       fmt ++;
	       continue;	   
		}

		flag = 0;
		fmt ++;
		while(*fmt == ' ' || *fmt == '0') {
		    if(*fmt==' ') {
			    flag |= 8;
			}
			else if(*fmt == '0') {
			    flag |= 1;
			}
			fmt ++;
		}

		print_width = 0;
		if(*fmt >= '0' && *fmt <= '9') {
		    while(*fmt >= '0' && *fmt <= '9') {
			    print_width = print_width * 10 + *fmt - '0';
				fmt ++;
			}
		}

		else if(*fmt == '*') {
		    fmt ++;
			print_width = va_arg(ap, int);
		}

		switch(*fmt) {
		    case's':
				temp_fmt = va_arg(ap, char*);
				len = strlen(temp_fmt);
				for(i = 0; i < len; i ++) {
				    *temp_out++ = *temp_fmt;
				}
				continue;
			case 'd': break;
		}

		num = va_arg(ap, int);
		j = 0;
		if(num == 0) {
		    num_s[j++] = '0';
		}

		else {
		    if(num < 0) {
				*temp_out++ = '-';
				num = -num;
			
			}

			while(num) {
			    num_s[j++] = num%10 + '0';
				num /= 10;
			}
		}

		if(j < print_width) {
		    num = print_width - j;
			c = flag & 1 ? '0':' ';
			while(num--) {
			    *temp_out++ = c;
			}
		}
		while(j--) {
		    *temp_out++ = num_s[j];
		}

	}
	*temp_out = '\0';
	return 0;
*/
	char *temp_out = out;
//	const char* temp_fmt;
//	va_start(ap, fmt);

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
					char whole_content[32] = "";

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

//				 char* fill_width = "0";
//				 size_t len_zero = strlen(fill_width);
                 char val_str[56] = "";

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
//					}
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
				 //char temp[65535] = "";
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

/*       default :
				{
				//进入default说明%后面有占位符和宽度
				char *fill_content = "";

				*fill_content = *fmt;

				fill_content[1]  = '\0';
				//fill_content是储存了占位符的数组的头指针

				size_t para_width = 0;
	
			//用于统计%之后，'d'或'x'之前的字符的数量，包括占位符和打印宽度
              
                const char* temp_fmt = fmt;

				while(*temp_fmt != 'd' && *temp_fmt != 'x') {
					para_width ++;
                    temp_fmt ++;
				}

			   char type = *temp_fmt;

			   char *width_num = "";

			   temp_fmt = fmt;
		   //让temp_fmt再次指向占位符

			   temp_fmt ++;
			   //temp_fmt指向了宽度字符的头

			   for(size_t i = 0; i < para_width - 1; i ++) {
				   width_num[i] = *temp_fmt;
				   temp_fmt ++;
			   }
			   width_num[para_width - 1] = '\0';
			   //把打印宽度读取到width_num所指向的字符数组中
               
			   size_t print_width = str_to_int(width_num);
			   //取出打印宽度的数值
			   
			   int val = va_arg(ap, int);
			   //从参数表中取出该数

			   char temp[65535];
			   char *head = temp;

			   switch(type) {
			       case 'd': {
			                     char *result = int_to_str(val, head);
			                     size_t len = strlen(result);
								 //把该数变成字符数组，并计算长度
			                 
								 char complete[512]; 
								 char* the_whole_fill = &complete[0];
	
					   			 for(size_t i = 0; i < print_width - len; i ++) {
									 the_whole_fill = strcat(the_whole_fill, fill_content);
								 }
								//先补上前面的占位符 
               
								 the_whole_fill = strcat(the_whole_fill, result);
								//把整数转换成的字符串也填上去
							 
								 temp_out = strcpy(temp_out, the_whole_fill);
								//把整个完善好的结果放到temp_out后面
			  
								 for(size_t i = 0; i < print_width; i ++) {
									 temp_out ++;
								 }
								 //把temp_out的指针指向下一个空处
		     
								 while(*fmt != 'd') {
									 fmt ++;
								 }
								 //由于fmt一直指向%后面的占位符，先把fmt移动到'd'或'x'上
								 fmt ++;
								 //fmt此时便指向了下一个字符

								 break;
							 }

				  case 'x': {
								char *result = to_hex(val, head);
			                     size_t len = strlen(result);
								 //把该数变成字符数组，并计算长度
			                  
								 char* the_whole_fill = "";

					   			 for(size_t i = 0; i < print_width - len; i ++) {
									 the_whole_fill = strcat(the_whole_fill, fill_content);
								 }
								//先补上前面的占位符 
               
								 the_whole_fill = strcat(the_whole_fill, result);
								//把整数转换成的字符串也填上去
							 
								 temp_out = strcpy(temp_out, the_whole_fill);
								//把整个完善好的结果放到temp_out后面
			  
								 for(size_t i = 0; i < print_width; i ++) {
									 temp_out ++;
								 }
								 //把temp_out的指针指向下一个空处
			     
								 while(*fmt != 'd') {
									 fmt ++;							 }
								 //由于fmt一直指向%后面的占位符，先把fmt移动到'd'或'x'上
								 fmt ++;
								 //fmt此时便指向了下一个字符

								 break;
			
							}
				 default: {assert(0); break;}
			   }
			   break;
			}
		}
*/
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
