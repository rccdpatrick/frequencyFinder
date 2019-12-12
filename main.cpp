/*
 * Text Finder
 *  A Program Created to Find the Frequency of a Character or Word
 *  Will use a Text File for Indexing
 * 
 * Created By: Patrick Saade
 * December 11, 2019
 * CIS17C
 */
#include <iostream>  //Input Output for C++ Program
#include <vector>    //Using Vectors in Program
#include <fstream>   //Used to Read a Text File

using namespace std; //For the Use of cin and cout

vector< int > locationVec;  //Vector that is Used to Store All Matches

/*
 * Structure node
 *  Declarations of *left and *right
 *  'value' is the Value of the node
 */
struct node {
    int value;
    struct node *left, *right;
};

/*
 * Creates a new Binary Search Tree (BST) Node
 */
struct node *newNode(int value) {
    struct node *temp = (struct node *) malloc(sizeof (struct node));
    temp->value = value;
    temp->left = temp -> right = NULL;
    return temp;
}

/*
 * Function to Insert a New node With Parameter 'value'
 */
struct node* insert(struct node*& node, int value) {
    /*
     * Check if the Tree is Empty
     *  If So, Initialize a New node
     */
    if (node == NULL) return newNode(value);

    /*
     * Is not Empty, Traverse Down the Tree
     */
    if (value < node -> value) {
        node->left = insert(node->left, value);
    } else if (value > node -> value) {
        node->right = insert(node->right, value);
    }

    /* 
     * Return the node Pointer
     */
    return node;
}

/*
 * Traversal of BST
 *  Will Find All Values of the Tree Above 0
 *  Will Print Those Values
 *  The Reason Being, Fail Location Values are Negative and Pass Location Values are Positive
 *  Will Insert Positive Values (The Matches) into the Vector
 */
void getPassLocation(struct node *root) {
    if (root != NULL) {
        getPassLocation(root -> left);
        if (root -> value > 0) {
            locationVec.push_back(root -> value); //If There is a Match, Push it into the Vector
        }
        getPassLocation(root -> right);
    }
}

/*
 * Program Driver
 */
int main() {
    /*
     * Variable Declarations
     *  keyWord         -   What Word Will be Searched
     *  fileLocation    -   Path of File
     *  word            -   Word Traversal When in FileStream
     *  wordLocation    -   Location of the Word in the Text File (By Word, not Letter)
     *  passFrequency   -   The Amount of Times the 'keyWord' Matched With 'word'
     *  failFrequency   -   The Amount of Times the 'keyWord' did not Match With 'word'
     */
    string keyWord, fileLocation, word;
    int wordLocation = 0, passFrequency = 0, failFrequency = 0;

    /*
     * Declare an Input File Stream
     */
    ifstream inFile;

    /*
     * Create root of Tree
     *  Declare it NULL
     */
    struct node *root = NULL;
    root = insert(root, 0);

    /*
     * User Input Prompt
     */
    cout << "Where is your text file location?" << endl;
    cin >> fileLocation;
    cout << endl << "What word (or character) that you want to find the frequency for in your text file?" << endl;
    cin >> keyWord;

    /*
     * Open the File Stream
     *  Otherwise Terminate With an Error
     */
    inFile.open(fileLocation);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1);
    }

    /*
     * Traverse the Text File
     *  Will Find the Frequency of a Word Given by the User
     */
    while (inFile >> word) {
        /*
         * Content Insertion
         *  wordLocation Increments for Every Word to Match With Text File
         *  Words that Match go to the Right Side
         *  Words that do not Match go to the Left Side (Due to Making Negative)
         *  This Allows for Organization of Locations and to Distinguish Between the Passes and Fails
         */
        if (word == keyWord) {
            insert(root, wordLocation); //Insert the Location to the Right Side of Tree Since Positive and Greater than 0
            passFrequency++; //Increment Up if the 'word' Matches 'keyWord'
        } else {
            insert(root, -1 * wordLocation); //Insert the Location to the Left Side of Tree Since Negative and Lesser than 0
            failFrequency++; //Increment Up if the 'word' does not Natch 'keyWord'
        }
        wordLocation++; //Increment 'wordLocation' to be Parallel with the 'word' Variable
    }

    /*
     * Close the File Stream
     */
    inFile.close();

    /*
     * Final User Prompt
     */
    cout << endl << endl;
    cout << endl << "The Execution of Finding the Word Frequency and Location is Complete!";
    cout << endl << "The word that you chose, '" << keyWord << "', has occurred '" << passFrequency << "' time(s) in your text file.";
    cout << endl << "The word locations are the following (Locations by Word, First Word is 0):\t";
    
    /*
     * Used to Print the Locations of the Matched Words
     *  Will Use getPassLocation to Traverse Tree
     *  Will Then Insert into the Vector     
     *  Then a For Loop Created to Print the Vector
     */
    getPassLocation(root);
    for (int count = 0; count < locationVec.size(); count++) {
        cout << locationVec[count] << "  ";
    }

    cout << endl << endl << "Thank you for using this program. Use it again if necessary!";

    /*
     * End Program Safely
     */
    return 0;
}
