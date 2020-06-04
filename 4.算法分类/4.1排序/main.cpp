#include<iostream>
#include<vector>
using namespace std;

void bubbleSort(vector<int> &v){
    int n=v.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(v[j]>v[j+1]) swap(v[j], v[j+1]);
        }
    }
}

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

int main(){
    vector<int> v={1,5,3,9,6,100,3,22,44};
    enhanceBubbleSort(v);
    
    for(auto a: v){
        cout<<a<<" ";
    }
    cout<<endl;
    return 0;
}
