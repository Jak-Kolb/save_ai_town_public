cc_library(
    name = "api",
    srcs = glob(["**/*.cc"]),
    hdrs = glob(["**/*.h"]),
    deps = ["@cpp-httplib//:httplib", "@nlohmann_json//:json", "@yaml-cpp//:yaml-cpp"],
    visibility = ["//visibility:public"],
    data = ["superprompt.yaml"],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [":api"],
)