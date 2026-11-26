#pragma once
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <cmath>
#include <limits>
#include "Vehicle.hpp"
#include "Violation.hpp"

namespace model {

struct FineRecord {
    int month            = 0;
    std::string violationId;
    double fineAmount    = 0.0;
    int pointsDeducted   = 0;
};

class Driver {
public:
    Driver(std::string id, std::string name,
           double monthlyIncome, double complianceRate,
           std::unique_ptr<Vehicle> vehicle,
           int initialRepeatCount = 0)
        : id_(std::move(id))
        , name_(std::move(name))
        , monthlyIncome_(sanitizeIncome(monthlyIncome))
        , complianceRate_(clampCompliance(complianceRate))
        , repeatCount_(initialRepeatCount > 0 ? initialRepeatCount : 0)
        , licensePoints_(12)
        , vehicle_(std::move(vehicle)) {}

    // Non-copyable
    Driver(const Driver&) = delete;
    Driver& operator=(const Driver&) = delete;
    Driver(Driver&&) = default;
    Driver& operator=(Driver&&) = default;

    // --- Getters ---
    const std::string& getId() const { return id_; }
    const std::string& getName() const { return name_; }
    double getMonthlyIncome() const { return monthlyIncome_; }
    double getComplianceRate() const { return complianceRate_; }
    int getRepeatCount() const { return repeatCount_; }
    int getLicensePoints() const { return licensePoints_; }
    const Vehicle* getVehicle() const { return vehicle_.get(); }
    const std::vector<FineRecord>& getHistory() const { return history_; }

    // --- Setters / mutators ---
    void setComplianceRate(double rate) {
        complianceRate_ = clampCompliance(rate);
    }

    void addFineRecord(FineRecord record) {
        if (record.pointsDeducted < 0)
            record.pointsDeducted = 0;
        if (!std::isfinite(record.fineAmount) || record.fineAmount < 0.0)
            record.fineAmount = 0.0;
        // Cập nhật trạng thái sau khi bản ghi đã được chuẩn hóa
        history_.push_back(std::move(record));
        licensePoints_ -= history_.back().pointsDeducted;
        if (licensePoints_ < 0) licensePoints_ = 0;
        if (repeatCount_ < std::numeric_limits<int>::max()) {
            ++repeatCount_;
        }
    }

    // Tổng tiền phạt trong một tháng cụ thể (dùng cho vòng lặp phản hồi hành vi)
    double totalFinesForMonth(int month) const {
        double total = 0.0;
        for (const auto& r : history_)
            if (r.month == month) total += r.fineAmount;
        return total;
    }

private:
    // Giới hạn tỷ lệ tuân thủ trong khoảng [0.05, 0.99]
    static double clampCompliance(double rate) {
        if (std::isnan(rate)) return 0.05;
        return std::clamp(rate, 0.05, 0.99);
    }

    // Đảm bảo thu nhập luôn dương để tránh chia cho 0 ở các công thức định giá
    static double sanitizeIncome(double income) {
        if (!std::isfinite(income) || income < 1'000'000.0) return 1'000'000.0;
        return income;
    }

    std::string id_;
    std::string name_;
    double monthlyIncome_;
    double complianceRate_;
    int repeatCount_;
    int licensePoints_;
    std::unique_ptr<Vehicle> vehicle_;
    std::vector<FineRecord> history_;
};

} // namespace model
