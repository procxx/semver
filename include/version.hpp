#include <cstdint>
#include <string>
#include <sstream>
#include <list>
#include <regex>
#include <vector>
#include <utility>


namespace procxx {
  class base_version {
  public:
    // Types
    enum class release_type {
      nightly   = 1,
      alpha     = 10,
      beta      = 20,
      rc        = 30,
      release   = 1000
    };

    enum class low_zeros {
      hide      = 0,
      show      = 1
    };
  };

  class version_exception : public std::exception {
  public:
    version_exception (const char* message)
      : msg(message)
    {}

    const char* what () const noexcept override { return msg; }

  private:
    const char* msg;
  };

  class version : public base_version {
  public:
    // Fields

    uint32_t             major;
    uint32_t             minor;
    uint32_t             patch;
    release_type        release;
    uint32_t             release_number;

    // Ctors

    constexpr version();

    // API of instanced object
 
    constexpr bool is_equal (const version& ver) const;
    constexpr bool is_not_equal (const version& ver) const { return !is_equal(ver); }
    constexpr bool is_greater (const version& ver) const;
    constexpr bool is_greater_or_equal (const version& ver) const;
    constexpr bool is_less (const version& ver) const;
    constexpr bool is_less_or_equal (const version& ver) const;

    constexpr bool operator < (const version& ver) const { return is_less(ver); }
    constexpr bool operator <= (const version& ver) const {  return is_less_or_equal(ver); }
    constexpr bool operator > (const version& ver) const { return is_greater(ver); }
    constexpr bool operator >= (const version& ver) const { return is_greater_or_equal(ver); }
    constexpr bool operator == (const version& ver) const { return is_equal(ver); }
    constexpr bool operator != (const version& ver) const {  return !is_equal(ver); }
  private:
  };

  // Utilites

  template<typename string_type = std::string>
  string_type to_string(
    const version& ver,
    const version::low_zeros low_zeros_format = version::low_zeros::show
  );

  template<typename string_type = std::string>
  constexpr string_type to_string(const base_version::release_type type);

  template<typename string_type = std::string>
  constexpr base_version::release_type from_string(const string_type& str);

  // Factory methods

  constexpr version make_version(
    const uint32_t major = 0,
    const uint32_t minor = 1,
    const uint32_t patch = 0,
    const version::release_type release = base_version::release_type::release,
    const uint32_t release_number = 0
  );

  template<typename string_type = std::string>
  version make_version(
    const string_type& str
  );

  version operator""_version (const char* str, const std::size_t size) {
    const std::string tempStr(str, size);
    return make_version<std::string>(tempStr);
  }

  // Typedefs

  // ==========================================================================

  constexpr version::version()
    : major(0), minor(1), patch(0),
      release(base_version::release_type::release), release_number(0)
  {}

  constexpr bool version::is_equal (const version& ver) const {
    return (
      major == ver.major &&
      minor == ver.minor &&
      patch == ver.patch &&
      release == ver.release &&
      release_number == ver.release_number
    );
  }
 
  constexpr bool version::is_greater (const version& ver) const {
    if (major > ver.major) { return true; }
    if (major < ver.major) { return false; }

    if (minor > ver.minor) { return true; }
    if (minor < ver.minor) { return false; }

    if (patch > ver.patch) { return true; }
    if (patch < ver.patch) { return false; }

    if (release > ver.release) { return true; }
    if (release < ver.release) { return false; }

    if (release_number > ver.release_number) { return true; }
    if (release_number < ver.release_number) { return false; }

    return false;
  }

  constexpr bool version::is_greater_or_equal (const version& ver) const {
    return is_greater(ver) || is_equal(ver);
  }

  constexpr bool version::is_less (const version& ver) const {
    if (major < ver.major) { return true; }
    if (major > ver.major) { return false; }

    if (minor < ver.minor) { return true; }
    if (minor > ver.minor) { return false; }

    if (patch < ver.patch) { return true; }
    if (patch > ver.patch) { return false; }

    if (release < ver.release) { return true; }
    if (release > ver.release) { return false; }

    if (release_number < ver.release_number) { return true; }
    if (release_number > ver.release_number) { return false; }

    return false;
  }

  constexpr bool version::is_less_or_equal (const version& ver) const {
    return is_less(ver) || is_equal(ver);
  }

  // --------------------------------------------------------------------------

