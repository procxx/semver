#include <stdint.h>
#include <stddef.h>

#include <cstdio>

#include "semver.hpp"

int main() {
    char buffer[22];
    // Test 1
    std::printf("Format version object to string\n");
    Version version1(2, 0, 0, Version::Pre::Alpha);
    std::printf("Version 1: %s\n", Semver::toString(version1, buffer));

    printf("\n\n");

    // Test 2
    std::printf("Parse version string to object\n");
    Version version2;
    printf("Version before parsing: %s\n", Semver::toString(version2, buffer));
    const char* versionStr = "2.12.10-betha.3";
    version2 = Semver::fromString(versionStr);
    printf("Raw version string: %s\n",versionStr);
    printf("Parsed version: %s (for example: minor = %d)\n",
        Semver::toString(version2, buffer), version2.minor);

    printf("\n\n");

    // Test 3
    std::printf("Compare versions\n");
    std::printf("Equals:\n");
    Version version3(1, 12, 0);
    Version version4 = Semver::fromString("1.12.0");
    std::printf("%s", Semver::toString(version3, buffer));
    std::printf(" %s ", version3.isEquals(version4) ? "=" : "!=");
    std::printf("%s\n", Semver::toString(version4, buffer));
    
    version3 = Semver::fromString("1.20.0");
    version4 = Semver::fromString("1.12.0");
    std::printf("%s", Semver::toString(version3, buffer));
    std::printf(" %s ", version3.isEquals(version4) ? "=" : "!=");
    std::printf("%s\n", Semver::toString(version4, buffer));

    std::printf("\n");
    std::printf("Newer then:\n");

    std::printf("%s", Semver::toString(version3, buffer));
    std::printf(" %s ", version3.isNewerThen(version4) ? ">" : "!>");
    std::printf("%s\n", Semver::toString(version4, buffer));

    std::printf("%s", Semver::toString(version4, buffer));
    std::printf(" %s ", version4.isNewerThen(version3) ? ">" : "!>");
    std::printf("%s\n", Semver::toString(version3, buffer));

    version3 = Semver::fromString("1.12.0");
    version4 = Semver::fromString("1.12.0-alpha");
    std::printf("%s", Semver::toString(version3, buffer));
    std::printf(" %s ", version3.isNewerThen(version4) ? ">" : "!>");
    std::printf("%s\n", Semver::toString(version4, buffer));

    std::printf("%s", Semver::toString(version4, buffer));
    std::printf(" %s ", version4.isNewerThen(version3) ? ">" : "!>");
    std::printf("%s\n", Semver::toString(version3, buffer));

    version3 = Semver::fromString("1.12.0-alpha.3");
    version4 = Semver::fromString("1.12.0-alpha.4");
    std::printf("%s", Semver::toString(version3, buffer));
    std::printf(" %s ", version3.isNewerThen(version4) ? ">" : "!>");
    std::printf("%s\n", Semver::toString(version4, buffer));

    std::printf("\n");
    std::printf("Older then:\n");

    std::printf("%s", Semver::toString(version3, buffer));
    std::printf(" %s ", version3.isOlderThen(version4) ? "<" : "!<");
    std::printf("%s\n", Semver::toString(version4, buffer));

    std::printf("%s", Semver::toString(version4, buffer));
    std::printf(" %s ", version4.isOlderThen(version3) ? "<" : "!<");
    std::printf("%s\n", Semver::toString(version3, buffer));

    return 0;
}