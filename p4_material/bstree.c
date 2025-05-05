#include "bstree.h"

#include <stdio.h>
#include <stdlib.h>

/* START [_BSTNode] */
typedef struct _BSTNode {
  void *info;
  struct _BSTNode *left;
  struct _BSTNode *right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree {
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
};
/* END [_BSTree] */

/*** BSTNode TAD private functions ***/
BSTNode *_bst_node_new() {
  BSTNode *pn = NULL;

  pn = malloc(sizeof(BSTNode));
  if (!pn) {
    return NULL;
  }

  pn->left = NULL;
  pn->right = NULL;
  pn->info = NULL;

  return pn;
}

void _bst_node_free(BSTNode *pn) {
  if (!pn) {
    return;
  }

  free(pn);
  return;
}

void _bst_node_free_rec(BSTNode *pn) {
  if (!pn) {
    return;
  }

  _bst_node_free_rec(pn->left);
  _bst_node_free_rec(pn->right);
  _bst_node_free(pn);

  return;
}


void _bst_node_free_rec_and_elements(BSTNode *pn) {
  if (!pn) {
    return;
  }

  _bst_node_free_rec_and_elements(pn->left);
  _bst_node_free_rec_and_elements(pn->right);
  free(pn->info);
  _bst_node_free(pn);

  return;
}

int _bst_depth_rec(BSTNode *pn) {
  int depth_l, depth_r;

  if (!pn) {
    return 0;
  }

  depth_l = _bst_depth_rec(pn->left);
  depth_r = _bst_depth_rec(pn->right);

  if (depth_r > depth_l) {
    return depth_r + 1;
  } else {
    return depth_l + 1;
  }
}

int _bst_size_rec(BSTNode *pn) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_size_rec(pn->left);
  count += _bst_size_rec(pn->right);

  return count + 1;
}

int _bst_preOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += print_ele(pf, pn->info);
  count += _bst_preOrder_rec(pn->left, pf, print_ele);
  count += _bst_preOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_inOrder_rec(pn->left, pf, print_ele);
  count += print_ele(pf, pn->info);
  count += _bst_inOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_postOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_postOrder_rec(pn->left, pf, print_ele);
  count += _bst_postOrder_rec(pn->right, pf, print_ele);
  count += print_ele(pf, pn->info);

  return count;
}

BSTNode *_bst_find_min_rec(BSTNode *pn) {
  if(!pn) return NULL;
  if(!pn->left) return pn;
  return _bst_find_min_rec(pn->left);
}

BSTNode *_bst_find_max_rec(BSTNode *pn) {
  if(!pn) return NULL;
  if(!pn->right) return pn;
  return _bst_find_max_rec(pn->right);
}

Bool _bst_contains_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
  int cmp_result = 0;

  if(!pn) return FALSE;
  cmp_result = cmp_elem(elem, pn->info);

  if(!cmp_result) return TRUE;
  else if(cmp_result < 0){
    return _bst_contains_rec(pn->left, elem, cmp_elem);
  }
  else{
    return _bst_contains_rec(pn->right, elem, cmp_elem);
  }
}

BSTNode *_bst_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
  int cmp_result = 0;

  if(!pn){
    if(!(pn = _bst_node_new())){
      return NULL;
    }
    pn->info = (void*)elem;
    return pn;
  }
  cmp_result = cmp_elem(elem, pn->info);
  if(!cmp_result) return NULL;
  else if(cmp_result>0){
    pn->right = _bst_insert_rec(pn->right, elem, cmp_elem);
  }
  else{
    pn->left = _bst_insert_rec(pn->left, elem, cmp_elem);
  }
  return pn;
}

BSTNode *_bst_remove_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
  int cmp_result = 0;
  void *info_to_remove = NULL;
  BSTNode *aux = NULL;

  if(!pn) return NULL;

  if(!(cmp_result = cmp_elem(elem, pn->info))){
    
    if(!pn->right && !pn->left){
      _bst_node_free(pn);
      return NULL;
    }
    else if(!pn->right && pn->left){
      aux = pn->left;
      _bst_node_free(pn);
      return aux;
    }
    else if(!pn->left && pn->right){
      aux = pn->right;
      _bst_node_free(pn);
      return aux;
    }
    else{
      aux = _bst_find_min_rec(pn->right);
      info_to_remove = aux->info;
      pn->info = aux->info;
      pn->right = _bst_remove_rec(pn->right, info_to_remove,cmp_elem);
      return pn;
    }
  }
  else if (cmp_result>0){
    pn->right = _bst_remove_rec(pn->right, elem, cmp_elem);
  }
  else{
    pn->left = _bst_remove_rec(pn->left, elem, cmp_elem);
  }
  return pn;
}

