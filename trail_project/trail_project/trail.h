#ifndef TRAIL_H
#define TRAIL_H

#include <cstring>

//Check out this link, used this for reference on what information to collect about trails.
//We also might want GPS for the trails.
//https://www.alltrails.com/explore?b_tl_lat=37.77722770873696&b_tl_lng=-122.89718627929688&b_br_lat=36.82907321372808&b_br_lng=-120.72326660156249&route[]=L

struct difficulty_t {
  enum type {
    EASY = 1,
    MODERATE = 2,
    HARD = 3
  };
};

struct activity_t {
  enum type {
    BACKPACKING = 1 << 0,
    X_COUNTRY_SKIING = 1 << 1,
    HORSE_BACK_RIDING = 1 << 2,
    OFF_ROAD_DRIVING = 1 << 3,
    ROCK_CLIMBING = 1 << 4,
    SNOW_SHOEING = 1 << 5,
    WALKING = 1 << 6,
    BIRDING = 1 << 7,
    FISHING = 1 << 8,
    MOUNTAIN_BIKING = 1 << 9,
    PADDLE_SPORTS = 1 << 10,
    SCENIC_DRIVING = 1 << 11,
    SURFING = 1 << 12,
    CAMPING = 1 << 13,
    HIKING = 1 << 14,
    NATURE_TRIPS = 1 << 15,
    ROAD_BIKING = 1 << 16,
    SKIIING = 1 << 17,
    TRAIL_RUNNING = 1 << 18
  };
};

inline activity_t::type operator|(activity_t::type a, activity_t::type b) {
  return static_cast<activity_t::type>(static_cast<int>(a) | static_cast<int>(b));
}

activity_t::type packed_string_to_activites(std::string str) {
  activity_t::type activites = static_cast<activity_t::type>(0);
  if (str.find('b') != std::string::npos)
    activites = activites | activity_t::BACKPACKING;
  if (str.find('x') != std::string::npos)
    activites = activites | activity_t::X_COUNTRY_SKIING;
  if (str.find('h') != std::string::npos)
    activites = activites | activity_t::HORSE_BACK_RIDING;
  if (str.find('o') != std::string::npos)
    activites = activites | activity_t::OFF_ROAD_DRIVING;
  if (str.find('r') != std::string::npos)
    activites = activites | activity_t::ROCK_CLIMBING;
  if (str.find('s') != std::string::npos)
    activites = activites | activity_t::SNOW_SHOEING;
  if (str.find('w') != std::string::npos)
    activites = activites | activity_t::WALKING;
  if (str.find('v') != std::string::npos)
    activites = activites | activity_t::BIRDING;
  if (str.find('f') != std::string::npos)
    activites = activites | activity_t::FISHING;
  if (str.find('m') != std::string::npos)
    activites = activites | activity_t::MOUNTAIN_BIKING;
  if (str.find('p') != std::string::npos)
    activites = activites | activity_t::PADDLE_SPORTS;
  if (str.find('d') != std::string::npos)
    activites = activites | activity_t::SCENIC_DRIVING;
  if (str.find('u') != std::string::npos)
    activites = activites | activity_t::SURFING;
  if (str.find('c') != std::string::npos)
    activites = activites | activity_t::CAMPING;
  if (str.find('g') != std::string::npos)
    activites = activites | activity_t::HIKING;
  if (str.find('n') != std::string::npos)
    activites = activites | activity_t::NATURE_TRIPS;
  if (str.find('j') != std::string::npos)
    activites = activites | activity_t::ROAD_BIKING;
  if (str.find('y') != std::string::npos)
    activites = activites | activity_t::SKIIING;
  if (str.find('t') != std::string::npos)
    activites = activites | activity_t::TRAIL_RUNNING;

  return activites;
}

