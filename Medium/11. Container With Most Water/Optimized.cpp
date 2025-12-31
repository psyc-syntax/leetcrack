/*
================================================================================
LEETCODE 11: CONTAINER WITH MOST WATER – TWO POINTER APPROACH
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- You are given an array "height", where each value is the height of a vertical line on the x-axis.
- Choose TWO lines that, together with the x-axis, form a container.
- The container holds water up to the shorter of the two lines.
- Goal: Find the MAXIMUM area (water) that can be stored between any two lines.

Example:
- height = [1,8,6,2,5,4,8,3,7]
- One best choice: lines at index 1 (height 8) and index 8 (height 7)
  width = 8 - 1 = 7
  min height = 7
  area = 7 * 7 = 49 (maximum)

REAL-LIFE FEEL:
- Think of vertical sticks on the ground.
- Pour water between two sticks; water level is limited by the shorter stick.
- You want two sticks that form the BIGGEST bucket.

RULES:
- You can pick any two indices i and j (i < j).
- Area = (j - i) * min(height[i], height[j]).
- Return the maximum area among all possible pairs.


TWO POINTER APPROACH (This Code):
1. Use TWO pointers:
   - i  → start from LEFT (0)
   - j  → start from RIGHT (heightSize - 1)
2. At each step:
   - Compute width = j - i.
   - Find minheight = minimum of height[i], height[j].
   - area = width * minheight.
   - Update maxheight (max area) if this area is bigger.
3. Move the pointer pointing to the SHORTER line:
   - If height[i] < height[j] → move i++ (try to find a taller line from left).
   - Else → move j-- (try to find a taller line from right).
4. Stop when i and j meet.
5. maxheight is the answer.

WHY MOVE THE SHORTER LINE?
- Area is limited by the SHORTER height.
- Moving the taller line inward will only reduce width, but height limit stays the same or worse.
- Moving the shorter line gives a chance to find a taller height and possibly a bigger area.


TIME & SPACE COMPLEXITY:
- TIME: O(n) because each pointer moves at most from one end to the other (no nested loops).
- SPACE: O(1) because only a few variables are used (no extra arrays).


================================================================================
YOUR CODE WITH SIMPLE ENGLISH COMMENTS
================================================================================
*/

int maxArea(int* height, int heightSize) {
    int maxheight = 0;   // This stores the maximum area found so far
    int minheight;       // To store the smaller of the two heights each time
    int i = 0;           // Left pointer (start of array)
    int j = heightSize - 1; // Right pointer (end of array)

    // Continue while left index is strictly less than right index
    while (i < j)
    {
        int comparision = 0;  // This will store the area for current pair (i, j)

        // Find the shorter line between height[i] and height[j]
        if (height[i] < height[j])
            minheight = height[i];
        else
            minheight = height[j];

        // Area formula: width * min height
        // width = j - i
        comparision = (j - i) * minheight;

        // Update maximum area if current area is larger
        if (comparision > maxheight)
        {
            maxheight = comparision;
        }

        // Move the pointer that points to the shorter line
        // This may help find a taller line and a bigger area
        if (height[i] < height[j])
            i++;    // move left pointer to the right
        else
            j--;    // move right pointer to the left
    }

    // After checking all possible pairs using two pointers, return max area found
    return maxheight;
}

/*
SUMMARY:
- Start with widest container (ends of array).
- Always move the pointer at the shorter line.
- Check area at each step and keep the maximum.
- Time: O(n), Space: O(1).
*/
