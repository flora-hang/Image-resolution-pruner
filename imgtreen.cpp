/**
 *  @file imgtree.cpp
 *  @description implementation of a binary tree class storing image data for CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN
 */

#include "imgtree.h"
#include <cfloat>
// not necessary to include imgtree-private.h since it is already included in imgtree.h

/**
 *  Default constructor creates an empty tree
 */
ImgTree::ImgTree() {
    // complete your implementation below
    root = nullptr;
}

/**
 *  Parameterized constructor creates a tree from an input image.
 *  Every leaf in the tree corresponds to a single pixel in the PNG.
 *  Every non-leaf node corresponds to a rectangle of pixels defined
 *  by upper, left, lower, and right image coordinates. A node will
 *  also store the average color over its defined rectangle. Note that
 *  this average MUST be freshly computed from the individual pixels in
 *  the image and NOT by computing a weighted average from the colors
 *  of its direct children, as this would lead to an accumulation of
 *  rounding errors due to the integer nature of RGB color channels.
 *
 *  A non-leaf node's children correspond to a partition of the node's
 *  rectangle into two smaller rectangles, either by a horizontal line
 *  creating an upper rectangle and a lower rectangle, or a vertical line
 *  creating a left rectangle and a right rectangle.
 *
 *  The split is determined as follows:
 *  1. If the current node's rectangle width is the same or larger than its height,
 *     then a vertical line will divide the rectangle into left and right rectangles.
 *     If the current node's rectangle width is smaller than its height,
 *     then a horizontal line will divide the rectangle into upper and lower rectangles.
 *  2. The coordinate of the dividing line is chosen such that combined sum squared
 *     deviations from the mean color in the left/upper and right/lower rectangles is minimal
 *     among all other potential dividing lines of the same orientation.
 *     e.g. for a region (0,0) to (3,2), the candidates are the vertical lines dividing the region into:
 *     - (0,0) to (0,2) and (1,0) to (3,2)
 *     - (0,0) to (1,2) and (2,0) to (3,2)
 *     - (0,0) to (2,2) and (3,2) to (3,2)
 *     The line which produces the minimal combined sum squared scores on the left
 *     and right will be used for the split.
 *  3. In the unlikely event that multiple candidates produce the same score, the one which
 *     most evenly splits the rectangular area will be chosen.
 *  4. In the even more unlikely even that two candidates produce the same score and produce
 *     the same minimal area difference, the one with the smaller coordinate will be chosen.
 */
ImgTree::ImgTree(const PNG& img) {
    // complete your implementation below
    if (img.height() != 0 && img.width() != 0) {
        Stats s(img);
        root = BuildNode(s, 0, 0, img.height()-1, img.width()-1);
        imgheight = img.height();
        imgwidth = img.width();
    } else {
        root = nullptr;
    }
}

/**
 *  Releases all heap memory associated with this tree, restoring it to an "empty tree" state.
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::Clear() {
    // complete your implementation below
    // clearTree(root);
}

/**
 *  Copies the supplied parameter tree into this tree. Does not free any memory.
 *  Called by the copy constructor and operator=.
 *  Will be useful to define a recursive helper function for this.
 *  HINT: the helper should allocate a new node, and return a pointer to the allocated node.
 *        See the documention for BuildNode - this should work similarly.
 */
void ImgTree::Copy(const ImgTree& other) {
    // complete your implementation below
    PNG img = other.Render(1);
    Stats s(img);
    root = BuildNode(s, other.root->upper, other.root->left, other.root->lower, other.root->right);

}

/**
 *  Recursive helper function for initial construction of the tree. Constructs a single
 *  node according to supplied Stats and the requirements specified by the constructor
 *  documentation, and returns a pointer to the completed node.
 *  @param s - populated Stats object for computing this node's attributes
 *  @param upr - y-coordinate of the upper edge of the node's rectangular region
 *  @param lft - x-coordinate of the left side of the node's rectangular region
 *  @param lwr - y-coordinate of the lower edge of the node's rectangular region
 *  @param rt - x-coordinate of the right side of the node's rectangular region
 *  @return - pointer to a (completed) newly-allocated node for the specified parameters.
 */