  template<typename string_type>
  string_type to_string(
    const version& ver,
    const base_version::low_zeros low_zeros_format
  ) {
    std::stringstream result;

    result << ver.major;

    if (
      (ver.minor == 0 && low_zeros_format == base_version::low_zeros::show) ||
      ver.minor > 0 ||
      ver.release != base_version::release_type::release
    ) {
      result << '.' << ver.minor;
    }

    if (
      (ver.patch == 0 && low_zeros_format == base_version::low_zeros::show) ||
      ver.patch > 0 ||
      ver.release != base_version::release_type::release
    ) {
      result << '.' << ver.patch;
    }

    if (ver.release != base_version::release_type::release) {
      result << '-' << to_string<string_type>(ver.release);

      if (ver.release_number > 0) {
        result << '.' << ver.release_number;
      }
    }

    return result.str();
  }

  template<typename string_type>
  constexpr string_type to_string(const base_version::release_type type) {
    switch (type) {
      case base_version::release_type::alpha:
        return "alpha";

      case base_version::release_type::beta:
        return "beta";

      case base_version::release_type::rc:
        return "rc";

      case base_version::release_type::nightly:
        return "nightly";

      default:
        return "";
    }
  }

  template<typename string_type>
  constexpr base_version::release_type from_string(const string_type& str) {
    if (str == "nightly") { return base_version::release_type::nightly; }
    if (str == "alpha") { return base_version::release_type::alpha; }
    if (str == "beta") { return base_version::release_type::beta; }
    if (str == "rc") { return base_version::release_type::rc; }

    return base_version::release_type::release;
  }

  constexpr version make_version(
    const uint32_t major,
    const uint32_t minor,
    const uint32_t patch,
    const base_version::release_type release,
    const uint32_t release_number
  ) {
    version result;

    result.major = major;
    result.minor = minor;
    result.patch = patch;
    result.release = release;
    result.release_number = release_number;

    return result;
  }

  namespace internal {
    template<typename string_type = std::string>
    std::list<string_type> split (const string_type& str, const string_type& delims) {
      std::list<string_type> tokens;
      std::size_t current = str.find_first_of(delims);
      std::size_t previous = 0;

      while (current != std::string::npos) {
          tokens.push_back(str.substr(previous, current - previous));
          previous = current + 1;
          current = str.find_first_of(delims, previous);
      }
      tokens.push_back(str.substr(previous, current - previous));

      return tokens;
    }

    void validate_number_token (const std::string& token) {
      const std::regex digits_regex("[0-9]*");

      if (std::regex_match(token, digits_regex) == 0) {
        throw version_exception("Invalid version number part. This part should be a number.");
      }
    }

    void validate_release_type_token (const std::string& token) {
      const std::regex release_type_regex("nightly|alpha|beta|rc");

      if (std::regex_match(token, release_type_regex) == 0) {
        throw version_exception("Invalid release type. This part should be a string: (nightly|alpha|beta|rc).");
      }
    }

    using parser = void(version& ver, const std::string& token);
    const std::vector<std::vector<parser*>> parsers = {
      {
        [] (version& ver, const std::string& token) {
          validate_number_token(token);
          ver.major = std::stoi(token);
        },
        [] (version& ver, const std::string& token) {
          validate_number_token(token);
          ver.minor = std::stoi(token);
        },
        [] (version& ver, const std::string& token) {
          validate_number_token(token);
          ver.patch = std::stoi(token);
        }
      },
      {
        [] (version& ver, const std::string& token) {
          validate_release_type_token(token);
          ver.release = from_string(token);
        },
        [] (version& ver, const std::string& token) {
          validate_number_token(token);
          ver.release_number = std::stoi(token);
        }
      }
    };
  }

  template<typename string_type>
  version make_version(
    const string_type& str
  ) {
    version result;

    // Split version string by delimeters
    const string_type semver_delims("-+");
    const string_type version_delims(".");
    std::list<string_type> semver_tokens = internal::split(str, semver_delims);

    // Parse version by parts from string
    std::size_t part = 0;
    for (auto semver_part : semver_tokens) {
      const std::list<string_type> tokens = internal::split(semver_part, version_delims);
      std::size_t token_index = 0;
      for (auto token : tokens) {
        internal::parsers[part][token_index](result, token);
        ++token_index;
      }

      ++part;
      if (part >= internal::parsers.size()) {
        break;
      }
    }

    return result;
  }
}
