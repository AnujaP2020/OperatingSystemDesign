package com.oshomeworks;

import java.util.Arrays;

public class SortingThread extends Thread {
    private int[] firstArray;
    private int[] secondArray;
    private int[] sortedArray;

    SortingThread(int[] firstArray, int[] secondArray, int[] sortedArray) {
        this.firstArray = firstArray;
        this.secondArray = secondArray;
        this.sortedArray = sortedArray;
    }

    public void run() {
        int position = 0;
        int index1 = 0;
        int index2 = 0;
        while ((index1 < firstArray.length) && (index2 < secondArray.length)) {
            if (firstArray[index1] < secondArray[index2]) {
                sortedArray[position] = firstArray[index1];
                index1++;
                position++;
            } else {
                sortedArray[position] = secondArray[index2];
                index2++;
                position++;
            }
        }
        while (index1 < firstArray.length){
            sortedArray[position++] = firstArray[index1++];
        }
        while (index2 < secondArray.length){
            sortedArray[position++] = secondArray[index2++];
        }

        System.out.println("Running thread: " + Thread.currentThread().getName());
        System.out.println("sorted final array: " + Arrays.toString(sortedArray));
        }
    }