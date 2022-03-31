#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
enum token_type
{
    NUMBER,
    OPERATOR,
    IDENTIFIER,
    EOF_TOKEN,
    UNKNOWN
};

map<token_type, string> token_names = {
    {NUMBER, "NUMBER"},
    {OPERATOR, "OPERATOR"},
    {IDENTIFIER, "IDENTIFIER"},
    {EOF_TOKEN, "EOF_TOKEN"},
    {UNKNOWN, "UNKNOWN"}};

map<string, token_type> token_type_map = {
    {"+", OPERATOR},
    {"-", OPERATOR},
    {"*", OPERATOR},
    {"/", OPERATOR},
    {"++", OPERATOR},
    {"--", OPERATOR},
    {"=", OPERATOR},
    {"!", OPERATOR},
    {"==", OPERATOR},
    {"!=", OPERATOR},
    {"<", OPERATOR},
    {">", OPERATOR},
    {"<=", OPERATOR},
    {">=", OPERATOR},
    {"{", OPERATOR},
    {"}", OPERATOR},
    {"[", OPERATOR},
    {"]", OPERATOR},
    {"(", OPERATOR},
    {")", OPERATOR},
    {"()", OPERATOR},
    {">>", OPERATOR},
    {"<<", OPERATOR},
    {"||", OPERATOR},
    {"&&", OPERATOR},
    {".", OPERATOR},
    {",", OPERATOR},
    {":", OPERATOR},
    {";", EOF_TOKEN},
    {"UNKNOWN", UNKNOWN}};

class Token
{
public:
    string value;
    token_type type;
    int lineNo;
    Token(token_type utype, string uvalue, int ulineNo)
    {
        value = uvalue;
        type = utype;
        lineNo = ulineNo;
    }
};

void printVector(vector<string> arr, bool printOnNextLine = false)
{
    for (int i = 0; i < arr.size(); i++)
    {
        printOnNextLine ? cout << arr[i] + "\n"
                        : cout << arr[i] + "\t";
    }
}

void printVector(vector<Token> tokens)
{
    int lastLineNo = 1;
    for (Token token : tokens)
    {
        if (token.lineNo != lastLineNo)
        {
            for (int i = 0; i < token.lineNo - lastLineNo; i++)
            {
                cout << "\n";
            }

            lastLineNo = token.lineNo;
        }
        cout << "| " << token_names[token.type] << " == " << token.value << " == " << token.lineNo << "|  \n";
    }
}

vector<string> splitBy(string code, char charecter)
{
    vector<string> splited;
    for (int i = 0; i < code.size(); i++)
    {
        int startingIndex = i;
        while (code[i] != charecter && i < code.size())
        {
            if (code[i] == '"')
            {
                int stringStartingIndex = i;
                do
                {
                    i++;
                } while (code[i] != '"' && i < code.size());
            }
            else
            {
                i++;
            }
        }
        splited.push_back(code.substr(startingIndex, i - startingIndex));
    }
    return splited;
}

string readFile(string pathToFile)
{
    string result;
    char c;
    // reading file
    ifstream outPutFile;
    outPutFile.open(pathToFile);
    if (outPutFile.is_open())
    {

        while (outPutFile.get(c))
        {
            result += c;
        }
        outPutFile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    return result;
}

void writeTokensToFile(string pathToFile, vector<Token> tokens)
{
    ofstream outPutFile;
    outPutFile.open(pathToFile);
    if (outPutFile.is_open())
    {

        int lastLineNo = 1;
        for (Token token : tokens)
        {
            if (token.lineNo != lastLineNo)
            {
                for (int i = 0; i < token.lineNo - lastLineNo; i++)
                {
                    outPutFile << "\n";
                }

                lastLineNo = token.lineNo;
            }
            outPutFile << "|" << token_names[token.type] << " == " << token.value << " == " << token.lineNo << "|  \n";
        }

        // Close the file
        outPutFile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

string removeComments(string code)
{
    string result = "";
    int i = 0;
    while (i < code.size())
    {
        if (code[i] == '/' && code[i + 1] == '/')
        {
            // add "\n" to maintain line numbers
            result += "\n";
            while (code[i] != '\n')
            {
                i++;
            }
        }
        else if (code[i] == '/' && code[i + 1] == '*')
        {
            i = i + 2;
            while (code[i] != '*' && code[i + 1] != '/')
            {
                // add "\n" to maintain line numbers
                if (code[i] == '\n')
                {
                    result += "\n";
                }
                i++;
                // check for Un-terminated comments
                if (i >= code.size())
                {
                    throw runtime_error("Un-terminated comments are present in your code");
                }
            }
            i = i + 2;
        }
        else
        {
            result += code[i];
            i++;
        }
    }
    return result;
}

vector<string> splitByLines(string code)
{
    vector<string> splited;
    string temp = "";

    for (int i = 0; i <= code.size(); i++)
    {
        if (code[i] == '\n')
        {
            splited.push_back(temp);
            temp = "";
        }
        else
        {
            temp += code[i];
        }
    }
    splited.push_back(temp);
    return splited;
}


bool isStatement(const std::string &str)
{
  const vector<std::string> statements{"for", "while"};
  for(const auto& statement : statements)
    if (statement == str)
      return true;

  return false;
}

