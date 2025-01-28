# Add support for foreign build systems
http_archive(
    name = "rules_foreign_cc",
    sha256 = "8e5605dc2d16a4229cb8fbe398514b10528553ed4f5f7737b663fdd92f48e1c2",
    strip_prefix = "rules_foreign_cc-0.13.0",
    url = "https://github.com/bazel-contrib/rules_foreign_cc/releases/download/0.13.0/rules_foreign_cc-0.13.0.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
# This sets up some common toolchains for building targets. For more details, please see
# https://bazelbuild.github.io/rules_foreign_cc/0.13.0/flatten.html#rules_foreign_cc_dependencies
rules_foreign_cc_dependencies(
    cmake_version = "3.31.1",
)

# Add SDL3 support
http_archive(
    name = "com_github_sdl",
    build_file = "//third_party:sdl.BUILD",
    urls = ["https://github.com/libsdl-org/SDL/releases/download/release-3.2.0/SDL3-3.2.0.tar.gz"],
    strip_prefix = "SDL3-3.2.0",
)