std::string activites_to_full_string(activity_t::type activites) {
  std::stringstream ss;
  ss << "[ ";
  if (activites & activity_t::BACKPACKING)
    ss << "{Backpacking} ";
  if (activites & activity_t::X_COUNTRY_SKIING)
    ss << "{Cross Country Skiing} ";
  if (activites & activity_t::HORSE_BACK_RIDING)
    ss << "{Horseback Riding} ";
  if (activites & activity_t::OFF_ROAD_DRIVING)
    ss << "{Off Road Driving} ";
  if (activites & activity_t::ROCK_CLIMBING)
    ss << "{Rock Climbing} ";
  if (activites & activity_t::SNOW_SHOEING)
    ss << "{Snow Shoeing} ";
  if (activites & activity_t::WALKING)
    ss << "{Walking} ";
  if (activites & activity_t::BIRDING)
    ss << "{Birding} ";
  if (activites & activity_t::FISHING)
    ss << "{Fishing} ";
  if (activites & activity_t::MOUNTAIN_BIKING)
    ss << "{Mountain Biking} ";
  if (activites & activity_t::PADDLE_SPORTS)
    ss << "{Paddle Sports} ";
  if (activites & activity_t::SCENIC_DRIVING)
    ss << "{Scenic Driving} ";
  if (activites & activity_t::SURFING)
    ss << "{Surfing} ";
  if (activites & activity_t::CAMPING)
    ss << "{Camping} ";
  if (activites & activity_t::HIKING)
    ss << "{Hiking} ";
  if (activites & activity_t::NATURE_TRIPS)
    ss << "{Nature Trips} ";
  if (activites & activity_t::ROAD_BIKING)
    ss << "{Road Biking} ";
  if (activites & activity_t::SKIIING)
    ss << "{Skiing} ";
  if (activites & activity_t::TRAIL_RUNNING)
    ss << "{Trail Running} ";

  ss << "]";
  return ss.str();
}

struct view_t {
  enum type {
    BEACH = 1 << 0,
    CITYWALK = 1 << 1,
    HISTORIC_SITE = 1 << 2,
    LAKE = 1 << 3,
    RIVER = 1 << 4,
    WATERFALL = 1 << 5,
    WILD_LIFE = 1 << 6,
    CAVE = 1 << 7,
    FOREST = 1 << 8,
    HOT_SPRINGS = 1 << 9,
    RAILS_TRAILS = 1 << 10,
    VIEWS = 1 << 11,
    WILD_FLOWERS = 1 << 12
  };
};

inline view_t::type operator|(view_t::type a, view_t::type b) {
  return static_cast<view_t::type>(static_cast<int>(a) | static_cast<int>(b));
}

view_t::type packed_string_to_views(std::string str) {
  view_t::type views = static_cast<view_t::type>(0);

  if (str.find('b') != std::string::npos)
    views = views | view_t::BEACH;
  if (str.find('c') != std::string::npos)
    views = views | view_t::CITYWALK;
  if (str.find('h') != std::string::npos)
    views = views | view_t::HISTORIC_SITE;
  if (str.find('l') != std::string::npos)
    views = views | view_t::LAKE;
  if (str.find('r') != std::string::npos)
    views = views | view_t::RIVER;
  if (str.find('w') != std::string::npos)
    views = views | view_t::WATERFALL;
  if (str.find('y') != std::string::npos)
    views = views | view_t::WILD_LIFE;
  if (str.find('v') != std::string::npos)
    views = views | view_t::CAVE;
  if (str.find('f') != std::string::npos)
    views = views | view_t::FOREST;
  if (str.find('s') != std::string::npos)
    views = views | view_t::HOT_SPRINGS;
  if (str.find('t') != std::string::npos)
    views = views | view_t::RAILS_TRAILS;
  if (str.find('e') != std::string::npos)
    views = views | view_t::VIEWS;
  if (str.find('o') != std::string::npos)
    views = views | view_t::WILD_FLOWERS;

  return views;
}

