#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
//冒泡排序
void bubbleSort(vector<int> &v){
    int n=v.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(v[j]>v[j+1]) swap(v[j], v[j+1]);
        }
    }
}
//优化的冒泡b排序
void enhanceBubbleSort(vector<int> &v){
    int n=v.size();
    for(int i=0;i<n-1;i++){
        bool isSort=false;
        for(int j=0;j<n-1-i;j++){
            if(v[j]>v[j+1]){
                isSort = true;
                swap(v[j], v[j+1]);
            }
        }
        if(!isSort) break;
    }
}

//选择排序
void selectSort(vector<int> &v){
    int n=v.size();
    for(int i=0;i<n-1;i++){
        int minIdx=i;
        for(int j=i+1;j<n;j++){
            if(v[j]<v[minIdx]) minIdx=j;
        }
        swap(v[minIdx], v[i]);
    }
}

// 简单插入排序
void insertionSort(vector<int> &v){
    int n=v.size();
    for(int i=1;i<n;i++){
        int j, val=v[i];
        for(j=i-1;j>=0 && v[j]>val;j--){
            v[j+1] = v[j];
        }
        v[j+1] = val;
    }
}
//希尔排序
void shellSort(vector<int> &v){
    int n=v.size();
    for(int step=n/2;step>0;step--){
        for(int i=step;i<n;i++){
            int j, val=v[i];
            for(j=i-step; j>=0 && v[j]>val; j-=step){
                v[j+step] = v[j];
            }
            v[j+step] = val;
        }
    }
}

//归并排序
void mergeSortRecursive(vector<int> &a, vector<int> &b, int begin, int end){
    if(begin>=end) return;
    int m=begin+(end-begin)/2;
    mergeSortRecursive(a, b, begin, m);
    mergeSortRecursive(a, b, m+1, end);
    int i=begin, j=m+1;
    int idx=begin;
    while(i<=m && j<=end){
        b[idx++] = a[i]<a[j]?a[i++]:a[j++];
    }
    while(i<=m) b[idx++]=a[i++];
    while(j<=end) b[idx++]=a[j++];
    for(int k=begin;k<=end;k++) a[k]=b[k];
    
}
void mergeSort(vector<int> &v){
    int n=v.size();
    vector<int> v_tmp(n);
    mergeSortRecursive(v, v_tmp, 0, n-1);
}

//快速排序
int partition(vector<int> &v, int begin, int end){
    int pivolt=v[begin];
    int mark=begin;
    for(int i=begin+1;i<=end;i++){
        if(v[i]<pivolt){
            mark++;
            swap(v[mark], v[i]);
        }
    }
    v[begin] = v[mark];
    v[mark] = pivolt;
    return mark;
}
void quickSortRecursive(vector<int> &v, int begin, int end){
    if(begin>=end) return;
    int pivoltIdx=partition(v, begin, end);
    quickSortRecursive(v, begin, pivoltIdx-1);
    quickSortRecursive(v, pivoltIdx+1, end);
}

void quickSort(vector<int> &v){
    int n=v.size();
    quickSortRecursive(v, 0, n-1);
}

//堆排序
//完全二叉树，不断下沉的方式
void updateHeap(vector<int> &v, int i, int n){
    int maxIdx=i;
    int L=2*i+1, R=2*i+2;
    if(L<n && v[maxIdx]<v[L]){
        maxIdx=L;
    }
    if(R<n && v[maxIdx]<v[R]){
        maxIdx=R;
    }
    if(maxIdx!=i){
        swap(v[i], v[maxIdx]);
        updateHeap(v, maxIdx, n);
    }
}

void heapSort(vector<int> &v){
    int n=v.size();
    for(int i=(n-1)/2; i>=0; i--){
        updateHeap(v, i, n);
    }
    
    for(int j=n-1;j>0;j--){
        swap(v[0], v[j]);
        n--;
        updateHeap(v, 0, n);
    }
}

//基数排序
void radixSort(vector<int> &v){
    int n=v.size();
    int max_v=v[0];
    for(int i=1;i<n;i++){
        if(v[i]>max_v) max_v=v[i];
    }
    vector<vector<int>> bucket(10);
    int location=1;
    while(true){
        int tmp=pow(10, location-1);
        if(tmp>max_v) break;
        for(int i=0;i<n;i++){
            int k=(v[i]/tmp)%10;
            bucket[k].push_back(v[i]);
        }
        int idx=0;
        for(int i=0;i<10;i++){
            int size=bucket[i].size();
            for(int j=0;j<size;j++){
                v[idx++] = bucket[i][j];
            }
        }
        location++;
        for(int i=0;i<10;i++) bucket[i].clear();
    }
}

//计数排序
void countSort(vector<int> &v){
    int n=v.size();
    int max_v=v[0];
    for(int i=1;i<n;i++){
        if(max_v<v[i]) max_v=v[i];
    }
    vector<int> counter(max_v+1, 0);
    for(int i=0;i<n;i++){
        counter[v[i]]++;
    }
    int idx=0;
    for(int i=0;i<=max_v;i++){
        for(int j=0;j<counter[i];j++){
            v[idx++]=i;
        }
    }
}
// 桶排序
void bucketSort(vector<int> &v){
    int n=v.size();
    int min_v=v[0], max_v=v[0];
    for(int i=1;i<n;i++){
        if(v[i]<min_v) min_v=v[i];
        if(v[i]>max_v) max_v=v[i];
    }
    int diff=max_v-min_v;
    vector<vector<int>> bucket(n+1);
    float section=(float)diff/(float)n;
    for(int i=0;i<n;i++){
        int idx=int((v[i]-min_v)/section);
        bucket[idx].push_back(v[i]);
    }
    for(int i=0;i<n+1;i++){
        sort(bucket[i].begin(), bucket[i].end());
    }
    int idx=0;
    for(int i=0;i<n+1;i++){
        int size=bucket[i].size();
        for(int j=0;j<size;j++){
            v[idx++] = bucket[i][j];
        }
    }
}

int main(){
    vector<int> v={1,8,3,7,3,8,10,18};
    bucketSort(v);
   
    for(auto a: v){
        cout<<a<<" ";
    }
    cout<<endl;
    return 0;
}