ImgTreeNode* ImgTree::BuildNode(Stats& s, unsigned int upr, unsigned int lft, unsigned int lwr, unsigned int rt) {
    ImgTreeNode * temp = new ImgTreeNode(upr, lft, lwr, rt, s.GetAvg(upr, lft, lwr, rt));

    // complete your implementation below
    bool verti = (lwr - upr) > (rt - lft);
    bool horiz = (lwr - upr) <= (rt - lft);
    unsigned int partition = 0;
    if ((upr-lwr) == 0 && (lft- rt) == 0) {
        return temp;
    }
    if (upr > lwr || lft > rt) {
        return nullptr;
    }
    if (verti) {
        double part = 500000000000;
        //find the lower value for horizontal partition
        for (unsigned int i = upr; i < lwr; i++) {
            double up = s.GetSumSqDev(upr, lft, i, rt);
            double down = s.GetSumSqDev(i+1, lft, lwr, rt);
            double sum  = up + down;
            
            if (sum == part) {
                int temp = (int) partition;
                int mid = (int) (lwr - upr)/2;
                int ii = (int) i;
                if (abs(mid - temp) > abs(mid - ii)) {
                    part = sum;
                    partition = i;
                }
            } else if (sum < part) {
                partition = i;
                part = sum;
                
            }
        }
       
        // printf("verti, upr: %d, lft: %d, lwr: %d, rt: %d\n", upr, lft, lwr, rt);
        // printf("Best split found at y=%d\n", partition);
        // printf("Child A will be created at upr: %d, lft: %d, lwr: %d, rt: %d\n", upr, lft, partition, rt);
        // printf("Child B will be created at upr: %d, lft: %d, lwr: %d, rt: %d\n", partition+1, lft, lwr, rt);
        

        temp->A = BuildNode(s, upr, lft, partition, rt);
        temp->B = BuildNode(s, partition + 1, lft, lwr, rt);

    } else if (horiz) {
        double part = 40000000000000.0;
        //find the lower value for vertical partition
        for (unsigned int i = lft; i < rt; i++) {
            double left = s.GetSumSqDev(upr, lft, lwr, i);
            double right = s.GetSumSqDev(upr, i+1, lwr, rt);
            
            double sum  = left + right;
            if (sum == part) {
                int temp = (int) partition;
                int mid = (int) (rt-lft)/2;
                int ii = (int) i;
                if (abs(mid - temp) > abs(mid - ii)) {
                    part = sum;
                    partition = i;
                }
            } else if (sum < part) {
                partition = i;
                part = sum;
                
            }
        }
        // printf("horiz, upr: %d, lft: %d, lwr: %d, rt: %d\n", upr, lft, lwr, rt);
        // printf("Best split found at x=%d\n", partition);
        // printf("Child A will be created at upr: %d, lft: %d, lwr: %d, rt: %d\n", upr, lft, lwr, partition);
        // printf("Child B will be created at upr: %d, lft: %d, lwr: %d, rt: %d\n", upr, partition+1, lwr, rt);
        

        temp->A = BuildNode(s, upr, lft, lwr, partition);
        temp->B = BuildNode(s, upr, partition + 1, lwr, rt);
    }
    return temp;
}

/**
 *  Produces a PNG of appropriate dimensions and paints every leaf node's rectangle
 *  into the appropriate area of the PNG.
 *  May be called on pruned trees.
 *  @param scaling factor for how large to render the image. Assume this is >= 1.
 *  @return fully-colored PNG, painted from the tree's leaf node data
 */
PNG ImgTree::Render(unsigned int scale) const {
    // complete your implementation below
    PNG png(imgwidth * scale, imgheight * scale);
    renderNode(root, png, scale);
    return png; // REPLACE THIS STUB
}

