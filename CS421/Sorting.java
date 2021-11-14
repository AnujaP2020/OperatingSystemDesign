package com.oshomeworks;

import java.util.Arrays;

public class Sorting {

    Sorting(){

    }

    public int[] sortMethod(int[] input){

        // get the array and divide into the halves
        int division = input.length/2;
        int[] firsthalf = new int[division];
        int[] secondhalf = new int[input.length- division];
        for (int i=0; i< division; i++){
            firsthalf[i] = input[i];
        }
        int start = 0;
        for (int i=division; i< input.length; i++){
            secondhalf[start] = input[i];
            start++;
        }
        System.out.println(Arrays.toString(firsthalf));
        System.out.println(Arrays.toString(secondhalf));

        // initialize output sorted array
        int[] sortedArray = new int[input.length];

        // create sand start thread1
        FirstThread firstThread = new FirstThread(firsthalf);
        firstThread.start();

        // create sand start thread2
        SecondThread secondThread = new SecondThread(secondhalf);
        secondThread.start();

        try {
            firstThread.join();
        } catch(Exception ex){
            System.out.println("Exception has been caught in firstThread" + ex);
        }

        try {
            secondThread.join();
        } catch(Exception ex){
            System.out.println("Exception has been caught in secondThread" + ex);
        }

//        // after finishing task of above two threads then only we will move for sorting thread operation
        SortingThread sortingThread = new SortingThread(firsthalf, secondhalf, sortedArray);
        sortingThread.start();
        try {
            sortingThread.join();
        } catch(Exception ex){
            System.out.println("Exception has been caught in sortingThread" + ex);
        }

        return sortedArray;
    }
}
