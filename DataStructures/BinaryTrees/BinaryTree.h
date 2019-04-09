#pragma once

template<class Type>
struct binaryTreeNode
{
	Type info;
	binaryTreeNode<Type> *l_link;
	binaryTreeNode<Type> *r_link;
};


template<class Type>
class binaryTree
{
private:
	Type max(Type info1, Type info2)
	{
		if (info1 > info2)
			return info1;
		else
			return info2;
	}
protected:
	binaryTreeNode<Type> *root;

public:
	int height(binaryTreeNode<Type> *p)
	{
		if (p == NULL) //if the binary tree is empty
			return 0;
		else
			return 1 + max(height(p->l_link), height(p->r_link));
	}
	void copy(binaryTreeNode<Type> *&copiedTreeRoot, binaryTreeNode<Type> *otherTreeRoot)
	{
		if (otherTreeRoot == NULL)
		{
			copiedTreeRoot = NULL;
		}
		else
		{
			copiedTreeRoot = new binaryTreeNode<Type>;
			copiedTreeRoot->info = otherTreeRoot->info;
			copy(copiedTreeRoot->l_link, otherTreeRoot->l_link);//copy the left side
			copy(copiedTreeRoot->r_link, otherTreeRoot->r_link);//copy the right side
		}
	}
	void preorder(binaryTreeNode<Type> *p)//node-left-right
		                                  //It can be used to make a copy of a binary tree
	{
		if (p != NULL)
		{
			cout << p->info << " ";
			preorder(p->l_link);
			preorder(p->r_link);
		}
	}
	void postorder(binaryTreeNode<Type> *p)//left-right-node
		                                   //It can be used to delete all of the nodes of a binary tree
	{
		if(p!=NULL)
		{
			postorder(p->l_link);
			postorder(p->r_link);
			cout << p->info << " ";
		}
	}
	void inorder(binaryTreeNode<Type> *p)//left-node-right
		                                 //Visits the nodes in SORTED ORDER.
	{
		if (p != NULL)
		{
			postorder(p->l_link);
			cout << p->info << " ";
			postorder(p->r_link);
		}
	}
	bool search(const Type &item)
	{
		binaryTreeNode<Type> *current;
		bool found = false;
		if(root==NULL)
			std::cout<<"Cannot search an empty tree."<<std::endl;
		else
		{
			current=root;
			while (current != NULL && found != true)
			{
				if (current->info == item)
					found = true;
				else if (current->info > item)
					current = current->l_link;
				else
					current = current->r_link;

			}
		}
		return found;
	}
	void insert(const Type &item)
	{
		binaryTreeNode<Type> *current;//pointer to traverse the node
		binaryTreeNode<Type> *trailCurrent;//pointter behind current
		binaryTreeNode<Type> *newNode;//pointer to create the node

		newNode = new binaryTreeNode<Type>;
		newNode->info = item;
		newNode->l_link = NULL;
		newNode->r_link = NULL;

		if (root == NULL)//if the tree is empty
			root = newNode;
		else
		{
			current = root;
			while (current != NULL)
			{
				trailCurrent = current;
				if (current->info == item)//the item to be inserted is already in the tree
				{
					std::cout << "The item to be insertedd is already in the tree -- duplicates are not allowerd." << std::endl;
					return;
				}
				else if (current->info > item)
					current = current->l_link;
				else
					current = current->r_link;
			}
			//insert thew new node in the binary tree
			if (trailCurrent->info > item)
				trailCurrent->l_link = newNode;
			else
				trailCurrent->r_link = newNode;
		}
	}

	void deleteFromTree(binaryTreeNode<Type> *p)
	{
		binaryTreeNode<Type> *current; //pointer to traverse the ree
		binaryTreeNode<Type> *trailCurrent;//pointer behinde current
		binaryTreeNode<Type> *temp;

		if (p == NULL)
			std::cout << "Error: The node to be deleted is NULL" << std::endl;
		else if (p->l_link == NULL & p->r_link == NULL)//if the node to be deleted don't have linked nodes( left and right).
		{
			temp = p;
			p = NULL;
			delete temp;
		}
		else if (p->l_link == NULL)// if the node to be deleted have only right node
		{
			temp = p;
			p = temp->r_link;
			delete temp;
		}
		else if (p->r_link == NULL)// if the node to be deleted have only left node
		{
			temp = p;
			p = temp->l_link;
			delete temp;
		}
		else// if the node to be deleted have both right and left node
		{
			current = p->l_link;
			trailCurrent = NULL;
			while (current->r_link != NULL)
			{
				trailCurrent = current;
				current = current->r_link;
			}

			p->info = current->info;
			
			if (trailCurrent == NULL)
				p->l_link = current->l_link;
			else
				trailCurrent->r_link = current->l_link;

			delete current;
		}
	}
};
