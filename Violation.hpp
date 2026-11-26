#pragma once
#include <string>
#include <utility>
#include <cmath>

namespace model {

enum class ViolationGroup {
    SPEEDING,
    ALCOHOL_REDLIGHT,
    ADMINISTRATIVE
};

inline std::string violationGroupToString(ViolationGroup g) {
    switch (g) {
        case ViolationGroup::SPEEDING:          return "SPEEDING";
        case ViolationGroup::ALCOHOL_REDLIGHT:  return "ALCOHOL_REDLIGHT";
        case ViolationGroup::ADMINISTRATIVE:    return "ADMINISTRATIVE";
    }
    return "UNKNOWN";
}

inline ViolationGroup violationGroupFromString(const std::string& s) {
    if (s == "SPEEDING")         return ViolationGroup::SPEEDING;
    if (s == "ALCOHOL_REDLIGHT") return ViolationGroup::ALCOHOL_REDLIGHT;
    return ViolationGroup::ADMINISTRATIVE;
}

struct Violation {
    std::string id;
    std::string name;
    ViolationGroup group      = ViolationGroup::ADMINISTRATIVE;
    double baseFine           = 0.0;
    int penaltyPoints         = 0;

    Violation() = default;
    Violation(std::string id_, std::string name_,
              ViolationGroup group_, double baseFine_, int penaltyPoints_)
        : id(std::move(id_))
        , name(std::move(name_))
        , group(group_)
        , baseFine(sanitizeFine(baseFine_))
        , penaltyPoints(penaltyPoints_ > 0 ? penaltyPoints_ : 0) {}

private:
    // Chỉ chấp nhận giá trị hữu hạn và không âm
    static double sanitizeFine(double v) {
        if (!std::isfinite(v) || v < 0.0) return 0.0;
        return v;
    }
};

} // namespace model
