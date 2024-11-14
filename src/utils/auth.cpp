#include "utils/auth.h"
#include "models/user.h"
#include <jwt-cpp/jwt.h>

using std::string;

_UserAuth getUserAuthFromRequest(const Pistache::Rest::Request &request)
{
    auto authHeader = request.headers().getRaw("Authorization");
    auto token = authHeader.value();

    if (token.find("Bearer ") != 0)
    {
        throw std::runtime_error("Invalid authorization header format");
    }

    token = token.substr(7); // Remove "Bearer " prefix

    auto decoded = jwt::decode(token);
    auto verifier = jwt::verify()
                        .allow_algorithm(jwt::algorithm::hs256{"secret"})
                        .with_issuer("auth0");

    verifier.verify(decoded);

    _UserAuth userAuth;
    auto is_admin = decoded.get_payload_json().at("is_admin");

    throw std::runtime_error("Not implemented");

    return userAuth;
}

void checkRequestPermission(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &response)
{

}