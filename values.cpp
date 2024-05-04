#include<iostream>  //for cin,cout,endl
#include<vector>    //for vector
#include<string>    //for string
#include<windows.h> //for sleep()
using namespace std ; 

//Function Prototypes
 bool expressionevaluation(vector<char>variables , vector<int>values ,vector<char> result); 
 void insertvalues(vector<char>& v, vector<char>& variables, vector<int>& values);
 vector<char> infixtopostfix(string str);
 bool valid(string &str);
 bool isoperator(char ch);
 bool isnum(char ch) ;
 //function to calculate power
 int integerPower(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}


//function to display menu
int main()
{
    
    int choice ;
    do{
    vector<char> variables , postfix_expression;
    vector<int> values ;
    string str;
    cout << endl << "Expression conversion and evaluation Tool " << endl ;
    cout << endl <<endl<<"      1) Enter Expression " << endl << "      2) Exit";
    cout << endl << "      Enter your choice : ";
    cin>>choice ;

        switch (choice)
        {
            case 1 :  cout << endl << endl << "         ******* Rules for inserting expression ******* " << endl ;
                      cout << endl << "1) Insert a infix expression with single alphabet for a single value."<<endl<< "   - Two adjecent Alphabets will be taken as (First_alphabet * Second_alphabet)" << endl << "2) There should not be closing parenthesis ')' after an operator and opening parenthesis '(' before an operator" << endl << "3) Expression should not start and end with operator" << endl << "4) TWo adjecent Operators are not Valid" << endl << "5) Avoid including spaces "<< endl;
                      
                      cout << endl <<  "Enter Infix expression to evaluate: ";
                      while (true) {
                         cin >> str;
                          if (valid(str)) {
                              break;
                          } else {
                              cout <<  endl  <<  "Enter a valid Expression: ";
                          }
                      }
                      break;
            case 2 : string a = "***********  Exiting  ***********";
                    for(char ch : a)
                    {
                        cout<<ch;
                        Sleep(100);
                    }
        }
        if(choice != 2)
        {
            cout << endl << "INFIX Expression : " << str << endl;
            postfix_expression = infixtopostfix(str) ;
            cout << endl << "     ---- Inserting values of variables ----" << endl ;
            Sleep(1000);
            insertvalue :
            insertvalues(postfix_expression , variables , values) ;
            cout << endl << "     ---- Evaluating Expression ----" << endl ;
            Sleep(1000);
            if(expressionevaluation(variables , values , postfix_expression) )
            {
                cout << endl << "     ---- Expression Evaluated Successfully ----" << endl ;
            }
            else 
            {
                cout << endl << "     ---- Expression Evaluation Failed ----" << endl ;
                goto insertvalue ;
            }
                
        }
    }

    while(choice != 2);
    
    return 0;
}

//function to check if a character is an alphabet
bool isnum(char ch) {
    return (ch >= '1' && ch <= '9');
}
//function to check if a character is an operator
bool isoperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
}


//function to check if a string is a valid expression
bool valid(string &str) 
{
    if( ( (!isnum(str[0])) && str[0] != '(' ) || ( (!isnum(str[str.length()-1])) && str[str.length()-1] != ')' ))
    {
        cout <<  endl  <<  "Expression should start and end with valid variables";
        return false;
    }
    for(int i = 0; i < str.length() - 1; i++)
    {
        while(isnum(str[i])) i++; 
        if ( isoperator(str[i]) && isoperator(str[i+1]))
        {
            cout << "At location " << i+1 << " " << i+2 << " " << str[i] << " and " << str[i+1] << " are not valid";
            return false;
        }
        if(isoperator( str[i] ) && str[i+1] == ')' )
        {
            cout << endl << "There is a operator behind ')'";
            return false ;
        }
        if(isnum( str[i-1] ) && str[i] == '('  || ( isnum(str[i-1]) && isnum(str[i]) ) || (isnum( str[i+1] ) && str[i] == ')'  ))
        {
            string st = "*";
            str.insert(i+1 , st );
        }
        if(str[i] == '/' && str[i+1] == 0)
        {
            cout << endl << "There is a division by zero";
            return false ;
        }
    }
    return true;
}


