#include <stdio.h> //define FILENAME_MAX
#include <iostream>
#include <PlatformInterfaces.hpp>
#include "SSEngine.hpp"

const string COLUMNS    = "columns";
const string UKEY       = "ukey";
const string KEY        = "key";
const string DELIMITER  = ".";
const string XML_SUBFIX = ".xml";
const string FOLDER     = "\\SqlStatements\\";

SSEngine::SSEngine(void)
{
    Init();
}

SSEngine::~SSEngine()
{
    if (NULL != m_pSSCache)
    {
        delete m_pSSCache;
        m_pSSCache = NULL;
    }

    if (NULL != m_pDoc)
    {
        delete m_pDoc;
        m_pDoc = NULL;
    }
}

void SSEngine::Init(void)
{
    m_pSSCache = new map<string, string>();
    m_pDoc = new rxml::xml_document<>();
}


SSEngine* SSEngine::GetInstance(void)
{
    static SSEngine s_SSEngine;
    return &s_SSEngine;
}

string SSEngine::GetColumns(const string& a_rTable, short a_ColumnID /* = 0 */)
{
    string l_Columns = "";
    string l_NodePath = "";

    switch (a_ColumnID)
    {
    //case 0 will be the same with default.
    case 0:
    default:
        {
            l_NodePath.append(COLUMNS); //columns
        }
        break;
    }

    string l_CacheKey = a_rTable + DELIMITER + l_NodePath; //Table.columns
    map<string, string>::iterator l_It = m_pSSCache->find(l_CacheKey);
    if (m_pSSCache->end() != l_It)
    {
        l_Columns.append(l_It->second);
    }
    else
    {
        l_Columns.append(Load(a_rTable, l_NodePath));
        
        //If the result of loading is not empty, add to the cache.
        if (l_Columns.size() != 0)
        {
            m_pSSCache->insert(pair<string, string>(l_CacheKey, l_Columns));
        }
    }

    return l_Columns;
}

string SSEngine::GetKey(const string& a_rTable, short a_KeyNum /* = 0 */)
{
    string l_Key = "";
    string l_NodePath = "";

    switch (a_KeyNum)
    {
    //case 0 will be the same with default.
    case 0:
    default:
    {
        l_NodePath.append(UKEY); //ukey
    }
    break;
    }

    string l_CacheKey = a_rTable + DELIMITER + l_NodePath; //Table.ukey
    map<string, string>::iterator l_It = m_pSSCache->find(l_CacheKey);
    if (m_pSSCache->end() != l_It)
    {
        l_Key.append(l_It->second);
    }
    else
    {
        l_Key.append(Load(a_rTable, l_NodePath));

        //If the result of loading is not empty, add to the cache.
        if (l_Key.size() != 0)
        {
            m_pSSCache->insert(pair<string, string>(l_CacheKey, l_Key));
        }
    }

    return l_Key;
}

string SSEngine::Load(const string& a_rTable, const string& a_rNodePath)
{
    string l_Value = "";

    char l_FileBuffer[FILENAME_MAX];
    memset(l_FileBuffer, 0, sizeof(l_FileBuffer));
    GetCurrentDir(l_FileBuffer, FILENAME_MAX);

    string l_FilePath(l_FileBuffer);
    string l_File = l_FilePath + FOLDER + a_rTable + XML_SUBFIX;

    try
    {
        rxml::file<> l_XmlFile(l_File.c_str());

        //rxml::xml_document<> l_Doc;
        m_pDoc->parse<0>(l_XmlFile.data());

        rxml::xml_node<>* l_pRoot = m_pDoc->first_node();

        //Get the first node and return the value.
        rxml::xml_node<>* l_pTargetNode = l_pRoot->first_node(a_rNodePath.c_str());
        if (NULL != l_pTargetNode)
        {
            l_Value.append(l_pTargetNode->value());
        }
    }
    catch (const std::exception& ex)
    {
        cout << __LINE__ << " : " << ex.what() << endl;
        l_Value.clear();
    }

    return l_Value;
}

