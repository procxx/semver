#pragma once

#include <stdint.h>
#include <stddef.h>

namespace utils {
	class Semver {
	public:
		enum class PreRelease {
			Alpha				= 1,
			Betha				= 2,
			ReleaseCandidate	= 3,
			None				= 4,
		};

		uint32_t 	major;
		uint32_t 	minor;
		uint32_t 	patch;
		PreRelease	preRelease;
		uint32_t	preReleaseVersion;

		Semver(const uint32_t major = 0, 
			const uint32_t minor = 1, 
			const uint32_t patch = 0, 
			const PreRelease preRelease = PreRelease::None,
			const uint8_t preReleaseVersion = 0);

		explicit Semver(const char* versionStr);

		operator const char*() const { return this->toString(); }
		bool operator>(const Semver& ver) const { return this->isNewerThen(ver); }
		bool operator<(const Semver& ver) const { return this->isOlderThen(ver); }
		bool operator==(const Semver& ver) const { return this->isEquals(ver); }

		char*	toString		() const;
		void	fromString		(const char* versionStr);
		void	set(const uint32_t major = 0, 
			const uint32_t minor = 1, 
			const uint32_t patch = 0, 
			const PreRelease preRelease = PreRelease::None,
			const uint8_t preReleaseVersion = 0);

		bool	isEquals		(const Semver& ver) const;
		bool	isNewerThen		(const Semver& ver) const;
		bool	isOlderThen		(const Semver& ver) const;
	private:
		char*		getPreReleaseStr(const PreRelease rel, const uint8_t version) const;
		PreRelease 	getPreReleaseVal(const char* str);
	};
}