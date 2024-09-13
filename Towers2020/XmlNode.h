/**
 * \file
 *
 * \author Charles B. Owen
 *
 * @brief Class that implements a wrapper for msxml nodes. 
 */
#pragma once

#include <MsXml6.h>
#include <memory>
#include <string>
#include <exception>

namespace xmlnode
{

    /**
     * @brief A wrapper for msxml nodes.

     * MSXML was designed to be used by a variety of languages,
     * including C++, C#, and Visual Basic. Consequently, it is
     * a compromise that is very cumbersome to use. This class
     * is designed to simplify the process considerably.
     *
     * All an XML document is a tree of nodes. This class
     * represents nodes in that tree and the root node represents
     * that underlying document. This class can be used to
     * both create and load XML documents.
     *
     * \version 1.01 07-16-2014 Initial development 
     * \version 1.02 07-17-2014 Namespace, added GetXML, added tests
     * \version 1.03 07-17-2014 Exceptions
     */
    class CXmlNode
    {
    public:
        /** 
        * @brief Constructor
        *
        * Creates an empty CXmlNode with no attached XML document.
        * You can then call either Open or Create on the node. However,
        * the preferred method is to use the static member functions
        * OpenDocument and CreateDocument.
        */
        CXmlNode();

        /** @brief Destructor */
        virtual ~CXmlNode();

        /*
         * Document management functions
         */

         /**
         * @brief Open an XML document and return the document root node.
         *
         * @param filename Filename to open
         * @returns Document root node
         */
        static std::shared_ptr<CXmlNode> OpenDocument(const std::wstring &filename);

        /**
        * @brief Create an empty XML document and return the document root node.
        *
        * @param rootname The name for the root node.
        * @returns Document root node
        */
        static std::shared_ptr<CXmlNode> CreateDocument(const std::wstring &rootname);

        /** 
        * @brief Open a file as an XML document.
        * @param filename Filename to open
        */
        void Open(const std::wstring &filename);

        /**
        * @brief Create an empty XML document in this node.
        * @param rootname The name for the root node.
        */
        void Create(const std::wstring &rootname);

        /**
        * @brief Save XML document to a file.
        * @param filename File to save to
        * @throws CXmlNode::Exception If there are errors in saving
        */
        void Save(const std::wstring &filename);

        /**
        * @brief Obtain the created XML as a string.
        * @returns String containing created XML
        */
        std::wstring GetXML();

        /*
         * Node name, type, and value
         */

         /**
         * @brief The node name.
         * @returns Node name
         */
        std::wstring GetName() const;

        /**
        * @brief The node type
        * 
        * The possible node types are:
        * - NODE_INVALID
        * - NODE_ELEMENT
        * - NODE_ATTRIBUTE
        * - NODE_TEXT
        * - NODE_CDATA_SECTION
        * - NODE_ENTITY_REFERENCE
        * - NODE_ENTITY
        * - NODE_PROCESSING_INSTRUCTION
        * - NODE_COMMENT
        * - NODE_DOCUMENT
        * - NODE_DOCUMENT_TYPE
        * - NODE_DOCUMENT_FRAGMENT
        * - NODE_NOTATION
        *
        * The types that are usually important are:
        * - NODE_ELEMENT the XML tags
        * - NODE_TEXT text between tags
        * 
        * @returns The node type
        */
        DOMNodeType GetType() const;

        /**
        * @brief Get the node value
        * 
        * This is most useful for text and attributes.
        * @returns The node value as a string
        */
        std::wstring GetValue() const;

        /**
        * @brief Get the node value
        *
        * This is most useful for text and attributes.
        * @returns The node value as an integer
        * @throws std::invalid_argument if no conversion could be performed
        * @throws std::out_of_range if the converted value would 
        * fall out of the range of the result type or if the underlying function
        */
        int GetIntValue() const;

        /**
        * @brief Get the node value
        *
        * This is most useful for text and attributes.
        * @returns The node value as a double
        * @throws std::invalid_argument if no conversion could be performed
        * @throws std::out_of_range if the converted value would
        * fall out of the range of the result type or if the underlying function
        */
        double GetDoubleValue() const;

        /*
         * Attributes
         */

