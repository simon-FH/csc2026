// CSC Latin America 2026 - Particle class implementation

#include "Particle.hpp"

#include <algorithm>   // std::max
#include <cmath>       // std::sqrt, std::hypot, std::log, std::atan2
#include <limits>      // std::numeric_limits

namespace csc2026 {

Particle::Particle(double px, double py, double pz, double mass)
    : m_px(px), m_py(py), m_pz(pz), m_mass(mass) {}

double Particle::pt() const {
    return std::hypot(m_px, m_py);
}

double Particle::p() const {
    // C++17+ provides 3-arg overload
    return std::hypot(m_px, m_py, m_pz);
}

double Particle::energy() const {
    const double mom = p();
    return std::sqrt(mom * mom + m_mass * m_mass);
}

double Particle::phi() const {
    return std::atan2(m_py, m_px);
}

double Particle::eta() const {
    const double mom = p();

    // Convention: eta(0,0,0) -> 0
    if (mom == 0.0) {
        return 0.0;
    }

    // pt -> 0 (mom -> |pz|): eta tends to +/- infinity
    const double denom = mom - m_pz;
    const double numer = mom + m_pz;
    if (denom == 0.0) {
        return (m_pz >= 0.0)
            ? std::numeric_limits<double>::infinity()
            : -std::numeric_limits<double>::infinity();
    }

    const double ratio = numer / denom;
    if (ratio <= 0.0) {
        return 0.0; // avoid NaNs from non-physical inputs
    }

    return 0.5 * std::log(ratio);
}

Particle Particle::operator+(const Particle& other) const {
    const double new_px = m_px + other.m_px;
    const double new_py = m_py + other.m_py;
    const double new_pz = m_pz + other.m_pz;

    const double e_total = energy() + other.energy();
    const double p_total_sq = new_px * new_px + new_py * new_py + new_pz * new_pz;

    // m^2 = E^2 - |p|^2, guard tiny negative due to FP rounding
    const double m2 = std::max(0.0, e_total * e_total - p_total_sq);
    const double new_mass = std::sqrt(m2);

    return Particle(new_px, new_py, new_pz, new_mass);
}

double invariantMass(const Particle& p1, const Particle& p2) {
    return (p1 + p2).mass();
}

} // namespace csc2026
