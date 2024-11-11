#include<stdio.h>
#include<stdlib.h>

int main(){
    int window_size;
    int frame_size;
    printf("Enter window size:");
    scanf("%d", &window_size);
    printf("Enter no. of frame:");
    scanf("%d", &frame_size);

    int nt=0, k=0;
    int left[10]={-1};
    int i;
    for(i=1; i<=frame_size; i++){
        int flag = rand()%2;

        if(flag){
            printf("Frame[%d] Acknowledged\n", i);
            nt++;
        }
        else{
            printf("Frame[%d] not Acknowledged\n", i);
            left[k++]=i;
            nt++;
        }

        if(i%window_size == 0){
            for(int x=0; x<k; x++){
                printf("Frame[%d] retransmitted\n", left[x]);
                printf("Frame[%d] acknowledged on 2nd attempt\n", left[x]);
                nt++;
            }
            k=0;
        }
    }
    for(i=0; i<k; i++){
        printf("Frame[%d] retransmitted\n", left[i]);
        printf("Frame[%d] acknowledged on 2nd attempt\n", left[i]);
        nt++;
    }
    printf("Total transmissions: %d\n", nt);
}