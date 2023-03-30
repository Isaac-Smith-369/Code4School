int binarySearch(int target) {
  int arr[5] = {1, 2, 3, 4, 5};

  int start = arr[0];
  int end = arr[4];

  while (start <= end) {
    int mid = start + (end - start) / 2;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] < target) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }
  }

  return -1;
}