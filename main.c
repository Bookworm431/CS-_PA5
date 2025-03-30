/*
 * COP 3502C Assignment 5
 * This program is written by: Amelia Keefe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct
struct tree_node {
    int data;
    char name[31];
    struct tree_node *left;
    struct tree_node *right;
};

//function calls
int add(struct tree_node *current_ptr);
int isBalanced(struct tree_node *root);
int height(struct tree_node* node);
struct tree_node* insert(struct tree_node *root, struct tree_node *element);
struct tree_node* findNode(struct tree_node *current_ptr, char* name, int* depth);
struct tree_node* delete(struct tree_node* root, char* name, int numTickets);
struct tree_node *create_node(char* name, int numTickets);
void inorder(struct tree_node *current_ptr);
struct tree_node* parent(struct tree_node *root, struct tree_node *node);
struct tree_node* minVal(struct tree_node *root);
struct tree_node* maxVal(struct tree_node *root);
int isLeaf(struct tree_node *node);
int hasOnlyLeftChild(struct tree_node *node);
int hasOnlyRightChild(struct tree_node *node);
struct tree_node* q6(struct tree_node* root, int x);
int what(struct tree_node *root, char* name);
int numnodes(struct tree_node* root);
int findKthSmallest(struct tree_node* root, int k);

int main() {
    struct tree_node *my_root = NULL, *temp_node;
    char command[31];
    char name[31];
    int num_commands, numTickets, depth = 0;
    scanf("%d", &num_commands);
    //takes in information
    for (int i = 0; i < num_commands; i++) {
        depth = 0;
        scanf("%s", command);

        //add/buy
        if (strcmp(command, "buy") == 0) {
            scanf("%s %d", name, &numTickets);

            //see if person exists
            temp_node = findNode(my_root, name, depth);

            //update ticket count if it exists
            if (temp_node != NULL) temp_node->data += numTickets;

            //make new node
            else {
                temp_node = create_node(name, numTickets);
                my_root = insert(my_root, temp_node);
            }
            printf("%s %d %d\n", name, numTickets, height(my_root));
        }

        //use/delete
        if (strcmp(command, "use") == 0) {
            scanf("%s %d", name, &numTickets);

            //check using find
            if (findNode(my_root, name, depth) == 0) printf("%s deleted\n", name);
            else delete(my_root, name, numTickets);
        }

        //find/search
        if (strcmp(command, "find") == 0) {
            scanf("%s", name);

            //search
            temp_node = findNode(my_root, name, depth);
            if (temp_node) printf("%s %d %d\n", name, temp_node->data, depth);
            else printf("%s not found\n", name);
        }

        //mean
        if (strcmp(command, "mean_tickets") == 0) printf("%.2f\n", (add(my_root) * 1.0)/numnodes(my_root));

        //height of branches
        if (strcmp(command, "height_balance") == 0) isBalanced(my_root);

        //finding tickets before person
        if (strcmp(command, "count_before") == 0) {
            scanf("%s", name);

            //print total
            printf("%d\n", what(my_root, name));
        }
    }
    inorder(my_root);
    free(my_root);
    return 0;
}

//check if function is balanced
int isBalanced(struct tree_node *root) {
    //no nodes
    if (root == NULL) return 1;

    //calculate height
    int left_height = height(root->left);
    int right_height = height(root->right);

    //balanced
    if (left_height - right_height == 0) printf("left height = %d right height = %d balanced\n", left_height, right_height);

    //unbalanced
    else printf("left height = %d right height = %d not balanced\n", left_height, right_height);
    return 0;
}

//find height of tree
int height(struct tree_node* root) {
    //check root
    if (root == NULL) return -1;

    //find heights
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    //compare heights
    if (leftHeight > rightHeight) return 1 + leftHeight;
    return 1 + rightHeight;
}

//inorder searching
void inorder(struct tree_node *current_ptr) {
    //only traverse the node if it's not null
    if (current_ptr != NULL) {
        //go left
        inorder(current_ptr->left);

        //print the root
        printf("%d ", current_ptr->data);

        //go right
        inorder(current_ptr->right);
    }
}

//insert new struct into big struct
struct tree_node* insert(struct tree_node *root, struct tree_node *element) {
    //inserting into an empty tree
    if (root == NULL) return element;

    //element should be inserted to the right
    if (strcmp(element->name, root->name) > 0) {
        //there is a right subtree to insert the node
        if (root->right != NULL) root->right = insert(root->right, element);

        //place the node directly to the right of root
        else root->right = element;
    }

    //element should be inserted to the left
    else {
        //there is a left subtree to insert the node
        if (root->left != NULL) root->left = insert(root->left, element);

        //place the node directly to the left of root
        else root->left = element;
    }

    //return the root pointer of the updated tree
    return root;
}

//create a place for the person and tickets
struct tree_node* create_node(char* name, int numTickets) {
    //allocate space for the node, set the fields
    struct tree_node* temp = malloc(sizeof(struct tree_node));

    //check for NULL
    if (!temp) return NULL;

    //copy in info
    temp->data = numTickets;
    strcpy(temp->name, name);
    temp->left = NULL;
    temp->right = NULL;

    //return a pointer to the created node
    return temp;
}

//find out how many tickets are before a name
int what(struct tree_node *root, char* name) {
    int total = 0;
    if (root != NULL) {
        //if current name is after name
        if (strcmp(root->name, name) < 0) {
            total += root->data;

            //traverse left subtree
            total += what(root->left, name);

            //traverse right subtree
            total += what(root->right, name);
        }
        //current name is before name
        else total += what(root->left, name);
    }
    return total;
}

//adds new person
int add(struct tree_node *current_ptr) {
    if (current_ptr != NULL) return current_ptr->data + add(current_ptr->left) + add(current_ptr->right);
    return 0;
}

//returns the parent of the node pointed to by node in the tree rooted at
//root. If the node is the root of the tree, or the node doesn't exist in
//the tree, NULL will be returned
struct tree_node* parent(struct tree_node *root, struct tree_node *node) {
    //take care of NULL cases
    if (root == NULL || root == node) return NULL;

    //the root is the direct parent of node
    if (root->left == node || root->right == node) return root;

    //look for node's parent on the left side of the tree
    if (node->data < root->data) return parent(root->left, node);

    //look for node's parent on the right side of the tree
    else if (node->data > root->data) return parent(root->right, node);

    //catch other cases
    return NULL;
}

//returns a pointer to the node storing the minimum value in the tree
//with the root, root Will not work if called with an empty tree
struct tree_node* minVal(struct tree_node *root) {
    //root stores the minimal value
    if (root->left == NULL) return root;

    //the left subtree of the root stores the minimal value
    else return minVal(root->left);
}

//returns a pointer to the node storing the maximum value in the tree
//with the root, root Will not work if called with an empty tree
struct tree_node* maxVal(struct tree_node *root) {
    //root stores the maximal value
    if (root->right == NULL) return root;

    //the right subtree of the root stores the maximal value
    else return maxVal(root->right);
}

//returns 1 if node is a leaf node, 0 otherwise
int isLeaf(struct tree_node *node) {
    return (node->left == NULL && node->right == NULL);
}

//returns 1 iff node has a left child and no right child
int hasOnlyLeftChild(struct tree_node *node) {
    return (node->left!= NULL && node->right == NULL);
}

//returns 1 iff node has a right child and no left child
int hasOnlyRightChild(struct tree_node *node) {
    return (node->left== NULL && node->right != NULL);
}

//returns a pointer to a node that stores value in it in the subtree
//pointed to by current_ptr NULL is returned if no such node is found
struct tree_node* findNode(struct tree_node *current_ptr, char* name, int* depth) {
    //check input exists
    if (current_ptr == NULL) return NULL;

    //find the value at the root
    if (strcmp(current_ptr->name, name) == 0) return current_ptr;

    //increment depth
    depth++;

    //search left
    if (strcmp(name, current_ptr->name) < 0) return findNode(current_ptr->left, name, depth);

    //search right
    return findNode(current_ptr->right, name, depth);
}

//will delete the node storing value in the tree rooted at root The
//value must be present in the tree in order for this function to work
//the function returns a pointer to the root of the resulting tree
struct tree_node* delete(struct tree_node* root, char* name, int numTickets) {
    struct tree_node *delnode, *new_del_node, *save_node;
    struct tree_node *par;
    int save_val, depth = 0;

    //get a pointer to the node to delete and check if customer exists
    delnode = findNode(root, name, depth);
    if (delnode == NULL)
    {
        printf("%s not found\n", name);
        return root;
    }

    //get the parent of this node
    par = parent(root, delnode);

    //take care of the case where the node to delete is a leaf node
    //case 1
    if (isLeaf(delnode)) {
        //deleting the only node in the tree
        if (par == NULL) {
            //free the memory for the node
            free(root);
            return NULL;
        }
        //deletes the node if it's a left child
        if (strcmp(name, par->name) < 0) {
            //free the memory for the node
            free(par->left);
            par->left = NULL;
        }

        //deletes the node if it's a right child
        else {
            //free the memory for the node
            free(par->right);
            par->right = NULL;
        }
        //return the root of the new tree
        return root;
    }
    //take care of the case where the node to be deleted only has a left child
    if (hasOnlyLeftChild(delnode)) {
        //deleting the root node of the tree
        if (par == NULL) {
            save_node = delnode->left;

            //free the node to delete
            free(delnode);

            //return the new root node of the resulting tree
            return save_node;
        }
        //deletes the node if it's a left child
        if (strcmp(name, par->name) < 0) {
            //save the node to delete
            save_node = par->left;

            //readjust the parent pointer
            par->left = par->left->left;

            //free the memory for the deleted node
            free(save_node);
        }
        //deletes the node if it's a right child
        else {
            //save the node to delete
            save_node = par->right;

            //readjust the parent pointer
            par->right = par->right->left;

            //free the memory for the deleted node
            free(save_node);
        }
        //return the root of the tree after the deletion
        return root;
    }

    //takes care of the case where the deleted node only has a right child
    if (hasOnlyRightChild(delnode)) {
        //node to delete is the root node
        if (par == NULL) {
            save_node = delnode->right;
            free(delnode);
            return save_node;
        }
        //deletes the node if it is a left child
        if (strcmp(name, par->name) < 0) {
            save_node = par->left;
            par->left = par->left->right;
            free(save_node);
        }
        //deletes the node if it is a right child
        else {
            save_node = par->right;
            par->right = par->right->right;
            free(save_node);
        }
        return root;
    }
    //if your code reaches hear it means delnode has two children find the new physical node to delete
    new_del_node = maxVal(delnode->left);
    save_val = new_del_node->data;

    //now, delete the proper value
    delete(root, name, save_val);

    //restore the data to the original node to be deleted
    delnode->data = save_val;

    //print stuff
    delnode = findNode(root, name, depth);
    if (delnode) printf("%s %d %d\n", name, delnode->data, height(root));
    else printf("%s deleted\n", name);
    return root;
}

//no clue what this does
struct tree_node* q6(struct tree_node* root, int x) {
    if (root == NULL) return NULL;
    if (root->data > x) {
        struct tree_node* tmp = q6(root->left, x);
        if (tmp == NULL) {
            printf("root: %d", root->data);
            return root;
        } else {
            printf("tmp: %d", tmp->data);
            return tmp;
        }
    }
    return q6(root->right, x);
}

//returns the number of nodes in the tree pointed to by root
int numnodes(struct tree_node* root) {
    if (root == NULL) return 0;
    return 1 + numnodes(root->left) + numnodes(root->right);
}

//guaranteed that k is in between 1 and the number of nodes in the tree pointed to by root
int findKthSmallest(struct tree_node* root, int k) {
    int numNodesLeft = numnodes(root->left);
    if (numNodesLeft >= k) return findKthSmallest(root->left, k);
    else if (numNodesLeft == k-1) return root->data;
    else return findKthSmallest(root->right, k-numNodesLeft-1);
}
