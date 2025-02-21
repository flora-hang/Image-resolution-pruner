#Image Resolution Pruner
- The pruner takes a image and coverts it into a Image tree (using linked list structure) of RBP pixel object 
- When given a resolution parameter, it will reduce the resolution of the current piction linked-list
 to a lower resolution through taking the average of colors in an area
- example (before):![Alt text](images-orig/kkkk-kmnn-960x540.png)
- example (after): ![Alt text](images-output/kkkk-kmnn-960x540-prune-pct85-tol002-r1.png)
