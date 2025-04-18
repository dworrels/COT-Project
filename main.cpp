#include <iostream>
#include <string>
#include <cstdlib> //random ... rand() % 100 == picks a number out of 100. 0-99
#include <sstream>
#include <vector>


using namespace std; 

// States
enum class sType{
    START0,
    START1,
    START2,
    QUESTION0,
    QUESTION1,
    QUESTION2,
    QUESTION3,
    QUESTION4,
    
};

// struct stateNode{
//     sType state;
//     // old
//     //string response;
//     // new
//     vector <string> response;
//     string keyword;
//     float probability;
//     vector<stateNode*> children;

//     stateNode(sType s) : state(s), response(), probability(rand() % 100), keyword(k)  {}
    
// };

struct stateNode{
    sType state;
    // old
    //string response;
    // new
    int key;
    vector <string> response;
    // string keyword;
    vector <string> keyWords;
    float probability;
    stateNode *left;
    stateNode *right;
    vector<stateNode*> children;

    stateNode(int k, sType s) : key(k), state(s) , left(nullptr) , right(nullptr)  {}
    
};

stateNode *root;

// stateNode* tree(){

//     // stateNode* start0 = new stateNode(sType::START0);
//     // vector<string> response ={"hi", "hello", "hey"};
//     // for(int i=0; i<response.size(); i++){
//     //     start0->response.push_back(response[i])
//     //     return start0;
//     // }

// };

vector<string> keyWords = {"start" , "restart" , "begin","order","order number", "update"};



// void startProccess()
// {
//     //maybe we do not need the key since we can have start as the key
//     // stateNode *newNode = new stateNode(1, sType:: START0, "start");

//    //we are going to want to just just call this function

//     root = addToTree(root,1);

//     stateNode *find = findNode(1);

//     find->response.push_back("Hello Welcome");
//     find->response.push_back("Hi, welcome! ");
//     find->response.push_back("Hello welcome to this chatbot! ");

//     find->keyWords.push_back("start");
//     find->keyWords.push_back("restart");
//     find->keyWords.push_back("begin");


//     root = addToTree(root,2);

//     stateNode *find = findNode(2);

//     find->response.push_back("Hello you need help , what do you need help with? ");
//     find->response.push_back("Do you need help to know when your order is going to arrive? ");
//     find->response.push_back("What is your order number? ");

//     find->keyWords.push_back("Order");
//     find->keyWords.push_back("order number");
//     find->keyWords.push_back("update");


// }

// stateNode *findNode(int key)
// {
//     return FindNodeHelper(root, key);
// }

/*
    helps find the Node for findNode and is called by findNode

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

stateNode *findNode(int key)
{
    return FindNodeHelper(root, key);
}

stateNode *addToTree(stateNode *root, int x)
{
    if(root == nullptr)
    {
        return new stateNode(x,sType::START0);
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

// Old tree
/*stateNode* tree(){
    stateNode* start0 = new stateNode(sType::START0, "hi");
    stateNode* start1 = new stateNode(sType::START1, "hey");
    stateNode* start2 = new stateNode(sType::START2, "hello");
    stateNode* question0 = new stateNode(sType::QUESTION0, "What's your question?");
    stateNode* question1 = new stateNode(sType::QUESTION1, "Sure, what's up?");
    stateNode* question2 = new stateNode(sType::QUESTION2, "How can I help you?");
    stateNode* question3 = new stateNode(sType::QUESTION3, "How can I help you?");
    stateNode* question4 = new stateNode(sType::QUESTION4, "How can I help you?");

    // puts each question state into a vector
    vector<stateNode*> questions = {question0, question1, question2, question3, question4};

    
    // assighn random question state to each start states
     for(int i=0; i<2; i++){
        int random = rand() % questions.size();
        start0->children.push_back(questions[random]);
    }
    for(int i=0; i<2; i++){
        int random = rand() % questions.size();
        start1->children.push_back(questions[random]);
    }
    for(int i=0; i<2; i++){
        int random = rand() % questions.size();
        start2->children.push_back(questions[random]);
    }

}
*/


// state get_next(state currentState, string input){
    
// }

//     for(int i=0, i<2, i++){
//         int random = rand() % questions.size();
//         start0->children.push_back(questions[random]);
//     }


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

//function that takes in the current state node and gets random probability for the 3 responses and uses if else if statements to print which node->presonse to print.
void out_put(stateNode *node)
{
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

//possibly can have a hashmap to help find us the node we are going to be looking for better and faster. 
stateNode* word_bank(vector<string> userInput)
{   
    string keyWord;
    bool keyWordFound = false;    

    for(size_t i = 0; i < userInput.size() && keyWordFound == false; i++) 
        {
            for(size_t j = 0; j < keyWords.size(); j++)
            {
                if(userInput[i] == keyWords[j])
                {
                    keyWord = keyWords[j];
                    keyWordFound = true;
                    break;
                    
                }

            }
        }

    //now that we got the keWord extracted we are going to have to find the node it is connected with. 
    
    if(keyWordFound == true)
    {
    stateNode *foundNode = findKeyWordState(root, keyWord);
    return foundNode;

    }
    else
    {
        cout << "Please re enter you statemenet I got lost trying to understand it.... my creators haven't developed that far. " <<  endl;
        return nullptr;
    }


    
}


void startProccess()
{
    //maybe we do not need the key since we can have start as the key
    // stateNode *newNode = new stateNode(1, sType:: START0, "start");

   //we are going to want to just just call this function

   vector<string> keyWords = {"start" , "restart" , "begin", "order","order number", "update"};


    root = addToTree(root,1);

    stateNode *find = findNode(1);

    find->response.push_back("Hello Welcome");
    find->response.push_back("Hi, welcome! ");
    find->response.push_back("Hello welcome to this chatbot! ");

    find->keyWords.push_back("start");
    find->keyWords.push_back("restart");
    find->keyWords.push_back("begin");


    //secound state we are going to add to the function. 
    root = addToTree(root,2);
    
    find = findNode(2);

    find->response.push_back("Hello you need help , what do you need help with? ");
    find->response.push_back("Do you need help to know when your order is going to arrive? ");
    find->response.push_back("What is your order number? ");

    find->keyWords.push_back("order");
    find->keyWords.push_back("order number");
    find->keyWords.push_back("update");



}

int main()
{


    string userInput; 
    
    while(userInput != "q")
    {
        stateNode *found = nullptr;
        startProccess();


        cout << "Please enter your statement: ";
        
        //cin >> userInput; 
        getline(cin, userInput);
        
        //curently has all the words extracted from the user. Now we got to compare the words for keyWords and from there will move to a state that has certain outputs
        vector<string> UserWords = Extract_Word(userInput);

        //get's the keyword associated with the users input and from there we are going to be moving nodes.
        found = word_bank(UserWords);

        if(found != nullptr)
        {
            out_put(found);
        }
       





        

    }


}