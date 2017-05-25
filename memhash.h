#include <string.h>
#include <memory.h>
#include "memblock.h"


struct mem_bucket{
	int val_len;
	int key_len;
	unsigned long hash;
	char *key;
	char *val;
	struct mem_bucket *next;
};



struct memhash{
	struct memblock;
	int size;
	struct mem_bucket*  ht1[0];	
} ;

#ifdef __cplusplus    //__cplusplus是cpp中自定义的一个宏
extern "C" {
#endif


struct memhash * memhash_new(int size);
int memhash_free(struct memhash *mh);
int memhash_clear(struct memhash *mh);
void *memhash_get(struct memhash *mh,const char *key, int keylen, int *val_len);
int memhash_set(struct memhash *mh,const char *key, int key_len, const void *val, int val_len);

#ifdef __cplusplus
}
#endif