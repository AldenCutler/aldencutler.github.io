public class GaussJordanElimination {

    /**
     * Prints a matrix to the console
     * 
     * @param matrix the matrix to be printed
     */
    static void printMatrix(double[][] matrix) {
        for (double[] row : matrix) {
            for (double element : row) {
                System.out.printf("%-6.30s", element);
            }
            System.out.println();
        }
    }
    // "%-6.30s

    /**
     * Performs Gauss-Jordan elimination on a system of linear equations
     * @param matrix the matrix of coefficients
     */
    static void gaussJordanElimination(double[][] matrix) {
        int n = matrix.length;

        for (int i = 0; i < n; i++) {

            // if the pivot element is zero, swap rows
            if (matrix[i][i] == 0) {
                int pivotRow = 1;

                // find a row to swap with
                // (such a row must exist if the system has a unique solution, which is assumed)
                while ((i + pivotRow) < n && matrix[i + pivotRow][i] == 0) {
                    pivotRow++;
                }

                // swap rows if the pivot element is zero
                for (int k = 0; k <= n; k++) {
                    double temp = matrix[i][k];
                    matrix[i][k] = matrix[i + pivotRow][k];
                    matrix[i + pivotRow][k] = temp;
                }
            }

            // j and k are the row and column indices, so this zeroing-out process is done
            // over the entire matrix
            for (int j = 0; j < n; j++) {
                if (i != j) { // excluding i == j because we don't want to zero out the pivot element
                    double temp = matrix[j][i] / matrix[i][i];
                    //
                    for (int k = 0; k <= n; k++) {
                        matrix[j][k] = matrix[j][k] - (matrix[i][k]) * temp;
                    }
                }
            }
        }

        // convert diagonal matrix to reduced row echelon form
        for (int i = 0; i < n; i++) {
            matrix[i][n] = (int) (matrix[i][n] / matrix[i][i]);
            matrix[i][i] = 1;
        }

    }

    public static void main(String[] args) {

        double[][] matrix = {
                { 1, 1, 1, 1, 1, 1, 1, 1, 1, 122 },
                { 1, 1, 1, 1, 1, -1, -1, -1, -1, -88 },
                { 1, -1, 1, -1, 1, -1, 1, -1, 1, 32 },
                { 1, 1, 0, 0, 0, 0, 0, 0, 0, 3 },
                { 0, 0, 1, 1, 0, 0, 0, 0, 0, 7 },
                { 0, 0, 0, 0, 1, 1, 0, 0, 0, 18 },
                { 0, 0, 0, 0, 0, 0, 0, 1, 1, 76 },
                { 9, -8, 7, -6, 5, -4, 3, -2, 1, 41 },
                { 1, 1, -1, 1, 1, -1, 1, 1, -1, 0 }
        };

        gaussJordanElimination(matrix);

        System.out.println("\nFinal augmented matrix is: ");

        printMatrix(matrix);

        System.out.println("\nSolutions are: ");
        for (int i = 0; i < matrix.length; i++) {
            System.out.println("x" + (i + 1) + " = " + (int) matrix[i][matrix.length]);
        }
    }

}
