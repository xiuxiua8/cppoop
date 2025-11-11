#include <stdio.h>
#include <stdlib.h>
#include <vector>

void indexedSequentialSearch(int arr[], int n, int k)
{
    constexpr int GROUP_SIZE = 3; // 每组元素数量
    const int numBlocks = (n + GROUP_SIZE - 1) / GROUP_SIZE;

    std::vector<int> elements(numBlocks);
    std::vector<int> indices(numBlocks);

    int ind = 0;
    for (int i = 0; i < n; i += GROUP_SIZE) {
        elements[ind] = arr[i];
        indices[ind] = i;
        ind++;
    }

    if (ind == 0 || k < elements[0]) {
        printf("Not found");
        return;
    }

    int start = 0, end = n - 1;
    bool set = false;
    for (int i = 1; i < ind; i++) {
        if (k <= elements[i]) {
            start = indices[i - 1];
            end = indices[i] - 1; // 上一块的末尾
            set = true;
            break;
        }
    }
    if (!set) {
        start = indices[ind - 1];
        end = n - 1; // 最后一块到数组末尾
    }

    for (int i = start; i <= end && i < n; i++) {
        if (k == arr[i]) {
            printf("Found at index %d", i);
            return;
        }
    }
    printf("Not found");
}

int main()
{
    int arr[] = { 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 8;
    indexedSequentialSearch(arr, n, k);
    return 0;
}