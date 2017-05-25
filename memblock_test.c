#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "memblock.h"

int main(){
//	test0();
//	test1();
	test2();

}


int test2(){
	struct memblock  * mem=mem_allocPool_ext(100,100);
	mem_hook(mem);
	printf("memblock %d head %p %p\n",sizeof(struct memblock),mem,mem->madr);
	printf("mem %p used:%d capc %d\n",mem,mem->__used_,mem->__capc_);
	struct memblock * p=mem;
	
	int i;
	for(i=10;i<1000000;i++){
			if(i!=100){
			void *ptr=mem_alloc1(mem,4096);
			memset(ptr,0x00,4096);
			strcpy(ptr,"h4096");
			}

		if(mem!=p){
			p=mem;
			printf(" haha %i %p %p %ld %ld \n",i,mem,*(mem->madr),mem->__used_,mem->__capc_);
		}
	}


}

int test1(){
	struct memblock  * mem=mem_allocPool(100);
	assert(mem->__capc_==100);
	assert(mem->__used_==0);
	void *ptr=mem_alloc(mem,10);
	assert(mem->__cadr[99]==NULL);
	assert(ptr!=NULL);
	assert(mem->__used_==10);
	ptr=mem_alloc(mem,60);
	assert(mem->__used_==70);
	assert(ptr!=NULL);
	ptr=mem_alloc(mem,41);
	assert(ptr==NULL);
}

int test0(){

	struct memblock  * mem=mem_allocPool_ext(100,100);
	printf("mem:%p\n",mem);
	void *ptr=mem_alloc(mem,10);
	void *tmp=malloc(100);
	printf("mem:%p\n",mem);
	ptr=mem_alloc(mem,20);
	printf("mem:%p\n",mem);
	ptr=mem_alloc(mem,500);
	assert(mem->__capc_=600);
	assert(mem->__cadr[299]==NULL);
	assert(ptr!=NULL);
	assert(mem->__used_==530);
	
	return 0;
}