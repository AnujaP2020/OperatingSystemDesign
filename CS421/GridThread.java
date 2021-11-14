package com.oshomeworks;

class GridThread extends Thread{
    // 3by3 grid checking
    private int rows;
    private int columns;
    private int[][] input;
    GridThread (int columns, int[][] input){
        this.rows = rows;
        this.columns = columns;
        this.input = input;
    }
    public void run(){
        int count = 0;
        SubGrid myThreads[] = new SubGrid[rows];
        int start = 0;
        for(int i=0; i< columns; i= i+3){
            for(int j=0; j< columns; j= j+3){

                myThreads[start].start();
                start++;
            }
        }
    }
}