std::string views_to_full_string(view_t::type views) {
  std::stringstream ss;
  ss << "[ ";
  if (views & view_t::BEACH)
    ss << "{Beach} ";
  if (views & view_t::CITYWALK)
    ss << "{City Walk} ";
  if (views & view_t::HISTORIC_SITE)
    ss << "{Historic Site} ";
  if (views & view_t::LAKE)
    ss << "{Lake} ";
  if (views & view_t::RIVER)
    ss << "{River} ";
  if (views & view_t::WATERFALL)
    ss << "{Waterfall} ";
  if (views & view_t::WILD_LIFE)
    ss << "{Wild Life} ";
  if (views & view_t::CAVE)
    ss << "{Cave} ";
  if (views & view_t::FOREST)
    ss << "{Forest} ";
  if (views & view_t::HOT_SPRINGS)
    ss << "{Hot Springs} ";
  if (views & view_t::RAILS_TRAILS)
    ss << "{Rails Trails} ";
  if (views & view_t::VIEWS)
    ss << "{Views} ";
  if (views & view_t::WILD_FLOWERS)
    ss << "{Wild Flowers} ";

  ss << "]";
  return ss.str();
}

struct suitability_t {
  enum type {
    DOG = 1 << 0,
    KID = 1 << 1,
    WHEELCHAIR = 1 << 2
  };
};

inline suitability_t::type operator|(suitability_t::type a, suitability_t::type b) {
  return static_cast<suitability_t::type>(static_cast<int>(a) | static_cast<int>(b));
}

suitability_t::type packed_string_to_suitability(std::string str) {
  suitability_t::type suitability = static_cast<suitability_t::type>(0);

  if (str.find('d') != std::string::npos)
    suitability = suitability | suitability_t::DOG;
  if (str.find('k') != std::string::npos)
    suitability = suitability | suitability_t::KID;
  if (str.find('w') != std::string::npos)
    suitability = suitability | suitability_t::WHEELCHAIR;

  return suitability;
}

std::string suitability_to_full_string(suitability_t::type suitability) {
  std::stringstream ss;
  ss << "[ ";
  if (suitability & suitability_t::DOG)
    ss << "{Dog} ";
  if (suitability & suitability_t::KID)
    ss << "{Kid} ";
  if (suitability & suitability_t::WHEELCHAIR)
    ss << "{Wheelchair} ";

  ss << "]";
  return ss.str();
}

struct route_type_t {
  enum type {
    OUT_AND_BACK = 1,
    LOOP = 2,
    POINT_TO_POINT = 3
  };
};

struct trail_traffic_t {
  enum type {
    LIGHT = 1,
    MODERATE = 2,
    HEAVY = 3
  };
};

struct geographic_location_t {
  double latitude;
  double longitude;
};

class trail_t {
private:
  char name[256];
  char area_name[256];
  char country_name[256];
  char city_name[256];
  char state_name[256];

  int review_count;
  difficulty_t::type difficulty;
  geographic_location_t location;
  double length_meters;
  int rating;
  activity_t::type activites;
  view_t::type views;
  suitability_t::type suitability;
  route_type_t::type route_type;
  trail_traffic_t::type trail_traffic;
  float elevation_gain;

public:
  void set_name(const char *name);
  const char *get_name(void) const;

  void set_area_name(const char *name);
  const char *get_area_name(void) const;

  void set_country_name(const char *name);
  const char *get_country_name(void) const;

  void set_city_name(const char *name);
  const char *get_city_name(void) const;

  void set_state_name(const char *name);
  const char *get_state_name(void) const;

  void set_review_count(int count);
  int get_review_count(void) const;

  void set_difficulty(difficulty_t::type difficulty);
  difficulty_t::type get_difficulty(void) const;

  void set_latitude(double latitude);
  double get_latitude(void) const;

  void set_longitude(double latitude);
  double get_longitude(void) const;

  void set_length_meters(double miles);
  double get_length_meters(void) const;

  void set_ratings(int ratings);
  int get_ratings(void) const;

  void set_activities(activity_t::type activities);
  activity_t::type get_activites(void) const;

  void set_views(view_t::type view);
  view_t::type get_views(void) const;

  void set_suitability(suitability_t::type suitability);
  suitability_t::type get_suitability(void) const;

  void set_route_type(route_type_t::type route_type);
  route_type_t::type get_route_type(void) const;

  void set_trail_traffic(trail_traffic_t::type trail_traffic);
  trail_traffic_t::type get_trail_traffic(void) const;

  void set_elevation_gain(float elevation_gain);
  float get_elevation_gain(void) const;

  std::string to_csv(void) const;
};