         /**
         * @brief Get an attribute.
         *
         * This returns a CXmlNode object that is the attribute.
         * You an then use the GetValue function to get the value of the attribute.
         * 
         * Calls to this function create a CXmlNode object as a wrapper for
         * the underlying attribute. Subsequent calls for the same attribute
         * will return a different object.
         *
         * @param name Attribute name
         * @returns Attribute as a CXmlNode object or null if attribute does not exist.
         */
        std::shared_ptr<CXmlNode> GetAttribute(const std::wstring &name);

        /**
        * @brief Get the value of an attribute.
        * @param name Name of the attribute
        * @param def Default value to return if attribute does not exist.
        * @returns Attribute value as a string or the default if does not exist.
        */
        std::wstring GetAttributeValue(const std::wstring &name, const std::wstring &def);

        /**
        * @brief Get the value of an attribute.
        * @param name Name of the attribute
        * @param def Default value to return if attribute does not exist.
        * @returns Attribute value as an int or the default if does not exist.
        * @throws std::invalid_argument if no conversion could be performed
        * @throws std::out_of_range if the converted value would
        * fall out of the range of the result type or if the underlying function
        */
        int GetAttributeIntValue(const std::wstring &name, int def);

        /**
        * @brief Get the value of an attribute.
        * @param name Name of the attribute
        * @param def Default value to return if attribute does not exist.
        * @returns Attribute value as a double or the default if does not exist.
        * @throws std::invalid_argument if no conversion could be performed
        * @throws std::out_of_range if the converted value would
        * fall out of the range of the result type or if the underlying function
        */
        double GetAttributeDoubleValue(const std::wstring &name, double def);

        /**
        * @brief Set an attribute on this node.
        * @param name Name of the attribute to set
        * @param val Value to set as a string
        */
        void SetAttribute(const std::wstring &name, const std::wstring &val);

        /**
        * @brief Set an attribute on this node.
        * @param name Name of the attribute to set
        * @param val Value to set as an integer
        */
        void SetAttribute(const std::wstring &name, int val);

        /**
        * @brief Set an attribute on this node.
        * @param name Name of the attribute to set
        * @param val Value to set as a double
        */
        void SetAttribute(const std::wstring &name, double val);

        class Children;

        /**
         * @brief Support for iterating over the children of a node
         */
        class Iterator
        {
        public:
			/// Friend class
            friend class CXmlNode;

            /** 
             * @brief Test to see if two iterator are at the same location
             * @param other The other object we are testing against
             * @returns true if they are equal.
             */
            bool operator!= (const Iterator& other) const
            {
                return mPos != other.mPos;
            }

            // this method must be defined after the definition of IntVector
            // since it needs to use it


            /**
             * @brief Operation * for the iterator. 
             *
             * Indiates the child that is the current iterator reference.
             *
             * @returns Pointer to child node.
             */
            std::shared_ptr<CXmlNode> operator* ();

            /** 
             * @brief Advance to the next item in the collection
             * @returns Reference to this iterator.
             */
            const Iterator& operator++ ()
            {
                ++mPos;
                return *this;
            }

        private:
            /** 
             * @brief Constructor
             * @param children The children object we iterate over
             * @param pos Initial position in the collection
             */
            Iterator(Children* children, int pos)
                : mPos(pos)
                , mChildren(children)
            {
            }

            /// Iterator position in the collection
            int mPos;     

            /// Pointer to the children object for the collection
            Children *mChildren; 
        };

        /**
         * @brief Representation of children to support iteration
         */
        class Children
        {
        public:
            /**
             * @brief Get the beginning of the child node collection.
             * @returns Iterator at beginning of collection.
             */
            Iterator begin();

            /**
             * @brief Get the end of the child node collection.
             * @returns Iterator at end of collection.
             */
            Iterator end();

			/// Friend class 
            friend class Iterator;

			/// Friend class
            friend class CXmlNode;

        private:
            /**
             * @brief Constructor
             * @param node Node this class represents the children of.
             */
            Children(CXmlNode *node);

            /// Node we are children of
            CXmlNode *mNode;       

            /// Node list of children
            CComPtr<IXMLDOMNodeList> mChildren; 
        };

