#pragma once


namespace etcdf::server::shared {
class ServerHandle {
public:
    virtual void run() = 0;
    virtual void stop() = 0;
    virtual ~ServerHandle(){};
};
};  // namespace etcdf::server::shared
