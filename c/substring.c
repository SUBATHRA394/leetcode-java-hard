#include <stdlib.h>
#include <string.h>

// Helper to compare words for qsort and bsearch
int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    int sLen = strlen(s);
    int wordLen = strlen(words[0]);
    int totalLen = wordsSize * wordLen;
    *returnSize = 0;
    if (sLen < totalLen) return NULL;

    int* res = malloc(sizeof(int) * sLen);
    
    // 1. Sort words so we can use binary search to count frequencies
    qsort(words, wordsSize, sizeof(char*), compareStrings);

    // 2. Track original frequencies
    int* targetCount = calloc(wordsSize, sizeof(int));
    int uniqueWords = 0;
    for (int i = 0; i < wordsSize; i++) {
        if (i > 0 && strcmp(words[i], words[i-1]) == 0) {
            targetCount[uniqueWords-1]++;
        } else {
            words[uniqueWords] = words[i];
            targetCount[uniqueWords++] = 1;
        }
    }

    // 3. Sliding Window
    for (int i = 0; i <= sLen - totalLen; i++) {
        int* currentCount = calloc(uniqueWords, sizeof(int));
        int j = 0;
        for (; j < wordsSize; j++) {
            char sub[31]; // Max word length is 30
            strncpy(sub, s + i + j * wordLen, wordLen);
            sub[wordLen] = '\0';
            
            // Binary search to find if 'sub' is in our words list
            char* pSub = sub;
            char** found = bsearch(&pSub, words, uniqueWords, sizeof(char*), compareStrings);
            
            if (!found) break;
            
            int idx = found - words;
            currentCount[idx]++;
            if (currentCount[idx] > targetCount[idx]) break;
        }
        
        if (j == wordsSize) {
            res[(*returnSize)++] = i;
        }
        free(currentCount);
    }
    
    free(targetCount);
    return res;
}
