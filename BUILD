load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")

cc_library(
  name = "game",
  srcs = glob(["src/game.*"]),
  hdrs = [
    "src/game.h"
  ],
  deps = [
    "@com_github_sdl//:sdl3_shared",
  ]
)

cc_binary(
  name = "engine",
  data = [":game"],
  srcs = glob(["src/engine.*", "src/main.cpp"]),
  deps = [
    "@com_github_sdl//:sdl3_shared",
    ":game",
  ]
)

cc_binary(
  name = "release",
  srcs = glob(["src/**"], exclude=["src/main.cpp"]),
  deps = [
    "@com_github_sdl//:sdl3_shared"
  ]
)

cc_binary(
    name = "release-static-linked",
    srcs = glob(["src/**"], exclude=["src/main.cpp"]),
    deps = [
        "@com_github_sdl//:sdl3_static",
    ]
)

wasm_cc_binary(
  name = "sdl3-wasm",
  cc_target = ":release-static-linked",
  # emcc main.cpp -o sdl3-wasm.html
  outputs = [
    "sdl3-wasm.html",
    "sdl3-wasm.wasm",
    "sdl3-wasm.js"
  ]
)

wasm_cc_binary(
  name = "sdl3-wasm-js-only",
  cc_target = ":release-static-linked",
  outputs = [
    "sdl3-wasm-js-only.wasm",
    "sdl3-wasm-js-only.js"
  ]
)
