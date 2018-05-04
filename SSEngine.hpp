#ifndef SS_ENGINE_HPP
#define SS_ENGINE_HPP

#include<string>
#include<map>
using namespace std;

class SSEngine
{
public:
    ~SSEngine(void);
    
    static SSEngine* GetInstance(); //Make this object a singleton to prevent the sql statment from reloading.

    string GetColumns(const string& a_rTable, short a_ColumnID);
    string GetKey(const string& a_rTable, short a_KeyNum);

private:
    SSEngine(void);
    SSEngine(const SSEngine& a_rSSEngine) = delete;

    static SSEngine* m_pSSEngine;

    //void Init(void);
    string Load(const string& a_rTable, const string& a_rNodePath);

    map<string, string> m_SSCache; //<NodePath, NodeValue>
};

#endif // !SS_ENGINE_HPP


