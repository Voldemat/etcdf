#pragma once

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include "src/etcdf_protobuf/rpc.grpc.pb.h"
#include "src/etcdf_protobuf/rpc.pb.h"

namespace etcdf::server::v3_grpc {
class GRPCAuthService final : public etcdserverpb::Auth::Service {
    ::grpc::Status AuthEnable(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthEnableRequest *request,
        ::etcdserverpb::AuthEnableResponse *response) override;
    ::grpc::Status AuthStatus(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthStatusRequest *request,
        ::etcdserverpb::AuthStatusResponse *response) override;
    ::grpc::Status AuthDisable(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthDisableRequest *request,
        ::etcdserverpb::AuthDisableResponse *response) override;
    ::grpc::Status Authenticate(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthenticateRequest *request,
        ::etcdserverpb::AuthenticateResponse *response) override;
    ::grpc::Status UserAdd(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthUserAddRequest *request,
        ::etcdserverpb::AuthUserAddResponse *response) override;
    ::grpc::Status UserGet(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthUserGetRequest *request,
        ::etcdserverpb::AuthUserGetResponse *response) override;
    ::grpc::Status UserList(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthUserListRequest *request,
        ::etcdserverpb::AuthUserListResponse *response) override;
    ::grpc::Status UserDelete(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthUserDeleteRequest *request,
        ::etcdserverpb::AuthUserDeleteResponse *response) override;
    ::grpc::Status UserGrantRole(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthUserGrantRoleRequest *request,
        ::etcdserverpb::AuthUserGrantRoleResponse *response) override;
    ::grpc::Status UserRevokeRole(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthUserRevokeRoleRequest *request,
        ::etcdserverpb::AuthUserRevokeRoleResponse *response) override;
    ::grpc::Status UserChangePassword(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthUserChangePasswordRequest *request,
        ::etcdserverpb::AuthUserChangePasswordResponse *response) override;
    ::grpc::Status RoleAdd(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthRoleAddRequest *request,
        ::etcdserverpb::AuthRoleAddResponse *response) override;
    ::grpc::Status RoleGet(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthRoleGetRequest *request,
        ::etcdserverpb::AuthRoleGetResponse *response) override;
    ::grpc::Status RoleList(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthRoleListRequest *request,
        ::etcdserverpb::AuthRoleListResponse *response) override;
    ::grpc::Status RoleDelete(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthRoleDeleteRequest *request,
        ::etcdserverpb::AuthRoleDeleteResponse *response) override;
    ::grpc::Status RoleGrantPermission(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthRoleGrantPermissionRequest *request,
        ::etcdserverpb::AuthRoleGrantPermissionResponse *response) override;
    ::grpc::Status RoleRevokePermission(
        ::grpc::ServerContext *context,
        const ::etcdserverpb::AuthRoleRevokePermissionRequest *request,
        ::etcdserverpb::AuthRoleRevokePermissionResponse *response) override;
};
};  // namespace etcdf::server::v3_grpc
