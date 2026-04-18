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
    virtual string nameget() const = 0;
    virtual bool eval(bool a, bool b) const { return false; }
    virtual string explanget() const = 0;
    virtual bool noteval(bool a) const { return false; }
    virtual bool isnot() const { return false; }
    virtual ~boolop() {}
};

class AND : public boolop
{
    string nameget() const override { return "AND"; }
    string explanget() const override
    {
        return "AND : True only if BOTH inputs are true.(0 AND 0=0, 1 AND 0=0, 1 AND 1=1)";
    }
    bool eval(bool a, bool b) const override { return a && b; }
};

class OR : public boolop
{
    string nameget() const override { return "OR"; }
    string explanget() const override
    {
        return "OR : True if at least ONE input is true.(0 OR 0=0, 1 OR 0=1, 1 OR 1=1)";
    }
    bool eval(bool a, bool b) const override { return a || b; }
};

class XOR : public boolop
{
    string nameget() const override { return "XOR"; }
    string explanget() const override
    {
        return "XOR : True if exactly ONE input is true. (0 XOR 0=0, 1 XOR 0=1, 1 XOR 1=0)";
    }
    bool eval(bool a, bool b) const override { return a != b; }
};

class NOT : public boolop
{
    string nameget() const override { return "NOT"; }
    string explanget() const override
    {
        return "NOT : Inverts the input. (NOT 0=1, NOT 1=0)";
    }
    bool noteval(bool a) const override { return !a; }
    bool isnot() const override { return true; }
};

class NAND : public boolop
{
    string nameget() const override { return "NAND"; }
    string explanget() const override
    {
        return "NAND : True unless BOTH inputs are true. (0 NAND 0=1, 1 NAND 0=1, 1 NAND 1=0)";
    }
    bool eval(bool a, bool b) const override { return !(a && b); }
};

class NOR : public boolop
{
    string nameget() const override { return "NOR"; }
    string explanget() const override
    {
        return "NOR : True only if BOTH inputs are false. (0 NOR 0=1, 1 NOR 0=0, 1 NOR 1=0)";
    }
    bool eval(bool a, bool b) const override { return !(a || b); }
};

string containsop(const string &stri, const string &word)
{
    size_t pos = stri.find(word);
    while (pos != string::npos)
    {
        bool before = (pos == 00) || !isalpha(stri[pos - 1]);
        bool after = (pos + word.size() >= stri.size()) || !isalpha(stri[pos + word.size()]);
        if (before && after)
        {
            return true;
        }
        pos = stri.find(word, pos + 1);
    }
    return false;
}

class boolexpression
{
private:
    string expression;
    bool a, b, c;
    bool a, b, c;

public:
    boolexpression()
    {
        expression = "";
        a = false;
        b = false;
        c = false;
    }
    void expressionset(const string &epress)
    {
        expression = uppercase(epress);
        a = (expression.find('A') != string::npos);
        b = (expression.find('B') != string::npos);
        c = (expression.find('C') != string::npos);
        opsfound.clear();
        if (containsop(expression, "AND"))
        {
            opsfound.push_back("AND");
        }
        if (containsop(expression, "OR"))
        {
            opsfound.push_back("OR");
        }
        if (containsop(expression, "XOR"))
        {
            opsfound.push_back("XOR");
        }
        if (containsop(expression, "NOT"))
        {
            opsfound.push_back("NOT");
        }
        if (containsop(expression, "NAND"))
        {
            opsfound.push_back("NAND");
        }
        if (containsop(expression, "NOR"))
        {
            opsfound.push_back("NOR");
        }
        if (int(opsfound.size()) > 3)
        {
            cout << "Operator count has exceeded the defined limit.\n";
        }
    }
};

string epressget() onst
{
    return expression;
}
bool geta() const
{
    return a;
}
bool getb() const
{
    return b;
}
bool getc() const
{
    return c;
}
vector<string> getopsfound() const
{
    return opsfound;
}
