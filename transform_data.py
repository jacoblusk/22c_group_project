from typing import *
from enum import Enum, IntFlag, unique
import struct
import json
import os
import errno

@unique
class Activity(IntFlag):
    Backpacking    =  1 << 0
    XCountrySkiing =  1 << 1
    HorsebackRiding = 1 << 2
    OffRoadDriving  = 1 << 3
    RockClimbing    = 1 << 4
    SnowShoeing     = 1 << 5
    Walking         = 1 << 6
    Birding         = 1 << 7
    Fishing         = 1 << 8
    MountainBiking  = 1 << 9
    PaddleSports    = 1 << 10
    ScenicDriving   = 1 << 11
    Surfing         = 1 << 12
    Camping         = 1 << 13
    Hiking          = 1 << 14
    NatureTrips     = 1 << 15
    RoadBiking      = 1 << 16
    Skiiing         = 1 << 17
    TrailRunning    = 1 << 18

@unique
class View(IntFlag):
  Beach        = 1 << 0
  CityWalk     = 1 << 1
  HistoricSite = 1 << 2
  Lake         = 1 << 3
  River        = 1 << 4
  Waterfall    = 1 << 5
  Wildlife     = 1 << 6
  Cave         = 1 << 7
  Forest       = 1 << 8
  HotSprings   = 1 << 9
  RailsTrails  = 1 << 10
  Views        = 1 << 11
  Wildflowers  = 1 << 12

@unique
class Suitability(IntFlag):
  Dog        = 1 << 0
  Kid        = 1 << 1
  Wheelchair = 1 << 2

@unique
class RouteType(Enum):
  OutAndBack   = 1,
  Loop         = 2,
  PointToPoint = 3

@unique
class TrailTraffic(Enum):
  Light    = 1,
  Moderate = 2,
  Heavy    = 3

@unique
class Difficulty(Enum):
  Easy     = 1
  Moderate = 2
  Hard     = 3


class GeographicLocation(object):
    def __init__(self, latitude: float, longitude: float):
        if latitude is None or longitude is None:
            raise ValueError("Latitude or Longitude was None.")
        if type(latitude) is not float or type(longitude) is not float:
            raise ValueError("Latitude or Longitude aren't floats.")
        self.latitude:  float = latitude
        self.longitude: float = longitude

