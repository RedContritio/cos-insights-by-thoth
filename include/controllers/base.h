#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include <pistache/http.h>
#include <pistache/router.h>

template <class T>
class BaseController {
public:
    BaseController(T& service) : _service(service) {}
    virtual ~BaseController() {}
protected:
    T& _service;
};

#endif