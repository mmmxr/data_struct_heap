#include <stdio.h>
#include "heap.h"
#define TEST_HEADER printf("\n================%s=============\n",__FUNCTION__);

int Greater(char x,char y)
{
    return x>y?1:0;
}
int Less(char x,char y)
{
    return x>y?0:1;
}
void HeapInit(Heap* heap, Compare cmp)
{
    if(heap==NULL)
    {
        return;
    }
    heap->cmp=cmp;
    heap->size=0;
}
void HeapDestroy(Heap* heap)
{
    if(heap==NULL)
    {
        return;
    }
    heap->size=0;
    heap->cmp=NULL;
}
void Swap(HeapType* x,HeapType* y)
{
    HeapType tmp=*x;
    *x=*y;
    *y=tmp;
}
void HeapInsert(Heap* heap, HeapType to_insert)
{
    if(heap==NULL)
    {
        return;
    }
    
    if(heap->size>=HEAPMAX)
    {
        return;
    }
    heap->data[heap->size++]=to_insert;
    size_t child=heap->size-1;
    size_t parent=(child-1)/2;
    while(child>=0&&child<heap->size&&parent>=0&&parent<heap->size)
    {
        if(heap->data[child]>heap->data[parent])
        {
            Swap(&heap->data[child],&heap->data[parent]);
            child=parent;
            parent=(child-1)/2;
        }
        else
        {
            break;
        }
    }
}
int HeapRoot(Heap* heap, HeapType* root)
{
    if(heap==NULL)
    {
        return 0;
    }
    if(heap->size==0)
    {
        return 0;
    }
    *root=heap->data[0];
    return 1;
}
void HeapErase(Heap* heap)
{
    if(heap==NULL)
    {
        return;
    }
    if(heap->size==0)
    {
        return;
    }
    Swap(&heap->data[0],&heap->data[heap->size-1]);
    --heap->size;
    size_t parent=0;
    size_t child=parent*2+1;
    while(child>=0&&child<heap->size&&parent>=0&&parent<heap->size)
    {
        if(child+1<heap->size)
        {
            if(!heap->cmp(heap->data[child],heap->data[child+1]))
            {
                child=child+1;
            }
        }
        if(heap->data[child]>heap->data[parent])
        {
            Swap(&heap->data[child],&heap->data[parent]);
            parent=child;
            child=parent*2+1;
        }
        else
        {
            break;
        }
    }
}
void HeapCreat(Heap* heap, HeapType array[], size_t size)
{
    if(heap==NULL||array==NULL||size==0)
    {
        return;
    }
    size_t i=0;
    for(i=0;i<size;i++)
    {
        HeapInsert(heap,array[i]);
    }
}
void HeapSort(HeapType array[], size_t size)
{
    if(array==NULL||size==0)
    {
        return;
    }
    Heap heap;
    HeapInit(&heap,Greater);
    HeapCreat(&heap,array,size);
    size_t i=0;
    for(i=0;i<size;i++)
    {
        HeapErase(&heap);
    }
    heap.size=size;
    for(i=0;i<size;i++)
    {
        array[i]=heap.data[i];
    }
}
/////////////////////////////////////////////
//测试函数
////////////////////////////////////////////
void TestInit()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    printf("size expect 0,actual %lu\n",heap.size);
}
void HeapPrintChar(Heap* heap,const char* msg)
{
    printf("%s\n",msg);
    size_t i=0;
    for(i=0;i<heap->size;i++)
    {
        printf("%c ",heap->data[i]);
    }
    printf("\n");
}
void TestInsert()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'d');
    HeapPrintChar(&heap,"插入六个元素");

}
void TestRoot()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'d');
    HeapPrintChar(&heap,"插入六个元素");
    HeapType value;
    HeapRoot(&heap,&value);
    printf("root expect f,actual %c\n",value);
}
void TestErase()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'d');
    HeapPrintChar(&heap,"插入六个元素");
    HeapErase(&heap);
    HeapErase(&heap);
    HeapPrintChar(&heap,"删除两个元素");
}
void TestCreat()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapType array[]={'a','b','c','d','e','f'};
    size_t size=sizeof(array)/sizeof(array[0]);
    HeapCreat(&heap,array,size);
    HeapPrintChar(&heap,"创建一个堆");

}
void TestHeapSort()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapType array[]={'e','b','a','d','c','f'};
    size_t size=sizeof(array)/sizeof(array[0]);
    HeapSort(array,size);
    printf("%s\n",array);
    
}
int main()
{
    TestInit();
    TestInsert();
    TestRoot();
    TestErase();
    TestCreat();
    TestHeapSort();
    return 0;
}

