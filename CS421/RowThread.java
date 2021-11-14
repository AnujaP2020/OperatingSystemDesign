package com.oshomeworks;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

class RowThread extends Thread{
    // rowwise checking
    private int rows;
    private int columns;
    private int[][] input;
    private int[] output;
    private int index;

    RowThread (int rows, int columns, int[][] input, int[] output, int index){
        this.rows = rows;
        this.columns = columns;
        this.input = input;
        this.output = output;
        this.index = index;
    }

    @Override
    public String toString() {
        return "RowThread{" +
                "rows=" + rows +
                ", columns=" + columns +
                ", input=" + Arrays.toString(input) +
                ", output=" + Arrays.toString(output) +
                ", index=" + index +
                '}';
    }

    public void run(){
        System.out.println("running thread: "+ Thread.currentThread().getName());
        output[this.index] = 1;

        for(int i=0; i< rows; i++){
            Set<Integer> set = new HashSet<>();
            for (int j=0; j< columns; j++){
                if(!(set.add(input[i][j]))){
                    System.out.println("Duplicate number");
                    output[this.index] = 0;
                    break;
                }
                else if (input[i][j] > 9 || input[i][j] <1 ){
                    System.out.println("Invalid number");
                    output[this.index] = 0;
                    break;
                }
            }
            if (output[this.index] == 0){
                break;
            }
        }

    }
}
