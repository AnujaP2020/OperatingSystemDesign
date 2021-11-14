package com.oshomeworks;

import java.util.Arrays;

public class SecondThread extends Thread {
    private int[] secondHalf;

    SecondThread(int[] secondHalf) {
        this.secondHalf = secondHalf;
    }

    public void run() {
        for (int i = 0; i < secondHalf.length; i++) {
            int min = secondHalf[i];
            int index = i;
            for (int j = i + 1; j < secondHalf.length; j++) {
                if (min > secondHalf[j]) {
                    min = secondHalf[j];
                    index = j;
                }
            }
            int var = secondHalf[i];
            secondHalf[i] = secondHalf[index];
            secondHalf[index] = var;
        }
        System.out.println("Running thread: " + Thread.currentThread().getName());
        System.out.println("sorted secondArray: " + Arrays.toString(secondHalf));
    }
}
