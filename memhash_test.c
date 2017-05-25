#include <stdio.h>
#include <assert.h>
#include "memhash.h"

int main(int args,char **argv){
		struct memhash *s=memhash_new(127000);
		mem_hook(s);
		assert(s!=NULL);
		
			int i=0;
			char key[100];
			char val[100];
		for(i=0;i<120000;i++){
			memset(key,0x00,sizeof(key));
			memset(val,0x00,sizeof(val));
			sprintf(key,"key %d     ",i);
			sprintf(val,"val (%d    )",i);
			memhash_set(s,key,strlen(key),val,strlen(val));	
//		printf("memblock: %p %d %d %d\n",s,s->__used,s->__capc,s->__extr);
			//printf("set %s =>%s \n",key,val);
		}

		for(i=0;i<120000;i++){
			sprintf(key,"key %d     ",i);
			int vallen;
			void *valptr=memhash_get(s,key,strlen(key),&vallen);	
			if(valptr==NULL){ 
				printf("ptr is null\n");
			   	return -1;
			}
		//	printf("%s =>%s \n",key,valptr);
		}
			
		printf("e:%p %d\n",s,s->__capc_);
		memset(key,0x00,sizeof(key));
		memset(val,0x00,sizeof(val));

		sprintf(key,"key %d				",1000);
		sprintf(val,"val (%d)			",1000);
		memhash_set(s,key,strlen(key),val,strlen(val));	


		return 0;
}
