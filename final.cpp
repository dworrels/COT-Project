#include <iostream>
#include <string>
#include <cstdlib> //random ... rand() % 100 == picks a number out of 100. 0-99
#include <sstream>
#include <vector>


using namespace std; 

/*
struct that makes the state nodes
each state/node contains:

contains a key (used for BST)
contains vector for response (each state/node has unique responses)
contains a vector for keyWords (each state/node has unique keywords that correspond to it)
left and right pointers are used for BST
*/
struct stateNode{

    int key;
    vector <string> response;
    vector <string> keyWords;
    stateNode *left;
    stateNode *right;

    //constructor used to make the node.
    stateNode(int k) : key(k), left(nullptr) , right(nullptr)  {}
    
};

//declares global variables. Node that is the root , and vector keyWords that stores all the keywords in it. 
stateNode *root ;
vector<string> keyWords = {"start" , "restart" , "begin", "order","order number", "update", "cancel" , "return" , "refund", "yes" , "no"};

/*
helper function to find a given stateNode given the key value
*/
stateNode *FindNodeHelper(stateNode *root, int x)
{
    if(root == nullptr)
    {
        return nullptr;
    }

    if(root->key == x)
    {
        return root;
    }

    //greater than , must search the left tree
    if(root->key > x)
    {
        return FindNodeHelper(root->left, x);
    }
    else
    {
        return FindNodeHelper(root->right, x);
    }

}

//function that will be given a key and will call its helper to find the specific node/state via the key.
stateNode *findNode(int key)
{
    return FindNodeHelper(root, key);
}

//Will add a node/state to the tree with a given key value
stateNode *addToTree(stateNode *root, int x)
{
    if(root == nullptr)
    {
        return new stateNode(x);
    }

    //greater than , must search the left tree
    if(root->key > x)
    {
        root->left = addToTree(root->left, x);
    }
    else
    {
        root->right = addToTree(root->right, x);
    }

    return root;

}

//going to search through the whole tree trying to find the node with the current keyword
stateNode *findKeyWordState(stateNode *current, string keyWord)
{
    //base case 
    if(current == nullptr)
    {
        return nullptr;
    }

    //we have muitple keywords that we can check , want to check them all.
    for(string key : current->keyWords)
    {
        if(key == keyWord)
        {
            return current;
        }

    }

    //recursivly calls itself checking for the keyword.
    stateNode *right = findKeyWordState(current->right,keyWord);

    if(right != nullptr)
    {
        return right;
    }

    return findKeyWordState(current->left,keyWord);
    
    //we are going to want to search the tree. inOrder
    
    findKeyWordState(current->left , keyWord);

    findKeyWordState(current->right,keyWord);


    //wont ever occur but for bug purposes
    return nullptr;

}

/*
This function here is going to get the user input as a string and make a vector that stores each word inside the input as a string by itself
After it performs this action it is going to return it as a vector.
*/
vector<string> Extract_Word(string userInput)
{
    //we need to get seperate words for each of these. //Hello please fix my ORDER ... ORDER IS a keyword and will take you to the state of ORDER where it has other options.

    stringstream ss(userInput);

    string currentWord;

    vector<string> indivdiualWords;

    while(ss >> currentWord)
    {
        for (size_t i = 0; i < currentWord.length(); i++){
            currentWord[i] = currentWord[i];
        }

        indivdiualWords.push_back(currentWord);
    }

    return indivdiualWords;
    
    
}

/*
function that takes in the current state node we are at
randomly outputs 1 of the 3 response associated / stored in the current state node
*/
void out_put(stateNode *node)
{
    //generating numbers out of 100 to get probability for what output we are going to get. 
    int prob_response1 = rand() % 100;

    int prob_response2 = rand() % 100;

    // int prob_response3 = rand() % 100;
    
    if(prob_response1 > 75)
    {
        cout << node->response.at(0);
    }
    else if (prob_response2 > 60)
    {
        cout << node->response.at(1);
    }
    else
    {
          cout << node->response.at(2);
    }


        }



