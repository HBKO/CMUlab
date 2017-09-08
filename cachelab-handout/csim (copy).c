#include "cachelab.h"
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 100

int s=0,E=0,b=0;
char *fp=NULL;
int miss=0,hit=0,eviction=0;
long clocktime=0;     //used to record the access time

//No need the block
struct cache
{
	int *valid;
	long *tag;
	clock_t *time_stamp;
};

struct cache *oneSet;

// the function shengming
void get_opt(int argc,char *const argv[]);
void get_file();
void do_init();
void de_init();
int getset(unsigned long addr);
long gettag(unsigned long addr);
void do_L(unsigned long address,int size);
void do_S(unsigned long address,int size);
void do_M(unsigned long address,int size);

int main(int argc,char *const argv[])
{
//    printSummary(0, 0, 0);
 //   void get_opt(int argc,char *const argv[]);
    void init();
    get_opt(argc,argv);

  //  printf("%d\n%d\n%d\n",s,E,b);
//    get_file();
    do_init();
    get_file();
//    printf("hits:%d misses:%d evictions:%d \n",hit,miss,eviction);
    de_init();
    printSummary(hit,miss,eviction);
    return 0;
}


void get_opt(int argc,char *const argv[])
{
	int ch=0;
	while((ch=getopt(argc,argv,"s:E:b:t:"))!=-1)
	{
		switch(ch)
		{
			case 's':
			{
				s=atoi(optarg);
				break;
			}
			case 'E':
			{
				E=atoi(optarg);
				break;
			}
			case 'b':
			{
				b=atoi(optarg);
				break;
			}
			case 't':
			{
				fp=optarg;
				break;
			}
			default:
			{
				printf("illeg operation!");
				exit(0);
			}
		}
	}
}


void get_file()
{
	FILE *filename=fopen(fp,"r");
	if(filename==NULL)
	{
		fprintf(stderr,"open file error\n");
		exit(0);
	}
	//read the information from the file
	char access_type;
	unsigned long address;
	int size;
	char buf[MAXSIZE];
	/* so we need to read a character, a hex number, and a decimal number */
	while(fgets(buf,MAXSIZE,filename)!=NULL)
	{
		sscanf(buf,"%s %lx,%d",&access_type,&address,&size);
		printf("acess_type:%c, address:%lx, size:%d\n",access_type,address,size);
//		printf("set:%d tag:%lx\n",getset(address),gettag(address));
		if(access_type=='L')
		{
			do_L(address,size);
		}
		else if(access_type=='S')
		{
			do_S(address,size);
		}
		else if(access_type=='M')
		{
			do_M(address,size);
		}   
	}


	fclose(filename);
}

void do_init()
{
	int S=(s<<1);
	if(S<0)
		printf("input is something wrong!");
	oneSet=(struct cache *)malloc(S*sizeof(struct cache));
	for(int inS=0;inS<S;++inS)
	{
		oneSet[inS].valid=(int *)malloc(E*sizeof(int));
		oneSet[inS].tag=(long *)malloc(E*sizeof(long));
		oneSet[inS].time_stamp=(clock_t *)malloc(E*sizeof(clock_t));
		for(int inE=0;inE<E;++inE)
		{
			oneSet[inS].valid[inE]=0;
			oneSet[inS].tag[inE]=0;
			oneSet[inS].time_stamp[inE]=0;
		}
	}

}


void de_init()
{
	int S=(s<<1);
	for(int inS=0;inS<S;++inS)
	{
		free(oneSet[inS].valid);
		free(oneSet[inS].tag);
		free(oneSet[inS].time_stamp);
	}
	free(oneSet);
}


void do_L(unsigned long address,int size)
{
	int set=getset(address);
//	printf("setnum=%d, ",set);
	struct cache *this_set=&oneSet[set];

	int index;
	int full=1;
	int empty_item=0;    // if not full, keep track of the empty item
	int last_item=0;     // if full, keep track of the evict item
	clock_t last_time=this_set->time_stamp[0];

	//find, and update the access_time
	for(index=0;index<E;++index)
	{
		//find the tag
		if(this_set->valid[index]==1 && gettag(address)==this_set->tag[index])
		{
			this_set->time_stamp[index]=(++clocktime);
			break;
		}
		// valid is zero
		else if(this_set->valid[index]==0)
		{
			full=0;
			empty_item=index;
		}
		// tag is wrong, and update
		else
		{
			if(this_set->time_stamp[index]<last_time)
			{
				last_time=this_set->time_stamp[index];
				last_item=index;
			}
		}
	}

	if(index==E)  //miss
	{
		miss++;
		if(full)  //evict
		{
			this_set->tag[last_item]=gettag(address);
			this_set->time_stamp[last_time]=(++clocktime);
			eviction++;
		}
		else
		{
			this_set->valid[empty_item]=1;
			this_set->tag[empty_item]=gettag(address);
			this_set->time_stamp[last_time]=(++clocktime);
		}
	}
	else
	{
		hit++;
	}
}


//the difference between S and M is that S only load when miss,while M always load
//first then store
void do_S(unsigned long address,int size)
{
	int set=getset(address);
//	printf("setnum=%d, ",set);
	struct cache *this_set=&oneSet[set];
	int index;
	//find the address
	for(index=0;index<E;++index)
	{
		if(this_set->valid[index]==1 && gettag(address)==this_set->tag[index])
		{
			this_set->time_stamp[index]=(++clocktime);
			break;
		}
	}
	//miss
	if(index==E)
	{
		do_L(address,size);
	}
	else
	{
		hit++;
	}
}


void do_M(unsigned long address,int size)
{

	do_L(address,size);
	do_S(address,size);
}



//get the set number from the address
int getset(unsigned long addr)
{
	return (int)( (addr >>b) & ((1<<s)-1)  );
}


//get the tag number from the address
long gettag(unsigned long addr)
{
	return (long)(addr >>(s+b));
}


