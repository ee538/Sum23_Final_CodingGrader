cc_library(
    name = "CPPLib",
    srcs = ["q.cc"],
    hdrs = ["q.h"],
    copts = ["--std=c++20"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "student_test",
    srcs = ["student_test.cc"],
    copts = ["--std=c++20"],
    deps = [
        ":CPPLib",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "grader_test",
    timeout = "moderate",
    srcs = ["grader_test.cc"],
    copts = ["--std=c++20"],
    deps = [
        ":CPPLib",
        "@com_google_googletest//:gtest_main",
    ],
)
