#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *mask_str, *ip_str;
    int mask[4], ip[4], i;
    unsigned char and_mask[4], or_mask[4], network[4], broadcast[4];

    if (argc < 3) {
        printf("Usage: %s mask ip\n", argv[0]);
        return 1;
    }

    mask_str = argv[1];
    ip_str = argv[2];

    // Parse mask string into integer array
    sscanf(mask_str, "%d.%d.%d.%d", &mask[0], &mask[1], &mask[2], &mask[3]);

    // Parse IP string into integer array
    sscanf(ip_str, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);

    // Calculate bitwise AND mask and OR mask
    for (i = 0; i < 4; i++) {
        and_mask[i] = (unsigned char) (ip[i] & mask[i]);
        or_mask[i] = (unsigned char) (ip[i] | (~mask[i] & 0xFF));
    }

    // Calculate network address
    for (i = 0; i < 4; i++) {
        network[i] = and_mask[i];
    }

    // Calculate broadcast address
    for (i = 0; i < 4; i++) {
        broadcast[i] = or_mask[i];
    }

    // Print results
    printf("Network Address: %d.%d.%d.%d\n", network[0], network[1], network[2], network[3]);
    printf("Broadcast Address: %d.%d.%d.%d\n", broadcast[0], broadcast[1], broadcast[2], broadcast[3]);
    printf("Usable IP Address Range: %d.%d.%d.%d - %d.%d.%d.%d\n", 
        and_mask[0], and_mask[1], and_mask[2], and_mask[3] + 1, 
        or_mask[0], or_mask[1], or_mask[2], or_mask[3] - 1);

    return 0;
}
