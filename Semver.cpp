#include "Semver.h"

#include <cstring>
#include <cstdio>

namespace Utils {
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
		std::sprintf(buffer, "%d.%d.%d%s", this->major, this->minor, this->patch, preReleaseBuffer);

		return buffer;
	}

	void Semver::fromString(const char* versionStr) {
		this->major = 0;
		this->minor = 0;
		this->patch = 0;
		this->preRelease = PreRelease::None;
		this->preReleaseVersion = 0;

		char preReleaseStr[6] = {0};
		std::sscanf(versionStr, "%u.%u.%u-%5[^.].%u",
			&this->major,
			&this->minor, 
			&this->patch,
			preReleaseStr,
			&this->preReleaseVersion);

		this->preReleaseVersion = (this->preReleaseVersion < 100 ? this->preReleaseVersion : 0);
		this->preRelease = this->getPreReleaseVal(preReleaseStr);
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

	bool Semver::isGreaterThen(const Semver& ver) const {
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

	bool Semver::isLesserThen(const Semver& ver) const {
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
			std::sprintf(versionBuffer, ".%d",version);
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