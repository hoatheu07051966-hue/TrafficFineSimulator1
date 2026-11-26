#pragma once
#include <string>
#include <map>
#include "Violation.hpp"

namespace model {

struct ScenarioConfig {
    std::string name;
    int months;                 // số tháng mô phỏng
    double trafficDensity;      // 0.7 vắng, 1.0 bình thường, 1.6 cao điểm
    double baseComplianceModifier;  // cộng thêm vào complianceRate nền

    // Nhân chính sách phạt theo nhóm hành vi
    std::map<ViolationGroup, double> policyMultipliers;

    // Tên chiến lược định giá: "Standard", "RiskBased", "Personalized"
    std::string pricingStrategy;

    ScenarioConfig()
        : name("Unnamed")
        , months(12)
        , trafficDensity(1.0)
        , baseComplianceModifier(0.0)
        , pricingStrategy("Standard") {
        policyMultipliers[ViolationGroup::SPEEDING]         = 1.0;
        policyMultipliers[ViolationGroup::ALCOHOL_REDLIGHT] = 1.0;
        policyMultipliers[ViolationGroup::ADMINISTRATIVE]   = 1.0;
    }
};

} // namespace model
