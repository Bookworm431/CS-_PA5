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
    struct tree_node* left;
    struct tree_node* right;
};

//function calls
int add(struct tree_node* current_ptr);
void freeTree(struct tree_node* my_root);
int isBalanced(struct tree_node* root);
int height(struct tree_node* node);
struct tree_node* insert(struct tree_node* root, struct tree_node* element);
struct tree_node* findNode(struct tree_node* current_ptr, char name[], int* depth);
struct tree_node* delete(struct tree_node* root, char name[]);
struct tree_node* create_node(char name[], int numTickets);
void inorder(struct tree_node* current_ptr);
struct tree_node* parent(struct tree_node* root, struct tree_node* node);
struct tree_node* minVal(struct tree_node* root);
struct tree_node* maxVal(struct tree_node* root);
int isLeaf(struct tree_node* node);
int hasOnlyLeftChild(struct tree_node* node);
int hasOnlyRightChild(struct tree_node* node);
int what(struct tree_node* root, char name[]);
int numnodes(struct tree_node* root);

int main() {
    struct tree_node *my_root = NULL, *temp_node;
    char command[31];
    char name[31];
    int num_commands, numTickets, depth;
    scanf("%d", &num_commands);
    //takes in information
    for (int i = 0; i < num_commands; i++) {
        depth = 0;
        scanf("%s", command);

        //add/buy
        if (strcmp(command, "buy") == 0) {
            scanf("%s %d", name, &numTickets);

            //see if person exists
            temp_node = findNode(my_root, name, &depth);

            //update ticket count if it exists
            if (temp_node != NULL) temp_node->data += numTickets;

            //make new node
            else {
                temp_node = create_node(name, numTickets);
                my_root = insert(my_root, temp_node);
            }
            printf("%s %d %d\n", name, temp_node->data, depth);
        }

        //use/delete
        if (strcmp(command, "use") == 0) {
            scanf("%s %d", name, &numTickets);

            //see if person exists
            temp_node = findNode(my_root, name, &depth);

            //check using find
            if (temp_node != NULL) temp_node->data -= numTickets;
            else printf("%s not found\n", name);

            //if (temp_node->data <= 0) delete(my_root, name);
            printf("%s %d %d\n", name, temp_node->data, depth);
        }

        //find/search
        if (strcmp(command, "find") == 0) {
            scanf("%s", name);

            //search
            temp_node = findNode(my_root, name, &depth);
            if (temp_node != NULL) printf("%s %d %d\n", name, temp_node->data, depth);
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
    freeTree(my_root);
    return 0;
}

//free my_root
void freeTree(struct tree_node* my_root) {
    if (my_root == NULL) return;
    freeTree(my_root->left);
    freeTree(my_root->right);
    free(my_root);
}

//returns a pointer to a node that stores value in it in the subtree
//pointed to by current_ptr NULL is returned if no such node is found
struct tree_node* findNode(struct tree_node* current_ptr, char name[], int* depth) {
    //check input exists
    if (current_ptr == NULL) return NULL;

    //find the value at the root
    if (strcmp(current_ptr->name, name) == 0) return current_ptr;

    //increment depth
    (*depth)++;

    //search left
    if (strcmp(current_ptr->name, name) > 0) return findNode(current_ptr->left, name, depth);

    //search right
    return findNode(current_ptr->right, name, depth);
}

//check if function is balanced
int isBalanced(struct tree_node* root) {
    //no nodes
    if (root == NULL) return -1;

    //calculate height
    int left_height = height(root->left);
    int right_height = height(root->right);

    //balanced
    if (abs(left_height - right_height) == 0) printf("left height = %d right height = %d balanced\n", left_height, right_height);

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
void inorder(struct tree_node* current_ptr) {
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
struct tree_node* insert(struct tree_node* root, struct tree_node* element) {
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
struct tree_node* create_node(char name[], int numTickets) {
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
int what(struct tree_node* root, char name[]) {
    if (root == NULL) return 0;

    //add up to name
    if (strcmp(root->name, name) <= 0) return root->data + what(root->left, name) + what(root->right, name);
    return what(root->left, name);
}


//adds new person
int add(struct tree_node* current_ptr) {
    if (current_ptr != NULL) return current_ptr->data + add(current_ptr->left) + add(current_ptr->right);
    return 0;
}

//returns the parent of the node pointed to by node in the tree rooted at
//root. If the node is the root of the tree, or the node doesn't exist in
//the tree, NULL will be returned
struct tree_node* parent(struct tree_node* root, struct tree_node* node) {
    //take care of NULL cases
    if (root == NULL || strcmp(root, node) == 0) return NULL;

    //the root is the direct parent of node
    if ((strcmp(root->left, node) == 0) || (strcmp(root->right, node) == 0)) return root;

    //look for node's parent on the left side of the tree
    if (strcmp(node->name, root->name) < 0) return parent(root->left, node);

    //look for node's parent on the right side of the tree
    else if (strcmp(node->name, root->name) > 0) return parent(root->right, node);

    //catch other cases
    return NULL;
}

//returns a pointer to the node storing the minimum value in the tree
//with the root, root Will not work if called with an empty tree
struct tree_node* minVal(struct tree_node* root) {
    //root stores the minimal value
    if (root->left == NULL) return root;

    //the left subtree of the root stores the minimal value
    else return minVal(root->left);
}

//returns a pointer to the node storing the maximum value in the tree
//with the root, root Will not work if called with an empty tree
struct tree_node* maxVal(struct tree_node* root) {
    //root stores the maximal value
    if (root->right == NULL) return root;

    //the right subtree of the root stores the maximal value
    return maxVal(root->right);
}

//returns 1 if node is a leaf node, 0 otherwise
int isLeaf(struct tree_node* node) {
    return (node->left == NULL && node->right == NULL);
}

//returns 1 iff node has a left child and no right child
int hasOnlyLeftChild(struct tree_node* node) {
    return (node->left != NULL && node->right == NULL);
}

//returns 1 iff node has a right child and no left child
int hasOnlyRightChild(struct tree_node* node) {
    return (node->left == NULL && node->right != NULL);
}

//will delete the node storing value in the tree rooted at root The
//value must be present in the tree in order for this function to work
//the function returns a pointer to the root of the resulting tree
struct tree_node* delete(struct tree_node* root, char name[]) {
    struct tree_node *delnode, *new_del_node, *save_node;
    struct tree_node *par;
    int save_val, depth = 0;
    char save_name[31];

    //pointer to node to delete
    delnode = findNode(root, name, &depth);

    //parent
    par = parent(root, delnode);

    //node to delete is a leaf node
    if (isLeaf(delnode)) {
        //deleting the only node in the tree
        if (par == NULL) {
            //free
            free(root);
            return NULL;
        }

        //left child
        if (strcmp(name, par->name) < 0) {
            //free
            free(par->left);
            par->left = NULL;
        }

        //right child
        else {
            //free
            free(par->right);
            par->right = NULL;
        }
        //return root
        return root;
    }

    //only has a left child
    if (hasOnlyLeftChild(delnode)) {
        //deleting root node of the tree
        if (par == NULL) {
            save_node = delnode->left;

            //free node to delete & return new root
            free(delnode);
            return save_node;
        }

        //deletes the node if it's a left child
        if (strcmp(name, par->name) < 0) {
            //save node to delete
            save_node = par->left;
            //readjust parent pointer
            par->left = par->left->left;
            //free memory of deleted node
            free(save_node);
        }

        //deletes the node if it's a right child
        else {
            //save node to delete
            save_node = par->right;
            //readjust parent pointer
            par->right = par->right->left;
            //free deleted node memory
            free(save_node);
        }
        //return root after deletion
        return root;
    }

    //deleted node only has a right child
    if (hasOnlyRightChild(delnode)) {
        //delete root node
        if (par == NULL) {
            save_node = delnode->right;
            free(delnode);
            return save_node;
        }

        //left child node deletion
        if (strcmp(name, par->name) < 0) {
            save_node = par->left;
            par->left = par->left->right;
            free(save_node);
        }

        //right child node deletion
        else {
            save_node = par->right;
            par->right = par->right->right;
            free(save_node);
        }
        return root;
    }

    //delnode has 2 kids
    //find new node to delete
    new_del_node = maxVal(delnode->left);
    strcpy(save_name, new_del_node->name);

    //delete proper value
    delete(root, save_name);

    //restore the data to the original node to be deleted
    strcpy(delnode->name, save_name);
    return root;
}

//returns the number of nodes in the tree pointed to by root
int numnodes(struct tree_node* root) {
    if (root == NULL) return 0;
    return 1 + numnodes(root->left) + numnodes(root->right);
}
