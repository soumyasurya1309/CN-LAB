#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 50

void sender(int frames[], int size, int win_size);
void receiver(int frames[], int start, int size, int win_size);

int main() {
    int n, win_size;
    int frames[MAX_FRAMES];

    printf("Sliding Window Protocol Simulation (Go-Back-N)\n");
    printf("Enter number of frames to send (max %d): ", MAX_FRAMES);
    scanf("%d", &n);
    if (n > MAX_FRAMES || n <= 0) {
        printf("Invalid number of frames\n");
        return 0;
    }
    printf("Enter window size: ");
    scanf("%d", &win_size);
    if (win_size <= 0 || win_size > n) {
        printf("Invalid window size\n");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        frames[i] = i;
    }
    sender(frames, n, win_size);
    return 0;
}

void sender(int frames[], int size, int win_size) {
    int base = 0;
    int next_seq = 0;
    char choice;
    srand(time(NULL));

    while (base < size) {
        printf("\nSender window: ");
        for (int i = base; i < base + win_size && i < size; i++) {
            printf("[%d] ", frames[i]);
        }
        printf("\nSending frames...\n");

        for (int i = base; i < base + win_size && i < size; i++) {
            printf("Sent frame: %d\n", frames[i]);
        }
        printf("Simulating receiver...\n");
        receiver(frames, base, size, win_size);

        printf("\nDid all frames receiver correctly? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            base += win_size;
        } else {
            printf("Resending from frame %d...\n", frames[base]);
        }
    }
    printf("\nAll frames sent!\n");
}

void receiver(int frames[], int start, int size, int win_size) {
    printf("Receiver received: ");
    for (int i = start; i < start + win_size && i < size; i++) {
        printf("[%d] ", frames[i]);
    }
    printf("\n");
}
