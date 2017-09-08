/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{


    if(M==32)
    {
        int bsize=8;
        int ii,jj,i,j,a;
        for(ii=0;ii<N;ii+=bsize)
        {
            for(jj=0;jj<M;jj+=bsize)
            {
                for(i=ii;i<ii+bsize;++i)
                {
                    for(j=jj;j<jj+bsize;++j)
                    {
                        if(i!=j)
                            B[j][i]=A[i][j];

                    }

                    //Transpose of a square-matrix has a unique property; no need to move elements on the diagonal.

                    if(ii==jj)
                    {
                        //Misses in B reduced to m<i
                        a=A[i][i];
                        B[i][i]=a;
                    }
                }
            }
        }
        return;
    }



    if(M==64)
    {
        int interval=8;
        int gap=4;
        
        int startX,startY;

        for(startY=0;startY<M;startY+=interval)
        {
            for(startX=0;startX<N;startX+=interval)
            {
                //设定对应的nowX,nowY对应的开始的startY,startX相反
                int nowX=startY;
                int nowY=startX;

                //第一个区域块
                int nextX=nowX;
                int nextY=nowY;

                do{
                    nextY+=interval;
                    if(nextY>=N)
                    {
                        nextX+=interval;
                        nextY-=N;
                    }
                }while(nextY==startY);


                //第二个区域块
                int nextX_2=nextX;
                int nextY_2=nextY;

                do{
                    nextY_2+=interval;
                    if(nextY_2>=N)
                    {
                        nextX_2+=interval;
                        nextY_2-=N;
                    }
                }while(startY==nextY_2);

                //如果横坐标的区域块超过,则直接交换
                if(nextX>=M){
                    
                    for(int i=0;i<interval;++i)
                    {
                        for(int j=0;j<interval;++j)
                            {
                                B[nowX+j][nowY+i]=A[startX+i][startY+j];
                            }
                    }
                }
                //如果不是，则执行其中两块交换
                else
                {
                    //首先先把upper矩阵赋值到nextX块
                    for(int i=0;i<gap;++i)
                    {
                        for(int j=0;j<interval;++j)
                        {
                            B[nextX+i][nextY+j]=A[startX+i][startY+j];
                        }
                    }

                    //接下来赋值下一块
                    for(int i=0;i<gap;++i)
                    {
                        for(int j=0;j<interval;++j)
                        {
                            B[nextX_2+i][nextY_2+j]=A[startX+gap+i][startY+j];
                        }
                    }


                    //已经把在A中需要交换的数据全部拷贝到B中新的块中，接下来就只需要对B矩阵的8*8进行操作
                    //不用考虑会发生碰撞的情况

                    //交换左上和右上
                    for(int i=0;i<gap;++i)
                    {
                        for(int j=0;j<gap;++j)
                        {
                            B[nowX+j][nowY+i]=B[nextX+i][nextY+j];
                            B[nowX+j][nowY+gap+i]=B[nextX_2+i][nextY_2+j];
                        }
                    }

                    //交换左下和右下
                    for(int i=0;i<gap;++i)
                    {
                        for(int j=0;j<gap;++j)
                        {
                            B[nowX+gap+j][nowY+i]=B[nextX+i][nextY+gap+j];
                            B[nowX+gap+j][nowY+gap+i]=B[nextX_2+i][nextY_2+gap+j];
                        }
                    }

                }

            }
        }
        return ;
    }


    if(M==61)
    {
        int interval=16;
        for(int startX=0;startX<N;startX+=interval)
        {
            for(int startY=0;startY<M;startY+=interval)
            {
                for(int i=0;i<interval;++i)
                {
                    for(int j=0;j<interval;++j)
                    {
                        if(startX+i>=N || startY+j>=M) continue;
                        B[startY+j][startX+i]=A[startX+i][startY+j];
                    }
                }
            }
        }
        return;
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
 //   registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

