#define CC        "clang"
#define CC_ARGS   "-O2"

#define CXX       "clang++"
#define CXX_ARGS  "-O2"

#include "build_c/build.h"

/* ========================================================================= */

struct CompileData target_kallok_files[] = {
    DIR("build/"),

    DIR("build/alloc/"),
    SP(CT_C, "alloc/libc.c"),
    SP(CT_C, "alloc/statistic.c"),
    SP(CT_C, "alloc/pages.c"),
    SP(CT_C, "alloc/virtual.c"),
    SP(CT_C, "alloc/fixed_basic.c"),
    SP(CT_C, "alloc/paged.c"),
    SP(CT_C, "alloc/basic.c"),
};

enum CompileResult target_kallok() {
    START;
    DO(compile(LI(target_kallok_files)));
    DO(linkTask(LI(target_kallok_files), "build/kallok.a"));
    END;
}

/* ========================================================================= */

struct CompileData target_kollektions_files[] = {
    DIR("build/"),

    DIR("build/dynamic_list/"),
    SP(CT_C, "dynamic_list/add_and_addAll.c"),
    SP(CT_C, "dynamic_list/init_and_clear.c"),
    SP(CT_C, "dynamic_list/insertAt_and_insertAllAt.c"),
    SP(CT_C, "dynamic_list/removeAt_and_removeRange.c"),
    SP(CT_C, "dynamic_list/reserve_and_shrink.c"),

    DIR("build/fixed_list/"),
    SP(CT_C, "fixed_list/get_and_set.c"),
    SP(CT_C, "fixed_list/indexOf.c"),

    DIR("build/lists/"),
    SP(CT_C, "lists/copy.c"),

    DIR("build/static_list/"),
    SP(CT_C, "static_list/add_and_addAll.c"),
    SP(CT_C, "static_list/init_and_clear.c"),
    SP(CT_C, "static_list/insertAt_and_insertAllAt.c"),
    SP(CT_C, "static_list/removeAt_and_removeRange.c"),

    DIR("build/blocking_list/"),
    SP(CT_C, "blocking_list/access.c"),
    SP(CT_C, "blocking_list/init_and_destroy.c"),

    DIR("build/linked_list/"),
    SP(CT_C, "linked_list/add.c"),
    SP(CT_C, "linked_list/addAll.c"),
    SP(CT_C, "linked_list/clear.c"),
    SP(CT_C, "linked_list/find.c"),
    SP(CT_C, "linked_list/findLast.c"),
    SP(CT_C, "linked_list/flatten.c"),
    SP(CT_C, "linked_list/fromFixed.c"),
    SP(CT_C, "linked_list/fromLinks.c"),
    SP(CT_C, "linked_list/linkAt.c"),
    SP(CT_C, "linked_list/remove.c"),
    SP(CT_C, "linked_list/removeMultiple.c"),
};

enum CompileResult target_kollektions() {
    START;
    DO(compile(LI(target_kollektions_files)));
    DO(linkTask(LI(target_kollektions_files), "build/kollektions.a"));
    END;
}

/* ========================================================================= */

enum CompileResult target_tests() {
    START;

#define t(id, file) test("tests/", "tests/" file ".c", id, CT_C, \
        DEP("build/kallok.a"), \
        DEP("build/kollektions.a"))
   
    t(0, "t00_fixed_basic_alloc");
    t(1, "t01_list");
    t(3, "t03_paged_alloc");
    t(2, "t02_basic_alloc");

#undef t 

    END;
}

/* ========================================================================= */

struct Target targets[] = {
	{ .name = "kallok.a",       .run = target_kallok },
	{ .name = "kollektions.a",  .run = target_kollektions },
	{ .name = "tests",          .run = target_tests },
};

#define TARGETS_LEN (sizeof(targets) / sizeof(targets[0]))

int main(int argc, char **argv) {
    return build_main(argc, argv, targets, TARGETS_LEN);
}
