#include <iostream>
#include <limits>

#include "csv_reader.h"
#include "hash_map.h"
#include "binary_search_tree.h"
#include "trail.h"
#include "menu.h"

#define SAVE_FILE "trail_data.csv"

//our user_data object to pass to our handler
struct containers_t {
  containers::hash_map_t<const char *, trail_t *> *map;
  containers::binary_search_tree_t<trail_t *> *bst;
};

void handle_csv_row(containers::linked_list_t<std::string> *tokens, containers_t user_data) {
  trail_t *new_trail = new trail_t;
  std::string value;

  tokens->pop(&value);
  new_trail->set_name(value.c_str());
  tokens->pop(&value);
  new_trail->set_area_name(value.c_str());
  tokens->pop(&value);
  new_trail->set_country_name(value.c_str());
  tokens->pop(&value);
  new_trail->set_city_name(value.c_str());
  tokens->pop(&value);
  new_trail->set_state_name(value.c_str());

  tokens->pop(&value);
  int review_count = std::stoi(value.c_str());
  new_trail->set_review_count(review_count);

  tokens->pop(&value);
  int difficulty_num = std::stoi(value.c_str());
  difficulty_t::type difficulty = static_cast<difficulty_t::type>(difficulty_num);
  new_trail->set_difficulty(difficulty);

  tokens->pop(&value);
  float latitude = std::stof(value.c_str());
  new_trail->set_latitude(latitude);

  tokens->pop(&value);
  float longitude = std::stof(value.c_str());
  new_trail->set_longitude(longitude);

  tokens->pop(&value);
  double length_meters = std::stod(value.c_str());
  new_trail->set_length_meters(length_meters);

  tokens->pop(&value);
  int ratings = std::stoi(value.c_str());
  new_trail->set_ratings(ratings);

  tokens->pop(&value);
  int activities_num = std::stoi(value.c_str());
  new_trail->set_activities(static_cast<activity_t::type>(activities_num));

  tokens->pop(&value);
  int views_num = std::stoi(value.c_str());
  new_trail->set_views(static_cast<view_t::type>(views_num));

  tokens->pop(&value);
  int suitability_num = std::stoi(value.c_str());
  new_trail->set_suitability(static_cast<suitability_t::type>(suitability_num));

  tokens->pop(&value);
  int route_type_num = std::stoi(value.c_str());
  new_trail->set_route_type(static_cast<route_type_t::type>(route_type_num));

  tokens->pop(&value);
  int trail_traffic_num = std::stoi(value.c_str());
  new_trail->set_trail_traffic(static_cast<trail_traffic_t::type>(trail_traffic_num));

  tokens->pop(&value);
  float elevation_gain = std::stof(value.c_str());
  new_trail->set_elevation_gain(elevation_gain);

  user_data.bst->insert(new_trail);
  user_data.map->put(new_trail->get_name(), new_trail);
}

bool trail_length_comparator(trail_t *a, trail_t* b) {
  return a->get_length_meters() > b->get_length_meters();
}

struct menu_option_t {
  enum type {
    ADD_DATA = 1,
    DELETE_DATA = 2,
    FIND_DATA = 3,
    LIST_DATA = 4,
    LIST_DATA_SORTED = 5,
    PRINT_TREE = 6,
    EFFICIENCY = 7,
    CHOICE = 8,
    QUIT = 9
  };
};

void print_menu(void) {
  std::cout << "Welcome to the Trails, choose an option from the menu: \n"
    << "(1) Add new data" << std::endl
    << "(2) Delete data" << std::endl
    << "(3) Find and display one data record using the primary key" << std::endl
    << "(4) List data in hash table sequence" << std::endl
    << "(5) List data in key sequence (sorted)" << std::endl
    << "(6) Print indented tree " << std::endl
    << "(7) Efficiency" << std::endl
    << "(8) Trail Questionaire" << std::endl
    << "(9) Quit" << std::endl;
}

