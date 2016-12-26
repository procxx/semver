#pragma once

#include <stdint.h>
#include <stddef.h>
#include <cstring>

class Semver {
public:
    enum class Meta {
        None                = 0,
        Alpha               = 1,
        Betha               = 2,
        ReleaseCandidate    = 3,
    };

    uint32_t    major;
    uint32_t    minor;
    uint32_t    patch;
    Meta        preRelease;
    uint32_t    preReleaseVersion;

    Semver(const uint32_t major = 0, 
        const uint32_t minor = 1, 
        const uint32_t patch = 0, 
        const Meta preRelease = Meta::None,
        const uint8_t preReleaseVersion = 0);

    explicit Semver(const char* versionStr);

    operator const char*() const { return this->toString(); }
    bool operator>(const Semver& ver) const { return this->isNewerThen(ver); }
    bool operator<(const Semver& ver) const { return this->isOlderThen(ver); }
    bool operator==(const Semver& ver) const { return this->isEquals(ver); }

    char*   toString        () const;
    void    fromString      (const char* versionStr);
    void    set(const uint32_t major = 0, 
        const uint32_t minor = 1, 
        const uint32_t patch = 0, 
        const Meta preRelease = Meta::None,
        const uint8_t preReleaseVersion = 0);

    bool    isEquals        (const Semver& ver) const;
    bool    isNewerThen     (const Semver& ver) const;
    bool    isOlderThen     (const Semver& ver) const;
private:
    char*   getMetaStr(const Meta rel, const uint8_t version) const;
    Meta    getMetaVal(const char* str);
};

// ========================================================================

Semver::Semver(const uint32_t major, 
    const uint32_t minor, 
    const uint32_t patch, 
    const Meta preRelease,
    const uint8_t preReleaseVersion) 
: major(major), minor(minor), patch(patch), 
preRelease(preRelease), preReleaseVersion(preReleaseVersion) {

}

Semver::Semver(const char* versionStr) 
: major(0), minor(1), patch(0), 
preRelease(Meta::None), preReleaseVersion(0) {
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

    const char* preReleaseBuffer = this->getMetaStr(this->preRelease, this->preReleaseVersion);
    std::sprintf(buffer, "%lu.%lu.%lu%s", this->major, this->minor, this->patch, preReleaseBuffer);

    return buffer;
}

void Semver::fromString(const char* versionStr) {
    this->major = 0;
    this->minor = 0;
    this->patch = 0;
    this->preRelease = Meta::None;
    this->preReleaseVersion = 0;

    char preReleaseStr[6] = {0};
    std::sscanf(versionStr, "%lu.%lu.%lu-%5[^.].%lu",
        &this->major,
        &this->minor, 
        &this->patch,
        preReleaseStr,
        &this->preReleaseVersion);

    this->preReleaseVersion = (this->preReleaseVersion < 100 ? this->preReleaseVersion : 0);
    this->preRelease = this->getMetaVal(preReleaseStr);
}

void Semver::set(const uint32_t major, 
    const uint32_t minor, 
    const uint32_t patch, 
    const Meta preRelease,
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

char* Semver::getMetaStr(const Meta rel, const uint8_t version) const {
    static const size_t bufferSize = 10;
    static char buffer[bufferSize] = {0};
    char versionBuffer[3] = {0};

    if(version > 0 && version < 100) {
        std::sprintf(versionBuffer, ".%u",version);
    }

    switch(rel) {
        case Meta::None:
        buffer[0] = '\0';
        break;
        case Meta::Alpha:
        std::sprintf(buffer, "-alpha%s",versionBuffer);
        break;
        case Meta::Betha:
        std::sprintf(buffer, "-betha%s",versionBuffer);
        break;
        case Meta::ReleaseCandidate:
        std::sprintf(buffer, "-rc%s",versionBuffer);
        break;
    }
    return buffer;
}

Semver::Meta Semver::getMetaVal(const char* str) {
    Meta result = Meta::None;
    if(std::strcmp(str,"alpha") == 0) {
        result = Meta::Alpha;
    } else if(std::strcmp(str,"betha") == 0) {
        result = Meta::Betha;
    } else if(std::strcmp(str,"rc") == 0) {
        result = Meta::ReleaseCandidate;
    }
    return result;
}