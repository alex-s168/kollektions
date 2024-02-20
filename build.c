//
// Created by Alexander Nutz on 17/02/2024.
//

#define CC  "clang"
#define CXX "clang++"
#define AR  "ar"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

#define error(msg) fprintf(stderr, "%s", msg)

enum CompileType {
    CT_C,
    CT_CXX,
    CT_NOC,
    CT_DEP,
};

enum CompileResult {
    CR_OK = 0,
    CR_FAIL = 1,
    CR_FAIL_2 = 2,
};

struct CompileData {
    char *srcFile;
    char *outFile;
    enum CompileType type;
};

void *compileThread(void *arg);
enum CompileResult linkTask(struct CompileData *objs, size_t len, char *out);
enum CompileResult link_exe(struct CompileData *objs, size_t len, char *out);
enum CompileResult compile(struct CompileData *objs, size_t len);
enum CompileResult verifyDependencies(struct CompileData *objs, size_t len);

bool exists(char *file) {
    return access(file, F_OK) == 0;
}

/* ========================================================================= */

struct CompileData target_kallok_files[] = {
        { .type = CT_C, .srcFile = "alloc/libc.c", .outFile = "build/alloc/libc.o" }
};

#define TARGET_KALLOK_FILES_LEN (sizeof(target_kallok_files) / sizeof(target_kallok_files[0]))

enum CompileResult target_kallok() {
    enum CompileResult r1 = compile(target_kallok_files, TARGET_KALLOK_FILES_LEN);
    if (r1 != CR_OK)
        return CR_FAIL_2;

    enum CompileResult r2 = linkTask(target_kallok_files, TARGET_KALLOK_FILES_LEN, "build/kallok.a");
    return r2;
}

/* ========================================================================= */

struct CompileData target_kollektions_files[] = {
        { .type = CT_C, .srcFile = "dynamic_list/add_and_addAll.c", .outFile = "build/dynamic_list/add_and_addAll.o" },
        { .type = CT_C, .srcFile = "dynamic_list/init_and_clear.c", .outFile = "build/dynamic_list/init_and_clear.o" },
        { .type = CT_C, .srcFile = "dynamic_list/insertAt_and_insertAllAt.c", .outFile = "build/dynamic_list/insertAt_and_insertAllAt.o" },
        { .type = CT_C, .srcFile = "dynamic_list/removeAt_and_removeRange.c", .outFile = "build/dynamic_list/removeAt_and_removeRange.o" },
        { .type = CT_C, .srcFile = "dynamic_list/reserve_and_shrink.c", .outFile = "build/dynamic_list/reserve_and_shrink.o" },

        { .type = CT_C, .srcFile = "fixed_list/get_and_set.c", .outFile = "build/fixed_list/get_and_set.o" },
        { .type = CT_C, .srcFile = "fixed_list/indexOf.c", .outFile = "build/fixed_list/indexOf.o" },

        { .type = CT_C, .srcFile = "lists/copy.c", .outFile = "build/lists/copy.o" },

        { .type = CT_C, .srcFile = "static_list/add_and_addAll.c", .outFile = "build/static_list/add_and_addAll.o" },
        { .type = CT_C, .srcFile = "static_list/init_and_clear.c", .outFile = "build/static_list/init_and_clear.o" },
        { .type = CT_C, .srcFile = "static_list/insertAt_and_insertAllAt.c", .outFile = "build/static_list/insertAt_and_insertAllAt.o" },
        { .type = CT_C, .srcFile = "static_list/removeAt_and_removeRange.c", .outFile = "build/static_list/removeAt_and_removeRange.o" },

        { .type = CT_C, .srcFile = "blocking_list/access.c", .outFile = "build/blocking_list/access.o" },
        { .type = CT_C, .srcFile = "blocking_list/init_and_destroy.c", .outFile = "build/blocking_list/init_and_destroy.o" },
};

#define TARGET_KOLLEKTIONS_FILES_LEN (sizeof(target_kollektions_files) / sizeof(target_kollektions_files[0]))

enum CompileResult target_kollektions() {
    enum CompileResult r1 = compile(target_kollektions_files, TARGET_KOLLEKTIONS_FILES_LEN);
    if (r1 != CR_OK)
        return CR_FAIL_2;

    enum CompileResult r2 = linkTask(target_kollektions_files, TARGET_KOLLEKTIONS_FILES_LEN, "build/kollektions.a");
    return r2;
}

/* ========================================================================= */

struct CompileData target_test_cpp_files[] = {
        // sources:
        { .type = CT_CXX, .srcFile = "test_cpp.cpp", .outFile = "build/test_cpp.o" },

        // dependencies:
        { .type = CT_DEP, .srcFile = "", .outFile = "build/kallok.a" },
        { .type = CT_DEP, .srcFile = "", .outFile = "build/kollektions.a" },
};

#define TARGET_TEST_CPP_FILES_LEN (sizeof(target_test_cpp_files) / sizeof(target_test_cpp_files[0]))

enum CompileResult target_test_cpp() {
    enum CompileResult r3 = verifyDependencies(target_test_cpp_files, TARGET_TEST_CPP_FILES_LEN);
    if (r3 != CR_OK)
        return CR_FAIL;

    enum CompileResult r1 = compile(target_test_cpp_files, TARGET_TEST_CPP_FILES_LEN);
    if (r1 != CR_OK)
        return CR_FAIL_2;

    enum CompileResult r2 = link_exe(target_test_cpp_files, TARGET_TEST_CPP_FILES_LEN, "build/test_cpp.exe");
    return r2;
}

/* ========================================================================= */

struct CompileData target_test_list_files[] = {
	// sources:
	{ .type = CT_C, .srcFile = "test_list.c", .outFile = "build/test_list.o" },