//function to convert infix to postfix expression
vector<char> infixtopostfix(string str)
{
    vector<char> stack , postfixexpression ;
    str[str.length()]  = ')';
    stack.push_back('(');

    for(int i = 0 ; i <= str.length() ; i++)
    {
        cout << endl << endl << "Incoming : " << str[i] ;

        Sleep(800);

        if(isnum(str[i]))
        {
            postfixexpression.push_back(str[i]);
        }
        else if(isoperator(str[i]))
        {
            if(str[i] == '^')
            {
                while(stack.back() == '^')
                {
                    postfixexpression.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(str[i]);
            }
            else if(str[i] == '*' || str[i] == '/')
            {
                while(stack.back() == '*' || stack.back() == '/')
                {
                    postfixexpression.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(str[i]);
            }
            else
            {
                while(isoperator( stack.back() ) )
                {
                    postfixexpression.push_back( stack.back() );
                    stack.pop_back();
                }
                stack.push_back( str[i] );
            }
        }
        else if( str[i] == '(' )
        {
            stack.push_back( '(' );
        }
        else{
            while( stack.back() != '(' )
            {
                postfixexpression.push_back( stack.back() );
                stack.pop_back();
            }
            stack.pop_back();
        }
        
        cout << endl << "STACK : " << endl;
        if(stack.empty())
        {
            cout<<"Stack is empty";
        }
        else{
            for(int j = stack.size()-1 ; j >= 0 ; j--)
        {
            printf("\n      |  %c  |",stack[j]);
            Sleep(300);
        }
        cout<< endl <<"      ```````";
        }
        
        cout << endl <<"POSTFIX expression : ";
        for(int j = 0 ; j < postfixexpression.size() ; j++)
        {
            Sleep(200);
            cout << postfixexpression[j];
        }
        cout << endl;
        Sleep(400);
    }

    return postfixexpression ;
}


//function to Take Values as input from user
void insertvalues(vector<char>& v, vector<char>& variables, vector<int>& values){
    variables.clear();
    values.clear();
    for (char ch : v) {
        bool found = false;
        for (char var : variables) {
            if (var == ch) {
                found = true;
                break;
            }
        }
        if (!found && isnum(ch)) {
            variables.push_back(ch);
            cout << endl << "Enter value of " << ch << " : ";
            int value;
            cin >> value;
            values.push_back(value);
        }
    }
}

//function to evaluate the postfix expression
bool expressionevaluation(vector<char>variables , vector<int>values ,vector<char> result)
{
    int finalresult , second_last , last ;
    vector<int> stack ;

    for(int i = 0 ; i < result.size() ; i++)
    {
        
        cout << endl << endl << "Incoming : " << result[i] ;
            Sleep(1000);
        if( isnum(result[i]) )
        {
            for(int j = 0 ; j < variables.size() ; j++)
            {
                if(result[i] == variables[j])
                {
                    stack.push_back(values[j]);
                    break ;
                }
            }
            cout << endl  <<  stack.back()  << " Pushed onto stack" << endl;
        }
        else
        {
            last = stack.back();
            stack.pop_back();
            second_last = stack.back();
            stack.pop_back();

            switch (result[i])
            {
            case '+' : stack.push_back( second_last + last );
                break;
        
            case '-' : stack.push_back( second_last - last );
                break ;
            
            case '*' : stack.push_back( second_last * last );
                break ;
            
            case '/' : if (last != 0) {
                        stack.push_back(second_last / last);
                    } else {
                        cout <<  "Error: Division by zero";
                        return false;
                    }
                break ;

            case '%' : stack.push_back( second_last % last );
                break ;
            case '^': stack.push_back(integerPower(second_last, last));
                break;
            }
            cout << endl << second_last ;
             Sleep(300) ;
             cout << result[i] ;
             Sleep(100);
             cout<< last ;
             Sleep(100) ; 
             cout<< " = " ;
             Sleep(100);
             cout<< stack.back() << endl;
            Sleep(700);
        }

        cout << endl << "Stack : "<<endl;
        for(int k = stack.size()-1 ; k >= 0  ; k--) 
        {
            printf("\n      | %-4d |",stack[k]);
            Sleep(300);
        }
        cout<< endl <<"      ````````";
        Sleep(400);
    }
    Sleep(1000);
    cout << endl << endl << "Final Answer : " << stack.back()<<endl<<endl;
    for (int i = 0; i <= 40; i++) //for animation
    {
        cout<<'\xDB';
        Sleep(50);
    }

    return true ;
}