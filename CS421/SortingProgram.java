package com.oshomeworks;

import java.util.Arrays;

public class SortingProgram {

    public static void main(String[] args)  {

        Sorting sortingObject = new Sorting();
        int[] input = {2,5,8,90,42,64,89,32,1};

        System.out.println(Arrays.toString(sortingObject.sortMethod(input)));

    }
}
