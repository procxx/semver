#include <catch2/catch.hpp>

#include <version.hpp>
#include <iostream>


TEST_CASE("[basic] Check default version", "[multi-file]") {
  procxx::version ver;

  REQUIRE(ver.major == 0);
  REQUIRE(ver.minor == 1);
  REQUIRE(ver.patch == 0);
}

TEST_CASE("[version] 1. Check factory make_version()", "[multi-file]") {
  constexpr procxx::version ver = procxx::make_version(1, 2, 3);

  REQUIRE(ver.major == 1);
  REQUIRE(ver.minor == 2);
  REQUIRE(ver.patch == 3);
}

TEST_CASE("[version] 2. Check factory make_version()", "[multi-file]") {
  const std::string version_str = "1.2.3";
  procxx::version ver = procxx::make_version(version_str);

  REQUIRE(ver.major == 1);
  REQUIRE(ver.minor == 2);
  REQUIRE(ver.patch == 3);
}

TEST_CASE("[version] 3. Check factory make_version()", "[multi-file]") {
  const std::string version_str = "1.2.3-beta.2";
  procxx::version ver = procxx::make_version(version_str);

  REQUIRE(ver.major == 1);
  REQUIRE(ver.minor == 2);
  REQUIRE(ver.patch == 3);
  REQUIRE(ver.release == procxx::version::release_type::beta);
  REQUIRE(ver.release_number == 2);
}

TEST_CASE("[version] 4. Check factory make_version()", "[multi-file]") {
  const std::string versionStr = "1.a.3-beta.2";

  REQUIRE_THROWS(procxx::make_version(versionStr));
}

TEST_CASE("[version] 5. Check factory make_version()", "[multi-file]") {
  const std::string versionStr = "1.1.3-x.2";

  REQUIRE_THROWS(procxx::make_version(versionStr));
}

TEST_CASE("[version] 6. Check factory make_version()", "[multi-file]") {
  const std::string version_str = "2.1-alpha";
  procxx::version ver = procxx::make_version(version_str);

  REQUIRE(ver.major == 2);
  REQUIRE(ver.minor == 1);
  REQUIRE(ver.patch == 0);
  REQUIRE(ver.release == procxx::version::release_type::alpha);
  REQUIRE(ver.release_number == 0);
}

TEST_CASE("[version] 7. Check factory make_version()", "[multi-file]") {
  const std::string version_str = "2.1-nightly+20200101";
  procxx::version ver = procxx::make_version(version_str);

  REQUIRE(ver.major == 2);
  REQUIRE(ver.minor == 1);
  REQUIRE(ver.patch == 0);
  REQUIRE(ver.release == procxx::version::release_type::nightly);
  REQUIRE(ver.release_number == 0);
}

TEST_CASE("[version] 1. Check literal ctor \"_version\"", "[multi-file]") {
  using procxx::operator""_version;

  procxx::version ver = "1.2.3-beta.2"_version;

  REQUIRE(ver.major == 1);
  REQUIRE(ver.minor == 2);
  REQUIRE(ver.patch == 3);
  REQUIRE(ver.release == procxx::version::release_type::beta);
  REQUIRE(ver.release_number == 2);
}

TEST_CASE("[version] 1. Check \"is_less\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 3, 5);
  constexpr procxx::version ver2 = procxx::make_version(1, 4, 0);

  REQUIRE(ver1.is_less(ver2));
}

TEST_CASE("[version] 2. Check \"is_less\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 4, 5);
  constexpr procxx::version ver2 = procxx::make_version(1, 3, 8);

  REQUIRE(!ver1.is_less(ver2));
}

TEST_CASE("[version] 3. Check \"is_less\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 0, 0, procxx::version::release_type::alpha);
  constexpr procxx::version ver2 = procxx::make_version(1, 0, 0, procxx::version::release_type::beta);

  REQUIRE(ver1.is_less(ver2));
}

TEST_CASE("[version] 1. Check \"is_equal\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 3, 5);
  constexpr procxx::version ver2 = procxx::make_version(1, 3, 5);

  REQUIRE(ver1.is_equal(ver2));
}

TEST_CASE("[version] 2. Check \"is_equal\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 4, 5);
  constexpr procxx::version ver2 = procxx::make_version(1, 3, 8);

  REQUIRE(!ver1.is_equal(ver2));
}

TEST_CASE("[version] 3. Check \"is_equal\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 0, 0, procxx::version::release_type::alpha, 0);
  constexpr procxx::version ver2 = procxx::make_version(1, 0, 0, procxx::version::release_type::alpha, 0);

  REQUIRE(ver1.is_equal(ver2));
}

