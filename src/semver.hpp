#pragma once

#include <stdint.h>
#include <stddef.h>
#include <cstring>

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

	// ========================================================================

	Semver::Semver(const uint32_t major, 
			const uint32_t minor, 
			const uint32_t patch, 
			const PreRelease preRelease,
			const uint8_t preReleaseVersion) 
		: major(major), minor(minor), patch(patch), 
		preRelease(preRelease), preReleaseVersion(preReleaseVersion) {

	}

	Semver::Semver(const char* versionStr) 
		: major(0), minor(1), patch(0), 
		preRelease(PreRelease::None), preReleaseVersion(0) {
		if(versionStr != nullptr) {
			this->fromString(versionStr);
		}
	}

	char* Semver::toString() const {
		static const size_t bufferSize = 21;
		static char buffer[bufferSize] = {0};
		for(size_t i = 0; i < bufferSize; ++i) {
			buffer[i] = '\0';
		}

		const char* preReleaseBuffer = this->getPreReleaseStr(this->preRelease, this->preReleaseVersion);
		std::sprintf(buffer, "%lu.%lu.%lu%s", this->major, this->minor, this->patch, preReleaseBuffer);

		return buffer;
	}

	void Semver::fromString(const char* versionStr) {
		this->major = 0;
		this->minor = 0;
		this->patch = 0;
		this->preRelease = PreRelease::None;
		this->preReleaseVersion = 0;

		char preReleaseStr[6] = {0};
		std::sscanf(versionStr, "%lu.%lu.%lu-%5[^.].%lu",
			&this->major,
			&this->minor, 
			&this->patch,
			preReleaseStr,
			&this->preReleaseVersion);

		this->preReleaseVersion = (this->preReleaseVersion < 100 ? this->preReleaseVersion : 0);
		this->preRelease = this->getPreReleaseVal(preReleaseStr);
	}

	void Semver::set(const uint32_t major, 
			const uint32_t minor, 
			const uint32_t patch, 
			const PreRelease preRelease,
			const uint8_t preReleaseVersion) {
		this->major = major;
		this->minor = minor;
		this->patch = patch;
		this->preRelease = preRelease;
		this->preReleaseVersion = preReleaseVersion;
	}

	bool Semver::isEquals(const Semver& ver) const {
		if(this->major == ver.major &&
			this->minor == ver.minor && 
			this->patch == ver.patch &&
			this->preRelease == ver.preRelease &&
			this->preReleaseVersion == ver.preReleaseVersion) {
			return true;
		}
		return false;
	}

	bool Semver::isNewerThen(const Semver& ver) const {
		if(this->major > ver.major)
			return true;

		if(this->minor > ver.minor)
			return true;

		if(this->patch > ver.patch)
			return true;

		if(this->preRelease > ver.preRelease)
			return true;

		if(this->preReleaseVersion > ver.preReleaseVersion)
			return true;

		return false;
	}

	bool Semver::isOlderThen(const Semver& ver) const {
		if(this->major < ver.major)
			return true;

		if(this->minor < ver.minor)
			return true;

		if(this->patch < ver.patch)
			return true;

		if(this->preRelease < ver.preRelease)
			return true;

		if(this->preReleaseVersion < ver.preReleaseVersion)
			return true;

		return false;
	}

	// ------------------------------------------------------------------------
	// Internal methods

	char* Semver::getPreReleaseStr(const PreRelease rel, const uint8_t version) const {
		static const size_t bufferSize = 10;
		static char buffer[bufferSize] = {0};
		char versionBuffer[3] = {0};

		if(version > 0 && version < 100) {
			std::sprintf(versionBuffer, ".%u",version);
		}

		switch(rel) {
			case PreRelease::None:
				buffer[0] = '\0';
				break;
			case PreRelease::Alpha:
				std::sprintf(buffer, "-alpha%s",versionBuffer);
				break;
			case PreRelease::Betha:
				std::sprintf(buffer, "-betha%s",versionBuffer);
				break;
			case PreRelease::ReleaseCandidate:
				std::sprintf(buffer, "-rc%s",versionBuffer);
				break;
		}
		return buffer;
	}

	Semver::PreRelease Semver::getPreReleaseVal(const char* str) {
		PreRelease result = PreRelease::None;
		if(std::strcmp(str,"alpha") == 0) {
			result = PreRelease::Alpha;
		} else if(std::strcmp(str,"betha") == 0) {
			result = PreRelease::Betha;
		} else if(std::strcmp(str,"rc") == 0) {
			result = PreRelease::ReleaseCandidate;
		}
		return result;
	}
}