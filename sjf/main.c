//
//  main.c
//  Pre-Emptive Shortest Job First
//
//  Created by Aniket Mitra on 01/11/14.

#include<stdio.h>

typedef struct presjf
{
    int p_no,arriv_time,burst_time,finish_time;
    float TAT,WT;
}presjf;

presjf p[20],p1[20];

int main()
{
    int i,limit,nextval,m,min,n,j;
    int temp1,temp2,temp3;
    
    p[0].WT=p[0].TAT=0;
    printf("\nEnter the no of processes: ");
    scanf("%d",&n);
    printf("\n\n");
    
    for(i=1;i<=n;i++)
    {
        p[i].p_no = i;
        printf("Enter the arrival time for the process P%d: ",p[i].p_no);
        scanf("%d",&p[i].arriv_time);
        printf("Enter the burst time for the process P%d: ",p[i].p_no);
        scanf("%d",&p[i].burst_time);
    }
    
    for (i=1; i<=n; i++)
    {
        for (j=i+1; j<=n; j++)
        {
            if (p[i].arriv_time>p[j].arriv_time)
            {
                temp1 = p[i].arriv_time;
                p[i].arriv_time = p[j].arriv_time;
                p[j].arriv_time = temp1;
                temp2 = p[i].burst_time;
                p[i].burst_time = p[j].burst_time;
                p[j].burst_time = temp2;
                temp3 = p[i].p_no;
                p[i].p_no = p[j].p_no;
                p[j].p_no = temp3;
            }
        }
    }
    
    limit=p[1].arriv_time;           // start time
    
    for(i=1;i<=n;i++)
        limit+=p[i].burst_time;      // end time
    
    for(i=1;i<=n;i++)
        p1[i]=p[i];                  // process numbers
    
    printf("\n\nGantt chart is as follows: \n\n");
    printf("%d",p[1].arriv_time);    // printing arrival time first value
    nextval=p[1].arriv_time;
    m=1;
    
    do
    {
        min = 9999;
        for(i=1;p[i].arriv_time<=nextval && i<=n ;i++)
            if(p[i].burst_time<min && p[i].burst_time>0)
            {
                m=i;
                min=p[i].burst_time;
            }
        nextval+=1;                            //time_limit = 1 sec
        p[m].burst_time=p[m].burst_time-1;  //burst time reduction after 1s
        printf("->P%d->%d",p[m].p_no,nextval);
        
        if(p[m].burst_time==0)
        {
            p[m].finish_time=nextval;
            p[m].TAT=p[m].finish_time-p[m].arriv_time;
            p[m].WT=p[m].TAT-p1[m].burst_time;
            p[0].TAT+=p[m].TAT;                    //total TAT
            p[0].WT+=p[m].WT;                      //total WT
        }
    }while(nextval<limit);
    
    p[0].TAT=p[0].TAT/n;                   //average TAT
    p[0].WT=p[0].WT/n;                     //average WT
    
    printf("\n\n-------------------TABLE----------------------------------\n");
    printf("\nProcess\tAT\tBT\tFT\tWT\t\t\tTAT\n");
    for(i=1;i<=n;i++)
        printf("\nP%d\t\t%d\t%d\t%d\t%f\t%f\n",p[i].p_no,p[i].arriv_time,p1[i].burst_time,p[i].finish_time,p[i].WT,p[i].TAT);
    printf("\n\n-----------------------------------------------------------\n");
    printf("Average WT = %f\n",p[0].WT);
    printf("Average TAT = %f\n",p[0].TAT);
    printf("Average Execution Time = %f\n",(p[0].TAT-p[0].WT));
    return 0;
}
