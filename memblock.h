#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

struct memblock {
  size_t __used_;
  size_t __capc_;
  size_t __extr_;
  struct memblock **madr;
  char __cadr[0];
};

#define mem_hook(m)         ((m)->madr) =&(m)
#define mem_reth(m)        (*((m)->madr)=(m)) 

//printf("mark1 %p %pcapc:%d d:%d\n",(m),(m)->__cadr+(m)->__capc_,(m)->__capc_,d);              			\
   			//memset((m)->__cadr+(m)->__capc_ ,0x00,d-1); 			\

#define mem_alloc(m, c)                                                        \
  ({                                                                           \
    void *ptr = NULL;                                                          \
    if ((m)->__used_ + (c) > ((m)->__capc_)) {                                 \
      if ((m)->__extr_ != 0) {                                                 \
        unsigned long d = ((int)(c / (m)->__extr_) + 1) * ((m)->__extr_);      \
        (m) = realloc((m), (m)->__capc_ + d);                                  \
        if ((m) == NULL)                                                       \
          ptr = NULL;                                                          \
        if ((m) != NULL) {                                                      \
          (m)->__capc_ += d;     mem_reth(m);            }                      \
      }                                                                        \
    }                                                                          \
    if ((m)->__used_ + (c) < ((m)->__capc_)) {                                 \
      (m)->__used_ += c;                                                       \
      ptr = (m)->__cadr + (m)->__used_;                                        \
    }                                                                          \
    ptr;                                                                       \
  })

static inline void * mem_alloc1(struct memblock *m,size_t c){
		void * ptr=NULL;
		if(m->__used_ +c  >= m->__capc_) {
				if(m->__extr_!=0){
					size_t d =((c+1)/m->__extr_+1)	*m->__extr_;
					assert(d>c);
				//	void *t=malloc(m->__capc_+d);
					//void *t=realloc(m,(m->__capc_+c));
					void *t=realloc(m,m->__capc_+d);
					if(t==NULL)  
						return NULL;
					m=t;
					//printf("memset %p size %ld\n",(m->__cadr+m->__capc_),d);
					//memset((m->__cadr+m->__capc_),0x00,d);
					memset((m->__cadr+m->__capc_),0x00,d);
					mem_reth(m);
					m->__capc_+= d ;
					//m->__capc_+= d ;
				}
		}
		assert(m->__used_+c < m->__capc_);
		if(m->__used_ +c  < m->__capc_) {
			//m->__used_+=c;
			ptr=m->__cadr+m->__used_;
			m->__used_+=c;
		}
		return ptr;
}


static inline void *mem_freePool(struct memblock *ptr) { free(ptr); }

static inline struct memblock *mem_allocPool_ext(unsigned long ca,
                                                 unsigned long ex) {

  int pgsz=getpagesize();
  size_t c=((ca/pgsz)+1)*pgsz;
  size_t e=((ex/pgsz)+1)*pgsz;
  struct memblock *ptr = malloc(c);
  if (ptr == NULL)
    return NULL;
  memset(ptr, 0x00, c);
  //ptr->__used_ = sizeof(struct memblock);
  ptr->__used_ = 0;
  ptr->__capc_ = c-sizeof(struct memblock)-0x10;
  //ptr->__capc_ = c  ;
  ptr->__extr_ = e;
  //ptr->__extr_ = 100;
  return ptr;
}

#define mem_allocPool(p) mem_allocPool_ext(p, 0)
