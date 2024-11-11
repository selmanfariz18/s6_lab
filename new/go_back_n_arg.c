#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){
    int nf, N;
    int tr=0;
    srand(time(NULL));

    printf("Enter the no. of frames:");
    scanf("%d", &nf);
    printf("Enter window size:");
    scanf("%d", &N);
    printf("\n");

    int i=1;
    while(i<=nf){
        int x=0;
        for(int j=i; j<i+N && j<=nf; j++){
            printf("Sent frames:%d\n", j);
            tr++;
        }
        for(int j=i; j<i+N && j<=nf; j++){
            int flag = rand()%2;

            if(flag){
                printf("%d: Acknowledged\n", j);
                x++;
            }
            else{
                printf("Frame %d not received\n", j);
                printf("Retransmitting...\n");
                break;
            }
        }
        printf("\n");
        i=i+x;
    }
    printf("Total no. of transmission: %d\n", tr);
    return 0;
}