/*
word_bank function
this function helps us look through the userInputs string that was modified into a vector and see if any of the words in there match any keywords
*/
stateNode* word_bank(vector<string> userInput)
{   

    string keyWord;
    bool keyWordFound = false;    
    bool isDigit = false;

    //searchs the userInput vector and the keywords vector and looks for a match.
    for(size_t i = 0; i < userInput.size() && keyWordFound == false && isDigit == false; i++) 
        {
            for(size_t j = 0; j < keyWords.size(); j++)
            {
                if(userInput[i] == keyWords[j])
                {
                    //if there is a match copy the keyword and change the bool to true and break out the loop
                    keyWord = keyWords[j];
                    keyWordFound = true;
                    break;
                    
                }


            }
        }

    //now that we got the keWord extracted we are going to have to find the node it is connected with. 
    if(keyWordFound == true)
    {
    //finds the node and returns the node
    stateNode *foundNode = findKeyWordState(root, keyWord);
    return foundNode;
    }

    //if keyword was never found , lets check to see if it was an order number.
    if(keyWordFound == false)
    {
        for(string each: userInput)
        {
            for(char characters : each)
            {
                if(isdigit(characters) && isDigit == false)
                {
                    isDigit = true;
                    break;

                }
            }
        }
    }

    //if the userInput contains a digit , we are going to assume an order number was entered and are going to go to that state that handles order numbers.
    if(isDigit == true)
    {
        stateNode *digitNode = findNode(4);
        return digitNode;
    }

    //if both cases above failed , no order number and no keyword we are going to output this. 
    if(keyWordFound == false && isDigit == false)
    {
        cout << "Please re enter you statemenet I got lost trying to understand it.... my creators haven't developed that far. " <<  endl;
        return nullptr;
    }
    return nullptr;

}

/*
startProccess
this code function below basically sets up the states we are going to be using throughout the code. 
Each "state" is represented by a node. 
In order to transfer from each state to another state it will need a keyword.
Each state/node has 3 keywords associated with it and 3 responses associated with it. And both are stored in vectors
*/

void startProccess()
{
    
    root = addToTree(root,1);

    stateNode *find = findNode(1);

    find->response.push_back("Hello Welcome \n");
    find->response.push_back("Hi, welcome! \n");
    find->response.push_back("Hello welcome to this chatbot! \n");

    find->keyWords.push_back("start");
    find->keyWords.push_back("restart");
    find->keyWords.push_back("begin");


    //secound state we are going to add to the function. 
    root = addToTree(root,2);
    
    find = findNode(2);

    find->response.push_back("Hello you need help , what do you need help with? \n");
    find->response.push_back("Do you need help to know when your order is going to arrive? \n");
    find->response.push_back("What is your order number? \n");

    find->keyWords.push_back("order");
    find->keyWords.push_back("order number");
    find->keyWords.push_back("update");

    root = addToTree(root,3);

    find = findNode(3);

    find->response.push_back("Just to confirm you want to cancel your order? \n");
    find->response.push_back("Do you want to return your order? \n");
    find->response.push_back("Sorry the order has already shipped and we cannot cancel the order. Just return it for a full refund! \n");

    find->keyWords.push_back("cancel");
    find->keyWords.push_back("return");
    find->keyWords.push_back("refund");

    root = addToTree(root,4);

    find = findNode(4);

    find->keyWords.push_back("digit");
    find->response.push_back("Double check that is your correct order number \n");
    find->response.push_back("This order has shipped, anymore questions? \n");
    find->response.push_back("Do you want me to cancel this order? ");

    root = addToTree(root,5);

    find = findNode(5);

    find->response.push_back("Okay I just canceled your order , if there was a mistake please retype start \n");
    find->response.push_back("Okay to return it we just emailed you instructions on how to do so. If there was a mistake retype start \n");
    find->response.push_back("We won't / can't cancel your order / return it at this time , please try again later \n");

    find->keyWords.push_back("yes");
    find->keyWords.push_back("no");




}

#ifndef MONTE

int main()
{
    //this here will declare and initalize all the states and the responses for each state.
    startProccess();

    //finds the start node and will output response using the out_put helper function
    stateNode *begin = findNode(1);

    out_put(begin);

    //this is what we are going to read from the user. 
    string userInput; 


    //q is the key word to quit while loop
    while(userInput != "q")
    {
        //default
        stateNode *found = nullptr;

        //prompty for user.
        cout << " \nPlease enter your statement: ";
        
        //reads user input
        getline(cin, userInput);
        
        //curently has all the words extracted from the user. Now we got to compare the words for keyWords and from there will move to a state that has certain keyword
        vector<string> UserWords = Extract_Word(userInput);

        //get's the keyword associated with the users input and from there we are going to be moving nodes. If no keyword we are going to have a promt for a user
        found = word_bank(UserWords);

        
        if(found != nullptr)
        {
            out_put(found);
        }
       

    }


}

#endif