/**
 *  Rearranges a tree's internal pointers and node content so that its image data
 *  appears flipped horizontally when rendered.
 *  Beware that the tree may or may not have been pruned!
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::FlipHorizontal() {
    // complete your implementation below
    flipTree(root);
}

/**
 *  Trims subtrees as high as possible in the tree.
 *  A subtree is pruned (all decendants deallocated and child links set to null)
 *  if at least pct (out of 100) of its leaves are within tol of the average
 *  color in the subtree's root.
 *  Assume that this will only be called on trees which have not previously been pruned.
 *  Will be useful to define AT LEAST one recursive helper function for this.
 *  @pre pct is a valid value between 0 and 100
 *  @param pct percentage (out of 100) of leaf node descendants must be within the tolerance threshold
 *             of color difference in order to be pruned
 *  @param tol threshold color difference to qualify for pruning
 */
void ImgTree::Prune(double pct, double tol) {
    // complete your implementation below
    pruneHelper(pct, tol, root);
}

/**
 *  Counts the number of leaf nodes in the tree.
 *  Will be useful to define a recursive helper function for this.
 */
unsigned int ImgTree::CountLeaves() const {
    // complete your implementation below
    int sum = counting(root, 0);
   
    return sum;
    
}

/**
 *  ADD YOUR PRIVATE FUNCTION IMPLEMENTATIONS BELOW
 */
void ImgTree::pruneHelper(double pct, double tol, ImgTreeNode* node) {
    
    if (!node) {
        return;
    }
    // if (node->A && node->B) {
       
        RGBAPixel color = node->avg;
        unsigned int soFar = 0;
        unsigned int leaves = 0;
        prunable(tol, soFar, leaves, node, color);

    

        if (pct <= (double) soFar* 100/leaves) {
            clearTree(node->A);
            clearTree(node->B);
            node->A = nullptr;
            node->B = nullptr;

        } else {
            pruneHelper(pct, tol, node->A);
            pruneHelper(pct, tol, node->B); 
        }
    
    // }
}
void ImgTree::prunable(double tol, unsigned int& soFar,unsigned int& leaves, ImgTreeNode* node, RGBAPixel& color) {
    if(!node) {
        return;
    }
    
    if (!node->A && !node->B) {
        leaves++;
        if (node->avg.dist(color) <= tol) {
            soFar++;
        }
    } else {
        prunable(tol, soFar, leaves, node->A, color);
        prunable(tol, soFar, leaves, node->B, color);
    }
    
   
}
void ImgTree::renderNode(ImgTreeNode* node, PNG& png, unsigned int scale) const {
    // cout << "\noutside" << endl;
    if (!node) {
        return;
    }
    renderNode(node->A, png, scale);
    if(!node->A && !node->B) {
        // cout << "\nhere" << endl;
        for (unsigned int y = node->upper*scale; y < node->lower*scale + 1; y++) {
            for (unsigned int x = node->left*scale; x < node->right*scale + 1; x++) {
                for(unsigned int j = 0; j < scale; j++) {
                    for (unsigned int i = 0; i < scale; i++) {
                        RGBAPixel * pixel = png.getPixel(x+i, y+j);
                        *pixel = node->avg;
                    }
                }
                
            }
        }
        
    }

    renderNode(node->B, png, scale);
}
void ImgTree:: flipTree(ImgTreeNode* node) {
    if(!node) {
        return;
    }
    flipTree(node->A);
    node->left = imgwidth - node->left - 1;
    node->right = imgwidth - node->right - 1;
    flipTree(node->B);

}
unsigned int ImgTree::counting(ImgTreeNode* node, unsigned int num) const{
    if (!node) {
        return 0;
    }

    if(!node->A && !node->B) {
        num++;
    }
   
    return num + counting(node->A, num) + counting(node->B, num);
}
 void ImgTree::clearTree(ImgTreeNode* node) {
    if (node == nullptr) {
        return;
    }
    
    // Recursively clear the left subtree
    clearTree(node->A);
    
    // Recursively clear the right subtree
    clearTree(node->B);
    
    // Delete the current node
    delete node;
}
