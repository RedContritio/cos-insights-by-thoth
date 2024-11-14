#ifndef SERVICES_BASE_H
#define SERVICES_BASE_H

#include "repositories/base.h"

template <class T>
class BaseService {
public:
    BaseService(T& repository) : _repository(repository) {}
    virtual ~BaseService() {}
protected:
    T& _repository;
};

#endif