	// dependencies:
	{ .type = CT_DEP, .srcFile = "", .outFile = "build/kallok.a" },
        { .type = CT_DEP, .srcFile = "", .outFile = "build/kollektions.a" },
};

#define TARGET_TEST_LIST_FILES_LEN (sizeof(target_test_list_files) / sizeof(target_test_list_files[0]))

enum CompileResult target_test_list() {
    enum CompileResult r3 = verifyDependencies(target_test_list_files, TARGET_TEST_LIST_FILES_LEN);
    if (r3 != CR_OK)
        return CR_FAIL;

    enum CompileResult r1 = compile(target_test_list_files, TARGET_TEST_LIST_FILES_LEN);
    if (r1 != CR_OK)
        return CR_FAIL_2;

    enum CompileResult r2 = link_exe(target_test_list_files, TARGET_TEST_LIST_FILES_LEN, "build/test_list.exe");
    return r2;
}

/* ========================================================================= */

struct Target {
    char *name;
    enum CompileResult (*run)();
};

struct Target targets[] = {
	{ .name = "kallok.a", .run = target_kallok },
	{ .name = "kollektions.a", .run = target_kollektions },
	{ .name = "test_cpp.exe", .run = target_test_cpp },
	{ .name = "test_list.exe", .run = target_test_list },
};

#define TARGETS_LEN (sizeof(targets) / sizeof(targets[0]))

int main(int argc, char **argv) {
    if (argc != 2)
	goto invalid_target;

    char *target = argv[1];

    bool found = false;
    for (size_t i = 0; i < TARGETS_LEN; i ++) {
    	struct Target tg = targets[i];
	if (strcmp(target, tg.name) == 0) {
            found = true;
	    enum CompileResult r = tg.run();
	    if (r == CR_FAIL) {
		error("FAIL\n");
		return 1;
	    } else if (r == CR_FAIL_2) {
		error("FAIL_2\n");
	    	return 1;
	    }
	    break;
	}
    }

    if (!found)
	goto invalid_target;

    return 0;

    invalid_target:
        error("Invalid target! Targets:\n");
	for (size_t i = 0; i < TARGETS_LEN; i ++) {
	    fprintf(stderr, "- \"%s\"\n", targets[i].name);
	}
        return 2;
}

void *compileThread(void *arg) {
    struct CompileData *data = arg;
    if (data->type == CT_C) {
        char *args = malloc(strlen(data->srcFile) + strlen(data->outFile) +
                            sizeof(CC) + 9);
        args[0] = '\0';
        sprintf(args, "%s -c %s -o %s", CC, data->srcFile, data->outFile);

        int res = system(args);
        free(args);
        if (res != 0) {
            printf("%i\n", res);
            return (void *) CR_FAIL;
        }
    } else if (data->type == CT_CXX) {
        char *args = malloc(strlen(data->srcFile) + strlen(data->outFile) +
                            sizeof(CXX) + 9);
        args[0] = '\0';
        sprintf(args, "%s -c %s -o %s", CXX, data->srcFile, data->outFile);

        int res = system(args);
        free(args);
        if (res != 0) {
            printf("%i\n", res);
            return (void *) CR_FAIL;
        }
    }
    return (void *) CR_OK;
}

enum CompileResult linkTask(struct CompileData *objs, size_t len, char *out) {
    size_t sl = strlen(out) + 6 + sizeof(AR);
    for (size_t i = 0; i < len; i ++) {
        sl += strlen(objs[i].outFile) + 1;
    }
    char *cmd = malloc(sl);
    cmd[0] = '\0';
    sprintf(cmd, "%s rcs %s ", AR, out);

    for (size_t i = 0; i < len; i ++) {
        strcat(cmd, objs[i].outFile);
        strcat(cmd, " ");
    }

    int res = system(cmd);
    free(cmd);
    if (res == 0)
        return CR_OK;
    return CR_FAIL;
}

enum CompileResult link_exe(struct CompileData *objs, size_t len, char *out) {
    size_t sl = strlen(out) + 5 + sizeof(CC);
    for (size_t i = 0; i < len; i ++) {
        sl += strlen(objs[i].outFile) + 1;
    }
    char *cmd = malloc(sl);
    cmd[0] = '\0';
    sprintf(cmd, "%s -o %s ", CC, out);

    for (size_t i = 0; i < len; i ++) {
        strcat(cmd, objs[i].outFile);
        strcat(cmd, " ");
    }

    int res = system(cmd);
    free(cmd);
    if (res == 0)
        return CR_OK;
    return CR_FAIL;
}

enum CompileResult compile(struct CompileData *objs, size_t len) {
    pthread_t *threads = malloc(sizeof(pthread_t) * len);

    for (size_t i = 0; i < len; i ++) {
        pthread_create(&threads[i], NULL, compileThread, &objs[i]);
    }

    for (size_t i = 0; i < len; i ++) {
        void *resr;
        pthread_join(threads[i], &resr);
        enum CompileResult res = (enum CompileResult) (intptr_t) resr;

        if (res != CR_OK) {
            for (size_t j = 0; j < len; j ++) {
                if (i == j)
                    continue;

                pthread_kill(threads[j], SIGABRT);
            }
            free(threads);
            return CR_FAIL;
        }
    }

    free(threads);
    return CR_OK;
}

enum CompileResult verifyDependencies(struct CompileData *objs, size_t len) {
    size_t err = 0;
    for (size_t i = 0; i < len; i ++) {
        if (objs[i].type != CT_DEP)
            continue;

        char *f = objs[i].outFile;
        if (!exists(f)) {
            error("Missing dependency:\n ");
            error(f);
            error("\n");
            err ++;
        }
    }
    if (err > 0)
        return CR_FAIL;
    return CR_OK;
}
