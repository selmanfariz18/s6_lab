#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct frame{
    int info;
    int seq;
};

int ak, k, t=5, disconnect=0, errorframe=1, errorrack=1;
char turn='s';
struct frame p;

void sender(){
    static int flag=0;
    if(turn == 's'){
        if(errorrack == 0){
            printf("SENDER: Sent packet with seq NO:%d\n", p.seq);
            errorframe = rand()%4;
            if(errorframe==0){
                printf("Error while sending packet!\n");
            }
            turn='r';
        }
        else{
            if(flag==1){
                printf("SENDER: Received ACK for packet %d\n",ak);
            }
            if(p.seq==5){
                disconnect=1;
                return;
            }
            p.info=p.info+1;
            p.seq=p.seq+1;

            printf("SENDER:Sent packet with seq NO:%d\n", p.seq);
            errorframe = rand()%4;
            if(errorframe==0){
                printf("Error while sending packet!\n");
            }
            turn='r';
            flag=1;
        }
    }
    else{
        t--;
        printf("SENDER time reducing\n");
        if(t==0){
            turn='s';
            errorrack=0;
            t=5;
        }
    }
}

void receiver(){
    static int frexp = 1;
    if(turn == 'r'){
        if(errorframe!=0){
            if(p.seq == frexp){
                printf("RECEIVER: Received packet with seq %d\n", p.seq);
                ak=p.seq;
                frexp++;
                turn='s';
                errorrack = rand()%4;
                if(errorrack == 0){
                    printf("Error while sending ACK\n");
                }
            }
            else{
                printf("RECEIVER: Duplicated packet with seq %d\n", frexp-1);
                ak = frexp - 1;
                turn='s';
                errorrack = rand()%4;
                if(errorrack == 0){
                    printf("Error while sending ACK\n");
                }
            }
        }
    }
}

int main(){
    srand(time(NULL));
    p.info=0;
    p.seq=0;
    while(!disconnect){
        sender();
        for(k=1;k<=10000000; k++);
        receiver();
    }
    return 0;
}
