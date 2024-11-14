#ifndef UTILS_AUTH_H
#define UTILS_AUTH_H

#include <string>
#include <pistache/http.h>
#include <pistache/router.h>

void checkRequestPermission(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter& response);

#endif