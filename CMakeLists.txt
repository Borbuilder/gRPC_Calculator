cmake_minimum_required(VERSION 3.14)
project(gRPC_Calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_SRC_DIR ${CMAKE_SOURCE_DIR}/resources)
set(PROTO_FILE ${PROTO_SRC_DIR}/arithmetic.proto)

set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic" CACHE STRING "Vcpkg target triplet")
find_program(PROTOC_EXECUTABLE protoc)
find_program(GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
#find_program(GRPC_CPP_PLUGIN_EXECUTABLE
#   NAMES grpc_cpp_plugin
#    PATHS "<path to vcpkg>/vcpkg/installed/x64-windows/tools/grpc"
#    NO_DEFAULT_PATH
#    REQUIRED
#)

if(NOT PROTOC_EXECUTABLE)
  message(FATAL_ERROR "protoc не найден")
endif()

if(NOT GRPC_CPP_PLUGIN_EXECUTABLE)
  message(FATAL_ERROR "grpc_cpp_plugin не найден")
endif()

add_custom_command(
  OUTPUT ${GENERATED_DIR}/arithmetic.pb.cc ${GENERATED_DIR}/arithmetic.pb.h
         ${GENERATED_DIR}/arithmetic.grpc.pb.cc ${GENERATED_DIR}/arithmetic.grpc.pb.h
  COMMAND ${PROTOC_EXECUTABLE}
          --proto_path=${PROTO_SRC_DIR}
          --cpp_out=${GENERATED_DIR}
          --grpc_out=${GENERATED_DIR}
          --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE}
          ${PROTO_FILE}
  DEPENDS ${PROTO_FILE}
  COMMENT "Генерация gRPC и Protobuf исходников из ${PROTO_FILE}"
)

set(PROTO_SRCS
  ${GENERATED_DIR}/arithmetic.pb.cc
  ${GENERATED_DIR}/arithmetic.grpc.pb.cc
)
set(PROTO_HDRS
  ${GENERATED_DIR}/arithmetic.pb.h
  ${GENERATED_DIR}/arithmetic.grpc.pb.h
)

add_custom_target(GenerateProto ALL
  DEPENDS ${PROTO_SRCS} ${PROTO_HDRS}
)

add_library(arithmetic_proto
  ${PROTO_SRCS}
)
add_dependencies(arithmetic_proto GenerateProto)

target_include_directories(arithmetic_proto
  PUBLIC ${GENERATED_DIR}
)

target_link_libraries(arithmetic_proto
  PUBLIC
  protobuf::libprotobuf
  gRPC::grpc++
)

add_executable(client
  client/ArithmeticalClient.cpp
  client/ClientFunctions.cpp
  client/main.cpp
)

target_include_directories(client
  PRIVATE
  ${GENERATED_DIR}
  client
)

target_link_libraries(client
  PRIVATE
  arithmetic_proto
  protobuf::libprotobuf
  gRPC::grpc++
  ws2_32  
  crypt32
)

add_executable(server
  server/ArithmeticalService.cpp
  server/ServerFunctions.cpp
  server/main.cpp
)

target_include_directories(server
  PRIVATE
  ${GENERATED_DIR}
  server
)

target_link_libraries(server
  PRIVATE
  arithmetic_proto
  protobuf::libprotobuf
  gRPC::grpc++
  ws2_32  
  crypt32
)

