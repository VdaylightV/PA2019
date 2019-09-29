#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

extern uint32_t token_end;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
	wp_pool[i].work_state = false;
	wp_pool[i].expression[0] = '\0';
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

WP *new_wp() {
   int index = 0;
   WP *follow_free_ = NULL;
   while ( ((*free_).work_state != false) && (index != 32) ) {
       follow_free_ = free_;
	   free_ = (*free_).next;
	   index ++;
   }

   assert(index != 32);
   WP *temp = free_;
   (*temp).work_state = true;
   
   if ( follow_free_ == NULL ) {
       free_ = (*free_).next;
	   return temp;
   }

   else if ( (*free_).next != NULL ) {
       (*follow_free_).next = (*free_).next;
       free_ = wp_pool;	   
	   return temp;
   }

   else if ( (*free_).next == NULL ) {
	   (*follow_free_).next = NULL;
	   free_ = wp_pool;
	   return temp;
   }

   else {
	    assert(0);
	}
}

void free_wp(WP *wp) {
    (*wp).work_state = false;
	WP *tail = free_;
	while( (*tail).next != NULL ) {
	    tail = (*tail).next;
	}

	(*tail).next = wp;
	tail = wp;
	(*tail).next = NULL;
}

void delete_wp( int NO ) {
    WP *follow_wp_NO = NULL;
	WP *wp_NO = head;

	while ( (*wp_NO).NO != NO && (*wp_NO).next != NULL ) {
		follow_wp_NO = wp_NO;
		wp_NO = (*wp_NO).next;
	}
    
	if ( follow_wp_NO == NULL ) {
		head = (*head).next;
        free_wp(wp_NO);
	}

	else if ( (*wp_NO).next != NULL ) {
	    (*follow_wp_NO).next = (*wp_NO).next;
        free_wp(wp_NO);
	}

	else if ( (*wp_NO).next == NULL && (*wp_NO).NO == NO ) {
	    (*follow_wp_NO).next = NULL;
		free_wp(wp_NO);
	}
    
	else {
		printf("The NO.%d watchpoint does not exist!\n",NO);
	    assert(0);
	}
}

void set_wp(WP *wp, char *args) {
    for (int i = 0; i <= 31; i ++) {
	    (*wp).expression[i] = '\0';
	}
    
	int j = 0;
	while (*args != '\0') {
	    (*wp).expression[j] = *args;
		j ++;
		args ++;
	}

/*	
    if (!make_token(&((*wp).expression)[0])) {
	    *success = false;
		return ;
	}
*/	
	bool success = true;

	uint32_t expression_value = expr(&((*wp).expression[0]), &success);
	assert(token_end != 0);
	(*wp).Old_Value = (*wp).New_Value = expression_value;

	if ( head == NULL ) {
	    (*wp).next = NULL;
		head = wp;
	}

	else {
	    WP *tail = head;
		while ( (*tail).next != NULL ) {
		    tail = (*tail).next;
		}
        (*tail).next = wp;
		(*wp).next = NULL;
	}
    
}

void wp_display() {
    assert(head != NULL);
	WP *ptr = head;
    while ( (*ptr).next != NULL ) {
	    printf("WatchPoint NO: %d\n",(*ptr).NO);
		printf("The Expression Under Watch: ");
		int j = 0;
		while ( (*ptr).expression[j] != '\0' ) {
		    printf("%c", (*ptr).expression[j]);
			j ++;
		}
		printf("\n");
        printf("The Old Value: %u\n", (*ptr).Old_Value);
        printf("The New Value: %u\n", (*ptr).New_Value);
        ptr = (*ptr).next;
	}
	printf("WatchPoint NO: %d\n",(*ptr).NO);
	printf("The Expression Under Watch: ");
	int j = 0;
	while ( (*ptr).expression[j] != '\0' ) {
		printf("%c", (*ptr).expression[j]);
		j ++;
	}
	printf("\n");
	printf("The Old Value: %u\n", (*ptr).Old_Value);
	printf("The New Value: %u\n", (*ptr).New_Value);

}

uint32_t wp_detect() {
	uint32_t Flags = 0;
    if ( head == NULL ) {
	    return Flags;
	}

	else {
	    WP *ptr = head;
	    bool success = true;

		while ( (*ptr).next != NULL ) {
			uint32_t expression_value = expr(&((*ptr).expression[0]), &success);

			assert(token_end != 0);

			(*ptr).Old_Value = (*ptr).New_Value; 
		    (*ptr).New_Value = expression_value;
		    
			if ( (*ptr).Old_Value != (*ptr).New_Value ) {
			    Flags ++;
			}

            ptr = (*ptr).next;
		}

		uint32_t expression_value = expr(&((*ptr).expression[0]), &success);

		assert(token_end != 0);

		(*ptr).Old_Value = (*ptr).New_Value; 
		(*ptr).New_Value = expression_value;
		
		if ( (*ptr).Old_Value != (*ptr).New_Value ) {
			Flags ++;
		}
    }
	return Flags;
}

/* TODO: Implement the functionality of watchpoint */