        /**
         * @brief Exceptions for CXmlNode
         */
        class Exception : public std::exception
        {
        public:
            /** @brief Exception types */
            enum Types {
                /// No exception type indicated
                None,         
                /// Unable to open file to read
                UnableToOpen,   
                /// Unable to open file to write
                UnableToWrite,  
                /// Unable to create XML document
                UnableToCreate, 
                /// Not XML document root node
                NoRoot          
            };

            /** 
             * @brief Default Constructor 
             */
            Exception() {}

            /** 
             * @brief Copy Constructor 
             * @param other Object to copy 
             */
            Exception(const Exception &other) : mType(other.mType), mMsg(other.mMsg) {}
            
            /** 
             * @brief Assignment operator
             * @param other Object to copy 
             * @returns Reference to this object
             */
            Exception& operator= (const Exception &other) { mMsg = other.mMsg; mType = other.mType; }
            
            /** 
             * @brief Constructor
             * @param type Exception type
             * @param msg Message associated with exception 
             */
            Exception(Types type, const std::wstring &msg) : mType(type), mMsg(msg) {}
            
            /** @brief Destructor */
            virtual ~Exception() {}

            /** 
             * @brief Exception message
             * 
             * More verbose exception messages are provided in 
             * Unicode as they should be by the Message() function.
             * @returns "CXmlNode exception" 
             */
            virtual const char* what() const throw()
            {
                return "CXmlNode exception.";
            }

            /** 
             * @brief Exception message
             * @returns Exception message 
             */
            std::wstring Message() { return mMsg; }

            /** 
             * @brief Exception type
             * @returns Exception type of type CXmlNode::Exception::Types 
             */
            Types Type() { return mType; }

        private:
            /// Exception type
            Types mType = None; 

            /// Exception error message
            std::wstring mMsg; 
        };

        /** 
         * @brief Get a child node of this node by index
         * @param n Index into the child nodes
         * @returns The child node as a shared pointer
         */
        std::shared_ptr<CXmlNode> GetChild(int n);

        /**
         * @brief Get the children of this node.
         *
         * This allows the children to be iterated over easily 
         * using C++ 11 range for loops:
         * \code
         * for(auto child : node->GetChildren())
         * {
         *     child->...
         * }
         * \endcode
         * @returns CXmlNode::Children object suitable to use as an iterator.
         */
        Children GetChildren();

        /** 
         * @brief Number of children of this node
         * @returns Number of children
         */
        int GetNumChildren();

        /**
         * Support for adding new children
         * @param name The name of the child
         */
        std::shared_ptr<CXmlNode> AddChild(const std::wstring &name);

    private:
        /** 
         * @brief Constructor (private, used internally only)
         * @param parent The parent of this node
         * @param node The underlying msxml node
         */
        CXmlNode(CXmlNode *parent, IXMLDOMNode *node);

        /// @brief Nested class for an object that describes one XML document
        class Document
        {
        public:
            /**
             * @brief Constructor
             */
            Document();

            /**
             * @brief Destructor
             */
            ~Document();


            /** 
             * @brief Open the document
             * @param filename File to open
             * @throws CXmlNode::Exception If there are errors loading document
             */
            void Open(const std::wstring &filename);

            /** 
             * @brief Create a new, empty document.
             * @param rootname The name for the document root node.
             * @throws CXmlNode::Exception If there are errors creating the document
             */
            void Create(const std::wstring &rootname);

            /**
             * @brief Save the document to a file.
             * @param filename Filename to save as.
             * @throws CXmlNode::Exception If there are errors in saving
             */
            void Save(const std::wstring &filename);

            /**
             * @brief Returns the document as a string.
             * @returns XML data as a string
             */
            std::wstring GetXML();

            /** 
             * @brief Get pointer to the root node
             * @returns Pointer to root node 
             */
            IXMLDOMNode *GetRoot() { return mRoot; }

            /** 
             * @brief Get pointer to underlying document
             * @returns Pointer to underlying document 
             */
            IXMLDOMDocument *GetDoc() { return mDoc; }

        private:
            /// Underlying msxml document
            CComPtr<IXMLDOMDocument>  mDoc; 

            /// Document root node
            CComPtr<IXMLDOMNode> mRoot;     
        };

        // The open document

        /// Reference to the document
        std::shared_ptr<Document> mDocument;    

        /// msxml node
        CComPtr<IXMLDOMNode> mNode;             
    };

}
