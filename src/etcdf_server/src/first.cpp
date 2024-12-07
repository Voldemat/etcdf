#include "./first.hpp"

#include <functional>

#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"

namespace etcdf::server {
void TestController::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    auto response = drogon::HttpResponse::newHttpResponse();
    response->setBody("1.0.0");
    response->setExpiredTime(0);
    callback(response);
};
};  // namespace etcdf::server
