#include <cstdint>
#include <string>
#include <sstream>
#include <list>
#include <regex>


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

    int32_t             major;
    int32_t             minor;
    int32_t             patch;
    release_type        release;
    int32_t             release_number;

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
    const int32_t major = 0,
    const int32_t minor = 1,
    const int32_t patch = 0,
    const version::release_type release = base_version::release_type::release,
    const int32_t release_number = 0
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
    const int32_t major,
    const int32_t minor,
    const int32_t patch,
    const base_version::release_type release,
    const int32_t release_number
  ) {
    version result;

    result.major = major;
    result.minor = minor;
    result.patch = patch;
    result.release = release;
    result.release_number = release_number;

    return result;
  }

  template<typename string_type>
  version make_version(
    const string_type& str
  ) {
    version result;

    // Split version string by delimeters
    const std::string delims(".-+");
    std::list<string_type> tokens;
    std::size_t current = str.find_first_of(delims);
    std::size_t previous = 0;

    while (current != std::string::npos) {
        tokens.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find_first_of(delims, previous);
    }
    tokens.push_back(str.substr(previous, current - previous));

    // Parse tokens from string
    const std::regex digits_regex("[0-9]*");
    const std::regex release_type_regex("[0-9A-Za-z]*");
    std::size_t index = 0;
    for (auto token : tokens) {
      switch (index) {
        case 0:
          if (std::regex_match(token, digits_regex) == 0) {
            throw version_exception("Invalid major part. This part shuold be a number.");
          }
          result.major = std::stoi(token);
          break;

        case 1:
          if (std::regex_match(token, digits_regex) == 0) {
            throw version_exception("Invalid minor part. This part shuold be a number.");
          }
          result.minor = std::stoi(token);
          break;

        case 2:
          if (std::regex_match(token, digits_regex) == 0) {
            throw version_exception("Invalid patch part. This part shuold be a number.");
          }
          result.patch = std::stoi(token);
          break;

        case 3:
          if (std::regex_match(token, release_type_regex) == 0) {
            throw version_exception("Invalid release type. This part shuold be a string: (nightly|alpha|beta|rc).");
          }
          result.release = from_string(token);
          break;

        case 4:
          if (std::regex_match(token, digits_regex) == 0) {
            throw version_exception("Invalid release number part. This part shuold be a number.");
          }
          result.release_number = std::stoi(token);
          break;

        default:
          break;
      }
      ++index;
    }

    return result;
  }
}
