/**
 * \file
 *
 * \author Charles B. Owen
 * @brief Class that implements a wrapper for msxml nodes
 *
 * \version 1.01 07-16-2014
 * \version 1.02 07-17-2014
 * \version 1.03 07-17-2014
 */

// Ensure the file version above matches the class version
// in XmlNode.h

#include "pch.h"
#include "XmlNode.h"

using namespace std;
using namespace xmlnode;

CXmlNode::CXmlNode()
{
}

CXmlNode::CXmlNode(CXmlNode *parent, IXMLDOMNode *node)
{
    mDocument = parent->mDocument;
    mNode = node;
}

CXmlNode::~CXmlNode()
{
}

std::shared_ptr<CXmlNode> CXmlNode::OpenDocument(const std::wstring &filename)
{
    auto node = make_shared<CXmlNode>();
    node->Open(filename);
    return node;
}

void CXmlNode::Open(const std::wstring &filename)
{
    // Open the document
    mDocument = make_shared<Document>();
    mDocument->Open(filename);

    mNode = mDocument->GetRoot();
}

std::shared_ptr<CXmlNode> CXmlNode::CreateDocument(const std::wstring &rootname)
{
    auto node = make_shared<CXmlNode>();
    node->Create(rootname);
    return node;
}

void CXmlNode::Create(const std::wstring &rootname)
{
    // Open the document
    mDocument = make_shared<Document>();
    mDocument->Create(rootname);

    mNode = mDocument->GetRoot();
}

void CXmlNode::Save(const std::wstring &filename)
{
    mDocument->Save(filename);
}

std::wstring CXmlNode::GetXML()
{
    return mDocument->GetXML();
}

std::wstring CXmlNode::GetName() const
{
    CComBSTR name;
    mNode->get_nodeName(&name);
    return wstring(name);
}

DOMNodeType CXmlNode::GetType() const
{
    DOMNodeType t;
    mNode->get_nodeType(&t);
    return t;
}

std::wstring CXmlNode::GetValue() const
{
    CComVariant value;
    mNode->get_nodeValue(&value);

    value.ChangeType(VT_BSTR);
    return wstring(value.bstrVal);
}

int CXmlNode::GetIntValue() const
{
    return stoi(GetValue());
}

double CXmlNode::GetDoubleValue() const
{
    return stod(GetValue());
}

std::shared_ptr<CXmlNode>  CXmlNode::GetAttribute(const wstring &name)
{
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    mNode->get_attributes(&attributes);

    CComPtr<IXMLDOMNode> attrib;
    attributes->getNamedItem(CComBSTR(name.c_str()), &attrib);
    if (attrib == nullptr) {
        return shared_ptr<CXmlNode>();
    }

    return shared_ptr<CXmlNode>(new CXmlNode(this, attrib));
}

std::wstring CXmlNode::GetAttributeValue(const std::wstring &name, const std::wstring &def)
{
    std::shared_ptr<CXmlNode> attr = GetAttribute(name);
    if (attr == nullptr)
    {
        return def;
    }

    return attr->GetValue();
}

int CXmlNode::GetAttributeIntValue(const std::wstring &name, int def)
{
    std::shared_ptr<CXmlNode> attr = GetAttribute(name);
    if (attr == nullptr)
    {
        return def;
    }

    return attr->GetIntValue();
}

double CXmlNode::GetAttributeDoubleValue(const std::wstring &name, double def)
{
    std::shared_ptr<CXmlNode> attr = GetAttribute(name);
    if (attr == nullptr)
    {
        return def;
    }

    return attr->GetDoubleValue();
}

void CXmlNode::SetAttribute(const std::wstring &name, const std::wstring &val)
{
    CComPtr<IXMLDOMElement> element;
    if (mNode.QueryInterface(&element) == S_OK)
    {
        element->setAttribute(CComBSTR(name.c_str()), CComVariant(val.c_str()));
    }
}

void CXmlNode::SetAttribute(const std::wstring &name, int val)
{
    CComPtr<IXMLDOMElement> element;
    if (mNode.QueryInterface(&element) == S_OK)
    {
        element->setAttribute(CComBSTR(name.c_str()), CComVariant(val));
    }
}

void CXmlNode::SetAttribute(const std::wstring &name, double val)
{
    CComPtr<IXMLDOMElement> element;
    if (mNode.QueryInterface(&element) == S_OK)
    {
        element->setAttribute(CComBSTR(name.c_str()), CComVariant(val));
    }
}

