#include "klib.h"
#include "stdio.h" 

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t count = 0;
  while(s[count] != '\0') {
	  count ++;
  }
  printf("Length:%d\n",count);
  return count;
}

char *strcpy(char* dst,const char* src) {
	if (src == NULL) {
		assert(0);
	    return NULL;
	}
/*  //Forget to consider the problem of overlapping  
	else {
		char* temp = dst;
	    while(*src != '\0') {
            *temp = *src;
		    temp ++;
		    src ++;
	    }
		*temp = '\0';
		return dst;
	}
*/
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


}

char* strncpy(char* dst, const char* src, size_t n) {
	if (src == NULL) {
		assert(0);
	    return NULL;
	}

	size_t length = strlen(src);

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

	int len_s1 = strlen(s1);
	int len_s2 = strlen(s2);
    
	if(len_s1 == len_s2) {
	    for(int i = 0; i < len_s1; i ++) {
		    if(s1[i] > s2[i]) {
				printf("S1 Bigger!\n");
			    return 1;
			}

			if(s1[i] < s2[i]) {
				printf("S2 Bigger!\n");
			    return -1;
			}

		}
		printf("Equal!\n");
		return 0;
	}

	if(len_s1 > len_s2) {
	    for(int i = 0; i < len_s2; i ++) {
		    if(s1[i] > s2[i]) {
				printf("S1 Bigger!\n");
			    return 1;
			}

			if(s1[i] < s2[i]) {
				printf("S2 Bigger!\n");
			    return -1;
			}

		}
		printf("Equal!\n");
		return 1;
	    
	}

	else {
	    for(int i = 0; i < len_s1; i ++) {
		    if(s1[i] > s2[i]) {
				printf("S1 Bigger!\n");
			    return 1;
			}

			if(s1[i] < s2[i]) {
				printf("S2 Bigger!\n");
			    return -1;
			}

		}
		printf("Equal!\n");
		return -1;
	    
	}

}

int strncmp(const char* s1, const char* s2, size_t n) {

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

}

void* memset(void* v,int c,size_t n) {
  int* temp_v = (int *)v;
  for(size_t i = 0; i < n; i ++) {
      temp_v[i] = c;
  }
  return v;
}

void* memcpy(void* out, const void* in, size_t n) {
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
}

int memcmp(const void* s1, const void* s2, size_t n){
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
}


#endif