class Trail(object):
    def __init__(self):
        self.name: str = None
        self.area_name: str = None
        self.country_name: str = None
        self.city_name: str = None
        self.state_name: str = None
        self.review_count: int = 0
        self.difficulty: Difficulty = 0
        self.geographic_location: GeographicLocation = None
        self.length: float = 0.0
        self.rating: float = 0
        self.activities: Activity = 0
        self.views: View = 0
        self.suitability: Suitability = 0
        self.routetype: RouteType = 0
        self.trail_traffic: int = 0
        self.elevation_gain: float = 0.0
    
    @staticmethod
    def from_json(json: Dict[str, Any]):
        trail = Trail()
        if type(json['name']) is not str:
            raise ValueError("name isn't a string.")
        trail.name = json['name']

        if type(json['length']) is not float:
            raise ValueError("length isn't a float.")
        trail.length = json['length']

        if type(json['difficulty_rating']) is not str:
            raise ValueError("difficulty_rating isn't a string.")
        difficulty = int(json['difficulty_rating'])
        if difficulty >= 0 and difficulty < 3:
            trail.difficulty = Difficulty.Easy
        elif difficulty >= 3 and difficulty < 5:
            trail.difficulty = Difficulty.Moderate
        elif difficulty >= 5 and difficulty <= 7:
            trail.difficulty = Difficulty.Hard
        else:
            raise ValueError("unknown difficulty value.")

        if type(json['route_type']) is not str:
            raise ValueError("length isn't a float.")

        if json['route_type'] == 'L':
            trail.route_type = RouteType.Loop
        elif json['route_type'] == 'O':
            trail.route_type = RouteType.OutAndBack
        elif json['route_type'] == 'P':
            trail.route_type = RouteType.PointToPoint
        else:
            raise ValueError("unknown route_type value.")
        
        if type(json['area_name']) is not str:
            raise ValueError("area_name isn't a string.")
        trail.area_name = json['area_name']

        if type(json['country_name']) is not str:
            raise ValueError("country_name isn't a string.")
        trail.country_name = json['country_name']

        if type(json['city_name']) is not str:
            raise ValueError("city_name isn't a string.")
        trail.country_name = json['city_name']

        if type(json['num_reviews']) is not int:
            raise ValueError("num_reviews isn't an integer.")
        trail.review_count = json['num_reviews']

        if type(json['avg_rating']) is not float and type(json['avg_rating']) is not int:
            raise ValueError("avg_rating isn't an integer or float.")
        trail.rating = float(json['avg_rating'])

        if type(json['elevation_gain']) is not float and type(json['elevation_gain']) is not int:
            print('elevation_gain is type %s' % type(json['elevation_gain']))
            raise ValueError("elevation_gain isn't a float.")
        trail.elevation_gain = json['elevation_gain']

        if "kids" in json['features']:
            trail.suitability = trail.suitability | Suitability.Kid
        
        if "dogs" in json['features'] or "dogs-leash" in json['features']:
            trail.suitability = trail.suitability | Suitability.Kid

        if "partially-paved" in json['features'] or "paved" in json['features']:
            trail.suitability = trail.suitability | Suitability.Kid

        if "lake" in json['features']:
            trail.views = trail.views | View.Lake
        
        if "wildlife" in json['features']:
            trail.views = trail.views | View.Wildlife

        if "wild-flowers" in json['features']:
            trail.views = trail.views | View.Wildflowers

        if "views" in json['features']:
            trail.views = trail.views | View.Views

        if "beach" in json['features']:
            trail.views = trail.views | View.Beach

        if "forest" in json['features']:
            trail.views = trail.views | View.Forest

        if "cave" in json['features']:
            trail.views = trail.views | View.Cave

        if "city-walk" in json['features']:
            trail.views = trail.views | View.CityWalk

        if "historic-site" in json['features']:
            trail.views = trail.views | View.HistoricSite

        if "hot-springs" in json['features']:
            trail.views = trail.views | View.HotSprings

        if "rails-trails" in json['features']:
            trail.views = trail.views | View.CityWalk

        if "river" in json['features']:
            trail.views = trail.views | View.River

        if "waterfall" in json['features']:
            trail.views = trail.views | View.Waterfall
        
        if "birding" in json['activities']:
            trail.activities = trail.activities | Activity.Birding

        if "fishing" in json['activities']:
            trail.activities = trail.activities | Activity.Fishing

        if "nature-trips" in json['activities']:
            trail.activities = trail.activities | Activity.NatureTrips

        if "paddle-sports" in json['activities'] or "sea-kayaking" in json['activities']:
            trail.activities = trail.activities | Activity.PaddleSports

        if "road-biking" in json['activities']:
            trail.activities = trail.activities | Activity.RoadBiking

        if "scenic-driving" in json['activities']:
            trail.activities = trail.activities | Activity.ScenicDriving

        if "surfing" in json['activities']:
            trail.activities = trail.activities | Activity.Surfing

        if "trail-running" in json['activities']:
            trail.activities = trail.activities | Activity.TrailRunning

        if "walking" in json['activities']:
            trail.activities = trail.activities | Activity.Walking

        if "rock-climbing" in json['activities']:
            trail.activities = trail.activities | Activity.RockClimbing

        if "mountain-biking" in json['activities']:
            trail.activities = trail.activities | Activity.MountainBiking

        if "backpacking" in json['activities']:
            trail.activities = trail.activities | Activity.Backpacking

        if "camping" in json['activities']:
            trail.activities = trail.activities | Activity.Camping

        if "horseback-riding" in json['activities']:
            trail.activities = trail.activities | Activity.HorsebackRiding

        if "off-road-driving" in json['activities']:
            trail.activities = trail.activities | Activity.OffRoadDriving

        if "skiing" in json['activities']:
            trail.activities = trail.activities | Activity.Skiiing

        if "x-country-skiing" in json['activities']:
            trail.activities = trail.activities | Activity.XCountrySkiing

        if "fishing" in json['activities'] or "fly-fishing" in json['activities'] :
            trail.activities = trail.activities | Activity.Fishing

        if "snow-shoeing" in json['activities']:
            trail.activities = trail.activities | Activity.SnowShoeing

        if type(json['popularity']) is not float:
            raise ValueError("popularity isn't a float.")
        popularity = json['popularity']

        if popularity >= 0 and popularity < 25:
            trail.trail_traffic = TrailTraffic.Light
        if popularity >= 25 and popularity < 50:
            trail.trail_traffic = TrailTraffic.Moderate
        if popularity >= 50:
            trail.trail_traffic = TrailTraffic.Heavy

        
        trail.geographic_location = GeographicLocation(json['_geoloc']['lat'], \
                                                       json['_geoloc']['lng'])
        return trail

def make_sure_path_exists(path):
    try:
        os.makedirs(path)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise

if __name__ == "__main__":

    with open('trail_data.json', 'r') as trail_data_file:
        trails_data = json.load(trail_data_file)
        trails = []
        for trail_data in trails_data['hits']:
            try:
                trail = Trail.from_json(trail_data)
                trails.append(trail)
            except Exception as e:
                print(e)

        make_sure_path_exists("trail_data")

        for trail in trails:
            #need to make sure trail.name is sanatized
            make_sure_path_exists("trail_data/%s" % trail.name)
            with open("trail_data/%s/data" % trail.name, 'w') as output:
                

