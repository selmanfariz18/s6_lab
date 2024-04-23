#include <stdio.h>
#include <stdlib.h>

int input(int a[], int frame_size) {
    printf("\n\n Input \n\n");
    for (int i = 1; i <= frame_size; i++) {
        printf(" Enter Value For Frame[%d] : ", i);
        scanf("%d", &a[i]);
        printf("\n");
    }
    printf("\n\n");
    return 1;
}

int display(int a[], int frame_size) {
    printf("\n\n Display \n\n");
    for (int i = 1; i <= frame_size; i++) {
        printf(" Frame[%d] : %d ", i, a[i]);
        // List all frames with sequence numbers
        printf("\n");
    }
    printf("\n\n");
    return 1;
}

int selective_repeat(int frames[], int window_size, int frame_size) {
    int nt = 0;
    int k = 0;

    int left[10] = {-1};
    int i;
    for (i = 1; i <= frame_size; i++) {
        int flag = rand() % 2;
        // Set frame to be dropped during transmission randomly
        if (flag) { // success
            printf("Frame[%d] with value %d Acknowledged!!!\n\n", i, frames[i]);
            nt++; // Increment nt when frame is acknowledged
        } else { // failure
            printf("Frame[%d] with value %d Not Acknowledged!!!\n\n", i, frames[i]);
            left[k++] = i; // Note frame number not acknowledged and store that frame number in left 1-D array
            nt++; // count retransmission
        }
        if (i % window_size == 0) { // Loop for retransmitting lost frame
            for (int x = 0; x < k; x++) {
                printf("Frame[%d] with value %d Retransmitted\n\n", left[x], frames[left[x]]);
                nt++; // increment nt for retransmitted frame
                printf("Frame[%d] with value %d Acknowledged on Second Attempt\n\n", left[x], frames[left[x]]);
            }
            k = 0;
        }
    }
    for (i = 0; i < k; i++) {
        printf("Frame[%d] with value %d Retransmitted\n\n", left[i], frames[left[i]]);
        // print retransmitted frame details
        nt++;
        printf("Frame[%d] with value %d Acknowledged on Second Attempt\n\n", left[i], frames[left[i]]);
    }
    printf("Total Transmissions: %d\n\n", nt);

    return 0;
}

int main() {
    int frames[50];
    int window_size;
    int frame_size;
    printf("\n\n Selective Repeat \n\n");
    printf("Enter Window Size: ");
    scanf("%d", &window_size);
    printf("Enter Number Of Frames To Be Transmitted: ");
    scanf("%d", &frame_size);

    input(frames, frame_size);
    display(frames, frame_size);
    selective_repeat(frames, window_size, frame_size);
    return 0;
}

