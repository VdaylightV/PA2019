#include "klib.h"

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t count = 0;
  while(*s != '\0') {
	  count ++;
	  s ++;
  }
  return count;
}

char *strcpy(char* dst,const char* src) {
	if (src == NULL) {
		assert(0);
	    return NULL;
	}
    
	else {
		char* temp = dst;
	    while(*src != '\0') {
            *temp = *src;
		    temp ++;
		    src ++;
	    }
		return dst;
	}
}

char* strncpy(char* dst, const char* src, size_t n) {
	if (src == NULL) {
		assert(0);
	    return NULL;
	}

	else {
		char* temp = dst;
		int count = 0;
		while(*src != '\0' && count < n) {
            *temp = *src;
		    temp ++;
		    src ++;
	        count ++;	
		}
	return dst;
	}
}

char* strcat(char* dst, const char* src) {
	char* temp_dst = dst;
	while(*temp_dst != '\0') {
	    temp_dst ++;
	}

	size_t n = strlen(src);
	for(size_t i = 0; i < n; i ++) {
	    *temp_dst = src[i];
	    temp_dst ++;
	}

	*temp_dst = '\0'; 

    return dst;
}

int strcmp(const char* s1, const char* s2) {

	int len_s1 = strlen(s1);
	int len_s2 = strlen(s2);
    
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

int strncmp(const char* s1, const char* s2, size_t n) {

	int len_s1 = strlen(s1);
	int len_s2 = strlen(s2);

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

		else {
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
	}

}

void* memset(void* v,int c,size_t n) {
  int* temp_v = (int *)v;
  for(size_t i = 0; i < n; i ++) {
      *temp_v = c;
	  temp_v ++;
  }
  return v;
}

void* memcpy(void* out, const void* in, size_t n) {
  unsigned char* temp_out = (unsigned char *)out;
  unsigned char* temp_in = (unsigned char *)in;
  for(size_t i = 0; i < n; i ++) {
	  *temp_out = *temp_in;
	  temp_out ++;
	  temp_in ++;
  }
  return out;
}

int memcmp(const void* s1, const void* s2, size_t n){
  unsigned char* temp_s1 = (unsigned char *)s1;
  unsigned char* temp_s2 = (unsigned char *)s2;
  for(size_t i = 0; i < n; i++) {
      if(*temp_s1 > *temp_s2) {
	      return 1;
	  }

	  if(*temp_s1 < *temp_s2) {
	      return -1;
	  }
	 
	  else {
	      temp_s1 ++;
		  temp_s2 ++;
	  }
  }
  return 0;
}


#endif
