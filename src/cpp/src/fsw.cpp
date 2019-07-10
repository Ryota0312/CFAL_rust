#define __STDC_WANT_LIB_EXT1__ 1
#define _XOPEN_SOURCE // for putenv
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <filter.hpp>
#include <monitor.hpp>
#include <monitor_factory.hpp>
#include "fsw.h"

void monitor_on_event(const std::vector<fsw::event>& events, void* unused) {
  for (const fsw::event& event : events) {

    time_t t = event.get_time();
    char str[81];
    
    std::strftime(str,sizeof(str),"%Y-%m-%dT%H:%I:%S",std::localtime(&t));
    
    std::cout << str << ",";
    std::cout << event.get_path() << ",";

    for (const fsw_event_flag& flag : event.get_flags()) {
      std::cout << fsw::event::get_event_flag_name(flag) << " ";
    }
    
    std::cout << std::endl;
  }
}

void fsw_test(char* path) {
  std::vector<std::string> paths{path};
  std::vector<fsw::monitor_filter> filters{
    {"/\\..*/", fsw_filter_type::filter_exclude},
    {"access_log", fsw_filter_type::filter_exclude},
    {"error_log", fsw_filter_type::filter_exclude}
  };
  std::vector<fsw_event_type_filter> events {
    {fsw_event_flag::Created},
    {fsw_event_flag::Updated},
    {fsw_event_flag::Removed},
    {fsw_event_flag::MovedFrom},
    {fsw_event_flag::MovedTo}
  };

  fsw::monitor* mon = fsw::monitor_factory::create_monitor(
        fsw_monitor_type::system_default_monitor_type,
        paths,
        &monitor_on_event
  );

  mon->set_recursive(true);
  mon->set_allow_overflow(true);
  mon->set_event_type_filters(events);
  mon->set_filters(filters);
  
  mon->start();
}
