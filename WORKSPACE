workspace(name = "save_ai_town")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "save-ai-town",
    remote = "https://github.com/dcloran/save-ai-town"
)

load("@rules_yaml//:defs.bzl", "yaml_repositories")

# This sets up the dependencies for rules_yaml
yaml_repositories()