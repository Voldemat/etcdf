#pragma once

#include <drogon/HttpSimpleController.h>

#include <functional>

#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"
#include "drogon/HttpTypes.h"

namespace etcdf::server {

class TestController : public drogon::HttpSimpleController<TestController, false> {
public:
    void asyncHandleHttpRequest(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback)
        override;
    PATH_LIST_BEGIN
    PATH_ADD("/version", drogon::Get);
    PATH_LIST_END
};
};  // namespace etcdf::server
