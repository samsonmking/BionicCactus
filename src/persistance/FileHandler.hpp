#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

class FileHandler {
public:
    virtual void save() = 0;
    virtual void load() = 0;
};

#endif