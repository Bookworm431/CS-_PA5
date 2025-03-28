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
    char *name;
    struct tree_node *left;
    struct tree_node *right;
};

//function calls
//useful ones
// add(struct tree_node *current_ptr);
int find(struct tree_node *current_ptr, char* name);
struct tree_node* insert(struct tree_node *root, struct tree_node *element);

//struct tree_node* delete(struct tree_node* root, char name[], int numTickets);

struct tree_node *create_node(char* name, int numTickets);
/*void inorder(struct tree_node *current_ptr);
struct tree_node* parent(struct tree_node *root, struct tree_node *node);
struct tree_node* minVal(struct tree_node *root);
struct tree_node* maxVal(struct tree_node *root);
int isLeaf(struct tree_node *node);
int hasOnlyLeftChild(struct tree_node *node);
int hasOnlyRightChild(struct tree_node *node);
struct tree_node* findNode(struct tree_node *current_ptr, int value);
struct tree_node* q6(struct tree_node* root, int x);
void what(struct tree_node *root, int val);
int numnodes(struct tree_node* root);
int findKthSmallest(struct tree_node* root, int k);
*/
int main() {
    struct tree_node *my_root=NULL, *temp_node;
    int done = 0, val, q6data;
    char command[31];
    char name[31];
    int num_commands, numTickets;
    scanf("%d", &num_commands);
    //takes in information
    for (int i = 0; i < num_commands; i++) {
        scanf("%s", command);
        //add/buy
        if (strcmp(command, "buy") == 0) {
            scanf("%s %d", name, &numTickets);

            //see if person exists
            temp_node = find(my_root, name);

            //update ticket count
            if (temp_node != NULL)
                temp_node->data += numTickets;
            else {
                temp_node = create_node(name, numTickets);
                my_root = insert(my_root, temp_node);
            }
        }

        /*
        //use/delete
        if (strcmp(command, "use") == 0) {
            scanf("%s %d", name, &numTickets);
            if (!find(my_root, name)) printf("%s not found\n", name);
            else my_root = delete(my_root, name, numTickets);
        }
        //find/search
        if (strcmp(command, "find") == 0) {
            printf("What value would you like to search for?\n");
            scanf("%d", &val);
            if (find(my_root, val)) printf(" Found %d in the tree\n", val);
            else printf(" Did not find %d in the tree\n", val);
        }
        //mean
        if (strcmp(command, "mean_tickets") == 0) printf("%f\n", add(my_root));
        
        if (strcmp(command, "height_balance") == 0) {
            //print the resulting tree
            printf("Here is an inorder traversal of your tree: ");
            inorder(my_root);
            printf("\n");
        }
        
        if (strcmp(command, "count_before") == 0) {
            //print the resulting tree
            printf("enter a value for q6: ");
            scanf("%d", &q6data);
            printf("Q6: ");
            q6(my_root, q6data );
            printf("\n");
        }*/
    }
    /*
    printf("Testing what function\n\n");
    what(my_root, 7);
    printf("\n");
    */
    /*int rank;
    printf("Which ranked item would you like to find?\n");
    scanf("%d", &rank);
    //printf("The item is %d\n", findKthSmallest(my_root, rank));
    system("PAUSE");
*/
    return 0;
}
/*
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
*/
//insert new struct into big struct
struct tree_node* insert(struct tree_node *root, struct tree_node *element) {
    //inserting into an empty tree
    if (root == NULL){
        //name, numTickets, height in tree
        printf("%s %d %d\n", element->name, element->data, element->data);
        return element;
    }
    else {
        printf("%s %d %d\n", element->name, element->data, element->data);

        //element should be inserted to the right
        if (element->data > root->data) {
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
}

//create a place for the person and tickets
struct tree_node* create_node(char* name, int numTickets) {
    //allocate space for the node, set the fields
    struct tree_node* temp;
    temp = (struct tree_node*)malloc(sizeof(struct tree_node));
    temp->data = numTickets;
    temp->name = name;
    temp->left = NULL;
    temp->right = NULL;

    //return a pointer to the created node
    return temp;
}

int find(struct tree_node *current_ptr, char* name) {
    //check if there are nodes in the tree
    if (current_ptr != NULL) {
        //found the value at the root
        if (strcmp(current_ptr->name, name) == 0) return 1;
        //search to the left
        if (strcmp(name, current_ptr->name) < 0) return find(current_ptr->left, name);
        //or search to the right
        else return find(current_ptr->right, name);
    }
    else return NULL;
}
/*
//finds what came before certain name
//MODIFY FOR TICKETSSSSSSSSS
void what(struct tree_node *root, int val) {
    if (root != NULL) {
        if (root->data > val) printf("%d ", root->data+val);
        if (root->data%val > 5) what(root->left, val+3);
        else what(root->right, val+4);
    }
}

//adds new person
int add(struct tree_node *current_ptr) {
    if (current_ptr != NULL) return current_ptr->+add(current_ptr->left)+add(current_ptr->right);
    else return 0;
}

//returns the parent of the node pointed to by node in the tree rooted at
//root. If the node is the root of the tree, or the node doesn't exist in
//the tree, NULL will be returned
struct tree_node* parent(struct tree_node *root, struct tree_node *node) {
    //take care of NULL cases
    if (root == NULL || root == node) return NULL;
    //the root is the direct parent of node
    if (root->left == node || root->right == node) return root;
    //look for node's parent in the left side of the tree
    if (node->data < root->data) return parent(root->left, node);
    //look for node's parent in the right side of the tree
    else if (node->data > root->data) return parent(root->right, node);
    //catch any other extraneous cases
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
struct tree_node* findNode(struct tree_node *current_ptr, int value) {
    //check if there are nodes in the tree
    if (current_ptr != NULL) {
        //found the value at the root
        if (current_ptr->data == value) return current_ptr;
        //search to the left
        if (value < current_ptr->data)return findNode(current_ptr->left, value);
        //orsearch to the right
        else return findNode(current_ptr->right, value);
    }
    //no node found
    else return NULL;
}

//will delete the node storing value in the tree rooted at root The
//value must be present in the tree in order for this function to work
//the function returns a pointer to the root of the resulting tree
struct tree_node* delete(struct tree_node* root, char name[], int numTickets) {
    struct tree_node *delnode, *new_del_node, *save_node;
    struct tree_node *par;
    int save_val;
    //get a pointer to the node to delete
    delnode = findNode(root, name);
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
        if (name < par->data) {
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
        if (value < par->data) {
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
        if (value < par->data) {
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
    new_del_node = minVal(delnode->right);
    save_val = new_del_node->data;

    //now, delete the proper value
    delete(root, save_val);

    //restore the data to the original node to be deleted
    delnode->data = save_val;
    return root;
}
*/

/*** NEW FUNCTION ADDED - EDIT AND PUT IN FRAMEWORK ***/
/*
struct tree_node* q6(struct tree_node* root, int x) {
    if (root == NULL) return NULL;
    if (root->data > x) {
        struct treenode* tmp = q6(root->left, x);
        if (tmp == NULL)
        {
            printf("root: %d", root->data);
            return root;
        }
        else
        {
            printf("tmp: %d", tmp);
            return tmp;
        }
    }
    else return q6(root->right, x);
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
*/
