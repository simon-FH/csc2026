#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "TrackReconstructor.hpp"

using Catch::Approx;

TEST_CASE("TrackReconstructor returns one track when hits are present") {
    csc2026::TrackReconstructor reco(1.0);

    csc2026::Hit h{};
    h.energy = 1.0;
    reco.addHit(h);

    auto tracks = reco.reconstruct();

    REQUIRE(tracks.size() == 1);
    REQUIRE(tracks[0].hits.size() == 1);
}

TEST_CASE("TrackReconstructor best track is accessible") {
    csc2026::TrackReconstructor reco(1.0);

    csc2026::Hit h{};
    h.energy = 2.0;
    reco.addHit(h);

    reco.reconstruct();

    const csc2026::Track* best = reco.getBestTrack();
    REQUIRE(best != nullptr);
    REQUIRE(best->pt == Approx(2.0));
}
