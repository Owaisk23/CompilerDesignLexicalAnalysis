#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <typeinfo>
#include "callMethods.h"
using namespace std;

bool isPunctuator(char ch)					//check if the given character is a punctuator or not
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == '&' || ch == '|')
        {
            return true;
        }
    return false;
}

bool validIdentifier(char* str)						//check if the given identifier is valid or not
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isPunctuator(str[0]) == true)
        {
            return false;
        }									//if first character of string is a digit or a special character, identifier is not valid
    int i,len = strlen(str);
    if (len == 1)
    {
        return true;
    }										//if length is one, validation is already completed, hence return true
    else
    {
    for (i = 1 ; i < len ; i++)						//identifier cannot contain special characters
    {
        if (isPunctuator(str[i]) == true)
        {
            return false;
        }
    }
    }
    return true;
}

bool isOperator(char ch)							//check if the given character is an operator or not
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '|' || ch == '&')
    {
       return true;
    }
    return false;
}

bool isKeyword(char *str)						//check if the given substring is a keyword or not
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") ||  !strcmp(str, "continue")
        || !strcmp(str, "int") || !strcmp(str, "double")
        || !strcmp(str, "float") || !strcmp(str, "return")
        || !strcmp(str, "char") || !strcmp(str, "case")
        || !strcmp(str, "long") || !strcmp(str, "short")
        || !strcmp(str, "typedef") || !strcmp(str, "switch")
        || !strcmp(str, "unsigned") || !strcmp(str, "void")
        || !strcmp(str, "static") || !strcmp(str, "struct")
        || !strcmp(str, "sizeof") || !strcmp(str,"long")
        || !strcmp(str, "volatile") || !strcmp(str, "typedef")
        || !strcmp(str, "enum") || !strcmp(str, "const")
        || !strcmp(str, "union") || !strcmp(str, "extern")
        || !strcmp(str,"bool"))
        {
            return true;
        }
    else
    {
       return false;
    }
}

bool isNumber(char* str)							//check if the given substring is a number or not
{
    int i, len = strlen(str),numOfDecimal = 0;
    if (len == 0)
    {
        return false;
    }
    for (i = 0 ; i < len ; i++)
    {
        if (numOfDecimal > 1 && str[i] == '.')
        {
            return false;
        } else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            {
                return false;
            }
    }
    return true;
}

