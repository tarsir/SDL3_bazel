# SDL3 Bazel Example

This repo is an example of how one can get an SDL3 C++ project
building with Bazel 8 by using modules.

## How to Run

If you just want to clone this repo and get started, the Bazel
invocation you seek is:

```sh
bazel run //:sdl3-test
```

### Suggestions

I recommend using [Bazelisk](https://github.com/bazelbuild/bazelisk)
to manage Bazel versions and make use of the `.bazelversion` file
in the repo.

## How it works

I'm not a Bazel expert, so this may be a flawed explanation!

For starters, I used [a Gist from
@k-bharadwaj](https://gist.github.com/k-bharadwaj/7f0922425a6ac6dd4b938894563b27a4)
as a starting point. Their Gist doesn't use modules, though, so I had to change
a few things.

Converting the `WORKSPACE` to a `MODULE.bazel` file wasn't too interesting,
since you can use the `http_archive` rule almost as-is. It's not even needed
for the `rules_foreign_cc` module, since it now exists in the [Bazel Central
Registry](https://registry.bazel.build/modules/rules_foreign_cc), so you can
just `bazel_dep` that one. The SDL archive was almost a copy-paste affair, I
just changed the `urls` to a single `url`.

The `third_party/sdl.BUILD` is where most of my experimenting to get it
building happened. The first thing that didn't work was the filename, but
renaming it to just `third_party/BUILD` fixed that.

The next block was the `defines` param to `cmake`, which could probably have
specified the other platforms like I did in `out_shared_libs`. Just adding the
`conditions:default` and an empty list as its value fixed that block.

The last thing I came across was that omitting the `out_shared_libs` parameter,
and trying to make Cmake build a static library instead, didn't seem to work by
just not specifying the shared libs parameter.
