# Quadtree-Project
Quadtree implementation is as follows: 

1. Add exactly four children to the node
2. The bounding rectangles for each child comprise exactly 1⁄4 of the original bounding rectangle. That is, the range
on both x and y are split exactly in half, giving us four identically sized sub-regions in space
3. The points stored in the parent node are distributed amongst the children according to their location in space
4. The parent node’s point array is empty and will no longer be used to store points



