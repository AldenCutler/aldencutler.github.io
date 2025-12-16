public class MostPreciousPath {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String GREEN_BOLD = "\033[1;32m";

    static int[][] mostPreciousPath(int[][] grid) {
        int n = grid.length;
        int[][] path = new int[n][2]; // to store the i, j coordinates of the path
        int gems = 0;

        // for every square in the bottom row, find the most precious path that starts at that square
        for (int i = 0; i < n; i++) {
            int[][] tempPath = mostPreciousPathHelper(grid, i);
            int tempGems = getGemsFromPath(grid, tempPath);
            if (tempGems > gems) {
                gems = tempGems;
                path = tempPath;
            }
        }

        return path;
    }


    /**
     * Given an n x n grid of squares, each containing a number of gems,
     * find the most precious path from any square in the bottom row
     * to the top row.
     * @param grid a 2D array of integers representing the number of gems in each square
     * @return an array of integers representing the path of the most precious path
     */
    static int[][] mostPreciousPathHelper(int[][] grid, int startCol) {

        int[][] path = new int[grid.length][2]; // to store the i, j coordinates of the path
        int n = grid.length;

        // initialize the path to start at the bottom row
        path[0][0] = n-1;
        path[0][1] = startCol;

        // find most precious square in the row above the previous square
        for (int i = 1; i < n; i++) {
            int prevRow = path[i-1][0];
            int prevCol = path[i-1][1];

            switch (prevCol) {

                // if our previous square was in the leftmost column, we can only move up-right or up
                // so we need to check which of those two squares has the most gems
                case 0 -> {
                    if (grid[prevRow - 1][prevCol] > grid[prevRow - 1][prevCol + 1]) {
                        path[i][0] = prevRow - 1;
                        path[i][1] = prevCol;
                    } else {
                        path[i][0] = prevRow - 1;
                        path[i][1] = prevCol + 1;
                    }
                }

                // if our previous square was in the rightmost column, we can only move up-left or up
                // 7 is the index of the rightmost column. I tried to use grid.length-1, but I was getting an error saying that case expressions must be constant expressions
                case 7 -> {
                    if (grid[prevRow - 1][prevCol] > grid[prevRow - 1][prevCol - 1]) {
                        path[i][0] = prevRow - 1;
                        path[i][1] = prevCol;
                    } else {
                        path[i][0] = prevRow - 1;
                        path[i][1] = prevCol - 1;
                    }
                }

                // otherwise, we can move up-left, up-right, or up
                default -> {
                    if (grid[prevRow - 1][prevCol] > grid[prevRow - 1][prevCol - 1]
                            && grid[prevRow - 1][prevCol] > grid[prevRow - 1][prevCol + 1]) {     // if up is the most precious square
                        path[i][0] = prevRow - 1;
                        path[i][1] = prevCol;
                    } else if (grid[prevRow - 1][prevCol - 1] > grid[prevRow - 1][prevCol]
                            && grid[prevRow - 1][prevCol - 1] > grid[prevRow - 1][prevCol + 1]) {   // if up-left is the most precious square
                        path[i][0] = prevRow - 1;
                        path[i][1] = prevCol - 1;
                    } else {                                                                  // if up-right is the most precious square
                        path[i][0] = prevRow - 1;
                        path[i][1] = prevCol + 1;
                    }
                }
            }
        }

        return path;
    }


    /**
     * Returns the number of gems collected from a path
     * @param grid the grid of gems
     * @param path the path to be evaluated
     * @return the number of gems collected from the path
     */
    static int getGemsFromPath(int[][] grid, int[][] path) {
        int gems = 0;
        for (int[] square : path) {
            gems += grid[square[0]][square[1]];
        }
        return gems;
    }


    /**
     * Prints the path to the console
     * @param path the path to be printed
     * @param grid the grid of gems
     */
    static void printPath(int[][] path, int[][] grid) {
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid.length; j++) {

                boolean inPath = false;
                for (int[] square : path) {
                    if (square[0] == i && square[1] == j) {
                        inPath = true;
                        break;
                    }
                }

                if (inPath) {
                    System.out.print(GREEN_BOLD + grid[i][j] + ANSI_RESET + "\t");
                } else {
                    System.out.print(grid[i][j] + "\t");
                }
            }

            System.out.println();
        }
    }


    public static void main(String[] args) {

        System.out.println("\nTo see the color-coded path, please run this program in a terminal that supports ANSI escape codes, such in IntelliJ or from the console (if you run it using the VSCode Java extension it won't work).");

        int[][] grid = {
                {35, 89, 52, 66, 82, 20, 95, 21},
                {79, 5, 14, 23, 78, 37, 40, 74},
                {32, 59, 17, 25, 31, 4, 16, 63},
                {91, 11, 77, 48, 13, 71, 92, 15},
                {56, 70, 47, 64, 22, 88, 67, 12},
                {83, 97, 94, 27, 65, 51, 30, 7},
                {10, 41, 1, 86, 46, 24, 53, 93},
                {96, 33, 44, 98, 75, 68, 99, 84},
        };

        int[][] bestPath = mostPreciousPath(grid);
        int maxGems = getGemsFromPath(grid, bestPath);


        System.out.println("\nBilbo's starting square is: Row 1, Column " + (bestPath[0][1]+1));

        System.out.println("Bilbo collected " + maxGems + " gems.\n");

        System.out.println("Bilbo's path is: \n");
        printPath(bestPath, grid);

        System.out.println("\nThe Arkenstone is in vault " + (bestPath[bestPath.length-1][1]+1) + ".\n");

    }
}
