#ifndef IDMANAGER_H
#define IDMANAGER_H


class IdManager
{
public:
    static IdManager& Instance();
    unsigned int GetId();
private:
    IdManager();
    IdManager(const IdManager& root) = delete;
    IdManager& operator=(const IdManager&) = delete;
    unsigned int m_currentId;
};

#endif // IDMANAGER_H
