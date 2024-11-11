#include<stdio.h>

#define BUCKET_SIZE 50

int main(){
    int bucket=0;
    int input, output;

    printf("Enter the input:");
    while(scanf("%d",&input) == 1 && input != 0){
        if(bucket < BUCKET_SIZE){
            bucket = bucket + input;
            printf("Input accepted: %d\n", input);
        }
        else{
            printf("Bucket full, leaking %d units..\n", input);
        }
        if (bucket > 0) {
            bucket--;
            printf("Leaked 1 unit\n");
        }
    }
    return 0;
}