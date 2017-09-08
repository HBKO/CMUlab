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
int getset(void * addr);
long gettag(void * addr);
void do_L(void * address,int size);
void do_S(void * address,int size);
void do_M(void * address,int size);

int main(int argc,char *const argv[])
{
    void init();
    get_opt(argc,argv);


    do_init();
    get_file();
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
    char access_type[MAXSIZE];
    void *address;
    int size;
    char buf[MAXSIZE];
    /* so we need to read a character, a hex number, and a decimal number */
    while(fgets(buf,MAXSIZE,filename)!=NULL)
    {
        sscanf(buf,"%s %p,%d",access_type,&address,&size);
        if(*access_type=='L')
        {
            do_L(address,size);
        }
        else if(*access_type=='S')
        {
            do_S(address,size);
        }
        else if(*access_type=='M')
        {
            do_M(address,size);
        }
    }


    fclose(filename);
}

void do_init()
{
    int S=(1<<s);
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
    int S=(1<<s);
    for(int inS=0;inS<S;++inS)
    {
        free(oneSet[inS].valid);
        free(oneSet[inS].tag);
        free(oneSet[inS].time_stamp);
    }
    free(oneSet);
}


void do_L(void* address,int size)
{
    int set=getset(address);
    //get the set of cache
    struct cache* cache_hit=&oneSet[set];
    int empty_item=0;
    int last_item=0;
    int last_time=cache_hit->time_stamp[0];
    int full=1;
    //search for E
    int index=0;
    for(index=0;index<E;++index)
    {
        //find
        if(cache_hit->valid[index]==1 && cache_hit->tag[index]==gettag(address))
        {
            //++clocktime
            cache_hit->time_stamp[index]=(++clocktime);
            break;
        }
        //empty item
        else if(cache_hit->valid[index]==0)
        {
            full=0;
            empty_item=index;
        }
        // full
        else
        {
            if(cache_hit->time_stamp[index]<last_time)
            {
                last_item=index;
                last_time=cache_hit->time_stamp[index];
            }
        }
    }

    // miss
    if(index==E)
    {
        miss++;
        //evict
        if(full)
        {
            eviction++;
            cache_hit->time_stamp[last_item]=(++clocktime);
            cache_hit->tag[last_item]=gettag(address);
        }
        else
        {
            cache_hit->time_stamp[empty_item]=(++clocktime);
            cache_hit->tag[empty_item]=gettag(address);
            cache_hit->valid[empty_item]=1;
        }
    }
    else    //hit
    {
        hit++;
    }

}


//the difference between S and M is that S only load when miss,while M always load
//first then store
void do_S(void* address,int size)
{
    int set=getset(address);
    struct cache* cache_hit=&oneSet[set];
    // find the correct line
    int index=0;
    for(index=0;index<E;++index)
    {
        if(cache_hit->valid[index]==1 && cache_hit->tag[index]==gettag(address))
        {
            cache_hit->time_stamp[index]=(++clocktime);
            break;
        }
    }
    //miss
    if(index==E)
    {
        //do_L
        do_L(address,size);
    }
    else
    {
        hit++;
    }
}


void do_M(void* address,int size)
{

    do_L(address,size);
    do_S(address,size);
}



//get the set number from the address
int getset(void* addr)
{
    return (int)(((long)addr >>b) & ((1<<s)-1)  );
}


//get the tag number from the address
long gettag(void* addr)
{
    return (long)((long)addr >>(s+b));
}

