#include <string.h>
#include <memory.h>
#include "memhash.h"

static size_t memhash_hash(const char *buf){
    unsigned int hash = 5381;
    unsigned char c;
    while ((c=*buf++)!='\0')
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

int memhash_free(struct memhash *mh){
	struct memblock *mb=(struct memblock *)mh;
	mem_freePool(mb);
}
struct memhash * memhash_new(int s){
	size_t size=sizeof(struct memhash)+s*(sizeof(struct mem_bucket)+120);
	//struct memblock *mb=mem_allocPool_ext(size,size);
	//if(mb==NULL)  return NULL;
	//struct memhash *mh=mem_alloc(mb,sizeof(struct memhash)+s*(sizeof(struct mem_bucket)));
	struct memhash *mh=(struct memhash *) mem_allocPool_ext(size,size);
	printf("mhaddr:%p *mh:%p used:%ld  capc:%ld\n",mh,*mh,mh->__used_,mh->__capc_);	
	mh->__used_=sizeof(struct memhash) -sizeof(struct memblock)+sizeof(void *)*s;

	mh->size=s;
	return mh;

}

int memhash_clear(struct memhash *mh){
	memset(mh->ht1,0x00,sizeof(struct mem_bucket ) * (mh->size ) );
	int s=sizeof(struct memhash) +(mh->size) *(sizeof(struct mem_bucket));
	mh->__used_=s;
}


int memhash_set(struct memhash *mh,const char *key, int key_len, const void *val, int val_len){
	int hash=memhash_hash(key)%mh->size;
	struct mem_bucket * *bk=&(mh->ht1[hash]);		
	while( (*bk)!=NULL){
		bk=&(*bk)->next;
	}
	int size=sizeof(struct mem_bucket)+key_len+val_len+1+1;
	printf("set key %s %d bkaddr:%p %p\n",key,hash,bk,&(mh->ht1[hash]));
	struct memblock *mb=(struct memblock *)mh;
	(*bk)=mem_alloc1((struct memblock *)mh,size);
	if(bk==NULL)  return -1;
	(*bk)->key=(*bk)+1;
	(*bk)->key_len=key_len;
	(*bk)->val_len=val_len;
	(*bk)->val=((*bk)->key)+key_len+1;
	strncpy((*bk)->key,key,key_len);
	strncpy((*bk)->val,val,val_len);
	(*bk)->next=NULL;
	//mb->used++;
	return 0;	
}

int memhash_set1(struct memhash *mh,const char *key, int key_len, const void *val, int val_len){
	int hash=memhash_hash(key)%mh->size;
	struct mem_bucket * *bk=&(mh->ht1[hash]);		
	while( (*bk)!=NULL){
		bk=&(*bk)->next;
	}
	printf("set key %s %d bkaddr:%p %p\n",key,hash,bk,&(mh->ht1[hash]));
	struct memblock *mb=(struct memblock *)mh;
	(*bk)=mem_alloc1((struct memblock *)mh,sizeof(struct mem_bucket));
	if(bk==NULL)  return -1;
	(*bk)->key=mem_alloc1((struct memblock *)mh,key_len+1);
	(*bk)->val=mem_alloc1((struct memblock *)mh,val_len+1);
	strncpy((*bk)->key,key,key_len);
	strncpy((*bk)->val,val,val_len);
	(*bk)->next=NULL;
	//mb->used++;
	return 0;	
}

void *memhash_get(struct memhash *mh,const char *key, int keylen,  int *val_len){
	int hash=memhash_hash(key)%mh->size;
	struct mem_bucket *bk=mh->ht1[hash];		
	printf("get key %s %d %p\n",key,hash,bk);
	while( bk!=NULL){
		if(strcmp(key,bk->key)==0)  break;
		bk=bk->next;
	}
	if(bk==NULL)  return NULL;
	*val_len=bk->val_len;
	return bk->val;
}