/*** BSTree TAD functions ***/
BSTree *tree_init(P_ele_print print_ele, P_ele_cmp cmp_ele) {
  BSTree *tree;

  if (!print_ele || !cmp_ele) {
    return NULL;
  }

  tree = malloc(sizeof(BSTree));
  if (!tree) {
    return NULL;
  }

  tree->root = NULL;
  tree->print_ele = print_ele;
  tree->cmp_ele = cmp_ele;

  return tree;
}

void tree_destroy(BSTree *tree) {
  if (!tree) {
    return;
  }

  if(tree->root != NULL){
    _bst_node_free_rec(tree->root);
    free(tree);
  }

  return;
}

Bool tree_isEmpty(const BSTree *tree) {
  if (!tree || !tree->root) {
    return TRUE;
  }
  return FALSE;
}

int tree_depth(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_size_rec(tree->root);
}

int tree_preOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

/**
 * @brief Public function that finds the minimum element in a Binary Search
 * Tree.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * minimum element. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 *
 * @return Pointer to the minimum element if found, NULL otherwise.
 */
void *tree_find_min(BSTree *tree){
  BSTNode *aux = NULL;
  if(!tree) return NULL;
  if(!tree->root) return NULL;
  aux = _bst_find_min_rec(tree->root);

  return (void*)aux->info; 
}

/**
 * @brief Public function that finds the maximum element in a Binary Search
 * Tree.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * maximum element. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 *
 * @return Pointer to the maximum element if found, NULL otherwise.
 */
void *tree_find_max(BSTree *tree){
  BSTNode *aux = NULL;
  if(!tree) return NULL;
  aux = _bst_find_max_rec(tree->root);

  return (void*)aux->info; 
}

/**
 * @brief Public function that tells if an element is in a Binary Search Tree.
 *
 * @param tree Pointer to the Tree.
 * @param elem Pointer to the element to be found in the Tree.
 *
 * @return Bool value TRUE if the element was found, FALSE otherwise.
 */
Bool tree_contains(BSTree *tree, const void *elem){
  if(!tree || !elem) return FALSE;
  if(!tree->cmp_ele) return FALSE;
  return _bst_contains_rec(tree->root, elem, tree->cmp_ele);
}

/**
 * @brief Public function that inserts an element into a Binary Search Tree.
 *
 * Inserts as a leaf the pointer of the element received as argument. If the
 * element is already in the BST it returns OK.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * insert position. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 * @param elem Pointer to the element to be inserted into the Tree.
 *
 * @return Status value OK if the insertion could be done or the element was
 * already in the BST, Status value ERROR otherwise.
 */
Status tree_insert(BSTree *tree, const void *elem){
  BSTNode *root = NULL;

  if(!tree || !elem) return ERROR;
  if(!tree->cmp_ele) return ERROR;
  root = _bst_insert_rec(tree->root, elem, tree->cmp_ele);
  if(!root) return OK;

  tree->root = root;
  return OK;
}

/**
 * @brief Public function that removes an element into a Binary Search Tree.
 *
 * Removes the (first) occurrence of the element received as argument.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * remove position. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 * @param elem Pointer to the element to be removed from the Tree.
 *
 * @return Status value OK if the removal could be done or the element was not
 * in the BST, Status value ERROR otherwise.
 */
Status tree_remove(BSTree *tree, const void *elem) {
  BSTNode *root = NULL;
  if(!tree || !elem) return ERROR;
  if(!tree->cmp_ele) return ERROR;

  root = _bst_remove_rec(tree->root, elem, tree->cmp_ele);

  if(!root) return OK;

  tree->root = root;
  return OK;
}


void tree_destroy_and_elements(BSTree *tree)
{
  if (!tree) {
    return;
  }

  if(tree->root != NULL){
    _bst_node_free_rec_and_elements(tree->root);
    free(tree);
  } 
}