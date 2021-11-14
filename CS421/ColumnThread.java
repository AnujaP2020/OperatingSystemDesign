package com.oshomeworks;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

class ColumnThread extends Thread{
    // columnwise checking
    private int rows;
    private int columns;
    private int[][] input;
    private int[] output;
    private int index;

    ColumnThread (int rows, int columns, int[][] input, int[] output, int index){
        this.rows = rows;
        this.columns = columns;
        this.input = input;
        this.output = output;
        this.index = index;
    }
    public void run(){
        System.out.println("running thread: "+ Thread.currentThread().getName());
        output[this.index] = 1;

        for (int j=0; j< columns; j++){
            Set<Integer> set = new HashSet<>();
            for(int i=0; i< rows; i++){

                if(!(set.add(input[j][i]))){
                    System.out.println("Duplicate number");
                    output[this.index] = 0;
                    break;
                }
                else if (input[j][i] > 9 || input[j][i] <1 ){
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
