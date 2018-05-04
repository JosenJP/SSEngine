#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include <boost\property_tree\exceptions.hpp>
//#include <boost\\optional\optional.hpp>
#include "SSEngine.hpp"

namespace pt = boost::property_tree;

const string COLUMNS    = "columns";
const string UKEY       = "ukey";
const string KEY        = "key";
const string DELIMITER  = ".";
const string XML_SUBFIX = ".xml";

//struct string_to_int_translator
//{
//    typedef string internal_type;
//    typedef string external_type;
//
//    boost::optional<string> get_value(const std::string &s)
//    {
//        char *c;
//        long l = std::strtol(s.c_str(), &c, 10);
//        return boost::make_optional(c != s.c_str(), static_cast<int>(l));
//    }
//};

SSEngine::SSEngine(void)
{
    //Init();
}

SSEngine::~SSEngine()
{
}

SSEngine* SSEngine::m_pSSEngine = new SSEngine();

SSEngine* SSEngine::GetInstance(void)
{
    return m_pSSEngine;
}

string SSEngine::GetColumns(const string& a_rTable, short a_ColumnID)
{
    string l_Columns = "";
    string l_NodePath = a_rTable;
    l_NodePath.append(DELIMITER); //table.

    switch (a_ColumnID)
    {

    case 0:
    default:
        {
            l_NodePath.append(COLUMNS); //table.columns
        }
        break;
    }

    if (m_SSCache.find(l_NodePath) != m_SSCache.end())
    {
        l_Columns.append(m_SSCache.find(l_NodePath)->second);
    }
    else
    {
        l_Columns.append(Load(a_rTable, l_NodePath));
        
        //If the result of loading is not empty, add to the cache.
        if (l_Columns.size() != 0)
        {
            m_SSCache[l_NodePath] = l_Columns;
        }
    }

    return l_Columns;
}

string SSEngine::GetKey(const string& a_rTable, short a_KeyNum)
{
    string l_Key = "";
    string l_NodePath = a_rTable;
    l_NodePath.append(DELIMITER); //table.

    switch (a_KeyNum)
    {

    case 0:
    default:
    {
        l_NodePath.append(UKEY); //table.columns
    }
    break;
    }

    if (m_SSCache.find(l_NodePath) != m_SSCache.end())
    {
        l_Key.append(m_SSCache.find(l_NodePath)->second);
    }
    else
    {
        l_Key.append(Load(a_rTable, l_NodePath));

        //If the result of loading is not empty, add to the cache.
        if (l_Key.size() != 0)
        {
            m_SSCache[l_NodePath] = l_Key;
        }
    }

    return l_Key;
}

string SSEngine::Load(const string& a_rTable, const string& a_rNodePath)
{
    string l_Value = "";
    string l_File = a_rTable + XML_SUBFIX;
    
    try
    {
        pt::ptree l_Tree;
        pt::read_xml(l_File, l_Tree);
    
        l_Value.append(l_Tree.get<string>(a_rNodePath));
    }
    catch (const pt::ptree_error& ex)
    {
        l_Value.clear();
    }

    return l_Value;
}

