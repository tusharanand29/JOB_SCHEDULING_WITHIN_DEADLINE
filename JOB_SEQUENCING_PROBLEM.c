 #include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int job_no;
    float profit;
    int  dead_line;
}node;

void heapify(node arr[] , int n , int p)  /// HEAPIFY FUNCTION
{
    int gt=p;
    int lc = 2*p+1;
    int rc = 2*p+2;
    if(lc<n && arr[lc].profit<arr[gt].profit)
        gt=lc;
    if(rc<n && arr[rc].profit<arr[gt].profit)
        gt=rc;
    if(gt!=p)
    {
        node temp = arr[p];
        arr[p] = arr[gt];
        arr[gt] = temp;
        heapify(arr,n,gt);
    }
}

void heap_sort(node arr[] , int n)  /// HEAP SORT
{
    int i;
    for(i=(n+1)/2;i>=0;i--)
    {
        heapify(arr,n,i);
    }
    int cs=n;
    while(cs>1)
    {
        node temp = arr[0];
        arr[0] = arr[cs-1];
        arr[cs-1] = temp;
        cs--;
        heapify(arr,cs,0);
    }
}

void JOB_SEQUENCING(node *arr,int n,int *slot_array,int max_deadline , float *total_profit)  /// JOB SEQUENCING WITHIN A DEADLINE
{
    int i=0,j;
    for(i=0;i<n;i++)
    {
        int temp = arr[i].dead_line;
        for(j=temp-1;j>=0;j--)
        {
            if(slot_array[j]==0)
            {
                slot_array[j] = arr[i].job_no;
                *total_profit+=arr[i].profit;
                break;
            }
        }
    }
}

int main()
{
    int n,i;
    printf("---------------------------------WELCOME TO THE JOB SCHEDULING PROGRAM---------------------------------\n");
    printf("---------------------------------ENTER THE NUMBER OF JOBS YOU WANT TO SCHEDULE-------------------------\n");
    scanf("%d",&n);
    node * arr = (node*)malloc(n*sizeof(node));
    printf("---------------------------------ENTER THE JOBS WITH THEIR PROFIT AND DEADLINE-------------------------\n");
    for(i=0;i<n;i++)
    {
        printf("JOB : %d ",i+1);
        printf("\nENTER PROFIT : ");
        scanf("%f",&arr[i].profit);
        printf("ENTER DEADLINE : ");
        scanf("%d",&arr[i].dead_line);
        arr[i].job_no = i+1;
    }
    int max_deadline = 0;
    for(i=0;i<n;i++)
    {
        if(arr[i].dead_line>max_deadline)
        {
            max_deadline = arr[i].dead_line;
        }
    }

    int * slot_array = (int*)calloc(max_deadline,sizeof(int));

    heap_sort(arr,n); /// SORTING THE JOBS ACCORDING TO THEIR MAXIMUM PROFIT

    float total_profit = 0;

    JOB_SEQUENCING(arr,n,slot_array,max_deadline,&total_profit);

    printf("--JOB SCHEDULED SLOT--\n");
    for(i=0;i<max_deadline;i++)
    {
        printf("--SLOT NUMBER : %d JOB NUMBER ASSIGNED : %d\n",i+1,slot_array[i]);
    }
    printf("---TOTAL PROFIT EARNED: %f---\n",total_profit);
    printf("------------------------------------------------THANK YOU :) ------------------------------------------\n");
    return 0;

}
