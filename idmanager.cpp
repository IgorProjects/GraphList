#include "idmanager.h"

IdManager& IdManager::Instance()
{
    static IdManager theSingleInstance;
    return theSingleInstance;
}

unsigned int IdManager::GetId()
{
    return m_currentId++;
}

IdManager::IdManager()
    : m_currentId(1)
{}
