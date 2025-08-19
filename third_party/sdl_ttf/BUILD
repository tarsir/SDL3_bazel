load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "srcs",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)

cmake(
    name = "sdl3_ttf_shared",
    lib_source = ":srcs",
    defines = select({
        "@bazel_tools//src/conditions:darwin": [
            "CMAKE_OSX_DEPLOYMENT_TARGET=10.13",
        ],
        "//conditions:default": []
    }),
    out_include_dir = "include",
    out_interface_libs = select({
        "@bazel_tools//src/conditions:windows": ["SDL3_ttf.lib"],
        "//conditions:default": []
    }),
    out_shared_libs = select({
        "@bazel_tools//src/conditions:darwin": ["libSDL_ttf3.0.dylib"],
        "@bazel_tools//src/conditions:linux": ["libSDL3_ttf.so.0"],
        "@bazel_tools//src/conditions:windows": ["SDL3_ttf.dll"]
    }),
    visibility = ["//visibility:public"],
    deps = [
      "@com_github_sdl//:sdl3_shared"
    ]
)

cmake(
    name = "sdl3_ttf_static",
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
        "@bazel_tools//src/conditions:linux": ["libSDL3_ttf.a"],
        "@platforms//cpu:wasm32": ["libSDL3_ttf.a"],
        "@platforms//os:wasi": ["libSDL3_ttf.a"],
        "@bazel_tools//src/conditions:windows": ["SDL3_ttf.lib"] # is this right?
    }),
    visibility = ["//visibility:public"],
    deps = [
      "@com_github_sdl//:sdl3_static"
    ]
)
