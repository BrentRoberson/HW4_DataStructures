#ifndef MYBSTREE_H
#define MYBSTREE_H

#include <iostream>
#include <string>
#include "abstractbstree.h"

template <typename T>
class TreeNode
{
public:
   T m_data;
   TreeNode* m_right;
   TreeNode* m_left;
   TreeNode(const T& data, TreeNode<T>* left, TreeNode<T>* right){
     m_data = data;
     m_right = right;
     m_left = left;
   }
   TreeNode<T>* clone(const TreeNode<T>* temp);
};

template <class T>   
TreeNode<T>* TreeNode<T>:: clone(const TreeNode<T>* t){
  if (t == NULL) return NULL;
  return new TreeNode<T>(t->m_data, clone(t->m_left), clone(t->m_right));
}

/* ---------------  Abstract Class AbstractBSTree --------------- */
template < class T >
class MyBSTree : public AbstractBSTree<T>
{
  TreeNode<T>* m_root;
  int m_size;
  int m_height;
  const T& recursive_getMin( TreeNode<T>* t ) const;
  const T& recursive_getMax( TreeNode<T>* t ) const;
  void prettyPrint(TreeNode<T>* t, int pad) const;
  void recursive_insert(TreeNode<T>* &t, const T& x);
  int recursive_max_depth(TreeNode<T>* t) const;
  void recursive_remove(TreeNode<T>*& t, const T& x);
  int recursive_find(TreeNode<T>* t, const T& x, int height) const;
  void recursive_clear(TreeNode<T>* t);
  void recursive_printPreOrder(TreeNode<T>* t) const;
  void recursive_printPostOrder(TreeNode<T>* t) const; 


  public:
    MyBSTree();
    int size() const;
    bool isEmpty() const;
    int height() const;
    const T& getMax() const throw (Oops);
    const T&  getMin() const throw (Oops);
    int  find(const T& x) const;
    void clear();
    void insert(const T& x);
    void remove(const T& x);
    void printPreOrder() const;
    void printPostOrder() const; 
    void print() const;   
    MyBSTree<T>& operator= (const MyBSTree<T>&rhs);       
    MyBSTree<T>& operator~();  
    MyBSTree(const MyBSTree<T>& t);     
};
 
#endif 