#include "SymbolInfo.h"
using namespace std;

class ScopeTable
{
    SymbolInfo **symbols;
    ScopeTable *parentScope;
    int total_buckets = 0;
    int id;

public:
    ScopeTable(int id, int total_buckets, ScopeTable *parentScope)
    {
        this->id = id;
        this->total_buckets = total_buckets;

        symbols = new SymbolInfo *[total_buckets];

        fill(symbols, symbols + total_buckets, NULL);

        this->parentScope = parentScope;
    }

    int hashFunction(string name)
    {
        int hashValue = 0;

        for (int i = 0; i < name.length(); ++i)
        {
            hashValue += name[i];
        }

        return hashValue % total_buckets;
    }

    int getID() const
    {
        return id;
    }

    int getLength() const
    {
        return total_buckets;
    }

    ScopeTable *getParentScope() const
    {
        return parentScope;
    }

    SymbolInfo *lookUp(string name)
    {
        int index = hashFunction(name);
        int pos = 0;

        SymbolInfo *symbol = symbols[index];

        while (symbol != NULL)
        {
            if (key == symbol->getName())
            {
                cout << "Found in ScopeTable #" << id << " at position" << index << ", " << pos << endl;
                return temp;
            }
            pos++;
            symbol = symbol->getNext();
        }
        cout << "Not found in ScopeTable #" << id << endl;

        return NULL;
    }

    bool insertSymbol(SymbolInfo &symbol)
    {
        if (lookUp(symbol.getName()) != NULL)
        {
            cout << symbol << " already exists in the current ScopeTable" << endl;
            return false;
        }

        int index = hashFunction(symbol.getName());
        int pos = 0;

        SymbolInfo *temp = symbols[index];

        //If there is no symbol at that position
        if (temp == NULL)
        {
            symbols[index] = &symbol;
            symbol.setNext(NULL);
        }
        else
        {
            //if there is already a symbol at that position
            while (temp->getNext() != NULL)
            {
                temp = temp->getNext();
                pos++;
            }
            temp->setNext(&symbol);
            symbol.setNext(NULL);
        }
        cout << "Inserted in ScopeTable #" << id << " at position" << index << ++pos << endl;
        return true;
    }

    bool deleteSymbol(string name)
    {
        if (lookUp(name) == NULL)
        {
            cout << name << " not found" << endl;
            return false;
        }

        int index = hashFunction(name);
        int pos = 0;

        SymbolInfo *temp = symbols[index];
        SymbolInfo *previous = NULL;

        while (temp != NULL)
        {
            if (name == temp->getName())
            {
                break;
            }

            pos++;
            previous = temp;
            temp = temp->getNext();
        }

        if (previous == NULL)
        {
            symbols[index] = temp->getNext();
        }
        else
        {
            previous->setNext(temp->getNext());
        }

        delete temp; //Deletes the symbolInfo object

        cout << "Deleted entry at " << index << ", " << pos << " from current scopeTable" << endl;
    }

    void print()
    {
        for (int i = 0; i < total_buckets; ++i)
        {
            cout << i << " -->";

            SymbolInfo *temp = symbols[i];

            while (temp != NULL)
            {
                cout << " " << *temp;

                temp = temp->getNext();
            }

            cout << "\n";
        }
    }
};