size_t hash_fn(trail_t *trail, size_t capacity) {
  const char* keychars = trail->get_name();
  size_t hashedkey = 0;
  for (int i = 0; i < (sizeof(keychars) / sizeof(keychars[0])); i++) {
    hashedkey += keychars[i];
  }
  hashedkey %= capacity;
  return hashedkey;
}

menu_option_t::type read_user_menu_option(void) {
  while (true) {
    print_menu();
    int option_number;
    std::cout << "Enter the option number: ";
    if (std::cin >> option_number) {
      try {
        if (option_number < 1 || option_number > 9) {
          throw 0;
        }
        else {
          return static_cast<menu_option_t::type>(option_number);
        }
      }
      catch (...) {
        std::cerr << "Error, your option number was invalid." << std::endl << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    else {
      std::cerr << "There was an error reading the menu option please try again." << std::endl << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

trail_t *menu_option_add_trail(void) {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  trail_t *new_trail = new trail_t;
  std::string string_value;

  std::cout << "Name? ";
  if (getline(std::cin, string_value))
    new_trail->set_name(string_value.c_str());
  else
    goto fail;

  std::cout << "Area Name? ";
  if (getline(std::cin, string_value))
    new_trail->set_area_name(string_value.c_str());
  else
    goto fail;

  std::cout << "Country Name? ";
  if (getline(std::cin, string_value))
    new_trail->set_country_name(string_value.c_str());
  else
    goto fail;

  std::cout << "State Name? ";
  if (getline(std::cin, string_value))
    new_trail->set_state_name(string_value.c_str());
  else
    goto fail;

  std::cout << "City Name? ";
  if (getline(std::cin, string_value))
    new_trail->set_city_name(string_value.c_str());
  else
    goto fail;

  int review_count;
  std::cout << "Review Count? ";
  if (std::cin >> review_count)
    new_trail->set_review_count(review_count);
  else
    goto fail;

  int difficulty_num;
  std::cout << "Difficulty (1-3)? ";
  if (std::cin >> difficulty_num) {
    if (difficulty_num < 1 || difficulty_num > 3) {
      goto fail;
    }
    new_trail->set_difficulty(static_cast<difficulty_t::type>(difficulty_num));
  } else
    goto fail;

  double latitude;
  std::cout << "Latitude? ";
  if (std::cin >> latitude)
    new_trail->set_latitude(latitude);
  else
    goto fail;

  double longitude;
  std::cout << "Longitude? ";
  if (std::cin >> longitude)
    new_trail->set_longitude(longitude);
  else
    goto fail;

  double length_meters;
  std::cout << "Length Meters? ";
  if (std::cin >> length_meters)
    new_trail->set_length_meters(length_meters);
  else
    goto fail;

  int ratings;
  std::cout << "Ratings? ";
  if (std::cin >> ratings)
    new_trail->set_ratings(ratings);
  else
    goto fail;

  std::cout << "Activities (represented by a packed string with no spaces with letters)" << std::endl
    << "b for Backpacking" << std::endl
    << "x for Cross Country Skiing" << std::endl
    << "h for Horseback Riding" << std::endl
    << "o for Off Road Driving" << std::endl
    << "r for Rock Climbing" << std::endl
    << "s for Snow Shoeing" << std::endl
    << "w for Walking" << std::endl
    << "v for Birding" << std::endl
    << "f for Fishing" << std::endl
    << "m for Mountain Biking" << std::endl
    << "p for Paddle Sports" << std::endl
    << "d for Scenic Driving" << std::endl
    << "u for Surfing" << std::endl
    << "c for Camping" << std::endl
    << "g for Hiking" << std::endl
    << "n for Nature Trips" << std::endl
    << "j for Road Biking" << std::endl
    << "y for Skiing" << std::endl
    << "t for Trail Running" << std::endl;

  std::cout << "Enter your packed activity string: ";
  if (std::cin >> string_value) {
    activity_t::type activites = packed_string_to_activites(string_value);
    new_trail->set_activities(activites);
    std::cout << activites_to_full_string(activites) << std::endl << std::endl;
  }
  else
    goto fail;


  std::cout << "Views (represented by a packed string with no spaces with letters)" << std::endl
    << "b for Beach" << std::endl
    << "c for City Walk" << std::endl
    << "h for Historic Site" << std::endl
    << "l for Lake" << std::endl
    << "r for River" << std::endl
    << "w for Waterfall" << std::endl
    << "y for Wild Life" << std::endl
    << "v for Cave" << std::endl
    << "f for Forest" << std::endl
    << "s for Hot Springs" << std::endl
    << "t for Rails Trails" << std::endl
    << "e for Views" << std::endl
    << "o for Wild Flowers" << std::endl;

  std::cout << "Enter your packed views string: ";
  if (std::cin >> string_value) {
    view_t::type views = packed_string_to_views(string_value);
    new_trail->set_views(views);
    std::cout << views_to_full_string(views) << std::endl << std::endl;
  }
  else
    goto fail;

  std::cout << "Suitability (represented by a packed string with no spaces with letters)" << std::endl
    << "d for Dog" << std::endl
    << "k for Kid" << std::endl
    << "w for Wheelchair" << std::endl;

  std::cout << "Enter your packed suitability string: ";
  if (std::cin >> string_value) {
    suitability_t::type suitability = packed_string_to_suitability(string_value);
    new_trail->set_suitability(suitability);
    std::cout << suitability_to_full_string(suitability) << std::endl << std::endl;
  }
  else
    goto fail;

  int route_type_num;
  std::cout << "Route Type (1=Out And Back, 2=Loop, 3=Point To Point)? ";
  if (std::cin >> route_type_num) {
    if (route_type_num < 1 || route_type_num > 3) {
      goto fail;
    }
    new_trail->set_route_type(static_cast<route_type_t::type>(route_type_num));
  }
  else
    goto fail;

  int trail_traffic_num;
  std::cout << "Trail Traffic (1=Light, 2=Moderate, 3=Heavey)? ";
  if (std::cin >> trail_traffic_num) {
    if (trail_traffic_num < 1 || trail_traffic_num > 3) {
      goto fail;
    }
    new_trail->set_trail_traffic(static_cast<trail_traffic_t::type>(trail_traffic_num));
  }
  else
    goto fail;

  float elevation_gain;
  std::cout << "Elevation Gain? ";
  if (std::cin >> elevation_gain)
    new_trail->set_elevation_gain(elevation_gain);
  else
    goto fail;

  return new_trail;
fail:
  std::cerr << "You entered bad data, please try again." << std::endl;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  delete new_trail;
  return nullptr;
}

void print_inorder_fn(trail_t *a, void *user_data) {
  std::cout << *a << std::endl;
}

bool compare_string(const char *a, const char *b) {
  return strcmp(a, b) == 0;
}

bool compare_int(int a, int b) {
  return a == b;
}

size_t hash_string(const char *s, size_t tableSize) {
  size_t h = 5381;
  while (char c = *s++) {
    h = ((h << 5) + h) + c;
    h = h % tableSize;
  }
  return h;
}

struct tree_user_data_t {
  containers::binary_search_tree_t<trail_t *> *tree;
  int count;
};

void trim_tree(trail_t *data, tree_user_data_t *ud) {
  if (ud->count % 150 == 0) {
    ud->tree->insert(data);
  }
  ud->count++;
}

bool ask_yes_no_question(const char *s) {
  while (true) {
    std::cout << s << " (y/n): ";
    char response;
    if (std::cin >> response) {
      if (response == 'y') {
        return true;
      }
      else if (response == 'n') {
        return false;
      }
      else {
        std::cerr << "Recieved bad input, try again!" << std::endl;
      }
    }
    else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

int main(int argc, char **argv) {
  containers::hash_map_t<const char *, trail_t *> trail_map(hash_string, compare_string, 1000);
  containers::binary_search_tree_t<trail_t *> trail_tree(trail_length_comparator);

  bool running = true;
  containers_t user_data;
  user_data.map = &trail_map;
  user_data.bst = &trail_tree;

  storage::csv_reader_t<containers_t> csv_reader(SAVE_FILE);
  csv_reader.process(handle_csv_row, user_data);

  while (running) {
    menu_option_t::type menu_option = read_user_menu_option();
    switch (menu_option) {
    case menu_option_t::ADD_DATA: {
      trail_t *new_trail = menu_option_add_trail();
      if (new_trail) {
        trail_tree.insert(new_trail);
        if (trail_map.put(new_trail->get_name(), new_trail)) {
          std::cout << "Successfully added a \"" << new_trail->get_name() << "\"." << std::endl << std::endl;
          storage::csv_writer_t<const char *, trail_t *>::write_to_file(SAVE_FILE, &trail_map);
        }
        else {
          std::cerr << "Failed to add new item because of conflicting key." << std::endl << std::endl;
        }
      }
    } break;
    case menu_option_t::DELETE_DATA: {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::string primary_key;
      std::cout << "Enter the name to delete: ";
      if (std::getline(std::cin, primary_key)) {
        trail_t *trail;
        if (trail_map.find(primary_key.c_str(), &trail)) {
          if (trail_map.remove(primary_key.c_str())) {
            std::cout << "\"" << primary_key << "\"" << " has been deleted." << std::endl << std::endl;
            storage::csv_writer_t<const char *, trail_t *>::write_to_file(SAVE_FILE, &trail_map);
          }
        }
      }
      else {
        std::cerr << "Sorry, you provided a invalid name." << std::endl << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    } break;
    case menu_option_t::FIND_DATA: {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::string primary_key;
      std::cout << "Enter the name to search for: ";
      if (std::getline(std::cin, primary_key)) {
        trail_t *trail;
        if (trail_map.find(primary_key.c_str(), &trail)) {
          std::cout << "Found item: " << *trail << std::endl << std::endl;
        }
        else {
          std::cout << "Unable to find item by primary key: " << primary_key << std::endl << std::endl;
        }
      }
      else {
        std::cerr << "Sorry, you provided a invalid name." << std::endl << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    } break;
    case menu_option_t::PRINT_TREE: {
      containers::binary_search_tree_t<trail_t *> trail_tree_trim(trail_length_comparator);
      tree_user_data_t tree_user_data;
      tree_user_data.tree = &trail_tree_trim;
      tree_user_data.count = 0;

      trail_tree.preorder<tree_user_data_t *>(trim_tree, &tree_user_data);
      trail_tree_trim.verticalPrint(std::cout);
      break;
    }
    case menu_option_t::LIST_DATA: {
      trail_map.print();
      std::cout << std::endl;
    } break;
    case menu_option_t::LIST_DATA_SORTED: {
      trail_tree.inorder<void *>(print_inorder_fn, NULL);
      std::cout << std::endl;
    } break;
    case menu_option_t::EFFICIENCY: {
      std::cout << "== Hash Map ==" << std::endl;
      std::cout << "Load Factor: " << trail_map.get_load_factor() * 100 << "%" << std::endl;
      std::cout << "Capacity: " << trail_map.get_capacity() << std::endl;

      containers::hash_map_diagnositics_t d = trail_map.get_last_diagnositics();
      std::cout << "Last Operation's Diagnositics: iterations: [" << d.iterations
        << "] links_traversed: [" << d.links_traversed << "]" << std::endl << std::endl;
      std::cout << "== Binary Search Tree ==" << std::endl;
      containers::binary_tree_diagnositics_t b = trail_tree.get_last_diagnositics();
      std::cout << "Size: " << trail_tree.get_size() << std::endl;
      std::cout << "Last Operation's Diagnositics: iterations: [" << b.iterations
        << "] comparisons: [" << b.comparisons << "]" << std::endl << std::endl;
    } break;
    case menu_option_t::QUIT: {
      running = false;
      break;
    }
    case menu_option_t::CHOICE: {
      std::cout << "Welcome to the Trail Questionaire where we try and match your likes to a particular trail." << std::endl;
      bool distant = ask_yes_no_question("Want to go on a long hike (>5 kilometers)?");

      containers::linked_list_t<trail_t *> trails;
      containers::linked_list_t<trail_t *> filter;
      for (size_t i = 0; i < trail_map.get_capacity(); i++) {
        containers::bucket_t <const char *, trail_t *> *cb = &trail_map.get_buckets()[i];
        if (!cb->empty) {
          for (; cb; cb = cb->next) {
            if (distant) {
              if (cb->data->get_length_meters() >= 5000) {
                trails.append(cb->data);
              }
            }
            else {
              if (cb->data->get_length_meters() < 5000) {
                trails.append(cb->data);
              }
            }
          }
        }
      }

      if (trails.get_length() == 0) {
        std::cout << "Sorry, your query didn't return any results, try again with a different answer!" << std::endl << std::endl;
        break;
      }
      std::cout << "There are " << trails.get_length() << " options in your area." << std::endl;

      bool water = ask_yes_no_question("Do you want to see water?");
      for (containers::linked_node_t<trail_t *> *cur = trails.get_head(); cur; cur = cur->get_next()) {
        trail_t *t = cur->get_value();
        if (water) {
          if (t->get_views() & view_t::BEACH || t->get_views() & view_t::LAKE || t->get_views() & view_t::WATERFALL) {
            filter.append(t);
          }
        }
        else if(!water) {
          if ((t->get_views() & view_t::BEACH) == 0 && (t->get_views() & view_t::LAKE) == 0 && (t->get_views() & view_t::WATERFALL) == 0) {
            filter.append(t);
          }
        }
      }

      if (filter.get_length() == 0) {
        std::cout << "Sorry, your query didn't return any results, try again with a different answer!" << std::endl << std::endl;
        break;
      }
      std::cout << "There are " << filter.get_length() << " options in your area." << std::endl;

      bool caves = ask_yes_no_question("Want to see caves?");
      trails.empty();
      for (containers::linked_node_t<trail_t *> *cur = filter.get_head(); cur; cur = cur->get_next()) {
        trail_t *t = cur->get_value();
        if (caves) {
          if (t->get_views() & view_t::CAVE) {
            trails.append(t);
          }
        }
        else if (!caves) {
          if ((t->get_views() & view_t::CAVE) == 0) {
            trails.append(t);
          }
        }
      }

      if (trails.get_length() == 0) {
        std::cout << "Sorry, your query didn't return any results, try again with a different answer!" << std::endl << std::endl;
        break;
      }
      std::cout << "There are " << trails.get_length() << " options in your area." << std::endl;
      bool forest = ask_yes_no_question("Want to see forest?");
      filter.empty();
      for (containers::linked_node_t<trail_t *> *cur = trails.get_head(); cur; cur = cur->get_next()) {
        trail_t *t = cur->get_value();
        if (forest) {
          if (t->get_views() & view_t::FOREST) {
            filter.append(t);
          }
        }
        else if (!forest) {
          if ((t->get_views() & view_t::FOREST) == 0) {
            filter.append(t);
          }
        }
      }

      if (filter.get_length() == 0) {
        std::cout << "Sorry, your query didn't return any results, try again with a different answer!" << std::endl << std::endl;
        break;
      }
      std::cout << "There are " << filter.get_length() << " options in your area." << std::endl;
      for (containers::linked_node_t<trail_t *> *cur = filter.get_head(); cur; cur = cur->get_next()) {
        trail_t *t = cur->get_value();
        std::cout << *t << std::endl;
      }

      std::cout << std::endl;
    } break;
    default:
      std::cerr << "Invalid option" << std::endl;
    }
  }

  return 0;
}