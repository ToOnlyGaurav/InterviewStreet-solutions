#include <stdio.h>
#define ARR_SIZE 6250

int main() {
    unsigned short A[ARR_SIZE], B[ARR_SIZE], C[ARR_SIZE+1], 
        value, transfer = 0;
    
    int j = 0, k = 0, i = 0, n, q, pos, len, bit;
    char cmd[32], ch;
    
    scanf("%d %d\n", &n, &q);
    
    len = n >> 4;
    j = n % 16;
    if (j) len++;
    k = j == 0 ? 15 : j - 1;
    i = 0;
    while ((ch = getchar()) != '\n') {
        value |= (ch - 48) << k;
        k--;
        if (k == -1) {
            A[len - i - 1] = value;
            k = 15;
            value = 0;
            i++;
        }
    }
    A[len - i - 1] = value;
    
    i = 0;
    k = j == 0 ? 15 : j - 1;
    while ((ch = getchar()) != '\n') {
        value |= (ch - 48) << k;
        k--;
        if (k == -1) {
            B[len - i - 1] = value;
            k = 15;
            value = 0;
            i++;
        }
    }
    B[len - i - 1] = value;
    
    while(q--) {
        gets(cmd);
        if (cmd[4] == 'a') {
            sscanf(cmd, "set_a %d %d", &pos, &bit);
            j = pos >> 4;
            k = 1 << (pos % 16);
            A[j] = bit ? A[j] | k : A[j] & (~k);
        } else if (cmd[4] == 'b') {
            sscanf(cmd, "set_b %d %d", &pos, &bit);
            j = pos >> 4;
            k = 1 << (pos % 16);
            B[j] = bit ? B[j] | k : B[j] & (~k);
        } else {
            sscanf(cmd, "get_c %d", &pos);
            j = pos >> 4;
            k = pos % 16;
            transfer = 0;
            for (i = 0; i <= j; i++) {
                value = A[i] + B[i] + transfer;
                C[i] = value & 0xffff;
                transfer = value >> 16;
            }
            
            printf("%d", (C[j] & (1 << k)) >> k);
        }
    }
    
    return 0;
}