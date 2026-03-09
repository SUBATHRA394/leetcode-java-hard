import java.util.*;

class Solution {
    public List<Integer> findSubstring(String s, String[] words) {
        List<Integer> result = new ArrayList<>();
        if (s == null || s.length() == 0 || words == null || words.length == 0) return result;
        
        int wordLen = words[0].length();
        int numWords = words.length;
        int totalLen = wordLen * numWords;
        
        Map<String, Integer> wordCount = new HashMap<>();
        for (String word : words) {
            wordCount.put(word, wordCount.getOrDefault(word, 0) + 1);
        }
        
        for (int i = 0; i < wordLen; i++) {
            int left = i, count = 0;
            Map<String, Integer> seen = new HashMap<>();
            
            for (int j = i; j + wordLen <= s.length(); j += wordLen) {
                String word = s.substring(j, j + wordLen);
                
                if (wordCount.containsKey(word)) {
                    seen.put(word, seen.getOrDefault(word, 0) + 1);
                    count++;
                    
                    // If seen more than expected, move left pointer
                    while (seen.get(word) > wordCount.get(word)) {
                        String leftWord = s.substring(left, left + wordLen);
                        seen.put(leftWord, seen.get(leftWord) - 1);
                        left += wordLen;
                        count--;
                    }
                    
                    // If window contains all words
                    if (count == numWords) {
                        result.add(left);
                    }
                } else {
                    // Reset window
                    seen.clear();
                    count = 0;
                    left = j + wordLen;
                }
            }
        }
        
        return result;
    }
}
