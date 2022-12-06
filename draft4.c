#include <stdio.h>
#include <graphics.h>

#define BlockWidth 7
#define WidthCoeff 10
#define HeightCoeff 6
#define BaseDepth 450
#define StartDist 20

void changeColor(int x, int y, int color){
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    rectangle(x, y, x+BlockWidth, BaseDepth);
    floodfill(x+1, y+1, color);
}

void drawBlock(int x, int y){
    setcolor(13);
    setfillstyle(SOLID_FILL, 13);
    rectangle(x, y, x+BlockWidth, BaseDepth);
    floodfill(x+1, y+1, 13);
}

void removeBlock(int x, int y){
    setcolor(0);
    setfillstyle(SOLID_FILL, 0);
    rectangle(x, y, x+BlockWidth, BaseDepth);
    floodfill(x+1, y+1, 0);
}

void draw(int arr[], int size){
    int i, x, y;
    
    for(i = 0; i < size; i++){ //drawing complete array
        x = StartDist + (WidthCoeff * i);
        y = BaseDepth - (HeightCoeff * arr[i]);
        
        drawBlock(x, y);
    }
}

void selectionSort(int arr[], int size){
    int i, j, temp, minIndex;
    int x1, y1, x2, y2;
    
    for(i = 0; i < size-1; i++){
        minIndex = i;
        for(j = i+1; j < size; j++){ //Searching the minimum element
            
            changeColor(StartDist + (WidthCoeff * j), BaseDepth - (HeightCoeff * arr[j]), 9); //Coloring the search head (BLUE)
            if(j != i+1){
                changeColor(StartDist + (WidthCoeff * (j-1)), BaseDepth - (HeightCoeff * arr[j-1]), 13);
            }
            delay(10);
        
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        changeColor(StartDist + (WidthCoeff * (size-1)), BaseDepth - (HeightCoeff * arr[size-1]), 13); //Changing color of last block from (BLUE) to (PINK)
        
        x1 = StartDist + (WidthCoeff * i); //calculating coordinates of the new blocks
        y1 = BaseDepth - (HeightCoeff * arr[i]);
        x2 = StartDist + (WidthCoeff * minIndex);
        y2 = BaseDepth - (HeightCoeff * arr[minIndex]);
        
        removeBlock(x1, y1); //swapping blocks
        drawBlock(x1, y2);
        removeBlock(x2, y2);
        drawBlock(x2, y1);
        
        temp = arr[i]; //swapping values in array
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
        
        changeColor(x1, y2, 2); //Changing color of swapped block (GREEN)
        if(i != 0){
            changeColor(x1 - WidthCoeff, y2 + HeightCoeff, 13);
        }
        
        delay(50);
    }
    changeColor(x1, y2, 13); //Changing color of last block from (GREEN) to (PINK)
}

int main()
{
    int gd = DETECT, gm;
    int arr[60] = {51, 25, 48, 49, 56, 16, 2, 3, 23, 38, 34, 42, 30, 10, 58, 57, 44, 8, 24, 17, 21, 31, 28, 53, 13, 40, 22, 27, 60, 36, 46, 5, 50, 41, 1, 4, 18, 29, 45, 32, 35, 26, 33, 59, 7, 11, 15, 20, 39, 14, 12, 52, 54, 47, 43, 6, 9, 19, 37, 55};
    
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    
    draw(arr, 60);
    delay(1000);
    selectionSort(arr, 60);

    return 0;
}

/*
2, 27, 31, 16, 9, 6, 32, 1, 39, 24, 17, 33, 29, 8, 21, 34, 4, 40, 26, 14, 35, 7, 22, 30, 36, 12, 15, 10, 37, 28, 11, 13, 23, 20, 38, 3, 19, 25, 5, 18
*/