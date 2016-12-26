#include <stdint.h>
#include <stddef.h>

#include <cstdio>

#include "semver.hpp"

int main() {
    // Test 1
    std::printf("Format version object to string\n");
    Semver version1(1, 0, 0, Semver::Meta::Alpha);
    std::printf("Version 1: %s\n", (const char*)version1);

    printf("\n\n");

    // Test 2
    std::printf("Parse version string to object\n");
    Semver version2;
    printf("Version before parsing: %s\n", (const char*)version2);
    const char* versionStr = "2.12.10-betha.3";
    version2.fromString(versionStr);
    printf("Raw version string: %s\n",versionStr);
    printf("Parsed version: %s (for example: minor = %d)\n",
        (const char*)version2, version2.minor);

    printf("\n\n");

    // Test 3
    std::printf("Compare versions\n");
    std::printf("Equals:\n");
    Semver version3(1, 12, 0);
    Semver version4("1.12.0");
    std::printf("%s", (const char*)version3);
    std::printf(" %s ", version3.isEquals(version4) ? "=" : "!=");
    std::printf("%s\n", (const char*)version4);
    
    version3.fromString("1.20.0");
    version4.fromString("1.12.0");
    std::printf("%s", (const char*)version3);
    std::printf(" %s ", version3.isEquals(version4) ? "=" : "!=");
    std::printf("%s\n", (const char*)version4);

    std::printf("\n");
    std::printf("Greater then:\n");

    std::printf("%s", (const char*)version3);
    std::printf(" %s ", version3.isNewerThen(version4) ? ">" : "!>");
    std::printf("%s\n", (const char*)version4);

    std::printf("%s", (const char*)version4);
    std::printf(" %s ", version4.isNewerThen(version3) ? ">" : "!>");
    std::printf("%s\n", (const char*)version3);

    version3.fromString("1.12.0");
    version4.fromString("1.12.0-alpha");
    std::printf("%s", (const char*)version3);
    std::printf(" %s ", version3.isNewerThen(version4) ? ">" : "!>");
    std::printf("%s\n", (const char*)version4);

    std::printf("%s", (const char*)version4);
    std::printf(" %s ", version4.isNewerThen(version3) ? ">" : "!>");
    std::printf("%s\n", (const char*)version3);

    version3.fromString("1.12.0-alpha.3");
    version4.fromString("1.12.0-alpha.4");
    std::printf("%s", (const char*)version3);
    std::printf(" %s ", version3.isNewerThen(version4) ? ">" : "!>");
    std::printf("%s\n", (const char*)version4);

    std::printf("\n");
    std::printf("Less then:\n");

    std::printf("%s", (const char*)version3);
    std::printf(" %s ", version3.isOlderThen(version4) ? "<" : "!<");
    std::printf("%s\n", (const char*)version4);

    std::printf("%s", (const char*)version4);
    std::printf(" %s ", version4.isOlderThen(version3) ? "<" : "!<");
    std::printf("%s\n", (const char*)version3);

    return 0;
}