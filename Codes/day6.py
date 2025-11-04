from collections import deque
from typing import List

def max_path_sum_bfs(nums: List[List[int]]) -> int:
    if not nums:
        raise ValueError("Triangle must have at least one row.")
    
    result = float('-inf') # to store the maximum path sum
    
    q = deque() # (row, col, path sum so far)
    q.append((0, 0, nums[0][0]))

    while q:
        i, j, p_sum = q.popleft()
        # When we reach the last row then compare path sums.
        if i == len(nums) - 1:
            result = max(result, p_sum)
        else: # add adjacent elements to the queue with updated path sum
            q.append((i+1, j, p_sum + nums[i+1][j]))
            q.append((i+1, j+1, p_sum + nums[i+1][j+1]))
    
    return result

# In-place bottom-up dp
def max_path_sum_inplace(nums: List[List[int]]) -> int:
    if not nums:
        raise ValueError("Triangle must have at least one row.")

    for i in range(len(nums) - 2, -1, -1):
        curr_row = nums[i]
        next_row = nums[i+1]
        for j in range(len(curr_row)):
            curr_row[j] += max(next_row[j], next_row[j+1])
    
    return nums[0][0]

# Functional style (concise)
def max_path_sum_compact(nums: List[List[int]]) -> int:
    if not nums:
        raise ValueError("Triangle must have at least one row.")
    
    prev = nums[-1].copy()
    for row in nums[-2::-1]:
        prev = [a + max(prev[i], prev[i+1]) for i, a in enumerate(row)]

    return prev[0]


triangle = [
    [75],
    [95, 64],
    [17, 47, 82],
    [18, 35, 87, 10],
    [20, 4, 82, 47, 65],
    [19, 1, 23, 75, 3, 34],
    [88, 2, 77, 73, 7, 63, 67],
    [99, 65, 4, 28, 6, 16, 70, 92],
    [41, 41, 26, 56, 83, 40, 80, 70, 33],
    [41, 48, 72, 33, 47, 32, 37, 16, 94, 29],
    [53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14],
    [70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57],
    [91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48],
    [63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31],
    [4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23],
]

print(max_path_sum_inplace(triangle))
