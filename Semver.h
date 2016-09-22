#pragma once

#include <stdint.h>
#include <stddef.h>

namespace Utils {
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
		bool operator>(const Semver& ver) const { return this->isGreaterThen(ver); }
		bool operator<(const Semver& ver) const { return this->isLesserThen(ver); }
		bool operator==(const Semver& ver) const { return this->isEquals(ver); }

		char*	toString		() const;
		void	fromString		(const char* versionStr);
		bool	isEquals		(const Semver& ver) const;
		bool	isGreaterThen	(const Semver& ver) const;
		bool	isLesserThen	(const Semver& ver) const;
	private:
		char*		getPreReleaseStr(const PreRelease rel, const uint8_t version) const;
		PreRelease 	getPreReleaseVal(const char* str);
	};
}