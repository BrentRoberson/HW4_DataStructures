#ifndef MYBSTREE_HPP
#define MYBSTREE_HPP

#include <iostream>
#include <string>
#include "abstractbstree.h"
#include "mybstree.h"
using namespace std;

template <class T>
MyBSTree<T> :: MyBSTree()
{
  m_size = 0;
  m_root = NULL;
}

template <class T>
void MyBSTree<T> :: prettyPrint(TreeNode<T>* t, int pad) const
{
  string s(pad, ' ');
  if (t == NULL)
      cout << endl;
  else{
    prettyPrint(t->m_right, pad+4);
    cout << s << t->m_data << endl;
    prettyPrint(t->m_left, pad+4);
  }
  return;  
}

template <class T>
void MyBSTree<T> :: recursive_printPreOrder(TreeNode<T>* t) const
{
  if(t==NULL) return;
  cout<<t->m_data<<" ";
  recursive_printPreOrder(t->m_left);
  recursive_printPreOrder(t->m_right);

  return;  
}

template <class T>
void MyBSTree<T> :: recursive_printPostOrder(TreeNode<T>* t) const
{
  if(t==NULL) return;
  else{
    recursive_printPostOrder(t->m_left);
    recursive_printPostOrder(t->m_right);
    cout<<t->m_data<<" ";
  }
  return;  
  return;  
}


template <class T>
const T& MyBSTree<T> :: recursive_getMin( TreeNode<T>* t ) const{
    if(t==NULL) return NULL;
    if ( t->m_left == NULL ) 
        return t->m_data;
    else 
        return recursive_getMin( t->m_left ); 
  }

template <class T>
const T& MyBSTree<T> :: recursive_getMax( TreeNode<T>* t ) const{
    if(t==NULL) return NULL;
    if ( t->m_right == NULL ) 
        return t->m_data;
    else 
        return recursive_getMax( t->m_right ); 
  }


template <class T>
void MyBSTree<T> :: recursive_insert(TreeNode<T>* &t, const T& x)
{
  if(t==NULL) {
    t = new TreeNode<T>(x,NULL,NULL);
    m_size++;
  }
  else if(x < t->m_data){
    recursive_insert(t->m_left,x);
  }
  else if(x > t->m_data){
    recursive_insert(t->m_right,x);
  }
  return;
}

template <class T>
int MyBSTree<T> :: recursive_max_depth(TreeNode<T>* t) const
{
  if(t==NULL) return -1;
  else{
    int leftMax = recursive_max_depth(t->m_left);
    int rightMax = recursive_max_depth(t->m_right);
    
    return (leftMax >= rightMax) ? leftMax+1: rightMax+1;
  }
}

template <class T>
void MyBSTree<T> :: recursive_remove(TreeNode<T>* &t, const T& x)
{
  if(t==NULL) return;
  //try to find the value we are searching for
  if( x < t->m_data) recursive_remove( t->m_left, x);
  else if ( x > t->m_data) recursive_remove( t->m_right, x);
  else //found the value
  {
    //no children
    if (t->m_left == NULL && t->m_right == NULL){
     
      delete t;
      t = NULL;
    }
    //one child
    else if (t->m_left == NULL || t->m_right == NULL){
      TreeNode<T>* child = t->m_left;
      if ( child == NULL ) child = t->m_right;
      delete t;
      t = child;
    }
    // two children
    else{
      t->m_data = recursive_getMax( t->m_left );
      recursive_remove( t->m_left, t->m_data );
    }
  }
}


template <class T>
int MyBSTree<T> :: recursive_find(TreeNode<T>* t, const T& x, int height) const
{
  if(t == NULL) return (height+1)*-1;
  if(t->m_data == x) return height+1;
  else if(x<t->m_data){
    recursive_find(t->m_left,x,height+1);
  }
  else{
    recursive_find(t->m_right, x, height+1);
  }
}

template <class T>
void MyBSTree<T> :: recursive_clear(TreeNode<T>* t)
{
  if(t==NULL) return;
  else{
    recursive_clear(t->m_left);
    recursive_clear(t->m_right);
    cout << "Deleting node: " << t->m_data << endl;
    delete t;
  }

}

template <class T>
int MyBSTree<T> :: size() const{
  return m_size;
}

template <class T> 
bool MyBSTree<T> :: isEmpty() const{
  return (m_size==0);
}

template <class T>
int MyBSTree<T> :: height() const{
  return recursive_max_depth(m_root)+1 ;
}

template <class T>
const T& MyBSTree<T> :: getMax() const throw (Oops){
  if(m_size == 0) throw Oops("OOPS! : Tree is Empty!!");;
  return recursive_getMax(m_root);

}

template <class T>
const T& MyBSTree<T> :: getMin() const throw (Oops){
  if(m_size == 0) throw Oops("OOPS! : Tree is Empty!!");;
  return recursive_getMin(m_root);

}

template <class T>
int MyBSTree<T>:: find(const T& x) const{
  return recursive_find(m_root, x, 0);
}

template <class T>
void MyBSTree<T> :: clear(){
  recursive_clear(m_root);
  m_size = 0;
}


template <class T>
void MyBSTree<T> :: insert(const T& x){
  recursive_insert(m_root, x);
}

template <class T>
void MyBSTree<T> :: remove(const T& x){
  recursive_remove(m_root, x);
  m_size --;
  return;
}
    
template <class T>
void MyBSTree<T> :: printPreOrder() const{
  recursive_printPreOrder(m_root);
  return;
}

template <class T> 
void MyBSTree<T> :: printPostOrder() const{
  recursive_printPostOrder(m_root);
  return;
} 

template <class T>   
void MyBSTree<T> :: print() const{
  if(isEmpty()) return;
  prettyPrint(m_root, 4);
  return;
}



template <class T>   
MyBSTree<T>& MyBSTree<T> ::operator= (const MyBSTree<T>&rhs){
  m_root = rhs.m_root->clone(rhs.m_root);
  m_size = rhs.m_size;
  return *this;
}

template <class T>   
MyBSTree<T>& MyBSTree<T> ::operator~(){
  clear();
}


template <class T>   
MyBSTree<T> ::MyBSTree(const MyBSTree<T>& t){
  m_root = t.m_root->clone(t.m_root);
  m_size = t.m_size;
}

#endif 