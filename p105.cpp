#include <iostream>
#include <queue>
using namespace std;

enum { bitEnter = 1 << (sizeof(int) * 8 - 1), bitLeave = bitEnter >> 1 };

// Use the higer too bits to indicate whether or not this is an enter or leave event
struct e
{
	int cordinate;
};

inline int compare(const e &a, const e &b)
{
	int va = a.cordinate & (~(bitEnter | bitLeave));
	int vb = b.cordinate & (~(bitEnter | bitLeave));

	return va - vb;
}
bool operator <(const e &a, const e &b) { return compare(a, b) < 0; } // SWO compare for STL

template<class T>
struct node
{
	T v;
	node* l;
	node* r;
};

// BST functions
template <class T>
node<T>* insertBST(node<T>* n, T v);

template <class T>
node<T>* removeBST(node<T>* n, T v);

template <class T>
T rightMost(node<T>* root);

template <class T>
node<T>* _rotate(node<T>* n, bool left);

template <class T>
int _height(const node<T>* n);

template <class T>
node<T>* _balance(node<T>* n);

int main()
{
	int bit = 4;
	// 8 - 1
	int a = (15 << 28);
	int b = (8 << 28);

	unsigned int c = unsigned int((a - b) >> 28);
	return 0;
}

template <class T>
node<T>* insertBST(node<T>* n, T v)
{
	if (n == NULL)
	{
		n = new node<T>();
		n->l = n->r = NULL;
		n->v = v;
		return n;
	}

	if (v < n->v)
		n->l = insertBST(n->l, v);
	else if (n->v < v)
		n->r = insertBST(n->r, v);
	else
		throw new invalid_argument("Duplicate key");

	return _balance(n);
}

template <class T>
node<T>* removeBST(node<T>* n, T v)
{
	if (n == NULL)
	{
		return NULL;
	}

	if (v < n->v)
		n->l = removeBST(n->l, v);
	else if (n->v < v)
		n->r = removeBST(n->r, v);
	else
	{
		// This is the node to remove
		node<T>* l = n->l;
		node<T>* r = n->r;

		if (l == NULL && r == NULL)
		{
			// leaf node
			delete n;
			n = NULL;
		}
		else if (l != null && r != null)
		{
			// Both childs
			// replace with largest node
			node<T>* p = NULL;
			while(r->r != null)
			{
				p = r;
				r = r->r;
			}

			if (p != NULL) p->r= NULL;
			r->l = l;
			r->r = n->r;
			delete n;
			n = r;
		}
		else
		{
			// single child
			delete n;
			n == l ? l : r;
		}

		n = _balance(n);
	}

	return n;
}

template <class T>
node<T>* _rotate(node<T>* n, bool left)
{
	if (n == NULL ||
		(left && n->r == NULL) ||
		(!left && n->l == NULL))
		return n;

	node<T> *root = NULL;
	if (left)
	{
		root = n->r;
		n->r = root->l;
		root->l = n;
	}
	else
	{
		root = n->l;
		n->l = root->r;
		root->r = n;
	}

	return root;
}

template <class T>
node<T>* _balance(node<T>* n)
{
	if (_height(n->l) - _height(n->r) == -2)
	{
		// right/right or right/left
		if (_height(n->r->l) - _height(n->r->r) < 1)
			n = _rotate(n, true); // right/right
		else
		{
			// right/left
			n->r = _rotate(n->r, false);
			n = _rotate(n, true);
		}
	}
	else if (_height(n->l) - _height(n->r) == 2)
	{
		// left/left or left/right
		if (_height(n->l->r) - _height(n->l->l) < 1)
			n = _rotate(n, false); // left/left
		else
		{
			// left/right
			n->l = _rotate(n->l, true);
			n = _rotate(n, false);
		}
	}

	return n;
}

template <class T>
T rightMost(node<T>* root)
{
	if (root == NULL)
		return NULL;

	while(root->r) root = root->r;

	return root->v;
}

template <class T>
int _height(const node<T>* n)
{
	if (n == NULL)
		return 0
	int hl = _height(n->l) + 1;
	int hr = _height(n->r) + 1;

	return (hl > hr ) ? hl : hr;
}