#include "klib.h"

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
/******GC***
  size_t count = 0;
  while(s[count] != '\0') {
	  count ++;
  }
//  printf("Length:%d\n",count);
  return count;
************
*/

    size_t size = 0;
	while(*(s++)) {
	    size ++;
	}
	return size;

}

char *strcpy(char* dst,const char* src) {
//#####CO###
  size_t i = 0;
  while(*(src+i) != '\0') {
      *(dst+i) = *(src+i);
	  i ++;
  }

  return dst;
//##########

/******GC***
	if (src == NULL) {
		assert(0);
	    return NULL;
	}

	size_t length = strlen(src);

	char store_src[length];

    for(int i = 0; i < length; i ++) {
	    store_src[i] = src[i];
	}
	store_src[length] = '\0';

	for(int i = 0; i < length; i ++) {
	    dst[i] = store_src[i];
	}
	dst[length] = '\0';

	return dst;
************/
//	return strncpy(dst, src, strlen(src));

}

char* strncpy(char* dst, const char* src, size_t n) {
//#####CO###
  size_t i = 0;
  for(i = 0; src[i] != '\0'; ++i) dst[i] = src[i];
  for(; i < n; ++i) dst[i] = '\0';
  return dst;
//##########
/******GC***
	if (src == NULL) {
		assert(0);
	    return NULL;
	}

	size_t length = strlen(src);

//The first version correct codes
//	if (n > length) {
//	    return strncpy(dst, src, length);
//	}
//
//	else {
//	    char str[length+1];
//		char* head = str;
//		size_t i = 0;
//		while(i < n) {
//		    *(head+i)= *(src+i);
//			i ++;
//		}
//		str[n] = '\0';
//		head = str;
//		char* result = dst;
//		while((*(dst++) = *(head++)));
//		return result;
//	}


	if(n >= length) {

		char store_src[length];

		for(int i = 0; i < length; i ++) {
		    store_src[i] = src[i]; 
		}
		store_src[length] = '\0';

        for(int i = 0; i < length; i ++) {
		    dst[i] = store_src[i];
		}
		dst[length] = '\0';
	    
		return dst;
	}

	else {
	    
		char store_src[n];

		for(int i = 0; i < n; i ++) {
		    store_src[i] = src[i];
		}
		store_src[n] = '\0';

		for(int i = 0; i < length; i ++) {
		   dst[i] = store_src[i];
		}
		dst[n] = '\0';

		return dst;
	}
***********/

/*

	else {
		char* temp = dst;
		int count = 0;
		while(*src != '\0' && count < n) {
            *temp = *src;
		    temp ++;
		    src ++;
	        count ++;	
		}
		*temp = '\0';
	return dst;
	}
*/
}

char* strcat(char* dst, const char* src) {
//#####CO###
  size_t dst_len = strlen(dst);
  size_t i = 0;

  for(i = 0; src[i] != '\0'; ++i) {
      dst[dst_len+i] = src[i];
  }
  dst[dst_len + i] = '\0';
  return dst;
//##########
/******GC***	
	char* temp_dst = dst;
	while(*temp_dst != '\0') {
	    temp_dst ++;
	}

    size_t length = strlen(src);

	char store_src[length];

	for(int i = 0; i < length; i ++) {
	    store_src[i] = src[i];
	}
	store_src[length] = '\0';

	for(int i = 0; i < length; i ++) {
	    temp_dst[i] = store_src[i];
	}
	temp_dst[length] = '\0';

    return dst;
*************/

/*/#####CO###The first version of correct 
	char* result = dst;
	while(*dst) {
	    dst ++;
	}
	strcpy(dst, src);
	return result;
*///##########
/*
	size_t n = strlen(src);
	for(size_t i = 0; i < n; i ++) {
	    *temp_dst = src[i];
	    temp_dst ++;
	}

	*temp_dst = '\0'; 
*/
}

int strcmp(const char* s1, const char* s2) {
//#####CO###
  int l1 = strlen(s1);
  int l2 = strlen(s2);

  int l = 0;
  if(l1 < l2) l = l1;
  else l = l2;
  for(int i = 0; i <=l; ++i) {
      if(s1[i] < s2[i]) return -1;
	  else if(s1[i] > s2[i]) return 1;
  }
  return 0;
//##########
/*****GC***
	int len_s1 = strlen(s1);
	int len_s2 = strlen(s2);

	int flag = 0;
    
	if(len_s1 == len_s2) {
	    for(int i = 0; i < len_s1; i ++) {
		    if(s1[i] > s2[i]) {
			///	printf("S1 Bigger!\n");
				flag = 1;
			    return flag;
			}

			if(s1[i] < s2[i]) {
				//printf("S2 Bigger!\n");
				flag = -1;
			    return flag;
			}

		}
		//printf("Equal!\n");
		return flag;
	}

	if(len_s1 > len_s2) {
	    for(int i = 0; i < len_s2; i ++) {
		    if(s1[i] > s2[i]) {
		//		printf("S1 Bigger!\n");
			    flag =  1;
			    return flag;
			}

			if(s1[i] < s2[i]) {
			//	printf("S2 Bigger!\n");
			    flag = -1;
			    return flag;
			}

		}
		//printf("Equal!\n");
		flag = 1;
	    return flag;
	    
	}

	else {
	    for(int i = 0; i < len_s1; i ++) {
		    if(s1[i] > s2[i]) {
			//	printf("S1 Bigger!\n");
			    flag =  1;
			    return flag;
			}

			if(s1[i] < s2[i]) {
			//	printf("S2 Bigger!\n");
			    flag = -1;
			    return flag;
			}

		}
	//	printf("Equal!\n");
	    flag = -1;
	    return flag;
	    
	}
*********/

/*
	int flag = 0;

	while(((flag = (*s1 - *s2)) == 0) && *s1 && *s2) {
	    s1 ++;
		s2 ++;
	}

	return flag;
*/
}