TEST_CASE("[version] 1. Check \"is_greater\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 4, 1);
  constexpr procxx::version ver2 = procxx::make_version(1, 3, 9);

  REQUIRE(ver1.is_greater(ver2));
}

TEST_CASE("[version] 2. Check \"is_greater\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 3, 8);
  constexpr procxx::version ver2 = procxx::make_version(1, 4, 5);

  REQUIRE(!ver1.is_greater(ver2));
}

TEST_CASE("[version] 3. Check \"is_greater\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 0, 0, procxx::version::release_type::beta, 0);
  constexpr procxx::version ver2 = procxx::make_version(1, 0, 0, procxx::version::release_type::alpha, 1);

  REQUIRE(ver1.is_greater(ver2));
}

TEST_CASE("[version] 1. Check \"is_less_or_equal\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 3, 5);
  constexpr procxx::version ver2 = procxx::make_version(1, 4, 0);

  REQUIRE(ver1.is_less_or_equal(ver2));
}

TEST_CASE("[version] 2. Check \"is_less_or_equal\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 4, 5);
  constexpr procxx::version ver2 = procxx::make_version(1, 3, 8);

  REQUIRE(!ver1.is_less_or_equal(ver2));
}

TEST_CASE("[version] 3. Check \"is_less_or_equal\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 3, 5);
  constexpr procxx::version ver2 = procxx::make_version(1, 3, 5);

  REQUIRE(ver1.is_less_or_equal(ver2));
}

TEST_CASE("[version] 1. Check \"is_greater_or_equal\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 4, 1);
  constexpr procxx::version ver2 = procxx::make_version(1, 3, 9);

  REQUIRE(ver1.is_greater(ver2));
}

TEST_CASE("[version] 2. Check \"is_greater_or_equal\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 3, 8);
  constexpr procxx::version ver2 = procxx::make_version(1, 4, 5);

  REQUIRE(!ver1.is_greater(ver2));
}

TEST_CASE("[version] 3. Check \"is_greater_or_equal\" for several versions", "[multi-file]") {
  constexpr procxx::version ver1 = procxx::make_version(1, 3, 8);
  constexpr procxx::version ver2 = procxx::make_version(1, 3, 8);

  REQUIRE(!ver1.is_greater(ver2));
}

TEST_CASE("[version] 1. \"to_string\" should return correct version string", "[multi-file]") {
  constexpr procxx::version ver = procxx::make_version(1, 3, 8);
  auto versionStr = procxx::to_string(ver);

  REQUIRE(versionStr == "1.3.8");
}

TEST_CASE("[version] 2. \"to_string\" should return correct version string", "[multi-file]") {
  constexpr procxx::version ver = procxx::make_version(1, 3, 8, procxx::version::release_type::alpha);
  auto versionStr = procxx::to_string(ver, procxx::version::low_zeros::hide);

  REQUIRE(versionStr == "1.3.8-alpha");
}

TEST_CASE("[version] 3. \"to_string\" should return correct version string", "[multi-file]") {
  constexpr procxx::version ver = procxx::make_version(1, 3, 8, procxx::version::release_type::beta);
  auto versionStr = procxx::to_string(ver, procxx::version::low_zeros::hide);

  REQUIRE(versionStr == "1.3.8-beta");
}

TEST_CASE("[version] 4. \"to_string\" should return correct version string", "[multi-file]") {
  constexpr procxx::version ver = procxx::make_version(1, 3, 8, procxx::version::release_type::rc, 1);
  auto versionStr = procxx::to_string(ver);

  REQUIRE(versionStr == "1.3.8-rc.1");
}

TEST_CASE("[version] 5. \"to_string\" should return correct version string", "[multi-file]") {
  constexpr procxx::version ver = procxx::make_version(1, 3, 0);
  auto versionStr = procxx::to_string(ver, procxx::version::low_zeros::hide);

  REQUIRE(versionStr == "1.3");
}

TEST_CASE("[version] 6. \"to_string\" should return correct version string", "[multi-file]") {
  constexpr procxx::version ver = procxx::make_version(1, 0, 0);
  auto versionStr = procxx::to_string(ver, procxx::version::low_zeros::hide);

  REQUIRE(versionStr == "1");
}

TEST_CASE("[version] 7. \"to_string\" should return correct version string", "[multi-file]") {
  constexpr procxx::version ver = procxx::make_version(1, 0, 0, procxx::version::release_type::alpha);
  auto versionStr = procxx::to_string(ver, procxx::version::low_zeros::hide);

  REQUIRE(versionStr == "1.0.0-alpha");
}
