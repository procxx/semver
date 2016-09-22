#include <stdint.h>
#include <stddef.h>

#include <cstdio>

#include "Semver.h"

int main() {
	// Test 1
	std::printf("Format version object to string\n");
	Utils::Semver version1(1, 0, 0, Utils::Semver::PreRelease::Alpha);
	std::printf("Version 1: %s\n", (const char*)version1);

	printf("\n\n");

	// Test 2
	std::printf("Parse version string to object\n");
	Utils::Semver version2;
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
	Utils::Semver version3(1, 12, 0);
	Utils::Semver version4("1.12.0");
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
	std::printf(" %s ", version3.isGreaterThen(version4) ? ">" : "!>");
	std::printf("%s\n", (const char*)version4);

	std::printf("%s", (const char*)version4);
	std::printf(" %s ", version4.isGreaterThen(version3) ? ">" : "!>");
	std::printf("%s\n", (const char*)version3);

	version3.fromString("1.12.0");
	version4.fromString("1.12.0-alpha");
	std::printf("%s", (const char*)version3);
	std::printf(" %s ", version3.isGreaterThen(version4) ? ">" : "!>");
	std::printf("%s\n", (const char*)version4);

	std::printf("%s", (const char*)version4);
	std::printf(" %s ", version4.isGreaterThen(version3) ? ">" : "!>");
	std::printf("%s\n", (const char*)version3);

	version3.fromString("1.12.0-alpha.3");
	version4.fromString("1.12.0-alpha.4");
	std::printf("%s", (const char*)version3);
	std::printf(" %s ", version3.isGreaterThen(version4) ? ">" : "!>");
	std::printf("%s\n", (const char*)version4);

	std::printf("\n");
	std::printf("Less then:\n");

	std::printf("%s", (const char*)version3);
	std::printf(" %s ", version3.isLesserThen(version4) ? "<" : "!<");
	std::printf("%s\n", (const char*)version4);

	std::printf("%s", (const char*)version4);
	std::printf(" %s ", version4.isLesserThen(version3) ? "<" : "!<");
	std::printf("%s\n", (const char*)version3);

	return 0;
}