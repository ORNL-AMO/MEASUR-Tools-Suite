#include "util/pchip.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <stdexcept>

namespace {

bool sameSign(double first, double second) {
    return first != 0 && second != 0 && std::signbit(first) == std::signbit(second);
}

double endpointTangent(double first_width, double second_width, double first_slope, double second_slope) {
    // Normalize widths to avoid overflowing the three-point endpoint estimate.
    const double scale = std::max(first_width, second_width);
    const double first = first_width / scale;
    const double fraction = first / (first + second_width / scale);
    const double tangent = (1 + fraction) * first_slope - fraction * second_slope;
    if (!sameSign(tangent, first_slope)) {
        return 0;
    }
    if (!sameSign(first_slope, second_slope) && std::abs(tangent) > 3 * std::abs(first_slope)) {
        return 3 * first_slope;
    }
    return tangent;
}

} // namespace

namespace pchip {

Interpolator::Interpolator(std::span<const double> x, std::span<const double> y)
    : x_(x.begin(), x.end()), y_(y.begin(), y.end()), tangents_(x.size()) {
    if (x.size() != y.size() || x.size() < 2) {
        throw std::invalid_argument("PCHIP requires matching arrays with at least two points");
    }
    std::vector<double> widths(x.size() - 1);
    std::vector<double> slopes(x.size() - 1);
    for (std::size_t i = 0; i < x.size(); ++i) {
        if (!std::isfinite(x[i]) || !std::isfinite(y[i]) || (i > 0 && x[i] <= x[i - 1])) {
            throw std::invalid_argument("PCHIP requires finite points with strictly increasing x");
        }
        if (i > 0) {
            widths[i - 1] = x[i] - x[i - 1];
            slopes[i - 1] = (y[i] - y[i - 1]) / widths[i - 1];
            if (!std::isfinite(widths[i - 1]) || !std::isfinite(slopes[i - 1])) {
                throw std::invalid_argument("PCHIP interval width or slope is not finite");
            }
        }
    }
    if (x.size() == 2) {
        tangents_[0] = tangents_[1] = slopes[0];
        return;
    }
    for (std::size_t i = 1; i + 1 < x.size(); ++i) {
        if (sameSign(slopes[i - 1], slopes[i])) {
            const double scale = std::max(widths[i - 1], widths[i]);
            const double previous = widths[i - 1] / scale;
            const double next = widths[i] / scale;
            const double first_weight = 2 * next + previous;
            const double second_weight = next + 2 * previous;
            const double slope_scale = std::min(std::abs(slopes[i - 1]), std::abs(slopes[i]));
            tangents_[i] = slope_scale * ((first_weight + second_weight) /
                           (first_weight * (slope_scale / slopes[i - 1]) +
                            second_weight * (slope_scale / slopes[i])));
        }
    }
    tangents_.front() = endpointTangent(widths[0], widths[1], slopes[0], slopes[1]);
    const std::size_t last = widths.size() - 1;
    tangents_.back() = endpointTangent(widths[last], widths[last - 1], slopes[last], slopes[last - 1]);
    for (double tangent : tangents_) {
        if (!std::isfinite(tangent)) {
            throw std::invalid_argument("PCHIP tangent is not finite");
        }
    }
}

double Interpolator::evaluate(double x) const {
    if (!std::isfinite(x) || x < minimum() || x > maximum()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    const auto upper = std::lower_bound(x_.begin(), x_.end(), x);
    const std::size_t index = static_cast<std::size_t>(upper - x_.begin());
    if (*upper == x) {
        return y_[index];
    }
    const std::size_t lower = index - 1;
    const double width = x_[index] - x_[lower];
    const double t = (x - x_[lower]) / width;
    const double t2 = t * t;
    const double t3 = t2 * t;
    return (2 * t3 - 3 * t2 + 1) * y_[lower] + (t3 - 2 * t2 + t) * width * tangents_[lower] +
           (-2 * t3 + 3 * t2) * y_[index] + (t3 - t2) * width * tangents_[index];
}

double Interpolator::minimum() const { return x_.front(); }
double Interpolator::maximum() const { return x_.back(); }

} // namespace pchip
