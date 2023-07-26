#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
	key = 0;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}
// Constructor
Node::Node(int in) {
	key = in;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}
// Destructor
Node::~Node() {
}

// Add parent 
void Node::add_parent(Node* in) {
		parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
		left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
		right = in;
}

// Get key
int Node::get_key()
{
	return key;
}
// Get parent node
Node* Node::get_parent()
{
		return parent;
}
// Get left node
Node* Node::get_left()
{
		return left;
}
// Get right node
Node* Node::get_right()
{
		return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}

void Node::set_key(int in)
{
	key = in;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
	if(in == nullptr)
		return;
	inorder_walk(in->get_left(), to);
	in->print_info(to);
	inorder_walk(in->get_right(), to);
}
// Constructor
BST::BST()
{
	root = nullptr;
}
// Destructor
BST::~BST()
{
	if (root)
		delete root;
}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
	if(!root)
		root = in;
	else
	{
		Node* curr = root;
		Node* par = nullptr;
		while(curr)
		{
			par = curr;
			if (curr->get_key() > in->get_key())
				curr = curr->get_left(); // searching for the correct position to input node
			else
				curr = curr->get_right();
		}
	in->add_parent(par);

	if (par->get_key() > in->get_key())
	{	
		par->add_left(in);
	}
	else
		par->add_right(in);
	}
}
// Delete a node to the subtree
void BST::delete_node(Node* out)
{
	if(!root)
		exit(EXIT_FAILURE);
	if(out == nullptr)
		exit(EXIT_FAILURE);

	// 3 cases, no children, one child, two children
	

	// No children
	if (out->get_left() == nullptr && out->get_right() == nullptr)
	{
		if (out == root)
			root = nullptr; // root is only node
		else
		{
			Node* par = out->get_parent();

			if(par->get_left() == out)
				par->add_left(nullptr); // set to empty
			else
				par->add_right(nullptr); // set to empty
		}
		delete out;
		return;
	}

	// one child
	
	if (out->get_left() == nullptr or out->get_right() == nullptr)
	{
		Node* tmp;

		if(out->get_left() == nullptr)
			tmp = out->get_right();
		else
			tmp = out->get_left();
		
		if (out == root)
		{
			root = tmp;
			tmp->add_parent(nullptr);
		}
		else
		{
			Node* par = out->get_parent();

			if (par->get_left() == out)
				par->add_left(tmp);
			else
				par->add_right(tmp);

			tmp->add_parent(par);
		}
		delete out;
		return;	
	}
	
	// two children
	Node* succ = get_succ(out);
	out->set_key(succ->get_key());
	delete_node(succ); // recursive call, referred to my old code for this part, pretty straightforward.
}
// minimum key in the BST
Node* BST::tree_min()
{
	if(!root)
	{
		cout << "Empty Tree" << endl;
		return nullptr;
	}	
	Node* curr = root;
		while(curr->get_left())
		{
			curr = curr->get_left(); // leftmost of a BST is the min
		}
	return curr;
}
// maximum key in the BST
Node* BST::tree_max()
{
	 if(!root)
        {
                cout << "Empty Tree" << endl;
                return nullptr;
        }
        Node* curr = root;
                while(curr->get_right())
                {
                      curr = curr->get_right(); // rightmost of a BST is the max
                }
	return curr;
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
	if(!root)
        {
                cout << "Empty Tree" << endl;
                return nullptr;
        }
	if(in == nullptr)
		return nullptr;
	
        Node* curr = in;
                while(curr->get_left())
                {
                      curr = curr->get_left(); // min node is always the leftmost of a BST
                }
	return curr;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
	if(!root)
        {
                cout << "Empty Tree" << endl;
                return nullptr;
        }
	if(in == nullptr)
		return nullptr;

        Node* curr = in;
                while(curr->get_right())
                {
                      curr = curr->get_right(); // max node is always the rightmost of a BST
                }
	return curr;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{
	if(!root)
	{
		cout << "Empty Tree" << endl;
		return nullptr;
	}

	if(in == nullptr)
		return nullptr;

	//Three cases, right child, no right child, parent is successor
	if(in->get_right())
		return get_min(in->get_right()); // leftmost node of the subtree
	
	Node* curr = in;
	Node* par = curr->get_parent();

	while(par != nullptr && curr == par->get_right())
	{
		curr = par;
		par = par->get_parent(); // go up until one of the other cases are met
	}

	return par;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
	// basically is the opposite method of finding successor
	        if(!root)
        {
                cout << "Empty Tree" << endl;
                return nullptr;
        }

        if(in == nullptr)
                return nullptr;

        //Three cases, right child, no right child, parent is pred
        if(in->get_left())
                return get_max(in->get_right()); // rightmost node of the subtree

        Node* curr = in;
        Node* par = curr->get_parent();

        while(par != nullptr && curr == par->get_left())
        {
                curr = par;
                par = par->get_parent(); // go up until one of the other cases are met
        }

        return par;
}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
	if(root == nullptr)
		exit(EXIT_FAILURE);
	else
		inorder_walk(root, to);
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
	if(root == nullptr)
		exit(EXIT_FAILURE);
	Node* curr = root;

	while(curr != nullptr && curr->get_key() != search_key) // exists, but have not found yet...
		{
			if(search_key < curr->get_key()) // less than, so go left
				curr = curr->get_left();
			else
				curr = curr->get_right(); // more than, go right


		}
	return curr;
}
