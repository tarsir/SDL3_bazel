package(default_visibility = ["//visibility:public"])
load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "srcs",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)

cmake (
    name = "sdl3",
    lib_source = ":srcs",
    defines = select({
        "@bazel_tools//src/conditions:darwin": [
            "CMAKE_OSX_DEPLOYMENT_TARGET=10.13",
        ],
    }),
    out_include_dir = "include",
    out_shared_libs = select({
        "@bazel_tools//src/conditions:darwin": ["libSDL3.0.dylib"],
    }),
    visibility = ["//visibility:public"],
)
