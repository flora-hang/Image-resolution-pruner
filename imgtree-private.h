/**
 *  @file imgtree-private.h
 *  @description student-defined functions for binary tree class storing image data for CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN, EVEN IF YOU DO NOT ADD ANYTHING TO IT
 * 
 *  Usage: As this file is included entirely into imgtree.h by the #include statement on line 214
 *  you only need to write the function signature,
 *  e.g.
 *  void MyOwnSpecialFunction(int fave_num, ImgTreeNode* nd);
 * 
 *  and add/complete your implementation in imgtree.cpp
 */
void clearTree(ImgTreeNode* node);
void flipTree(ImgTreeNode* node);
void renderNode(ImgTreeNode* node, PNG& png, unsigned int scale) const;
unsigned int counting(ImgTreeNode* node, unsigned int num) const;
void pruneHelper(double pct, double tol, ImgTreeNode* node);
void prunable(double tol, unsigned int& soFar, unsigned int& leaves, ImgTreeNode* node, RGBAPixel& color);
