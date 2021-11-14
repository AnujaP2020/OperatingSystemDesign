package com.oshomeworks;

import java.util.Arrays;

public class FirstThread extends Thread{
    private int[] firstHalf;

    FirstThread(int[] firstHalf){
        this.firstHalf = firstHalf;
    }

    public void run(){
        for(int i=0; i< firstHalf.length; i++){
            int min = firstHalf[i];
            int index = i;
            for (int j=i+1; j< firstHalf.length; j++){
                if (min> firstHalf[j]){
                    min = firstHalf[j];
                    index = j;
                }
            }
            int var = firstHalf[i];
            firstHalf[i] = firstHalf[index];
            firstHalf[index] = var;
        }
        System.out.println("Running thread: "+ Thread.currentThread().getName());
        System.out.println("sorted firstArray :" + Arrays.toString(firstHalf));       ;
    }
}
