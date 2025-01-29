load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

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
        "//conditions:default": [
        ]
    }),
    out_include_dir = "include",
    out_shared_libs = select({
        "@bazel_tools//src/conditions:darwin": ["libSDL3.0.dylib"],
        "@bazel_tools//src/conditions:linux": ["libSDL3.so.0"],
        "@bazel_tools//src/conditions:windows": ["libSDL3.dll"]
    }),
    visibility = ["//visibility:public"],
)
