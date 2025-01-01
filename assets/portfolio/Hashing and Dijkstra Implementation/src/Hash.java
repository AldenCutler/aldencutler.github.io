import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.*;

public class Hash {

    static int m;
    static int C;

    static String[] hashTable;
    static Set<String> duplicates;
    static Map<Integer, Integer> freq;
    static Map<String, Integer> dist;

    public static void main(String[] args) {
        
        Scanner scanner = new Scanner(System.in);
        InputStream file;
        
        duplicates = new HashSet<>();

        // Maps to keep track of frequency and distance from hash value
        freq = new HashMap<>();
        dist = new HashMap<>();

        
        
        try {

            // Ask user if they want to choose input file and size of table
            System.out.print("Would you like to choose the input file and size of table? (y/n): ");
            String input = scanner.nextLine();
    
            if (input.equals("y")) {
                System.out.print("Enter the name of the input file (you don't have to list the full path, just make sure the file is in the current folder): ");
                String fileName = scanner.nextLine();
    
                file = Hash.class.getResourceAsStream("/" + fileName);
    
                System.out.print("Enter the size of the hash table: ");
                m = scanner.nextInt();
    
                System.out.print("Enter the value of C: ");
                C = scanner.nextInt();
            } else {
                // Default values
                m = 997;
                C = 123;
                file = Hash.class.getResourceAsStream("/DeclarationOfIndependence.txt");
            }
            scanner.close();

            //----------------------------------------------------------------------------------

            // Initialize hash table
            hashTable = new String[m];
            Arrays.fill(hashTable, "");

            assert file != null;        // to make analyzer happy
            BufferedReader reader = new BufferedReader(new InputStreamReader(file));

            String line;
            while ((line = reader.readLine()) != null) {

                // use regex to split line into words (ignoring punctuation and whitespace)
                String[] words = line.split("[^a-zA-Z'-]+");

                for (String word : words) {
                    // skip empty strings and duplicates
                    if (!word.isEmpty() && !duplicates.contains(word)) {
                        duplicates.add(word);

                        int hashValue = hash(word);
                        int index = hashValue % m;
                        
                        // Linear probing if collision occurs
                        while (!hashTable[index].isEmpty() && !hashTable[index].equals(word)) {
                            index = (index + 1) % m;    // wrap around to beginning of table if necessary
                        }

                        // If the index is empty, place the word there
                        if (hashTable[index].isEmpty()) {
                            hashTable[index] = word;

                            // Update frequency and distance maps
                            freq.put(hashValue, freq.getOrDefault(hashValue, 0) + 1);
                            int distance = Math.abs(index - hashValue % m);
                            dist.put(word, distance);
                        }
                    }
                }
            }

            reader.close();

        } catch (Exception e) {
            e.printStackTrace();
        }


        // Print out hash table
        System.out.println("Address\t\tWord\t\tHash value");
        for (int i = 0; i < m; i++) {
            String word = hashTable[i];
            int hashValue = hash(word);
            if (hashValue == 0) hashValue = -1;

            System.out.printf("%-6.6s %-20.20s %-20.20s\n", i, word, hashValue);
        }

        // Print out statistics
        int nonEmptyAddresses = nonEmptyAddresses();
        double loadFactor = (double) nonEmptyAddresses / m;

        System.out.println("\nNumber of non-empty addresses: " + nonEmptyAddresses);
        System.out.printf("Load factor: %6.6s\n", loadFactor);          // rounded to 4 decimal places (6 total characters including 0.)
        System.out.println("Longest empty area: " + longestEmptyChain());
        System.out.println("Longest chain: " + longestChain()[0] + ", starting at index: " + longestChain()[1]);
        System.out.println("Hash value with most distinct words: " + mostDistinctWords()[0] + ", number of distinct words that hash to this value: " + mostDistinctWords()[1]);
        System.out.println("Word farthest from its hash value: " + farthestFromHash() + ", distance: " + farthestDistance());
        
    }


    /**
     * Calculates the hash value of a word
     * @param word the word to be hashed
     * @return the hash value of the word
     */
    private static int hash(String word) {
        int h = 0;
        int s = word.length();

        for (int i = 0; i < s; i++) {
            char ci = word.charAt(i);
            h = (h * C + (int) ci) % m;
        }

        return h;
    }

    /**
     * Calculates the number of non-empty addresses in the hash table
     * @return the number of non-empty addresses
     */
    private static int nonEmptyAddresses() {
        int count = 0;
        for (String s : hashTable) {
            if (!s.isEmpty()) count++;
        }
        return count;
    }

    /**
     * Calculates the longest chain of empty addresses
     * @return the length of this chain
     */
    private static int longestEmptyChain() {
        int longestEmptyChain = 0;
        int currentEmptyChain = 0;
        for (String s : hashTable) {
            if (s.isEmpty()) {
                currentEmptyChain++;
            } else {
                longestEmptyChain = Math.max(longestEmptyChain, currentEmptyChain);
                currentEmptyChain = 0;
            }
        }
        return longestEmptyChain;
    }

    /**
     * Calculates the hash value resulting from the most distinct words
     * @return the hash value as well as the number of distinct words with that hash value
     */
    private static int[] mostDistinctWords() {
        int hashWithMostDistinctWords = -1;
        int maxDistinctWords = 0;
        for (Map.Entry<Integer, Integer> entry : freq.entrySet()) {
            int currentDistinctWords = entry.getValue();
            if (currentDistinctWords > maxDistinctWords) {
                maxDistinctWords = currentDistinctWords;
                hashWithMostDistinctWords = entry.getKey();
            }
        }
        return new int[] {hashWithMostDistinctWords, maxDistinctWords};
    }

    /**
     * Finds the word placed farthest from its actual hash value
     * @return the word farthest from its actual hash value
     */
    private static String farthestFromHash() {

        String farthestWord = "";

        try {
            farthestWord = Collections.max(dist.entrySet(), Map.Entry.comparingByValue()).getKey();
        } catch (NoSuchElementException e) {
            System.out.println("There is no element farther from its hash value than 0.");
        }

        return farthestWord;
    }

    /**
     * Finds the distance of the word farthest from its actual hash value
     * @return the distance of the word farthest from its actual hash value
     */
    private static int farthestDistance() {
        return dist.getOrDefault(farthestFromHash(), -1);
    }

    /**
     * Finds the longest chain of words in the hash table
     * @return the length of the longest chain as well as the index of the first word in the chain
     */
    private static int[] longestChain() {
        int longestChainSize = 0;
        int longestChainStart = 0;
        int currentChainSize = 0;
        int currentChainStart = 0;

        for (int i = 0; i < m; i++) {
            String word = hashTable[i];
            if (!word.isEmpty()) {
                currentChainSize++;
            } else {
                if (currentChainSize > longestChainSize) {
                    longestChainSize = currentChainSize;
                    longestChainStart = currentChainStart;
                }
                currentChainStart = i + 1;
                currentChainSize = 0;
            }

        }

        return new int[] {longestChainSize, longestChainStart};
    }
    
}