std::shared_ptr<CXmlNode> CXmlNode::AddChild(const std::wstring &name)
{
    // Create an XML node for the item
    CComPtr<IXMLDOMNode> node;
    CComPtr<IXMLDOMElement> element;
    mDocument->GetDoc()->createElement(CComBSTR(name.c_str()), &element);
    mNode->appendChild(element, &node);

    return shared_ptr<CXmlNode>(new CXmlNode(this, node));
}

std::shared_ptr<CXmlNode> CXmlNode::GetChild(int n)
{
    CComPtr<IXMLDOMNodeList> children;
    mNode->get_childNodes(&children);

    CComPtr<IXMLDOMNode> child;
    children->get_item(n, &child);

    return shared_ptr<CXmlNode>(new CXmlNode(this, child));
}

int CXmlNode::GetNumChildren()
{
    CComPtr<IXMLDOMNodeList> children;
    mNode->get_childNodes(&children);

    long len;
    children->get_length(&len);

    return (int)len;
}

CXmlNode::Children CXmlNode::GetChildren()
{
    return Children(this);
}

CXmlNode::Iterator CXmlNode::Children::begin()
{
    return Iterator(this, 0);
}

CXmlNode::Iterator CXmlNode::Children::end()
{
    long len;
    mChildren->get_length(&len);
    return Iterator(this, (int)len);
}

CXmlNode::Children::Children(CXmlNode *node)
{
    mNode = node;
    node->mNode->get_childNodes(&mChildren);
}

std::shared_ptr<CXmlNode>  CXmlNode::Iterator::operator* ()
{
    CComPtr<IXMLDOMNode> child;

    mChildren->mChildren->get_item(mPos, &child);

    return shared_ptr<CXmlNode>(new CXmlNode(mChildren->mNode, child));
}

CXmlNode::Document::Document()
{
    CoInitialize(NULL);
}

CXmlNode::Document::~Document()
{
    CoUninitialize();
}

void CXmlNode::Document::Open(const std::wstring &filename)
{
    //
    // Create an XML document
    //
    HRESULT hr = CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
        IID_IXMLDOMDocument, (void**)&mDoc);
    if (hr != S_OK)
    {
        wstring err(L"Failed to create an XML document to use");
        throw Exception(Exception::UnableToCreate, err);
    }

    // Open the XML document
    VARIANT_BOOL ok;
    hr = mDoc->load(CComVariant(filename.c_str()), &ok);
    if (hr != S_OK || ok == VARIANT_FALSE)
    {
        wstring err(L"Unable to open file: ");
        err += filename;
        throw Exception(Exception::UnableToOpen, err);
    }

    //
    // Get the document root node
    //
    CComPtr<IXMLDOMElement> rootElement;
    if (mDoc->get_documentElement(&rootElement) != S_OK ||
        rootElement.QueryInterface(&mRoot) != S_OK)
    {
        wstring err(L"Unable to find a root element in file: ");
        err += filename;
        throw Exception(Exception::NoRoot, err);
    }

}

void CXmlNode::Document::Create(const std::wstring &rootname)
{
    HRESULT hr = CoCreateInstance(CLSID_DOMDocument, NULL,
        CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, (void**)&mDoc);
    if (hr != S_OK)
    {
        wstring err(L"Failed to create an XML document to use");
        throw Exception(Exception::UnableToCreate, err);
    }

    // Create a processing instruction targeted for xml.
    // This creates the line:  <?xml version='1.0'>
    CComPtr<IXMLDOMProcessingInstruction> pi;
    CComPtr<IXMLDOMNode> pinode;
    mDoc->createProcessingInstruction(L"xml", L"version='1.0' encoding='UTF-8'", &pi);
    mDoc->appendChild(pi, &pinode);

    // Create the root element
    CComPtr<IXMLDOMElement> pe;
    mDoc->createElement(CComBSTR(rootname.c_str()), &pe);
    mDoc->appendChild(pe, &mRoot);
}

void CXmlNode::Document::Save(const std::wstring &filename)
{
    HRESULT hr = mDoc->save(CComVariant(filename.c_str()));
    if (hr != S_OK)
    {
        wstring err(L"Unable to write file: ");
        err += filename;
        throw Exception(Exception::UnableToWrite, err);
    }
}

std::wstring CXmlNode::Document::GetXML()
{
    CComBSTR xml;
    mDoc->get_xml(&xml);
    return wstring(xml);
}

