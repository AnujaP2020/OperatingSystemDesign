package com.oshomeworks;

import java.util.Arrays;

public class Sudoku {
    private int rows;
    private int columns;
    private int[][] input;
    private int[] output;

    Sudoku(){

    }

    Sudoku(int rows, int columns, int[][] input){
        this.rows = rows;
        this.columns = columns;
        this.input = input;
        this.output = new int[11];
    }

    @Override
    public String toString() {
        return "Sudoku{" +
                "rows=" + rows +
                ", columns=" + columns +
                ", input=" + Arrays.deepToString(input) +
                '}';
    }

    public boolean validateSudoku() {


        RowThread rowThread = new RowThread(rows, columns, input, output, 0);
        ColumnThread columnThread = new ColumnThread(rows, columns, input, output, 1);
        rowThread.start();
        columnThread.start();

        int start = 0;
        Thread[] myThreads = new SubGrid[rows];
        for(int i=0; i< rows; i= i+3){
            for(int j=0; j< rows; j= j+3){
                myThreads[start] = new SubGrid(i,j, input, output, start + 2);
                myThreads[start].start();
                start++;
            }
        }

        try {
            rowThread.join();
        } catch(Exception ex){
            System.out.println("Exception has been caught in rowThread" + ex);
        }

        try {
            columnThread.join();
        } catch(Exception ex){
            System.out.println("Exception has been caught in columnThread" + ex);
        }

        for (int threadIndex = 0; threadIndex < rows; threadIndex++){
            try {
                myThreads[threadIndex].join();
            } catch(Exception ex){
                System.out.println("Exception has been caught in threadIndex: " + threadIndex + ". Exception:" + ex);
            }
        }

        System.out.println("---- Output array ----" + Arrays.toString(output));
        // checking if all elements are 1 or not
        for (int j : output) {
            if (j == 0) {
                return false;
            }
        }
        return true;
    }
}
