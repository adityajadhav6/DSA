#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 2048

typedef struct {
    int key;
    int value;
} HashItem;

int hash(int key) {
    return abs(key) % HASH_SIZE;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashItem* hashTable[HASH_SIZE] = {NULL};

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int h = hash(complement);

        // Search for complement
        while (hashTable[h] != NULL) {
            if (hashTable[h]->key == complement) {
                int* result = (int*)malloc(2 * sizeof(int));
                result[0] = hashTable[h]->value;
                result[1] = i;
                *returnSize = 2;

                // Free allocated hash table
                for (int j = 0; j < HASH_SIZE; j++)
                    if (hashTable[j]) free(hashTable[j]);
                return result;
            }
            h = (h + 1) % HASH_SIZE; // Linear probing
        }

        // Insert current number
        int h2 = hash(nums[i]);
        while (hashTable[h2] != NULL) {
            h2 = (h2 + 1) % HASH_SIZE;
        }
        hashTable[h2] = (HashItem*)malloc(sizeof(HashItem));
        hashTable[h2]->key = nums[i];
        hashTable[h2]->value = i;
    }

    *returnSize = 0;
    return NULL; // Should never reach here if solution guaranteed
}

int main() {
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int returnSize;
    int* result = twoSum(nums, 4, target, &returnSize);

    if (result != NULL) {
        printf("Indices: %d, %d\n", result[0], result[1]);
        free(result);
    } else {
        printf("No solution found.\n");
    }
    return 0;
}
