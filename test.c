/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017/03/09 21时01分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void showcur(){
	void *p=sbrk(0);
	printf("current:%p\n",p);

}

void *mymalloc(size_t size){
	void *p;
	p=sbrk(0);
	if(sbrk(size)==(void* )-1)
		return NULL;
	return p;
}

int main(){
	showcur();
	void *k=malloc(409600000);
	showcur();
	void *p=mymalloc(5);
	printf(" %p %p\n",k,p);

	return 0;
}