char* subString(char* realStr, int l, int r)				//extract the required substring from the main string
{
    int i;

    char* str = (char*) malloc(sizeof(char) * (r - l + 2));

    for (i = l; i <= r; i++)
    {
        str[i - l] = realStr[i];
        str[r - l + 1] = '\0';
    }
    return str;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int doSegment(char *sentence)
{
  std::stringstream ss(sentence);
  std::string to;
  string str[100];
  int  i = 0;
  if (sentence != NULL)
  {
    while(std::getline(ss,to,'\n')){
      cout << to <<endl;
      str[i] = to;
      i++;
    }
  }

  cout<<"////////\n";
    cout<<i<<endl;
    cout<< str[0]<<endl;
    cout<< str[1]<<endl;
    cout<< str[2]<<endl;
    cout<< str[3]<<endl;
    cout<< str[4]<<endl;
    cout<< str[5]<<endl;
    cout<< str[6]<<endl;
    cout<< str[7]<<endl;
    cout<< str[8]<<endl;
return 0;

}


void parse(char* code, int codeLength)						//parse the expression
{
    string OutputFile = "./output.dat";
    string sourceCode;

      for (int j = 0; j < codeLength; j++)
    {
        sourceCode += code[j];
    }
    
      // Remove Comments from source Code....
    string codeWithoutComments = removeComments(sourceCode);
    // cout<<codeWithoutComments;

    // Spliting each line by space
     vector<string> splitedInLines;
    splitedInLines = splitByLines(codeWithoutComments);
    vector<vector<string>> splitBySpaceAndLine;
        for (string line : splitedInLines)
        {
            splitBySpaceAndLine.push_back(splitBy(line, ' '));
        }
      vector<Token> tokens;
     
        for (int lineIndex = 0; lineIndex < splitBySpaceAndLine.size(); lineIndex++)
        {
            for (string word : splitBySpaceAndLine[lineIndex])
            {          
                //  Read charecter by charecter
                for (int charIndex = 0; charIndex < word.size(); charIndex++)
                {     
                    if (word[charIndex] == '\'')
                    {
                        // check for valid charecter
                        if (word[charIndex + 2] == '\'')
                        {
                            tokens.push_back(Token(IDENTIFIER, word.substr(charIndex, 3), lineIndex + 1));
                            charIndex = charIndex + 2;
                        }
                        else
                        {
                            throw runtime_error("Char constant too long at line No : " + to_string(lineIndex + 1));
                        }
                    }
                    else if (word[charIndex] == '"')
                    {
                        int stringStartIndex = charIndex;
                        // check for valid String
                        do
                        {
                            charIndex++;
                            if (charIndex >= word.size())
                            {
                                throw runtime_error("String constants exceed line OR not ended properly at line No : " + to_string(lineIndex + 1));
                            }

                            if (word[charIndex] == '\n')
                            {
                                throw runtime_error("String constants exceed line at line No : " + to_string(lineIndex + 1));
                            }

                        } while (word[charIndex] != '"');

                        // push string to tokens vector
                        tokens.push_back(Token(IDENTIFIER, word.substr(stringStartIndex, charIndex - stringStartIndex + 1), lineIndex + 1));
                    }
                    else if (word[charIndex] >= 48 && word[charIndex] <= 57)
                    {
                        int numberStartIndex = charIndex;
                        // check for valid number constant
                        do
                        {
                            charIndex++;
                            if (charIndex >= word.size())
                            {
                                throw runtime_error("Number constants exceed line OR not ended properly at line No : " + to_string(lineIndex + 1));
                            }
                        } while (word[charIndex] >= 48 && word[charIndex] <= 57);
                        charIndex--; // to get the last index of number
                        // push number string to tokens vector
                        tokens.push_back(Token(NUMBER, word.substr(numberStartIndex, charIndex - numberStartIndex + 1), lineIndex + 1));
                    }
                    else if (token_type_map[word.substr(charIndex, 1)] == OPERATOR)
                    {
                        // check if next chaecter is also operator
                        if (token_type_map[word.substr(charIndex + 1, 1)] == OPERATOR)
                        {
                            // check of both cherecters combine to form a valid operator
                            if (token_type_map[word.substr(charIndex, 2)] == OPERATOR)
                            {
                                tokens.push_back(Token(OPERATOR, word.substr(charIndex, 2), lineIndex + 1));
                                charIndex++;
                            }
                            else
                            {
                                throw runtime_error("Not a valid operator at line No : " + to_string(lineIndex + 1));
                            }
                        }
                        else
                        {
                            tokens.push_back(Token(OPERATOR, word.substr(charIndex, 1), lineIndex + 1));
                        }
                    }
                    else if (
                        (word[charIndex] >= 65 && word[charIndex] <= 90) ||
                        (word[charIndex] >= 97 && word[charIndex] <= 122))
                    {
                        int identifierStartingIndex = charIndex;
                        do
                        {
                            charIndex++;

                        } while ((word[charIndex] >= 65 && word[charIndex] <= 90) ||
                                 (word[charIndex] >= 97 && word[charIndex] <= 122) ||
                                 (word[charIndex] >= 48 && word[charIndex] <= 57) ||
                                 word[charIndex] == '_');
                        charIndex--; // to get the last index of identifier
                        // push the identifier
                        tokens.push_back(Token(IDENTIFIER, word.substr(identifierStartingIndex, charIndex - identifierStartingIndex + 1), lineIndex + 1));
                    }
                    else if (word[charIndex] == ';')
                    {
                        tokens.push_back(Token(EOF_TOKEN, word.substr(charIndex, 1), lineIndex + 1));
                    }
                    
                    
                    else
                    {
                        // cout << (int)word[charIndex] << " : " << word[charIndex] << endl;
                        if (word[charIndex] != 0 && word[charIndex] != 32)
                        {
                            throw runtime_error("Undefined symbol" + word.substr(charIndex, 1) + "at line No : " + to_string(lineIndex + 1));
                        }
                    }
                }
            }
        }

        // output tokens
        cout << "Tokens : \n";
        printVector(tokens);
        // write to file
        writeTokensToFile(OutputFile, tokens);
        // writeTokensToFile('token.txt', tokens); // my change



}

///////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    string testFile = readFile("./code.txt");
    
    char code[100];
    int i;
    for (i = 0; i < testFile.size(); i++)
    {
        code[i] = testFile[i];
    }
    code[i] = '\0';

    parse(code , i);
    

    return 0;
}


