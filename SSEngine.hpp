#ifndef SS_ENGINE_HPP
#define SS_ENGINE_HPP
#include <rapidxml\rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <string>
#include <map>
#include <memory>
#include <STDAFX.hpp>
using namespace std;

namespace rxml = rapidxml;

class SSENGINECLASS SSEngine
{
public:
    ~SSEngine(void);
    
    static SSEngine* GetInstance(); //Make this object a singleton to prevent the sql statment from reloading.

    string GetColumns(const string& a_rTable, short a_ColumnID = 0);
    string GetKey(const string& a_rTable, short a_KeyNum = 0);

private:
    SSEngine(void);
    SSEngine(const SSEngine& a_rSSEngine) = delete;

    void Init(void);
    string Load(const string& a_rTable, const string& a_rNodePath);

    map<string, string>* m_pSSCache; //<NodePath, NodeValue>
    rxml::xml_document<>* m_pDoc;
};

#endif // !SS_ENGINE_HPP


