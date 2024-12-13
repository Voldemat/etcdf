#include "./auth.hpp"

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>

#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {
::grpc::Status GRPCAuthService::AuthEnable(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthEnableRequest *request,
    ::etcdserverpb::AuthEnableResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::AuthStatus(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthStatusRequest *request,
    ::etcdserverpb::AuthStatusResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::AuthDisable(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthDisableRequest *request,
    ::etcdserverpb::AuthDisableResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::Authenticate(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthenticateRequest *request,
    ::etcdserverpb::AuthenticateResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::UserAdd(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthUserAddRequest *request,
    ::etcdserverpb::AuthUserAddResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::UserGet(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthUserGetRequest *request,
    ::etcdserverpb::AuthUserGetResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::UserList(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthUserListRequest *request,
    ::etcdserverpb::AuthUserListResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::UserDelete(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthUserDeleteRequest *request,
    ::etcdserverpb::AuthUserDeleteResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::UserGrantRole(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthUserGrantRoleRequest *request,
    ::etcdserverpb::AuthUserGrantRoleResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::UserRevokeRole(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthUserRevokeRoleRequest *request,
    ::etcdserverpb::AuthUserRevokeRoleResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::UserChangePassword(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthUserChangePasswordRequest *request,
    ::etcdserverpb::AuthUserChangePasswordResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::RoleAdd(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthRoleAddRequest *request,
    ::etcdserverpb::AuthRoleAddResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::RoleGet(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthRoleGetRequest *request,
    ::etcdserverpb::AuthRoleGetResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::RoleList(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthRoleListRequest *request,
    ::etcdserverpb::AuthRoleListResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::RoleDelete(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthRoleDeleteRequest *request,
    ::etcdserverpb::AuthRoleDeleteResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::RoleGrantPermission(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthRoleGrantPermissionRequest *request,
    ::etcdserverpb::AuthRoleGrantPermissionResponse *response) {
    return grpc::Status::OK;
};
::grpc::Status GRPCAuthService::RoleRevokePermission(
    ::grpc::ServerContext *context,
    const ::etcdserverpb::AuthRoleRevokePermissionRequest *request,
    ::etcdserverpb::AuthRoleRevokePermissionResponse *response) {
    return grpc::Status::OK;
};
};  // namespace etcdf::server::v3_grpc
