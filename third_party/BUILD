load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "srcs",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)

cmake(
    name = "sdl3_shared",
    lib_source = ":srcs",
    defines = select({
        "@bazel_tools//src/conditions:darwin": [
            "CMAKE_OSX_DEPLOYMENT_TARGET=10.13",
        ],
        "//conditions:default": []
    }),
    out_include_dir = "include",
    out_interface_libs = select({
        "@bazel_tools//src/conditions:windows": ["SDL3.lib"],
        "//conditions:default": []
    }),
    out_shared_libs = select({
        "@bazel_tools//src/conditions:darwin": ["libSDL3.0.dylib"],
        "@bazel_tools//src/conditions:linux": ["libSDL3.so.0"],
        "@bazel_tools//src/conditions:windows": ["SDL3.dll"]
    }),
    visibility = ["//visibility:public"],
)

cmake(
    name = "sdl3_static",
    lib_source = ":srcs",
    generate_args = ["-DSDL_STATIC=true", "-DSDL_SHARED=false"] + select({
        "@platforms//cpu:wasm32": ["-DEMSCRIPTEN=true"],
        "@platforms//os:wasi": ["-DEMSCRIPTEN=true"],
        "//conditions:default": []
    }),
    defines = select({
        "@bazel_tools//src/conditions:darwin": [
            "CMAKE_OSX_DEPLOYMENT_TARGET=10.13",
        ],
        "//conditions:default": []
    }),
    out_include_dir = "include",
    out_static_libs = select({
        "@bazel_tools//src/conditions:linux": ["libSDL3.a"],
        "@platforms//cpu:wasm32": ["libSDL3.a"],
        "@platforms//os:wasi": ["libSDL3.a"],
        "@bazel_tools//src/conditions:windows": ["SDL3.lib"] # is this right?
    }),
    visibility = ["//visibility:public"],
)
