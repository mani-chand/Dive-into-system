#include <stdio.h>

int arr_sum(int arr[],int n){
    int sum = 0;
    for(int i = 0; i < n;i++){
        sum += arr[i];
    }
    return sum;
}

  int arr_max(int arr[], int n) {
      int max = arr[0];
      for(int i = 1;i<n;i++){
        if(max<arr[i]){
            max = arr[i];
        }
      }
      return max;
  }



int main(){
    int nums[5] = {10, 20, 30, 40, 50};
    printf("%d\n",nums[0]);
    printf("%d\n",nums[4]);
    nums[2] = 99;
    printf("sum of array nums is %d\n",arr_sum(nums,5));
    printf("max = %d\n", arr_max(nums, 5));
}