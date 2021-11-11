#pragma once

#include <exception>
#include <string>
#include <string_view>

/// @file userver/ugrpc/server/errors.hpp
/// @brief Errors thrown by gRPC server streams

USERVER_NAMESPACE_BEGIN

namespace ugrpc::server {

/// @brief Base exception for all the server errors
class BaseError : public std::exception {
 public:
  explicit BaseError(std::string message);

  const char* what() const noexcept override;

 private:
  std::string message_;
};

/// @brief Error during an RPC
class RpcError : public BaseError {
 public:
  RpcError(std::string_view call_name, std::string_view additional_info);
};

/// @brief RPC failed without a status. This means that either the call got
/// cancelled using `TryCancel`, the deadline has expired, or the client
/// disconnected.
class RpcInterruptedError : public RpcError {
 public:
  RpcInterruptedError(std::string_view call_name, std::string_view stage);
};

}  // namespace ugrpc::server

USERVER_NAMESPACE_END