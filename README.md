# SDL3 Bazel Example

This repo is an example of how one can get an SDL3 C++ project
building with Bazel 8 by using modules.

## How to Run

This repo uses Bazel as the build system, which gives us a form of package management (although
it's not always so simple) to pull in dependencies like SDL and emscripten.

A quick list of the useful Bazel targets is as follows:

```sh
bazel run //:engine # this is "development mode" with hot reload enabled
bazel run //:release # "release mode" with no hot reload and the game code linked statically
bazel build //:sdl3-wasm-js-only # build to WASM and JS, more info below
bazel build //:sdl3-wasm --features="-output_format_js" --linkopt="-o=sdl3-wasm.html" --linkopt="--oformat=html" # see below
```

### Suggestions

I recommend using [Bazelisk](https://github.com/bazelbuild/bazelisk)
to manage Bazel versions and make use of the `.bazelversion` file
in the repo.

### Building for development

The current version of the repo has a rough "development" mode, allowing for hot reload. This
can be started with:

```sh
bazel run //:engine
```

The current project may need some heavy modifications to work with more complex aspects of the
hot reload functionality, such as state migration between "world" versions.

The hot reload currently does not support WASM builds. For WASM, you can use...

### Building for WASM

Building to WASM requires Emscripten, which basically replaces the C/C++ compiler
in a build-to-WASM toolchain. Integrating Emscripten with Bazel modules isn't fully
supported, but there is a [handy in-progress branch](https://github.com/emscripten-core/emsdk/pull/1530)
that we can use by pointing the `git_repository` rule at the branch.

After several late nights of experimenting, I finally arrived at a better understanding of
Bazel and that branch, and here is the summary! The target and flags you'll use depend
on the artifact you want.

```sh
# to do the equivalent of `emcc main.cpp -o sdl3-wasm.html`
bazel build //:sdl3-wasm --features="-output_format_js" --linkopt="-o=sdl3-wasm.html" --linkopt="--oformat=html"
# if you just need the JS, you can instead do the simpler:
bazel build //:sdl3-wasm-js-only
```

In both cases, for some reason, the generated HTML/JS will have incorrect references to the
JS/WASM. It uses the `cc_target` name instead of the specified output names, so you
will need to correct them:

```html
<!-- bazel-bin/sdl3-wasm.html -->
<script
  async
  type="text/javascript"
  src="sdl3-example-static-linked.js"
></script>
```

```js
// bazel-bin/sdl3-wasm.js
function findWasmBinary() {
  return locateFile("sdl3-example-static-linked.wasm");
}
```

## Credits/Attributions

I would just like to thank some folks for a lot of the functionality in this
project:

- [A Gist from @k-bharadwaj](https://gist.github.com/k-bharadwaj/7f0922425a6ac6dd4b938894563b27a4)
  was the first thing I adapted
- [@kkpattern](https://github.com/kkpattern) who kindly submitted the first pull request, which
  added Windows support for one of the earlier project versions!
- [@iozsaygi](https://github.com/iozsaygi/sdl-hot-reload) who hasn't directly contributed, but I
  used a fair bit of the structure of their SDL hot reload code

## How it works

I'm not a Bazel expert, so this may be a flawed explanation!

First, I'd like to credit [a Gist from
@k-bharadwaj](https://gist.github.com/k-bharadwaj/7f0922425a6ac6dd4b938894563b27a4)
which gave me a starting point. Their Gist doesn't use modules, though, so I
had to change a few things.

### MODULE.bazel

The point I started with from there was the `MODULE.bazel` file. In there, we
declare two external dependencies for the project: SDL3 in the form of an
archive, and the `rules_foreign_cc` module, which provides Cmake and other
build toolchains.

`rules_foreign_cc` exists in the [Bazel Central
Registry](https://registry.bazel.build/modules/rules_foreign_cc), so we can
just declare it with `bazel_dep`, specify the version, and it's good to go.

SDL isn't in there for now, so we have to use the no-longer-built-in `http_archive`
rule to download and extract the latest 3.2 release from Github.

### third_party/BUILD

The Gist seems to use an older version of Bazel, but on Bazel 8, `BUILD` files
can only have the name `BUILD`. That's one change.

Inside the `cmake` invocation, I needed to make a couple changes. First, I
needed to specify `defines` for my platform (Linux on WSL, specifically), but
I just used the "default" case. Here's where you can put any of the Cmake
arguments that start with `-D`, and specify platforms if needed.

The other thing was I needed to add the Linux condition for the produced shared
library, and I added the Windows one as well. At first, I didn't realize the
produced filename has a `.0` at the end, so this was a minor skill issue.

I tried briefly to have this step make a static library, but didn't have much
success using the `defines` parameter and omitting the `out_shared_libs` parameter.
I'm sure it's possible - but I haven't figured it out yet.

### BUILD

The last piece is the top-level `BUILD` file, which is pretty much as-is from
the Gist. Specify a binary with `main.cpp` as the source file list, specify
the SDL3 built with the Cmake step as a dependency, and then it works!
