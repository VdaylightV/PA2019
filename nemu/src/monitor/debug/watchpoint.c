#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
	wp_pool[i].work_state = false;
	wp_pool[i].str[0] = '\0';
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

WP *new_wp() {
   index = 0
   WP *follow_free_ = NULL;
   while ( (*free_).work_state != false && index != 32 ) {
       follow_free_ = free_;
	   free_ = *free_.next;
	   index ++;
   }

   assert(index != 32);
   WP *temp = free_;
   *temp.work_state = true;
   
   if ( follow_free_ == NULL ) {
       free_ = *free_.next;
	   return temp;
   }

   else if ( *free_.next != NULL ) {
       *follow_free_.next = *free_.next;
       free_ = wp_pool;	   
	   return temp;
   }

   else if ( free_.next == NULL ) {
	   *follow_free_.next = NULL;
	   free_ = wp;
	   return temp;
   }

   else {
	    assert(0);
	}
}

void free_wp(WP *wp) {
    (*wp).work_state = false;
	WP *tail = free_;
	while( *tail.next != NULL ) {
	    tail = *tail.next;
	}

	tail.next = wp;
	tail = wp;
	tail.next = NULL;
}
/* TODO: Implement the functionality of watchpoint */


