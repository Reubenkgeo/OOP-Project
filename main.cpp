/*
NTO1046
OOP(object-oriented programming) project
Author: Reuben Kuruvila George
Student ID: 40467327
Boolean expression and truth table simulatoor
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class boolop
{
public:
    virtual string nameget() const = 0;                       // returns the operator name
    virtual bool eval(bool a, bool b) const { return false; } // evaluates two input operators
    virtual string explanget() const = 0;                     // returns a readable explanation
    virtual bool noteval(bool a) const { return false; }
    virtual bool isnot() const { return false; }
    virtual ~boolop() {}
};

class AND : public boolop // AND operator
{
public:
    string nameget() const override { return "AND"; }
    string explanget() const override
    {
        return "AND : True only if BOTH inputs are true.(0 AND 0=0, 1 AND 0=0, 1 AND 1=1)";
    }
    bool eval(bool a, bool b) const override { return a && b; }
};

class OR : public boolop // OR operator
{
public:
    string nameget() const override { return "OR"; }
    string explanget() const override
    {
        return "OR : True if at least ONE input is true.(0 OR 0=0, 1 OR 0=1, 1 OR 1=1)";
    }
    bool eval(bool a, bool b) const override { return a || b; }
};

class XOR : public boolop // XOR Operator
{
public:
    string nameget() const override { return "XOR"; }
    string explanget() const override
    {
        return "XOR : True if exactly ONE input is true. (0 XOR 0=0, 1 XOR 0=1, 1 XOR 1=0)";
    }
    bool eval(bool a, bool b) const override { return a != b; }
};

class NOT : public boolop // NOT operator
{
public:
    string nameget() const override { return "NOT"; }
    string explanget() const override
    {
        return "NOT : Inverts the input. (NOT 0=1, NOT 1=0)";
    }
    bool noteval(bool a) const override { return !a; }
    bool isnot() const override { return true; }
};

class NAND : public boolop // NAND operator
{
public:
    string nameget() const override { return "NAND"; }
    string explanget() const override
    {
        return "NAND : True unless BOTH inputs are true. (0 NAND 0=1, 1 NAND 0=1, 1 NAND 1=0)";
    }
    bool eval(bool a, bool b) const override { return !(a && b); }
};

class NOR : public boolop // NOR Operator
{
public:
    string nameget() const override { return "NOR"; }
    string explanget() const override
    {
        return "NOR : True only if BOTH inputs are false. (0 NOR 0=1, 1 NOR 0=0, 1 NOR 1=0)";
    }
    bool eval(bool a, bool b) const override { return !(a || b); }
};

bool containsop(const string &stri, const string &word) // Chekcs if a given operator keyword shows up as a whole word in the string
{
    size_t pos = stri.find(word);
    while (pos != string::npos)
    {
        bool before = (pos == 0) || !isalpha(stri[pos - 1]);
        bool after = (pos + word.size() >= stri.size()) || !isalpha(stri[pos + word.size()]);
        if (before && after)
        {
            return true;
        }
        pos = stri.find(word, pos + 1);
    }
    return false;
}
string uppercase(string str) // Converts a string to uppercase, so it should allow the usage of lowercase letters without worrying about case sensitivity
{
    for (int i = 0; i < (int)str.size(); i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;
    return str;
}

class boolexpression // Stores and evaluates a boolean expression which is entered by the user
{
private:
    string expression;
    bool a, b, c;
    vector<string> opsfound; // list of operators which are detected in the current expression

public:
    boolexpression()
    {
        expression = "";
        a = false;
        b = false;
        c = false;
    }
    void setexpression(const string &epress) // Stores the expression and detects which variables and operators are used
    {
        expression = uppercase(epress);
        a = (expression.find('A') != string::npos); // Checks which variables appear in the expression
        b = (expression.find('B') != string::npos);
        c = (expression.find('C') != string::npos);
        opsfound.clear();
        if (containsop(expression, "NAND"))
            opsfound.push_back("NAND");
        if (containsop(expression, "NOR"))
            opsfound.push_back("NOR");
        if (containsop(expression, "AND"))
            opsfound.push_back("AND");
        if (containsop(expression, "OR"))
            opsfound.push_back("OR");
        if (containsop(expression, "NOT"))
            opsfound.push_back("NOT");
        if (containsop(expression, "XOR"))
            opsfound.push_back("XOR");

        if ((int)opsfound.size() > 3)
        {
            cout << "[WARNING] More than 3 operators detected. Results may be unexpected.\n";
        }
    }
    string getexpression() const { return expression; } //  For the expression string and variable info
    bool geta() const { return a; }
    bool getb() const { return b; }
    bool getc() const { return c; }
    vector<string> getOpsFound() const { return opsfound; }

    bool evaluate(bool valA, bool valB, bool valC) const // This is meant for evaluating the expression for the given values for A,B,C
    {
        vector<string> tokens;
        string current = "";
        for (int i = 0; i < (int)expression.size(); i++)
        {
            char ch = expression[i];

            if (ch == ' ')
            {
                if (!current.empty())
                {
                    tokens.push_back(current);
                    current = "";
                }
            }
            else if (ch == '(' || ch == ')')
            {
                if (!current.empty())
                {
                    tokens.push_back(current);
                    current = "";
                }
                tokens.push_back(string(1, ch));
            }
            else
            {
                current += ch;
            }
        }
        if (!current.empty())
            tokens.push_back(current);
        vector<bool> valuestack; // holds the boolean values which we get from the calculations
        vector<string> opstack;  // holds operators which are waiting to be applied

        auto applyTop = [&]()
        {
            string op = opstack.back();
            opstack.pop_back();
            if (op == "NOT")
            {
                bool a = valuestack.back(); // since NOT is a unary operator it only has one value
                valuestack.pop_back();
                valuestack.push_back(!a);
            }
            else
            {
                bool b = valuestack.back(); // Unlike NOT these operators are binary
                valuestack.pop_back();
                bool a = valuestack.back();
                valuestack.pop_back();

                if (op == "AND")
                    valuestack.push_back(a && b);
                else if (op == "OR")
                    valuestack.push_back(a || b);
                else if (op == "XOR")
                    valuestack.push_back(a != b);
                else if (op == "NAND")
                    valuestack.push_back(!(a && b));
                else if (op == "NOR")
                    valuestack.push_back(!(a || b));
            }
        };

        auto precedence = [](const string &op) -> int // Meant to return precedence level
        {
            if (op == "NOT")
                return 3;
            if (op == "AND" || op == "NAND")
                return 2;
            return 1;
        };

        for (const string &tok : tokens)
        {
            if (tok == "A")
            {
                valuestack.push_back(valA);
            }
            else if (tok == "B")
            {
                valuestack.push_back(valB);
            }
            else if (tok == "C")
            {
                valuestack.push_back(valC);
            }
            else if (tok == "(")
            {
                opstack.push_back("(");
            }
            else if (tok == ")")
            {
                while (!opstack.empty() && opstack.back() != "(")
                    applyTop();
                if (!opstack.empty())
                    opstack.pop_back(); // remove "("
            }
            else if (tok == "AND" || tok == "OR" || tok == "NOT" ||
                     tok == "XOR" || tok == "NAND" || tok == "NOR")
            {
                while (!opstack.empty() &&
                       opstack.back() != "(" &&
                       precedence(opstack.back()) >= precedence(tok) &&
                       tok != "NOT")
                {
                    applyTop();
                }
                opstack.push_back(tok);
            }
        }
        while (!opstack.empty())
            applyTop();

        if (!valuestack.empty())
            return valuestack.back();
        return false;
    }
};
class TruthTable // This is meant to print the truth table to any output stream
{
private:
    boolexpression &expr;

public:
    TruthTable(boolexpression &e) : expr(e) {}

    void print(ostream &out) const
    {
        bool useA = expr.geta();
        bool useB = expr.getb();
        bool useC = expr.getc();
        string exprStr = expr.getexpression();

        out << "| ";
        if (useA)
            out << "A | ";
        if (useB)
            out << "B | ";
        if (useC)
            out << "C | ";
        out << exprStr << " |\n";

        out << "|-";
        if (useA)
            out << "--|-";
        if (useB)
            out << "--|-";
        if (useC)
            out << "--|-";
        for (int i = 0; i < (int)exprStr.size() + 2; i++)
            out << "-";
        out << "|\n";

        int numVars = (useA ? 1 : 0) + (useB ? 1 : 0) + (useC ? 1 : 0); // Calculates number of rows
        int numRows = 1;
        for (int i = 0; i < numVars; i++)
            numRows *= 2;

        for (int row = 0; row < numRows; row++)
        {

            bool valA = false, valB = false, valC = false;
            int bit = numVars - 1;
            if (useA)
            {
                valA = (row >> bit) & 1;
                bit--;
            }
            if (useB)
            {
                valB = (row >> bit) & 1;
                bit--;
            }
            if (useC)
            {
                valC = (row >> bit) & 1;
            }

            bool result = expr.evaluate(valA, valB, valC);

            out << "| ";
            if (useA)
                out << valA << " | ";
            if (useB)
                out << valB << " | ";
            if (useC)
                out << valC << " | ";

            int padding = (int)exprStr.size() / 2;
            for (int i = 0; i < padding; i++)
                out << " ";
            out << result;
            for (int i = 0; i < (int)exprStr.size() - padding; i++)
                out << " ";
            out << "|\n";
        }
    }
};
class filehandler // Handles saving results to a file and also loading these previously saved files as per request
{
public:
    static void save(const string &filename, boolexpression &expr, TruthTable &table)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Could not open file: " << filename << "\n";
            return;
        }

        file << "=== BOOLEAN TRUTH TABLE SIMULATOR ===\n\n";
        file << "Expression: " << expr.getexpression() << "\n\n";
        file << "Operators Detected and Explained:\n";

        vector<string> ops = expr.getOpsFound();
        for (int i = 0; i < (int)ops.size(); i++)
        {
            boolop *op = nullptr;
            if (ops[i] == "AND")
                op = new AND();
            else if (ops[i] == "OR")
                op = new OR();
            else if (ops[i] == "NOT")
                op = new NOT();
            else if (ops[i] == "XOR")
                op = new XOR();
            else if (ops[i] == "NAND")
                op = new NAND();
            else if (ops[i] == "NOR")
                op = new NOR();

            if (op != nullptr)
            {
                file << "  - " << op->explanget() << "\n";
                delete op; // just to clean up
            }
        }
        file << "\nTruth Table:\n";
        table.print(file);
        file << "\n[Saved by Boolean Truth Table Simulator]\n";
        file.close();
        cout << "Saved successfully to '" << filename << "'!\n";
    }
    static void load(const string &filename) // Reads and prints all lines from already saved files
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "[ERROR] Could not open file: " << filename << "\n";
            return;
        }

        string line;
        while (getline(file, line))
        {
            cout << line << "\n";
        }
        file.close();
    }

    static string readExpression(const string &filename)
    {
        ifstream file(filename);
        string line;
        while (getline(file, line))
        {
            if (line.substr(0, 12) == "Expression: ")
                return line.substr(12);
        }
        return "";
    }
};
void printexplans(boolexpression &expr)
{
    vector<string> ops = expr.getOpsFound();

    if (ops.empty())
    {
        cout << "  (No operators detected)\n";
        return;
    }

    for (int i = 0; i < (int)ops.size(); i++)
    {
        boolop *op = nullptr;

        if (ops[i] == "AND")
            op = new AND();
        else if (ops[i] == "OR")
            op = new OR();
        else if (ops[i] == "NOT")
            op = new NOT();
        else if (ops[i] == "XOR")
            op = new XOR();
        else if (ops[i] == "NAND")
            op = new NAND();
        else if (ops[i] == "NOR")
            op = new NOR();

        if (op != nullptr)
        {
            cout << "  - " << op->explanget() << "\n";
            delete op;
        }
    }
}
int main()
{
    cout << "\n><================================================><\n";
    cout << "\n               boolean truth table sim              \n";
    cout << "\n><================================================><\n";
    int choice = 0;
    while (true)
    {
        cout << "MENU\n"; // main menu
        cout << "1) enter a new Boolean expression\n";
        cout << "2) load a previously saved file\n";
        cout << "3) exit\n";
        cout << "choice: ";
        cin >> choice;
        cin.ignore();
        cout << "\n";

        if (choice == 1)
        {
            cout << "enter Boolean Expression\n"; // asks user to enter a boolean expression
            cout << "variables : A  B  C\n";
            cout << "operators : AND  OR  NOT  XOR  NAND  NOR\n";
            cout << "can use a max of 3 operators\n";
            cout << "example : A AND B OR NOT C / (A AND B) OR (NOT C)\n";
            cout << "> ";

            string exprInput;
            getline(cin, exprInput);

            boolexpression expr;
            expr.setexpression(exprInput);

            cout << "\nOperators Detected and Explained:\n";
            printexplans(expr);

            cout << "\nGenerating Truth Table...\n\n"; // Generates and displays a truth table from the entered expression
            TruthTable table(expr);
            table.print(cout);

            cout << "\nWould you like to save to a file? (Y/N): ";
            char saveChoice;
            cin >> saveChoice;
            cin.ignore();

            if (saveChoice == 'Y' || saveChoice == 'y') // Asks user if they want to save the results
            {
                cout << "Enter filename (e.g. myresult.txt): ";
                string filename;
                getline(cin, filename);
                filehandler::save(filename, expr, table);
            }
        }

        else if (choice == 2) // Load and display a previously saved file
        {
            cout << "Enter filename to load: ";
            string filename;
            getline(cin, filename);
            filehandler::load(filename);
        }

        else if (choice == 3)
        {
            cout << "Exiting program. Goodbye!\n";
            break;
        }
    }
}