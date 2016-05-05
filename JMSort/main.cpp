//
//  main.cpp
//  JMSort
//
//  Created by jm on 16/5/5.
//  Copyright © 2016年 raozhizhen. All rights reserved.
//

#include <iostream>

//JMSort 平均时间复杂度O(n^2) 额外空间复杂度O(1)
void JMSort(long array[], long length){
    long i;
    //循环N次，每次找到一个最大数。
    for (i = 0; i < length; i++) {
        //间隔多少个元素进行比较
        long interval = 1;
        long left, right;
        long end = length - i - 1;
//        long whileNumber = 0;
        while (interval <= end) {
            left = 0;
            right = left + interval;
//            long whileNumber2 = 0;
            while (right <= end) {
//                whileNumber2 ++;
                if (array[left] < array[right])
                    std::swap(array[left], array[right]);
                left += interval << 1;
                right = left + interval;
            }
//            printf("floors:%ld---%ld\n", interval, whileNumber2);
            if (left <= end)
                if (array[left] > array[0])
                    std::swap(array[left], array[0]);
            interval <<= 1;
//            whileNumber ++;
        }
//        printf("%ld\n", whileNumber);
        std::swap(array[0], array[end]);
    }
}

//堆排序  平均时间复杂度O(nlogn) 额外空间复杂度O(1)
void maxHeap(long array[], long start, long end) {
    long dad = start;
    long son = dad * 2 + 1;
    while (son < end) {
        //比较两个子节点的大小。
        if (son + 1 < end && array[son] < array[son + 1])
            son++;
        //如果父节点大于子节点，直接返回。
        if (array[dad] > array[son])
            return;
        //如果父节点小于子节点，交换父子节点，因为子节点变了，所以子节点可能比孙节点小，需继续
        //比较。
        std::swap(array[dad], array[son]);
        dad = son;
        son = dad * 2 + 1;
    }
}

void heapSort(long array[], long length) {
    long i;
    //i从最后一个父节点开始调整
    for (i = length / 2 - 1; i >= 0; i--) {
        //形成最大堆，第一个元素为最大数。
        maxHeap(array, i, length);
    }
    //将第一个元素放置到最后，再将前面的元素重新调整，得到最大堆，将此时最大的数放置到倒数第二
    //位置，如此反复。
    for (long i = length - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        maxHeap(array, 0, i);
    }
}

void printfArray(long array[], long length) {
    if (array != NULL) {
        for (long i = 0; i < length; i++) {
            printf("%ld\t", array[i]);
        }
        printf("\n");
    }
}

//测试
void Test(long array[], long length) {
    long array1[length], array2[length];
    double start;
    double end;
    
    memcpy(array1, array, length * sizeof(long));
    start = clock();
    heapSort(array1, length);
    end = clock();
    std::cout << "堆排序: " << (end - start)/CLOCKS_PER_SEC << "秒" << std::endl;

    memcpy(array2, array, length * sizeof(long));
    start = clock();
    JMSort(array2, length);
    end = clock();
    std::cout << "臻排序: " << (end - start)/CLOCKS_PER_SEC << "秒" << std::endl;
    long i;
    for (i = 0; i < length; i++) {
        if (array2[i] != array1[i]) {
            printf("错误\n");
            printfArray(array1, length);
            printfArray(array2, length);
            return;
        }
    }
    printf("通过\n");
}

//测试随机数组排序
void Test3() {
    long maxLength = 100;
    long array[maxLength];
    for (long i = 0; i < maxLength; ++i) {
        array[i] = rand()%(maxLength * 10);
    }
    printf("Test3:%ld条数据\n", maxLength);
    Test(array, maxLength);
}

//测试空数组排序
void Test2() {
    long array[0];
    long length = sizeof(array) / sizeof(long);
    printf("Test2:\n");
    printfArray(array, length);
    Test(array, length);
}

//测试固定数组排序
void Test1() {
    long array[] = {22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70};
    long length = sizeof(array) / sizeof(long);
    printf("Test1:\n");
    printfArray(array, length);
    Test(array, length);
}

int main(int argc, const char * argv[]) {
//      Test1();
//    Test2();
    Test3();
    return 0;
    return 0;
}
