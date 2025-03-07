load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")

cc_binary(
  name = "sdl3-shared",
  srcs = [
    "main.cpp"
  ],
  deps = [
    "@com_github_sdl//:sdl3_shared"
  ]
)

cc_binary(
    name = "sdl3-slib",
    srcs = [
        "main.cpp"
    ],
    deps = [
        "@com_github_sdl//:sdl3_static",
    ]
)

wasm_cc_binary(
  name = "sdl3-wasm",
  cc_target = ":sdl3-slib",
  outputs = [
    "sdl3-wasm.html",
    "sdl3-wasm.wasm",
    "sdl3-wasm.js"
  ]
)