void trail_t::set_name(const char *name) {
  strncpy_s(this->name, name, 256);
}

const char *trail_t::get_name(void) const {
  return this->name;
}

void trail_t::set_area_name(const char *name) {
  strncpy_s(this->area_name, name, 256);
}

const char *trail_t::get_area_name(void) const {
  return this->area_name;
}

void trail_t::set_country_name(const char *name) {
  strncpy_s(this->country_name, name, 256);
}

const char *trail_t::get_country_name(void) const {
  return this->country_name;
}

void trail_t::set_city_name(const char *name) {
  strncpy_s(this->city_name, name, 256);
}

const char *trail_t::get_city_name(void) const {
  return this->city_name;
}

void trail_t::set_state_name(const char *name) {
  strncpy_s(this->state_name, name, 256);
}

const char *trail_t::get_state_name(void) const {
  return this->state_name;
}

void trail_t::set_review_count(int count) {
  this->review_count = count;
}

int trail_t::get_review_count(void) const {
  return this->review_count;
}

void trail_t::set_difficulty(difficulty_t::type difficulty) {
  this->difficulty = difficulty;
}

difficulty_t::type trail_t::get_difficulty(void) const {
  return this->difficulty;
}

void trail_t::set_latitude(double latitude) {
  this->location.latitude = latitude;
}

double trail_t::get_latitude(void) const {
  return this->location.latitude;
}

void trail_t::set_longitude(double longitude) {
  this->location.longitude = longitude;
}

double trail_t::get_longitude(void) const {
  return this->location.longitude;
}

void trail_t::set_length_meters(double meters) {
  this->length_meters = meters;
}

double trail_t::get_length_meters(void) const {
  return this->length_meters;
}

void trail_t::set_ratings(int ratings) {
  this->rating = rating;
}

int trail_t::get_ratings(void) const {
  return this->rating;
}

void trail_t::set_activities(activity_t::type activities) {
  this->activites = activites;
}

activity_t::type trail_t::get_activites(void) const {
  return this->activites;
}

void trail_t::set_suitability(suitability_t::type suitability) {
  this->suitability = suitability;
}

suitability_t::type trail_t::get_suitability(void) const {
  return this->suitability;
}

void trail_t::set_route_type(route_type_t::type route_type) {
  this->route_type = route_type;
}

route_type_t::type trail_t::get_route_type(void) const {
  return this->route_type;
}

void trail_t::set_trail_traffic(trail_traffic_t::type trail_traffic) {
  this->trail_traffic = trail_traffic;
}

trail_traffic_t::type trail_t::get_trail_traffic(void) const {
  return this->trail_traffic;
}

void trail_t::set_elevation_gain(float elevation_gain) {
  this->elevation_gain = elevation_gain;
}

float trail_t::get_elevation_gain(void) const {
  return this->elevation_gain;
}

void trail_t::set_views(view_t::type view) {
  this->views = view;
}
view_t::type trail_t::get_views(void) const {
  return this->views;
}

std::string trail_t::to_csv(void) const {
  std::stringstream ss;
  ss << this->name << ","
    << this->area_name << ","
    << this->country_name << ","
    << this->city_name << ","
    << this->state_name << ","
    << this->review_count << ","
    << static_cast<int>(this->difficulty) << ","
    << this->location.latitude << ","
    << this->location.longitude << ","
    << this->length_meters << ","
    << this->rating << ","
    << static_cast<int>(this->activites) << ","
    << static_cast<int>(this->views) << ","
    << static_cast<int>(this->suitability) << ","
    << static_cast<int>(this->route_type) << ","
    << static_cast<int>(this->trail_traffic) << ","
    << this->elevation_gain;

  return ss.str();
}

std::ostream &operator<<(std::ostream &out, trail_t const &trail) {
  return out << trail.get_name() << " [meters: " << trail.get_length_meters()  << "] " << std::endl
    << "\t" << activites_to_full_string(trail.get_activites())
    << std::endl << "\t" << views_to_full_string(trail.get_views())
    << std::endl << "\t" << suitability_to_full_string(trail.get_suitability()) ;
}

#endif