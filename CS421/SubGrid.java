package com.oshomeworks;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

class SubGrid extends Thread{
    // subgrid class
    private int rows;
    private int columns;
    private int[][] input;
    private int[] output;
    private int index;
    SubGrid (int rows, int columns, int[][] input, int[] output, int index){
        this.rows = rows;
        this.columns = columns;
        this.input = input;
        this.output = output;
        this.index = index;
    }

    @Override
    public String toString() {
        return " SubGrid{" +
                "rows=" + rows +
                ", columns=" + columns +
                ", output=" + Arrays.toString(output) +
                ", index=" + index +
                '}';
    }

    public void run(){
        System.out.println("Running thread: "+ Thread.currentThread().getName());
        Set<Integer> set = new HashSet<>();
        output[this.index] = 1;

        for (int i=rows; i< rows+3; i++){
            for(int j=columns; j< columns+3; j++){
                if(!(set.add(input[i][j]))){
                    output[this.index] = 0;
                    break;
                }
                else if (input[i][j] > 9 || input[i][j] <1 ){
                    System.out.println("Invalid entry");
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

