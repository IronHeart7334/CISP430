package dataStructures.sorting;

import dataStructures.priorityQueue.Prioritizable;
import dataStructures.priorityQueue.PrioritizableInteger;
import java.util.Arrays;

/**
 *
 * @author Matt
 */
public class QuickSort {
    
    public QuickSort(){
        
    }
    
    /**
     * 
     * @param min inclusive
     * @param max exclusive
     * @return 
     */
    private int medianIdx(Prioritizable[] array, int min, int max){
        int mid = (min + max) / 2;
        int minVal = array[min].getPriority();
        int midVal = array[mid].getPriority();
        int maxVal = array[max - 1].getPriority();
        
        // todo median idx
        
        
        return mid;
    }
    
    private void swap(Prioritizable[] array, int a, int b){
        Prioritizable temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }
    
    /**
     * Sort the array in ascending order
     * @param array
     * @param min minimum index - inclusive
     * @param max maximum index - exclusive
     */
    private void quickSort(Prioritizable[] array, int min, int max) {
        if(min >= max){
            return;
        }
        // choose pivot. Can be any index within [min, max)
        int pivotIdx = medianIdx(array, min, max);
        Prioritizable pivot = array[pivotIdx];
        
        // move pivot to the end to make things easier
        swap(array, pivotIdx, max - 1);
        
        // partition values smaller than pivot to its left
        // partition values greater than pivot to its right
        int i = min;
        int j = max - 2; // left of pivot
        while(i < j){
            while(i < max - 2 && array[i].getPriority() <= pivot.getPriority()){
                i++;
            } // by now, i points to a problematic value
            while(j > min && array[j].getPriority() >= pivot.getPriority()){
                j--;
            } // by now, both i and j point to problematic values
            if(i < j){
                // a[i] is greater than pivot, a[j] is lesser, so swap them 
                swap(array, i, j);
                i++;
                j--;
            }
            // don't do else here
            if(i >= j){
                // array[i] is now greater than the pivot
                swap(array, max - 1, i);
                // pivot is now in its proper place
            }
        }          
        
        
        System.out.printf("Pivot %d Index %d is set: %s\n", pivot.getPriority(), i, Arrays.toString(array));
        
        System.out.printf("[%d, %d) U [%d,%d)\n", min, i, i + 1, max);
        // call quicksort on the left partition
        quickSort(array, min, i);
        // call quicksort on the right partition
        quickSort(array, i + 1, max);
    }
    
    public final void quickSort(Prioritizable[] array){
        quickSort(array, 0, array.length);
    }
    
    public static void main(String[] args){
        PrioritizableInteger[] unsorted = new PrioritizableInteger[10];
        int[] is = new int[]{9, 0, 1, 3, 4, 6, 8, 2, 5, 7};
        for(int i = 0; i < is.length; i++){
            unsorted[i] = new PrioritizableInteger(is[i]);
        }
        
        System.out.println(Arrays.toString(unsorted));
        new QuickSort().quickSort(unsorted);
        System.out.println(Arrays.toString(unsorted));
    }
}