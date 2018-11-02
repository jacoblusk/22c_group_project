#ifndef TRAIL_H
#define TRAIL_H

//Check out this link, used this for reference on what information to collect about trails.
//We also might want GPS for the trails.
//https://www.alltrails.com/explore?b_tl_lat=37.77722770873696&b_tl_lng=-122.89718627929688&b_br_lat=36.82907321372808&b_br_lng=-120.72326660156249&route[]=L

enum Difficulty {
  DifficultyEasy,
  DifficultyModerate,
  DifficultyHard
};

enum Activity {
  ActivityBackpacking     = 1 << 0,
  ActivityXCountrySkiing  = 1 << 1,
  ActivityHorsebackRiding = 1 << 2,
  ActivityOffRoadDriving  = 1 << 3,
  ActivityRockClimbing    = 1 << 4,
  ActivitySnowShoeing     = 1 << 5,
  ActivityWalking         = 1 << 6,
  ActivityBirding         = 1 << 7,
  ActivityFishing         = 1 << 8,
  ActivityMountainBiking  = 1 << 9,
  ActivityPaddleSports    = 1 << 10,
  ActivityScenicDriving   = 1 << 11,
  ActivitySurfing         = 1 << 12,
  ActivityCamping         = 1 << 13,
  ActivityHiking          = 1 << 14,
  ActivityNatureTrips     = 1 << 15,
  ActivityRoadBiking      = 1 << 16,
  ActivitySkiiing         = 1 << 17,
  ActivityTrailRunning    = 1 << 18
};

inline Activity operator|(Activity a, Activity b) {
  return static_cast<Activity>(static_cast<int>(a) | static_cast<int>(b));
}

enum View {
  ViewBeach        = 1 << 0,
  ViewCityWalk     = 1 << 1,
  ViewHistoricSite = 1 << 2,
  ViewLake         = 1 << 3,
  ViewRiver        = 1 << 4,
  ViewWaterfall    = 1 << 5,
  ViewWildlife     = 1 << 6,
  ViewCave         = 1 << 7,
  ViewForest       = 1 << 8,
  ViewHotSprings   = 1 << 9,
  ViewRailsTrails  = 1 << 10,
  ViewViews        = 1 << 11,
  ViewWildflowers  = 1 << 12
};

inline View operator|(View a, View b) {
  return static_cast<View>(static_cast<int>(a) | static_cast<int>(b));
}

enum Suitability {
  SuitabilityDog        = 1 << 0,
  SuitabilityKid        = 1 << 1,
  SuitabilityWheelchair = 1 << 2
};

inline Suitability operator|(Suitability a, Suitability b) {
  return static_cast<Suitability>(static_cast<int>(a) | static_cast<int>(b));
}

enum RouteType {
  RouteTypeOutAndBack   = 1 << 0,
  RouteTypeLoop         = 1 << 1,
  RouteTypePointToPoint = 1 << 2
};

enum TrailTraffic {
  TrailTrafficLight    = 1 << 0,
  TrailTrafficModerate = 1 << 1,
  TrailTrafficHeavy    = 1 << 2
};

class Trail {
private:
  char m_szName[256];
  Difficulty m_difficulty;
  int m_lengthMiles;
  int m_rating;
  Activity m_fActivities;
  View m_fViews;
  Suitability m_fSuitability;
  RouteType m_routeType;
  TrailTraffic m_trailTraffic;
  int m_elevationGain;
};

#endif