void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int firstMissingPositive(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        // Use a while loop to keep swapping until nums[i] is in the correct spot
        // or is out of the valid range [1, numsSize]
        while (nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[nums[i] - 1]) {
            swap(&nums[i], &nums[nums[i] - 1]);
        }
    }

    // Find the first index that doesn't match its value
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }

    // If all numbers 1 to n are present
    return numsSize + 1;
}
