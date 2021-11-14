package com.oshomeworks;

public class SudokuValidator {

    public static void main(String[] args) {

        // test case 1 : valid sudoku
        int[][] matrix1 =
                {{1, 4, 5, 3, 2, 7, 6, 9, 8},
                        {8, 3, 9, 6, 5, 4, 1, 2, 7},
                        {6, 7, 2, 9, 1, 8, 5, 4, 3},
                        {4, 9, 6, 1, 8, 5, 3, 7, 2},
                        {2, 1, 8, 4, 7, 3, 9, 5, 6},
                        {7, 5, 3, 2, 9, 6, 4, 8, 1},
                        {3, 6, 7, 5, 4, 2, 8, 1, 9},
                        {9, 8, 4, 7, 6, 1, 2, 3, 5},
                        {5, 2, 1, 8, 3, 9, 7, 6, 4},};

        // test case 2 : invalid sudoku
        int[][] matrix2 =
                {{1, 4, 5, 3, 2, 7, 6, 9, 8},
                {8, 3, 9, 6, 5, 4, 1, 2, 7},
                {6, 7, 2, 9, 1, 8, 5, 4, 3},
                {4, 9, 6, 1, 8, 50, 3, 7, 2},
                {2, 1, 8, 4, 7, 3, 9, 5, 6},
                {7, 5, 3, 2, 90, 6, 4, 8, 1},
                {3, 6, 7, 5, 4, 2, 8, 1, 9},
                {9, 8, 4, 7, 6, 1, 2, 3, 5},
                {5, 2, 1, 8, 3, 9, 7, 6, 4},};

        int rows = 9;
        int cols = 9;


        Sudoku sudoku = new Sudoku(rows, cols, matrix1);
        System.out.println(sudoku.toString());
        System.out.println(sudoku.validateSudoku());

        Sudoku sudoku2 = new Sudoku(rows, cols, matrix2);
        System.out.println(sudoku2.toString());
        System.out.println(sudoku2.validateSudoku());



    }
}