int strncmp(const char* s1, const char* s2, size_t n) {
//#####GC##
  for(size_t i = 0; i < n; ++i) {
      if(s1[i] <s2[i]) return -1;
	  else if(s1[i] >s2[i]) return 1;
  }
  return 0;
//#########
/*****GC***
	size_t len_s1 = strlen(s1);
	size_t len_s2 = strlen(s2);

    if(n >= len_s1 && n >= len_s2) {
		if(len_s1 == len_s2) {
			for(int i = 0; i < len_s1; i ++) {
				if(s1[i] > s2[i]) {
					return 1;
				}	

				if(s1[i] < s2[i]) {
					return -1;
				}

			}
			return 0;
		}

		if(len_s1 > len_s2) {
			for(int i = 0; i < len_s2; i ++) {
				if(s1[i] > s2[i]) {
					return 1;
				}

				if(s1[i] < s2[i]) {
					return -1;
				}

			}
			return 1;
	    
		}

		else {
			for(int i = 0; i < len_s1; i ++) {
				if(s1[i] > s2[i]) {
					return 1;
				}

				if(s1[i] < s2[i]) {
					return -1;
				}

			}
			return -1;
		}
    }

    if ( n <= len_s1 && n <= len_s2) {
		for(int i = 0; i < n; i ++) {
			if(s1[i] > s2[i]) {
				return 1;
			}	

			if(s1[i] < s2[i]) {
				return -1;
			}

		}
		return 0;
	    
	}	

	else {
	    if (len_s1 > len_s2) {
			for(int i = 0; i < len_s2; i ++) {
			    if(s1[i] > s2[i]) {
					return 1;
				}

			    if(s1[i] < s2[i]) {
					return -1;
				}

			}
			return 1;
		
		}

		else {
			for(int i = 0; i < len_s1; i ++) {
			    if(s1[i] > s2[i]) {
					return 1;
				}

			    if(s1[i] < s2[i]) {
					return -1;
				}

			}
			return -1;
		
		}
	}
************/

}

void* memset(void* v,int c,size_t n) {
//#####CO###
  if(v == NULL || n < 0) return NULL;
  char* temp = (char*) v;
  for(int i = 0; i < n; ++i) {
      temp[i] = (char) c;
  }
  return v;
//##########
/*****GC**	
  char* temp_v = (char *)v;
  for(size_t i = 0; i < n; i ++) {
      temp_v[i] = c;
  }
  return v;
**********/
/*First version of co	
	void* ret = v;
	while(n--) {
	    *(char*)v = (char)c;
		v = (char*)v + 1;
	}
	return ret;
*/
}

void* memcpy(void* out, const void* in, size_t n) {
//#####CO###
    if(out == NULL ||n < 0) return NULL;
    char* charout = (char*) out;
	char* charin = (char*) in;
    
	for(int i = 0; i < n;  ++i) {
	    charout[i] = charin[i];
	}

	return out;

//##########
/*****GC***

  char* temp_out = (char *)out;
  char* temp_in = (char *)in;

  char store_in[n];

  for(size_t i = 0; i < n; i ++) {
      store_in[i] = temp_in[i];
  }
  temp_in[n] = '\0';

  for(size_t i = 0; i < n; i ++) {
      temp_out[i] = store_in[i];
  }
//  temp_out[n] = '\0';

  return out;
**********/
/*
*/
/*  
	void* ret = out;
	char *begin1 = (char*) out;
	const char *begin2 = (const char *)in;
	while(n--) {
	    *(begin1+n-1) = *(begin2+n-1);
	}
	return ret;
*/
/*####First Version of CO
   assert((out!=NULL) && (in!=NULL));
   if(out < in || (char*)out > (char*)in + n) {
       for(int i = 0; i < n; i ++) {
	       *(char*)(out+i) = *(char*)(in+i);
	   }
   }
   else{
       for(int i = n; i > 0; i --) {
	       *(char*)(out+n-i) = *(char*)(in+i);
	   }
   }
   return out;
*/

}

int memcmp(const void* s1, const void* s2, size_t n) {
//#####CO###
  char* c1 = (char*)s1;
  char* c2 = (char*)s2;

  for(int i = 0; i < n; ++i) {
      if(c1[i] < c2[i]) return -1;
	  else if(c1[i] > c2[i]) return 1;
  }
  return 0;
//##########
/******GC***	
	const char* temp_s1 = (char*)s1;
	const char* temp_s2 = (char*)s2;

	while(*temp_s1 == *temp_s2 && --n>0) {
	    temp_s1 ++;
		temp_s2 ++;

	}

	int flag = *temp_s1 - *temp_s2;
	if(flag > 0)
	{
	    return 1;
	}
	else if(flag < 0)
	{
		return -1;
	}
	else
	{
	    return flag;
	}
**********/

/*	
  unsigned char* temp_s1 = (unsigned char *)s1;
  unsigned char* temp_s2 = (unsigned char *)s2;
  for(size_t i = 0; i < n; i++) {
      if(temp_s1[i] > temp_s2[i]) {
	      return 1;
	  }

	  if(temp_s1[i] < temp_s2[i]) {
	      return -1;
	  }
	 
  }
  return 0;
*/  
}


#endif
