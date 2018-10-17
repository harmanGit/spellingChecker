
/**
 * Partial implementation of an AVL search tree.
 * Note that all "matching" is based on the compares method.
 */
 /**
  * Construct the tree.
  */
template <class Comparable>
AvlTree<Comparable>::AvlTree(const Comparable & notFound) :
	ITEM_NOT_FOUND(notFound), root(NULL)
{
}

/**
 * Copy constructor.
 */
template <class Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree<Comparable> & rhs) :
	ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), root(NULL)
{
	*this = rhs;
}

/**
 * Destructor for the tree.
 */
template <class Comparable>
AvlTree<Comparable>::~AvlTree()
{
	makeEmpty();
}

/**
 * Insert x into the tree; duplicates are ignored.
 */
template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable & x)
{
	insert(x, root);
}

/**
 * Find item x in the tree.
 * Return the matching item or ITEM_NOT_FOUND if not found.
 */
template <class Comparable>
const Comparable & AvlTree<Comparable>::find(const Comparable & x) const
{
	return elementAt(find(x, root));
}

/**
 * Make the tree logically empty.
 */
template <class Comparable>
void AvlTree<Comparable>::makeEmpty()
{
	makeEmpty(root);
}

/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
template <class Comparable>
bool AvlTree<Comparable>::isEmpty() const
{
	return root == NULL;
}

/**
 * Public method to print a tree's structure
 */
template <class Comparable>
void AvlTree<Comparable>::printTree() const
{
	printTree(root, 0);
}

/**
 * Internal method to print a tree's structure
 * t points to the node that roots the tree.
 */
template <class Comparable>
void AvlTree<Comparable>::printTree(AvlNode<Comparable> *t, int depth) const
{
	if (t != NULL)
	{
		printTree(t->right, depth + 1);
		for (int i = 0; i < depth; i++)
			cout << "     ";
		cout << t->element << endl;
		printTree(t->left, depth + 1);
	}
}

/**
 * Deep copy.
 */
template <class Comparable>
const AvlTree<Comparable> & AvlTree<Comparable>::operator=(const AvlTree<Comparable> & rhs)
{
	if (this != &rhs)
	{
		makeEmpty();
		root = clone(rhs.root);
		count = rhs.count;
	}
	return *this;
}

/**
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable>
const Comparable & AvlTree<Comparable>::elementAt(AvlNode<Comparable> *t) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
 * Internal method to find an item in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 * Return node containing the matched item.
 */
template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::find(const Comparable & x, AvlNode<Comparable> *t) const
{
	while (t != NULL)
		if (x < t->element)
			t = t->left;
		else if (t->element < x)
			t = t->right;
		else
			return t;    // Match

	return NULL;   // No match
}

/**
 * Internal method to make subtree empty.
 */
template <class Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode<Comparable> * & t)
{
	if (t != NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}

/**
 * Internal method to clone subtree.
 */
template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::clone(AvlNode<Comparable> * t) const
{
	if (t == NULL)
		return NULL;
	else
		return new AvlNode<Comparable>(t->element, clone(t->left),
			clone(t->right), t->height);
}

/**
 * Return the height of node t, or -1, if NULL.
 */
template <class Comparable>
int AvlTree<Comparable>::height(AvlNode<Comparable> *t) const
{
	return t == NULL ? -1 : t->height;
}


/**************************************************************************************
 ****** INCOMPLETE METHODS - finish or modify as needed
 **************************************************************************************/



template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable & x)
{
	cout << "Sorry, remove unimplemented; " << x <<  // <--- Implement this public method
		" still present" << endl;
}

/**
 * Internal method to remove x from the tree. Nothing is done if x is not found.
 * If x is found, lazy deletion is used.
 */
template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable & x, AvlNode<Comparable> * & t)
{
	// <--- Implement this private method
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.               // <----- This is the binary search tree insert
 */                                                 // Modify to do rotations as needed
template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable & x, AvlNode<Comparable> * & t)
{
	if (t == NULL)
		t = new AvlNode<Comparable>(x, NULL, NULL);
	else if (x < t->element)
	{
		insert(x, t->left);

	}
	else if (t->element < x)
	{
		insert(x, t->right);

	}
	else
		;  // Duplicate; do nothing

}

/**
* Return maximum of lhs and rhs.
*/
template <class Comparable>
int AvlTree<Comparable>::max(int lhs, int rhs) const
{
	return 0; // temporary code, just so it will compile   <----------- Finish this
}

/**
 * Rotate binary tree node with left child.
 * For AVL trees, this is a single rotation for case 1.
 * Update heights, then set new root.
 */
template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode<Comparable> * & k2)
{
	AvlNode<Comparable> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

/**
 * Rotate binary tree node with right child.
 * For AVL trees, this is a single rotation for case 4.
 * Update heights, then set new root.
 */
template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild(AvlNode<Comparable> * & k1)
{
	// <----------- Finish this
}

/**
 * Double rotate binary tree node: first left child.
 * with its right child; then node k3 with new left child.
 * For AVL trees, this is a double rotation for case 2.
 * Update heights, then set new root.
 */
template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild(AvlNode<Comparable> * & k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

/**
 * Double rotate binary tree node: first right child.
 * with its left child; then node k1 with new right child.
 * For AVL trees, this is a double rotation for case 3.
 * Update heights, then set new root.
 */
template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild(AvlNode<Comparable> * & k1)
{
	// <----------- Finish this
}


